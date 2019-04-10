// 12345Dlg.h : header file
//

#if !defined(AFX_12345DLG_H__6556B537_7493_42CE_B5D1_19A59435A879__INCLUDED_)
#define AFX_12345DLG_H__6556B537_7493_42CE_B5D1_19A59435A879__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy12345Dlg dialog

class CMiKCBDlg : public CDialog
{
//Данные добавленные мною
private:
	CProcessInfo *Work;
	CString fileName;
	wchar_t* p;
	char typeFile;
	CString FilePathName;
	CString DBPath;
	CString PathResult;
	void RetName();

// Construction
public:
	CMiKCBDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy12345Dlg)
	enum { IDD = IDD_MY12345_DIALOG };
	CString	m_edit1;
	CString	m_edit2;

	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy12345Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy12345Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_12345DLG_H__6556B537_7493_42CE_B5D1_19A59435A879__INCLUDED_)
