// created by: geo (March 2012)
#ifndef COMMON_H_
#define COMMON_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>
#include <sys/time.h> /* setitimer() */
#include <sys/stat.h>

/* includes below are order dependent */
#include <sys/param.h> /* htons() */
#include <sys/ioctl.h>
#include <sys/types.h> /* socket() */
#include <sys/socket.h> /* socket() */
#include <netinet/in.h> /* inet_addr() INADDR_ANY */
#include <arpa/inet.h> /* inet_addr() */
#include <netdb.h> /* gethostbyname() */
#include <pwd.h>
#include <net/if.h>

#include <Xm/PushBG.h>
#include <Xm/LabelG.h>
#include <Xm/ToggleBG.h>
#include <Xm/MessageB.h>

#include <Xm/FileSB.h>
#include <Xm/SelectioB.h>

#include <Xm/Frame.h>
#include <Xm/Form.h>
#include <Xm/List.h>
#include <Xm/PanedW.h>
#include <Xm/Text.h>
#include <Xm/Protocols.h>

#include <Xm/MwmUtil.h>

#include "ipmsg.h"



#define _MSG_BUF_SIZE (65536)
#define _MSG_BUF_MIN_SIZE ((_MSG_BUF_SIZE)/2)

#define _TCP_BUF_SIZE (0x40000)
#define _TCP_BUF_MIN_SIZE (_TCP_BUF_SIZE/2)
#define TCP_FILE_BUFSIZ      (8192)


#define	USERNAME_MAXLEN			100
#define	HOSTNAME_MAXLEN			100
#define	HANDLENAME_MAXLEN		100


struct FileInfo_Packet {
	char* FileID;
	char* FileName;
	char* FileSize;
	char* FileTime;
	char* FileAttrib;
};

struct Broadcast_Packet {
	unsigned long IP_Flags;
	unsigned long PacketID;
	char* IP_Ver;
	char* UNIX_Time;
	char* Username;
	char* Hostname;	
	char* Handlename;
	char* Extended;
	char* ExtendedAddr;
	char IP_Address[20];
};

struct TCPSendData{
	XtWorkProcId dWorkID;	
	int dSocket;
	int dFileSize;
	int dProgSize;
	
	FILE* dfpRead;
	char* dBuffer;	
};

struct SendClientData{
	Widget dList;
	Widget dText;	
	Widget dLabel;	
	
	Widget dDialog;
	Widget dAttach;
	char* Extended;
	char PacketID[16];
		
	int dItemsCount;
	XmStringTable xItemsList;
	char** apItemList;
	int* dFileIDs;
	
	int dDestCount;
	char** apDestList;
	int* dItemsLeft;
	
	int dUserIdx;
	struct TCPSendData* dTCPData;
};

struct RecvClientData{
	int dPos;
	int dSocket;
	Widget dText;	
	Widget dCheck;	
	struct Broadcast_Packet dServerInfo;
	
	int dLevel;
	unsigned long dFileSize;
	unsigned long dCalcSize;
	unsigned long dProgress;
	XtWorkProcId dWorkID;
	Widget dButton;
	FILE* fpWrite;
	char* dBuffer;
	char* dFilename;
};

struct NODE {
	struct SendClientData* ptrData;
	struct NODE* next;
};

extern struct NODE* appLList;


extern Position posX, posY;
extern int n;
extern Arg args[20];
extern char bgcolor[10];
extern char fgcolor[10];

extern char GXIM_Local_Hostname[HOSTNAME_MAXLEN];
extern char GXIM_Local_Username[USERNAME_MAXLEN];
extern char GXIM_Local_Handlename[HANDLENAME_MAXLEN];

extern int GXIM_UDP_Socket;
extern struct passwd* GXIM_Passwd;
extern XtAppContext GXIM_App;
extern Widget GXIM_TopLevel;

extern int DLProcedures;

extern void gXipmsg_MapDialog(Widget dialog, XtPointer client_data, XtPointer call_data);
void gXipmsg_AtExit(Widget w_Widget, XtPointer xp_Client_data, XtPointer xp_Call_data);
void gXipmsg_CheckData(XtPointer xp_Client_data, XtIntervalId* id);


#endif /*COMMON_H_*/
