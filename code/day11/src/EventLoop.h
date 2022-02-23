#pragma once
#include <functional>
class Channel;
class Epoll;
class ThreadPoll;
class EventLoop
{
private:
    Epoll *ep;
    bool quit;
    ThreadPoll *threadpoll;
public:
    EventLoop();
    ~EventLoop();
    void loop();
    void updateChannel(Channel *);
    void addThread(std::function<void()>);
};