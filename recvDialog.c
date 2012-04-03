// created by: geo (April 2012)
#include "recvDialog.h"


void recvDialog_PrintMsg(Widget* w_TopLevel, char* ptr_Msg)
{
	Widget dialog;
	XmString text;
	dialog = (Widget) XmCreateMessageDialog (*w_TopLevel, "dialog", NULL, 0);
	text = XmStringCreateLocalized (ptr_Msg);
	XtVaSetValues (dialog, XmNdialogType, XmDIALOG_MESSAGE, XmNmessageString, text, NULL);
	XmStringFree (text);
	XtManageChild (dialog);
}
