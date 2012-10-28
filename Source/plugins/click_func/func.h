/*
typedef HANDLE (InitPtr)(char*, int);
typedef int (MenuFuncCreate)(HMENU,int);
typedef int (MenuFuncRefresh)(HANDLE);
typedef int (MenuFuncClick)(int);
*/
extern "C"__declspec(dllexport) int InitPlugin(char* data, int obj_id,HANDLE DieEvent);
extern "C"__declspec(dllexport) int CreatePluginMenu(HMENU parent,int obj_id);
extern "C"__declspec(dllexport) int RefreshPluginMenu(int obj_id);
extern "C"__declspec(dllexport) int ClickPluginMenu(int menu_id);

int InitPlugin(char* data, int obj_id,HANDLE DieEvent);
int CreatePluginMenu(HMENU parent,int obj_id);
int RefreshPluginMenu(int obj_id);
int ClickPluginMenu(int menu_id);
