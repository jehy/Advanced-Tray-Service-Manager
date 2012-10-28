// document.h : main header file for the document DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CdocumentApp
// See document.cpp for the implementation of this class
//
//char* ShowDlg();
class CdocumentApp : public CWinApp
{
public:
	CdocumentApp();
	~CdocumentApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

