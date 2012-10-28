//#include "stdafx.h"
//#define IDM_CLOSE	   423

typedef mvector <char*> ArgVec;	
class click_class
{
public:
	~click_class();
	click_class();
	void SetObjectCaption(char *text);
	void SetFormCaption(char *text);
	void SetTitle(char *text);
	HMENU hMenu;
	int id;//menu id
	bool Debug;
	char* ObjectCaption;
	char* FormCaption;
	char* title;
};