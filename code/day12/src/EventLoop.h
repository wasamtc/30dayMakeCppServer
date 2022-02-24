#pragma once
#include <functional>
class Channel;
class Epoll;
class EventLoop
{
private:
    Epoll *ep;
    bool quit;
public:
    EventLoop();
    ~EventLoop();
    void loop();
    void updateChannel(Channel *);
};