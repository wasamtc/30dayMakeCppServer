#pragma once
#include <sys/epoll.h>
#include <functional>

class EventLoop;

class Channel
{
private:
    EventLoop *loop;
    int fd;
    uint32_t events;
    uint32_t revents;
    uint32_t ready;
    bool inEpoll;
    std::function<void ()> readCallback;
    std::function<void ()> writeCallback;
public:
    Channel(int _fd, EventLoop *_loop);
    ~Channel();

    void enableReading();
    void handleEvent();
    void setReadCallback(std::function<void ()>);
    void setRevents(uint32_t);
    uint32_t getRevents();
    uint32_t getEvents();
    uint32_t getReady();
    void setReady(uint32_t);
    bool getInEpoll();
    void setInEpoll();
    void useET();
    int getFd();
};