#include "library.h"
#pragma once
typedef mvector <MyLibrary*> LibVec;
class LibStore
{
public:
	LibStore();
	~LibStore();
	MyLibrary* Search(char* name);
	LibVec Store;
	bool Add(MyLibrary* lib);
};