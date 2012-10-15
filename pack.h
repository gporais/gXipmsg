// created by: geo (March 2012)
#ifndef PACK_H_
#define PACK_H_

#include "main.h"

// Constants
#define PACK_IPMSG_VERSION			"1"


// Variable declerations
char* PACK_Full_Packet;


// Function declerations
char* pack_PackBroadcast(unsigned long m_Flags, char* p_username, char* p_hostname, char* p_handlename, char* p_extended, unsigned long* p_packetID);
void pack_CleanPacketBuffer(void);

void pack_UnpackBroadcast(char* p_Packet, struct Broadcast_Packet* p_RestoredPacket);
void pack_UnpackExtended(struct RecvClientData* p_Data, struct FileInfo_Packet* p_FileInfo);
#endif /*PACK_H_*/
