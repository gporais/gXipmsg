// created by: geo (April 2012)
#include "appIcon.h"

void appIcon_Init(XtAppContext* xac_App, Widget* w_TopLevel, int argc, char* argv[])
{	
	appLList = (struct NODE *)malloc(sizeof(struct NODE));
	appLList->ptrData = NULL;
	appLList->next = NULL;
	
	
	XtSetLanguageProc (NULL, NULL, NULL);
	*w_TopLevel = XtVaOpenApplication (xac_App, "gXipmsg", NULL, 0, &argc, argv, NULL,sessionShellWidgetClass, NULL);

	APPICON_Form = XmCreateForm (*w_TopLevel, "ipmsgForm", NULL, 0);
	
	// Create list holder
	APPICON_List_Users = XmCreateScrolledList (APPICON_Form, "List", NULL, 0);
	
	XtVaGetValues (APPICON_Form, XmNforeground, &fg, XmNbackground, &bg, NULL);
	
	pixmap = XmGetPixmap (XtScreen (APPICON_Form), "ipmsg.xpm", fg, bg);
		
	// Create icon button
	n = 0;
	XtSetArg (args[n], XmNlabelType, XmPIXMAP); n++; 
	XtSetArg (args[n], XmNlabelPixmap, pixmap); n++;
	APPICON_BtnG_Icon = XmCreatePushButtonGadget (APPICON_Form, "ipmsg.xpm", args, n);	
	XtAddCallback (APPICON_BtnG_Icon, XmNactivateCallback, appIcon_IconCallBack, APPICON_List_Users);
	XtManageChild (APPICON_BtnG_Icon);	
	
	XtManageChild (APPICON_Form);
	
	XtVaSetValues (*w_TopLevel,
		       XmNmwmDecorations, MWM_DECOR_TITLE | MWM_DECOR_MENU,	
		       XmNmwmFunctions, MWM_FUNC_CLOSE | MWM_FUNC_MOVE,
		       XmNtitle, "gXip",
		       NULL);	
	
	// Materialize major widgets
	XtRealizeWidget (*w_TopLevel);
}


void appIcon_SetupClose(Widget* w_TopLevel, XtCallbackProc xcp_CloseProc)
{
	/* get window manager delete protocol atom */
	APPICON_DelWin_protocol = XmInternAtom(XtDisplay(*w_TopLevel), "WM_DELETE_WINDOW", True);
	
    /* turn off default delete response */
    XtVaSetValues( *w_TopLevel, XmNdeleteResponse, XmDO_NOTHING, NULL);
    
    /* add callback for window manager delete protocol */
    XmAddWMProtocolCallback(*w_TopLevel, APPICON_DelWin_protocol, xcp_CloseProc, NULL);
}


void appIcon_SetupTimeout(XtAppContext* xac_App, XtTimerCallbackProc xcp_TOProc)
{
	XtAppAddTimeOut(*xac_App, 500, xcp_TOProc, *xac_App);	
}


void appIcon_Run(XtAppContext* xac_App)
{
	XtAppMainLoop (*xac_App);
}


void appIcon_IconCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{	
	append_node(appLList,(struct SendClientData*)sendDialog_Create(client_data, 0));	
}

void appIcon_AddRemoveList(struct Broadcast_Packet* p_Item, char m_Option)
{
	appIcon_AddRemoveItem(APPICON_List_Users, p_Item, m_Option, NULL);
	appIcon_UpdateLists(appLList, p_Item, m_Option);
}


void appIcon_AddRemoveItem(Widget wList, struct Broadcast_Packet* p_Item, char m_Option, XtPointer xtLabel)
{
	XmString xstr_item;
	XmStringTable xstr_list;
	int mFound = 0;
	int mIdx = 0;
	int mCount;	
	char str_Item[150]; 
	char* text;	
	char* test;

	char str_Count[4];	
			
	if(strlen(p_Item->Handlename) == 0)
	{
		sprintf(str_Item, "%s@%s (%s)", p_Item->Username, p_Item->Hostname, p_Item->IP_Address);
	}
	else
	{
		sprintf(str_Item, "%s@%s (%s)", p_Item->Handlename, p_Item->Hostname, p_Item->IP_Address);
	}
	
  	// Get the current entries (and number of entries) from the List
	XtVaGetValues (wList, XmNitemCount, &mCount,	XmNitems, &xstr_list, NULL);
		
	xstr_item = XmStringCreateLocalized (str_Item);
		
	
	
	if(m_Option == 1)
	{
		while(mCount>mIdx)
		{		
			if(XmStringCompare(xstr_item, xstr_list[mIdx]))
			{
				mFound = 1;
				break;
			}	
			mIdx++;
		}	
		
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
			
			mCount++;
			XmListAddItemUnselected (wList, xstr_item, mIdx+1);
			if(wList != APPICON_List_Users)
			{
				sprintf(str_Count, "%i", mCount);
				XtVaSetValues(*(Widget*)xtLabel, XmNvalue, str_Count, NULL);				
			}	
		}
	}
	else
	{
		while(mCount>mIdx)
		{		
			text = (char *) XmStringUnparse (xstr_list[mIdx], NULL,XmCHARSET_TEXT, XmCHARSET_TEXT,NULL, 0, XmOUTPUT_ALL);
					
			if ((test = strstr(text, p_Item->IP_Address)) != '\0')
			{
				*(strchr(test,')')) = '\0';
				if(strcmp(test, p_Item->IP_Address) == 0)
				{
					mFound = 1;
					XtFree(text);
					break;
				}
			}		
			
			XtFree(text);						
			mIdx++;
		}	
		
		if(mFound == 1)
		{
			mCount--;
			XmListDeletePos(wList, mIdx+1);	
			if(wList != APPICON_List_Users)
			{
				sprintf(str_Count, "%i", mCount);
				XtVaSetValues(*(Widget*)xtLabel, XmNvalue, str_Count, NULL);
			}	
		}
	}
	
	XmStringFree (xstr_item);	
}


void appIcon_RecieveDialog(struct Broadcast_Packet* p_Item)
{
	recvDialog_Create(APPICON_List_Users, p_Item);
}

void appIcon_ReplyDialog(int mPos)
{
	append_node(appLList,(struct SendClientData*)sendDialog_Create(APPICON_List_Users, mPos+1));
}

void appIcon_Unreg(struct SendClientData* num)
{
	delete_node(appLList, num);	
}

void appIcon_ClearUserList(XtPointer clientList)
{
	XmListDeleteAllItems(APPICON_List_Users);
}


void appIcon_UpdateLists(struct NODE *llist, struct Broadcast_Packet* p_Item, char m_Option)
{	
	while(llist->next != NULL)
	{
		if(llist->ptrData != NULL)
		{
			appIcon_AddRemoveItem(llist->ptrData->dList, p_Item, m_Option, &llist->ptrData->dLabel);
		}
		llist = llist->next;
	}

	if(llist->ptrData != NULL)
	{
		appIcon_AddRemoveItem(llist->ptrData->dList, p_Item, m_Option, &llist->ptrData->dLabel);
	}	
}




void append_node(struct NODE *llist, struct SendClientData* num) {
 while(llist->next != NULL)
  llist = llist->next;

 llist->next = (struct NODE *)malloc(sizeof(struct NODE));
 llist->next->ptrData = num;
 llist->next->next = NULL;
}

void delete_node(struct NODE *llist, struct SendClientData* num) {
 struct NODE *temp;
 temp = (struct NODE *)malloc(sizeof(struct NODE));

 if(llist->ptrData == num) {
  /* remove the node */
  temp = llist->next;
  free(llist);
  llist = temp;
 } else {
  while(llist->next->ptrData != num)
   llist = llist->next;

  temp = llist->next->next;
  free(llist->next);
  llist->next = temp;
 }   
}

