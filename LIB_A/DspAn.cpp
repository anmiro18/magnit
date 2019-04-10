// DspAn.cpp : implementation file
//

#include "stdafx.h"
#include "hlibbas.h"
#include "DspAn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDspAn dialog


CDspAn::CDspAn(CWnd* pParent /*=NULL*/)
	: CDialog(CDspAn::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDspAn)
	//}}AFX_DATA_INIT
	Xsh=Ysh=nPd=0;
}


void CDspAn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDspAn)
	DDX_Control(pDX, IDC_STM1, m_STM1);
	DDX_Control(pDX, IDC_ST0, m_ST0);
	DDX_Control(pDX, IDC_ST9, m_ST9);
	DDX_Control(pDX, IDC_ST8, m_ST8);
	DDX_Control(pDX, IDC_ST7, m_ST7);
	DDX_Control(pDX, IDC_ST6, m_ST6);
	DDX_Control(pDX, IDC_ST5, m_ST5);
	DDX_Control(pDX, IDC_ST4, m_ST4);
	DDX_Control(pDX, IDC_ST23, m_ST23);
	DDX_Control(pDX, IDC_ST22, m_ST22);
	DDX_Control(pDX, IDC_ST21, m_ST21);
	DDX_Control(pDX, IDC_ST20, m_ST20);
	DDX_Control(pDX, IDC_ST19, m_ST19);
	DDX_Control(pDX, IDC_ST18, m_ST18);
	DDX_Control(pDX, IDC_ST17, m_ST17);
	DDX_Control(pDX, IDC_ST16, m_ST16);
	DDX_Control(pDX, IDC_ST15, m_ST15);
	DDX_Control(pDX, IDC_ST14, m_ST14);
	DDX_Control(pDX, IDC_ST13, m_ST13);
	DDX_Control(pDX, IDC_ST12, m_ST12);
	DDX_Control(pDX, IDC_ST11, m_ST11);
	DDX_Control(pDX, IDC_ST10, m_ST10);
	DDX_Control(pDX, IDC_ST2, m_ST2);
	DDX_Control(pDX, IDC_ST3, m_ST3);
	DDX_Control(pDX, IDC_ST1, m_ST1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDspAn, CDialog)
	//{{AFX_MSG_MAP(CDspAn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDspAn message handlers

BOOL CDspAn::Create(CRect Area, CString s) 
{
	BOOL b= CDialog::Create(CDspAn::IDD);
	CRect r;
	GetWindowRect(&r);
	int h=r.Height();
	int w=r.Width();
	int H=Area.Height();
	int W=Area.Width();
	r.left = (W-w)/2 + Xsh;
	r.top  = (H-h)/2 + Ysh;
	r.right =r.left+w;
	r.bottom=r.top+h;
	SetWindowText(s);
	SetWindowPos(&wndTopMost, r.left, r.top, w, h, SWP_SHOWWINDOW);

	m_ST4.SetWindowText("Ï Î Ä Ð À Ç Ä Å Ë");
	m_ST5.SetWindowText("Ï À Ð À Ì Å Ò Ð");
	m_ST0.SetWindowText("ÈÌß:");
	m_ST6.SetWindowText("ÍÎÌÅÐ:");
	m_ST2.SetWindowText("ÂÑÅÃÎ:");

	return b;
}

BOOL CDspAn::OnInitDialog() 
{
	myFont(&font,  18, 700, ANSI_CHARSET, "Courier"); 

	CDialog::OnInitDialog();

	m_ST0.SetFont(&font);
	m_ST1.SetFont(&font);
	m_ST2.SetFont(&font);
	m_ST3.SetFont(&font);
	m_ST4.SetFont(&font);
	m_ST5.SetFont(&font);
	m_ST6.SetFont(&font);
	m_ST7.SetFont(&font);
	m_ST8.SetFont(&font);
	m_ST9.SetFont(&font);
	m_ST10.SetFont(&font);
	m_ST11.SetFont(&font);
	m_ST12.SetFont(&font);
	m_ST13.SetFont(&font);
	m_ST14.SetFont(&font);
	m_ST15.SetFont(&font);
	m_ST16.SetFont(&font);
	m_ST17.SetFont(&font);
	m_ST18.SetFont(&font);
	m_ST19.SetFont(&font);
	m_ST20.SetFont(&font);
	m_ST21.SetFont(&font);
	m_ST22.SetFont(&font);
	m_ST23.SetFont(&font);

	m_STM1.SetFont(&font);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDspAn::AddPodr(CString s)
{
	nPd++;
	switch(nPd)
	{
		case 1:		m_ST8.SetWindowText(s); break;
		case 2:		m_ST9.SetWindowText(s); break;
		case 3:		m_ST10.SetWindowText(s); break;
		case 4:		m_ST11.SetWindowText(s); break;
		case 5:		m_ST12.SetWindowText(s); break;
		case 6:		m_ST13.SetWindowText(s); break;
		case 7:		m_ST14.SetWindowText(s); break;
		case 8:		m_ST15.SetWindowText(s); break;
		case 9:		m_ST16.SetWindowText(s); break;
		case 10:	m_ST17.SetWindowText(s); break;
		case 11:	m_ST18.SetWindowText(s); break;
		case 12:	m_ST19.SetWindowText(s); break;
		case 13:	m_ST20.SetWindowText(s); break;
		case 14:	m_ST21.SetWindowText(s); break;
		case 15:	m_ST22.SetWindowText(s); break;
		case 16:	m_ST23.SetWindowText(s); break;
		default:	m_ST23.SetWindowText(s);
	}
}
