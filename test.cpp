// Copyright (C) 2015  .
// Author: davidluan
// CreateTime: 2015-03-03

#include "stdio.h"
#include "sys/epoll.h"

int main(int argc, const char *argv[])
{
    fprintf(stderr, "sizeof(epoll_data)=%u\n", sizeof(epoll_data));
    fprintf(stderr, "sizeof(void*)=%u\n", sizeof(void*));
    fprintf(stderr, "sizeof(int)=%u\n", sizeof(int));
    fprintf(stderr, "sizeof(uint32_t)=%u\n", sizeof(uint32_t));
    return 0;
}


