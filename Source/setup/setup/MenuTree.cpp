#include "stdafx.h"
#include "MenuTree.h"

void XmlMenuTree::SortRecursive(HTREEITEM Node)
{
	tree->SortChildren(Node);
	if (tree->ItemHasChildren(Node))
	{
	   HTREEITEM hNextItem;
	   HTREEITEM hChildItem = tree->GetChildItem(Node);
	   while (hChildItem != NULL)
	   {
		  hNextItem = tree->GetNextItem(hChildItem, TVGN_NEXT);
		  //pmyTreeCtrl->DeleteItem(hChildItem);
		  this->SortRecursive(hChildItem);
		  hChildItem = hNextItem;
	   }
	}
}


XmlMenuTree::XmlMenuTree()
{
}
XmlMenuTree::~XmlMenuTree()
{
	for(int i=0;i<vec.RealCount;i++)
	{
		delete(vec[i]);
	}
}
int XmlMenuTree::LoadFromFile(char* filename)
{

	char* text=file_get_contents(filename);
	this->MenuXml.Parse(text,"xml");
	delete(text);
	return 1;
}

int XmlMenuTree::Load2(MenuItem* parent)
{
	for(int i=0;i<MenuXml.vec.size();i++)
		{
			if(MenuXml.vec[i]->parent==parent->XmlItem)
			{
			//MessageBox(NULL,MenuXml.vec[i]->name,"",MB_OK);
				if(_stricmp(MenuXml.vec[i]->name,"submenu")==0)
				{
					//
					//TV_INSERTSTRUCT* tvstruct;
					HTREEITEM pNode;//


					//tvstruct=new(TV_INSERTSTRUCT);
					TV_INSERTSTRUCT tvstruct;//=new(TV_INSERTSTRUCT);
//TV_INSERTSTRUCT
					//pItm = tree.GetSelectedItem();
					tvstruct.hParent = parent->pNode;
					tvstruct.item.mask = TVIF_TEXT ;
					xml* child=MenuXml.GetItemOnlyChild(MenuXml.vec[i],"title",1);
					tvstruct.item.pszText = child->subtext;
					pNode = this->tree->InsertItem(&tvstruct);
					MenuItem* NewItem=new(MenuItem);
					NewItem->XmlItem=MenuXml.vec[i];
					NewItem->pNode=pNode;
					this->vec.push_back(NewItem);
					Load2(NewItem);
					tree->Expand(pNode,TVE_EXPAND);
				}
				else if(_stricmp(MenuXml.vec[i]->name,"item")==0)
				{
					//TV_INSERTSTRUCT* tvstruct;
					HTREEITEM pNode;//
					TV_INSERTSTRUCT tvstruct;//=new(TV_INSERTSTRUCT);
					//pItm = tree.GetSelectedItem();
					tvstruct.hParent = parent->pNode;
					tvstruct.item.mask = TVIF_TEXT ;
					xml* child=MenuXml.GetItemOnlyChild(MenuXml.vec[i],"title",1);
					tvstruct.item.pszText = child->subtext;
					pNode = this->tree->InsertItem(&tvstruct);
					MenuItem* NewItem=new(MenuItem);
					NewItem->XmlItem=MenuXml.vec[i];
					NewItem->pNode=pNode;
					this->vec.push_back(NewItem);
					//Load2(NewItem);
				}
				else if(_stricmp(MenuXml.vec[i]->name,"menu")==0)
				{
					HTREEITEM pNode;//
					TV_INSERTSTRUCT tvstruct;//=new(TV_INSERTSTRUCT);
					//pItm = tree.GetSelectedItem();
					tvstruct.hParent = NULL;
					tvstruct.item.mask = TVIF_TEXT ;
					tvstruct.item.pszText = "menu";
					pNode = this->tree->InsertItem(&tvstruct);
					MenuItem* NewItem=new(MenuItem);
					NewItem->XmlItem=MenuXml.vec[i];
					NewItem->pNode=pNode;
					this->vec.push_back(NewItem);
					Load2(NewItem);
				
				}
			}
		}
return 1;
}

int XmlMenuTree::LoadToTree()
{
	tree->DeleteAllItems();
	vec.Clear_And_Delete_Elements();
	//////////
	/*
	HTREEITEM pNode;//
	TV_INSERTSTRUCT tvstruct;//=new(TV_INSERTSTRUCT);
	//pItm = tree.GetSelectedItem();
	tvstruct.hParent = NULL;
	tvstruct.item.mask = TVIF_TEXT ;
	xml* child=MenuXml.GetItemOnlyChild(MenuXml.vec[i],"title");
	tvstruct.item.pszText = child->subtext;
	pNode = this->tree->InsertItem(&tvstruct);
	MenuItem* NewItem=new(MenuItem);
	NewItem->XmlItem=MenuXml.vec[i];
	NewItem->pNode=pNode;
	this->vec.push_back(NewItem);
*/

	//////////


	//if(vec!=NULL)delete(vec);
	/*xml* main=new xml(NULL);
	main->name=NULL;
	main->subtext=NULL;
	MenuXml.vec.push_back(main);
*/
	MenuItem* item=new(MenuItem);
	item->pNode=NULL;
	item->XmlItem=MenuXml.GetItemOnlyChild(MenuXml.MainElement,"xml",1);
	//item->XmlItem=MenuXml.GetItemOnlyChild(item->XmlItem,"menu");
	vec.push_back(item);
	Load2(item);
	tree->Expand(tree->GetRootItem(),TVE_EXPAND);
	return 1;
}

char* XmlMenuTree::Save2(xml* parent, int offset)
{

	CString FileContents;
	CString NewContents;
	bool found=0;
	for(int i=0;i<this->MenuXml.vec.size();i++)
	{
		if(MenuXml.vec[i]->parent==parent)
		{
			//CString fuck;
			//fuck.Format("child of %s is equal to %s",parent->name,MenuXml.vec[i]->name);
			//MessageBox(NULL,fuck,"",MB_OK);
			found=1;
			char* NewC=Save2(MenuXml.vec[i],offset+1);
			NewContents.Append(NewC);
			delete(NewC);
		}
	}
	if (found==0)
	{
		for(int n=0;n<offset;n++)FileContents.Append("	");
		/*<tag>*/FileContents+="<";FileContents+=parent->name;FileContents+=">";
		/*value*/FileContents+=parent->subtext;
		/*</tag>*/FileContents+="</";FileContents+=parent->name;FileContents+=">";
		FileContents.Append("\n");
	}
	else
	{
			for(int n=0;n<offset;n++)FileContents.Append("	");
			FileContents+="<";FileContents+=parent->name;FileContents+=">";
			FileContents.Append("\n");
			
			FileContents.Append(NewContents);
			//delete(NewContents);
			for(int n=0;n<offset;n++)FileContents.Append("	");
			FileContents+="</";FileContents+=parent->name;FileContents+=">";
			FileContents.Append("\n");
	
	}
	//file_put_contents(filename,);
	char* contents=new char[FileContents.GetLength()+1];
	strcpy_s(contents,FileContents.GetLength()+1,FileContents);
	//FileContents.ReleaseBuffer();
	//NewContents.ReleaseBuffer();
	return contents;
}

int XmlMenuTree::SaveToFile(char* filename)
{

	//CString FileContents;
	char* FileContents=Save2(MenuXml.GetItemOnlyChild(this->MenuXml.MainElement,"xml",1),0);
	file_put_contents(filename,FileContents);
	delete(FileContents);
	return 1;
}


int XmlMenuTree::InsertItem(char* subtext, HTREEITEM item)
{
	//HTREEITEM item=this->tree->GetSelectedItem();
	xml* main=NULL;
	for(int i=0;i<vec.RealCount;i++)
	{
		if(vec[i]->pNode==item)main=vec[i]->XmlItem;
	}
	if((_stricmp(main->name,"submenu")!=0)&&(_stricmp(main->name,"menu")!=0))
		MessageBox(NULL,"Unable to assign item here","Error",MB_ICONWARNING);
	////
	///	the part above was not so neccesary but...
	///
	else
	{
		if(main==NULL)ShowError("Parent node not found in xml cache!");
		CString temp;
		temp.Append(subtext);
		if(temp.Find("<submenu>")==0)//detected submenu
			this->MenuXml.parse2(subtext,"submenu",strlen("<submenu>"),main,&MenuXml.vec);
		else 
			this->MenuXml.parse2(subtext,"item",strlen("<item>"),main,&MenuXml.vec);
		MenuItem* NewItem=new(MenuItem);
		xml* ready=MenuXml.vec[MenuXml.vec.RealCount-1];
		NewItem->XmlItem=ready;

		//TV_INSERTSTRUCT* tvstruct;
		HTREEITEM pNode;//
		TV_INSERTSTRUCT tvstruct;
		//tvstruct=new(TV_INSERTSTRUCT);
		//pItm = tree.GetSelectedItem();
		tvstruct.hParent = item;
		tvstruct.item.mask = TVIF_TEXT ;
		xml* child=MenuXml.GetItemOnlyChild(ready,"title",1);
		tvstruct.item.pszText=child->subtext;
		pNode = tree->InsertItem(&tvstruct);
		tree->SetFocus();
		tree->SelectItem(pNode);
		NewItem->pNode=pNode;
		this->vec.push_back(NewItem);
	}
return 1;
}


int XmlMenuTree::DeleteItem(HTREEITEM Node)
{
	for(int i=0;i<this->vec.RealCount;i++)
	{
		if(vec[i]->pNode==Node)
		{
			//MessageBox(NULL,"found node to delete!","",MB_OK);
			DeleteItem(vec[i]);
			break;
			//if(!MenuXml.vec.delete_by_value(vec[i]->XmlItem))ShowError("Not found in XML elements");
		}
		//if(!vec.delete_by_value(vec[i]))ShowError("Not found in menu elements");
		
	}
	tree->SelectItem(tree->GetPrevVisibleItem(Node));
	tree->SetFocus();
	tree->DeleteItem(Node);
	return 1;
}

//
int XmlMenuTree::DeleteItem(MenuItem* parent)
{
	for(int i=0;i<this->vec.RealCount;i++)
	{
		if(vec[i]->XmlItem->parent==parent->XmlItem)
		{
			//MessageBox(NULL,"found child to delete!","",MB_OK);
			DeleteItem(vec[i]);
			//if(!vec.delete_by_value(vec[i]))ShowError("Not found in XML elements");
			//if(!MenuXml.vec.delete_by_value(vec[i]->XmlItem))ShowError("Not found in XML elements");
		}
		//if(!vec.delete_by_value(vec[i]))ShowError("Not found in menu elements");
		//break;
	}
	//MessageBox(NULL,"Deleting parent!","",MB_OK);
	if(!MenuXml.vec.delete_by_value(parent->XmlItem))ShowError("Not found in XML elements");
	if(!vec.delete_by_value(parent))ShowError("Not found in MENU elements");
	return 1;

}



int XmlMenuTree::UpdateItemTitle(HTREEITEM Node, char* NewTitle)
{
	if(NewTitle==NULL)return 0;
	if(_stricmp(NewTitle,"")==0)
	{
		MessageBox(NULL,"Please, input some text there","Error",MB_ICONWARNING);//MB_ICONERROR
		return 0;
	}
	else
	{
		for(int i=0;i<vec.RealCount;i++)
		{
			if(vec[i]->pNode==Node)
			{
				xml* title=this->MenuXml.GetItemOnlyChild(vec[i]->XmlItem,"title",1);
				title->SetSubtext(NewTitle);
			}
		}
	}
	return 1;//result - to update or not
}