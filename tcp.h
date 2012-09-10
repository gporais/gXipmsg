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


// Function declerations
int tcp_InitClient(struct RecvClientData* data);
void tcp_CloseClient(struct RecvClientData* data);

#endif /*TCP_H_*/
