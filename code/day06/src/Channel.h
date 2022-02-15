#pragma once
#include <sys/epoll.h>
#include <functional>

class EventLoop;

class Channel{
    private:
        EventLoop *loop;
        int fd;
        uint32_t events;
        uint32_t revents;
        bool inEpoll;
        std::function<void ()> callback;
    public:
        Channel(int _fd, EventLoop *_loop);
        ~Channel();

        void enableReading();
        void handleEvent();
        void setCallback(std::function<void ()>);
        void setRevents(uint32_t);
        uint32_t getRevents();
        uint32_t getEvents();
        bool getInEpoll();
        void setInEpoll();
        int getFd();
};