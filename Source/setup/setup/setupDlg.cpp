// setupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "setup.h"
#include "setupDlg.h"
#include "ChoosePluginDlg.h"
#include "EditItemDlg.h"
#include "Windows.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//POPUP MENU
HMENU hMenu;                                 // menu handle
ChoosePluginDlg* dlg2;
EditItemDlg* dlg3;
extern XmlMenuTree TreeManager;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CsetupDlg dialog




CsetupDlg::CsetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CsetupDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, tree);
}

BEGIN_MESSAGE_MAP(CsetupDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CsetupDlg::OnBnClickedButton1)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE1, &CsetupDlg::OnTvnEndlabeleditTree1)
	ON_BN_CLICKED(IDC_BUTTON2, &CsetupDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CsetupDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CsetupDlg::OnBnClickedButton4)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CsetupDlg::OnNMClickTree1)
	ON_NOTIFY(TVN_BEGINDRAG, IDC_TREE1, &CsetupDlg::OnTvnBegindragTree1)
	ON_BN_CLICKED(IDOK, &CsetupDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CsetupDlg::OnBnClickedCancel)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CsetupDlg::OnNMRclickTree1)
	ON_BN_CLICKED(IDC_BUTTON6, &CsetupDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CsetupDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &CsetupDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CsetupDlg message handlers

BOOL CsetupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	tree.ModifyStyle(LVS_TYPEMASK, TVS_SHOWSELALWAYS|TVS_LINESATROOT|TVS_HASLINES|TVS_HASBUTTONS| TVS_NOTOOLTIPS|TVS_EDITLABELS/*| TVS_TRACKSELECT */);
	hMenu=CreatePopupMenu();
//	CreateItemList(hMenu);    
	AppendMenu(hMenu,MF_STRING ,ADDSUBMENU,"Add SubMenu");// append menu
	AppendMenu(hMenu,MF_STRING ,ADDSUBITEM,"Add SubItem");// append menu
	AppendMenu(hMenu,MF_STRING ,EDITITEM,"Rename Item");// append menu
	AppendMenu(hMenu,MF_STRING ,DELETEITEM,"Delete Item");// append menu
	AppendMenu(hMenu,MF_STRING ,EDITSUBITEM,"Edit SubItem");// append menu

	TreeManager.tree=&tree;
	CString sett;
	char* way=GetApplicationDir();
	sett.Append(way);
	sett.Append("settings.txt");
	TreeManager.LoadFromFile(sett.GetBuffer(sett.GetLength()));
	TreeManager.LoadToTree();
	TreeManager.SortRecursive(NULL);
	delete(way);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CsetupDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CsetupDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CsetupDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CsetupDlg::OnBnClickedButton1()
{
	HTREEITEM item=tree.GetSelectedItem();
	xml* main=NULL;
	for(int i=0;i<TreeManager.vec.RealCount;i++)
	{
		if(TreeManager.vec[i]->pNode==item)main=TreeManager.vec[i]->XmlItem;
	}
	if(_stricmp(main->name,"item")==0)
		MessageBox("Unable to assign item here","Error",MB_ICONWARNING);
	else
	{
		char* smenu="<submenu><title>New SubMenu</title></submenu>";
		TreeManager.InsertItem(smenu,TreeManager.tree->GetSelectedItem());
		TreeManager.SortRecursive(NULL);
	}
}
void CsetupDlg::OnTvnEndlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	*pResult = TreeManager.UpdateItemTitle(pTVDispInfo->item.hItem,pTVDispInfo->item.pszText);
}

void CsetupDlg::OnBnClickedButton2()
{
	TreeManager.DeleteItem(tree.GetSelectedItem());
}

void CsetupDlg::OnBnClickedButton3()
{
	HTREEITEM item=tree.GetSelectedItem();
	xml* main=NULL;
	for(int i=0;i<TreeManager.vec.RealCount;i++)
	{
		if(TreeManager.vec[i]->pNode==item)main=TreeManager.vec[i]->XmlItem;
	}
	if(_stricmp(main->name,"item")==0)
		MessageBox("Unable to assign item here","Error",MB_ICONWARNING);
	else
	{
		dlg2=new ChoosePluginDlg();
		dlg2->DoModal();
		delete(dlg2);
	}
}

void CsetupDlg::OnBnClickedButton4()
{
		tree.EditLabel(tree.GetSelectedItem());
}

void CsetupDlg::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
}

void CsetupDlg::OnTvnBegindragTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	/*LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	*pResult = 0;*/
}

void CsetupDlg::OnBnClickedOk()//save
{
	int z=IDNO;
	if(FindProc("tray.exe"))
	{
		z=MessageBox("I see, here's tray manager running - do you want to restart it for changes to take effect?","Message",MB_YESNO);
	}
	if(z==IDYES)
	{
		HWND wnd=::FindWindow("Tiny class","Tray_Manager");
		::PostMessage(wnd, WM_DESTROY, 0, 0);
	}
	CString sett;
	char* way=GetApplicationDir();
	sett.Append(way);
	sett.Append("settings.txt");
	TreeManager.SaveToFile(sett.GetBuffer(sett.GetLength()));
	if(z==IDYES)
	{
		CString exec;
		exec.Append(way);
		exec.Append("tray.exe");
		while(FindProc("tray.exe"))Sleep(100);
		ShellExecute(NULL,"open",exec,"","",SW_HIDE);
	}
	delete(way);
}

void CsetupDlg::OnBnClickedCancel()
{
	//OnCancel();
	exit(0);
}


void CsetupDlg::OnNMRclickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM hItem = tree.GetFirstVisibleItem();
	while (hItem != NULL)
	{
		int state=tree.GetItemState(hItem,TVIS_SELECTED);//TVIS_FOCUSED does not exist
		if(
			(state==104)||//first&expanded
			(state==8)||//last&expanded
			(state==66)||//first&closed
			(state==72)//last&closed
			)
			{
				tree.SelectItem(hItem);
				break;
				//MessageBox(tree.GetItemText(hItem));
			}
	    //else break;
		hItem = tree.GetNextVisibleItem(hItem);
	}


	POINT pt;// point structure
	GetCursorPos(&pt);// get the cursors position
	
	int i=TrackPopupMenu(hMenu,TPM_LEFTALIGN | TPM_NONOTIFY | TPM_RIGHTBUTTON | TPM_RETURNCMD,pt.x,pt.y,0,this->m_hWnd,NULL);// track the popup
	//i=0;
	switch(i){
	case ADDSUBMENU:
		OnBnClickedButton1();
		break;
	case ADDSUBITEM:
		OnBnClickedButton3();
		break;
case EDITITEM:
		OnBnClickedButton4();
		break;
	case DELETEITEM:
		OnBnClickedButton2();
		break;
	case EDITSUBITEM:
		OnBnClickedButton7();
		break;
}
	*pResult = 1;
	//*pResult = 0;
}

void CsetupDlg::OnBnClickedButton6()//new item
{
	HTREEITEM item=tree.GetSelectedItem();
	xml* main=NULL;
	for(int i=0;i<TreeManager.vec.RealCount;i++)
	{
		if(TreeManager.vec[i]->pNode==item)main=TreeManager.vec[i]->XmlItem;
	}
	if(_stricmp(main->name,"item")==0)
		MessageBox("Unable to assign item here","Error",MB_ICONWARNING);
	else
	{
		//char* smenu="<item><title>New SubMenu</title></item>";
		dlg3=new EditItemDlg(0);
		dlg3->DoModal();
		delete(dlg3);		
		//TreeManager.InsertItem(smenu);
	}
	// TODO: Add your control notification handler code here
}

void CsetupDlg::OnBnClickedButton5()//edit item
{
	HTREEITEM item=tree.GetSelectedItem();
	xml* main=NULL;
	for(int i=0;i<TreeManager.vec.RealCount;i++)
	{
		if(TreeManager.vec[i]->pNode==item)main=TreeManager.vec[i]->XmlItem;
	}
	if(_stricmp(main->name,"item")!=0)
		MessageBox("It's not an item!","Error",MB_ICONWARNING);
	else
	{
		dlg3=new EditItemDlg(1);
		dlg3->DoModal();
		delete(dlg3);
	}
}

void CsetupDlg::OnBnClickedButton7()//wizard: edit subitem
{
	HTREEITEM item=tree.GetSelectedItem();
	xml* main=NULL;
	for(int i=0;i<TreeManager.vec.RealCount;i++)
	{
		if(TreeManager.vec[i]->pNode==item)main=TreeManager.vec[i]->XmlItem;
	}
	if(_stricmp(main->name,"item")!=0)
		MessageBox("EDIT can be applied only to ITEMS!","Error",MB_ICONWARNING);
	else
	{
		//MessageBox("Sorry, it's still kinda beta function(\nHowever, you can edit item in xml;)");
		Sorry_Beta();
	}
}
