#include "StdAfx.h"
#include "ProcessInfo1.h"


CProcessInfo::CProcessInfo(CString path)
{
	File = new CTmiFile();
	File->OpenUsiFile(path);
	cMob = cMpb = 0;
	MashtabTime=0;// Ìàñøòàá âðåìåíè (çàãîëîâîê)+
	CountParametr=0;// Êîëè÷åñòâî ïàðàìåòðîâ (çàãîëîâîê)+
	TimeKadr = 0;
	LengthKadr = 0;
	priznak = 0;
	for (int i = 0; i < 10; i++)
	{
		ZnMpB[i] =  ZnMoB[i] = 0;
	}
	prP = false;
	MpbDown = 2;
	MpbUp = 25; 
	MovDown = 0; 
	MovUp = 10;
}


CProcessInfo::~CProcessInfo(void)
{
	mmap.erase(mmap.begin(), mmap.end());
	for(i = cMpb - 1; i > -1; i--)
	{
		delete aMpb[i].Name;
	}
	for(i = cMob - 1; i > -1; i--)
	{
		delete aMob[i].Name;
	}

	delete File;
}



void CProcessInfo::OpenTxt(CString path)
{
	File->OpenTxtFile(path);
}

char CProcessInfo::ReturnPriznak()
{
	return priznak;
}

char CProcessInfo::RetDoubl()
{
	if	(cMob == cMpb)
		return 1;
	return 0;
}

void CProcessInfo::ReadTitle(bool PriznakStartManager)
{
	String = File->ReadStr(94);
		
	i=0;
	int k=0;

	memcpy(&(Title.sKeyWord)	, (LPCSTR)String, 10);

	memcpy(&(Title.sIzdel)		, (LPCSTR)String + 10, 11);

	memcpy(&(Title.sNumIzdel)	, (LPCSTR)String + 21, 11);

	memcpy(&(Title.sAbbrRazdel)	, (LPCSTR)String + 32, 17);

	memcpy(&(Title.sProt)		, (LPCSTR)String + 49, 11);

	memcpy(&(Title.fTbegin)		, (LPCSTR)String + 60, sizeof(float));
	memcpy(&(Title.fTend)		, (LPCSTR)String + 60 + sizeof(float), sizeof(float));
	memcpy(&(Title.sCreateTime)	, (LPCSTR)String + 60 + sizeof(float)*2, 16);


	if (!PriznakStartManager)
	
	{	

		CString StringToFile;
		StringToFile.Format("ÈÍÄÅÊÑ ÈÇÄÅËÈß\t:\t%s", Title.sIzdel);
		File->WriteToFileString(StringToFile);

		StringToFile.Format("ÍÎÌÅÐ ÈÇÄÅËÈß\t:\t%s", Title.sNumIzdel);
		File->WriteToFileString(StringToFile);

		StringToFile.Format("ÐÀÇÄÅË\t\t:\t%s", Title.sAbbrRazdel);
		File->WriteToFileString(StringToFile);


		StringToFile.Format("ÏÐÎÒßÆÊÀ\t:\t%s", Title.sProt);
		File->WriteToFileString(StringToFile);


		StringToFile.Format("ÄÀÒÀ ÏÐÈÅÌÀ\t:\t%s", Title.sCreateTime);
		File->WriteToFileString(StringToFile);
				
		CString sTime, sDate;
		Time = CTime::GetCurrentTime();
		sTime.Format("%s", Time.Format("%H:%M:%S"));
		Time.GetMonth();
		sDate.Format("%s", Time.Format("%d.%m.%y"));
		
		StringToFile.Format("ÄÀÒÀ ÎÁÐÀÁÎÒÊÈ\t:\t%s \t\t\t\t ÂÐÅÌß ÎÁÐÀÁÎÒÊÈ:\t%s\n", sDate, sTime);
		File->WriteToFileString(StringToFile);
	}

	memcpy(&(MashtabTime), (LPCSTR)String + 86, 4);

	memcpy(&(CountParametr), (LPCSTR)String + 90, 2);

	return;
}

void CProcessInfo::FindNeedParamUsi()
{
	for (i = 0; i < CountParametr; i++)
	{
		String = File->ReadStr(32);
		CString filename = String;
		filename.OemToAnsi();
		aMob[cMob].Name = new char[10]; // по идее только это
		memcpy(aMob[cMob].Name, (LPCSTR)filename , 10);
	}
}


void CProcessInfo::FindNeedParamUsl()
{
	for (i = 0; i < CountParametr; i++)
	{
		String = File->ReadStr(256);
		CString filename = String;
		filename.OemToAnsi();
		aMob[cMob].Name = new char[32];
		memcpy(aMob[cMob].Name, filename, 32);
	}
}


void CProcessInfo::ReadKadr()
{
	while(1)
	{
		CString StringToProceed;
		String = File->ReadStr(6);

		if (File->RetEof())
		{
			//здесь при последнем случае подсчёт
			return;
		}

		//TimeOrZn = ZnMpB = 0;
		memcpy(&(TimeKadr), (LPCSTR)String, 4);
		memcpy(&(LengthKadr), (LPCSTR)String + 4, 2);
		KadrMashtabTime = (float)TimeKadr / MashtabTime;
		if (LenghtKadt == 0) continue;
		
		lStr = File->ReadKadr(LengthKadr);
		
		//вот здесь логика по обрабоке кадра
		//и для теста используй WriteToFileTxt(CString) эту функцию
		
	}
}

void CProcessInfo::WriteToFileTxt(CString Str)
{
	File->WriteToFileString(Str);
}


