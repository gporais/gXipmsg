// created by: geo (March 2012)
#ifndef GXIPMSG_H_
#define GXIPMSG_H_

#include "main.h"

// Constants


// Variable declerations
int GXIM_UDP_Socket;

struct passwd* GXIM_Passwd;

XtAppContext GXIM_App;
Widget GXIM_TopLevel;

// Function declerations
void gxipmg_AtExit(Widget w_Widget, XtPointer xp_Client_data, XtPointer xp_Call_data);
void gxipmg_CheckData(XtPointer xp_Client_data, XtIntervalId* id);

#endif /*GXIPMSG_H_*/
