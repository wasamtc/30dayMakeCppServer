#include "Channel.h"
#include "EventLoop.h"
#include <unistd.h>

Channel::Channel(int _fd, EventLoop *_loop) : events(0), revents(0), inEpoll(false), ready(0){
    fd = _fd;
    loop = _loop;
}

Channel::~Channel(){
    if(fd != -1){
        close(fd);
        fd = -1;
    }
}

void Channel::enableReading(){
    events = EPOLLIN | EPOLLPRI;
    loop->updateChannel(this);
}

int Channel::getFd(){
    return fd;
}

uint32_t Channel::getEvents(){
    return events;
}

uint32_t Channel::getRevents(){
    return revents;
}

bool Channel::getInEpoll(){
    return inEpoll;
}

void Channel::setInEpoll(){
    inEpoll = true;
}

void Channel::setRevents(uint32_t _ev){
    revents = _ev;
}

uint32_t Channel::getReady(){
    return ready;
}

void Channel::setReady(uint32_t _ready){
    ready = _ready;
}

void Channel::handleEvent(){
    if(ready & (EPOLLIN || EPOLLPRI)){
        readCallback();
        
    }
    if(ready & (EPOLLOUT)){
        writeCallback();
    }
}

void Channel::setReadCallback(std::function<void ()> _cb){
    readCallback = _cb;
}


void Channel::useET(){
    events |= EPOLLET;
    loop->updateChannel(this);
}