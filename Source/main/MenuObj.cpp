#include "stdafx.h"
#include "MenuObj.h"

MenuObj::MenuObj(void)
{
	interval=0;
	Shutdown=1;
	BusyEventName=NULL;
}


MenuObj::~MenuObj(void)
{
	if(BusyEventName!=NULL)
		delete (BusyEventName);
}

void MenuObj::SetBusyEventName(char* name)
{
	if(BusyEventName!=NULL)
		delete (BusyEventName);
	size_t z=strlen(name)+1;
	BusyEventName=new char[z];
	strcpy_s(BusyEventName,z,name);
}