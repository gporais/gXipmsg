// created by: geo (March 2012)
#ifndef SENDDIALOG_H_
#define SENDDIALOG_H_

#include "main.h"


// Constants


// Variable declerations


// Function declerations
struct SendClientData* sendDialog_Create(XtPointer xt_List, int mSelPos, XtPointer xt_Text);
void sendDialog_SendCallBack(Widget widget, XtPointer client_data, XtPointer call_data);
void sendDialog_CloseCallBack(Widget widget, XtPointer client_data, XtPointer call_data);
void sendDialog_RefreshCallBack(Widget widget, XtPointer client_data, XtPointer call_data);
void sendDialog_Destroy(Widget dialog, XtPointer client_data, XtPointer call_data);

void sendDialog_AttachCallBack(Widget widget, XtPointer client_data, XtPointer call_data);
void sendDialog_AddFilesCallBack(Widget widget, XtPointer client_data, XtPointer call_data);
void sendDialog_DeleteItemCallBack(Widget widget, XtPointer client_data, XtPointer call_data);
void sendDialog_CloseAttachCallBack(Widget widget, XtPointer client_data, XtPointer call_data);

void sendDialog_AddFileCallBack(Widget dialog, XtPointer client_data, XtPointer call_data);
void sendDialog_CancelAddCallBack(Widget dialog, XtPointer client_data, XtPointer call_data);



#endif /*SENDDIALOG_H_*/
