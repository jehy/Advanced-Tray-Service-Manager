#include "StdAfx.h"
#include "CheckThread.h"
#include "EventWait.h"
extern ExitClass ExitProgram;
//extern HWND hwnd; 
//extern HMENU hmenu; 
CheckThread::CheckThread(int ThreadMethod)
{
	method=ThreadMethod;
	return;
}

CheckThread::~CheckThread(void)
{
	return;
}

int CheckThread::Run(void)
{
	DWORD z;
	for(int i=0;i<ObjectStore.RealCount;i++)
	{
		if(ObjectStore[i]->interval!=0)
			CreateThread(
			NULL,              // default security attributes
			0,                 // use default stack size  
			(LPTHREAD_START_ROUTINE)Run2,        // thread function 
			ObjectStore[i],             // argument to thread function 
			0,                 // use default creation flags 
			&z);   // returns the thread identifier 
	}


	CreateThread(
			NULL,              // default security attributes
			0,                 // use default stack size  
			(LPTHREAD_START_ROUTINE)EventWait,        // thread function 
			&ClickEvents,             // argument to thread function 
			0,                 // use default creation flags 
			&z);  
	return 1;
}


int CheckThread::Stop(void)
{
	return 1;
}

int Run2(LPVOID lpParam)
{
	MenuObj* Obj=(MenuObj*) lpParam;
	Obj->Shutdown=0;
	while(!ExitProgram.Shutdown)
	{
			Obj->library->RefreshPluginMenu(Obj->id);
			Sleep(Obj->interval);
	}
	Obj->Shutdown=1;
return 1;
}
