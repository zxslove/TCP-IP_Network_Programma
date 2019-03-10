/*
     阻塞的TCP服务器
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<iostream>
using namespace std;

#define ADDR_PORT 666
#define SOCKET_ERROR -1

int main()
{
    char buf[256];
    int listenfd, clientfd;
    struct sockaddr_in addr, client_addr;

    // 1.创建侦听套接字
    listenfd = socket(PF_INET, SOCK_STREAM, 0);
    if(listenfd == SOCKET_ERROR)
    {
        std::cout << "create lsiten socket error" << std::endl;
    }

    // 2.绑定IP和端口号
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(ADDR_PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);   //inet_pton()
    if(bind(listenfd, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        std::cout << "bind() function error" << std::endl;
    }

    // 3.指定同一时刻的最大连接数
    if(listen(listenfd, 128) == SOCKET_ERROR)
    {
        std::cout << "listen() function error" << std::endl;
    }


    socklen_t clientaddr_len;
    clientaddr_len = sizeof(client_addr);
    while(true)
    {
        menset(&client_addr, 0, sizeof(client_addr));
        // 4.等待用户发起连接
        clientfd = accept(listenfd, (struct sockaddr*)&client_addr, &clientaddr_len)
        if(clientfd == SOCKET_ERROR)
        {
            std::cout << "accept() function error" << std::endl;
            return;
        }

        size_t readBuf = 0;
        readBuf = read(clientfd, &buf, sizeof(buf));
        if(readBuf == -1)
        {
            std::cout << "read data error" << std::endl;
        }

        if(wrtite(clientfd, buf, sizeof(buf) == -1)
        {
            std::cout << "write data error" << std::endl;
        }
        close(clientfd);
    }

    close(listenfd);
    return 0;
}

//可以用nc ip地址 端口号 模拟客户端连接