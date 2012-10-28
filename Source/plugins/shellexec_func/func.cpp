#include "stdafx.h"
#include "func.h"
#include "class.h"
typedef mvector <doc_class*> doc_classes;
doc_classes Items;
AllXml MenuXml;

HANDLE DieEvent;

int InitPlugin(char* data, int obj_id,HANDLE DieEvent);
int CreatePluginMenu(HMENU parent,int obj_id);
int RefreshPluginMenu(int obj_id);
int ClickPluginMenu(int obj_id);

inline char* GetExecuteError(int z)
{
	CString err="";
	switch (z)
	{
	case 0:
		err="The operating system is out of memory or resources.";
		break;
	case ERROR_FILE_NOT_FOUND:
		err="The specified file was not found";
		break;
	case ERROR_PATH_NOT_FOUND:
		err="The specified path was not found";
		break;
	case ERROR_BAD_FORMAT:
		err="The .exe file is invalid (non-Microsoft Win32 .exe or error in .exe image)";
		break;
	case SE_ERR_ACCESSDENIED:
		err="The operating system denied access to the specified file";
		break;
	case SE_ERR_ASSOCINCOMPLETE:
		err="The file name association is incomplete or invalid";
		break;
	case SE_ERR_DDEBUSY:
		err="The Dynamic Data Exchange (DDE) transaction could not be completed because other DDE transactions were being processed";
		break;
	case SE_ERR_DDEFAIL:
		err="The DDE transaction failed";
		break;
	case SE_ERR_DDETIMEOUT:
		err="The DDE transaction could not be completed because the request timed out";
		break;
	case SE_ERR_DLLNOTFOUND:
		err="The specified DLL was not found";
		break;
//	case SE_ERR_FNF:
//		err="The specified file was not found";
		break;
	case SE_ERR_NOASSOC:
		err="There is no application associated with the given file name extension. This error will also be returned if you attempt to print a file that is not printable.";
		break;
	case SE_ERR_OOM:
		err="There was not enough memory to complete the operation";
		break;
//	case SE_ERR_PNF:
//		err="The specified path was not found";
		break;
	case SE_ERR_SHARE:
		err="A sharing violation occurred";
		break;
	default:
		err="Some kind of unknown to Microsoft error happened ^_^";
		break;
	}
	char* error=new char[err.GetLength()+1];
	strcpy_s(error,err.GetLength()+1,err.GetBuffer(err.GetLength()));
	return error;
}


doc_class* FindItem(int id, doc_classes& vec)
{
	for(int i=0;i<vec.RealCount;i++)
		if(vec[i]->id==id)
			return vec[i];
	return NULL;
}
int InitPlugin(char* data, int obj_id, HANDLE ExitEvent)
{
	DieEvent=ExitEvent;
	//doc_class* doc;
	doc_class* doc=new(doc_class);
	doc->id=obj_id;
	////parsing
	MenuXml.Parse(data,"item");

	xml* main=MenuXml.GetItemOnlyChild(MenuXml.MainElement,"item",1);
	xml* current=MenuXml.GetItemOnlyChild(main,"way",1);
	doc->SetWay(current->subtext);
	current=MenuXml.GetItemOnlyChild(main,"app",1);
	doc->SetApp(current->subtext);
	current=MenuXml.GetItemOnlyChild(main,"title",1);
	doc->SetTitle(current->subtext);
	current=MenuXml.GetItemOnlyChild(main,"action",1);
	doc->SetAction(current->subtext);
	current=MenuXml.GetItemOnlyChild(main,"launch",1);
	doc->SetLaunch(current->subtext);
	current=MenuXml.GetItemOnlyChild(main,"dir",1);
	doc->SetDir(current->subtext);
	current=MenuXml.GetItemOnlyChild(main,"ReallyCreateMenu");
	if(current!=NULL)
		if(IsTrue(current->subtext))
			doc->ReallyCreateMenu=1;
	///parsing
	Items.push_back(doc);
	return 1;
}

int ClickPluginMenu(int obj_id)
{
	int my_id=floor((float)obj_id/1000);

	//CString msg;
	//msg.Format("message from item %d",menu_id);
	//MessageBox(NULL,msg,"",MB_OK);
	doc_class* doc=FindItem(my_id,Items);
	int z=(int)ShellExecute(NULL,doc->action,doc->app,doc->way,doc->dir,doc->launch);
	if(z<32)//error
	{
		//char* error=GetExecuteError(z);
		char* error=GetTextError(z);
		MessageBox(NULL,error,"Tray Manager: Error",MB_OK);
		delete(error);
	}
	return 1;
}

int CreatePluginMenu(HMENU parent,int obj_id)
{
	int MenuNum=obj_id*1000+1;
	doc_class* doc=FindItem(obj_id,Items);
	AppendMenu(parent,MF_STRING,MenuNum,doc->title);// append menu
	doc->hMenu=parent;
	//MessageBox(0,"make menu!","",MB_OK);
	return 1;
}
int RefreshPluginMenu(int obj_id)
{
	doc_class* doc=FindItem(obj_id,Items);
	if(doc->ReallyCreateMenu==1)
	{
		HBITMAP hBitmapChecked = NULL;
		char* way=GetApplicationDir();
		CString pic;
		pic.Append(way);
		delete(way);
		pic.Append("\\pic\\application");
		SetCurrentDirectory(pic);
		if(FindProc(doc->app))
			pic="run.bmp";
		else 
			pic="stop.bmp";
		if(doc->pic!=NULL)DeleteObject(doc->pic);
		doc->pic = (HBITMAP)LoadImage(NULL,pic, IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE  | LR_SHARED);
		pic.ReleaseBuffer();
		SetMenuItemBitmaps(doc->hMenu, obj_id*1000+1, MF_BYCOMMAND, doc->pic, doc->pic);
		EnableMenuItem(doc->hMenu,  obj_id*1000+1,(MF_BYCOMMAND+MF_GRAYED));
		EnableMenuItem(doc->hMenu,  obj_id*1000+1,(MF_BYCOMMAND+MF_ENABLED));
	}
	return 1;
}

//HANDLE* FunctPtr;
/*
void ShowError(CString err)
{
	MessageBox(NULL,err,"Error",MB_OK);			
	exit(2);
}*/