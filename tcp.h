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

int tcp_Write(struct RecvClientData* ptrData, char* ptrBuff, int mSize);
int tcp_Read(struct RecvClientData* ptrData, char* ptrBuff, int mSize);

#endif /*TCP_H_*/
