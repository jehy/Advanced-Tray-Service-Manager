// setupDlg.h : header file
//

#pragma once

#define ADDSUBMENU		1
#define ADDSUBITEM		2
#define DELETEITEM		3
#define EDITITEM		4
#define EDITSUBITEM		5
#include "afxcmn.h"


// CsetupDlg dialog
class CsetupDlg : public CDialog
{
// Construction
public:
	CsetupDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SETUP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl tree;
public:
	afx_msg void OnBnClickedButton1();
public:
	afx_msg void OnTvnEndlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedButton2();
public:
//	afx_msg void OnNMRclickTree1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedButton3();
public:
	afx_msg void OnBnClickedButton4();
public:
//	afx_msg void OnTvnSelchangingTree1(NMHDR *pNMHDR, LRESULT *pResult);
public:
//	afx_msg void OnNMSetfocusTree1(NMHDR *pNMHDR, LRESULT *pResult);
public:
//	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnTvnBegindragTree1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnBnClickedCancel();
public:
//	afx_msg void OnNMRdblclkTree1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnNMRclickTree1(NMHDR *pNMHDR, LRESULT *pResult);
public:
//	afx_msg void OnNMReturnTree1(NMHDR *pNMHDR, LRESULT *pResult);
public:
//	afx_msg void OnTvnKeydownTree1(NMHDR *pNMHDR, LRESULT *pResult);
public:
//	afx_msg void OnTvnBeginlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult);
public:
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
public:
	afx_msg void OnBnClickedButton6();
public:
	afx_msg void OnBnClickedButton5();
public:
	afx_msg void OnBnClickedButton7();
};
