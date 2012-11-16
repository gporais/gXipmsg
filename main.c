// created by: geo (March 2012)
#include "main.h"


struct NODE* appLList;

Position posX, posY;
int n;
Arg args[20];
char bgcolor[10];
char fgcolor[10];

char GXIM_Local_Hostname[HOSTNAME_MAXLEN];
char GXIM_Local_Username[USERNAME_MAXLEN];
char GXIM_Local_Handlename[HANDLENAME_MAXLEN];

int GXIM_UDP_Socket;
struct passwd* GXIM_Passwd;
XtAppContext GXIM_App;
Widget GXIM_TopLevel;
int DLProcedures;

static int gXipmsg_main (int argc, char* argv[])
{	
	DLProcedures = 0;
	posX = 0;
	posY = 0;
	
	// Get local hostname
	if((gethostname(GXIM_Local_Hostname, HOSTNAME_MAXLEN)) == -1)
	{
		printf("error: gethostname()");
		exit(1);
	}
	
	// Get local username
	if((GXIM_Passwd = getpwuid (getuid())) == NULL)
	{
		printf("error: getpwuid(getuid())");
		exit(1);
	}
	else
	{
		// Set local username
		strcpy(GXIM_Local_Username, GXIM_Passwd->pw_name);		
	}
	
	//Get handlename
	if(argc > 1)
	{
		// Set local handlename 
		strcpy(GXIM_Local_Handlename, argv[1]);
	}
	else
	{
		// Set local handlename using username
		strcpy(GXIM_Local_Handlename, GXIM_Passwd->pw_name);
	}
	
	// Initialize a socket for UDP
	if((udp_InitSocket(&GXIM_UDP_Socket)) == -1)
	{
		exit(1);
	}
	
	// Initialize listener socket for TCP
	if((tcp_InitListener()) == -1)
	{
		exit(1);
	}
	
	appIcon_Init(&GXIM_TopLevel, argc, argv);
	appIcon_SetupClose(&GXIM_TopLevel, gXipmsg_AtExit, NULL);
	appIcon_SetupTimeout(gXipmsg_CheckData);
	appIcon_Run();
			

	return 0;
}

int main(int argc, char* argv[])
{
	return gXipmsg_main(argc,argv);    
}

void gXipmsg_AtExit(Widget w_Widget, XtPointer xp_Client_data, XtPointer xp_Call_data)
{	
	if(DLProcedures == 0)
	{
		udp_BroadcastExit();
		udp_CloseSocket();	
		tcp_CloseListener();
		exit(1);
	}
}

void gXipmsg_CheckData(XtPointer xp_Client_data, XtIntervalId* id)
{
	udp_InquirePackets();
	tcp_InquirePackets();
	
	appIcon_SetupTimeout(gXipmsg_CheckData);	
}

void gXipmsg_MapDialog(Widget dialog, XtPointer client_data, XtPointer call_data)
{
	Dimension w, h;
	
	XtVaGetValues(dialog, XmNwidth, &w, XmNheight, &h, NULL);
	if ((posX + w) >= WidthOfScreen (XtScreen (dialog)))
		posX = 0;
	if ((posY + h) >= HeightOfScreen (XtScreen (dialog)))
		posY = 0;
	XtVaSetValues (dialog, XmNx, posX, XmNy, posY, NULL);
	posX += 20;
	posY += 20;	
}

