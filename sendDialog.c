// created by: geo (March 2012)
#include "sendDialog.h"


void sendDialog_Destroy(Widget dialog, XtPointer client_data, XtPointer call_data)
{
	struct SendClientData* data = (struct SendClientData*) client_data;
	
	if(data->Extended != NULL)
	{
		free(data->Extended);
		data->Extended = NULL;
	}
		
	appIcon_Unreg(data);
	
	XtFree ((char*) data);	
}

struct SendClientData* sendDialog_Create(XtPointer xt_List, int mSelPos, XtPointer xt_Text)
{
	Widget* w_List = (Widget*)xt_List;
		
	Widget SENDDIALOG_Dialog;
	Widget SENDDIALOG_Text;
	Widget SENDDIALOG_List;
	Widget SENDDIALOG_Form_Upper;
	Widget SENDDIALOG_Frame_Member;
	Widget SENDDIALOG_LblG_Count;
	Widget SENDDIALOG_LblG_Member;
	Widget SENDDIALOG_BtnG_Refresh;
	Widget SENDDIALOG_Pane_Vertical;
	Widget SENDDIALOG_Form_Lower;
	Widget SENDDIALOG_BtnG_Attach;
	Widget SENDDIALOG_BtnG_Send;
	Widget SENDDIALOG_BtnG_Close;
		
	int m_Count;	
	char str_Count[4];	
	char* strText;
	XmStringTable xstr_list;	
	
	struct SendClientData* data = XtNew (struct SendClientData);
	
	
	// Get the current entries (and number of entries) from the List
	XtVaGetValues (*w_List, XmNitemCount, &m_Count,	XmNitems, &xstr_list, NULL);	
		
	// Create dialog
	SENDDIALOG_Dialog = XtVaCreatePopupShell("send_diag", 
			topLevelShellWidgetClass, XtParent (*w_List),
			XmNtitle, "Send Message",
			XmNdeleteResponse, XmDESTROY,			
			NULL);	
	XtAddCallback (SENDDIALOG_Dialog, XmNpopupCallback, gXipmsg_MapDialog, NULL);
	XtAddCallback (SENDDIALOG_Dialog, XmNdestroyCallback, sendDialog_Destroy, data);

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
	
	n = 0;
	XtSetArg (args[n], XmNchildType, XmFRAME_WORKAREA_CHILD); n++;
	XtSetArg (args[n], XmNchildVerticalAlignment, XmALIGNMENT_CENTER); n++;
	XtSetArg (args[n], XmNcolumns, 5); n++;
	XtSetArg (args[n], XmNeditable, False); n++;
	XtSetArg (args[n], XmNcursorPositionVisible, False); n++;
	XtSetArg (args[n], XmNvalue, str_Count); n++;
	SENDDIALOG_LblG_Count = XmCreateText (SENDDIALOG_Frame_Member, "Count", args, n);	
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
	XtSetArg (args[n], XmNitemCount, m_Count); n++;
	XtSetArg (args[n], XmNitems, xstr_list); n++;
	SENDDIALOG_List = XmCreateScrolledList (SENDDIALOG_Form_Upper, "Users", args, n);
	
	if(mSelPos > 0)
	{
		XmListSelectPos (SENDDIALOG_List, mSelPos, 0);
		XmListSetPos (SENDDIALOG_List, mSelPos);
	}
	
	XtManageChild (SENDDIALOG_List);
	
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
	XtAddCallback (SENDDIALOG_BtnG_Refresh, XmNactivateCallback, sendDialog_RefreshCallBack, (XtPointer)data);
	XtManageChild (SENDDIALOG_BtnG_Refresh);	
	
	// Create lower form
	SENDDIALOG_Form_Lower = XmCreateForm (SENDDIALOG_Pane_Vertical, "Lower", NULL, 0);
	
	// Create attach button
	n = 0;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++;  
	XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM); n++; 						
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++; 	
	XtSetArg (args[n], XmNleftOffset, 5); n++; 
	XtSetArg (args[n], XmNtopOffset, 3); n++; 
	XtSetArg (args[n], XmNrightOffset, 5); n++; 
	SENDDIALOG_BtnG_Attach = XmCreatePushButtonGadget (SENDDIALOG_Form_Lower, "Attach", args, n);
	XtAddCallback (SENDDIALOG_BtnG_Attach, XmNactivateCallback, sendDialog_AttachCallBack, (XtPointer)data);
	
	XtManageChild (SENDDIALOG_BtnG_Attach);
	
	
	// Create send button
	n = 0;
	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
	SENDDIALOG_BtnG_Send = XmCreatePushButtonGadget (SENDDIALOG_Form_Lower, "Send", args, n);		
	XtAddCallback (SENDDIALOG_BtnG_Send, XmNactivateCallback, sendDialog_SendCallBack, (XtPointer)data);
	XtManageChild (SENDDIALOG_BtnG_Send);
	
	
	// Create close button
	n = 0;
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
	SENDDIALOG_BtnG_Close = XmCreatePushButtonGadget (SENDDIALOG_Form_Lower, "Close", args, n);		
	XtAddCallback (SENDDIALOG_BtnG_Close, XmNactivateCallback, sendDialog_CloseCallBack, NULL);
	XtManageChild (SENDDIALOG_BtnG_Close);
	
	
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
	XtSetArg (args[n], XmNvalue, (char*)xt_Text); n++;
	SENDDIALOG_Text = XmCreateScrolledText(SENDDIALOG_Form_Lower, "Message", args, n);
	XtManageChild (SENDDIALOG_Text);
	
	strcpy(bgcolor, "black");
	strcpy(fgcolor, "green");
	XtVaSetValues(SENDDIALOG_Text,
	        XtVaTypedArg, XmNforeground, XtRString, fgcolor,
	        strlen(fgcolor) + 1, NULL);	
	XtVaSetValues(SENDDIALOG_Text,
		        XtVaTypedArg, XmNbackground, XtRString, bgcolor,
		        strlen(bgcolor) + 1, NULL);	
	

	if(((char*)xt_Text)!= NULL)
	{
		if(strlen((char*)xt_Text) > 0)
		{
			XmTextReplace (SENDDIALOG_Text, 0, 0, ">");
			n = 0;
			m_Count = 1;
			while(((char*)xt_Text)[n] != '\0')
			{
				if(((char*)xt_Text)[n] == '\n')
				{
					XmTextReplace (SENDDIALOG_Text, n+m_Count+1, n+m_Count+1, ">");
					m_Count++;
				}
				n++;
			}
			
			strText = XmTextGetString(SENDDIALOG_Text);
			strcat(strText,"\n");
			XmTextSetString(SENDDIALOG_Text, strText);
		}
	}	
	
	// Materialize major widgets
	XtManageChild (SENDDIALOG_Form_Upper);
	XtManageChild (SENDDIALOG_Form_Lower);
	XtManageChild (SENDDIALOG_Pane_Vertical);	
	XtPopup (SENDDIALOG_Dialog, XtGrabNone);
	
	/* complete the timeout client data */
	data->dList = SENDDIALOG_List;
	data->dText = SENDDIALOG_Text;
	data->dLabel = SENDDIALOG_LblG_Count;
	
	data->Extended = NULL;
	data->m_Count = 0;
	return data;
}


void sendDialog_RefreshCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	struct SendClientData* data = (struct SendClientData*) client_data;

	XmListDeleteAllItems(data->dList);
	appIcon_ClearUserList(client_data);
	udp_BroadcastEntry();
}

void sendDialog_SendCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	struct SendClientData* data = (struct SendClientData*) client_data;
	
	XmStringTable xstr_list;
	int mIdx = 0;
	int mCount = 0;	
	char* text;
	char* str_IP;
	
	Widget SENDDIALOG_Dialog = XtParent(widget);
	SENDDIALOG_Dialog = XtParent(SENDDIALOG_Dialog);
	SENDDIALOG_Dialog = XtParent(SENDDIALOG_Dialog);		
	
  	// Get the selected items (and number of selected) from the List
	XtVaGetValues (data->dList, XmNselectedItemCount, &mCount,	XmNselectedItems, &xstr_list, NULL);
			
	if(mCount > 0)
	{
		while(mCount>mIdx)
		{
			text = (char *) XmStringUnparse (xstr_list[mIdx], NULL,XmCHARSET_TEXT, XmCHARSET_TEXT,NULL, 0, XmOUTPUT_ALL);
			str_IP = strtok(text, "(");
			str_IP = strtok(NULL, ")");
			
			if (text = XmTextGetString (data->dText)) {
				if(data->Extended == NULL)
					udp_SendToString(str_IP,text, IPMSG_SENDMSG, data->Extended);
				else
					udp_SendToString(str_IP,text, IPMSG_SENDMSG | IPMSG_FILEATTACHOPT, data->Extended);
			}
			
			XtFree(text);
			mIdx++;
		}
			
		XtDestroyWidget(SENDDIALOG_Dialog);
	}
}

void sendDialog_CloseCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	Widget SENDDIALOG_Dialog = XtParent(widget);
	SENDDIALOG_Dialog = XtParent(SENDDIALOG_Dialog);
	SENDDIALOG_Dialog = XtParent(SENDDIALOG_Dialog);
		
	XtDestroyWidget(SENDDIALOG_Dialog);
}

void sendDialog_AttachCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	struct SendClientData* data = (struct SendClientData*) client_data;
	Widget dialog = XmCreateSelectionDialog (XtParent (widget), "Attachments", NULL, 0);
	Widget add_button;
	XmString xstr_item = XmStringCreateLocalized("Attachments");
	XmString xstr_apply = XmStringCreateLocalized("Delete");
	XmString xstr_cancel = XmStringCreateLocalized("Close");
	int mIdx;	

	XtVaSetValues(dialog, 
				XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
				XmNautoUnmanage, False,
				XmNlistLabelString, xstr_item,
				XmNapplyLabelString, xstr_apply,
				XmNcancelLabelString, xstr_cancel,
				NULL);	
	
	XtVaSetValues(XtNameToWidget(dialog, "*ItemsList"),	
				XmNselectionPolicy, XmEXTENDED_SELECT,
				NULL);
	
	data->dDialog = dialog;
	data->dAttach = widget;
	
	for(mIdx = 0; mIdx < data->m_Count; mIdx++)
	{
		XmListAddItemUnselected (XtNameToWidget(dialog, "*ItemsList"), data->xstr_list[mIdx], 0);
	}	
		
	XtUnmanageChild(XtNameToWidget(dialog, "Selection"));
	XtUnmanageChild(XtNameToWidget(dialog, "Text"));
	XtUnmanageChild(XtNameToWidget(dialog, "OK"));
	XtUnmanageChild(XtNameToWidget(dialog, "Help"));
	XtAddCallback (dialog, XmNapplyCallback, sendDialog_DeleteItemCallBack, (XtPointer)data);
	XtAddCallback (dialog, XmNcancelCallback, sendDialog_CloseAttachCallBack, (XtPointer)data);
	
	
	XmCreatePushButtonGadget(dialog, "Unmanaged", NULL, 0);
	add_button = XmCreatePushButtonGadget(dialog, "Add Files", NULL, 0);
	XtAddCallback (add_button, XmNactivateCallback, sendDialog_AddFilesCallBack, (XtPointer)data);
	XtManageChild(add_button);
	XtManageChild(dialog);
	
	XmStringFree(xstr_cancel);
	XmStringFree(xstr_apply);
	XmStringFree(xstr_item);
}


void sendDialog_AddFilesCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	Widget dialog = XmCreateFileSelectionDialog (XtParent (widget), "File Add", NULL, 0);
	XmString xstr_ok = XmStringCreateLocalized("Open");
	
	XtVaSetValues(dialog, 
				XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL, 
				XmNokLabelString, xstr_ok,				
				NULL);
		
	XtVaSetValues(XtNameToWidget(dialog, "*ItemsList"),	XmNselectionPolicy, XmEXTENDED_SELECT, NULL);	
	

	XtSetSensitive(XtNameToWidget(dialog, "Help"), False);
	XtAddCallback (dialog, XmNokCallback, sendDialog_AddFileCallBack, client_data);
	XtAddCallback (dialog, XmNcancelCallback, sendDialog_CancelAddCallBack, NULL);
		
	XtManageChild(dialog);	
	
	XmStringFree(xstr_ok);
}

void sendDialog_CloseAttachCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	struct SendClientData* data = (struct SendClientData*) client_data;
	char strAttachments[30];
	char* strFilename = NULL;
	char* strSingleFile = NULL;
	char* strTemp = NULL;
	char* strExtended = NULL;
	int mIdx;
	struct stat st;
		
	if(data->m_Count == 0)
	{
		recvDialog_UpdateBtnLabel(data->dAttach, "Attach");
		data->Extended = NULL;
	}
	else
	{
		sprintf(strAttachments, "Attachments (%i)", data->m_Count);
		recvDialog_UpdateBtnLabel(data->dAttach, strAttachments);
		
		for(mIdx = 0; mIdx<data->m_Count; mIdx++)
		{
			strFilename = (char *) XmStringUnparse (data->xstr_list[mIdx], NULL,XmCHARSET_TEXT, XmCHARSET_TEXT,NULL, 0, XmOUTPUT_ALL);
			stat(strFilename,&st);
			
			strSingleFile = malloc(strlen(strrchr(strFilename, '/')) + 6 + 30);
			sprintf(strSingleFile, "%i:%s:%lx:%lx:1:", (long)st.st_ino, strrchr(strFilename, '/') + 1, (long)st.st_size, (long)st.st_ctime);
			
			if(strExtended != NULL)
			{
				strTemp = strExtended;				
				strExtended = malloc(strlen(strTemp) + strlen(strSingleFile) + 2);
				strcpy(strExtended, strTemp);
				free(strTemp);				
			}
			else
			{
				strExtended = malloc(strlen(strSingleFile) + 2);
				strExtended[0] = '\0';
			}
			
			strcat(strExtended, strSingleFile);
			
			
			free(strSingleFile);
			
			XtFree(strFilename);
		}		
		data->Extended = strExtended;		
	}
	
	XtUnmanageChild(widget);
}

void sendDialog_DeleteItemCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	struct SendClientData* data = (struct SendClientData*) client_data;
	Widget attachList = XtNameToWidget((Widget)data->dDialog, "*ItemsList");
	XmStringTable xstr_list;
	int m_Count = 0, mIdx = 0;	
		
	// Get the selected items (and number of selected) from the List
	XtVaGetValues (attachList, XmNselectedItemCount, &m_Count, XmNselectedItems, &xstr_list, NULL);
	
	for(mIdx = 0; mIdx < m_Count; mIdx++)
	{
		XmListDeleteItem (attachList, xstr_list[0]);
	}	
	
	XtVaGetValues (attachList, XmNitemCount, &data->m_Count, XmNitems, &data->xstr_list, NULL);
}





void sendDialog_AddFileCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	struct SendClientData* data = (struct SendClientData*) client_data;
	Widget attachList = XtNameToWidget((Widget)data->dDialog, "*ItemsList");
	Widget selectedList = XtNameToWidget(widget, "*ItemsList");
	XmStringTable xstr_list;
	int m_Count = 0, mIdx = 0;
		
	// Get the selected items (and number of selected) from the List
	XtVaGetValues (selectedList, XmNselectedItemCount, &m_Count, XmNselectedItems, &xstr_list, NULL);
	
	for(mIdx = 0; mIdx < m_Count; mIdx++)
	{
		if(!XmListItemExists (attachList, xstr_list[mIdx]))
			XmListAddItemUnselected (attachList, xstr_list[mIdx], 0);
	}
	
	XtVaGetValues (attachList, XmNitemCount, &data->m_Count, XmNitems, &data->xstr_list, NULL);
	
	XtUnmanageChild(widget);	
}

void sendDialog_CancelAddCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	XtUnmanageChild(widget);
}

