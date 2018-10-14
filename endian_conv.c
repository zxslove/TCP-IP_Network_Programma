#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	unsigned short host_port = Ox1234;
	unsigned short net_port;
	unsigned long  host_addr = Ox12345678;
	unsigned long	 net_addr;
	
	//转化为网络字节序
	net_port = htons(host_port);
	net_addr = htonl(host_addr);
	
	printf("Host ordered port: %#x \n", host_port);
	printf("NetWork ordered port: %#x \n", net_port);
	printf("Host ordered address: %#x \n", host_addr);
	printf("NetWork ordered address: %#x \n", net_addr);
	
	return 0;
}