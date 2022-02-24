#pragma once
#include <map>
#include <vector>

class EventLoop;
class Socket; 
class Acceptor;
class Connection;
class ThreadPoll;
class Server
{
private:

    EventLoop *mainReactor;
    std::vector<EventLoop*>subReactor;
    ThreadPoll *thpoll;
    Acceptor *acceptor;
    std::map<int, Connection*> connections;
public:
    Server(EventLoop*);
    ~Server();
    
    void deleteConnection(Socket*);
    void newConnection(Socket*);
};