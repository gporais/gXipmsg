// created by: geo (March 2012)
#ifndef SENDDIALOG_H_
#define SENDDIALOG_H_

#include "common.h"

// Constants


// Variable declerations
Widget SENDDIALOG_Dialog;
Widget SENDDIALOG_Form_Upper;
Widget SENDDIALOG_Frame_Member;
Widget SENDDIALOG_LblG_Count;
Widget SENDDIALOG_LblG_Member;
Widget SENDDIALOG_BtnG_Refresh;
Widget SENDDIALOG_List_Users;
Widget SENDDIALOG_Pane_Vertical;
Widget SENDDIALOG_Form_Lower;
Widget SENDDIALOG_BtnG_Attach;
Widget SENDDIALOG_Text_Message;
Widget SENDDIALOG_BtnG_Send;

// Function declerations
void sendDialog_Create(Widget* w_Parent, Widget* w_List);
void sendDialog_RefreshCallBack(Widget widget, XtPointer client_data, XtPointer call_data);
void sendDialog_SendCallBack(Widget widget, XtPointer client_data, XtPointer call_data);


void sendDialog_AddUser(XmString* xmstr_User, int m_Idx);
void sendDialog_UpdateCount(int m_Count);


#endif /*SENDDIALOG_H_*/
