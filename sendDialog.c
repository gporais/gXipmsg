// created by: geo (March 2012)
#include "sendDialog.h"

void sendDialog_Create(Widget* w_Parent)
{
	// Create dialog
	n = 0;
	XtSetArg (args[n], XmNtitle, "Send Message"); n++;
	XtSetArg (args[n], XmNdeleteResponse, XmDESTROY); n++;
	SENDDIALOG_Dialog = (Widget) XmCreateDialogShell (XtParent (*w_Parent), "Dialog", args, n);
		
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
	n = 0;
	XtSetArg (args[n], XmNchildType, XmFRAME_WORKAREA_CHILD); n++;
	XtSetArg (args[n], XmNchildVerticalAlignment, XmALIGNMENT_CENTER); n++;
	SENDDIALOG_LblG_Count = XmCreateLabelGadget (SENDDIALOG_Frame_Member, "0", args, n);	
	XtManageChild (SENDDIALOG_LblG_Count);	
	
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
	SENDDIALOG_List_Users = XmCreateScrolledList (SENDDIALOG_Form_Upper, "Users", args, n);
	XtManageChild (SENDDIALOG_List_Users);
	
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
	XtAddCallback (SENDDIALOG_BtnG_Refresh, XmNactivateCallback, sendDialog_RefreshCallBack, NULL);
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
	
	// Create send button
	n = 0;
	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM); n++;													
	XtSetArg (args[n], XmNbottomOffset, 5); n++;
	SENDDIALOG_BtnG_Send = XmCreatePushButtonGadget (SENDDIALOG_Form_Lower, "Send", args, n);
	XtAddCallback (SENDDIALOG_BtnG_Send, XmNactivateCallback, sendDialog_SendCallBack, NULL);
	XtManageChild (SENDDIALOG_BtnG_Send);
	
	// Creatr text message
	n = 0;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++; 												
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++;	
	XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET); n++; 
	XtSetArg (args[n], XmNtopWidget, SENDDIALOG_BtnG_Attach); n++;
	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_WIDGET); n++; 
	XtSetArg (args[n], XmNbottomWidget, SENDDIALOG_BtnG_Send); n++;
	XtSetArg (args[n], XmNleftOffset, 5); n++;
	XtSetArg (args[n], XmNtopOffset, 5); n++;
	XtSetArg (args[n], XmNrightOffset, 5); n++;
	XtSetArg (args[n], XmNbottomOffset, 5); n++;
	
	XtSetArg (args[n], XmNrows, 10); n++;
	XtSetArg (args[n], XmNcolumns, 50); n++;
	XtSetArg (args[n], XmNscrollHorizontal, False); n++;
	XtSetArg (args[n], XmNwordWrap, True); n++;
	XtSetArg (args[n], XmNeditMode, XmMULTI_LINE_EDIT); n++;
	SENDDIALOG_Text_Message = XmCreateScrolledText(SENDDIALOG_Form_Lower, "Message", args, n);
	XtManageChild (SENDDIALOG_Text_Message);
	
	
	// Materialize major widgets
	XtManageChild (SENDDIALOG_Form_Upper);
	XtManageChild (SENDDIALOG_Form_Lower);
	XtManageChild (SENDDIALOG_Pane_Vertical);
	
	XtManageChild (SENDDIALOG_Dialog);
}



void sendDialog_UpdateCount(int m_Count)
{
	char str_Dest[8];	
	XmString xstr_Dest;
	
	sprintf(str_Dest, "%i", m_Count);
			
	xstr_Dest = XmStringCreateLocalized (str_Dest);		
	XtVaSetValues (SENDDIALOG_LblG_Count, XmNlabelString, xstr_Dest, NULL);
	
	
	strcpy(str_Dest, "Member");
		
	xstr_Dest = XmStringCreateLocalized (str_Dest);	
	XtVaSetValues (SENDDIALOG_LblG_Member, XmNlabelString, xstr_Dest, NULL);		
			
	XmStringFree(xstr_Dest);
}

void sendDialog_RefreshCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	sendDialog_UpdateCount(0);
	XmListDeleteAllItems(SENDDIALOG_List_Users);
	udp_BroadcastEntry();
}

void sendDialog_SendCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	XmStringTable xstr_list;
	int mIdx = 0;
	int mCount;	
	char* text;
	char* str_IP;
	
  	// Get the selected items (and number of selected) from the List
	XtVaGetValues (SENDDIALOG_List_Users, XmNselectedItemCount, &mCount,	XmNselectedItems, &xstr_list, NULL);
	
	while(mCount>mIdx)
	{
		text = (char *) XmStringUnparse (xstr_list[mIdx], NULL,XmCHARSET_TEXT, XmCHARSET_TEXT,NULL, 0, XmOUTPUT_ALL);
		str_IP = strtok(text, "(");
		str_IP = strtok(NULL, ")");
		
		if (text = XmTextGetString (SENDDIALOG_Text_Message)) {
			udp_SendToString(str_IP,text, IPMSG_SENDMSG);		
		}
		
		XtFree(text);
		mIdx++;
	}
	
	XmTextSetString (SENDDIALOG_Text_Message, NULL); /* clear message area */
}

void sendDialog_AddRemoveItem(struct Broadcast_Packet* p_Item, char m_Option)
{
	XmString xstr_item;
	XmStringTable xstr_list;
	int mFound = 0;
	int mIdx = 0;
	int mCount;	
	char str_Item[50]; 
	char* text;
		
	if(strlen(p_Item->Handlename) == 0)
	{
		sprintf(str_Item, "%s@%s (%s)", p_Item->Username, p_Item->Hostname, p_Item->IP_Address);
	}
	else
	{
		sprintf(str_Item, "%s@%s (%s)", p_Item->Handlename, p_Item->Hostname, p_Item->IP_Address);
	}
	
  	// Get the current entries (and number of entries) from the List
	XtVaGetValues (SENDDIALOG_List_Users, XmNitemCount, &mCount,	XmNitems, &xstr_list, NULL);
		
	xstr_item = XmStringCreateLocalized (str_Item);
		
	while(mCount>mIdx)
	{		
		if(XmStringCompare(xstr_item, xstr_list[mIdx]))
		{
			mFound = 1;
			break;
		}	
		mIdx++;
	}	
	
	if(m_Option == 1)
	{
		if(mFound == 0)
		{
			mIdx = 0;
			while(mCount>mIdx)
			{
				text = (char *) XmStringUnparse (xstr_list[mIdx], NULL,XmCHARSET_TEXT, XmCHARSET_TEXT,NULL, 0, XmOUTPUT_ALL);
			
				if (strcmp (text, str_Item) > 0)
				{
					// str_Item comes before item
					XtFree(text);
					break;
				}
				
				XtFree(text);
				mIdx++;
			}
			
			XmListAddItemUnselected (SENDDIALOG_List_Users, xstr_item, mIdx+1);
			mCount++;
		}
	}
	else
	{
		if(mFound == 1)
		{
			XmListDeletePos(SENDDIALOG_List_Users, mIdx+1);
			mCount--;
		}
	}
	
	XmStringFree (xstr_item);
	sendDialog_UpdateCount(mCount);
}

