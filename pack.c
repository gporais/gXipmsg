// created by: geo (March 2012)
#include "pack.h"

char* pack_PackBroadcast(unsigned long m_Flags, char* p_username, char* p_hostname, char* p_handlename, char* p_extended)
{
	// Prepare the flags
	unsigned long PACK_Flags = m_Flags;	
	
	// Prepare the packet no
	unsigned long PACK_Packet_No = time(NULL);	
	
	int len = (strlen(PACK_IPMSG_VERSION) + 1) + 11 + (strlen(p_username) + 1) + (strlen(p_hostname) + 1) + 11 + (strlen(p_handlename) + 1);
	char* pIdx;
	
	if(p_extended != NULL)
	{
		len += (strlen(p_extended) + 1);
	}
	
	// Prepare PACK_Full_Packet
	PACK_Full_Packet = malloc(len);
	
	sprintf(PACK_Full_Packet, "%s:%lu:%s:%s:%lu:%s", PACK_IPMSG_VERSION, PACK_Packet_No, p_username, p_hostname, PACK_Flags, p_handlename);
	
	len = strlen(PACK_Full_Packet);
	
	if(p_extended != NULL)
	{
		// Add exteneded
		strcat(PACK_Full_Packet, p_extended);
		
		pIdx = &PACK_Full_Packet[len];
		len = 0;
		
		while((pIdx = strchr(pIdx, '+')) != NULL)
		{
			if(len == 0)
				*pIdx = 0;
			else
				*pIdx = 7;
			
			pIdx++;
			len++;
		}
	}	

	return PACK_Full_Packet;
}


void pack_CleanPacketBuffer(void)
{
	if(PACK_Full_Packet != NULL)
	{
		free(PACK_Full_Packet);
		PACK_Full_Packet = NULL;		
	}
}


void pack_UnpackBroadcast(char* p_Packet, struct Broadcast_Packet* p_RestoredPacket)
{
	char* search = ":";
	char* temp;
	
	// Token will point to Get IP_Ver
	p_RestoredPacket->IP_Ver = strtok(p_Packet, search);
			
	// Token will point to Get UNIX_Time
	p_RestoredPacket->UNIX_Time = strtok(NULL, search);
	sscanf(p_RestoredPacket->UNIX_Time, "%lu", &p_RestoredPacket->PacketID);
		
	// Token will point to Get Username
	p_RestoredPacket->Username = strtok(NULL, search);
		
	// Token will point to Get Hostname
	p_RestoredPacket->Hostname = strtok(NULL, search);
	
	// Token will point to Get IP_Flags
	sscanf((temp = strtok(NULL, search)), "%lu", &p_RestoredPacket->IP_Flags);
	
	// Token will point to Get Handlename
	p_RestoredPacket->Handlename = strtok(NULL, search);
	
	// Get Extended
	if(p_RestoredPacket->Handlename != NULL)
	{
		p_RestoredPacket->ExtendedAddr = p_RestoredPacket->Handlename + strlen(p_RestoredPacket->Handlename) + 1;
	}
	else
	{
		p_RestoredPacket->ExtendedAddr = temp + strlen(temp) + 2;
	}
	
	if(p_RestoredPacket->ExtendedAddr != NULL)
	{
		p_RestoredPacket->Extended = malloc(strlen(p_RestoredPacket->ExtendedAddr) + 1);
		strcpy(p_RestoredPacket->Extended, p_RestoredPacket->ExtendedAddr);
		p_RestoredPacket->ExtendedAddr = p_RestoredPacket->Extended;
	}
}


void pack_UnpackExtended(struct RecvClientData* p_Data, struct FileInfo_Packet* p_FileInfo)
{
	char* search = ":";
	
	// Token will point to Get FileID
	p_FileInfo->FileID = strtok(p_Data->dServerInfo.Extended, search);
			
	// Token will point to Get FileName
	p_FileInfo->FileName = strtok(NULL, search);
	p_Data->dFilename = p_FileInfo->FileName;
		
	// Token will point to Get FileSize
	p_FileInfo->FileSize = strtok(NULL, search);
		
	// Token will point to Get FileTime
	p_FileInfo->FileTime = strtok(NULL, search);
	
	// Token will point to Get FileAttrib
	p_FileInfo->FileAttrib = strtok(NULL, search);
	
	
	// Update original string
	p_Data->dServerInfo.Extended = p_FileInfo->FileAttrib + strlen(p_FileInfo->FileAttrib) + 2;
}

