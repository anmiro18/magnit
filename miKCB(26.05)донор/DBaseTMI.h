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

             ///    ТАРИРОВКИ
struct AFX_EXT_CLASS DataSetBits         //  Данные по адресу в БИТС 
{
   CString   setBits;             // прибор БИТС
   int       nKanal;              // канал в приборе 
   int       razr;                // разряд
};

struct AFX_EXT_CLASS TarirKoeff             // Коэффициенты для параметра
{

	float a;                      // ах2
	float b;                      // вх
	float c;                      // с 

};

struct AFX_EXT_CLASS PointApproksimation    // Точка аппроксимации
{
	float kod;                    // код или % или вольты или еще чего-нибудь
	float fiz;                    // физическое значение
};


class AFX_EXT_CLASS DataForTarir           //Данные для тарирования параметра
{
public:

	DataForTarir();
	~DataForTarir();

    CString index;                  // индекс параметра
	CString typeParam;                // тип параметра
	CString zavNum;                 // заводской номер
    DataSetBits adr;                // адрес в БИТС
    CString unit;                   // единицы измерения
	TYPE_TARIR typeT;               // тип тарировки
	CString dataCorrect;            // дата коррекции
	float min;                      // min диапазона  
	float max;                      // max диапазона  
    TarirKoeff* koeff;              // данные по коеффициентам 
	int numPoints;                  // число точек аппроксимации
	CString unitApp;                // единицы кода аппроксимации
	PointApproksimation* pointsApp; // массив точек аппроксимации
	float Rdop;                     // R дополнительное
	float Rkab;                     // R кабеля 
	float R0;
	float deltaR;
	
	void Clear();                   // установка информации в состояние "тарировка не определена"
	BOOL SetTypeTarir(TYPE_TARIR type, int numPoint = NULL); //установить тип тарировки   
   
private:

	BOOL Control();                 // контроль правильности информации
	void SetUndefType();
 	void InitKoeff();
	void InitPointsApp();
};

////////////////////////////////////////////////////////////////////////////////





struct AFX_EXT_CLASS DataForEssential    // Данные для выбора существенности
{
   int       point;               // точки усреднения(а)/подтверждения(с)
   float     deltS;               // дельта существенности 
   float     deltD;               // дельта достоверности 
   CString   typePrint;           // вывод на печать (% или физ)
};

struct AFX_EXT_CLASS DataForIshodn      // Данные для ОЦЕНКИ ИСХОДНОГО
{
   CString typeEstimate;          // тип поведения 
   float min;                     // мин(а)/исходное значение(с) 
   float max;                     // мах(а)
   float delta;                   // наводка
   CString unitEstimate;          // единицы оценки(% или физ)
};

struct AFX_EXT_CLASS DataForView        // Данные для ОТОБРАЖЕНИЯ
{
   CString placeInShip;           // место на корабле 
   CString stream;                // поток
   CString typeView;              // тип параметра для вывода  
   int     length;                // длина 
};

struct AFX_EXT_CLASS DataForViewOnInterval  //  Данные для отображения на интервале
{
	float min;                    // мин
	float max;                    // максимум 
	float timeBeg;                // начало интервала
	float timeEnd;                // конец интервала 
};



struct AFX_EXT_CLASS MeanKod                // значения кодовых параметров
{
	int kod;                      // код
	CString  znKod;               // его значение
	
};
struct AFX_EXT_CLASS DataForDeshifr      //  Данные для ДЕШИФРОВКИ
{
   CString typeParam;            //тип параметра
   int     typeDeshifr;          // номер алгоритма   
   int     delta;                //допуск 
   CString unit;                 // единицы измерения 
};
struct AFX_EXT_CLASS DataForAdrInKadr       // Данные для ДЕКОММУТАЦИИ параметра
{
	short kodPsb;                // числовой код ПСБ
	int posInKadr;               // первая позиция в кадре 
    int lamelSSK;                // первая ламель ССК (-1 если 2 ступень)
	int  razr;                   // разряд   (-1 если аналоговый параметр)
	int  f;                      // запараллеленность 
	CString strAdr;             // строка адреса, отличного от стандарта 
};
class AFX_EXT_CLASS MainCharParametr               // набор основной информации по параметру
{
public:
	MainCharParametr();
	~MainCharParametr();

   CString        indeks;          // индекс
   CString        identif;        // идентификатор
   CString        name;           // название
   DataForDeshifr desh;           // данные для дешифровки 
   int            numPsb;
   DataForAdrInKadr* adrInKadr;     // данные для декоммутации

   void Clear();                      // очистить данные
   BOOL SetNumPsb(int n);            // установить кол-во возможных ПСБ
private:
   BOOL Control();
};

struct AFX_EXT_CLASS CharCurrentJob          // Данные по текущей выбранной работе
{
   long    personalKey;           // индивидуальный ключ - код для записи в архив
   CString nameRazdel;            // название раздела
   CString nameProt;              // название протяжки
   CString nameTask;              // название задачи 
   CString regObr;                // режим протяжки  
   CString strPSB;                // программы сбора
   CStringList listContentTask;   // список наборов параметров и типов их обработки
};

struct AFX_EXT_CLASS KalibrParam             // Данные по параметрам калибровки
{
	CString index;                // индекс
	int min;                      // мин значение кода
	int max;                      // макс значение кода 
};

struct AFX_EXT_CLASS CharPSB                       // Данные по программам сбора
{
	long key;                     // уникальный ключ
	CString name;                 // название ПСБ
	short kodInKadr;              // код в кадре
};

struct AFX_EXT_CLASS Razdel             // данные по разделам
{
    CString nameRazdel;                   //название
	CString abbrevRazdel;                 // аббревиатура
};

struct AFX_EXT_CLASS ParamInList        // данные по параметрам в списках
{
	CString indeks;                // индекс
	CString typePrint;             // тип печати (%?, физ, код)  
	int currentDelta;              // дельта существенности - либо основная, 
	                               // либо для установленного раздела
};
struct AFX_EXT_CLASS AdrInKadrBCVM     // адрес параметра в цифровом массиве
{
	int nKadr;                      // номер(или тип)кадра
	int nRow;                       // номер строки
	int nWord;                    // номер слова в строке
	short bitBeg;                   // номер первого бита
	short bitEnd;                   // номер последнего бита
};

struct AFX_EXT_CLASS ParametrKPUD    //данные по параметрам КПУД
{
    CString name;           // название
	CString unit;           // ед-ца измерения
	short mst;              // масштаб
	float ka;               // ка 
	float kb;               // кв 
	int nAdr;               // число адресных позиций по всем кадрам
	AdrInKadrBCVM* adr;     // массив адресов

};

struct AFX_EXT_CLASS CommandSUBS      //данные по командам БЦВМ
{
    CString nameCommand;            // название команды
	CString abonent;                // абонент 
	CString kod;                    // код команды
	CString comment;                // описание
	short   type;                   // тип команды
	CString nKadr;                  // тип кадра
	int     nWord;                  // номер слова в строке
	short nHalfWord;                // номер полуслова
	short nRazr;                    // номер первого разряда
	short meanRazr;                 // значение разрядов
	short nRazrEnd;                 // номер последнего разряда
};

struct AFX_EXT_CLASS CharIzdel
{
    CString nameIzdel;               // название изделия
	CString numIzdel;                // номер изделия
	CString typeBort;                // кодировка борта 

};
struct AFX_EXT_CLASS CharAlg
{
	CString nameAlg;                  //обозначение алгоритма (3 символа) 
	CString nameProgr;                // название соответствующей программы обработки
	CString prEssential;              // признак необходимости выделения существенности (+ или -)
	CString typeFile;                 // формат файла на входе
};
struct AFX_EXT_CLASS Diapazon
{
    float PointBeg;                   //начальная точка диапазона
    float PointEnd;                   // конечная точка 
	CString MeanDiapazon;             // значение параметра 
};

/////////////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS DBbits
{

public:

  DBbits();
  ~DBbits();

              // НАСТРОЙКА ( УСПЕШНЫЙ ВЫЗОВ ФУНКЦИЙ SET.. ИЗ ЭТОЙ ГЛАВЫ ВЫЗЫВАЕТ ЗАКРЫТИЕ 
              // ПРЕДЫДУЩЕЙ ОТКРЫТОЙ БАЗЫ ДАННЫХ если таковая была открыта)

  BOOL SetDirDB(CString nameDirDb);   // +установить главную директорию хранения всех БД

  BOOL GetAllIzdel(CStringList* listIzdel);    // +дать список изделий, по к-рым есть БД
  BOOL GetAllNumForCurrentIzdel(CStringList* listNumIzdel); //+ дать список  № машин по установленному изделию, для которых есть БД

  BOOL SetIzdel(CString nameCurrentIzdel);     // +установить изделие, с которым в дальнейшем будет вестись работа     
  BOOL SetNumIzdel(CString numIzdel);          // +установить № машины
  BOOL SetIzdel(CString nameCurrentIzdel,CString numForCurrentIzdel); //+установить сразу изделие и №
  BOOL GetCharIzdel(CharIzdel* charCurrentIzdel); // дать характеристики изделия из БД
 
                   // ОТКРЫТИЕ БАЗЫ
  BOOL OpenDB(); // +открыть базу данных по ранее установленным изделию и номеру
                         //+ открыть базу по указанным параметрам вызова
  BOOL OpenDB(CString nameDirDb,CString nameCurrentIzdel,CString numForCurrentIzdel);
  BOOL CloseDB(); // +закрыть БД
  BOOL GetListPO(CStringList* listPO);  // выдать список ПО для обработки данного изделия 
  BOOL GetCharForAlgObr(CString nameAlgObr, CharAlg* charAlg);
              // ВЫДАЧА ПРИЗНАКОВ ГРУППИРОВКИ

  BOOL GetListSets(CStringList* listSets);      // +дать список приборов в БИТС
  BOOL GetListTypeParam(CStringList* listTypes); // +дать список возможных типов параметров
      
              // ВОЗМОЖНАЯ ВЫДАЧА СПИСКОВ ПАРАМЕТРОВ по признакам

  BOOL GetListAllParam(CStringList* listParam);   // +дать список всех параметров из БД
  BOOL GetListAllParamBITS(CStringList* listParam); // +дать список только параметров БИТС
  BOOL GetListAllParamCM(CStringList* listParam); // дать список только параметров цифровых массивов
  BOOL GetListParamFromSet(CString setBits, CStringList* listParam); // +дать полный список параметров по конкретному прибору
  BOOL GetListParamKPUD(CStringList* listParam);  // дать список параметров КПУД
  BOOL GetListCommandSUBS(CStringList* ListCommand);  //дать список команд ЦВМ 
   
                //    АДРЕСАЦИЯ В БИТС

  BOOL GetDataSetBitsForParam(CString index, DataSetBits* adrInBits);  // +дать адрес параметра в БИТС 
  
               //     ДЕКОММУТАЦИЯ и ДЕШИФРОВКА
  int GetAllPSB(CharPSB** charPsb); // дать программы сбора и их характеристики
  BOOL GetAdrParametrAndDataForDeshifr(MainCharParametr* charParam);  //+ выдать данные для декоммутации и дешифровки
  
              ///        ТАРИРОВКИ
  int  GetParamFromSet(CString nameSet,DataForTarir** tarir);  // +дать параметры с тарировками с заданного прибора
  BOOL GetTarirForParam(DataForTarir* tarir); //+ получить тарировки для параметра
  BOOL SetTarirForParam(DataForTarir* tarir); //+установить тарировки для параметра
  int GetConstZnForParam(CString nameParam, MeanKod** listZn);  //выдать расшифровку значений параметра
  int GetListDiapazonForParam(CString nameParam,Diapazon** listDiapazon); //выдать расшифровку значений аналогового параметра по диапазонам 
 
            ///         КАЛИБРОВКИ
  BOOL GetKalibrParamForParametr(CString index, KalibrParam* kalibr0, KalibrParam* kalibr100, KalibrParam* kalibr50); // дать параметры калибровок для параметра
  BOOL GetKalibrParamForSetBits(CString setBits, KalibrParam* kalibr0, KalibrParam* kalibr100, KalibrParam* kalibr50); // дать параметры калибровок для прибора
  
  
            /// ДАННЫЕ ПО ЗАДАНИЯМ и НАБОРАМ ПАРАМЕТРОВ 
                       ////+ выдать содержание конкретного задания на обработку
  BOOL GetListContentTask(CString nameTask, CStringList* listContentTask); 
                       // выдать содержание набора параметров 
  int GetContentListParam(CString nameListParam, ParamInList** listParam);  
  BOOL GetAllListsParam(CStringList* listNamesListParam); // выдать полный список названий наборов параметров
  

            ///      ДАННЫЕ ДЛЯ РАБОТЫ ПО РАЗДЕЛАМ

  int  GetListRazdel(Razdel** listRazdel);  //+ дать список разделов испытаний
  BOOL GetNameRazdelByAbbrev(CString abbrev, CString* nameRazdel); //выдать полное название раздела по аббревиатуре
  BOOL SetCurrentRazdel(CString currentRazdel);   // +установить текущий раздел
  BOOL GetListProtForCurrentRazdel(CStringList* listProt);    //+ дать список протяжек для текущего раздела 
  BOOL SetCurrentProt(CString nameProt);//+установить текущую работу по названию протяжки
  


          ///    ДАННЫЕ  ПО КОНКРЕТНЫМ РАБОТАМ
  BOOL SetCurrentProt(long personalKey);  // +установить текущую работу(раздел и протяжку) по ключу из заголовка архива
  CharCurrentJob* GetCharCurrentJob(){return &currentJob;};     //+ дать характеристики текущей работы    

         ///     ОЦЕНКА ИСХОДНОГО ПО РАЗДЕЛАМ
                    // +значения для оценки исходного конкретного параметра на ранее установленной работе, если
                    //  работа ранее не установлена, возвращает основное исходное
  BOOL GetIshodnForParamOnCurrentJob(CString indeks, DataForIshodn* dtIsh);

         ///     ДАННЫЕ ДЛЯ ОТОБРАЖЕНИЯ ПО РАЗДЕЛАМ

  BOOL GetDateForView( CString indeks,DataForView* dtView); // Выдать общие данные для отображения параметра
  int GetDateForViewOnInterval(CString indeks, DataForViewOnInterval** dtIntervalView); // выдать интервалы и диапазоны

         /// ДАННЫЕ ДЛЯ РАБОТЫ С БЦВМ

 // int GetCommandFromBCVM(CommandBCVM** dtCommand);   // Выдать полный список команд 
  BOOL GetDataForParametrKPUD(ParametrKPUD* parametr); //Дать данные по параметру КПУД
  BOOL GetDataForCommandSUBS(CommandSUBS* ptrCommand);        // дать данные по команде ЦВМ
  BOOL GetVersDB(CStringList* listVersion);   // дать версию БД
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
