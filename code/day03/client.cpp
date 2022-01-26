/*
 *Author: wasamtc
 *EditTime: 2022-01-26 14:59
 *LastEditors: wasamtc
 *LastEditTime: 2020-01-26 15:00
 *Description: 客户端，创建接口，创建并初始化地址结构体，连接服务端，进入循环，输入数据，写数据到服务端，写成功则读取相应数据，对读取数据进行判断输出，循环完成。
 *FilePath: test/
 */
 #include <stdlib.h>
 #include <stdio.h>
 #include <unistd.h>
 #include <sys/socket.h>
 #include <arpa/inet.h>
 #include <string.h>
 #include "util.h"
 
 
 int main(){
     int sockfd = socket(AF_INET, SOCK_STREAM, 0);
     errif(sockfd == -1, "socket create error!");
     
     sockaddr_in serv_addr;
     bzero(&serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
     serv_addr.sin_port = htons(8888);
     
     errif(connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) == -1, "socket connect error!");
     
     char buf[1024];
     bzero(&buf, sizeof(buf));
     
     while(true){
         scanf("%s", buf);
         ssize_t write_bytes = write(sockfd, buf, sizeof(buf));
         if(write_bytes == -1){
             printf("socket already disconnected!\n");
             break;    
         }
         
         bzero(&buf, sizeof(buf));
         ssize_t read_bytes = read(sockfd, buf, sizeof(buf));
         if(read_bytes > 0){
             printf("message from server: %s\n", buf);
         }else if(read_bytes == 0){
             printf("socket already disconnected!\n");
             break;
         }else if(read_bytes == -1){
             errif(true, "socket read error!");
             close(sockfd);
         }
     }
     close(sockfd);
     
     return 0;
 }
