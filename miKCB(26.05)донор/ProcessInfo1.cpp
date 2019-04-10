#include "StdAfx.h"
#include "ProcessInfo1.h"


CProcessInfo::CProcessInfo(CString path)
{
	File = new CTmiFile();
	File->OpenUsiFile(path);
	cMob = cMpb = 0;
	MashtabTime=0;// Масштаб времени (заголовок)+
	CountParametr=0;// Количество параметров (заголовок)+
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
		StringToFile.Format("ИНДЕКС ИЗДЕЛИЯ\t:\t%s", Title.sIzdel);
		File->WriteToFileString(StringToFile);

		StringToFile.Format("НОМЕР ИЗДЕЛИЯ\t:\t%s", Title.sNumIzdel);
		File->WriteToFileString(StringToFile);

		StringToFile.Format("РАЗДЕЛ\t\t:\t%s", Title.sAbbrRazdel);
		File->WriteToFileString(StringToFile);


		StringToFile.Format("ПРОТЯЖКА\t:\t%s", Title.sProt);
		File->WriteToFileString(StringToFile);


		StringToFile.Format("ДАТА ПРИЕМА\t:\t%s", Title.sCreateTime);
		File->WriteToFileString(StringToFile);
				
		CString sTime, sDate;
		Time = CTime::GetCurrentTime();
		sTime.Format("%s", Time.Format("%H:%M:%S"));
		Time.GetMonth();
		sDate.Format("%s", Time.Format("%d.%m.%y"));
		
		StringToFile.Format("ДАТА ОБРАБОТКИ\t:\t%s \t\t\t\t ВРЕМЯ ОБРАБОТКИ:\t%s\n", sDate, sTime);
		File->WriteToFileString(StringToFile);
	}

	memcpy(&(MashtabTime), (LPCSTR)String + 86, 4);

	memcpy(&(CountParametr), (LPCSTR)String + 90, 2);

	return;
}

void CProcessInfo::FindNeedParamUsi()
{
	//char *filename = new char[32];
	CString filename;

	int z = 0;
	
	for (i = 0; i < CountParametr; i++)
	{
		String = File->ReadStr(32);
		
//		OemToChar(String, (LPSTR)filename);
		filename = String;
		filename.OemToAnsi();


		z = 0;
		while (filename[z] != '\0')
		{
			if ((filename.GetAt(z + 0) == char(0xcc)) || (filename.GetAt(z + 0) == char(0x4d)))
			{
				if ((filename.GetAt(z + 1) == char(0xce)) || (filename.GetAt(z + 1) == char(0x4f)))
				{
					if ((filename.GetAt(z + 2) == char(0xc2)) || (filename.GetAt(z + 2) == char(0x42)))
						{
						if (z)
						{	
							if (filename.GetAt(z -1) == char(0xc5))
								SetGran();
						}

						aMob[cMob].Name = new char[10];
						aMob[cMob].o_byte = 0;
						aMob[cMob].cZnach = 0;
						aMob[cMob].IterOut = 0;
						aMob[cMob].IterIn = 0;

						aMob[cMob].flagOut = aMob[cMob].flag = aMob[cMob].BPeriod = aMob[cMob].EPeriod = 0;

						aMob[cMob].Sr = aMob[cMob].tfirst = 0;
						memcpy(aMob[cMob].Name, (LPCSTR)filename , 10);
						memcpy(&(aMob[cMob].o_byte), (LPCSTR)String + 14, 2);
						
						cMob++;
						priznak = 1;
					//	aMob[cMob].priznakE = priznakE;

					}
				}
				else if (filename.GetAt(z + 1) == char(0xcf))
				{
					if ((filename.GetAt(z + 2) == char(0xc2)) || (filename.GetAt(z + 2) == char(0x42)))
					{
						aMpb[cMpb].Name = new char[10];
						aMpb[cMpb].o_byte = 0;

						aMpb[cMpb].Sr = aMpb[cMpb].tfirst = 0;
						memcpy(aMpb[cMpb].Name, (LPCSTR)filename, 10);
						memcpy(&(aMpb[cMpb].o_byte), (LPCSTR)String + 14, 2);

						cMpb++;
					}
				}
			}
			z++;
		}
	}

	cKadr = 0;
}


void CProcessInfo::FindNeedParamUsl()
{
	CString filename;
	int z = 0;
	for (i = 0; i < CountParametr; i++)
	{
		String = File->ReadStr(256);
	
		filename = String;
		filename.OemToAnsi();
		z = 0;
		while (filename[z] != '\0')
		{
			if ((filename.GetAt(z + 0) == char(0xcc)) || (filename.GetAt(z + 0) == char(0x4d)))
			{
				if ((filename.GetAt(z + 1) == char(0xce)) || (filename.GetAt(z + 1) == char(0x4f)))
				{
					if ((filename.GetAt(z + 2) == char(0xc2)) || (filename.GetAt(z + 2) == char(0x42)))
						{
						if (z)
						{	
							if (filename.GetAt(z -1) == char(0xc5))
								SetGran();
						}

						aMob[cMob].Name = new char[32];
						aMob[cMob].o_byte = 0;
						aMob[cMob].cZnach = 0;
						aMob[cMob].IterOut = 0;
						aMob[cMob].IterIn = 0;

						aMob[cMob].flagOut = aMob[cMob].flag = aMob[cMob].BPeriod = aMob[cMob].EPeriod = 0;

						aMob[cMob].Sr = aMob[cMob].tfirst = 0;
						memcpy(aMob[cMob].Name, filename, 32);
						memcpy(&(aMob[cMob].o_byte), (LPCSTR)String + 100, 2);
					
						cMob++;
						priznak = 1;
						
						//aMob[cMob].priznakE = priznakE;
						break;
					}
				}
				else if (filename.GetAt(z + 1) == char(0xcf))
				{
					if ((filename.GetAt(z + 2) == char(0xc2)) || (filename.GetAt(z + 2) == char(0x42)))
					{

						aMpb[cMpb].Name = new char[32];
						aMpb[cMpb].o_byte = 0;

						aMpb[cMpb].Sr = aMpb[cMpb].tfirst = 0;
						memcpy(aMpb[cMpb].Name, filename, 32);
						memcpy(&(aMpb[cMpb].o_byte), (LPCSTR)String + 100, 2);

						cMpb++;
						break;
					}
				}
			}
			z++;
		}
	}

	cKadr = 0;

}


void CProcessInfo::ReadKadr()
{
	char flag = 1;

	bool TheFirst = true;

	while(1)
	{
		CString StringToProceed;
		String = File->ReadStr(6);
		
		if (!File->RetEof())
		{
			memcpy(&(TimeKadr), (LPCSTR)String, 4);
			memcpy(&(LengthKadr), (LPCSTR)String + 4, 2);
			KadrMashtabTime = (float)TimeKadr / MashtabTime;
		}
		
	
		if (File->RetEof())
		{
			for (i = 0; i < cMob; i++)
			{
				if (aMob[i].flag == 2)
				{
					aMob[i].Sr = aMob[i].Sr / aMob[i].cZnach + aMob[i].tfirst;

					aMpb[i].Sr = aMpb[i].Sr / aMob[i].cZnach + aMpb[i].tfirst;
					CalcKsv(i);
					aMob[i].flagOut = 1;
					StringToProceed.Format(_T("|  %*.4f - %*.4f |           %*.2f Вт            %*.2f Вт  |  %*.2f | "), 12, aMob[i].BTime, 12, aMob[i].ETime, 6, aMob[i].Sr, 6, aMpb[i].Sr, 6, KCB[i]);
					//StringToProceed.Format(_T("|  %*.4f - %*.4f |  %*.2f Вт   %*.2f Вт  |  %*.2f | "), 12, aMob[i].BTime, 12, aMob[i].ETime, 6, aMob[i].Sr, 6, aMpb[i].Sr, 6, KCB[i]);
					if ((aMob[i].IterOut > 5) || (aMob[i].BTime + 0.20 <= KadrMashtabTime))
						mmap.insert(MUL_MAP::value_type(i, StringToProceed));
				}
			}

			printf("\n");
			return;
		}

		//TimeOrZn = ZnMpB = 0;
		
		lStr = "";
		lStr = File->ReadKadr(LengthKadr);
		
		for (i = 0; i < cMob; i++)
		{
			if (cKadr == 0)
				aMob[i].BTime = aMob[i].ETime = (float)TimeKadr / MashtabTime;
			char oldflag = aMob[i].flag;
			if (!aMob[i].cZnach)
			{
				aMob[i].BTime = aMob[i].ETime = (float)TimeKadr / MashtabTime;
				if (aMob[i].o_byte < LengthKadr)
				{
					memcpy(&(aMob[i].tfirst), ((LPCSTR)lStr + aMob[i].o_byte), 4);
					ZnMoB[i]  = aMob[i].tfirst;
				}
				
				if (aMpb[i].o_byte < LengthKadr)
				{
					memcpy(&(aMpb[i].tfirst), ((LPCSTR)lStr + aMpb[i].o_byte), 4);
					ZnMpB[i] = aMpb[i].tfirst;

				}
				if ((aMpb[i].tfirst > MpbDown) && (aMpb[i].tfirst < MpbUp) && (aMob[i].tfirst < MovUp) && (aMob[i].tfirst > MovDown))
				{
					aMob[i].cZnach++;
					aMob[i].flag = 2;
					aMob[i].IterOut++;
				}
				else
				{
					aMob[i].flag = 1;
					aMob[i].IterIn++;
				}

			}
			else
			{
				if (aMob[i].o_byte < LengthKadr)
				{
					ZnMoB[i] = 0;
					memcpy(&(ZnMoB[i]), ((LPCSTR)lStr + aMob[i].o_byte), 4);
				}
				if (aMpb[i].o_byte < LengthKadr)
				{
					ZnMpB[i] = 0;
					memcpy(&(ZnMpB[i]), ((LPCSTR)lStr + aMpb[i].o_byte), 4);
				}
				if ((ZnMpB[i] > MpbDown) && (ZnMoB[i] < MovUp) && (ZnMoB[i] > MovDown) && (ZnMpB[i] < MpbUp)) 
				{
					aMob[i].Sr = aMob[i].Sr + ZnMoB[i] - aMob[i].tfirst;
					aMpb[i].Sr = aMpb[i].Sr + ZnMpB[i] - aMpb[i].tfirst;
					aMob[i].ETime = (float)TimeKadr / MashtabTime;
					aMob[i].cZnach++;
					aMob[i].flag = 2;
					aMob[i].IterOut++;
					aMob[i].IterIn = 0;// ?? ???? ????????

				}
				else
				{
					aMob[i].flag = 1;
					aMob[i].IterIn++;
				}

		
			}

			/*if (aMob[i].ETime + 10 < (float)TimeKadr / MashtabTime)
			{
				if (oldflag == 2)
				{
					aMob[i].Sr = aMob[i].Sr / aMob[i].cZnach + aMob[i].tfirst;
					aMpb[i].Sr = aMpb[i].Sr / aMob[i].cZnach + aMpb[i].tfirst;
					CalcKsv(i);
					aMob[i].flagOut = 1;
					StringToProceed.Format(_T("|  %*.4f - %*.4f |           %*.2f Вт            %*.2f Вт  |  %*.2f | "), 12, aMob[i].BTime, 12, aMob[i].ETime, 6, aMob[i].Sr, 6, aMpb[i].Sr, 6, KCB[i]);
					if ((aMob[i].IterOut > 5)  || (aMob[i].BTime + 30 <= KadrMashtabTime))
					{
						mmap.insert(MUL_MAP::value_type(i, StringToProceed));
						aMob[i].IterIn = 0;
						
					}
					aMob[i].Sr = aMob[i].tfirst = aMob[i].cZnach = aMpb[i].Sr = aMpb[i].tfirst = 0;
					aMob[i].IterOut = 0;
					
				}

			}*/




			if (oldflag != aMob[i].flag)
			{
				if ((aMob[i].flag == 1)&&(oldflag == 2))
				{
					if (aMob[i].IterIn > 3)
					{
						aMob[i].Sr = aMob[i].Sr / aMob[i].cZnach + aMob[i].tfirst;
						aMpb[i].Sr = aMpb[i].Sr / aMob[i].cZnach + aMpb[i].tfirst;
						CalcKsv(i);
						aMob[i].flagOut = 1;
						StringToProceed.Format(_T("|  %*.4f - %*.4f |           %*.2f Вт            %*.2f Вт  |  %*.2f | "), 12, aMob[i].BTime, 12, aMob[i].ETime, 6, aMob[i].Sr, 6, aMpb[i].Sr, 6, KCB[i]);
						if ((aMob[i].IterOut > 5)  || (aMob[i].BTime + 0.20 <= KadrMashtabTime))
						{
							TheFirst = false;
							mmap.insert(MUL_MAP::value_type(i, StringToProceed));
							aMob[i].IterIn = 0;
							
						}
						aMob[i].Sr = aMob[i].tfirst = aMob[i].cZnach = aMpb[i].Sr = aMpb[i].tfirst = 0;
						aMob[i].IterOut = 0;
					}
					else
					{
						aMob[i].flag = oldflag;
					}
				}
				else
				{
					if ((aMob[i].IterOut < 5) && (!TheFirst))
					{
						aMob[i].flag = oldflag;
					}
				/*	else
						aMob[i].BTime = aMob[i].ETime = (float)TimeKadr / MashtabTime;*/
				}
			/*	if ((aMob[i].IterIn > 5) || (!prP))
				{
					if (aMob[i].BPeriod != cKadr)
					{
						if (oldflag == 2)
						{
							aMob[i].Sr = aMob[i].Sr / aMob[i].cZnach + aMob[i].tfirst;
							aMpb[i].Sr = aMpb[i].Sr / aMob[i].cZnach + aMpb[i].tfirst;
							CalcKsv(i);
							aMob[i].flagOut = 1;
							StringToProceed.Format(_T("|  %*.4f - %*.4f |           %*.2f Вт            %*.2f Вт  |  %*.2f | "), 12, aMob[i].BTime, 12, aMob[i].ETime, 6, aMob[i].Sr, 6, aMpb[i].Sr, 6, KCB[i]);
							if ((aMob[i].IterOut > 5)  || (aMob[i].BTime + 30 <= KadrMashtabTime))
							{
								mmap.insert(MUL_MAP::value_type(i, StringToProceed));
								//aMob[i].IterIn = 0;
								prP = true;
							}
							aMob[i].Sr = aMob[i].tfirst = aMob[i].cZnach = aMpb[i].Sr = aMpb[i].tfirst = 0;
							aMob[i].IterOut = 0;
							
							
						}
						aMob[i].BTime = aMob[i].ETime = (float)TimeKadr / MashtabTime;
					}
				}
				else
				{
					aMob[i].flag = oldflag;
				}		*/
			}
		//	else
		//		aMob[i].ETime = (float)TimeKadr / MashtabTime;
		}
		cKadr++;
		
	}
}



void CProcessInfo::CalcKsv(int i)
{
	KCB[i] = (1 + sqrt(aMob[i].Sr / aMpb[i].Sr) )/(1 - sqrt(aMob[i].Sr / aMpb[i].Sr) ); 

}

void CProcessInfo::CalcKsv()
{
	if	(cMob == cMpb)
		for(i = 0; i < cMob; i++)
		{
			KCB[i] = (1 + sqrt(aMob[i].Sr / aMpb[i].Sr) )/(1 - sqrt(aMob[i].Sr / aMpb[i].Sr) ); 

		}
}

void CProcessInfo::WriteKsv()
{

	CString Ole;
	Ole = "+------------------------------+-------------------------------------------+---------+";
	File->WriteToFileString(Ole);

	bool flag = false;
	CString StringToProceed;
	for(i = 0; i < cMob; i++)
	{
		if (aMob[i].flagOut)
		{

			StringToProceed.Format(_T("|       Тстанционное сек       |  %*s        %*s   |    КСВ  |"), 15, aMob[i].Name, 15, aMpb[i].Name);

			File->WriteToFileString(StringToProceed);
			Ole = "|------------------------------+---------------------+---------------------+---------|";
			File->WriteToFileString(Ole);

			for(itr=mmap.begin();itr!=mmap.end();itr++)
			{
				if(itr->first == i)
				{
					File->WriteToFileString(itr->second);	
				}
			
			}
			Ole = "+------------------------------|-----------------------------------------------------+";
			File->WriteToFileString(Ole);
		}



	}
}

void CProcessInfo::ProvWrited()
{
	CString StringToProceed;
	for(i = 0; i < cMob; i++)
	{
		if (!aMob[i].flagOut)
		{
			StringToProceed.Format(_T("Значения параметров(%*s %*s) не соответствуют условиям расчета КСВ"), 15, aMob[i].Name, 15, aMpb[i]);
			File->WriteToFileString(StringToProceed);
		}
	}
}


void CProcessInfo::WriteToFileTxt(CString Str)
{
	File->WriteToFileString(Str);
}


void CProcessInfo::SaveTime(float Time, MoB &Element)
{
	if (*Element.Name == '5')
		Element.NTime = Time + 60;
	else
		Element.NTime = Time - 2;

}

void CProcessInfo::ErrorMessage(CString Str)
{
	File->WriteToFileString(Str);
}

void CProcessInfo::SetGran()
{
	MpbDown = 0.6;
	MpbUp = 2.2; 
	MovDown = 0; 
	MovUp = 0.5;
}


