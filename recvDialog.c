// created by: geo (April 2012)
#include "recvDialog.h"


void recvDialog_Destroy (Widget dialog, XtPointer client_data, XtPointer call_data)
{
	struct RecvClientData* data = (struct RecvClientData*) client_data;
		
	XtFree ((char*) data);	
}

void recvDialog_Create(XtPointer xt_List, struct Broadcast_Packet* p_Item)
{
	Widget* w_List = (Widget*)xt_List;
	
	Widget RECVDIALOG_Dialog;
	Widget RECVDIALOG_MainForm;
	Widget RECVDIALOG_Form_Upper;
	Widget RECVDIALOG_Form_Lower;
	Widget RECVDIALOG_Frame;
	Widget RECVDIALOG_LblG_FrameTitle;
	Widget RECVDIALOG_LblG_FrameChild;	
	Widget RECVDIALOG_Text_Message;
	Widget RECVDIALOG_BtnG_Download;
	Widget RECVDIALOG_BtnG_Reply;
	Widget RECVDIALOG_BtnG_Close;	
	Widget RECVDIALOG_TglG_Quote;
	
	char str_Buff[150];	
	XmString xstr_Buff;
	
	int mClientSocket = -1;
	int mCount;
	int mIdx = 0;
	XmStringTable xstr_list;
	char* text;	
	char* test;
	time_t clock = time(NULL);
	struct RecvClientData* data = XtNew (struct RecvClientData);
	
	// Get the current entries (and number of entries) from the List
	XtVaGetValues (*w_List, XmNitemCount, &mCount,	XmNitems, &xstr_list, NULL);

	while(mCount>mIdx)
	{		
		text = (char *) XmStringUnparse (xstr_list[mIdx], NULL,XmCHARSET_TEXT, XmCHARSET_TEXT,NULL, 0, XmOUTPUT_ALL);
		
		if ((test = strstr(text, p_Item->IP_Address)) != '\0')
		{
			*(strchr(test,')')) = '\0';
			if(strcmp(test, p_Item->IP_Address) == 0)
			{			
				// str_Item comes before item
				sprintf(str_Buff, "%s)\n%s", text, ctime(&clock));
				XtFree(text);
				break;
			}
		}		
		
		XtFree(text);						
		mIdx++;
	}	
	
	
		
	// Create dialog
	RECVDIALOG_Dialog = XtVaCreatePopupShell("recv_diag", 
			topLevelShellWidgetClass, XtParent (*w_List),
			XmNtitle, "Recieve Message",
			XmNdeleteResponse, XmDESTROY,			
			NULL);
	XtAddCallback (RECVDIALOG_Dialog, XmNpopupCallback, gXipmsg_MapDialog, NULL);
	XtAddCallback (RECVDIALOG_Dialog, XmNdestroyCallback, recvDialog_Destroy, data);

	// Create paned window
	RECVDIALOG_MainForm = XmCreateForm (RECVDIALOG_Dialog, "recv_form", NULL, 0);
		
	// Create form
	n = 0;	
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++;
	RECVDIALOG_Form_Upper = XmCreateForm (RECVDIALOG_MainForm, "recv_form_upr", args, n);
	
	
	// Create frame
	n = 0;
	XtSetArg (args[n], XmNshadowType, XmSHADOW_ETCHED_OUT); n++;
	XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNtopOffset, 5); n++;
	XtSetArg (args[n], XmNleftOffset, 5); n++;
	XtSetArg (args[n], XmNrightOffset, 5); n++;
	RECVDIALOG_Frame = XmCreateFrame (RECVDIALOG_Form_Upper, "recv_frame", args, n);
	
	
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
	
	// Create form
	n = 0;
	XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
	XtSetArg (args[n], XmNtopWidget, RECVDIALOG_Form_Upper); n++;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
	RECVDIALOG_Form_Lower = XmCreateForm (RECVDIALOG_MainForm, "recv_form_lwr", args, n);
	
	// Create download button
	n = 0;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++;  
	XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM); n++; 
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++; 
	XtSetArg (args[n], XmNtopOffset, 7); n++; 
	XtSetArg (args[n], XmNleftOffset, 5); n++; 
	XtSetArg (args[n], XmNrightOffset, 5); n++; 
	RECVDIALOG_BtnG_Download = XmCreatePushButtonGadget (RECVDIALOG_Form_Lower, "Download", args, n);
	XtAddCallback (RECVDIALOG_BtnG_Download, XmNactivateCallback, recvDialog_DownloadCallBack, (XtPointer)data);
	
	if((GET_OPT(p_Item->IP_Flags) & IPMSG_FILEATTACHOPT)  == IPMSG_FILEATTACHOPT)
	{
		XtManageChild (RECVDIALOG_BtnG_Download);
	}
	
	// Create reply button
	n = 0;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNleftOffset, 5); n++;
	XtSetArg (args[n], XmNbottomOffset, 5); n++;
	RECVDIALOG_BtnG_Reply = XmCreatePushButtonGadget (RECVDIALOG_Form_Lower, "Reply", args, n);		
	XtAddCallback (RECVDIALOG_BtnG_Reply, XmNactivateCallback, recvDialog_ReplyCallBack, (XtPointer)data);
	XtManageChild (RECVDIALOG_BtnG_Reply);
	
	// Create close button
	n = 0;
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNrightOffset, 5); n++;
	XtSetArg (args[n], XmNbottomOffset, 5); n++;
	RECVDIALOG_BtnG_Close = XmCreatePushButtonGadget (RECVDIALOG_Form_Lower, "Close", args, n);		
	XtAddCallback (RECVDIALOG_BtnG_Close, XmNactivateCallback, recvDialog_CloseCallBack, NULL);
	XtManageChild (RECVDIALOG_BtnG_Close);
	
	// Create quote checkbox
	n = 0;
	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_WIDGET); n++; 
	XtSetArg (args[n], XmNleftWidget, RECVDIALOG_BtnG_Reply); n++;
	XtSetArg (args[n], XmNleftOffset, 5); n++;
	XtSetArg (args[n], XmNbottomOffset, 5); n++;
	XtSetArg (args[n], XmNindicatorOn, XmINDICATOR_CHECK_BOX); n++;
	XtSetArg (args[n], XmNset, XmSET); n++;
	RECVDIALOG_TglG_Quote = XmCreateToggleButtonGadget (RECVDIALOG_Form_Lower, "Quote", args, n);
	XtManageChild (RECVDIALOG_TglG_Quote);
	
	
	// Creatr text message
	n = 0;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++; 												
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++;	
	XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET); n++; 
	XtSetArg (args[n], XmNtopWidget, RECVDIALOG_BtnG_Download); n++;
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
	RECVDIALOG_Text_Message = XmCreateScrolledText(RECVDIALOG_Form_Lower, "Message", args, n);	
	XtManageChild (RECVDIALOG_Text_Message);
	
	strcpy(bgcolor, "black");
	strcpy(fgcolor, "white");
	XtVaSetValues(RECVDIALOG_Text_Message,
	        XtVaTypedArg, XmNforeground, XtRString, fgcolor,
	        strlen(fgcolor) + 1, NULL);	
	XtVaSetValues(RECVDIALOG_Text_Message,
		        XtVaTypedArg, XmNbackground, XtRString, bgcolor,
		        strlen(bgcolor) + 1, NULL);	
	
	XtManageChild (RECVDIALOG_Form_Upper);
	XtManageChild (RECVDIALOG_Form_Lower);
	XtManageChild (RECVDIALOG_MainForm);
	XtPopup (RECVDIALOG_Dialog, XtGrabNone);
	
	/* complete the timeout client data */
	data->dPos = mIdx;
	data->dText = RECVDIALOG_Text_Message;
	data->dCheck = RECVDIALOG_TglG_Quote;
	data->dSocket = mClientSocket;
	data->dServerInfo = *p_Item;
	
	XmStringFree (xstr_Buff);
}


void recvDialog_ReplyCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	struct RecvClientData* data = (struct RecvClientData*) client_data;
	char* text;
	
	Widget RECVDIALOG_Dialog = XtParent(widget);
	RECVDIALOG_Dialog = XtParent(RECVDIALOG_Dialog);
	RECVDIALOG_Dialog = XtParent(RECVDIALOG_Dialog);	

	XtDestroyWidget(RECVDIALOG_Dialog);	
	
	text = XmTextGetString (data->dText);
	appIcon_ReplyDialog(data->dPos, XmToggleButtonGadgetGetState(data->dCheck) ? text : NULL);	
	XtFree (text);
}


void recvDialog_CloseCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	Widget RECVDIALOG_Dialog = XtParent(widget);
	RECVDIALOG_Dialog = XtParent(RECVDIALOG_Dialog);
	RECVDIALOG_Dialog = XtParent(RECVDIALOG_Dialog);
		
	XtDestroyWidget(RECVDIALOG_Dialog);
}


void recvDialog_DownloadCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	struct RecvClientData* data = (struct RecvClientData*) client_data;
	struct FileInfo_Packet RecvdFileInfos;
	
	printf("init.. \n");	
	tcp_InitClient(data);
	
	pack_UnpackExtended(data, &RecvdFileInfos);
	printf("\nunpacked: %s:%s:%s:%s:%s\n", RecvdFileInfos.FileID, RecvdFileInfos.FileName, RecvdFileInfos.FileSize, RecvdFileInfos.FileTime, RecvdFileInfos.FileAttrib);
	
	printf("close %s\n", data->dServerInfo.Extended);
	tcp_CloseClient(data);
	
	
}


