// miKCB.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "miKCB.h"
#include "miKCBDlg.h"

// 12345.cpp : Defines the class behaviors for the application.
//

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMiKCBApp

BEGIN_MESSAGE_MAP(CMiKCBApp, CWinApp)
	//{{AFX_MSG_MAP(CMiKCBApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMiKCBApp construction

CMiKCBApp::CMiKCBApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMiKCBApp object

CMiKCBApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMiKCBApp initialization

BOOL CMiKCBApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


	if (__argc != 1)
	{
		CString nameFileUSI = __targv[1];
		CString nameDirResult = __targv[2];
		CString nameFilePSP = __targv[3];
		CString nameFileDB = __targv[4];
		std::fstream FilePSP;
		
		//AfxMessageBox(nameFilePSP); 

		CString NewFileName;
				
//		USES_CONVERSION;
		//LPCWSTR nameUsiFile = nameFileUSI;
		//LPCWSTR nameUsiFileWithOutPath = PathFindFileName(nameUsiFile);
			
		
		//char *nameUsiFileWithOutPath = new char[nameFileUSI.GetLength()];
		CString nameUsiFileWithOutPath;
		
		//оптимизировать можно 
		int itr = 0;
		for (itr = 0; itr < nameFileUSI.GetLength(); itr++)
		{
			if  (nameFileUSI.GetAt(itr) == '\\' )
			{
				nameUsiFileWithOutPath = "";
			}
			else
			{
				if  (nameFileUSI.GetAt(itr) == '.' )
				{
					break;
				}
				nameUsiFileWithOutPath += nameFileUSI.GetAt(itr);				
			}
		}


		NewFileName.Format(_T("%s\\КСВ(%s).txt"), nameDirResult, nameUsiFileWithOutPath);

		


		//char  *StrPath = new char[nameFileUSI.GetLength()];
		CString StrPath;
			
		for (itr = 0; itr < nameFileUSI.GetLength(); itr++)
		{
			if  (nameFileUSI.GetAt(itr) == '.' )
			{
				StrPath = "";
			}
			else
			{
				StrPath += nameFileUSI.GetAt(itr);
				
			}
		}
	
		char typeFile;
		if	((StrPath.GetAt(0) == 'u') && (StrPath.GetAt(1) == 's') && (StrPath.GetAt(2) == 'i'))
			typeFile = 1;
		else
		{
			if	((StrPath.GetAt(0) == 'u') && (StrPath.GetAt(1) == 's') && (StrPath.GetAt(2) == 'l'))
				typeFile = 0;
			else
			{
				FilePSP.open(nameFilePSP, std::ios::app);
				FilePSP << "\nОшибка передан не тот тип файла";
				FilePSP.close();
				return true;
			}
		}

		Work = new CProcessInfo(nameFileUSI);
		Work->OpenTxt(NewFileName);
		char Str[100];
		CString StrToF;
		FilePSP.open(nameFilePSP, std::ios::in);
		for(int i = 0; i < 13; i++)
		{
			FilePSP.getline(Str, 100);
			StrToF.Format("%s", Str);
			Work->WriteToFileTxt(StrToF);
//			Work->WriteToWorkTxt(Str);
		}	
		FilePSP.close();
		Work->ReadTitle(true);
		//Work->DBopen(nameFileDB);
		/*if (Work->RetDBErr())
		{
			FilePSP.open(nameFilePSP, std::ios::app);
			//AfxMessageBox("База не открылась, будут использованы статические таррировки 21,10,2015"); 
		 	FilePSP << "\nБаза не открылась, будут использованы статические таррировки 21.01.2015";
			FilePSP.close();
			
		}*/
	/*	else 
			AfxMessageBox("База открылась. Ура ТОВАРИЩИ!!!"); */
	
		if (typeFile)
			Work->FindNeedParamUsi();
		else
			Work->FindNeedParamUsl();
		
		//AfxMessageBox(Work->ReturnPriznak());
		if (Work->ReturnPriznak())
		{
			if (Work->RetDoubl())
			{
			//	AfxMessageBox("\nПроисходит Обработка"); 	
				FilePSP.open(nameFilePSP, std::ios::app);
				FilePSP << "\nПроисходит Обработка";
				FilePSP.close();
				Work->ReadKadr();
				//Work->CalcKsv();
				Work->WriteKsv();
				Work->ProvWrited();
			}
			else
			{
				FilePSP.open(nameFilePSP, std::ios::app);
				//AfxMessageBox(L"МОВ и МПВ не одинаковое количество; файл usi не правильный"); 
		 		FilePSP << "\nМОВ и МПВ не одинаковое количество; файл usi не правильный";
				FilePSP.close();
			}
		}
		else
		{
			FilePSP.open(nameFilePSP, std::ios::app);
			//AfxMessageBox(L"МОВ в USI файле не найден"); 
			FilePSP << "\nПараметры для оценки КСВ в файле не найдены"; 
			FilePSP.close();
		}


		
		return true;
	}
	else
	{

		CMiKCBDlg dlg;
		m_pMainWnd = &dlg;
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
}
