// MultiFilez.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MultiFilez.h"
#include "MultiFilezDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

/////////////////////////////////////////////////////////////////////////////
// CMultiFilezApp

BEGIN_MESSAGE_MAP(CMultiFilezApp, CWinApp)
	//{{AFX_MSG_MAP(CMultiFilezApp)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiFilezApp construction

CMultiFilezApp::CMultiFilezApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMultiFilezApp object

CMultiFilezApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMultiFilezApp initialization

BOOL CMultiFilezApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	//#ifdef _AFXDLL
	//	Enable3dControls();			// Call this when using MFC in a shared DLL
	//#else
	//	Enable3dControlsStatic();	// Call this when linking to MFC statically
	//#endif

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	CMultiFilezDlg dlg;
	CString strDirectory = cmdInfo.m_strFileName;

	// Drive hiccup
	if (strDirectory.Right(2) == ":\"")
		strDirectory.Replace("\"", "\\");

	char szDir[MAX_PATH];
	memset(szDir, 0, sizeof(szDir));
	GetLongPathName(strDirectory, szDir, sizeof(szDir));
	strDirectory = szDir;

	if (!strDirectory.IsEmpty()) {
		dlg.m_strWorkingDir = strDirectory;
	}

	m_pMainWnd = &dlg;
	dlg.theApp = this;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
