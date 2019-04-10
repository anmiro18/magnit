#if !defined(AFX_DSPAN_H__B6FE6DBA_7364_4689_BA30_3FFF20595BAC__INCLUDED_)
#define AFX_DSPAN_H__B6FE6DBA_7364_4689_BA30_3FFF20595BAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DspAn.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CDspAn dialog

class CDspAn : public CDialog
{
// Construction
public:
	void AddPodr(CString s);
	CDspAn(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDspAn)
	enum { IDD = IDD_DIALOG1 };
	CStatic	m_STM1;
	CStatic	m_ST0;
	CStatic	m_ST9;
	CStatic	m_ST8;
	CStatic	m_ST7;
	CStatic	m_ST6;
	CStatic	m_ST5;
	CStatic	m_ST4;
	CStatic	m_ST23;
	CStatic	m_ST22;
	CStatic	m_ST21;
	CStatic	m_ST20;
	CStatic	m_ST19;
	CStatic	m_ST18;
	CStatic	m_ST17;
	CStatic	m_ST16;
	CStatic	m_ST15;
	CStatic	m_ST14;
	CStatic	m_ST13;
	CStatic	m_ST12;
	CStatic	m_ST11;
	CStatic	m_ST10;
	CStatic	m_ST2;
	CStatic	m_ST3;
	CStatic	m_ST1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDspAn)
	public:
	virtual BOOL Create(CRect Area, CString s);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int Ysh;
	int Xsh;
	CFont font;
	int   nPd;
	// Generated message map functions
	//{{AFX_MSG(CDspAn)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSPAN_H__B6FE6DBA_7364_4689_BA30_3FFF20595BAC__INCLUDED_)
