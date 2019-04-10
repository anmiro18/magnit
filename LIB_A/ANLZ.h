// ANLZ.h: Интерфейсный модуль для класса ANLZ 

#if !defined(AFX_ANLZ_H__CF3CAD5B_CAE6_11DA_82FD_004095E20ABF__INCLUDED_)
#define AFX_ANLZ_H__CF3CAD5B_CAE6_11DA_82FD_004095E20ABF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS ANLZ 
{
public:
	CFile  FReport;
	CFile  FLevel;
public:
	void SetADD1(float x);
	void DubManal(short Npar, long tn, long tk);
//	CSize ConvToL(CSize s);
	int GetNA();
	float GetArg(int n);
	long GettnI();
	long GettkI();
	void finish();
	void DispPar(short n, short i);
	ANLZ(Izdel* pi=NULL, DataIz* pd=NULL, CDC* pDC=NULL);
	virtual ~ANLZ();
	short sigN(double x);
	int SetTask(int n);
	void CheckCom(short Npar, short na, CString Sar, long tn, long tk);
		          
	void CheckFunc(short Npar, long k, double Yopt, float mi, float ma,
		           float de, float podr);
	short Numb(short Npar, long tn, long tk, short eps);
	short checkV(double z, float A, float B, CString& s);
	void WrResult(CString State, short Er, CString Se,short nR, CString Sd);
	int start(int& k);
	long ARRAY(short np, long tn, long tk, ArrFL& P, ArrLG& T, short eps);
	CString Checking(int np, int ni);
	
protected:
	int TestLev(short np, double U, double E, long t1, long t2);
	int ZnachP(short Npar, long tn, long tk);
	void Magnit(short Npar);
	void CCK(short Npar);
	int  nFRep;
	int  nBndrIsx;
	void kd(short Npar, CString Sar, long tn, long tk);
	void dpn(short Npar);
	void maxmin(short Npar);
	void mperek(short Npar, long tn, long tk);
	void vozubiv(short Npar, short j);
	void msig(short Npar, int Ls);
	void Manal(short Npar, long tn, long tk);
	void meandr(short Npar);
	 Izdel* pI;
	DataIz* pD;
	   CDC* pC;
	 CDmtr* pDmt;
	 CDmtr* pMat;
	CDspAn* pDsp;
	//================================================
	RESANL RemarkStr;
	CString StatePar;
	CString ParName;
	float ADD1;
	double UrovTek;
	float dev;
	float Tint;
	float Xpod;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	float arg5;
	long  NumV;
	long  tnI;
	long  tkI;
	short star;
	short ErrorKod;
	int   nparP;
	int   isigp;
	short naP;
	CString SarP;
	CRect  Area;
	int nMatr;
	//================================================

};

#endif // !defined(AFX_ANLZ_H__CF3CAD5B_CAE6_11DA_82FD_004095E20ABF__INCLUDED_)
