// created by: geo (April 2012)
#include "recvDialog.h"


void recvDialog_Create(Widget* w_Parent, struct Broadcast_Packet* p_Item)
{
	Widget RECVDIALOG_Dialog;
	Widget RECVDIALOG_Panel;
	Widget RECVDIALOG_Form;
	Widget RECVDIALOG_Frame;
	Widget RECVDIALOG_LblG_FrameTitle;
	Widget RECVDIALOG_LblG_FrameChild;	
	Widget RECVDIALOG_Text_Message;
	Widget RECVDIALOG_BtnG_Reply;

	char str_Buff[150];	
	XmString xstr_Buff;

	sprintf(str_Buff, "%s@%s (%s)\n%s", p_Item->Username, p_Item->Hostname, p_Item->IP_Address, asctime(localtime ((const time_t *)&p_Item->UNIX_Time)));
		
	// Create dialog
	n = 0;
	XtSetArg (args[n], XmNtitle, "Recieve Message"); n++;
	XtSetArg (args[n], XmNdeleteResponse, XmDESTROY); n++;
	XtSetArg (args[n], XmNdefaultPosition, False); n++;
	XtSetArg (args[n], XmNx, posX); n++;
	XtSetArg (args[n], XmNy, posY); n++;
	RECVDIALOG_Dialog = (Widget) XmCreateDialogShell (*w_Parent, "recv_diag", args, n);
	
	posX += 20;
	posY += 20;
		
	// Create paned window
	RECVDIALOG_Panel = XmCreatePanedWindow (RECVDIALOG_Dialog, "recv_panel", NULL, 0);
		
	// Create form
	RECVDIALOG_Form = XmCreateForm (RECVDIALOG_Panel, "recv_form", NULL, 0);
	
	
	// Create frame
	n = 0;
	XtSetArg (args[n], XmNshadowType, XmSHADOW_ETCHED_OUT); n++;
	XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNtopOffset, 5); n++;
	XtSetArg (args[n], XmNleftOffset, 5); n++;
	XtSetArg (args[n], XmNrightOffset, 5); n++;
	RECVDIALOG_Frame = XmCreateFrame (RECVDIALOG_Form, "recv_frame", args, n);
	
	
	// Create handle field
	xstr_Buff = XmStringCreateLocalized (str_Buff);
		
	n = 0;
	XtSetArg (args[n], XmNchildType, XmFRAME_WORKAREA_CHILD); n++;
	XtSetArg (args[n], XmNlabelString, xstr_Buff); n++;
	RECVDIALOG_LblG_FrameChild = XmCreateLabelGadget (RECVDIALOG_Frame, "recv_frame_child", args, n);
	XtManageChild (RECVDIALOG_LblG_FrameChild);		
	
	
	// Create frame title
	n = 0;
	XtSetArg (args[n], XmNchildType, XmFRAME_TITLE_CHILD); n++;
	XtSetArg (args[n], XmNchildVerticalAlignment, XmALIGNMENT_CENTER); n++;
	RECVDIALOG_LblG_FrameTitle = XmCreateLabelGadget (RECVDIALOG_Frame, "Message from", args, n);	
	XtManageChild (RECVDIALOG_LblG_FrameTitle);	
	
	XtManageChild (RECVDIALOG_Frame);
	
	// Create reply button
	n = 0;
	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNbottomOffset, 5); n++;
	RECVDIALOG_BtnG_Reply = XmCreatePushButtonGadget (RECVDIALOG_Form, "Reply", args, n);		
//	XtAddCallback (SENDDIALOG_BtnG_Send, XmNactivateCallback, sendDialog_SendCallBack, (XtPointer)SENDDIALOG_ClientData);
	XtManageChild (RECVDIALOG_BtnG_Reply);

	
	// Creatr text message
	n = 0;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++; 												
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++;	
	XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET); n++; 
	XtSetArg (args[n], XmNtopWidget, RECVDIALOG_Frame); n++;
	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_WIDGET); n++;	
	XtSetArg (args[n], XmNbottomWidget, RECVDIALOG_BtnG_Reply); n++;
	XtSetArg (args[n], XmNleftOffset, 5); n++;
	XtSetArg (args[n], XmNtopOffset, 5); n++;
	XtSetArg (args[n], XmNrightOffset, 5); n++;
	XtSetArg (args[n], XmNbottomOffset, 5); n++;
	
	XtSetArg (args[n], XmNrows, 10); n++;
	XtSetArg (args[n], XmNcolumns, 50); n++;
	XtSetArg (args[n], XmNscrollHorizontal, False); n++;
	XtSetArg (args[n], XmNwordWrap, True); n++;
	XtSetArg (args[n], XmNeditMode, XmMULTI_LINE_EDIT); n++;
	XtSetArg (args[n], XmNeditable, False); n++;
	XtSetArg (args[n], XmNcursorPositionVisible, False); n++;
	XtSetArg (args[n], XmNvalue, p_Item->Handlename); n++;
	RECVDIALOG_Text_Message = XmCreateScrolledText(RECVDIALOG_Form, "Message", args, n);	
	XtManageChild (RECVDIALOG_Text_Message);	
		
	XtManageChild (RECVDIALOG_Form);
	XtManageChild (RECVDIALOG_Panel);
	XtManageChild (RECVDIALOG_Dialog);
}
