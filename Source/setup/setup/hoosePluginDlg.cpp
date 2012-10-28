// hoosePluginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "setup.h"
#include "hoosePluginDlg.h"


// ChoosePluginDlg dialog

IMPLEMENT_DYNAMIC(ChoosePluginDlg, CDialog)

ChoosePluginDlg::ChoosePluginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ChoosePluginDlg::IDD, pParent)
{

}

ChoosePluginDlg::~ChoosePluginDlg()
{
}

void ChoosePluginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChoosePluginDlg, CDialog)
END_MESSAGE_MAP()


// ChoosePluginDlg message handlers
