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

#include <Xm/Frame.h>
#include <Xm/Form.h>
#include <Xm/List.h>
#include <Xm/PanedW.h>
#include <Xm/Text.h>
#include <Xm/Protocols.h>

#include <Xm/MwmUtil.h>

#include "ipmsg.h"


#define	IPVER_MAXLEN			2
#define	UNIXTIME_MAXLEN			12
#define	IPFLAGS_MAXLEN			12
#define	IPADDRESS_MAXLEN		16
#define	USERNAME_MAXLEN			50
#define	HOSTNAME_MAXLEN			50
#define	HANDLENAME_MAXLEN		50
#define	MESSAGE_MAXLEN			500
#define	EXTENDED_MAXLEN			100

#define	PACKET_MAXLEN			IPVER_MAXLEN+UNIXTIME_MAXLEN+IPFLAGS_MAXLEN+IPADDRESS_MAXLEN+USERNAME_MAXLEN+HOSTNAME_MAXLEN+MESSAGE_MAXLEN+EXTENDED_MAXLEN

struct Broadcast_Packet {
	unsigned long UNIX_Time;
	unsigned long IP_Flags;
	char IP_Ver[IPVER_MAXLEN];
	char IP_Address[IPADDRESS_MAXLEN];
	char Username[USERNAME_MAXLEN];
	char Hostname[HOSTNAME_MAXLEN];
	char Handlename[MESSAGE_MAXLEN];
	char Extended[EXTENDED_MAXLEN];
};

struct SendClientData{
	Widget dList;
	Widget dText;	
	Widget dLabel;	
};

struct RecvClientData{
	int dPos;
	Widget dText;	
	Widget dCheck;	
};
	
extern Position posX, posY;
extern int n;
extern Arg args[20];
extern char bgcolor[10];
extern char fgcolor[10];

extern void gXipmsg_MapDialog(Widget dialog, XtPointer client_data, XtPointer call_data);


#endif /*COMMON_H_*/
