#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "errno.h"
#include "time.h"
#include <sys/epoll.h>

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
#define MAX_EVENT 1000
char szRecvBuff[4096];
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

void main_loop(int listen_fd)
{

    int epfd = epoll_create(1);
    if(epfd == -1)
    {
        perror("create epoll fd error");
        exit(-1);
    }


    struct epoll_event ev, events[MAX_EVENT];

    ev.events = EPOLLIN;
    ev.data.fd = listen_fd;
    if(epoll_ctl(epfd, EPOLL_CTL_ADD, listen_fd, &ev))
    {
        fprintf(stderr, "epoll add error:%d\n",listen_fd );

        exit(-1);
    }

    while(1)
    {
        int nready = epoll_wait(epfd, events, MAX_EVENT, -1);
        if(nready == -1)
        {
            perror("epollwait");
            exit(-1);
        }
        if(nready <= 0 )
        {
            sleep(1);
            continue;
        }

        printf("epoll, ready %d\n", nready);
        for(int i = 0;i < nready; i++)
        {
            if(events[i].data.fd == listen_fd)
            {
                printf("accept new connecting\n");
                int conn_fd= accept(listen_fd, NULL, NULL );
                if(conn_fd< 0)
                {
                    if(errno != EINTR)
                    {
                        perror("accept");
                        close(listen_fd);
                        exit(-1);
                    }
                    else
                    {
                        continue;
                    }
                }

                set_noblock(conn_fd);

                ev.events = EPOLLIN;
                ev.data.fd = conn_fd;
    //            ev.data.u32 = time(NULL);
                if(epoll_ctl(epfd, EPOLL_CTL_ADD, conn_fd, &ev))
                {
                    fprintf(stderr, "epoll add error:%d, line:%d\n",listen_fd, __LINE__ );
                    exit(-1);
                }
            }
            else
            {
                do_fd(events[i].data.fd);
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

