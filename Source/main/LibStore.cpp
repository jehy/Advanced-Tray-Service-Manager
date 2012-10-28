#include "stdafx.h"
#include "LibStore.h"
//#include "library.h"
LibStore::LibStore()
{

}

bool LibStore::Add(MyLibrary* lib)
{
	Store.push_back(lib);
	return true;
}
LibStore::~LibStore()
{
	for(int i=0;i<Store.size();i++)
		delete Store[i];
}

MyLibrary* LibStore::Search(char* name)
{
	for(int i=0;i<Store.size();i++)
		if(_stricmp(Store[i]->name,name)==0)
			return Store[i];
	return NULL;
}