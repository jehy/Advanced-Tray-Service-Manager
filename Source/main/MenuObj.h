#pragma once

class MenuObj
{
public:
	MyLibrary* library;
	MenuObj(void);
	~MenuObj(void);
	int id;
	int interval;
	bool Shutdown;
	void SetBusyEventName(char* name);
	char* BusyEventName;
	//HANDLE IDHandle;
};

typedef mvector <MenuObj*> MenuObjectsVec;