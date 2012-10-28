#include "stdafx.h"
#include "func.h"
#include "class.h"
#include <windows.h>
//#include <stdio.h>

//drive_class DrivesClass;
AllXml MenuXml;
drive_classes Items;
HANDLE DieEvent;

int InitPlugin(char* data, int obj_id,HANDLE DieEvent);
int CreatePluginMenu(HMENU parent,int obj_id);
int RefreshPluginMenu(int obj_id);
int ClickPluginMenu(int obj_id);



drive_class* FindItem(int id, drive_classes& vec)
{
	for(int i=0;i<vec.RealCount;i++)
		if(vec[i]->id==id)
			return vec[i];
	return NULL;
}


int InitPlugin(char* data, int obj_id, HANDLE ExitEvent)
{
	DieEvent=ExitEvent;
	drive_class* DrivesClass=new drive_class;
	//CString mess;
	//mess.Format("I'm told to make an object with text '%s' and id %d",data,obj_id);
	DrivesClass->id=obj_id;
	////parsing
	MenuXml.Parse(data,"item");
	
	xml* main=MenuXml.GetItemOnlyChild(MenuXml.MainElement,"item",1);//main element detected

	xml* current=MenuXml.GetItemOnlyChild(main,"Drives");//getting drives
	//MessageBox(NULL,current->name,"",MB_OK);
	if(!_stricmp(current->subtext,"ALL"))
		DrivesClass->Drives=NULL;
	else
	{
		for(int i=0;i<MenuXml.vec.RealCount;i++)
			if(MenuXml.vec[i]->parent==current)DrivesClass->DriveTypes.push_back(atoi(MenuXml.vec[i]->subtext));
	}

	current=MenuXml.GetItemOnlyChild(main,"ShowVolName");//
	if(IsTrue(current->subtext))DrivesClass->ShowVolName=true;

	current=MenuXml.GetItemOnlyChild(main,"ShowVolIcon");//
	if(IsTrue(current->subtext))DrivesClass->ShowVolIcon=true;

	current=MenuXml.GetItemOnlyChild(main,"ShowVolSpace");//
	if(IsTrue(current->subtext))DrivesClass->ShowVolSpace=true;

	Items.push_back(DrivesClass);
	return 1;
}

int ClickPluginMenu(int obj_id)
{
	/*
	int my_id=floor((float)obj_id/1000);
	int sub_id=obj_id-my_id*1000;
	drive_class* serv=FindItem(my_id,Items);
	int z;
	switch(sub_id)
	{
	case 1:
		z=MyStartService(serv->name,(const char**)serv->Args,serv->ArgNum);
		//if(!z)MessageBox(NULL,"Service could not be started!","Error",MB_ICONWARNING);
		break;
	case 2:
		z=MyControlService(serv->name,SERVICE_CONTROL_STOP);
		//if(!z)MessageBox(NULL,"Service could not be stopped!","Error",MB_ICONWARNING);
		break;
	case 3:
		z=MyControlService(serv->name,SERVICE_CONTROL_PAUSE);
		//if(!z)MessageBox(NULL,"Service could not be paused!","Error",MB_ICONWARNING);
		break;
	}
	/*
	CString msg;
	msg.Format("message from item %d.%d",my_id,sub_id);
	MessageBox(NULL,msg,"",MB_OK);
	*/
	////######## 1-start
	////######## 2-stop
	////#########3-pause
	////######## 4-restart

	/*
	int z=(int)ShellExecute(NULL,serv->action,serv->app,serv->way,serv->dir,serv->launch);
	if(z<32)ShowError("Some kind of error happened!");
		*/	
	return 1;
}

int CreatePluginMenu(HMENU parent,int obj_id)
{
	int MenuNum=obj_id*1000+1;
	int add=0;
	
	xml* main=MenuXml.GetItemOnlyChild(MenuXml.MainElement,"item",1);
	xml* current=MenuXml.GetItemOnlyChild(main,"title",1);

	drive_class* DrivesClass=FindItem(obj_id,Items);

	HMENU NewMenu=CreatePopupMenu();
	AppendMenu(parent,MF_POPUP+MF_STRING,(UINT_PTR)NewMenu,current->subtext);
	DrivesClass->hMenu=parent;
	DrivesClass->number=GetMenuItemCount(parent)-1;

	AppendMenu(NewMenu,MF_STRING,MenuNum+add,"1");// append menu
	add++;
	AppendMenu(NewMenu,MF_STRING,MenuNum+add,"2");// append menu
	add++;
	AppendMenu(NewMenu,MF_STRING,MenuNum+add,"3");// append menu
	add++;
	AppendMenu(NewMenu,MF_STRING,MenuNum+add,"4");// append menu
	add++;
	//MessageBox(0,"make menu!","",MB_OK);
	return 1;
}
int RefreshPluginMenu(int obj_id)
{
	/*
	CString pic;
	switch(ssStatus.dwCurrentState)
	{
	case SERVICE_START_PENDING:
		pic="SERVICE_START_PENDING.bmp";
		break;
	case SERVICE_CONTINUE_PENDING:
		pic="SERVICE_CONTINUE_PENDING.bmp";
		break;
	case SERVICE_PAUSED:
		pic="SERVICE_PAUSED.bmp";
		break;
	case SERVICE_PAUSE_PENDING:
		pic="SERVICE_PAUSE_PENDING.bmp";
		break;
	case SERVICE_RUNNING:
		pic="SERVICE_RUNNING.bmp";
		break;
	case SERVICE_STOP_PENDING:
		pic="SERVICE_STOP_PENDING.bmp";
		break;
	case SERVICE_STOPPED:
		pic="SERVICE_STOPPED.bmp";
		break;
	}
	//#######################################################################
	//HBITMAP hBitmapChecked = NULL;
	char* way=GetApplicationDir();
	CString dir;
	dir.Append(way);
	delete(way);
	dir.Append("pic\\service");
	SetCurrentDirectory(dir);
	dir.ReleaseBuffer();
	
	if(serv->pic!=NULL)DeleteObject(serv->pic);
	serv->pic = (HBITMAP)LoadImage(NULL, pic, IMAGE_BITMAP, 0, 0,
	LR_LOADFROMFILE  | LR_SHARED);

    SetMenuItemBitmaps(serv->hMenu, serv->number, MF_BYPOSITION, serv->pic,serv->pic);
	//CheckMenuItem(serv->hMenu, serv->number, (MF_BYPOSITION+MF_CHECKED));
	//CheckMenuItem(serv->hMenu, serv->number, (MF_BYPOSITION+MF_UNCHECKED));
	EnableMenuItem(serv->hMenu, serv->number,(MF_BYPOSITION+MF_GRAYED));
	//z=
	EnableMenuItem(serv->hMenu, serv->number,(MF_BYPOSITION+MF_ENABLED));
	//if(z==-1)MessageBox(NULL,"Fuck! Doesn't exist!","",MB_OK);
	//EnableMenuItem(serv->hMenu, serv->number, MF_BYPOSITION||MF_ENABLED);
	//HWND hwnd=NULL;
	//if(!HiliteMenuItem(hwnd,serv->hMenu,serv->number,MF_BYPOSITION||MF_HILITE));

	//HWND win=GetWindow((HWND)serv->hMenu,GW_OWNER);
	//PostMessage(win,WM_INITMENU,(WPARAM)serv->hMenu,NULL);
	//EnableMenuItem(serv->hMenu, serv->number,MF_ENABLED);
	//DrawMenuBar(GetParent((HWND)serv->hMenu));
	*/
	return 1;
}
