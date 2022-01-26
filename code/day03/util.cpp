#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include "util.h"


void errif(bool condition, const char* message){
    if(condition == 1){
        perror(message);
        exit(EXIT_FAILURE);
    }
}

void setnonblocking(int fd){
    fcntl(fd, F_SETFL, O_NONBLOCK);
}
