// created by: geo (September 2012)
#include "tcp.h"


int tcp_InitClient(struct RecvClientData* data)
{
	int reuse = 1;
	int buff_size;
	int buff_minsize;
	
	// Create socket
	if((data->dSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("error: socket(SOCK_STREAM)");
		return -1;
	}
		
	// Create socket address from
	TCP_AddrServ.sin_family = TCP_DEFAULT_FAMILY;
	TCP_AddrServ.sin_port = htons(TCP_DEFAULT_PORT);
			
	// Set IP of socket address of server
	if((TCP_AddrServ.sin_addr.s_addr = inet_addr(data->dServerInfo.IP_Address)) == -1)
	{
		printf("error: inet_addr(%s)\n", data->dServerInfo.IP_Address);		
		return -1;
	}
	
	// Connect socket 
	if((connect(data->dSocket, (struct sockaddr*)&TCP_AddrServ, sizeof(TCP_AddrServ))) == -1)
	{
		tcp_CloseClient(data);
		printf("error: connect(tcp)");
		return -1;
	}
	
	// Set reuse address option 
	if ((data->dSocket != -1) && setsockopt(data->dSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) != 0)
	{
		printf("error: setsockopt(tcp, reuseaddr)");
		return -1;
	}
	
	// Set TCP send buffer size
	buff_size = _TCP_BUF_SIZE;
	buff_minsize = _TCP_BUF_MIN_SIZE;
	if((setsockopt(data->dSocket, SOL_SOCKET, SO_SNDBUF, (void*)&buff_size, sizeof(int))) != 0 && (setsockopt(data->dSocket, SOL_SOCKET, SO_SNDBUF, (void*)&buff_minsize, sizeof(int))) != 0)
	{
		printf("error: setsockopt(udp, SOL_SOCKET, SENDSIZE)");
		return -1;
	}
		 
	// Set TCP recv buffer size
	buff_size = _TCP_BUF_SIZE;
	buff_minsize = _TCP_BUF_MIN_SIZE;
	if((setsockopt(data->dSocket, SOL_SOCKET, SO_RCVBUF, (void*)&buff_size, sizeof(int))) != 0 && (setsockopt(data->dSocket, SOL_SOCKET, SO_RCVBUF, (void*)&buff_minsize, sizeof(int))) != 0)
	{
		printf("error: setsockopt(udp, SOL_SOCKET, RECVSIZE)");
		return -1;
	}
					
	return 0;
}


void tcp_CloseClient(struct RecvClientData* data)
{
	// Close socket
	if(data->dSocket != -1)
	{
		close(data->dSocket);
		data->dSocket = -1;
	}
}


int tcp_Write(struct RecvClientData* ptrData, char* ptrBuff, int mSize)
{
	return write(ptrData->dSocket, ptrBuff, mSize);
}


int tcp_Read(struct RecvClientData* ptrData, char* ptrBuff, int mSize)
{
	return read(ptrData->dSocket, ptrBuff, mSize);
}


