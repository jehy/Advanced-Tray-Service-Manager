#include "stdafx.h"
#include "func.h"
#include "class.h"
#include <windows.h>

typedef mvector <joystick_class*> joystick_classes;
joystick_classes Items;
AllXml MenuXml;
HANDLE DieEvent;
joystick_class* FindItem(int id, joystick_classes& vec)
{
	for(int i=0;i<vec.RealCount;i++)
		if(vec[i]->id==id)
			return vec[i];
	return NULL;
}
int InitPlugin(char* data, int obj_id, HANDLE ExitEvent)
{
	DieEvent=ExitEvent;
	joystick_class* serv=new(joystick_class);
	Items.push_back(serv);
	serv->id=obj_id;
	////parsing
	MenuXml.Parse(data,"item");
	xml* main=MenuXml.GetItemOnlyChild(MenuXml.MainElement,"item",1);
	xml* current=MenuXml.GetItemOnlyChild(main,"Debug",1);
	if(current!=NULL)
		if(IsTrue(current->subtext))
			serv->Debug=1;
	current=MenuXml.GetItemOnlyChild(main,"DeviceId",1);
	serv->DeviceId=atoi(current->subtext);
	current=MenuXml.GetItemOnlyChild(main,"SleepAfterClick",1);
	serv->SleepAfterClick=atoi(current->subtext);

	
	for(int z=0;z<MenuXml.vec.size();z++)//For calling plugins
	{
		current=MenuXml.vec[z];
		if(current!=NULL)
		{
			if((current->name!=NULL)&&(!_stricmp(current->name,"CallEvent")))
			{
				xml* child2=MenuXml.GetItemOnlyChild(current,"Name",1);
				HANDLE hevent=CreateEvent(NULL,TRUE,FALSE,child2->subtext);
				serv->WaitingEventsHandles.push_back(hevent);
			}
		}
	}
	return 1;
}

int ClickPluginMenu(int obj_id)
{
	return 1;
}

int CreatePluginMenu(HMENU parent,int obj_id)
{
	return 1;
}
int RefreshPluginMenu(int obj_id)
{
	joystick_class* serv=FindItem(obj_id,Items);
	JOYINFOEX jiInfo;
	int z=joyGetPosEx(serv->DeviceId, &jiInfo);
	char* err=NULL;
	switch (z)
	{
	case(JOYERR_NOERROR):
		{
			/*printf("x=%d,y=%d\n",jiInfo.dwYpos,jiInfo.dwXpos);
			if(jiInfo.dwButtons&JOY_BUTTON1)
				printf("1 pushed\n");
			if(jiInfo.dwButtons&JOY_BUTTON2)
				printf("2 pushed\n");
			if(jiInfo.dwButtons&JOY_BUTTON3)
				printf("3 pushed\n");
			if(jiInfo.dwButtons&JOY_BUTTON4)
				printf("4 pushed\n");
			if(jiInfo.dwButtons&JOY_BUTTON5)
				printf("5 pushed\n");
			 if(jiInfo.dwButtons&JOY_BUTTON6)
				printf("6 pushed\n");
			 if(jiInfo.dwButtons&JOY_BUTTON7)
				printf("7 pushed\n");
			 if(jiInfo.dwButtons&JOY_BUTTON8)
				printf("8 pushed\n");*/
			if(jiInfo.dwButtons)/*||(jiInfo.dwYpos!=32511)||(jiInfo.dwXpos!=32511)*/
			{
				//Click(serv->FormCaption,serv->ObjectCaption);
				for(int i=0;i<serv->WaitingEventsHandles.size();i++)
					SetEvent(serv->WaitingEventsHandles[i]);
				Sleep(serv->SleepAfterClick);//avoid secondary pushing
			}
		}
		break;
		case(MMSYSERR_NODRIVER):
			err=("The joystick driver is not present. \n");
			break;
		case(MMSYSERR_INVALPARAM):
			err=("An invalid parameter was passed.\nWindows 95/98/Me: The specified joystick identifier is invalid.\n");
			break;
		case(MMSYSERR_BADDEVICEID):
			err=("The specified joystick identifier is invalid.\n");
			break;
		case(JOYERR_UNPLUGGED):
			err=("The specified joystick is not connected to the system.\n");
			break;
		case(JOYERR_PARMS):
			err=("The specified joystick identifier is invalid.\n");
			break;
	}

	if((err!=NULL)&&(serv->Debug))
		ShowError(err);

	return 1;
}
