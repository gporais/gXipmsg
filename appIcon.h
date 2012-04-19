// created by: geo (April 2012)
#ifndef APPICON_H_
#define APPICON_H_

#include "common.h"

// Constants


// Variable declerations
Widget APPICON_Form;
Widget APPICON_BtnG_Icon;
Widget APPICON_List_Users;

Pixmap pixmap;
Pixel fg, bg;

Atom APPICON_DelWin_protocol;

// Function declerations
void appIcon_Init(XtAppContext* xac_App, Widget* w_TopLevel, int argc, char* argv[]);
void appIcon_SetupClose(Widget* w_TopLevel, XtCallbackProc xcp_CloseProc);
void appIcon_SetupTimeout(XtAppContext* xac_App, XtTimerCallbackProc xcp_TOProc);
void appIcon_Run(XtAppContext* xac_App);
void appIcon_IconCallBack(Widget widget, XtPointer client_data, XtPointer call_data);
void appIcon_AddRemoveItem(struct Broadcast_Packet* p_Item, char m_Option);


#endif /*APPICON_H_*/
