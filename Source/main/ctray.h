#pragma once
// tray.h
//
// Minimize window in Tray with popup menu with icons.  
// This code is free, you may use it without any warranty or too much expectations...
// If you find something wrong then post your corrections or suggestions on the web.
// If you think to do better than me simply you do not use this code but send to me the your :)
//
// 2003/2004 by Massimiliano Miani (imianz@tiscalinet.it)

//About message
//#define APP_ABOUT "Minimize in tray + menu with icons example\n\n(c)2003/2004 by Imianz"
//Other message
//#define MY_MSG "Minimize this window in tray and click with \n\nleft button on icon to see a 'button effect'"

//Application icon, Tray icon and Popup menu bitmaps
#define APP_ICON       90 //app icon
#define TRAY_ICON      91 //tray icon
#define IDB_MENU_CHECK 92 //checked item bitmap (popup menu)
#define IDB_MENU_CLOSE 93 //close bitmap (popup menu)
#define IDB_MENU_ABOUT 94 //about bitmap (popup menu)
//#define COMMAND_ABOUT 1488
#define WM_NOTIFYICONTRAY (WM_APP + 1)//tray message
#define WM_MY_MENU_CLICKED 1000//tray message

//Popup Menu items
//#define IDM_MINIMIZE   421 							
//#define IDM_TEXT_MINIMIZE " Minimize to tray"			
//#define IDM_TEXT_RESTORE " Restore"

#define IDM_ABOUT	   422							
//#define IDM_TEXT_ABOUT " About"

#define IDM_CLOSE	   423						
//#define IDM_TEXT_CLOSE " Close"

//#define IDM_ONTOP	   424						
//#define IDM_TEXT_ONTOP " Always on top"

//Functions
class CTray
{
public:
	~CTray(void);              //WM_DESTROY message
	CTray(HWND hwnd);
public:
	HMENU hMenu;                                    // menu handle
	HMENU hMenu2;                                    // menu handle
	HICON hIcon;
	HWND  hwnd;                                     // main window handle
	BOOL  LoadAppIcon();                            //Application icon
	BOOL  OnCommandTrayMenu(WPARAM wParam); //Popup menu events
	void  CreateItemList(HMENU hMenu);              //Crate Popup menu
	void  SetBitmaps(HMENU hMenu);                  //Set bitmaps for popup menu items
	BOOL  SetIcon(char* pszTip, int nAction);        //Change tray icon
	void  OnNotifyTray(LPARAM lParam);      //Tray message (mouse clicks on tray icon)
private:
	void  TRAY_Menu_Show(void);             //Show popup menu
};