// created by: geo (September 2012)
#include "tcp.h"


int tcp_InitSocket(int* p_Socket)
{
	int reuse = 1;	
	
	// Create socket
	if((*p_Socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("error: socket(SOCK_STREAM)");
		return -1;
	}
		
	// Create socket address from
	TCP_AddrServ.sin_family = TCP_DEFAULT_FAMILY;
	TCP_AddrServ.sin_port = htons(TCP_DEFAULT_PORT);
	TCP_AddrServ.sin_addr.s_addr = TCP_DEFAULT_IPADDR;
	
	// Bind socket 
	if((bind(*p_Socket, (struct sockaddr*)&TCP_AddrServ, sizeof(TCP_AddrServ))) == -1)
	{
		tcp_CloseSocket();
		printf("error: bind(tcp)");
		return -1;
	}
	
	// Set reuse address option 
	if ((*p_Socket != -1) && setsockopt(*p_Socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) != 0)
	{
		printf("setsockopt tcp(reuseaddr)");
		return -1;
	}

	if ((*p_Socket != -1) && listen(*p_Socket, 100) != 0)
		return	-1;
	
	TCP_LocalSocket = p_Socket;
				
	return 0;
}


void tcp_CloseSocket(void)
{
	// Close socket
	close(*TCP_LocalSocket);
	*TCP_LocalSocket = -1;
}

