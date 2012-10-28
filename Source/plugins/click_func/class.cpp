#include "stdafx.h"
#include "class.h"
click_class::click_class()
{
	Debug=0;
	ObjectCaption=NULL;
	FormCaption=NULL;
	title=NULL;
}

click_class::~click_class()
{
	if(ObjectCaption!=NULL)delete(ObjectCaption);
	if(FormCaption!=NULL)delete(FormCaption);
	if(title!=NULL)delete(title);
}


void click_class::SetObjectCaption(char *text)
{
	size_t z=strlen(text)+1;
	this->ObjectCaption=new char[z];
	strcpy_s(this->ObjectCaption,z,text);
}
void click_class::SetFormCaption(char *text)
{
	size_t z=strlen(text)+1;
	this->FormCaption=new char[z];
	strcpy_s(this->FormCaption,z,text);
}

void click_class::SetTitle(char *text)
{
	size_t z=strlen(text)+1;
	this->title=new char[z];
	strcpy_s(this->title,z,text);
}