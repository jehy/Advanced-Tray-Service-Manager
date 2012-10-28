// atsm++2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ctray.h"
#include "main.h"
#include "funcs.h"
extern MenuObjectsVec MenuObjects;
extern ClickEventsStore ClickEvents;
extern LibStore Libs;
ExitClass ExitProgram;
char szClassName[ ] = "Tiny class";
CTray* OurTray;

HWND hwnd;

void ExitWatch(LPVOID lpParam)
{
	int WaitForTermination=10000;
	int CheckPeriod=100;
	int Waited=0;
	DWORD ComingEvent=WaitForSingleObject(ExitProgram.ExitEvent,INFINITE);
	ExitProgram.Shutdown=1;
	if(ComingEvent==WAIT_OBJECT_0)
		while(1)
		{
			bool exit=1;
			for(int i=0;i<MenuObjects.size();i++)
				if(!MenuObjects[i]->Shutdown)
					exit=0;
			if(!ExitProgram.ClickEventExit)
				exit=0;
			if((exit)||(Waited>WaitForTermination))
			{
				delete(OurTray);
				for(int i=0;i<MenuObjects.size();i++)
					delete(MenuObjects[i]);
				PostMessage(hwnd, WM_CLOSE, 0, 0);
				return;
			}
			else 
			{
				Waited+=CheckPeriod;
				Sleep(CheckPeriod);
			}
		}
}


int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)
{
	DWORD z;
	CreateThread(
			NULL,              // default security attributes
			0,                 // use default stack size  
			(LPTHREAD_START_ROUTINE)ExitWatch,        // thread function 
			NULL,             // argument to thread function 
			0,                 // use default creation flags 
			&z); 
    /* The Window structure */
	MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    // =NULL;// CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon=wincl.hIconSm=NULL;
	wincl.hCursor=NULL;
	wincl.style=NULL;
	wincl.lpszMenuName=NULL;
	wincl.hbrBackground=NULL;
	wincl.hInstance=NULL;// LoadIcon (NULL, IDI_APPLICATION);
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindow (
          // 0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Tray_Manager",         /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           230,                 /* The programs width */
           200,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );
	CString path;
	char* buffer=GetApplicationDir();
	path.Append(buffer);
	path.Append("settings.txt");
	//delete(buffer);

	buffer=file_get_contents(path.GetBuffer());
	AllXml* xmlvec=new(AllXml);
	xmlvec->Parse(buffer,"xml");
	delete(buffer);
	bool ShowInTray=1;
	xml* main=xmlvec->GetItemOnlyChild(xmlvec->MainElement,"xml",1);
	xml* child=xmlvec->GetItemOnlyChild(main,"Global");
	if(child!=NULL)
	{
		child=xmlvec->GetItemOnlyChild(child,"ShowInTray");
		if(child!=NULL)
			ShowInTray=IsTrue(child->subtext);
	}
	OurTray=new CTray(hwnd);

	if(ShowInTray)
		OurTray->SetIcon("icon", 1);
	main=xmlvec->GetItemOnlyChild(main,"menu",1);
	CreateMyMenu(xmlvec,OurTray->hMenu,main);
	SetMenu(hwnd,OurTray->hMenu);
	delete(xmlvec);
	CheckThread* Manager=new CheckThread();
	Manager->ObjectStore=MenuObjects;
	Manager->ClickEvents=ClickEvents;
	Manager->Run();
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*if(LOWORD(wParam)>1000)
	{
	MessageBox(NULL,"","",MB_OK);
	}
	else*/ 
		if((message==WM_COMMAND)&&(LOWORD(wParam)>1000))
	{
		DWORD z;
		CreateThread(
			NULL,              // default security attributes
			0,                 // use default stack size  
			(LPTHREAD_START_ROUTINE)ClickPluginMenu,        // thread function 
			(LPVOID)wParam,             // argument to thread function 
			0,                 // use default creation flags 
			&z);   // returns the thread identifier 
	}
	else switch (message)
    {
//		case WM_CREATE:{       
//            TRAY_Init(hwnd); // Create tray icon and popup menu              
//		}break;
    	//case WM_SIZE:
    	     //OnSizeTray(wParam); // Minimize/Restore to/from tray
        break;            
    	case WM_NOTIFYICONTRAY:
    	     OurTray->OnNotifyTray(lParam); // Manages message from tray
        return TRUE;
		break;
    	case WM_COMMAND:
	    { 
          // Manage popup menu message (before switch statement)
          if (OurTray->OnCommandTrayMenu(wParam)) break;
       
        case WM_DESTROY:
			PostQuitMessage (0);       // send a WM_QUIT to the message queue
            break;
        default:                      // for messages that we don't deal with
            return DefWindowProc (hwnd, message, wParam, lParam);
		}
		}
    return 0;
}

