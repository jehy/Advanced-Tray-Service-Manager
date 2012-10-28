#include "ClickEvent.h"
#pragma once
typedef mvector <ClickEvent*> ClickEventVec;
class ClickEventsStore
{
public:
	ClickEventsStore();
	~ClickEventsStore();
	ClickEvent* Search(char* EventName);
	ClickEventVec Store;
	bool Add(ClickEvent* NewEvent);
	ClickEvent* Create(char* EventName);
};