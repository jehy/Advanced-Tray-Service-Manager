#pragma once
#include "stdafx.h"
#include "func.h"
#include "class.h"

typedef mvector <click_class*> click_classes;
click_classes Items;
AllXml MenuXml;
HANDLE DieEvent;
click_class* FindItem(int id, click_classes& vec)
{
	for(int i=0;i<vec.RealCount;i++)
		if(vec[i]->id==id)
			return vec[i];
	return NULL;
}
BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam) 
{ 
	char* text;
	text=new char[200];
	int lResult = GetWindowText(hwndChild,text,200);
	CString z;
	z.Append(text);
	z=z.Left(lResult);
	if(!_stricmp(z.GetBuffer(),(char*)lParam))
	{
		//SendMessage(hwndChild, WM_LBUTTONDOWN,NULL,NULL);
		PostMessage(hwndChild, WM_LBUTTONDOWN,NULL,NULL);
		//Sleep(100);
		//SendMessage(hwndChild, WM_LBUTTONUP,NULL,NULL);
		PostMessage(hwndChild, WM_LBUTTONUP,NULL,NULL);
		//SendMessage(hwndChild,BM_CLICK,NULL,NULL); 
	}
	delete(text);
    return TRUE;
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
	current=MenuXml.GetItemOnlyChild(main,"ObjectCaption",1);
	serv->SetObjectCaption(current->subtext);
	current=MenuXml.GetItemOnlyChild(main,"FormCaption",1);
	serv->SetFormCaption(current->subtext);
	current=MenuXml.GetItemOnlyChild(main,"title",1);
	serv->SetTitle(current->subtext);
	Items.push_back(serv);
	return 1;
}

int ClickPluginMenu(int obj_id)
{
	int my_id=floor((float)obj_id/1000);
	click_class* serv=FindItem(my_id,Items);
	HWND wn=FindWindow(NULL,serv->FormCaption);
	if(wn!=NULL)
	{
		SetActiveWindow(wn);
		EnumChildWindows(wn, EnumChildProc,(LPARAM)serv->ObjectCaption);
	}
	else if(serv->Debug==1)
		ShowError("Click plugin: Window not found!",1);
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
