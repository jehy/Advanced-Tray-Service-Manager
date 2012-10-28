//#include "stdafx.h"
//#define IDM_CLOSE	   423	
class doc_class
{
public:
	~doc_class();
	doc_class();
	void SetApp(char* text);
	void SetTitle(char* text);
	void SetWay(char* text);
	void SetAction(char* text);
	void SetLaunch(char* text);
	void SetDir(char* text);
//private:
	int id;
//	int ClickPluginMenu(int id);
//private:
	char* way;
	char* app;
	char* title;
	char* action;
	char* dir;
	int ReallyCreateMenu;
	int launch;
	HMENU hMenu;
	HBITMAP pic;
};