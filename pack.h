// created by: geo (March 2012)
#ifndef PACK_H_
#define PACK_H_

#include "common.h"

// Constants
#define	PACK_PACKET_MAXLEN			500
#define PACK_IPMSG_VERSION			1


// Variable declerations
char PACK_Full_Packet[PACK_PACKET_MAXLEN];
int PACK_Packet_No;
unsigned long PACK_Flags;

// Function declerations
char* pack_Broadcast(int m_Flags, char* p_username, char* p_hostname, char* p_handlename);

#endif /*PACK_H_*/
