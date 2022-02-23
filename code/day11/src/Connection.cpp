#include "Connection.h"
#include "Channel.h"
#include "Socket.h"
#include <string.h>
#include <unistd.h>
#include "Buffer.h"
#include "util.h"

#define READ_BUFFER 1024

Connection::Connection(EventLoop *_loop, Socket *_sock) : loop(_loop), clnt_sock(_sock), inBuffer(new std::string), readBuffer(nullptr){
    clnt_ch = new Channel(clnt_sock->getFd(), loop);
    std::function<void()> cb = std::bind(&Connection::handleReadEvent, this, clnt_sock->getFd());
    clnt_ch->setReadCallback(cb);
    clnt_sock->setnonblocking();

    clnt_ch->setUseThreadPoll(true);
    clnt_ch->enableReading();
    clnt_ch->useET();
    readBuffer = new Buffer();
}

Connection::~Connection(){
    delete clnt_sock;  
    delete clnt_ch;
    delete readBuffer;
}

void Connection::handleReadEvent(int sockfd){
    char buf[READ_BUFFER];
    int i = 1;
    while(true){
        bzero(buf, READ_BUFFER); // 这里和源程序有一点不同，源程序是&buf,但是我觉得buf已经是指针类型的了。
        ssize_t read_bytes = read(sockfd, buf, READ_BUFFER);
        if(read_bytes > 0){
            readBuffer->setbuf(buf, read_bytes);
        } else if(read_bytes == -1 && errno == EINTR){
            printf("continue reading");
            continue;
        } else if(read_bytes == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)){
            printf("the message from client %d : %s\n", sockfd, readBuffer->getbuf());
            printf("finish reading once. errno: %d\n", errno);
            errif(write(sockfd, readBuffer->getbuf(), readBuffer->getsize()) == -1, "socket write error!");
            readBuffer->clear();
            break;
        } else if(read_bytes == 0){
            printf("EOF, client fd %d disconnected\n", sockfd);
            deleteConnectionCallback(clnt_sock);
            break;
        }
    }
}

void Connection::setDeleteConnectionCallback(std::function<void(Socket*)> _cb){
    deleteConnectionCallback = _cb;
}