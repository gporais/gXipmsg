// created by: geo (March 2012)
#include "pack.h"

char* pack_Broadcast(int m_Flags, char* p_username, char* p_hostname, char* p_handlename)
{
	// Prepare the flags
	PACK_Flags = m_Flags;	
	
	// Prepare the packet no
	PACK_Packet_No = time(NULL);	
	
	// Compose the full packet
	snprintf(PACK_Full_Packet, PACK_PACKET_MAXLEN,"%i:%i:%s:%s:%i:%s", PACK_IPMSG_VERSION, PACK_Packet_No, p_username, p_hostname, PACK_Flags, p_handlename);
	
	return PACK_Full_Packet;
}


