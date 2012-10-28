#include <stdafx.h>
// tray.cpp
//
// Minimize window in Tray with popup menu with icons.  
// This code is free, you may use it without any warranty or too much expectations...
// If you find something wrong then post your corrections or suggestions on the web.
// If you think to do better than me simply you do not use this code but send to me the your :)
//
// 2003/2004 by Massimiliano Miani (imianz@tiscalinet.it)

#include "ctray.h"

//DWORD CheckMenuItem(UINT IDItem, BOOL Checked); //Check/uncheck an item in popup menu
//BOOL  IsItemChecked(UINT IDItem);               //Is popup item checked?

//POPUP MENU
//HMENU hMenu;                                    // menu handle
//HWND  hwnd;                                     // main window handle
//TRAY
//bool  bTray;                                    // tray state (is window minimized in tray?)

extern ExitClass ExitProgram;

/************
 ************
 ** PUBLIC **
 ************
 ************/
CTray::CTray(HWND hWnd)
{
	this->hwnd=hWnd;
    this->hMenu=CreatePopupMenu();
    this->hMenu2=CreatePopupMenu();
    CreateItemList(this->hMenu2); 
    LoadAppIcon();
} 

CTray::~CTray()
{
    //Destroy popup menu
	DestroyMenu(this->hMenu);
	//Ensure to remove tray icon
    SetIcon("", 0);
	//delete(this);
}

BOOL CTray::OnCommandTrayMenu(WPARAM wParam)
{
 switch(LOWORD(wParam))
 {
    //POPUP MENU ******************************************************//
    /*case IDM_ONTOP: //ALWAYS ON TOP
    {   
        HWND HWND_ORDER;
        BOOL Checked;
        
        //If menu item is checked put window on top
		if (IsItemChecked(LOWORD(wParam))){ 
		  HWND_ORDER = HWND_NOTOPMOST;  // 
		  Checked=false;
		}else{
	      HWND_ORDER = HWND_TOPMOST;
	      Checked=true;
		}
		
		CheckMenuItem(LOWORD(wParam),Checked);
		SetWindowPos(hwnd, HWND_ORDER, 0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		
	}return TRUE;		      
	//POPUP MENU
	case IDM_MINIMIZE:{ //minimize/restore window
 
		//NOTE: SW_SHOWMINIMIZED and SW_RESTORE cause WM_SIZE event
        //(see also OnSizeTray())
        if (!bTray){ 
			ShowWindow(hwnd, SW_SHOWMINIMIZED);//minimize window in tray
     				
		}else{       			
			ShowWindow(hwnd, SW_RESTORE);//restore window 
        }	
	}return TRUE;
	//POPUP MENU 
	case IDM_ABOUT:{
        MessageBox(hwnd,APP_ABOUT,"Info",MB_ICONINFORMATION);
	}return TRUE;	
	//POPUP MENU */
	case IDM_CLOSE: //CHIUDE L'APPLICAZIONE
        //PostMessage(hwnd, WM_CLOSE, 0, 0);
		SetEvent(ExitProgram.ExitEvent);
		break;
	case IDM_ABOUT: //CHIUDE L'APPLICAZIONE
		MessageBox(hwnd,"Godlike programming\n\n(c) by Jehy 2006-2008\n\nIf interested, visit http://jehy.ru","About",MB_OK);
		break;
 }
 return TRUE;
	
}//end switch(LOWORD(wParam))	
  
//return FALSE; //No event match
//}
void CTray::OnNotifyTray(LPARAM lParam)
{
 // Right click, show the menu
 if(lParam == WM_LBUTTONDOWN) 
 {
	// load menu
	POINT pt;// point structure
	GetCursorPos(&pt);// get the cursors position
	SetForegroundWindow(hwnd);// set the foreground window
	TrackPopupMenu(hMenu,TPM_RIGHTALIGN,pt.x,pt.y,0,this->hwnd,NULL);// track the popup			              
 }else{
	// Left click, button effect :)
    if(lParam ==WM_RBUTTONDOWN )
	{
        //SetIcon("ingrandisci", 2);//imposta la nuova icona
		POINT pt;// point structure
		GetCursorPos(&pt);// get the cursors position
		SetForegroundWindow(hwnd);// set the foreground window
		TrackPopupMenu(hMenu2,TPM_RIGHTALIGN,pt.x,pt.y,0,this->hwnd,NULL);// track 
	}
	else{	
		if(lParam == WM_RBUTTONUP)
	{
        //SetIcon("ingrandisci", 3);//imposta la nuova icona
	}}    			
 }
 //PostMessage(hwnd,WM_NULL,0,0);// post a null message
}

void CTray::TRAY_Menu_Show()
{			
	POINT pt;// point structure
	GetCursorPos(&pt);// get the cursors position
	//SetForegroundWindow(this->hwnd);// set the foreground window
	TrackPopupMenu(this->hMenu,TPM_RIGHTALIGN,pt.x,pt.y,0,this->hwnd,NULL);// track the popup
	PostMessage(this->hwnd,WM_NULL,0,0);// post a null message	    
}

//Set bitmaps for popup menu items
void CTray::SetBitmaps(HMENU hMenu)
{    
    //Checked item bitmap
   // HBITMAP hBitmapChecked = LoadBitmap((HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),MAKEINTRESOURCE(IDB_MENU_CHECK));
//    SetMenuItemBitmaps(hMenu, IDM_ONTOP, MF_BYCOMMAND, NULL/*hBitmapUnchecked*/,hBitmapChecked); 
    //Close bitmap
    //hBitmapChecked = LoadBitmap((HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE), 
    //                                        MAKEINTRESOURCE(IDB_MENU_CLOSE));
/////////////////////////
	//LPCTSTR szFilename;
	//ASSERT(szFilename);
	//DeleteObject();

	HBITMAP hBitmapChecked = NULL;
	char* way=GetApplicationDir();
	CString dir;
	dir.Append(way);
	delete(way);
	dir.Append("\\");
	dir.Append("pic");
	SetCurrentDirectory(dir);
	hBitmapChecked = (HBITMAP)LoadImage(NULL, "menu_close.bmp", IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);

/////////////////////////
	//menu_close.bmp
    SetMenuItemBitmaps(hMenu, IDM_CLOSE, MF_BYCOMMAND, hBitmapChecked, NULL);
    
    //About bitmap  
    //hBitmapChecked = LoadBitmap((HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),MAKEINTRESOURCE(IDB_MENU_ABOUT));
//    SetMenuItemBitmaps(hMenu, IDM_ABOUT, MF_BYCOMMAND, hBitmapChecked, NULL);    
}
/**************************************************************************************************/
/**************************************************************************************************/
//Create menu items
void CTray::CreateItemList(HMENU hMenu)
{
	int ret=0; // buffer for errors
 		
	// CREATE POPUP MENU ( on the fly )
	//hMenu = CreatePopupMenu(); // create the popupmenu (See BOOL TRAY_Init()...)
//	AppendMenu(hMenu,MF_STRING ,IDM_ONTOP,IDM_TEXT_ONTOP);// append menu    
//	AppendMenu(hMenu,MF_STRING ,IDM_MINIMIZE,IDM_TEXT_MINIMIZE);// append menu
//	AppendMenu(hMenu,MF_SEPARATOR,0,0);// append menu
	AppendMenu(hMenu,MF_STRING,IDM_CLOSE,"Close");// append menu 
	AppendMenu(hMenu,MF_STRING,IDM_ABOUT,"About");// append menu 
//	AppendMenu(hMenu,MF_SEPARATOR,0,0);// append menu
//	AppendMenu(hMenu,MF_STRING,IDM_ABOUT,IDM_TEXT_ABOUT);// append menu  
	
    SetBitmaps(hMenu); 
}
/**************************************************************************************************/
/**************************************************************************************************/
//Load app. icon
BOOL CTray::LoadAppIcon()
{
    // Load icon from resource
	char* way=GetApplicationDir();
	CString dir;
	dir.Append(way);
//	dir.Append("\\");
	dir.Append("pic");
	SetCurrentDirectory(dir);
	this->hIcon=(HICON)LoadImage(NULL, "icon.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
	//this->hIcon = (HICON)LoadImage(NULL, "app.ico", IMAGE_ICON, 0, 0,LR_LOADFROMFILE);



    //HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(APP_ICON), 
    //                                            IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
    if (hIcon) 
	{
		// Associate icon to the app.
		//SendMessage(hwnd, WM_SETICON, WPARAM (ICON_SMALL), LPARAM (hIcon));// App. icon
		SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
		SendMessage(hwnd, WM_SETICON, WPARAM (ICON_BIG), LPARAM (hIcon));  //ALT+TAB icon
		return true;
    }
	else
            MessageBox(hwnd, "Could not load small icon!", "Error", MB_OK | MB_ICONERROR);
return false;
}
/**************************************************************************************************/
/**************************************************************************************************/
// Add/Set tray icon
// nAction - 1 = Create Tray Icon
//           0 = Remove Tray Icon
//           n = Change Tray Icon
// pszTip = Tray icon ToolTip text
BOOL CTray::SetIcon(PSTR pszTip , int nAction) 
{              
UINT  uIcon; // Icon ID buffer
DWORD dMsg;  // Message buffer (ADD/DELETE/MODIFY)

	NOTIFYICONDATA ni;
	ni.cbSize = sizeof(ni);
	ni.uID = 0;
	//ni.szTip=new char[128];
	lstrcpyn(ni.szTip, pszTip, sizeof(ni.szTip)); 
	ni.hWnd = this->hwnd;
	ni.uFlags = NIF_MESSAGE /*| NIF_TIP*/ | NIF_ICON; // We want to use icon, tip, and callback message
	ni.uCallbackMessage = WM_NOTIFYICONTRAY;      // Our custom callback message (WM_APP + 1)
    
    switch (nAction){
        case 0:// Remove tray icon
                return Shell_NotifyIcon(NIM_DELETE, &ni);
           break; 
        case 1://Add icon in tray
                uIcon=APP_ICON; // Set tray icon
                dMsg=NIM_ADD; // Add tray icon        
           break;
        case 2:// Modify current icon in tray
                uIcon=TRAY_ICON; // Set new tray icon	
                dMsg=NIM_MODIFY; // Modify tray icon     
           break;               
        case 3:// Modify current icon in tray
                uIcon=APP_ICON; // Set new tray icon	
                dMsg=NIM_MODIFY; // Modify tray icon      
           break;                                
     }
     
	
	char* way=GetApplicationDir();
	CString dir;
	dir.Append(way);
//	dir.Append("\\");
	dir.Append("pic");
	SetCurrentDirectory(dir);
	delete(way);
     //Load selected icon
     //ni.hIcon = (HICON)LoadIcon((HINSTANCE)GetWindowLong(this->hwnd, GWL_HINSTANCE), 
     //                                                  MAKEINTRESOURCE(uIcon));
	 CString fname;
	 fname.Append(pszTip);
	 fname.Append(".ico");
     ni.hIcon = (HICON)LoadImage(NULL, fname, IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
     // Windooows, ohohooo, we have changed icon! :)                                                
     return Shell_NotifyIcon(dMsg, &ni);       
     
     
}