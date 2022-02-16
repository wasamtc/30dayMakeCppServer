#pragma once
#include <functional>

class Socket;
class Channel;
class EventLoop;
class Connection
{
private:
    Socket *clnt_sock;
    Channel *clnt_ch;
    EventLoop *loop;
    std::function<void(Socket*)> deleteConnectionCallback;
public:
    Connection(EventLoop *_loop, Socket *_sock);
    void handleReadEvent(int sockfd);
    void setDeleteConnectionCallback(std::function<void(Socket*)>);
    ~Connection();
};
