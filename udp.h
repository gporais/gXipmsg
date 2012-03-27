// created by: geo (March 2012)
#ifndef UPD_H_
#define UPD_H_

#include "common.h"

// Constants
#define	UDP_DEFAULT_FAMILY		AF_INET
#define	UDP_DEFAULT_PORT		2425
#define	UDP_DEFAULT_IPADDR		INADDR_ANY
#define	UDP_BROADCAST_IPADDR	"255.255.255.255"

// Variable declerations
struct sockaddr_in UDP_AddrFrom;
struct sockaddr_in UDP_AddrTo;
struct Broadcast_Packet UDP_DataFrom;

int* UDP_LocalSocket;
char* UDP_LocalHostname;
char* UDP_LocalUsername;
char* UDP_LocalHandlename;


// Function declerations
int udp_InitSocket(int* p_Socket, char* p_Username, char* p_Hostname, char* p_Handlename);
int udp_BroadcastString(char* p_String);
void udp_InquirePackets(void);
void udp_CloseSocket(void);

void udp_BroadcastEntry(void);
void udp_BroadcastExit(void);

#endif /*UPD_H_*/
