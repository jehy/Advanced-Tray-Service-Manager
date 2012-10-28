// document.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "document.h"
#include "docdialog.h"
//#include "dirdialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
char* result;

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/*		extern "C" BOOL PASCAL EXPORT ExportedFunction()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		// normal function body here
	}
*/


//CdocumentApp

BEGIN_MESSAGE_MAP(CdocumentApp, CWinApp)
END_MESSAGE_MAP()


// CdocumentApp construction

CdocumentApp::CdocumentApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CdocumentApp object

CdocumentApp theApp;


// CdocumentApp initialization

BOOL CdocumentApp::InitInstance()
{
	
	//theApp.DoMessageBox("Library initialized!",MB_OK,0);
	return TRUE;
}

CdocumentApp::~CdocumentApp()
{
	delete(result);
}
//
char* DlgNewItem()
//extern "C" char* PASCAL EXPORT ShowDlg()
//extern "C" __declspec(dllexport)char* ShowDlg()
{  
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	//theApp.DoMessageBox("Library&Function loaded!",MB_OK,0);
	extern CString app,doc;
	docdialog* c;
	c=new(docdialog);
	c->DoModal();
	//theApp.DoMessageBox(doc+app,MB_OK,0);
	CString res;
	res+=doc;
	res+=app;
//	CWinApp::InitInstance();
	result=new char[res.GetLength()+1];
	strcpy_s(result,res.GetLength()+1,res);
	//c->();
	delete(c);
	return result;//res.CopyChars;
	//delete(ret);
	// normal function body here
}