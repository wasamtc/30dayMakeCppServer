#include "Channel.h"
#include "EventLoop.h"


Channel::Channel(int _fd, EventLoop *_loop) : events(0), revents(0), inEpoll(false){
    fd = _fd;
    loop = _loop;
}

Channel::~Channel(){

}

void Channel::enableReading(){
    events = EPOLLIN | EPOLLET;
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

void Channel::handleEvent(){
    callback();
}

void Channel::setCallback(std::function<void ()> _cb){
    callback = _cb;
}