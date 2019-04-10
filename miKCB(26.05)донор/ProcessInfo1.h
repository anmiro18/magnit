#pragma once
struct MoB
{//структуры особо не нужны, разве что некоторые поля тип имени(возможно) и видимо всё, так как параметр 1 и смещение всегда будет в 0
	char *Name;
	int o_byte;
	float Sr;
	float tfirst;
	int cZnach;
	char flag;
	int BPeriod;
	int EPeriod;
	float BTime;
	float ETime;
	float NTime;
	char flagOut;
	int IterOut;
	int IterIn;
	//char priznakE;
};	

struct MpB
{
	char *Name;
	int o_byte;
	float Sr;
	float tfirst;
};

struct SERVICE_INFO
{
	char sKeyWord[10];
	char sIzdel[11];
	char sNumIzdel[11];
	char sAbbrRazdel[17];
	char sProt[11];
	float fTbegin;
	float fTend;
	char sCreateTime[16];
};

typedef std::multimap<int, CString, std::less<int> > MUL_MAP;
#define TitleFile	struct SERVICE_INFO

class CProcessInfo
{
private:
	CTmiFile *File;
	CString String;
	CTime Time;
	
	int i;
	MoB aMob[10];
	MpB aMpb[10];
	TitleFile Title;


	//CString DBIzdel, DBNumIzdel;
	int cMob, cMpb;
	int MashtabTime;// ??????? ??????? (?????????)+
	int CountParametr;// ?????????? ?????????? (?????????)+
	int MASK;// ????? ??? ????????? ?? ?????+
	bool prP; //??????? ??????? ????????
	
	MUL_MAP mmap;
	MUL_MAP::const_iterator itr;
	

	int cKadr;
	int LengthKadr;
	float ZnMoB[10], ZnMpB[10], KadrMashtabTime;
	int TimeKadr;
	CString lStr;
	char priznak;

	float MpbUp, MpbDown, MovUp, MovDown;
	float KCB[];
	void CalcKsv(int NumberMpv);
	void SaveTime(float Time, MoB &Element);
	void SetGran();
	
public:

	void ProvWrited();
	CProcessInfo(CString path);
	~CProcessInfo(void);
	void ReadTitle(bool PriznakStartManager);
	
	void FindNeedParamUsi();
	void FindNeedParamUsl();
	void ReadKadr();
	void CalcKsv();
	void WriteKsv();
	void OpenTxt(CString path);
	void WriteToFileTxt(CString Str);
	char ReturnPriznak();
	char RetDoubl();
	void ErrorMessage(CString Str);
	
};

