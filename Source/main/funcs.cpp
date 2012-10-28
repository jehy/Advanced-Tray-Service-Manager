#include "stdafx.h"
#define MENU_ITEMS_OFFSET 1000
LibStore Libs;
ClickEventsStore ClickEvents;
MenuObjectsVec MenuObjects;
extern ExitClass ExitProgram;




int ClickPluginMenu(LPVOID wParam)
{
	//wparam is clicked object id
	//item_id*1000
	WORD cl=LOWORD(wParam);
	int item_id=floor((float)(cl/1000));
	for(int i=0;i<MenuObjects.RealCount;i++)
		if(MenuObjects[i]->id==item_id)
		{
			if(MenuObjects[i]->BusyEventName!=NULL)
			{
				HANDLE hBusyEvent=CreateEvent(NULL,TRUE,FALSE,MenuObjects[i]->BusyEventName);
				//ShowError(MenuObjects[i]->BusyEventName);
				if (hBusyEvent!=NULL)
				{
					DWORD x=WaitForSingleObject(hBusyEvent,0);
					if(x==WAIT_OBJECT_0)//busy
					{
						//Beep( 750, 3000 );
						MessageBeep(-1);
				//ShowError(GetTextLastError());
						return 0;
						//MenuObjects[i]->library->ClickPluginMenu(cl);
						//ReleaseBusyEvent(hBusyEvent);
					}
				}

			}
				MenuObjects[i]->library->ClickPluginMenu(cl);
		}
	return 1;
}


int CreateMyMenu (AllXml* mxml, HMENU menu, xml* parent)
{
	for(int i=0;i<mxml->vec.size();i++)
	{
		if(mxml->vec[i]->parent==parent)
		{
			if(_stricmp(mxml->vec[i]->name,"submenu")==0)
			{
				HMENU NewMenu=CreatePopupMenu();
				xml* title=mxml->GetItemOnlyChild(mxml->vec[i],"title",1);
				AppendMenu(menu,MF_POPUP,(UINT_PTR)NewMenu,title->subtext);
				CreateMyMenu(mxml,(HMENU)NewMenu,mxml->vec[i]);
			}
			else if(_stricmp(mxml->vec[i]->name,"item")==0)
			{
				xml* child=mxml->GetItemOnlyChild(mxml->vec[i],"RunPlugin",1);
				MyLibrary* ThisLib=Libs.Search(child->subtext);
				if(ThisLib==NULL)
				{
					ThisLib=new(MyLibrary)(child->subtext);
					Libs.Add(ThisLib);
				}
				//now we need to initialize and get a handle to object
				//later we'll just make one thread for each of handles and make
				//them work
				MenuObj* obj=new(MenuObj);
				obj->id=MenuObjects.RealCount+1;
				obj->library=ThisLib;

				CString temp="<";
				temp.Append(mxml->vec[i]->name);
				temp.Append(">");
				temp.Append(mxml->vec[i]->subtext);
				temp.Append("</");
				temp.Append(mxml->vec[i]->name);
				temp.Append(">");


				for(int z=0;z<mxml->vec.size();z++)//For answering plugins
				{
					child=mxml->vec[z];
					if(child!=NULL)
					{
						if((child->parent==mxml->vec[i])&&(!_stricmp(child->name,"WaitEvent")))
						{
							ClickEvent* Event=ClickEvents.Create(child->subtext);
							Event->obj_id=obj->id;
						}
					}
				}

				for(int z=0;z<mxml->vec.size();z++)//For calling plugins
				{
					child=mxml->vec[z];
					if(child!=NULL)
					{
						if((child->parent==mxml->vec[i])&&(!_stricmp(child->name,"CallEvent")))
						{
							xml* child2=mxml->GetItemOnlyChild(child,"Name",1);
							ClickEvent* Event=ClickEvents.Create(child2->subtext);			
							child=mxml->GetItemOnlyChild(child,"AddToId");
							if(child!=NULL)
							{
								int z=atoi(child->subtext);
								Event->AddToId=z;
							}
						}
					}
				}

				
				obj->library->InitPlugin(temp.GetBuffer(), obj->id,ExitProgram.ExitEvent);
				bool c=true;
				child=mxml->GetItemOnlyChild(mxml->vec[i],"ReallyCreateMenu");
				if(child!=NULL)
				{
					if(!IsTrue(child->subtext));
						c=false;
				}
				if(c)
					ThisLib->CreatePluginMenu(menu,obj->id);

				child=mxml->GetItemOnlyChild(mxml->vec[i],"Refresh");
				if(child!=NULL)
					if(strcmp(child->subtext,"0"))
						obj->interval=atoi(child->subtext);
				child=mxml->GetItemOnlyChild(mxml->vec[i],"BusyEvent");
				if(child!=NULL)
						obj->SetBusyEventName(child->subtext);
				MenuObjects.push_back(obj);
			}
			else CreateMyMenu(mxml,menu,mxml->vec[i]);
		}
	}
	return 1;
}


