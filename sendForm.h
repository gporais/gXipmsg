// created by: geo (March 2012)
#ifndef SENDFORM_H_
#define SENDFORM_H_

#include "common.h"

// Constants


// Variable declerations
Widget SENDFORM_Btn_Refresh;
Atom SENDFORM_DelWin_protocol;

// Function declerations
void sendForm_Init(XtAppContext* xac_App, Widget* w_TopLevel, int argc, char* argv[]);
void sendForm_SetupClose(Widget* w_TopLevel, XtCallbackProc xcp_CloseProc);
void sendForm_SetupTimeout(XtAppContext* xac_App, XtTimerCallbackProc xcp_TOProc);
void sendForm_Run(XtAppContext* xac_App);

#endif /*SENDFORM_H_*/
