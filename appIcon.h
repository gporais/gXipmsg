// created by: geo (April 2012)
#ifndef APPICON_H_
#define APPICON_H_

#include "common.h"

// Constants


// Variable declerations
Widget APPICON_Btn_Icon, APPICON_Form;

Pixmap pixmap;
Pixel fg, bg;

int APPICON_Index;
Arg	APPICON_Args[20];

Atom APPICON_DelWin_protocol;

// Function declerations
void appIcon_Init(XtAppContext* xac_App, Widget* w_TopLevel, int argc, char* argv[]);
void appIcon_SetupClose(Widget* w_TopLevel, XtCallbackProc xcp_CloseProc);
void appIcon_SetupTimeout(XtAppContext* xac_App, XtTimerCallbackProc xcp_TOProc);
void appIcon_Run(XtAppContext* xac_App);

void appIcon_AddRemoveItem(struct Broadcast_Packet* p_Item, char m_Option);


#endif /*APPICON_H_*/
