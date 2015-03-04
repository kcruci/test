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
    return 0;

}

int init_server( char * sIp, unsigned short shPort)
{
    int reuse =1 ;
    int socketfd;
    struct sockaddr_in address;

    memset((void*)&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    inet_aton("0.0.0.0", &address.sin_addr);
    address.sin_port = htons(shPort);


    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if(socketfd < 0)
    {
        fprintf(stderr, " socketfd error %d\n", socketfd);
        return -1;
    }

    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse) );

    if(bind( socketfd,  (sockaddr *)&address, sizeof(address))< 0)
    {
        perror("bind error");
        close(socketfd);
        return -2;
    }


    if( listen(socketfd, 1012)< 0)
    {
        perror("listen error");
        close(socketfd);
        return -3;
    }
    return socketfd;
}

#define MAXFD_CNT 1024
char szRecvBuff[4096];

int ReadSelect(int maxfd , fd_set* fdset)
{
    timeval tm;

    memset(&tm, 0, sizeof(tm));
    tm.tv_sec = 0;
    tm.tv_usec = 500;
    int iRet = select(maxfd+1, fdset, NULL, NULL,&tm);

    return iRet;
}

void do_fd(int fd)
{
    int iConnectFd = fd;
    printf("process new data iConnectFd:%d\n",iConnectFd);

    memset(szRecvBuff, 0 , sizeof(szRecvBuff));

    int len = recv(iConnectFd, szRecvBuff, sizeof(szRecvBuff),0);

    printf("client data len:%d, value:%s\n", len, (char*)szRecvBuff);
    //printf("server data is:%u\n", time(NULL));


    char szBuff[1024];
    memset(szBuff, 0 , sizeof(szBuff));

    snprintf(szBuff, sizeof(szBuff),"%s world, time:%u", szRecvBuff, time(NULL));

    len = send(iConnectFd, szBuff, sizeof(szBuff),0);
    printf("server data len:%d, value::%s\n", len, (char*)szBuff);




}
int main_loop(int iListenSock)
{
    fd_set readfds;
    fd_set masterfds;

    FD_ZERO(&readfds);
    FD_ZERO(&masterfds);
    FD_SET(iListenSock, &readfds);
    FD_SET(iListenSock, &masterfds);
    int max_fd = iListenSock;

    printf("listen sock fd :%d\n", max_fd);
    while(true)
    {
        int nready(0);
        memcpy(&readfds, &masterfds, sizeof(fd_set));
        nready= ReadSelect(max_fd, &readfds);
        printf("select maxfd:%d, ready %d\n", max_fd, nready);
        if(nready <= 0 )
        {
            sleep(1);
            continue;
        }

        if(nready> 0 )
        {
            for(int i=3; i < MAXFD_CNT,nready>0;i++)
            {
                if(FD_ISSET(i, &readfds))
                {
                    nready --;

                    //accept for new  connecting sock
                    if(i == iListenSock)
                    {
                        printf("accept new connecting\n");
                        int ConnectedFd = accept(iListenSock, NULL, NULL );
                        if(ConnectedFd < 0)
                        {
                            if(errno != EINTR)
                            {
                                perror("accept");
                                close(iListenSock);
                                exit(-1);
                            }
                            else
                            {
                                continue;
                            }
                        }

                        FD_SET(ConnectedFd, &masterfds);

                        if(ConnectedFd > max_fd)
                            max_fd = ConnectedFd;
                        //FD_ADD(ConnectedFd);
                    }
                    //process for the sock
                    else
                    {
                        do_fd(i);

                          //                  close(iConnectFd);
     //                 FD_CLR(iConnectFd, &masterfds);

                        //modify the maxfd here!!

                    }
                }
            }

        }
    }

}
void usage(const char * name)
{
    fprintf(stderr, "%s port\n", name);
}



int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        usage(argv[0]);
        exit(-1);
    }

    unsigned short shPort = atoi(argv[1]);
    int listen_fd = init_server("0.0.0.0", shPort);
    set_noblock(listen_fd);

    main_loop(listen_fd);

    return 0;
}
