// DBaseTMI.h: interface for the DBaseTMI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBASETMI_H__1E948468_FDB0_4E40_94BD_15C753EDDB9B__INCLUDED_)
#define AFX_DBASETMI_H__1E948468_FDB0_4E40_94BD_15C753EDDB9B__INCLUDED_
#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma pack(1)
enum TYPE_TARIR {UNDEF,APP,KOEFF,MIX,OM};
enum TYPE_FILE_DAO {UNK,MDB,ISAM,ODBC};

class AFX_EXT_CLASS DBaseTMI  
{
public:
    TYPE_FILE_DAO m_nDatabaseType;
    DBaseTMI();
	~DBaseTMI();
	BOOL Open(CString name);
	BOOL OpenIsamFile(CString name);
	BOOL OpenMdbFile(CString name);
	BOOL IsOpen();
	void Close();

	CString GetNameDb() { return m_strDatabase;}
	CString GetStrConnect() { return m_strConnect;}
	CString GetNameIsam() { return m_nameIsam;}
	CDaoRecordset* GetRecordset(); 
    CDaoDatabase*  GetDB(){return &m_dtb;}
//	long GetCountRec() {return m_nCountRec;}

	void DaoErrorMsg(CDaoException* e);
	BOOL GetListFromTable(CStringList* list);
	BOOL OpenRecordset(CString strSelect,BOOL prExclusive);
    void CloseRecordset();
	BOOL GetListRecordset(CString strSelect, CStringList* listData);
   	BOOL EditRecordset(COleVariant* listEdit);
	BOOL ClearRecordset();
	
private:

    CDaoDatabase m_dtb;
	CString      m_strDatabase;
	CString      m_strConnect;
	BOOL         m_bConnected;
	long         m_nFields;
	CString      m_strQuery;
	CString      m_nameIsam;
	

    CDaoRecordset* m_pRecordset;
	long          m_nCountRec;

};

/////////////////////////////////////////////////////////////////////////

             ///    ���������
struct AFX_EXT_CLASS DataSetBits         //  ������ �� ������ � ���� 
{
   CString   setBits;             // ������ ����
   int       nKanal;              // ����� � ������� 
   int       razr;                // ������
};

struct AFX_EXT_CLASS TarirKoeff             // ������������ ��� ���������
{

	float a;                      // ��2
	float b;                      // ��
	float c;                      // � 

};

struct AFX_EXT_CLASS PointApproksimation    // ����� �������������
{
	float kod;                    // ��� ��� % ��� ������ ��� ��� ����-������
	float fiz;                    // ���������� ��������
};


class AFX_EXT_CLASS DataForTarir           //������ ��� ����������� ���������
{
public:

	DataForTarir();
	~DataForTarir();

    CString index;                  // ������ ���������
	CString typeParam;                // ��� ���������
	CString zavNum;                 // ��������� �����
    DataSetBits adr;                // ����� � ����
    CString unit;                   // ������� ���������
	TYPE_TARIR typeT;               // ��� ���������
	CString dataCorrect;            // ���� ���������
	float min;                      // min ���������  
	float max;                      // max ���������  
    TarirKoeff* koeff;              // ������ �� ������������� 
	int numPoints;                  // ����� ����� �������������
	CString unitApp;                // ������� ���� �������������
	PointApproksimation* pointsApp; // ������ ����� �������������
	float Rdop;                     // R ��������������
	float Rkab;                     // R ������ 
	float R0;
	float deltaR;
	
	void Clear();                   // ��������� ���������� � ��������� "��������� �� ����������"
	BOOL SetTypeTarir(TYPE_TARIR type, int numPoint = NULL); //���������� ��� ���������   
   
private:

	BOOL Control();                 // �������� ������������ ����������
	void SetUndefType();
 	void InitKoeff();
	void InitPointsApp();
};

////////////////////////////////////////////////////////////////////////////////





struct AFX_EXT_CLASS DataForEssential    // ������ ��� ������ ��������������
{
   int       point;               // ����� ����������(�)/�������������(�)
   float     deltS;               // ������ �������������� 
   float     deltD;               // ������ ������������� 
   CString   typePrint;           // ����� �� ������ (% ��� ���)
};

struct AFX_EXT_CLASS DataForIshodn      // ������ ��� ������ ���������
{
   CString typeEstimate;          // ��� ��������� 
   float min;                     // ���(�)/�������� ��������(�) 
   float max;                     // ���(�)
   float delta;                   // �������
   CString unitEstimate;          // ������� ������(% ��� ���)
};

struct AFX_EXT_CLASS DataForView        // ������ ��� �����������
{
   CString placeInShip;           // ����� �� ������� 
   CString stream;                // �����
   CString typeView;              // ��� ��������� ��� ������  
   int     length;                // ����� 
};

struct AFX_EXT_CLASS DataForViewOnInterval  //  ������ ��� ����������� �� ���������
{
	float min;                    // ���
	float max;                    // �������� 
	float timeBeg;                // ������ ���������
	float timeEnd;                // ����� ��������� 
};



struct AFX_EXT_CLASS MeanKod                // �������� ������� ����������
{
	int kod;                      // ���
	CString  znKod;               // ��� ��������
	
};
struct AFX_EXT_CLASS DataForDeshifr      //  ������ ��� ����������
{
   CString typeParam;            //��� ���������
   int     typeDeshifr;          // ����� ���������   
   int     delta;                //������ 
   CString unit;                 // ������� ��������� 
};
struct AFX_EXT_CLASS DataForAdrInKadr       // ������ ��� ������������ ���������
{
	short kodPsb;                // �������� ��� ���
	int posInKadr;               // ������ ������� � ����� 
    int lamelSSK;                // ������ ������ ��� (-1 ���� 2 �������)
	int  razr;                   // ������   (-1 ���� ���������� ��������)
	int  f;                      // ����������������� 
	CString strAdr;             // ������ ������, ��������� �� ��������� 
};
class AFX_EXT_CLASS MainCharParametr               // ����� �������� ���������� �� ���������
{
public:
	MainCharParametr();
	~MainCharParametr();

   CString        indeks;          // ������
   CString        identif;        // �������������
   CString        name;           // ��������
   DataForDeshifr desh;           // ������ ��� ���������� 
   int            numPsb;
   DataForAdrInKadr* adrInKadr;     // ������ ��� ������������

   void Clear();                      // �������� ������
   BOOL SetNumPsb(int n);            // ���������� ���-�� ��������� ���
private:
   BOOL Control();
};

struct AFX_EXT_CLASS CharCurrentJob          // ������ �� ������� ��������� ������
{
   long    personalKey;           // �������������� ���� - ��� ��� ������ � �����
   CString nameRazdel;            // �������� �������
   CString nameProt;              // �������� ��������
   CString nameTask;              // �������� ������ 
   CString regObr;                // ����� ��������  
   CString strPSB;                // ��������� �����
   CStringList listContentTask;   // ������ ������� ���������� � ����� �� ���������
};

struct AFX_EXT_CLASS KalibrParam             // ������ �� ���������� ����������
{
	CString index;                // ������
	int min;                      // ��� �������� ����
	int max;                      // ���� �������� ���� 
};

struct AFX_EXT_CLASS CharPSB                       // ������ �� ���������� �����
{
	long key;                     // ���������� ����
	CString name;                 // �������� ���
	short kodInKadr;              // ��� � �����
};

struct AFX_EXT_CLASS Razdel             // ������ �� ��������
{
    CString nameRazdel;                   //��������
	CString abbrevRazdel;                 // ������������
};

struct AFX_EXT_CLASS ParamInList        // ������ �� ���������� � �������
{
	CString indeks;                // ������
	CString typePrint;             // ��� ������ (%?, ���, ���)  
	int currentDelta;              // ������ �������������� - ���� ��������, 
	                               // ���� ��� �������������� �������
};
struct AFX_EXT_CLASS AdrInKadrBCVM     // ����� ��������� � �������� �������
{
	int nKadr;                      // �����(��� ���)�����
	int nRow;                       // ����� ������
	int nWord;                    // ����� ����� � ������
	short bitBeg;                   // ����� ������� ����
	short bitEnd;                   // ����� ���������� ����
};

struct AFX_EXT_CLASS ParametrKPUD    //������ �� ���������� ����
{
    CString name;           // ��������
	CString unit;           // ��-�� ���������
	short mst;              // �������
	float ka;               // �� 
	float kb;               // �� 
	int nAdr;               // ����� �������� ������� �� ���� ������
	AdrInKadrBCVM* adr;     // ������ �������

};

struct AFX_EXT_CLASS CommandSUBS      //������ �� �������� ����
{
    CString nameCommand;            // �������� �������
	CString abonent;                // ������� 
	CString kod;                    // ��� �������
	CString comment;                // ��������
	short   type;                   // ��� �������
	CString nKadr;                  // ��� �����
	int     nWord;                  // ����� ����� � ������
	short nHalfWord;                // ����� ���������
	short nRazr;                    // ����� ������� �������
	short meanRazr;                 // �������� ��������
	short nRazrEnd;                 // ����� ���������� �������
};

struct AFX_EXT_CLASS CharIzdel
{
    CString nameIzdel;               // �������� �������
	CString numIzdel;                // ����� �������
	CString typeBort;                // ��������� ����� 

};
struct AFX_EXT_CLASS CharAlg
{
	CString nameAlg;                  //����������� ��������� (3 �������) 
	CString nameProgr;                // �������� ��������������� ��������� ���������
	CString prEssential;              // ������� ������������� ��������� �������������� (+ ��� -)
	CString typeFile;                 // ������ ����� �� �����
};
struct AFX_EXT_CLASS Diapazon
{
    float PointBeg;                   //��������� ����� ���������
    float PointEnd;                   // �������� ����� 
	CString MeanDiapazon;             // �������� ��������� 
};

/////////////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS DBbits
{

public:

  DBbits();
  ~DBbits();

              // ��������� ( �������� ����� ������� SET.. �� ���� ����� �������� �������� 
              // ���������� �������� ���� ������ ���� ������� ���� �������)

  BOOL SetDirDB(CString nameDirDb);   // +���������� ������� ���������� �������� ���� ��

  BOOL GetAllIzdel(CStringList* listIzdel);    // +���� ������ �������, �� �-��� ���� ��
  BOOL GetAllNumForCurrentIzdel(CStringList* listNumIzdel); //+ ���� ������  � ����� �� �������������� �������, ��� ������� ���� ��

  BOOL SetIzdel(CString nameCurrentIzdel);     // +���������� �������, � ������� � ���������� ����� ������� ������     
  BOOL SetNumIzdel(CString numIzdel);          // +���������� � ������
  BOOL SetIzdel(CString nameCurrentIzdel,CString numForCurrentIzdel); //+���������� ����� ������� � �
  BOOL GetCharIzdel(CharIzdel* charCurrentIzdel); // ���� �������������� ������� �� ��
 
                   // �������� ����
  BOOL OpenDB(); // +������� ���� ������ �� ����� ������������� ������� � ������
                         //+ ������� ���� �� ��������� ���������� ������
  BOOL OpenDB(CString nameDirDb,CString nameCurrentIzdel,CString numForCurrentIzdel);
  BOOL CloseDB(); // +������� ��
  BOOL GetListPO(CStringList* listPO);  // ������ ������ �� ��� ��������� ������� ������� 
  BOOL GetCharForAlgObr(CString nameAlgObr, CharAlg* charAlg);
              // ������ ��������� �����������

  BOOL GetListSets(CStringList* listSets);      // +���� ������ �������� � ����
  BOOL GetListTypeParam(CStringList* listTypes); // +���� ������ ��������� ����� ����������
      
              // ��������� ������ ������� ���������� �� ���������

  BOOL GetListAllParam(CStringList* listParam);   // +���� ������ ���� ���������� �� ��
  BOOL GetListAllParamBITS(CStringList* listParam); // +���� ������ ������ ���������� ����
  BOOL GetListAllParamCM(CStringList* listParam); // ���� ������ ������ ���������� �������� ��������
  BOOL GetListParamFromSet(CString setBits, CStringList* listParam); // +���� ������ ������ ���������� �� ����������� �������
  BOOL GetListParamKPUD(CStringList* listParam);  // ���� ������ ���������� ����
  BOOL GetListCommandSUBS(CStringList* ListCommand);  //���� ������ ������ ��� 
   
                //    ��������� � ����

  BOOL GetDataSetBitsForParam(CString index, DataSetBits* adrInBits);  // +���� ����� ��������� � ���� 
  
               //     ������������ � ����������
  int GetAllPSB(CharPSB** charPsb); // ���� ��������� ����� � �� ��������������
  BOOL GetAdrParametrAndDataForDeshifr(MainCharParametr* charParam);  //+ ������ ������ ��� ������������ � ����������
  
              ///        ���������
  int  GetParamFromSet(CString nameSet,DataForTarir** tarir);  // +���� ��������� � ����������� � ��������� �������
  BOOL GetTarirForParam(DataForTarir* tarir); //+ �������� ��������� ��� ���������
  BOOL SetTarirForParam(DataForTarir* tarir); //+���������� ��������� ��� ���������
  int GetConstZnForParam(CString nameParam, MeanKod** listZn);  //������ ����������� �������� ���������
  int GetListDiapazonForParam(CString nameParam,Diapazon** listDiapazon); //������ ����������� �������� ����������� ��������� �� ���������� 
 
            ///         ����������
  BOOL GetKalibrParamForParametr(CString index, KalibrParam* kalibr0, KalibrParam* kalibr100, KalibrParam* kalibr50); // ���� ��������� ���������� ��� ���������
  BOOL GetKalibrParamForSetBits(CString setBits, KalibrParam* kalibr0, KalibrParam* kalibr100, KalibrParam* kalibr50); // ���� ��������� ���������� ��� �������
  
  
            /// ������ �� �������� � ������� ���������� 
                       ////+ ������ ���������� ����������� ������� �� ���������
  BOOL GetListContentTask(CString nameTask, CStringList* listContentTask); 
                       // ������ ���������� ������ ���������� 
  int GetContentListParam(CString nameListParam, ParamInList** listParam);  
  BOOL GetAllListsParam(CStringList* listNamesListParam); // ������ ������ ������ �������� ������� ����������
  

            ///      ������ ��� ������ �� ��������

  int  GetListRazdel(Razdel** listRazdel);  //+ ���� ������ �������� ���������
  BOOL GetNameRazdelByAbbrev(CString abbrev, CString* nameRazdel); //������ ������ �������� ������� �� ������������
  BOOL SetCurrentRazdel(CString currentRazdel);   // +���������� ������� ������
  BOOL GetListProtForCurrentRazdel(CStringList* listProt);    //+ ���� ������ �������� ��� �������� ������� 
  BOOL SetCurrentProt(CString nameProt);//+���������� ������� ������ �� �������� ��������
  


          ///    ������  �� ���������� �������
  BOOL SetCurrentProt(long personalKey);  // +���������� ������� ������(������ � ��������) �� ����� �� ��������� ������
  CharCurrentJob* GetCharCurrentJob(){return &currentJob;};     //+ ���� �������������� ������� ������    

         ///     ������ ��������� �� ��������
                    // +�������� ��� ������ ��������� ����������� ��������� �� ����� ������������� ������, ����
                    //  ������ ����� �� �����������, ���������� �������� ��������
  BOOL GetIshodnForParamOnCurrentJob(CString indeks, DataForIshodn* dtIsh);

         ///     ������ ��� ����������� �� ��������

  BOOL GetDateForView( CString indeks,DataForView* dtView); // ������ ����� ������ ��� ����������� ���������
  int GetDateForViewOnInterval(CString indeks, DataForViewOnInterval** dtIntervalView); // ������ ��������� � ���������

         /// ������ ��� ������ � ����

 // int GetCommandFromBCVM(CommandBCVM** dtCommand);   // ������ ������ ������ ������ 
  BOOL GetDataForParametrKPUD(ParametrKPUD* parametr); //���� ������ �� ��������� ����
  BOOL GetDataForCommandSUBS(CommandSUBS* ptrCommand);        // ���� ������ �� ������� ���
  BOOL GetVersDB(CStringList* listVersion);   // ���� ������ ��
private:

  DBaseTMI  m_dataBase;

  CString   nameDirDbase;
  CString   currentIzdel;
  CString   numCurrentIzdel;

  CString   m_nameDB;

  CString   currentPSB;

  CharCurrentJob currentJob;

  LONG  keyCurrentRazdel;
  LONG  keyCurrentTask;
  LONG  keyCurrentListParam;
  LONG  keyCurrentParam;

  BOOL  ControlCorrectDBbyTableIzdel();  
  void  Clear();
  BOOL  ControlCorrectSettingDB();
  BOOL  GetListIDForOneParametr(CString identParam,CStringList* list,CString strQ1, CString strQ2);
  BOOL SetKoeffForParametr(DataForTarir* tarir,long key);
  BOOL SetApproksForParametr(DataForTarir* tarir,long key);
  BOOL GetKeyParam(CString index, long* keyParametr);
  BOOL GetCharProt(CString strConnect);
  BOOL ReadIshFromDB(CStringList& listIsh,DataForIshodn* dtIsh);
  BOOL GetDataForViewFromStr(CString strData,DataForViewOnInterval* dtView);
  
};

#endif // !defined(AFX_DBASETMI_H__1E948468_FDB0_4E40_94BD_15C753EDDB9B__INCLUDED_)
