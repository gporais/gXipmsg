// created by: geo (March 2012)
#include "sendForm.h"

void sendForm_Init(XtAppContext* xac_App, Widget* w_TopLevel, int argc, char* argv[])
{
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
	SENDFORM_Index = 0;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNchildType, XmFRAME_WORKAREA_CHILD); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNchildVerticalAlignment, XmALIGNMENT_CENTER); SENDFORM_Index++;
	SENDFORM_LblG_Count = XmCreateLabelGadget (SENDFORM_Frame_Member, "0", SENDFORM_Args, SENDFORM_Index);	
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
	XtAddCallback (SENDFORM_BtnG_Refresh, XmNactivateCallback, sendForm_RefreshCallBack, NULL);
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
	XtAddCallback (SENDFORM_BtnG_Send, XmNactivateCallback, sendForm_SendCallBack, NULL);
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
	
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNrows, 10); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNcolumns, 50); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNscrollHorizontal, False); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNwordWrap, True); SENDFORM_Index++;
	XtSetArg (SENDFORM_Args[SENDFORM_Index], XmNeditMode, XmMULTI_LINE_EDIT); SENDFORM_Index++;
	SENDFORM_Text_Message = XmCreateScrolledText(SENDFORM_Form_Lower, "Message", SENDFORM_Args, SENDFORM_Index);
	XtManageChild (SENDFORM_Text_Message);
	
	
	// Materialize major widgets
	XtManageChild (SENDFORM_Form_Upper);
	XtManageChild (SENDFORM_Form_Lower);
	XtManageChild (SENDFORM_Pane_Vertical);
	XtRealizeWidget (*w_TopLevel);    
	
	
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

void sendForm_UpdateCount(int m_Count)
{
	char str_Dest[8];	
	XmString xstr_Dest;
	
	sprintf(str_Dest, "%i", m_Count);
			
	xstr_Dest = XmStringCreateLocalized (str_Dest);		
	XtVaSetValues (SENDFORM_LblG_Count, XmNlabelString, xstr_Dest, NULL);
	
	
	strcpy(str_Dest, "Member");
		
	xstr_Dest = XmStringCreateLocalized (str_Dest);	
	XtVaSetValues (SENDFORM_LblG_Member, XmNlabelString, xstr_Dest, NULL);		
			
	XmStringFree(xstr_Dest);
}

void sendForm_RefreshCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	sendForm_UpdateCount(0);
	XmListDeleteAllItems(SENDFORM_List_Users);
	udp_BroadcastEntry();
}

void sendForm_SendCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	XmStringTable xstr_list;
	int mIdx = 0;
	int mCount;	
	char* text;
	char* str_IP;
	
  	// Get the selected items (and number of selected) from the List
	XtVaGetValues (SENDFORM_List_Users, XmNselectedItemCount, &mCount,	XmNselectedItems, &xstr_list, NULL);
	
	while(mCount>mIdx)
	{
		text = (char *) XmStringUnparse (xstr_list[mIdx], NULL,XmCHARSET_TEXT, XmCHARSET_TEXT,NULL, 0, XmOUTPUT_ALL);
		str_IP = strtok(text, "(");
		str_IP = strtok(NULL, ")");		
		XtFree(text);
		
		if (text = XmTextGetString (SENDFORM_Text_Message)) {
			udp_SendToString(str_IP,text, IPMSG_SENDMSG);	
			XtFree(text);			
		}
			
		mIdx++;
	}
	
	XmTextSetString (SENDFORM_Text_Message, NULL); /* clear message area */
}

void sendForm_AddRemoveItem(struct Broadcast_Packet* p_Item, char m_Option)
{
	XmString xstr_item;
	XmStringTable xstr_list;
	int mFound = 0;
	int mIdx = 0;
	int mCount;	
	char str_Item[50]; 
	char* text;
		
	sprintf(str_Item, "%s@%s (%s)", p_Item->Handlename, p_Item->Hostname, p_Item->IP_Address);
	
  	// Get the current entries (and number of entries) from the List
	XtVaGetValues (SENDFORM_List_Users, XmNitemCount, &mCount,	XmNitems, &xstr_list, NULL);
		
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
			
			XmListAddItemUnselected (SENDFORM_List_Users, xstr_item, mIdx+1);
			mCount++;
		}
	}
	else
	{
		if(mFound == 1)
		{
			XmListDeletePos(SENDFORM_List_Users, mIdx+1);
			mCount--;
		}
	}
	
	XmStringFree (xstr_item);
	sendForm_UpdateCount(mCount);
}

