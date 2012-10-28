#include "stdafx.h"
#include "func.h"
#include "class.h"
#include <windows.h>

typedef mvector <autoload_class*> autoload_classes;
autoload_classes Items;
AllXml MenuXml;
HANDLE DieEvent;

int InitPlugin(char* data, int obj_id,HANDLE DieEvent);
int CreatePluginMenu(HMENU parent,int obj_id);
int RefreshPluginMenu(int obj_id);
int ClickPluginMenu(int obj_id);


int InitPlugin(char* data, int obj_id, HANDLE ExitEvent)
{
	DieEvent=ExitEvent;
	MenuXml.Parse(data,"item");
	xml* child;
	for(int i=0;i<MenuXml.vec.RealCount;i++)
	{
		child=MenuXml.vec[i];
		if(child->name!=NULL)
		{
			if(!_stricmp(child->name,"CallEvent"))
			{
				child=MenuXml.GetItemOnlyChild(child,"Name",1);
				HANDLE h=OpenEvent(EVENT_MODIFY_STATE,0,child->subtext);
				if(h==NULL)
				{
					CString err;
					err="Handle for ";
					err.Append(child->subtext);
					err.Append(" could not be opened!");
					ShowError(err);
				}
				else
					SetEvent(h);
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
	return 1;
}
