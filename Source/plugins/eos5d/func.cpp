#pragma once
#include "stdafx.h"
#include "func.h"
#include "class.h"
#include <time.h>

typedef mvector <click_class*> click_classes;
click_classes Items;
AllXml MenuXml;
HANDLE DieEvent;
time_t seconds;

click_class* FindItem(int id, click_classes& vec)
{
	for(int i=0;i<vec.RealCount;i++)
		if(vec[i]->id==id)
			return vec[i];
	return NULL;
}


int InitPlugin(char* data, int obj_id, HANDLE ExitEvent)
{
	DieEvent=ExitEvent;
	click_class* serv=new(click_class);
	serv->id=obj_id;
	////parsing
	MenuXml.Parse(data,"item");
	xml* main=MenuXml.GetItemOnlyChild(MenuXml.MainElement,"item",1);
	xml* current=MenuXml.GetItemOnlyChild(main,"Debug");
	if(current!=NULL)
		if(IsTrue(current->subtext))
			serv->Debug=1;
	serv->id=obj_id;
	Items.push_back(serv);
	seconds=0;
	return 1;
}

int ClickPluginMenu(int obj_id)
{
	int my_id=floor((float)obj_id/1000);
	click_class* serv=FindItem(my_id,Items);
	
	
	time_t seconds2 = time (0);
	if(seconds2-seconds>=1)
	{
		seconds=time (0);
		HWND wn=FindWindow(NULL," EOS 5D Mark II");
		if(wn==NULL)
			MessageBox(NULL,"Can't find main window!","ERROR",MB_OK);

		wn=GetWindow(wn,GW_CHILD);
		wn=GetWindow(wn,GW_HWNDLAST);
		wn=GetWindow(wn,GW_CHILD);
		wn=GetWindow(wn,GW_HWNDNEXT);
		wn=GetWindow(wn,GW_HWNDNEXT);
		PostMessage(wn, WM_LBUTTONDOWN,NULL,NULL);
		PostMessage(wn, WM_LBUTTONUP,NULL,NULL);
	}
	seconds=time (0);
	return 1;
}

int CreatePluginMenu(HMENU parent,int obj_id)
{
	int MenuNum=obj_id*1000+1;
	click_class* serv=FindItem(obj_id,Items);
	AppendMenu(parent,MF_STRING,MenuNum,serv->title);// append menu
	serv->hMenu=parent;
	return 1;
}
int RefreshPluginMenu(int obj_id)
{
	return 1;
}
