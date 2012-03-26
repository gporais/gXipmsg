// created by: geo (March 2012)
#include "sendForm.h"

void sendForm_Init(XtAppContext* xac_App, Widget* w_TopLevel, int argc, char* argv[])
{
	XtSetLanguageProc (NULL, NULL, NULL);
	*w_TopLevel = XtVaOpenApplication (xac_App, "Hello", NULL, 0, &argc, argv, NULL,sessionShellWidgetClass, NULL);
	
	SENDFORM_Btn_Refresh = XmCreatePushButton (*w_TopLevel, "Refresh", NULL, 0);	
	XtManageChild (SENDFORM_Btn_Refresh);	
	
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

