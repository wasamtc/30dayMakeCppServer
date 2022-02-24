/*
 * Author: wasamtc
 * EditTime: 2022-02-16 15:49
 * LastEditors: wasamtc
 * LastEditTime: 2022-02-24 19:34
 * Description: 把连接抽象为Conneciton类，并在类中完成对事件的处理(这一天俄罗斯进攻了乌克兰)
 */

#include "Server.h"
#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"
#include "InetAddress.h"
#include "Acceptor.h"
#include <string.h>
#include <unistd.h>
#include "Connection.h"
#include "ThreadPoll.h"

#define READ_BUFFER 1024
Server::Server(EventLoop *_loop){
    mainReactor = _loop;
    acceptor = new Acceptor(mainReactor);
    std::function<void(Socket*)> cb = std::bind(&Server::newConnection, this, std::placeholders::_1);
    acceptor->setNewConnectionCallback(cb);

    int size = std::thread::hardware_concurrency();
    thpoll = new ThreadPoll(size);
    for(int i = 0; i < size; ++i){
        subReactor.push_back(new EventLoop());
        std::function<void()> sub_loop = std::bind(&EventLoop::loop, subReactor[i]);
        thpoll->addTask(sub_loop);
    }

}

Server::~Server(){
    delete acceptor;
}

void Server::newConnection(Socket* clnt_sock){
    if(clnt_sock->getFd() != -1){
        int random = clnt_sock->getFd() % subReactor.size();
        Connection *clnt_conn = new Connection(subReactor[random], clnt_sock);
        std::function<void(Socket*)> cb = std::bind(&Server::deleteConnection, this, std::placeholders::_1);
        clnt_conn->setDeleteConnectionCallback(cb);
        connections[clnt_sock->getFd()] = clnt_conn;
    }

}

void Server::deleteConnection(Socket *clnt_sock){
    Connection *conn = connections[clnt_sock->getFd()];
    connections.erase(clnt_sock->getFd());
    delete conn;
}