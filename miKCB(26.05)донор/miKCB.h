// miKCB.h : main header file for the 12345 application
//

#if !defined(AFX_12345_H__2265F13B_C6FA_495D_AD5E_36801E4787EF__INCLUDED_)
#define AFX_12345_H__2265F13B_C6FA_495D_AD5E_36801E4787EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMiKCBApp:
// See miKCB.cpp for the implementation of this class
//

class CMiKCBApp : public CWinApp
{
private:
	CProcessInfo *Work;
public:
	CMiKCBApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMiKCBApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMiKCBApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_12345_H__2265F13B_C6FA_495D_AD5E_36801E4787EF__INCLUDED_)
