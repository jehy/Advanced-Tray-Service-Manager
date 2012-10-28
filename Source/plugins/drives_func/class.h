//#include "stdafx.h"
//#define IDM_CLOSE	   423

class drive
{
public:
	~drive();
	drive();
	char letter;
	DWORD Type;
	char* Label;
	char* Fsys;
	__int64 i64FreeBytesToCaller, i64TotalBytes, i64FreeBytes;
	DWORD VolumeSerialNumber;
	HBITMAP pic;
	void SetType(char* text);
	void SetLabel(char* text);
	HMENU hMenu;
};
typedef mvector <drive*> drives;
typedef mvector <DWORD> drive_types;

class drive_class
{
public:
	~drive_class();
	drive_class();
	//void SetName(char* text);
	//void SetArgs(char** Args);
	int id;
	drives Drives;
	drive_types DriveTypes;
	HMENU hMenu;
	bool ShowVolName;
	bool ShowVolIcon;
	bool ShowVolSpace;
	int number;
};

typedef mvector <drive_class*> drive_classes;	