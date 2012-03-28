// created by: geo (March 2012)
#ifndef SENDFORM_H_
#define SENDFORM_H_

#include "common.h"

// Constants


// Variable declerations
Widget SENDFORM_Form_Upper;
Widget SENDFORM_Frame_Member;
Widget SENDFORM_LblG_Count;
Widget SENDFORM_LblG_Member;
Widget SENDFORM_BtnG_Refresh;
Widget SENDFORM_List_Users;

Widget SENDFORM_Pane_Vertical;

Widget SENDFORM_Form_Lower;
Widget SENDFORM_BtnG_Attach;
Widget SENDFORM_Text_Message;
Widget SENDFORM_BtnG_Send;

int SENDFORM_Index;
Arg	SENDFORM_Args[20];

Atom SENDFORM_DelWin_protocol;

// Function declerations
void sendForm_Init(XtAppContext* xac_App, Widget* w_TopLevel, int argc, char* argv[]);
void sendForm_SetupClose(Widget* w_TopLevel, XtCallbackProc xcp_CloseProc);
void sendForm_SetupTimeout(XtAppContext* xac_App, XtTimerCallbackProc xcp_TOProc);
void sendForm_Run(XtAppContext* xac_App);

void sendForm_RefreshCallBack(Widget widget, XtPointer client_data, XtPointer call_data);
void sendForm_AddRemoveItem(struct Broadcast_Packet* p_Item, char m_Option);
void sendForm_UpdateCount(int m_Count);


#endif /*SENDFORM_H_*/
