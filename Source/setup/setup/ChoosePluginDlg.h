#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// ChoosePluginDlg dialog

class ChoosePluginDlg : public CDialog
{
	DECLARE_DYNAMIC(ChoosePluginDlg)

public:
	ChoosePluginDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ChoosePluginDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
//public:
	//CListCtrl filelist;
public:
	CListBox FileList;
public:
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
public:
	afx_msg void OnBnClickedOk();
public:
	CEdit ItemName;
public:
	CEdit title;
public:
	afx_msg void OnLbnDblclkList2();
public:
	afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedButton1();
};
