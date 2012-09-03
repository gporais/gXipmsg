// created by: geo (April 2012)
#ifndef RECVDIALOG_H_
#define RECVDIALOG_H_

#include "main.h"

// Constants


// Variable declerations


// Function declerations
void recvDialog_Create(XtPointer xt_List, struct Broadcast_Packet* p_Item);
void recvDialog_ReplyCallBack(Widget widget, XtPointer client_data, XtPointer call_data);
void recvDialog_CloseCallBack(Widget widget, XtPointer client_data, XtPointer call_data);
void recvDialog_Destroy(Widget dialog, XtPointer client_data, XtPointer call_data);
static void recvDialog_Map(Widget dialog, XtPointer client_data, XtPointer call_data);

#endif /*RECVDIALOG_H_*/
