#include "Server.h"
#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"
#include "InetAddress.h"
#include <string.h>
#include <unistd.h>

#define READ_BUFFER 1024
Server::Server(EventLoop *_loop){
    loop = _loop;
    Socket *serv_sock = new Socket();
    InetAddress *serv_addr = new InetAddress("127.0.0.1", 8888);
    serv_sock->bind(serv_addr);
    serv_sock->listen();
    serv_sock->setnonblocking();

    Channel *serv_ch = new Channel(serv_sock->getFd(), _loop);
    std::function<void()> cb = std::bind(&Server::newConnection, this, serv_sock);
    serv_ch->setCallback(cb);
    serv_ch->enableReading();
}

Server::~Server(){

}

void Server::handleReadEvent(int sockfd){
    char buf[READ_BUFFER];
    int i = 1;
    while(true){
        bzero(buf, READ_BUFFER); // 这里和源程序有一点不同，源程序是&buf,但是我觉得buf已经是指针类型的了。
        ssize_t read_bytes = read(sockfd, buf, READ_BUFFER);
        if(read_bytes > 0){
            printf("the message from client %d : %s\n", sockfd, buf);
            write(sockfd, buf, sizeof(buf));
        } else if(read_bytes == -1 && errno == EINTR){
            printf("continue reading");
            continue;
        } else if(read_bytes == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)){
            printf("finish reading once. errno: %d\n", errno);
            break;
        } else if(read_bytes == 0){
            printf("EOF, client fd %d disconnected\n", sockfd);
            close(sockfd);
            break;
        }
    }
}

void Server::newConnection(Socket* serv_sock){
    InetAddress *clnt_addr = new InetAddress();
    Socket *clnt_sock = new Socket(serv_sock->accept(clnt_addr));
    printf("new client fd:%d, ip:%s, port:%d\n", clnt_sock->getFd(), inet_ntoa(clnt_addr->addr.sin_addr), ntohs(clnt_addr->addr.sin_port));
    clnt_sock->setnonblocking();
    Channel *clntChannel = new Channel(clnt_sock->getFd(), loop);
    std::function<void()> cb = std::bind(&Server::handleReadEvent, this, clnt_sock->getFd());
    clntChannel->setCallback(cb);
    clntChannel->enableReading();
}