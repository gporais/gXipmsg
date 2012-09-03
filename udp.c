// created by: geo (March 2012)
#include "udp.h"

int udp_InitSocket(int* p_Socket, char* p_Username, char* p_Hostname, char* p_Handlename)
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
		
	UDP_LocalSocket = p_Socket;
	UDP_LocalUsername = p_Username;
	UDP_LocalHostname = p_Hostname;	
	UDP_LocalHandlename = p_Handlename;
	
	udp_BroadcastEntry();
		
	return 0;
}

void udp_BroadcastEntry(void)
{
	udp_BroadcastString((char*)pack_PackBroadcast(IPMSG_NOOPERATION, UDP_LocalUsername, UDP_LocalHostname, UDP_LocalHandlename));
	udp_BroadcastString((char*)pack_PackBroadcast(IPMSG_BR_ENTRY, UDP_LocalUsername, UDP_LocalHostname, UDP_LocalHandlename));
}

void udp_BroadcastExit(void)
{
	udp_BroadcastString((char*)pack_PackBroadcast(IPMSG_NOOPERATION, UDP_LocalUsername, UDP_LocalHostname, UDP_LocalHandlename));
	udp_BroadcastString((char*)pack_PackBroadcast(IPMSG_BR_EXIT, UDP_LocalUsername, UDP_LocalHostname, UDP_LocalHandlename));
	udp_BroadcastString((char*)pack_PackBroadcast(IPMSG_NOOPERATION, UDP_LocalUsername, UDP_LocalHostname, UDP_LocalHandlename));
	udp_BroadcastString((char*)pack_PackBroadcast(IPMSG_BR_EXIT, UDP_LocalUsername, UDP_LocalHostname, UDP_LocalHandlename));
}

int udp_BroadcastString(char* p_String)
{
#ifdef IP_ONESBCAST
	
	int onesbcast = 1;   /* 0 = disable (default), 1 = enable */
	setsockopt(*UDP_LocalSocket, IPPROTO_IP, IP_ONESBCAST, &onesbcast, sizeof(onesbcast));
	UDP_AddrTo.sin_addr.s_addr = inet_addr("192.168.0.255");
	
#else
		
	// Set IP of socket address for broadcast
	UDP_AddrTo.sin_addr.s_addr = UDP_BROADCAST_IPADDR;
		
#endif	
	
	// Send string to address to
	if((sendto(*UDP_LocalSocket, p_String, strlen(p_String)+1, 0, (struct sockaddr*)&UDP_AddrTo, sizeof(UDP_AddrTo))) == -1)
	{
		printf("error: sendto()\n");		
		return -1;
	}
	
	return 0;
}

int udp_SendToString(char* p_IPAddress, char* p_String, int m_Flags)
{
	char* p_Buffer = (char*)pack_PackBroadcast(m_Flags, UDP_LocalUsername, UDP_LocalHostname, p_String);
	
#ifdef IP_ONESBCAST
	
	int onesbcast = 0;   /* 0 = disable (default), 1 = enable */
	setsockopt(*UDP_LocalSocket, IPPROTO_IP, IP_ONESBCAST, &onesbcast, sizeof(onesbcast));
	
#endif
	
		
	// Set IP of socket address for send
	if((UDP_AddrTo.sin_addr.s_addr = inet_addr(p_IPAddress)) == -1)
	{
		printf("error: inet_addr(%s)\n", p_IPAddress);		
		return -1;
	}
		
	// Send string to address to
	if((sendto(*UDP_LocalSocket, p_Buffer, strlen(p_Buffer)+1, 0, (struct sockaddr*)&UDP_AddrTo, sizeof(UDP_AddrTo))) == -1)
	{
		printf("error: sendto()\n");		
		return -1;
	}
	
	return 0;
}

void udp_InquirePackets(void)
{
	int m_AddrLen = sizeof(UDP_AddrFrom);
	char str_Reply[12];
	char UDP_Buffer[PACKET_MAXLEN];
	
	while(recvfromTimeOutUDP(*UDP_LocalSocket, 0, 0) > 0)
	{	
		//Clear buffer
		memset(UDP_Buffer,'\0',PACKET_MAXLEN);
		
		// Ok the data is ready, call recvfrom() to get it then
	    recvfrom(*UDP_LocalSocket, UDP_Buffer, PACKET_MAXLEN, 0, (struct sockaddr*)&UDP_AddrFrom, &m_AddrLen);
	    
	    pack_UnpackBroadcast(UDP_Buffer, &UDP_DataFrom);
	    strcpy(UDP_DataFrom.IP_Address, inet_ntoa(UDP_AddrFrom.sin_addr));

	    switch(UDP_DataFrom.IP_Flags & 0x000000FFUL)
		{
			case IPMSG_NOOPERATION:
				break;			
				
			case IPMSG_BR_ENTRY:
				udp_SendToString(UDP_DataFrom.IP_Address, UDP_LocalHandlename, IPMSG_ANSENTRY);
				appIcon_AddRemoveList(&UDP_DataFrom, 1);
				break;
				
			case IPMSG_ANSENTRY:
				appIcon_AddRemoveList(&UDP_DataFrom, 1);
				break;
				
			case IPMSG_BR_EXIT:				
				appIcon_AddRemoveList(&UDP_DataFrom, 0);
				break;
				
			case IPMSG_SENDMSG:
				// Pop message
				appIcon_RecieveDialog(&UDP_DataFrom);
								
				// Confirm send
				sprintf(str_Reply, "%lu", UDP_DataFrom.UNIX_Time);
				udp_SendToString(UDP_DataFrom.IP_Address, str_Reply, IPMSG_RECVMSG);
				break;
				
			case IPMSG_RECVMSG:
				printf("IPMSG_RECVMSG\n");
				break;
				
			default:
				printf("unknown: %s\n", UDP_Buffer);
		}
	}	
}

void udp_CloseSocket(void)
{
	// Close socket
	close(*UDP_LocalSocket);
}

// A sample of the select() return value
int recvfromTimeOutUDP(int socket, long sec, long usec)
{
    // Setup timeval variable
    struct timeval timeout;
    fd_set fds;
 
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
