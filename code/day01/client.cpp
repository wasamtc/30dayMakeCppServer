/*
 * @Author: wasam
 * @Date: 2022-01-24
 * @LaseEditTime: 2022-01-24
 * @LastEditors: wasam
 * @Description: 编写客户端的代码，首先是引入相应的头文件，然后是创立一个套接字，然后一个结构体绑定ip和端口，最后用connect函数用套接字连接相应的地址端口连接服务器
 * FilePath: test
 */
 #include <sys/socket.h> // 这个头文件包含socket()用来创建一个socket,还包含bind
 #include <arpa/inet.h> // 这个头文件包含结构体sockaddr_in
 #include <cstring> // 包含bzero
 int main(){
     int sockfd = socket(AF_INET, SOCK_STREAM, 0); 
     /* 
      * AF_INET代表IP地址类型，这里是ipv4，第二个参数代表数据传输方式，SOCK_STREAM表示流格式、面向连接，多用于TCP。SOCK_DGRAM表示数据报格式、无连接，多用于UDP。
      * 第三个代表协议, 0表示根据前面的两个参数自动推导协议类型。设置为IPPROTO_TCP和IPPTOTO_UDP，分别表示TCP和UDP。
      * 关于TCP与UDP的区别：http://c.biancheng.net/view/2124.html 以及 https://zhuanlan.zhihu.com/p/24860273
      */
     struct sockaddr_in serv_addr; // 关于sockaddr_in和sockaddr的区别见：https://blog.csdn.net/will130/article/details/53326740/
     bzero(&serv_addr, sizeof(serv_addr)); // 将字符串s的前n个字节置为0，一般来说n通常取sizeof(s),将整块空间清零。也可以将一个结构体清零
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // inet_addr()作用是将一个IP字符串转化为一个网络字节序的整数值，用于sockaddr_in.sin_addr.s_addr。
     serv_addr.sin_port = htons(8888); // htons()作用是将端口号由主机字节序转换为网络字节序的整数值。(host to net)
     
     connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr));
     /*
      * 定义函数：int connect(int sockfd, struct sockaddr * serv_addr, int addrlen);
      * sockfd：标识一个套接字  serv_addr：套接字s想要连接的主机地址和端口号  addrlen：name缓冲区的长度。
      */
      
      return 0;
     
 }
