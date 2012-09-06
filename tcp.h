// created by: geo (September 2012)
#ifndef TCP_H_
#define TCP_H_

#include "main.h"

// Constants
#define	TCP_DEFAULT_FAMILY		AF_INET
#define	TCP_DEFAULT_PORT		2425
#define	TCP_DEFAULT_IPADDR		INADDR_ANY
#define	TCP_BROADCAST_IPADDR	INADDR_BROADCAST

// Variable declerations
struct sockaddr_in TCP_AddrFrom;
struct sockaddr_in TCP_AddrTo;
struct Broadcast_Packet TCP_DataFrom;

int* TCP_LocalSocket;
char* TCP_LocalHostname;
char* TCP_LocalUsername;
char* TCP_LocalHandlename;


// Function declerations
int tcp_InitSocket(int* p_Socket, char* p_Username, char* p_Hostname, char* p_Handlename);
void tcp_CloseSocket(void);

#endif /*TCP_H_*/
