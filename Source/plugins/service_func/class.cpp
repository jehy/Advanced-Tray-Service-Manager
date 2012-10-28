#include "stdafx.h"
#include "class.h"
service_class::service_class()
{
	Args=NULL;
	ArgNum=0;
	pic=NULL;
}

service_class::~service_class()
{
	if(Args!=NULL)delete[] Args;
}

void service_class::SetName(char *text)
{
	size_t z=strlen(text)+1;
	this->name=new char[z];
	strcpy_s(this->name,z,text);
}

void service_class::SetArgs(char** Args)
{
	this->Args=Args;
}