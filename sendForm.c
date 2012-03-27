// created by: geo (March 2012)
#include "sendForm.h"

void sendForm_Init(XtAppContext* xac_App, Widget* w_TopLevel, int argc, char* argv[])
{
	char* str_item = "hello rose";
	XmString xstr_item;
	 
	 
	XtSetLanguageProc (NULL, NULL, NULL);
	*w_TopLevel = XtVaOpenApplication (xac_App, "gXipmsg", NULL, 0, &argc, argv, NULL,sessionShellWidgetClass, NULL);
	
	// Create paned window
	SENDFORM_Pane_Vertical = XmCreatePanedWindow (*w_TopLevel, "Vertical", NULL, 0);
	
	// Create upper form
	SENDFORM_Form_Upper = XmCreateForm (SENDFORM_Pane_Vertical, "Upper", NULL, 0);
	
	// Create frame
	SENDFORM_Index = 0;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNshadowType, XmSHADOW_ETCHED_OUT); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNtopAttachment, XmATTACH_FORM); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNrightAttachment, XmATTACH_FORM); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNtopOffset, 5); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNrightOffset, 5); SENDFORM_Index++;
	SENDFORM_Frame_Member = XmCreateFrame (SENDFORM_Form_Upper, "MemberFrame", SENDFORM_Args, SENDFORM_Index);
	
	// Create count label
	SENDFORM_LblG_Count = XmCreateLabelGadget (SENDFORM_Frame_Member, "0", NULL, 0);	
	XtManageChild (SENDFORM_LblG_Count);
	
	// Create member label
	SENDFORM_Index = 0;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNchildType, XmFRAME_TITLE_CHILD); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNchildVerticalAlignment, XmALIGNMENT_CENTER); SENDFORM_Index++;
	SENDFORM_LblG_Member = XmCreateLabelGadget (SENDFORM_Frame_Member, "Member", SENDFORM_Args, SENDFORM_Index);	
	XtManageChild (SENDFORM_LblG_Member);	
	
	XtManageChild (SENDFORM_Frame_Member);
	
	// Create list
	SENDFORM_Index = 0;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNvisibleItemCount, 5); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNtopAttachment, XmATTACH_FORM); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNleftAttachment, XmATTACH_FORM); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNbottomAttachment, XmATTACH_FORM); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNtopOffset, 5); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNleftOffset, 5); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNbottomOffset, 5); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNrightAttachment, XmATTACH_WIDGET); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNrightWidget, SENDFORM_Frame_Member); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNrightOffset, 5); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNselectionPolicy, XmEXTENDED_SELECT); SENDFORM_Index++;
	SENDFORM_List_Users = XmCreateScrolledList (SENDFORM_Form_Upper, "Users", SENDFORM_Args, SENDFORM_Index);
	XtManageChild (SENDFORM_List_Users);
	
	// Create refresh button
	SENDFORM_Index = 0;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNtopAttachment, XmATTACH_WIDGET); SENDFORM_Index++; 
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNtopWidget, SENDFORM_Frame_Member); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNleftAttachment, XmATTACH_OPPOSITE_WIDGET); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNleftWidget, SENDFORM_Frame_Member); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNrightAttachment, XmATTACH_OPPOSITE_WIDGET); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNrightWidget, SENDFORM_Frame_Member); SENDFORM_Index++;	
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNtopOffset, 5); SENDFORM_Index++;
	SENDFORM_BtnG_Refresh = XmCreatePushButtonGadget (SENDFORM_Form_Upper, "Refresh", SENDFORM_Args, SENDFORM_Index);
	XtManageChild (SENDFORM_BtnG_Refresh);	
	
	// Create lower form
	SENDFORM_Form_Lower = XmCreateForm (SENDFORM_Pane_Vertical, "Lower", NULL, 0);
	
	// Create attach button
	SENDFORM_Index = 0;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNleftAttachment, XmATTACH_FORM); SENDFORM_Index++;  
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNtopAttachment, XmATTACH_FORM); SENDFORM_Index++; 						
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNrightAttachment, XmATTACH_FORM); SENDFORM_Index++; 	
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNleftOffset, 5); SENDFORM_Index++; 
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNtopOffset, 5); SENDFORM_Index++; 
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNrightOffset, 5); SENDFORM_Index++; 
	SENDFORM_BtnG_Attach = XmCreatePushButtonGadget (SENDFORM_Form_Lower, "Attach", SENDFORM_Args, SENDFORM_Index);
	XtManageChild (SENDFORM_BtnG_Attach);
	
	// Create send button
	SENDFORM_Index = 0;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNbottomAttachment, XmATTACH_FORM); SENDFORM_Index++;													
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNbottomOffset, 5); SENDFORM_Index++;
	SENDFORM_BtnG_Send = XmCreatePushButtonGadget (SENDFORM_Form_Lower, "Send", SENDFORM_Args, SENDFORM_Index);
	XtManageChild (SENDFORM_BtnG_Send);
	
	// Creatr text message
	SENDFORM_Index = 0;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNleftAttachment, XmATTACH_FORM); SENDFORM_Index++; 												
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNrightAttachment, XmATTACH_FORM); SENDFORM_Index++;	
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNtopAttachment, XmATTACH_WIDGET); SENDFORM_Index++; 
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNtopWidget, SENDFORM_BtnG_Attach); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNbottomAttachment, XmATTACH_WIDGET); SENDFORM_Index++; 
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNbottomWidget, SENDFORM_BtnG_Send); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNleftOffset, 5); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNtopOffset, 5); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNrightOffset, 5); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNbottomOffset, 5); SENDFORM_Index++;
	SENDFORM_Text_Message = XmCreateText (SENDFORM_Form_Lower, "Message", SENDFORM_Args, SENDFORM_Index);
	XtManageChild (SENDFORM_Text_Message);
	
	
	// Materialize major widgets
	XtManageChild (SENDFORM_Form_Upper);
	XtManageChild (SENDFORM_Form_Lower);
	XtManageChild (SENDFORM_Pane_Vertical);
	XtRealizeWidget (*w_TopLevel);    
	
	xstr_item = XmStringCreateLocalized (str_item);
	XmListAddItemUnselected (SENDFORM_List_Users, xstr_item, 1);
	XmListAddItemUnselected (SENDFORM_List_Users, xstr_item, 2);
	XmListAddItemUnselected (SENDFORM_List_Users, xstr_item, 3);
	XmListAddItemUnselected (SENDFORM_List_Users, xstr_item, 4);
	XmListAddItemUnselected (SENDFORM_List_Users, xstr_item, 5);
	XtFree ((char *) xstr_item);
}

void sendForm_SetupClose(Widget* w_TopLevel, XtCallbackProc xcp_CloseProc)
{
	/* get window manager delete protocol atom */
	SENDFORM_DelWin_protocol = XmInternAtom(XtDisplay(*w_TopLevel), "WM_DELETE_WINDOW", True);
	
    /* turn off default delete response */
    XtVaSetValues( *w_TopLevel, XmNdeleteResponse, XmDO_NOTHING, NULL);
    
    /* add callback for window manager delete protocol */
    XmAddWMProtocolCallback(*w_TopLevel, SENDFORM_DelWin_protocol, xcp_CloseProc, NULL);
}

void sendForm_SetupTimeout(XtAppContext* xac_App, XtTimerCallbackProc xcp_TOProc)
{
	XtAppAddTimeOut(*xac_App, 500, xcp_TOProc, *xac_App);	
}

void sendForm_Run(XtAppContext* xac_App)
{
	XtAppMainLoop (*xac_App);
}

