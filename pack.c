// created by: geo (March 2012)
#include "pack.h"

char* pack_PackBroadcast(unsigned long m_Flags, char* p_username, char* p_hostname, char* p_handlename)
{
	// Prepare the flags
	unsigned long PACK_Flags = m_Flags;	
	
	// Prepare the packet no
	unsigned long PACK_Packet_No = time(NULL);	
	
	int len = (strlen(PACK_IPMSG_VERSION) + 1) + 11 + (strlen(p_username) + 1) + (strlen(p_hostname) + 1) + 11 +(strlen(p_handlename) + 1);
	
	// Prepare PACK_Full_Packet
	PACK_Full_Packet = malloc(len);
	
	// Compose the full packet
	sprintf(PACK_Full_Packet, "%s:%lu:%s:%s:%lu:%s", PACK_IPMSG_VERSION, PACK_Packet_No, p_username, p_hostname, PACK_Flags, p_handlename);

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
//	int n = 0;
//	sscanf(p_Packet, "%[^':']:%[^':']:%[^':']:%[^':']:%d:%n", p_RestoredPacket->IP_Ver, p_RestoredPacket->UNIX_Time, p_RestoredPacket->Username, p_RestoredPacket->Hostname, &p_RestoredPacket->IP_Flags, &n);
//	strcpy(p_RestoredPacket->Handlename, (p_Packet+n));	
//	n += strlen(p_RestoredPacket->Handlename)+1;
//		
//	
//	p_RestoredPacket->Extended = malloc(strlen(p_Packet + n) + 1);
//	p_RestoredPacket->ExtendedAddr = p_RestoredPacket->Extended;
//	strcpy(p_RestoredPacket->Extended, (p_Packet + n));	
	

	char* search = ":";
//	char* temp;
	
	// Token will point to Get IP_Ver
	p_RestoredPacket->IP_Ver = strtok(p_Packet, search);
			
	// Token will point to Get UNIX_Time
	p_RestoredPacket->UNIX_Time = strtok(NULL, search);
		
	// Token will point to Get Username
	p_RestoredPacket->Username = strtok(NULL, search);
		
	// Token will point to Get Hostname
	p_RestoredPacket->Hostname = strtok(NULL, search);
	
	// Token will point to Get IP_Flags
	sscanf(strtok(NULL, search), "%lu", &p_RestoredPacket->IP_Flags);
	
	// Token will point to Get FileTime
	p_RestoredPacket->Handlename = strtok(NULL, search);
	
	
	p_RestoredPacket->Extended = strtok(NULL, search);
//	strcpy(p_RestoredPacket->Extended,strtok(NULL, search));
	printf("start%send\n",p_RestoredPacket->Extended);
//	if()
		
//	temp = p_RestoredPacket->Handlename + strlen(p_RestoredPacket->Handlename) + 1;
//	printf("len %i s: %send\n ",strlen(temp),temp);
	// Token will point to Get FileAttrib
//	p_RestoredPacket->Extended = p_RestoredPacket->Handlename + strlen(p_RestoredPacket->Handlename) + 1;
//	strcpy(p_RestoredPacket->Extended, p_RestoredPacket->Handlename + strlen(p_RestoredPacket->Handlename) + 1);
//	printf("len %i  s:%send\n ",strlen(p_RestoredPacket->Handlename),p_RestoredPacket->Handlename);
//	strcpy(p_RestoredPacket->Extended, p_RestoredPacket->Handlename + strlen(p_RestoredPacket->Handlename) + 1);
//	printf("len %i  s:%send\n ",strlen(p_RestoredPacket->Extended),p_RestoredPacket->Extended);
	
//	if(temp != NULL)
//	{
//		printf("p: %i end: %i\n",p_RestoredPacket->IP_Ver, temp);
//		p_RestoredPacket->Extended = malloc(100);
//		p_RestoredPacket->ExtendedAddr = p_RestoredPacket->Extended;
//		strcpy(p_RestoredPacket->Extended, temp);
//	}

//	strcpy(p_RestoredPacket->Extended, temp);	
//	p_RestoredPacket->ExtendedAddr = malloc(strlen(p_RestoredPacket->Extended) + 1);
//	p_RestoredPacket->Extended = p_RestoredPacket->ExtendedAddr;
}


void pack_UnpackExtended(struct RecvClientData* p_Data, struct FileInfo_Packet* p_FileInfo)
{
	char* search = ":";

	// Token will point to Get FileID
	p_FileInfo->FileID = strtok(p_Data->dServerInfo.Extended, search);
			
	// Token will point to Get FileName
	p_FileInfo->FileName = strtok(NULL, search);
		
	// Token will point to Get FileSize
	p_FileInfo->FileSize = strtok(NULL, search);
		
	// Token will point to Get FileTime
	p_FileInfo->FileTime = strtok(NULL, search);
	
	// Token will point to Get FileAttrib
	p_FileInfo->FileAttrib = strtok(NULL, search);
	
	
	// Update original string
//	p_Data->dServerInfo.Extended = p_FileInfo->FileAttrib + strlen(p_FileInfo->FileAttrib) + 2;
}

