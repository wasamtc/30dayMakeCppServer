#include "Server.h"
#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"
#include "InetAddress.h"
#include "Acceptor.h"
#include <string.h>
#include <unistd.h>
/*
 * Author: wasamtc
 * EditTime: 2022-02-16 15:49
 * LastEditors: wasamtc
 * LastEditTime: 
 * Description: 把连接抽象为Conneciton类，并在类中完成对事件的处理
 */
#include "Connection.h"

#define READ_BUFFER 1024
Server::Server(EventLoop *_loop){
    loop = _loop;
    acceptor = new Acceptor(loop);
    std::function<void(Socket*)> cb = std::bind(&Server::newConnection, this, std::placeholders::_1);
    acceptor->setNewConnectionCallback(cb);
}

Server::~Server(){
    delete acceptor;
}

void Server::newConnection(Socket* clnt_sock){
    Connection *clnt_conn = new Connection(loop, clnt_sock);
    std::function<void(Socket*)> cb = std::bind(&Server::deleteConnection, this, std::placeholders::_1);
    clnt_conn->setDeleteConnectionCallback(cb);
    connections[clnt_sock->getFd()] = clnt_conn;
}

void Server::deleteConnection(Socket *clnt_sock){
    Connection *conn = connections[clnt_sock->getFd()];
    connections.erase(clnt_sock->getFd());
    delete conn;
}