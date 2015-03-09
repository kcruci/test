// Copyright (C) 2015  .
// Author: davidluan
// CreateTime: 2015-03-03

#include "stdio.h"
#include "sys/epoll.h"

void test()
{
    return ;

}

int main(int argc, const char *argv[])
{
    fprintf(stderr, "sizeof(epoll_data)=%u\n", sizeof(epoll_data));
    fprintf(stderr, "sizeof(void*)=%u\n", sizeof(void*));
    fprintf(stderr, "sizeof(int)=%u\n", sizeof(int));
    fprintf(stderr, "sizeof(uint32_t)=%u\n", sizeof(uint32_t));
    fprintf(stderr, "sizeof(uint64_t)=%u\n", sizeof(uint64_t));

    exit(0);
    exit(1);
    // return 0;
    exit(25);
//    fprintf(stderr, "sizeof(uint64_t)=%u\n", sizeof(uint64_t));

    sleep(1);
    sleep(3);
    return 0;
}




