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
#include <sys/types.h> /* socket() */
#include <sys/socket.h> /* socket() */
#include <netinet/in.h> /* inet_addr() INADDR_ANY */
#include <arpa/inet.h> /* inet_addr() */
#include <netdb.h> /* gethostbyname() */
#include <pwd.h>

#include <Xm/PushBG.h>
#include <Xm/LabelG.h>

#include <Xm/MessageB.h>

#include <Xm/Frame.h>
#include <Xm/Form.h>
#include <Xm/List.h>
#include <Xm/PanedW.h>
#include <Xm/Text.h>
#include <Xm/Protocols.h>

#include <Xm/MwmUtil.h>


#define IPMSG_NOOPERATION		0x00000000UL
#define IPMSG_BR_ENTRY			0x00000001UL
#define IPMSG_BR_EXIT			0x00000002UL
#define IPMSG_ANSENTRY			0x00000003UL
#define IPMSG_BR_ABSENCE		0x00000004UL

#define IPMSG_BR_ISGETLIST		0x00000010UL
#define IPMSG_OKGETLIST			0x00000011UL
#define IPMSG_GETLIST			0x00000012UL
#define IPMSG_ANSLIST			0x00000013UL
#define IPMSG_BR_ISGETLIST2		0x00000018UL

#define IPMSG_SENDMSG			0x00000020UL
#define IPMSG_RECVMSG			0x00000021UL
#define IPMSG_READMSG			0x00000030UL
#define IPMSG_DELMSG			0x00000031UL
#define IPMSG_ANSREADMSG		0x00000032UL



#define	IPVER_MAXLEN			2
#define	UNIXTIME_MAXLEN			12
#define	IPFLAGS_MAXLEN			12
#define	IPADDRESS_MAXLEN		16
#define	USERNAME_MAXLEN			50
#define	HOSTNAME_MAXLEN			50
#define	HANDLENAME_MAXLEN		50
#define	MESSAGE_MAXLEN			500

#define	PACKET_MAXLEN			IPVER_MAXLEN+UNIXTIME_MAXLEN+IPFLAGS_MAXLEN+IPADDRESS_MAXLEN+USERNAME_MAXLEN+HOSTNAME_MAXLEN+MESSAGE_MAXLEN

struct Broadcast_Packet {
	unsigned long UNIX_Time;
	unsigned long IP_Flags;
	char IP_Ver[IPVER_MAXLEN];
	char IP_Address[IPADDRESS_MAXLEN];
	char Username[USERNAME_MAXLEN];
	char Hostname[HOSTNAME_MAXLEN];
	char Handlename[MESSAGE_MAXLEN];
};
	



#endif /*COMMON_H_*/
