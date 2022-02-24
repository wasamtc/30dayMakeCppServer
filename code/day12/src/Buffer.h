#pragma once
#include <string>

class Buffer
{
private:
    std::string buf;
public:
    Buffer();
    ~Buffer();
    void setbuf(const char *_str, int _size = 10);
    ssize_t getsize();
    const char* getbuf();
    void clear();
    void getline();
};
