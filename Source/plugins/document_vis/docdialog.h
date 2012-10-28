#pragma once
#include "afxwin.h"


// docdialog dialog

class docdialog : public CDialog
{
	DECLARE_DYNAMIC(docdialog)

public:
	docdialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~docdialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit document;
public:
	CEdit application;
public:
	afx_msg void OnBnClickedOk();
public:
	CEdit dir;
public:
	CComboBox action;
public:
	CComboBox options;
public:
	afx_msg void OnBnClickedButton1();
public:
	afx_msg void OnBnClickedButton2();
public:
	afx_msg void OnBnClickedButton3();
public:
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};
