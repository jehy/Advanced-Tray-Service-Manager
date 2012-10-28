#include "stdafx.h"
#include "ClickEventsStore.h"
//#include "library.h"
ClickEventsStore::ClickEventsStore()
{

}

bool ClickEventsStore::Add(ClickEvent* NewEvent)
{
	Store.push_back(NewEvent);
	return true;
}
ClickEventsStore::~ClickEventsStore()
{
	for(int i=0;i<Store.size();i++)
		delete Store[i];
}

ClickEvent* ClickEventsStore::Search(char* EventName)
{
	for(int i=0;i<Store.size();i++)
		if(!_stricmp(Store[i]->EventName,EventName))
			return Store[i];
	return NULL;
}

ClickEvent*  ClickEventsStore::Create(char* EventName)
{
	HANDLE hevent=CreateEvent(NULL,TRUE,FALSE,EventName);
	ClickEvent* Event=this->Search(EventName);
	if(Event==NULL)
	{
		Event=new ClickEvent();
		Event->hEvent=hevent;
		Event->EventName=EventName;
		this->Add(Event);
	}
	return Event;
}