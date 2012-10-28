// EditItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "setup.h"
#include "EditItemDlg.h"

//bool activated=false;
extern XmlMenuTree TreeManager;
extern char* EditItem;
// EditItemDlg dialog
xml* main;
IMPLEMENT_DYNAMIC(EditItemDlg, CDialog)

EditItemDlg::EditItemDlg(int mode, CWnd* pParent /*=NULL*/)
	: CDialog(EditItemDlg::IDD, pParent)
{
	this->mode=mode;
}

EditItemDlg::~EditItemDlg()
{
}

void EditItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, title);
	DDX_Control(pDX, IDC_COMBO1, setup_plugin);
	DDX_Control(pDX, IDC_COMBO2, run_plugin);
	DDX_Control(pDX, IDC_CHECK1, monitor);
	DDX_Control(pDX, IDC_EDIT1, XmlText);
}


BEGIN_MESSAGE_MAP(EditItemDlg, CDialog)
//	ON_WM_CREATE()
//ON_WM_ACTIVATE()
//ON_WM_PAINT()
//ON_WM_SHOWWINDOW()
ON_BN_CLICKED(IDCANCEL, &EditItemDlg::OnBnClickedCancel)
ON_BN_CLICKED(IDOK, &EditItemDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// EditItemDlg message handlers

BOOL EditItemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//this->DoDataExchange(NULL);
if(mode==1)//change
	//load data
	{
		
		HTREEITEM item=TreeManager.tree->GetSelectedItem();
		xml*child;
		for(int i=0;i<TreeManager.vec.RealCount;i++)
		{
			if(TreeManager.vec[i]->pNode==item)main=TreeManager.vec[i]->XmlItem;
		}

		for(int i=0;i<TreeManager.MenuXml.vec.RealCount;i++)
		{
			if(TreeManager.MenuXml.vec[i]->parent==main)
			{
				child=TreeManager.MenuXml.vec[i];
				//switch(child->subtext)
				//{
				if(_stricmp(child->name,"title")==0)
					title.SetWindowTextA(child->subtext);
				else if(_stricmp(child->name,"monitor")==0)
				{
					if(child!=NULL)
					{
						if(IsTrue(child->subtext))monitor.SetCheck(1);
					}
				}
				else if(_stricmp(child->name,"RunPlugin")==0)
					run_plugin.SetWindowTextA(child->subtext);
				else if(_stricmp(child->name,"SetupPlugin")==0)
					setup_plugin.SetWindowTextA(child->subtext);	
				else
				{
					CString buf;
					XmlText.GetWindowTextA(buf);
					buf.Append("<");
					buf.Append(child->name);
					buf.Append(">");

					buf.Append(child->subtext);

					buf.Append("</");
					buf.Append(child->name);
					buf.Append(">\r\n");
					XmlText.SetWindowTextA(buf);
				}
			}
		}
		
}
return TRUE;
}



void EditItemDlg::OnBnClickedCancel()
{
	//EditItem=new char[7];
	//strcpy_s(EditItem,7,"Cancel");
	// TODO: Add your control notification handler code here
	OnCancel();
}

void EditItemDlg::OnBnClickedOk()
{
	HTREEITEM parent;
	if(mode==1)//edit item
	{
		HTREEITEM item=TreeManager.tree->GetSelectedItem();
		parent=TreeManager.tree->GetParentItem(item);
		TreeManager.tree->DeleteItem(item);//remove from tree
		TreeManager.MenuXml.DeleteItem(main);//remove from xml
		for(int i=0;i<TreeManager.vec.RealCount;i++)//remove from menu collection
		{
			if(TreeManager.vec[i]->XmlItem==main)
				TreeManager.vec.delete_by_value(TreeManager.vec[i]);
		}
	}
	else parent=TreeManager.tree->GetSelectedItem();

	CString res,temp;
	title.GetWindowTextA(temp);
	res="<title>"+temp;
	res+="</title>";
	setup_plugin.GetWindowTextA(temp);
	res+="<SetupPlugin>"+temp;
	res+="</SetupPlugin>";
	
	run_plugin.GetWindowTextA(temp);
	res+="<RunPlugin>"+temp;
	res+="</RunPlugin>";
	
	if(monitor.GetCheck()==0)temp="False";
	else temp="True";
	res+="<monitor>"+temp;
	res+="</monitor>";
	
	XmlText.GetWindowTextA(temp);
	res+=temp;

	res="<item>"+res+"</item>";
	//TreeManager.MenuXml.parse2(res,"item",strlen("<item>"),main,&TreeManager.MenuXml.vec);
	TreeManager.InsertItem(res.GetBuffer(),parent);
	TreeManager.SortRecursive(NULL);
	//EditItem=new char[res.GetLength()+1];
	//strcpy_s(EditItem,res.GetLength()+1,res.GetBuffer(res.GetLength()));
	// TODO: Add your control notification handler code here
	OnOK();
}
