#include "stdafx.h"
#include "class.h"
doc_class::doc_class()
{
	app=NULL;
	title=NULL;
	way=NULL;
	action=NULL;
	dir=NULL;
	launch=0;
	pic=NULL;
	ReallyCreateMenu=0;
}

doc_class::~doc_class()
{
	if(app!=NULL)delete []app;
	if(title!=NULL)delete []title;
	if(way!=NULL)delete []way;
	if(action!=NULL)delete []action;
	if(dir!=NULL)delete []dir;
}

void doc_class::SetApp(char *text)
{
	size_t z=strlen(text)+1;
	this->app=new char[z];
	strcpy_s(this->app,z,text);
}


void doc_class::SetTitle(char *text)
{
	size_t z=strlen(text)+1;
	this->title=new char[z];
	strcpy_s(this->title,z,text);
}

void doc_class::SetWay(char *text)
{
	size_t z=strlen(text)+1;
	this->way=new char[z];
	strcpy_s(this->way,z,text);
}


void doc_class::SetAction(char *text)
{
	size_t z=strlen(text)+1;
	this->action=new char[z];
	strcpy_s(this->action,z,text);
}

void doc_class::SetDir(char *text)
{
	size_t z=strlen(text)+1;
	this->dir=new char[z];
	strcpy_s(this->dir,z,text);
}

void doc_class::SetLaunch(char *text)
{
	///That's not beautiful but to create temporary arrays is worse(( 
	if(_stricmp(text,"SW_HIDE")==0)this->launch=SW_HIDE;
	else if (_stricmp(text,"SW_SHOW")==0)this->launch=SW_SHOW;
	else if (_stricmp(text,"SW_MAXIMIZE")==0)this->launch=SW_MAXIMIZE;
	else if (_stricmp(text,"SW_MINIMIZE")==0)this->launch=SW_MINIMIZE;
	else if (_stricmp(text,"SW_RESTORE")==0)this->launch=SW_RESTORE;
	else if (_stricmp(text,"SW_SHOWDEFAULT")==0)this->launch=SW_SHOWDEFAULT;
	else if (_stricmp(text,"SW_SHOWMAXIMIZED")==0)this->launch=SW_SHOWMAXIMIZED;
	else if (_stricmp(text,"SW_SHOWMINIMIZED")==0)this->launch=SW_SHOWMINIMIZED;
	else if (_stricmp(text,"SW_SHOWMINNOACTIVE")==0)this->launch=SW_SHOWMINNOACTIVE;
	else if (_stricmp(text,"SW_SHOWNOACTIVATE")==0)this->launch=SW_SHOWNOACTIVATE;
	else if (_stricmp(text,"SW_SHOWNORMAL")==0)this->launch=SW_SHOWNORMAL;
}

