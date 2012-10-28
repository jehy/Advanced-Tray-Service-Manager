#pragma once
typedef int (InitPtr)(char*, int,HANDLE);
typedef int (MenuFuncCreate)(HMENU,int);
typedef int (MenuFuncRefresh)(int);
typedef int (MenuFuncClick)(int);
//typedef mvector <HANDLE> HandleVec;

class MyLibrary
{
public:
	MyLibrary(char* classname);
	~MyLibrary();
	InitPtr* InitPlugin;
	MenuFuncCreate* CreatePluginMenu;
	MenuFuncRefresh* RefreshPluginMenu;
	MenuFuncClick* ClickPluginMenu;
	char* name;
	//HandleVec objects;
private:
	HMODULE LibHandle;
};