// created by: geo (September 2012)
#ifndef TCP_H_
#define TCP_H_

#include "main.h"

// Constants
#define	TCP_DEFAULT_FAMILY		AF_INET
#define	TCP_DEFAULT_PORT		IPMSG_DEFAULT_PORT
#define	TCP_DEFAULT_IPADDR		INADDR_ANY
#define	TCP_BROADCAST_IPADDR	INADDR_BROADCAST

// Variable declerations
struct sockaddr_in TCP_AddrServ;

int* TCP_LocalSocket;


// Function declerations
int tcp_InitSocket(int* p_Socket);
void tcp_CloseSocket(void);

#endif /*TCP_H_*/
