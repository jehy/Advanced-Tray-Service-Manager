#include "StdAfx.h"
#include "ExitClass.h"

ExitClass::ExitClass(void)
{
	Shutdown=0;
	ClickEventExit=0;
	ExitEvent=CreateEvent(NULL,TRUE,FALSE,"Exit_Tray_App");
}

ExitClass::~ExitClass(void)
{
}
