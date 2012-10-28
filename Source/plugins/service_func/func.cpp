#include "stdafx.h"
#include "func.h"
#include "class.h"
#include <windows.h>
//#include <stdio.h>

typedef mvector <service_class*> service_classes;
service_classes Items;
AllXml MenuXml;
HANDLE DieEvent;

int InitPlugin(char* data, int obj_id,HANDLE DieEvent);
int CreatePluginMenu(HMENU parent,int obj_id);
int RefreshPluginMenu(int obj_id);
int ClickPluginMenu(int obj_id);



service_class* FindItem(int id, service_classes& vec)
{
	for(int i=0;i<vec.RealCount;i++)
		if(vec[i]->id==id)
			return vec[i];
	return NULL;
}



int MyStartService(char* name,const char** Args,int ArgNum) 
{ 
    SERVICE_STATUS_PROCESS ssStatus; 
    DWORD dwOldCheckPoint; 
    DWORD dwStartTickCount;
    DWORD dwWaitTime;
    DWORD dwBytesNeeded;
	SC_HANDLE schSCManager = OpenSCManager( 
    NULL,                    // local machine 
    NULL,                    // ServicesActive database 
    SERVICE_QUERY_STATUS);  // 
    SC_HANDLE schService = OpenService(schSCManager,name,SERVICE_ALL_ACCESS); 
    if (schService == NULL) 
    { 
        return 0; 
    }
    if (!StartService(
            schService,  // handle to service 
            ArgNum,           // number of arguments 
            Args))      // no arguments 
	{
		char* err=GetTextLastError();
		MessageBox(NULL,err,"Error",MB_OK);
		delete(err);
		return 0;
	} 
 
    else 
		;//printf("Service start pending.\n"); 
    // Check the status until the service is no longer start pending. 
    if (!QueryServiceStatusEx( 
            schService,             // handle to service 
            SC_STATUS_PROCESS_INFO, // info level
            (LPBYTE)&ssStatus,              // address of structure
            sizeof(SERVICE_STATUS_PROCESS), // size of structure
            &dwBytesNeeded ) )              // if buffer too small
	{
		
		MessageBox(NULL,"QueryServiceStatusEx failed!","Error",MB_OK);
        return 0; 
	}
    // Save the tick count and initial checkpoint.
    dwStartTickCount = GetTickCount();
    dwOldCheckPoint = ssStatus.dwCheckPoint;
    while (ssStatus.dwCurrentState == SERVICE_START_PENDING) 
    { 
        // Do not wait longer than the wait hint. A good interval is 
        // one tenth the wait hint, but no less than 1 second and no 
        // more than 10 seconds. 
        dwWaitTime = ssStatus.dwWaitHint / 10;
        if(dwWaitTime<1000)dwWaitTime=1000;
        else if (dwWaitTime>10000)dwWaitTime=10000;
        Sleep(dwWaitTime);
        // Check the status again. 
		if (!QueryServiceStatusEx( 
            schService,             // handle to service 
            SC_STATUS_PROCESS_INFO, // info level
            (LPBYTE)&ssStatus,              // address of structure
            sizeof(SERVICE_STATUS_PROCESS), // size of structure
            &dwBytesNeeded))              // if buffer too small
            break; 
        if ( ssStatus.dwCheckPoint > dwOldCheckPoint )
        {
            // The service is making progress.
            dwStartTickCount = GetTickCount();
            dwOldCheckPoint = ssStatus.dwCheckPoint;
        }
        else
        {
            if(GetTickCount()-dwStartTickCount > ssStatus.dwWaitHint)
            {
                // No progress made within the wait hint
                break;
            }
        }
    } 
    CloseServiceHandle(schService); 
    if (ssStatus.dwCurrentState==SERVICE_RUNNING) 
    {
        //printf("StartService SUCCESS.\n"); 
        return 1;
    }
    else 
    { 
        /*printf("\nService not started. \n");
        printf("  Current State: %d\n", ssStatus.dwCurrentState); 
        printf("  Exit Code: %d\n", ssStatus.dwWin32ExitCode); 
        printf("  Service Specific Exit Code: %d\n", 
            ssStatus.dwServiceSpecificExitCode); 
        printf("  Check Point: %d\n", ssStatus.dwCheckPoint); 
        printf("  Wait Hint: %d\n", ssStatus.dwWaitHint); */
        return 0;
    } 
}


int StopDependent(SC_HANDLE hService,SC_HANDLE hSCM)
{
SERVICE_STATUS ss;
DWORD dwStartTime = GetTickCount();
//DWORD dwBytesNeeded;
DWORD dwTimeout=2000;
DWORD i;
DWORD dwBytesNeeded;
DWORD dwCount;
LPENUM_SERVICE_STATUS   lpDependencies = NULL;
ENUM_SERVICE_STATUS     ess;
SC_HANDLE               hDepService;
// Pass a zero-length buffer to get the required buffer size
if (EnumDependentServices(hService,SERVICE_ACTIVE,lpDependencies,0,&dwBytesNeeded,&dwCount )) 
{
	// If the Enum call succeeds, then there are no dependent
	// services so do nothing
	return 1;
} 
else 
{
 if (GetLastError()!= ERROR_MORE_DATA)
    return GetLastError(); // Unexpected error
 // Allocate a buffer for the dependencies
 lpDependencies = (LPENUM_SERVICE_STATUS) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwBytesNeeded );
 if ( !lpDependencies )
    return GetLastError();
 __try {
    // Enumerate the dependencies
    if (!EnumDependentServices(hService,SERVICE_ACTIVE,lpDependencies, dwBytesNeeded,&dwBytesNeeded,&dwCount))
       return GetLastError();

    for (i=0;i<dwCount;i++) 
    {
       ess=*(lpDependencies + i);
       // Open the service
       hDepService = OpenService( hSCM, ess.lpServiceName,SERVICE_STOP|SERVICE_QUERY_STATUS);
       if ( !hDepService )
          return GetLastError();
       __try {
           // Send a stop code
          if (!ControlService( hDepService,SERVICE_CONTROL_STOP,&ss))
             return GetLastError();
          // Wait for the service to stop
          while ( ss.dwCurrentState != SERVICE_STOPPED ) 
          {
             Sleep( ss.dwWaitHint );
             if ( !QueryServiceStatusEx(hDepService,SC_STATUS_PROCESS_INFO,(LPBYTE)&ss,sizeof(SERVICE_STATUS_PROCESS),&dwBytesNeeded))
                return GetLastError();
             if (ss.dwCurrentState==SERVICE_STOPPED )
                break;
             if (GetTickCount()-dwStartTime>dwTimeout )
                return ERROR_TIMEOUT;
          }
       } 
       __finally 
       {
          // Always release the service handle
          CloseServiceHandle( hDepService );
	   }
	}
 }
__finally 
         {
            // Always free the enumeration buffer
            HeapFree( GetProcessHeap(), 0, lpDependencies );
         }
}
return 0;//not needed
}
//}

int MyControlService(char* name,DWORD code) 
{ 
    DWORD dwBytesNeeded;
	int waitfor=0;
	if(code==SERVICE_CONTROL_STOP)waitfor=SERVICE_STOPPED;
	else if(code==SERVICE_CONTROL_PAUSE)waitfor=SERVICE_PAUSED;
    SERVICE_STATUS ssStatus; 
    SERVICE_STATUS_PROCESS ssStatus2;
	SC_HANDLE schSCManager = OpenSCManager( 
    NULL,                    // local machine 
    NULL,                    // ServicesActive database 
    SC_MANAGER_ALL_ACCESS);  // 
    SC_HANDLE schService = OpenService(schSCManager,name,SERVICE_ALL_ACCESS); 
    if (schService == NULL) 
    { 
		MessageBox(NULL,"Service could not be opened!","Error",MB_OK);
        return 0; 
    }
	int wait=0;
    if(!ControlService( 
		schService,   // handle to service 
        code,   // control value to send 
        &ssStatus) )  // address of status info 
    {
        //printf("ControlService failed (%d)\n", GetLastError());
		/*
		char* err=GetTextLastError();
		CString error="ControlService failed: ";
		error.Append(err);
		MessageBox(NULL,error,"Error",MB_OK);
		delete(err);
		*/
		int z=StopDependent(schService,schSCManager);
		if(z!=1)
		{
			char* err=GetTextLastError();
			CString error="Stop dependent failed: ";
			error.Append(err);
			MessageBox(NULL,error,"Error",MB_OK);
			delete(err);
		}
		else
		{
			if(!ControlService( 
			schService,   // handle to service 
			code,   // control value to send 
			&ssStatus) )  // address of status info 
			{
			//printf("ControlService failed (%d)\n", GetLastError());
				char* err=GetTextLastError();
				CString error="ControlService after stopping dependent failed: ";
				error.Append(err);
				MessageBox(NULL,error,"Error",MB_OK);
				delete(err);
				//MessageBox(NULL,"ControlService failed!","Error",MB_OK);
				return 0;
			}
		}
    }
	else do
	{
		if (!QueryServiceStatusEx( 
            schService,             // handle to service 
            SC_STATUS_PROCESS_INFO, // info level
            (LPBYTE)&ssStatus2,              // address of structure
            sizeof(SERVICE_STATUS_PROCESS), // size of structure
            &dwBytesNeeded))              // if buffer too small
            break; 
		if(wait>10)break;
		wait++;
		Sleep(1000);
	} while(ssStatus2.dwCurrentState!= waitfor);
	if(ssStatus2.dwCurrentState==waitfor)return 1;
	else return 0;
}



int InitPlugin(char* data, int obj_id, HANDLE ExitEvent)
{
	
	DieEvent=ExitEvent;
	//CString mess;
	//mess.Format("I'm told to make an object with text '%s' and id %d",data,obj_id);
	service_class* serv=new(service_class);
	serv->id=obj_id;
	////parsing
	MenuXml.Parse(data,"item");
	xml* main=MenuXml.GetItemOnlyChild(MenuXml.MainElement,"item",1);
	xml* current=MenuXml.GetItemOnlyChild(main,"name",1);
	serv->SetName(current->subtext);
	current=MenuXml.GetItemOnlyChild(main,"parameters");
	if(current!=NULL)
	{
		int z=0;//counting number of arguments;
		for(int i=0;i<MenuXml.vec.RealCount;i++)
			if(MenuXml.vec[i]->parent==current)
				z++;	
		if(z!=0)
		{
			serv->Args=new char*[z];
			serv->ArgNum=z;
			z=0;
			size_t k;
			for(int i=0;i<MenuXml.vec.RealCount;i++)
			{
				if(MenuXml.vec[i]->parent==current)
				{
					k=strlen(MenuXml.vec[i]->subtext)+1;
					serv->Args[z]=new char[k];
					strcpy_s(serv->Args[z],k,MenuXml.vec[i]->subtext);
					z++;
				}
			}
		}
	}
	///parsing
	Items.push_back(serv);
	return 1;
}

int ClickPluginMenu(int obj_id)
{
	int my_id=floor((float)obj_id/1000);
	int sub_id=obj_id-my_id*1000;
	service_class* serv=FindItem(my_id,Items);
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
	case 4:
		z=MyControlService(serv->name,SERVICE_CONTROL_STOP);
		if(z)//MessageBox(NULL,"Service could not be stopped!","Error",MB_ICONWARNING);
		//else
		{
			//Sleep(100);
			z=MyStartService(serv->name,(const char**)serv->Args,serv->ArgNum);
			if(!z)MessageBox(NULL,"Service could not be started!","Error",MB_ICONWARNING);
		}
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
	//current=MenuXml.GetItemOnlyChild(main,"name");
	xml* current=MenuXml.GetItemOnlyChild(main,"title",1);
	service_class* serv=FindItem(obj_id,Items);

	HMENU NewMenu=CreatePopupMenu();
	AppendMenu(parent,MF_POPUP+MF_STRING,(UINT_PTR)NewMenu,current->subtext);
	serv->hMenu=parent;
	serv->number=GetMenuItemCount(parent)-1;
	AppendMenu(NewMenu,MF_STRING,MenuNum+add,"start");// append menu
	add++;
	AppendMenu(NewMenu,MF_STRING,MenuNum+add,"stop");// append menu
	add++;
	AppendMenu(NewMenu,MF_STRING,MenuNum+add,"pause");// append menu
	add++;
	AppendMenu(NewMenu,MF_STRING,MenuNum+add,"restart");// append menu
	add++;
	//MessageBox(0,"make menu!","",MB_OK);
	return 1;
}
int RefreshPluginMenu(int obj_id)
{
	
    SERVICE_STATUS_PROCESS ssStatus; 
//    DWORD dwOldCheckPoint; 
//    DWORD dwStartTickCount;
//    DWORD dwWaitTime;
    DWORD dwBytesNeeded;

	//ssStatus=new BYTE[sizeof(SERVICE_STATUS_PROCESS)];
	SC_HANDLE schSCManager = OpenSCManager( 
    NULL,                    // local machine 
    NULL,                    // ServicesActive database 
    SERVICE_QUERY_STATUS);  // 
 
if (NULL == schSCManager) 
    return 0;
	service_class* serv=FindItem(obj_id,Items);
    SC_HANDLE schService = OpenService(schSCManager,serv->name,SERVICE_QUERY_STATUS); 
    if (schService == NULL) 
		return 0; 
	if (!QueryServiceStatusEx(schService,// handle to service 
            SC_STATUS_PROCESS_INFO, // info level
            (LPBYTE)&ssStatus,              // address of structure
            sizeof(SERVICE_STATUS_PROCESS), // size of structure
            &dwBytesNeeded ) )              // if buffer too small
    {
        return 0; 
    }
	CloseServiceHandle(schService);
	 CloseServiceHandle(schSCManager);
    // Save the tick count and initial checkpoint.
	//    dwStartTickCount = GetTickCount();
	//    dwOldCheckPoint = ssStatus.dwCheckPoint;
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
	EnableMenuItem(serv->hMenu, serv->number,(MF_BYPOSITION+MF_GRAYED));
	EnableMenuItem(serv->hMenu, serv->number,(MF_BYPOSITION+MF_ENABLED));
	return 1;
}

//HANDLE* FunctPtr;
/*
void ShowError(CString err)
{
	MessageBox(NULL,err,"Error",MB_OK);			
	exit(2);
}*/