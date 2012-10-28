#pragma once

class ExitClass
{
public:
	bool Shutdown;
	bool ClickEventExit;
	HANDLE ExitEvent;
	ExitClass(void);
	~ExitClass(void);
};
