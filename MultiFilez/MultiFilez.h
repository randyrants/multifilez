// MultiFilez.h : main header file for the MULTIFILEZ application
//

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMultiFilezApp:
// See MultiFilez.cpp for the implementation of this class
//

class CMultiFilezApp : public CWinApp
{
public:
	CMultiFilezApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiFilezApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMultiFilezApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
