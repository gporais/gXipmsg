// created by: geo (March 2012)
#include "udp.h"

int udp_InitSocket(int* p_Socket)
{
	int broadcast = 1;
	
	// Create socket
	if((*p_Socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		printf("error: socket()");
		return -1;
	}
	
	// Enable broadcast option 
	if((setsockopt(*p_Socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))) == -1)
	{
		printf("error: setsockopt()");
		return -1;
	}
	
	// Create socket address from
	UDP_AddrFrom.sin_family = UDP_DEFAULT_FAMILY;
	UDP_AddrFrom.sin_port = htons(UDP_DEFAULT_PORT);
	UDP_AddrFrom.sin_addr.s_addr = UDP_DEFAULT_IPADDR;
	
	// Bind socket 
	if((bind(*p_Socket, (struct sockaddr*)&UDP_AddrFrom, sizeof(UDP_AddrFrom))) == -1)
	{
		printf("error: bind()");
		return -1;
	}
	
	// Create socket address to
	UDP_AddrTo.sin_family = UDP_DEFAULT_FAMILY;
	UDP_AddrTo.sin_port = htons(UDP_DEFAULT_PORT);
	UDP_AddrTo.sin_addr.s_addr = inet_addr(UDP_BROADCAST_IPADDR);
	
	return 0;
}

int udp_BroadcastString(int* p_Socket, char* p_String)
{
	// Set IP of socket address to to broadcast
	UDP_AddrTo.sin_addr.s_addr = inet_addr(UDP_BROADCAST_IPADDR);
	
	// Send string to address to
	if((sendto(*p_Socket, p_String, strlen(p_String), 0, (struct sockaddr*)&UDP_AddrTo, sizeof(UDP_AddrTo))) == -1)
	{
		printf("error: sendto()");
		return -1;
	}
	
	return 0;
}

void udp_InquirePackets(int* p_Socket, char* p_Buffer)
{
	int m_AddrLen = sizeof(UDP_AddrFrom);
	
	while(recvfromTimeOutUDP(*p_Socket, 1, 0) > 0)
	{
		// Ok the data is ready, call recvfrom() to get it then
	    recvfrom(*p_Socket, p_Buffer, 1000, 0, (struct sockaddr*)&UDP_AddrFrom, &m_AddrLen);
	    printf("recieved from IP address %s: ", inet_ntoa(UDP_AddrFrom.sin_addr));
		printf("%s\n", p_Buffer);
	}	
}

void udp_CloseSocket(int* p_Socket)
{
	// Close socket
	close(*p_Socket);
}

// A sample of the select() return value
int recvfromTimeOutUDP(int socket, long sec, long usec)
{
    // Setup timeval variable
    struct timeval timeout;
    struct fd_set fds;
 
    timeout.tv_sec = sec;
    timeout.tv_usec = usec;
    // Setup fd_set structure
    FD_ZERO(&fds);
    FD_SET(socket, &fds);
    // Return value:
    // -1: error occurred
    // 0: timed out
    // > 0: data ready to be read
    return select(socket+1, &fds, 0, 0, &timeout);
}
