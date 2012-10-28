#pragma once
//AND ONE THREAD TO RULE THEM ALL!
class CheckThread
{
public:
	CheckThread(int ThreadMethod=0);
//public:
	~CheckThread(void);
	int Stop(void);
	MenuObjectsVec ObjectStore;
	ClickEventsStore ClickEvents;
	int interval;
	int method;
	int Run(void);
//private:
};

	int Run2(LPVOID lpParam);