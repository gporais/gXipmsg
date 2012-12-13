// created by: geo (September 2012)
#ifndef TCP_H_
#define TCP_H_

#include "main.h"

// Constants
#define	TCP_DEFAULT_FAMILY		AF_INET
#define	TCP_DEFAULT_PORT		IPMSG_DEFAULT_PORT
#define	TCP_DEFAULT_IPADDR		INADDR_ANY
#define	TCP_BROADCAST_IPADDR	INADDR_BROADCAST

#define TCP_LISTEN_LEN       	(5)

// Variable declerations
struct sockaddr_in TCP_AddrRemoteServ;
struct sockaddr_in TCP_AddrLocalServ;
struct Broadcast_Packet TCP_DataFrom;
int TCP_SockListener;




// Function declerations
int tcp_InitClient(struct RecvClientData* ptrData);
void tcp_CloseClient(struct RecvClientData* ptrData);
int tcp_WriteClient(struct RecvClientData* ptrData, char* ptrBuff, int mSize);
int tcp_ReadClient(struct RecvClientData* ptrData, char* ptrBuff, int mSize);

int tcp_InitListener(void);
void tcp_CloseListener(void);

void tcp_Close(int mSocket);
int tcp_Write(int mSocket, char* ptrBuff, int mSize);
int tcp_Read(int mSocket, char* ptrBuff, int mSize);

void tcp_InquirePackets(void);
Boolean tcp_SendProcedure(XtPointer client_data);

#endif /*TCP_H_*/
