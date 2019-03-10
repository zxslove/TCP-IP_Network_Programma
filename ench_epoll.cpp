/*
    采用epoll的回声服务端
*/
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/scoket.h>
#include <sys/epoll.h>
#include <string.h>
#include <fcntl.h>
#include <error.h>
#include <iostream>

#define sock_error -1;
#define BUF_SIZE 4;
#define EPOLL_SIZE 50;
void setNonBlock_socket(int fd);

int main(int argc, char* argv[])
{
    int listenfd, clientfd;
    struct sockaddr_in serv_addr, clen_addr;
    socklen_t len;
    char buf[BUF_SIZE];
    int str_len;

    //epoll
    int ep_fd;  //epoll例程返回的文件描述符
    struct epoll_event event;   //监视对象的事件类型
    struct epoll_event* ep_events; //保存发生事件的文件描述符集合的结构地址值
    int event_cnt;

    listenfd = socket(PF_INET, SOCK_STREAM, 0);
    if(listenfd == sock_error)
    {
        std::cout << " create listen socket error!" << std::endl;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(INADDR_ANY);

    if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == sock_error)
    {
        std::cout << "bind listenfd socket error!" << std::endl;
    }

    if(listen(listenfd, 128) == sock_error)
    {
        std::cout << "listen socket error!" << std::endl;
    }

    //use epoll
    ep_fd = epoll_create(EPOLL_SIZE);
    if(ep_fd == -1)
    {
        std::cout << "epoll_crate error!" << std::endl;
    }
    ep_events = malloc(sizeof(struct epoll_event)*EPOLL_SIZE);

    //将套接字设置为非阻塞
    setNonBlock_socket(listenfd);

    event.events = EPOLLIN;
    event.data.fd = listenfd;
    epoll_ctl(ep_fd, EPOLL_CTL_ADD, listenfd, &event);

    while(1)
    {
        event_cnt = epoll_wait(ep_fd, ep_events, EPOLL_SIZE, -1);
        if(event_cnt == -1)
        {
            std::cout << "epoll_wait error!" << std::endl;
            break;
        }

        std::cout <<"epool wait"<< std::endl
        for(int i = 0; i < event_cnt; ++i)
        {
            //新的客户端连接请求
            if(ep_events[i].data.fd == listenfd)
            {
               len = sizeof(clen_addr);
               clientfd = accept(listenfd, (struct sockaddr*)&clen_addr, &len);
               if(clientfd == sock_error)
               {
                   std::cout << "accept error!" << std::endl;
                   continue;
               } 

               setNonBlock_socket(clientfd);
               event.events = EPOLLIN | EPOLLET;   //改为边缘触发模式
               event.data.fd = clientfd;
               epoll_ctl(ep_fd, EPOLL_CTL_ADD, listenfd, &event);
               printf("client connecting: %d\n", clientfd);
            }
            else
            {
                while(1)
                {
                    str_len = read(ep_events[i].data.fd, buf, BUF_SIZE);
                    if(str_len == 0)
                    {
                        epoll_ctl(ep_fd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                        close(ep_events[i].data.fd);
                        printf("close client: %d\n", ep_events[i].data.fd);
                        break;
                    }
                    else if(str_len < 0)
                    {
                        //str_len == -1 and errno = EAGAIN 说明已经读取全部输入缓冲区的数据
                        if(errno = EAGAIN)
                            break;
                    }
                    else
                    {
                        //write
                        write(ep_events[i].data.fd, buf, str_len);
                    }

                }
            }
        }
    }

    close(listenfd);
    close(ep_fd);
    return 0;
}

void setNonBlock_socket(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags|O_NONBLOCK);
}