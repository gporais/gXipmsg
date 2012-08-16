// created by: geo (March 2012)
#ifndef SENDDIALOG_H_
#define SENDDIALOG_H_

#include "main.h"


// Constants


// Variable declerations
typedef struct {
	XtIntervalId id;
	Widget globalList;
	Widget localList;
	XtAppContext app;
} TimeOutClientData;

// Function declerations
void sendDialog_Create(XtPointer xt_List, int mSelPos);
void sendDialog_SendCallBack(Widget widget, XtPointer client_data, XtPointer call_data);


void sendDialog_RefreshCallBack(Widget widget, XtPointer client_data, XtPointer call_data);


void sendDialog_AddUser(XmString* xmstr_User, int m_Idx);
void sendDialog_UpdateCount(int m_Count);

void destroy_it (Widget dialog, XtPointer client_data, XtPointer call_data);
void update (XtPointer client_data, XtIntervalId *id);


#endif /*SENDDIALOG_H_*/
