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
struct Broadcast_Packet UDP_DataIn;

// Function declerations
int udp_InitSocket(int* p_Socket);
int udp_BroadcastString(int* p_Socket, char* p_String);
void udp_InquirePackets(int* p_Socket);
void udp_CloseSocket(int* p_Socket);

#endif /*UPD_H_*/
