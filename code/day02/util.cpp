#include "util.h"
#include <stdio.h>
#include <stdlib.h>
// Description: 这是对util.h中的errif的具体实现，方便其他的程序用，也就是说，头文件中放声明，声明具体在某个cpp文件中实现，其他cpp文件只需要包含相应的头文件就可以用这个声明了。
void errif(bool condition, const char *errmsg){
    if(condition){
        perror(errmsg);
        exit(EXIT_FAILURE);
    }
}
