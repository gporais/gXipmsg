// created by: geo (March 2012)
#include "pack.h"

char* pack_PackBroadcast(int m_Flags, char* p_username, char* p_hostname, char* p_handlename)
{
	// Prepare the flags
	PACK_Flags = m_Flags;	
	
	// Prepare the packet no
	PACK_Packet_No = time(NULL);	
	
	// Compose the full packet
	sprintf(PACK_Full_Packet, "%i:%i:%s:%s:%i:%s", PACK_IPMSG_VERSION, PACK_Packet_No, p_username, p_hostname, PACK_Flags, p_handlename);
	
	return PACK_Full_Packet;
}


void pack_UnpackBroadcast(char* p_Packet, struct Broadcast_Packet* p_RestoredPacket)
{
	sscanf(p_Packet, "%i:%i:%[^':']:%[^':']:%i:%[^':']", &p_RestoredPacket->IP_Ver, &p_RestoredPacket->UNIX_Time, p_RestoredPacket->Username, p_RestoredPacket->Hostname, &p_RestoredPacket->IP_Flags, p_RestoredPacket->Handlename);		
}

