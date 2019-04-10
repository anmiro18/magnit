#include "StdAfx.h"
#include "TmiFile.h"


CTmiFile::CTmiFile(void)
{
	k = 0;
}


CTmiFile::~CTmiFile(void)
{
	FileKCB.close();
	FileUsi.close();
}

void CTmiFile::OpenUsiFile(CString path)
{
	FileUsi.open(path, std::ios::binary);
}

void CTmiFile::OpenTxtFile(CString path)
{
	CString path1;
	int endpath = 0;
	int itr = 0;

	for (itr = 0; itr < path.GetLength(); itr++)
	{
		if  (path.GetAt(itr) == '.' )
		{
			break;
		}
		path1 += path.GetAt(itr);
	}

	CString NewFileName;
	NewFileName.Format(_T("%s(KCB).txt"), path1);
	FileKCB.open(NewFileName);
}

CString CTmiFile::ReadStr(int length)
{
		CString S = "";
		for( int i = 0; i < length; i++)
		{
			S += FileUsi.get();
		}
		k = FileUsi.tellg();
		if (FileUsi.tellg() < 0)
			return "0xfffffff";

		return S;
}

void CTmiFile::PrintfTellg()
{
	printf("\n ----- %i ----- \n", k);
}


void CTmiFile::WriteToFileString(CString Info)
{
	LPTSTR lpANSI = Info.GetBuffer(Info.GetLength());

	FileKCB << lpANSI << std::endl;

	FileKCB.flush();
}


CString CTmiFile::ReadKadr(int lk)
{
	CString S = "";
	for( int i = 0; i < lk; i++)
	{
	//	FileUsi.get(*(BufUKadr + i));
		S += FileUsi.get();
	}
	return S;
}


int CTmiFile::RetEof()
{
	return FileUsi.eof();
}