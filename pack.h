// created by: geo (March 2012)
#ifndef PACK_H_
#define PACK_H_

#include "common.h"

// Constants
#define PACK_IPMSG_VERSION			"1"


// Variable declerations
char PACK_Full_Packet[PACKET_MAXLEN];
long PACK_Packet_No;
unsigned long PACK_Flags;

// Function declerations
char* pack_PackBroadcast(unsigned long m_Flags, char* p_username, char* p_hostname, char* p_handlename);
void pack_UnpackBroadcast(char* p_Packet, struct Broadcast_Packet* p_RestoredPacket);

#endif /*PACK_H_*/
