#pragma once

class EventLoop;
class Socket; 
class Server{
    private:
        EventLoop *loop;
    public:
        Server(EventLoop*);
        ~Server();

        void handleReadEvent(int sockfd);
        void newConnection(Socket*);
};