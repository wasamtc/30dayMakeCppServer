/*
 * Author: wasam
 * Date: 2022-01-24
 * LastEditTime: 2022-01-24
 * LastEditor: wasam
 * Description: 服务端，首先是创建套接字，然后是创建一个结构体与地址端口绑定再与套接字绑定，然后监听套接字，然后创建接受存储客户信息的套接字，用accept函数接受客户端的请求
 * FilePath: test
 */
 #include <stdio.h>
 #include <sys/socket.h>
 #include <arpa/inet.h>
 #include <cstring>
 
 int main(){
     int sockfd = socket(AF_INET, SOCK_STREAM, 0);
     
     struct sockaddr_in serv_addr;
     bzero(&serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 用inet_addr将ip地址转化为网络字节序
     serv_addr.sin_port = htons(8888); // host to net short 用htons将端口号转化为网络字节序
     
     bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr));
     /*
      * 将一本地地址与一套接口捆绑。本函数适用于未连接的数据报或流类套接口，在connect()或listen()调用前使用。
      * 当用socket()创建套接口后，它便存在于一个名字空间（地址族）中，但并未赋名。bind()函数通过给一个未命名套接口分配一个本地名字来为套接口建立本地捆绑（主机地址/端口号）。
      * int bind( int sockfd , const struct sockaddr * my_addr, socklen_t addrlen);
      * 参数列表中，sockfd 表示已经建立的socket编号（描述符）；my_addr 是一个指向sockaddr结构体类型的指针；参数addrlen表示my_addr结构的长度，可以用sizeof操作符获得。
      */
     listen(sockfd, SOMAXCONN); // listen函数监听这个socket端口，这个函数的第二个参数是listen函数的最大监听队列长度，系统建议的最大值SOMAXCONN被定义为128。
     
     struct sockaddr_in clnt_addr;
     socklen_t clnt_addr_len = sizeof(clnt_addr);
     bzero(&clnt_addr, sizeof(clnt_addr));
     
     int clnt_sockfd = accept(sockfd, (sockaddr*)&clnt_addr, &clnt_addr_len);
     /*
      * 返回值是一个新的套接字描述符，它代表的是和客户端的新的连接，可以把它理解成是一个客户端的socket,这个socket包含的是客户端的ip和port信息 。
      * addr用于存放客户端的地址，addrlen在调用函数时被设置为addr指向区域的长度，在函数调用结束后被设置为实际地址信息的长度。本函数会阻塞等待知道有客户端请求到达。
      * 要注意和accept和bind的第三个参数有一点区别，对于bind只需要传入serv_addr的大小即可，而accept需要写入客户端socket长度，所以需要定义一个类型为socklen_t的变量
      * 另外，accept函数会阻塞当前程序，直到有一个客户端socket被接受后程序才会往下运行。
      */
     printf("new client fd %d! IP:%s Port:%d\n", clnt_sockfd, inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));
      
     return 0;
     
     
 }
