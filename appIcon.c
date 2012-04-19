// created by: geo (April 2012)
#include "appIcon.h"

void appIcon_Init(XtAppContext* xac_App, Widget* w_TopLevel, int argc, char* argv[])
{
	XtSetLanguageProc (NULL, NULL, NULL);
	*w_TopLevel = XtVaOpenApplication (xac_App, "gXipmsg", NULL, 0, &argc, argv, NULL,sessionShellWidgetClass, NULL);

	APPICON_Form = XmCreateForm (*w_TopLevel, "ipmsgForm", NULL, 0);
	
	XtVaGetValues (APPICON_Form, XmNforeground, &fg, XmNbackground, &bg, NULL);
	
	pixmap = XmGetPixmap (XtScreen (APPICON_Form), "ipmsg.xpm", fg, bg);
		
	// Create icon button
	n = 0;
	XtSetArg (args[n], XmNlabelType, XmPIXMAP); n++;
	XtSetArg (args[n], XmNlabelPixmap, pixmap); n++;
	APPICON_BtnG_Icon = XmCreatePushButtonGadget(APPICON_Form, "ipmsg.xpm", args, n);
	XtAddCallback (APPICON_BtnG_Icon, XmNactivateCallback, appIcon_IconCallBack, NULL);
	XtManageChild (APPICON_BtnG_Icon);	
	
	APPICON_List_Users = XmCreateScrolledList (APPICON_Form, "List", NULL, 0);
	XtManageChild (APPICON_List_Users);
	
	XtManageChild (APPICON_Form);
	
	XtVaSetValues (*w_TopLevel,
		       XmNmwmDecorations, MWM_DECOR_TITLE | MWM_DECOR_MENU,	
		       XmNmwmFunctions, MWM_FUNC_CLOSE,
		       XmNtitle, "gXip",
		       NULL);	
	
	// Materialize major widgets
	XtRealizeWidget (*w_TopLevel); 	
	XtUnmanageChild (APPICON_List_Users);
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
	sendDialog_Create(&widget, &APPICON_List_Users);
}


void appIcon_AddRemoveItem(struct Broadcast_Packet* p_Item, char m_Option)
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
	XtVaGetValues (APPICON_List_Users, XmNitemCount, &mCount,	XmNitems, &xstr_list, NULL);
		
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
			
			XmListAddItemUnselected (APPICON_List_Users, xstr_item, mIdx+1);
			mCount++;
		}
	}
	else
	{
		if(mFound == 1)
		{
			XmListDeletePos(APPICON_List_Users, mIdx+1);
			mCount--;
		}
	}
	
	XmStringFree (xstr_item);	
}

