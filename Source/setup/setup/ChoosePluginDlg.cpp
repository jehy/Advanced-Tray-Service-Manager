// hoosePluginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "setup.h"
#include "ChoosePluginDlg.h"
typedef char* (CALLBACK* LPFNDLLFUNC1)();

typedef char* (DlgNewItemFunc)();
typedef char* (DlgEditItemFunc)(char*);
extern XmlMenuTree TreeManager;
DlgNewItemFunc* DlgNewItem;
DlgEditItemFunc* DlgEditItem;

// ChoosePluginDlg dialog

IMPLEMENT_DYNAMIC(ChoosePluginDlg, CDialog)

ChoosePluginDlg::ChoosePluginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ChoosePluginDlg::IDD, pParent)
{
	//filelist.


}

ChoosePluginDlg::~ChoosePluginDlg()
{
}

void ChoosePluginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//	DDX_Control(pDX, IDC_LIST1, filelist);
	DDX_Control(pDX, IDC_LIST2, FileList);
	//DDX_Control(pDX, IDC_EDIT1, ItemName);
	DDX_Control(pDX, IDC_EDIT1, title);
}


BEGIN_MESSAGE_MAP(ChoosePluginDlg, CDialog)
	ON_WM_ACTIVATE()
	ON_BN_CLICKED(IDOK, &ChoosePluginDlg::OnBnClickedOk)
	ON_LBN_DBLCLK(IDC_LIST2, &ChoosePluginDlg::OnLbnDblclkList2)
	ON_BN_CLICKED(IDCANCEL, &ChoosePluginDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &ChoosePluginDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// ChoosePluginDlg message handlers

void ChoosePluginDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	FileList.ResetContent();
	char* dir=GetApplicationDir();
	CString path;
	path.Append(dir);
	delete(dir);
	path.Append("plugins\\");
	CString PathSearch=path;
	PathSearch.Append("*");
	CString PluginPath;
//	char path[MAX_PATH];
	WIN32_FIND_DATA fd;
	DWORD dwAttr = FILE_ATTRIBUTE_DIRECTORY;
	//dwAttr |= FILE_ATTRIBUTE_HIDDEN;
	//sprintf( path, "%s\\*", szDir);
	HANDLE hFind = FindFirstFile(PathSearch, &fd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if( (fd.dwFileAttributes & dwAttr))
			{
				if((strcmp(fd.cFileName,".")&&(strcmp(fd.cFileName,"..")))!=0)
				{
					//puts( fd.cFileName);
					PluginPath=path+fd.cFileName+"\\*_vis.dll";
					//MessageBox(PluginPath);
					FileList.Dir(DDL_DIRECTORY, PluginPath);
				}
			}
		}
		while( FindNextFile( hFind, &fd));
		FindClose( hFind);
	}



	FileList.SetCurSel(0);
	//MessageBox(path);
	/*FileList.DeleteString(0);
	delete(dir);*/
//	filelist.InsertItem(
	//CDialog::OnActivate(nState, pWndOther, bMinimized);

	// TODO: Add your message handler code here
}

void ChoosePluginDlg::OnBnClickedOk()
{
	
	CString full;
	title.GetWindowTextA(full);
	if(full.Trim()=="")
	{
		MessageBox("Please, input title for this menu item","Please...",MB_OK);
		title.SetFocus();
	}
	else
	{
		//load library
		
		
		char* dir=GetApplicationDir();
		CString path;
		path.Append(dir);
		delete(dir);
		//CString find="/";
		path.Append("plugins\\");
		//path.AppendChar(92);
		CString dllname;
		FileList.GetText(FileList.GetCurSel(),dllname);
		//dllname=dllname.Mid(1,dllname.GetLength()-2);
		//dllname.AppendChar(92);
		//dllname.Append(dllname.Left(dllname.GetLength()-1));
		//dllname.Append("_vis.dll");
		path.Append(dllname.Left(dllname.GetLength()-8)+"\\"+dllname);
		//path.Append();
		//path.Append();
		//MessageBox(path);

		HINSTANCE hinstLib; 
		hinstLib = LoadLibrary(path);
		bool CloseDialog=false;
		if(hinstLib==NULL)
		{
			CString err="Main App: Error! Library "+path+" not loaded!";
			MessageBox(err.GetBuffer(err.GetLength()));
		}
		else
		{
			try
			{
				//MessageBox("Yeah! Library loaded!");
				DlgNewItem=(DlgNewItemFunc*)GetProcAddress(hinstLib,"DlgNewItem");
				if(DlgNewItem==NULL)
					MessageBox("Main App: Error! Function not loaded!");
				else 
				{
					//MessageBox("Function loaded!");
					char* x=DlgNewItem();
					//if
					if(_stricmp(x,"cancel")!=0)
					{
						full="<item><SetupPlugin>"+dllname.Left(dllname.GetLength()-8)+"</SetupPlugin><title>"+full+"</title>";
						full.Append(x);
						full.Append("</item>");
						//MessageBox(full);
						//delete (x);
						//////////////////////////////////
						TreeManager.InsertItem(full.GetBuffer(full.GetLength()),TreeManager.tree->GetSelectedItem());
						TreeManager.SortRecursive(NULL);
						CloseDialog=true;
					}
					/////////////////////////////////
				}
			}
			catch(...){MessageBox("Smth went wrong with this plugin...","Error",MB_ICONERROR);}
		
		}
		FreeLibrary(hinstLib);
		if(CloseDialog)OnOK();
	}
	
}

void ChoosePluginDlg::OnLbnDblclkList2()
{
	CString name;
	title.GetWindowText(name);
	if(name.Trim()=="")title.SetFocus();//().SetSel(-1);
	else OnBnClickedOk();
	/*{
		MessageBox
	}*/

	// TODO: Add your control notification handler code here
}

void ChoosePluginDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void ChoosePluginDlg::OnBnClickedButton1()
{
	Sorry_Beta();
	// TODO: Add your control notification handler code here
}
