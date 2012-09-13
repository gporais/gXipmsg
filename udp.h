// created by: geo (March 2012)
#ifndef UDP_H_
#define UDP_H_

#include "main.h"

// Constants
#define	UDP_DEFAULT_FAMILY		AF_INET
#define	UDP_DEFAULT_PORT		IPMSG_DEFAULT_PORT
#define	UDP_DEFAULT_IPADDR		INADDR_ANY
#define	UDP_BROADCAST_IPADDR	INADDR_BROADCAST

// Variable declerations
struct sockaddr_in UDP_AddrFrom;
struct sockaddr_in UDP_AddrTo;
struct Broadcast_Packet UDP_DataFrom;

int* UDP_LocalSocket;

#ifdef IP_ONESBCAST
struct sockaddr_in UDP_Info;
void udp_GetInfo(int* p_Socket);
#endif

// Function declerations
int udp_InitSocket(int* p_Socket);
int udp_BroadcastString(char* p_String);
int udp_SendToString(char* p_IPAddress, char* p_String, int m_Flags);
void udp_InquirePackets(void);
void udp_CloseSocket(void);

void udp_BroadcastEntry(void);
void udp_BroadcastExit(void);

int recvfromTimeOutUDP(int socket, long sec, long usec);

#endif /*UDP_H_*/
