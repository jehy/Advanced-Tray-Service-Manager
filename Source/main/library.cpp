#include "stdafx.h"
#include "funcs.h"
#include "library.h"

MyLibrary::MyLibrary(char* classname)
{
	size_t z=strlen(classname)+1;
	this->name=new char[z];
	strcpy_s(name,z,classname);

	CString path;
	char* addr=GetApplicationDir();
	path.Append(addr);
	path.Append("plugins\\");
	path.Append(classname);
	path.Append("\\");
	path.Append(classname);
	path.Append("_func.dll");
	delete(addr);
	LibHandle=LoadLibrary(path);
	if(LibHandle==NULL)
	{
		CString err="Error loading lib "+path+"!";
		ShowError(err.GetBuffer(err.GetLength()));
	}
	//intf f1,f2;
	//f1=(intf)GetProcAddress(h,"test");
	//HANDLE obj;
	//obj=MakeObject("where the fuck is it?!");
	CString err,err1;

	CreatePluginMenu=(MenuFuncCreate*)GetProcAddress(LibHandle,"CreatePluginMenu");
	if(!CreatePluginMenu)err1.Format("\nCreatePluginMenu Library function not found in library '%s_func.dll'",+classname);
	err.Append(err1);err1="";

	RefreshPluginMenu=(MenuFuncRefresh*)GetProcAddress(LibHandle,"RefreshPluginMenu");
	if(!RefreshPluginMenu)err1.Format("\nRefreshPluginMenu Library function not found in library '%s_func.dll'",+classname);
	err.Append(err1);err1="";

	ClickPluginMenu=(MenuFuncClick*)GetProcAddress(LibHandle,"ClickPluginMenu");
	if(!ClickPluginMenu)err1.Format("\nClickPluginMenu Library function not found in library '%s_func.dll'",+classname);
	err.Append(err1);err1="";

	InitPlugin=(InitPtr*)GetProcAddress(LibHandle,"InitPlugin");
	if(!InitPlugin)err1.Format("\nInitPlugin Library function not found in library '%s_func.dll'",+classname);
	err.Append(err1);err1="";
	if(err.GetLength()>0)ShowError(err.GetBuffer(err.GetLength()));

}
MyLibrary::~MyLibrary()
{
	delete (name);
	FreeLibrary(LibHandle);
}