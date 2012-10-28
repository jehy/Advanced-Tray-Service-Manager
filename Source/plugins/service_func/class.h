//#include "stdafx.h"
//#define IDM_CLOSE	   423
typedef mvector <char*> ArgVec;	
class service_class
{
public:
	~service_class();
	service_class();
	void SetName(char* text);
	void SetArgs(char** Args);
//private:
	int id;
//	int ClickPluginMenu(int id);
//private:
	char** Args;
	char* name;
	HMENU hMenu;
	int number;
	int ArgNum;
	HBITMAP pic;
};