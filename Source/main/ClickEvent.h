#pragma once
class ClickEvent
{
public:
	ClickEvent();
	~ClickEvent(void);
	HANDLE hEvent;
	int AddToId;
	int obj_id;
	char * EventName;//Be careful! It will be wrong after the finishing of xml parsing!!
};
