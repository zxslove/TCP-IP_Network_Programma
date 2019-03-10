#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/scoket.h>
#include <iostream>

#define sock_error -1;

int main(int argc, char* argv[])
{
    int listenfd, clientfd;
    struct sockaddr_in serv_addr, clen_addr;
    socklen_t len;
    FILE* readfp;
    FILE* writefp;
    char buf[30];

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

    while(1)
    {
        len = sizeof(clen_addr);
        clientfd = accept(listenfd, (struct sockaddr*)&clen_addr, &len);

        readfp = fdopen(clientfd, "r");
        writefp = fdopen(dup(clitenfd),"w");

        fputs("Hi I am kobe\n",writefp);
        fputs("Hi I am james\n",writefp);
        fflush(writefp);

        shutdown(fileno(writefp), SHUT_WR);
        fclose(writefp);

        fgets(buf, sizeof(buf), readfp);
        fclose(readfp);
    }
    
    return 0;
}