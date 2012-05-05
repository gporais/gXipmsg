// created by: geo (March 2012)
#include "sendDialog.h"

void sendDialog_Create(XtPointer xt_List)
{
	Widget* w_List = (Widget*)xt_List;
	
	Widget SENDDIALOG_Dialog;
	Widget SENDDIALOG_Form_Upper;
	Widget SENDDIALOG_Frame_Member;
	Widget SENDDIALOG_LblG_Count;
	Widget SENDDIALOG_LblG_Member;
	Widget SENDDIALOG_BtnG_Refresh;
	Widget SENDDIALOG_Pane_Vertical;
	Widget SENDDIALOG_Form_Lower;
	Widget SENDDIALOG_BtnG_Attach;
	Widget SENDDIALOG_BtnG_Send;
	
	Widget* SENDDIALOG_ClientData = malloc((sizeof(Widget)*2));
	
	
	int m_Count;	
	char str_Count[3];	
	XmString xstr_Count;	
	XmStringTable xstr_list;	
	
	// Get the current entries (and number of entries) from the List
	XtVaGetValues (*w_List, XmNitemCount, &m_Count,	XmNitems, &xstr_list, NULL);	
		
	// Create dialog
	SENDDIALOG_Dialog = XtVaCreatePopupShell("send_diag", 
			topLevelShellWidgetClass, XtParent (*w_List),
			XmNtitle, "Send Message",
			XmNdeleteResponse, XmUNMAP,
			NULL);	
		
	// Create paned window
	SENDDIALOG_Pane_Vertical = XmCreatePanedWindow (SENDDIALOG_Dialog, "Vertical", NULL, 0);
	
	// Create upper form
	SENDDIALOG_Form_Upper = XmCreateForm (SENDDIALOG_Pane_Vertical, "Upper", NULL, 0);
	
	// Create frame
	n = 0;
	XtSetArg (args[n], XmNshadowType, XmSHADOW_ETCHED_OUT); n++;
	XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNtopOffset, 5); n++;
	XtSetArg (args[n], XmNrightOffset, 5); n++;
	SENDDIALOG_Frame_Member = XmCreateFrame (SENDDIALOG_Form_Upper, "MemberFrame", args, n);
	
	// Create count label
	sprintf(str_Count, "%i", m_Count);
	xstr_Count = XmStringCreateLocalized (str_Count);
	
	n = 0;
	XtSetArg (args[n], XmNchildType, XmFRAME_WORKAREA_CHILD); n++;
	XtSetArg (args[n], XmNchildVerticalAlignment, XmALIGNMENT_CENTER); n++;
	XtSetArg (args[n], XmNlabelString, xstr_Count); n++;
	SENDDIALOG_LblG_Count = XmCreateLabelGadget (SENDDIALOG_Frame_Member, "Count", args, n);	
	XtManageChild (SENDDIALOG_LblG_Count);
	XmStringFree(xstr_Count);
	
	// Create member label
	n = 0;
	XtSetArg (args[n], XmNchildType, XmFRAME_TITLE_CHILD); n++;
	XtSetArg (args[n], XmNchildVerticalAlignment, XmALIGNMENT_CENTER); n++;
	SENDDIALOG_LblG_Member = XmCreateLabelGadget (SENDDIALOG_Frame_Member, "Member", args, n);	
	XtManageChild (SENDDIALOG_LblG_Member);	
	
	XtManageChild (SENDDIALOG_Frame_Member);
	
	// Create list
	n = 0;
	XtSetArg (args[n], XmNvisibleItemCount, 5); n++;
	XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNtopOffset, 5); n++;
	XtSetArg (args[n], XmNleftOffset, 5); n++;
	XtSetArg (args[n], XmNbottomOffset, 5); n++;
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_WIDGET); n++;
	XtSetArg (args[n], XmNrightWidget, SENDDIALOG_Frame_Member); n++;
	XtSetArg (args[n], XmNrightOffset, 5); n++;
	XtSetArg (args[n], XmNselectionPolicy, XmEXTENDED_SELECT); n++;
	XtSetArg (args[n], XmNitemCount, m_Count); n++;
	XtSetArg (args[n], XmNitems, xstr_list); n++;
	SENDDIALOG_ClientData[0] = XmCreateScrolledList (SENDDIALOG_Form_Upper, "Users", args, n);
	XtManageChild (SENDDIALOG_ClientData[0]);
	
	// Create refresh button
	n = 0;
	XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET); n++; 
	XtSetArg (args[n], XmNtopWidget, SENDDIALOG_Frame_Member); n++;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_OPPOSITE_WIDGET); n++;
	XtSetArg (args[n], XmNleftWidget, SENDDIALOG_Frame_Member); n++;
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_OPPOSITE_WIDGET); n++;
	XtSetArg (args[n], XmNrightWidget, SENDDIALOG_Frame_Member); n++;	
	XtSetArg (args[n], XmNtopOffset, 5); n++;
	SENDDIALOG_BtnG_Refresh = XmCreatePushButtonGadget (SENDDIALOG_Form_Upper, "Refresh", args, n);
	XtAddCallback (SENDDIALOG_BtnG_Refresh, XmNactivateCallback, sendDialog_RefreshCallBack, SENDDIALOG_Dialog);
	XtManageChild (SENDDIALOG_BtnG_Refresh);	
	
	// Create lower form
	SENDDIALOG_Form_Lower = XmCreateForm (SENDDIALOG_Pane_Vertical, "Lower", NULL, 0);
	
	// Create attach button
	n = 0;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++;  
	XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM); n++; 						
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++; 	
	XtSetArg (args[n], XmNleftOffset, 5); n++; 
	XtSetArg (args[n], XmNtopOffset, 5); n++; 
	XtSetArg (args[n], XmNrightOffset, 5); n++; 
	SENDDIALOG_BtnG_Attach = XmCreatePushButtonGadget (SENDDIALOG_Form_Lower, "Attach", args, n);
	XtManageChild (SENDDIALOG_BtnG_Attach);
	
	
	
	// Creatr text message
	n = 0;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++; 												
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++;	
	XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET); n++; 
	XtSetArg (args[n], XmNtopWidget, SENDDIALOG_BtnG_Attach); n++;
	XtSetArg (args[n], XmNleftOffset, 5); n++;
	XtSetArg (args[n], XmNtopOffset, 5); n++;
	XtSetArg (args[n], XmNrightOffset, 5); n++;
	
	XtSetArg (args[n], XmNrows, 10); n++;
	XtSetArg (args[n], XmNcolumns, 50); n++;
	XtSetArg (args[n], XmNscrollHorizontal, False); n++;
	XtSetArg (args[n], XmNwordWrap, True); n++;
	XtSetArg (args[n], XmNeditMode, XmMULTI_LINE_EDIT); n++;
	SENDDIALOG_ClientData[1] = XmCreateScrolledText(SENDDIALOG_Form_Lower, "Message", args, n);
	XtManageChild (SENDDIALOG_ClientData[1]);
	
	// Create send button
	n = 0;
	XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET); n++; 
	XtSetArg (args[n], XmNtopWidget, SENDDIALOG_ClientData[1]); n++;
	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNtopOffset, 5); n++;
	XtSetArg (args[n], XmNbottomOffset, 5); n++;
	SENDDIALOG_BtnG_Send = XmCreatePushButtonGadget (SENDDIALOG_Form_Lower, "Send", args, n);
		
	XtAddCallback (SENDDIALOG_BtnG_Send, XmNactivateCallback, sendDialog_SendCallBack, (XtPointer)SENDDIALOG_ClientData);
	XtManageChild (SENDDIALOG_BtnG_Send);
	
	
	// Materialize major widgets
	XtManageChild (SENDDIALOG_Form_Upper);
	XtManageChild (SENDDIALOG_Form_Lower);
	XtManageChild (SENDDIALOG_Pane_Vertical);	

	XtPopup (SENDDIALOG_Dialog, XtGrabNone);	
}



void sendDialog_UpdateCount(int m_Count)
{
//	char str_Dest[8];	
//	XmString xstr_Dest;
//	
//	sprintf(str_Dest, "%i", m_Count);
//			
//	xstr_Dest = XmStringCreateLocalized (str_Dest);		
//	XtVaSetValues (SENDDIALOG_LblG_Count, XmNlabelString, xstr_Dest, NULL);
//	
//	
//	strcpy(str_Dest, "Member");
//		
//	xstr_Dest = XmStringCreateLocalized (str_Dest);	
//	XtVaSetValues (SENDDIALOG_LblG_Member, XmNlabelString, xstr_Dest, NULL);		
//			
//	XmStringFree(xstr_Dest);
}

void sendDialog_RefreshCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	Widget* SENDDIALOG_Dialog = (Widget*)client_data;
	
	
	XtPopup (*SENDDIALOG_Dialog, XtGrabNone);
//	sendDialog_UpdateCount(0);
//	XmListDeleteAllItems(SENDDIALOG_List_Users);
	udp_BroadcastEntry();
}

void sendDialog_SendCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	Widget* SENDDIALOG_List_Users = (Widget*)client_data;
	Widget* SENDDIALOG_Text_Message = (Widget*)client_data+1;

	XmStringTable xstr_list;
	int mIdx = 0;
	int mCount = 0;	
	char* text;
	char* str_IP;
	
  	// Get the selected items (and number of selected) from the List
	XtVaGetValues (*SENDDIALOG_List_Users, XmNselectedItemCount, &mCount,	XmNselectedItems, &xstr_list, NULL);
		
	while(mCount>mIdx)
	{
		text = (char *) XmStringUnparse (xstr_list[mIdx], NULL,XmCHARSET_TEXT, XmCHARSET_TEXT,NULL, 0, XmOUTPUT_ALL);
		str_IP = strtok(text, "(");
		str_IP = strtok(NULL, ")");
		
		if (text = XmTextGetString (*SENDDIALOG_Text_Message)) {
			udp_SendToString(str_IP,text, IPMSG_SENDMSG);		
		}
		
		XtFree(text);
		mIdx++;
	}
	
	XmTextSetString (*SENDDIALOG_Text_Message, NULL); /* clear message area */
}


void sendDialog_AddUser(XmString* xmstr_User, int m_Idx)
{
//	XmListAddItemUnselected (SENDDIALOG_List_Users, *xmstr_User, m_Idx);
}

