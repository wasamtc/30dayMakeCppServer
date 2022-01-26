/*
 *Author: wasamtc
 *EditTime: 2022-01-26 15:31
 *LastEditors: wasamtc
 *LastEditTime: 2022-01-26 15:31
 *Description: 服务端，创建接口，创建地址，绑定接口地址，监听接口，创建epoll，添加服务端接口到epoll，等待事件，判断事件，若为服务端事件则接受客户端连接，添加到epoll，若为可读事件则读取并写出。
 *FilePath: test
 */
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/epoll.h>  
#include "util.h"


#define MAXEVENT 1024


int main(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    errif(sockfd == -1, "socket create error!");
    
    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8888);
    
    errif(bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) == -1, "socket bind error!");
    
    errif(listen(sockfd, SOMAXCONN) == -1, "socket listen error!");
    
    int epfd = epoll_create1(0); //创建内核事件表
    struct epoll_event event[MAXEVENT], ev;
    bzero(&event, sizeof(event));
    bzero(&ev, sizeof(ev));
    
    ev.data.fd = sockfd;
    ev.events = EPOLLIN; //EPOLLIN：连接到达；有数据来临；
    setnonblocking(sockfd);
    errif(epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev) == -1, "epoll add error!");
    
    while(true){
        int nfds = epoll_wait(epfd, event, MAXEVENT, -1);
        errif(nfds == -1, "epoll wait error!");
        for(int i = 0; i<nfds; ++i){
            if(sockfd == event[i].data.fd){
                struct sockaddr_in clnt_addr;
                socklen_t clnt_addr_len = sizeof(clnt_addr);
                bzero(&clnt_addr, sizeof(clnt_addr));
                
                int clnt_sockfd = accept(sockfd, (sockaddr*)&clnt_addr, &clnt_addr_len);
                errif(clnt_sockfd == -1, "socket accept error!");
                printf("new client fd %d IP:%s\n", clnt_sockfd, inet_ntoa(clnt_addr.sin_addr));
                ev.events = EPOLLIN;
                ev.data.fd = clnt_sockfd;
                setnonblocking(clnt_sockfd);
                errif(epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sockfd, &ev) == -1, "epoll_clnt add error!");
            } else if(event[i].events & EPOLLIN){
                char buf[1024];
                while(true){
                    bzero(&buf, sizeof(buf));
                    int read_bytes = read(event[i].data.fd, buf, sizeof(buf));
                    if(read_bytes > 0){
                        printf("message from client fd %d : %s\n", event[i].data.fd, buf);
                        write(event[i].data.fd, buf, sizeof(buf));
                    } else if(read_bytes == 0){
                        printf("client fd %d already disconnected!\n", event[i].data.fd);
                        close(event[i].data.fd);
                        break;
                    } else if(read_bytes == -1 && errno == EINTR){
                        printf("continue reading");
                        continue;
                    } else if(read_bytes == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){
                        printf("finish reading. errno:%d\n", errno);
                        break;
                    }
                }
            } else{
                printf("something else happened\n");
            }
        }
    }
    close(sockfd);
    
    return 0;
}
