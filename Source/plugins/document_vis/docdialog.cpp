// docdialog.cpp : implementation file
//

#include "stdafx.h"
#include "document.h"
#include "docdialog.h"


// docdialog dialog

IMPLEMENT_DYNAMIC(docdialog, CDialog)

docdialog::docdialog(CWnd* pParent /*=NULL*/)
	: CDialog(docdialog::IDD, pParent)
{
}

docdialog::~docdialog()
{
}

void docdialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, document);
	DDX_Control(pDX, IDC_EDIT2, application);
	DDX_Control(pDX, IDC_EDIT3, dir);
	DDX_Control(pDX, IDC_COMBO1, action);
	DDX_Control(pDX, IDC_COMBO2, options);
}


BEGIN_MESSAGE_MAP(docdialog, CDialog)
	ON_BN_CLICKED(IDOK, &docdialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &docdialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &docdialog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &docdialog::OnBnClickedButton3)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// docdialog message handlers

void docdialog::OnBnClickedOk()
{
	extern CString doc,app;
	this->document.GetWindowTextA(doc);
	this->application.GetWindowTextA(app);
	// TODO: Add your control notification handler code here
	//OnOK();
	//Folder Browser code.
    
}

void docdialog::OnBnClickedButton1()
{
/*
	CDirDialog GetApp;
	if(GetApp.DoModal()==IDOK)
	{
		CString pathName = GetApp.GetPathName();
		application.SetWindowTextA(pathName);
	}
*/	
	CFileDialog GetApp(1,0,0,(OFN_FORCESHOWHIDDEN||OFN_PATHMUSTEXIST),0,0,0);
	if(GetApp.DoModal()==IDOK)
	{
		CString pathName = GetApp.GetPathName();
		application.SetWindowTextA(pathName);
	}
	
	/*
	BROWSEINFO bi;
    ZeroMemory(&bi, sizeof(BROWSEINFO));
    bi.hwndOwner = m_hWnd;
    //bi.ulFlags   = BIF_RETURNONLYFSDIRS;
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    BOOL bRet = FALSE;
    TCHAR szFolder[MAX_PATH*2];
    szFolder[0] = _T('\0');
    if (pidl)
    {
        if (SHGetPathFromIDList(pidl, szFolder))
			bRet = TRUE;
        IMalloc *pMalloc = NULL;
        if (SUCCEEDED(SHGetMalloc(&pMalloc)) && pMalloc)
        { 
            pMalloc->Free(pidl); 
            pMalloc->Release();
        }
    }
    //Return value is kept in szFolder.
    AfxMessageBox(szFolder);
	//GetApp.do
	// TODO: Add your control notification handler code here
	*/
}

void docdialog::OnBnClickedButton2()
{
	CFileDialog GetDoc(1,0,0,(OFN_FORCESHOWHIDDEN||OFN_PATHMUSTEXIST),0,0,0);
	if(GetDoc.DoModal()==IDOK)
	{
		CString pathName = GetDoc.GetPathName();
		document.SetWindowTextA(pathName);
	}
	// TODO: Add your control notification handler code here
}

void docdialog::OnBnClickedButton3()
{
	CFileDialog GetDir(1,0,0,(OFN_FORCESHOWHIDDEN||OFN_PATHMUSTEXIST),0,0,0);
	if(GetDir.DoModal()==IDOK)
	{
		CString pathName = GetDir.GetPathName();
		dir.SetWindowTextA(pathName);
	}
	// TODO: Add your control notification handler code here
}

void docdialog::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{

	//action.AddString("SW_SHOW");
	//action.AddString("SW_HIDE");
	//action.SetDlgItemTextA(0,"SW_SHOW");
	//action.SetDlgItemTextA(1,"SW_HIDE");

	CDialog::OnActivate(nState, pWndOther, bMinimized);

	// TODO: Add your message handler code here
}
