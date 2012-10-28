#pragma once
#include "afxwin.h"


// EditItemDlg dialog

class EditItemDlg : public CDialog
{
	DECLARE_DYNAMIC(EditItemDlg)

public:
	EditItemDlg(int mode, CWnd* pParent = NULL);   // standard constructor
	int mode;
	virtual ~EditItemDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
//public:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	CEdit title;
public:
	CComboBox setup_plugin;
public:
	CComboBox run_plugin;
public:
	CButton monitor;
public:
	CEdit XmlText;
public:
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
//public:
	//afx_msg void OnPaint();
public:
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
	afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedOk();
};
