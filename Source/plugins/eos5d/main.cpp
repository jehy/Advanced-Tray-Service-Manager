// document_func.cpp : Defines the entry point for the DLL application.
//
#include "stdafx.h"
#include "class.h"
click_class* objects;
//#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))


/*int i=0;
extern "C"__declspec(dllexport) int RefreshPluginMenu(HMENU parent);
extern "C"__declspec(dllexport) int ClickPluginMenu(int id);
extern "C"__declspec(dllexport) int test(void);
*/
#ifdef _MANAGED
#pragma managed(push, off)
#endif


BOOL APIENTRY DllMain(HMODULE hModule,DWORD ul_reason_for_call,LPVOID lpReserved)
{
switch(ul_reason_for_call)
{
	case DLL_PROCESS_ATTACH:
		//MessageBox(0,"Loading library","",MB_OK);
		break;
	case DLL_THREAD_ATTACH:
		//MessageBox(0,"Attaching a new thread...","",MB_OK);
		break;
	case DLL_THREAD_DETACH:
		//MessageBox(0,"Detaching a new thread...","",MB_OK);
		break;
	case DLL_PROCESS_DETACH:
		//MessageBox(0,"Unloading library","",MB_OK);
		break;
}
    return TRUE;
}

//We will kill object when detach library
//We need to return handles for:
//refreshmenu
//clickmenu

#ifdef _MANAGED
#pragma managed(pop)
#endif

