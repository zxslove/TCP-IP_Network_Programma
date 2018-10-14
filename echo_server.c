//回声服务器实例
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;  //服务器和客户端的套接字描述符
	char message[BUF_SIZE];
	int str_len, i;
	
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	
	if(argc != 2)
	{
    printf("Usage : %s <port>\n", argv[0]);
    exit(1);
	}
	
	//创建服务端TCP套接字
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		 error_handling("sockt() error");
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));
		 
	//分配IP和端口号
	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		  error_handling("bind() error");
		
	// 设置为可连接请求状态 
	if(listen(serv_sock, 5) == -1)
			error_handling("listen() error");
		
	clnt_adr_sz = sizeof(clnt_adr);
	
	for(int i = 0; i < 5; ++i)
	{
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
		if(clnt_sock == -1)
			error_handling("accept() error");
		else
			printf("Connected client %d \n", i+1);
			
		while((str_len = read(clnt_sock, message, BUF_SIZE)!= 0))
				write(clnt_sock, message, str_len);
				
		close(clnt_sock);
	}
	 
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}