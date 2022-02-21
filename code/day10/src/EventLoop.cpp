#include "EventLoop.h"
#include "Epoll.h"
#include <vector>
#include "Channel.h"
#include "ThreadPoll.h"

EventLoop::EventLoop() : quit(false){
    ep = new Epoll();
    threadpoll = new ThreadPoll();
}

EventLoop::~EventLoop(){
    delete ep;
    delete threadpoll;
}

void EventLoop::loop(){
    while(!quit){
        std::vector<Channel*> chs = ep->poll();
        for(auto it = chs.begin(); it != chs.end(); ++it){
            (*it)->handleEvent();
        }
    }
}

void EventLoop::updateChannel(Channel *ch){
    ep->updateChannel(ch);
}

void EventLoop::addThread(std::function<void()> func){
    threadpoll->addTask(func);
}