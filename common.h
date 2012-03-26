// created by: geo (March 2012)
#ifndef COMMON_H_
#define COMMON_H_

#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>

#include <Xm/PushBG.h>
#include <Xm/LabelG.h>
#include <Xm/PushB.h>
#include <Xm/Frame.h>
#include <Xm/Form.h>
#include <Xm/List.h>
#include <Xm/PanedW.h>
#include <Xm/Text.h>
#include <Xm/Protocols.h>

#include <iconv.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <pwd.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/ioctl.h> 
#include <sys/mman.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>

#define	NAME_MAXLEN			50
#define	PACKET_MAXLEN		200

struct Broadcast_Packet {
	int m_Ver;
	int m_Time;
	int m_Flags;
	char p_username[NAME_MAXLEN];
	char p_hostname[NAME_MAXLEN];
	char p_handlename[NAME_MAXLEN];
};
	


#endif /*COMMON_H_*/
