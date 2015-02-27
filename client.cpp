// Copyright (C) 2015  .
// Author: davidluan
// CreateTime: 2015-02-11
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "errno.h"
#include "time.h"

#include <stdlib.h>


#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <netinet/in.h>
int set_noblock(int iSock)
{
    int iFlag;

    iFlag = fcntl(iSock, F_GETFL, 0);

    iFlag |= O_NONBLOCK;
    iFlag |= O_NDELAY;

    fcntl(iSock, F_SETFL, iFlag);

    return 0;

}

int main(int argc, const char *argv[])
{
//    int listen_fd = init_server("0.0.0.0", 9900);
//
    int reuse =1 ;
    int socketfd;
    struct sockaddr_in address;
    const char *szIp;
    unsigned short shPort;

    szIp = argv[1];
    shPort = atoi(argv[2]);


    memset((void*)&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    inet_aton(szIp, &address.sin_addr);
    address.sin_port = htons(shPort);


    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if(socketfd < 0)
    {
        fprintf(stderr, " socketfd error %d\n", socketfd);
        return -1;
    }

    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse) );

    set_noblock(socketfd);
    int ret(0);

    if((ret = connect(socketfd, (struct sockaddr *) &address, sizeof(address)))< 0 )
    {
        if(errno != EINPROGRESS)
        {

        fprintf(stderr, "connect error %d, errno:%d, msg:%s\n", ret, errno, strerror(errno));
        return -2;
        }
    }

    fprintf(stdout, "connect success \n");


    while(1)
    {
        sleep(1);
        char szBuff[1024];
        memset(szBuff, 0 ,sizeof(szBuff));
        snprintf(szBuff,sizeof(szBuff), "hellow");

        int sendret = send(socketfd,szBuff, 5, 0 );
        fprintf(stdout, "send success :%d , data:%s\n", sendret, szBuff);


        int recvret = recv(socketfd, szBuff, sizeof(szBuff), 0 );
        fprintf(stdout, "recv success :%d , data:%s\n", recvret, szBuff);


    }

    return 0;
}
