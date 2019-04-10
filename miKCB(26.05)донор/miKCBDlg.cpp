// miKCBDlg.cpp : implementation file
//

#include "stdafx.h"
#include "miKCB.h"
#include "miKCBDlg.h"
// 12345Dlg.cpp : implementation file
//

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy12345Dlg dialog

CMiKCBDlg::CMiKCBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMiKCBDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy12345Dlg)
	m_edit1 = _T("");
	m_edit2 = _T("");
	
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMiKCBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy12345Dlg)
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMiKCBDlg, CDialog)
	//{{AFX_MSG_MAP(CMy12345Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)

	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy12345Dlg message handlers

BOOL CMiKCBDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMiKCBDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMiKCBDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMiKCBDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMiKCBDlg::OnButton1() 
{
	/*m_edit1 = "Ko1";
	m_edit2 = "ko-ko-ko2";
	UpdateData(false);*/
	m_edit1 = "";
	UpdateData(false);

	//p = fileName.GetBuffer( FILE_LIST_BUFFER_SIZE );
	CFileDialog dlgFile(TRUE, NULL, NULL, NULL, "File Usi (*.usi)|*.usi|File Usl (*.usl)|*.usl|");
	//	CFileDialog fileDialog(TRUE,NULL,"*.mak",NULL,"File Mak (*.mak)|*.mak|Resouce Files (*.res)|*.res|");

	//OPENFILENAME& ofn = dlgFile.GetOFN( );
	//ofn.Flags |= OFN_ALLOWMULTISELECT;
	//ofn.lpstrFile = p;
	//ofn.nMaxFile = FILE_LIST_BUFFER_SIZE;


	if (dlgFile.DoModal() == IDOK)
	{

		fileName = dlgFile.GetPathName(); 
		CString StrPath;
		
		
		int itr = 0;
		for (itr = 0; itr < fileName.GetLength(); itr++)
		{
			if  (fileName.GetAt(itr) == '.' )
			{
				StrPath = "";
			}
			else
			{
				StrPath += fileName.GetAt(itr);
				
			}
		}
		
		m_edit1 = fileName;

		if	((StrPath.GetAt(0) == 'u') && (StrPath.GetAt(1) == 's') && (StrPath.GetAt(2) == 'i'))
			typeFile = 1;
		else
			if	((StrPath.GetAt(0) == 'u') && (StrPath.GetAt(1) == 's') && (StrPath.GetAt(2) == 'l'))
				typeFile = 0;
			else	
				fileName = "";

		m_edit1 = fileName;


//		delete StrPath;
//		delete StrFileName;

	}

	UpdateData(false);
	if (PathResult != "")
		RetName();
	//fileName.ReleaseBuffer();

	
}

void CMiKCBDlg::OnButton2() 
{
	char eFla = 0;
//	if (m_edit1 != "")
//	{
		//CString fileName;
		CFileDialog dlgFile(FALSE, "txt", "*.txt", NULL, "File txt (*.txt)|*.txt|");
		char *buf = new char[100];
		BROWSEINFO bi; 
		bi.hwndOwner = m_hWnd; 
		bi.pidlRoot=NULL; 
		bi.pszDisplayName=buf; 
		bi.lpszTitle="Выберите директорию для сохранения результата"; 
		bi.ulFlags=NULL; 
		bi.lpfn=NULL; 

		ITEMIDLIST *itls; 
		if((itls=SHBrowseForFolder(&bi)) != NULL) 
		{
			SHGetPathFromIDList(itls,buf); 
			
			//AfxMessageBox(dlgFile.GetPathName()); 
			PathResult = buf;
			m_edit2 = buf;
		}
		else
		{
			//AfxMessageBox("Путь для сохранения файла не выбран"); 
			eFla = 1;
		}
		if (eFla)
			m_edit2 = "";
		UpdateData(false);
		if (fileName != "")
			RetName();
}




void CMiKCBDlg::OnButton4() 
{
	if ((m_edit1 != "" ) && (m_edit2 != ""))
	{
		Work = new CProcessInfo(fileName);
		
		
		Work->OpenTxt(FilePathName);
		Work->ReadTitle(false);

		if (typeFile)
			Work->FindNeedParamUsi();
		else 
			Work->FindNeedParamUsl();
		//AfxMessageBox(Work->ReturnPriznak());
		if (Work->ReturnPriznak())
		{
			if (Work->RetDoubl())
			{
				Work->ReadKadr();
				//Work->CalcKsv();
				Work->WriteKsv();
				Work->ProvWrited();
				AfxMessageBox("Расчет КСВ удачен, результат записан в выбранную Вами директорию  с именем выбранного файла");
			}
			else
			{
				AfxMessageBox("МОВ и МПВ не одинаковое количество; файл не правильный"); 
				Work->ErrorMessage("МОВ и МПВ не одинаковое количество; файл не правильный");
			//	eFla = 1;
			}
		}
		else
		{
			AfxMessageBox("Параметры для оценки КСВ в файле не найдены"); 
			Work->ErrorMessage("Параметры для оценки КСВ в файле не найдены"); 
		//	eFla = 1;
		}

	}
	else
	{
		if (m_edit1 == "" )
				AfxMessageBox("Исходный файл не выбран"); 
		if (m_edit2 == "")
				AfxMessageBox("Путь для сохранения файла не выбран"); 
	}
	//delete Work;
			
	// TODO: Add your control notification handler code here
	
}


void CMiKCBDlg::RetName()
{
	CString FileNameWithOutPath = fileName;
	
	CString StrNameWithOutPath;
	
	int itr = 0;
	for (itr = 0; itr < FileNameWithOutPath.GetLength(); itr++)
	{
		if  (FileNameWithOutPath.GetAt(itr) == '\\' )
		{
			StrNameWithOutPath = "";
		}
		else
		{
			StrNameWithOutPath += FileNameWithOutPath.GetAt(itr);
			
		}
	}
	
	FilePathName.Format("%s\\%s", PathResult, StrNameWithOutPath);
}
