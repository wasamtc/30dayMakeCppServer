#pragma once
#include <functional>

class EventLoop;
class Channel;
class Socket;
class InetAddress;

class Acceptor
{
private:
    EventLoop *loop;
    Channel *acceptChannel;
    Socket *sock;
    InetAddress *addr;
public:
    Acceptor(EventLoop *_loop);
    ~Acceptor();
    void acceptConnection();
    std::function<void(Socket*)> newConnectionCallback;
    void setNewConnectionCallback(std::function<void(Socket*)>);
};


