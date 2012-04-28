// created by: geo (March 2012)
#ifndef SENDDIALOG_H_
#define SENDDIALOG_H_

#include "common.h"

// Constants


// Variable declerations


// Function declerations
void sendDialog_Create(Widget* w_Parent, Widget* w_List);
void sendDialog_RefreshCallBack(Widget widget, XtPointer client_data, XtPointer call_data);
void sendDialog_SendCallBack(Widget widget, XtPointer client_data, XtPointer call_data);


void sendDialog_AddUser(XmString* xmstr_User, int m_Idx);
void sendDialog_UpdateCount(int m_Count);


#endif /*SENDDIALOG_H_*/