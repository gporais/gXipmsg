// created by: geo (April 2012)
#include "recvDialog.h"


void recvDialog_Create(Widget* w_Parent, char* ptr_Msg)
{
	Widget SENDDIALOG_Dialog;
	Widget SENDDIALOG_Form;
	Widget SENDDIALOG_Text_Message;


		
	// Create dialog
	n = 0;
	XtSetArg (args[n], XmNtitle, "Recieve Message"); n++;
	XtSetArg (args[n], XmNdeleteResponse, XmDESTROY); n++;
	SENDDIALOG_Dialog = (Widget) XmCreateDialogShell (*w_Parent, "Dialog", args, n);
		
	// Create upper form
	SENDDIALOG_Form = XmCreateForm (SENDDIALOG_Dialog, "Form", NULL, 0);
	

	
	// Creatr text message
	n = 0;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++; 												
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++;	
//	XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET); n++; 
//	XtSetArg (args[n], XmNtopWidget, SENDDIALOG_BtnG_Attach); n++;
//	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_WIDGET); n++; 
//	XtSetArg (args[n], XmNbottomWidget, SENDDIALOG_BtnG_Send); n++;
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
	XtSetArg (args[n], XmNvalue, ptr_Msg); n++;
	SENDDIALOG_Text_Message = XmCreateScrolledText(SENDDIALOG_Form, "Message", args, n);
	
	
	XtManageChild (SENDDIALOG_Text_Message);
	
	
	
	XtManageChild (SENDDIALOG_Form);
	
	XtManageChild (SENDDIALOG_Dialog);
	
//	XmStringFree (text);
}
