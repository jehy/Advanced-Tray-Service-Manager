#include "stdafx.h"
#include "EventWait.h"
#include "funcs.h"
extern MenuObjectsVec MenuObjects;
extern ClickEventsStore ClickEvents;
extern ExitClass ExitProgram;
void EventWait (LPVOID lpParam)
{
	HANDLE* hevents=new HANDLE[ClickEvents.Store.RealCount+1];
	for(int i=1;i<=ClickEvents.Store.RealCount;i++)
		hevents[i]=ClickEvents.Store.handles[i-1]->hEvent;
	hevents[0]=ExitProgram.ExitEvent;
	DWORD ComingEvent;
	bool NoExit=1;
	while(NoExit)
	{
		ComingEvent=WaitForMultipleObjects(ClickEvents.Store.RealCount+1,hevents,FALSE,INFINITE);
		switch (ComingEvent)
		{
		case WAIT_FAILED:
				ShowError("Wrong handle!");
				break;
		case WAIT_OBJECT_0:
				NoExit=0;
				break;
		default:
			int HandleNum=ComingEvent-WAIT_OBJECT_0;
			ResetEvent(hevents[HandleNum]);
//			int menu_id;
			if(ClickEvents.Store[HandleNum-1]->obj_id==-1)
				ShowError("Target object for event not set!");
			//if(ClickEvents.Store[HandleNum]->AddToId==0)
			//	menu_id=ClickEvents.Store[HandleNum]->obj_id;
			//else
			//	menu_id=ClickEvents.Store[HandleNum-1]->obj_id*1000+ClickEvents.Store[HandleNum-1]->AddToId+1;
			//MenuObjects[ClickEvents.Store[HandleNum-1]->obj_id-1]->library->ClickPluginMenu(menu_id);
			ClickPluginMenu((LPVOID)(ClickEvents.Store[HandleNum-1]->obj_id*1000+ClickEvents.Store[HandleNum-1]->AddToId+1));
			break;
		}
	}
	ExitProgram.ClickEventExit=1;
	
}