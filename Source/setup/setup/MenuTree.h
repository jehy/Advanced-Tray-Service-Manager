#pragma once
#include "MenuItem.h"
typedef mvector <MenuItem*> MenuItems;
class XmlMenuTree
{
public:
	XmlMenuTree();
	~XmlMenuTree();
	int LoadFromFile(char* filename);
	int LoadToTree();
	int SaveToFile(char* filename);
	int InsertItem(char* subtext,HTREEITEM item);
	int	DeleteItem(HTREEITEM Node);
	int UpdateItemTitle(HTREEITEM Node, char* NewTitle);
	void SortRecursive(HTREEITEM Node);
	MenuItems vec;
	AllXml MenuXml;
	CTreeCtrl* tree;
private:
	int DeleteItem(MenuItem* parent);
	int Load2(MenuItem* parent);
	char* Save2(xml* parent, int offset);
};