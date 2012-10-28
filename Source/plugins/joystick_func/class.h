//#include "stdafx.h"
//#define IDM_CLOSE	   423

typedef mvector <char*> ArgVec;	
typedef mvector <HANDLE> HandleVec;	
class joystick_class
{
public:
	~joystick_class();
	joystick_class();
	//HMENU hMenu;
	int DeviceId;
	int id;//menu id
	int SleepAfterClick;
	bool Debug;
	HandleVec WaitingEventsHandles;
};