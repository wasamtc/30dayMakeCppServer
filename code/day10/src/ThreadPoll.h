#pragma once
#include <thread>
#include <queue>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPoll
{
private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex tasks_mtx;
    std::condition_variable cv;
    bool stop;
public:
    ThreadPoll(int size = std::thread::hardware_concurrency());
    ~ThreadPoll();
    void addTask(std::function<void()>);
};
