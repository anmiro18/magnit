// ANLZ.cpp: Реализация класса ANLZ
//	Библиотека программ анализа.    Кукушкин И.Л.
////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "io.h"
#include "hlibbas.h"
#include "comm_c.h"
#include "Izdel.h"
#include "Dmtr.h"
#include "DataIz.h"

#include "DspAn.h"
#include "ANLZ.h"
#include "math.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define ZEROM 99999
//===============================================//
CFile Fsboi;
struct zg
		{
			char sN[32];	//имя параметра
			char sg1[16];	//имя границы1
			char sg2[16];	//имя границы2
			double xnt;		//номер п/раздела
			double xTg1;	//время границы1
			double xTg2;	//время границы2
			double tpL;		//тип вывода параметра
		}	xzg;
double zrd;
void ZagFsboi(CString sn, CString SG1, CString SG2, int Xnt, double T1, double T2, int tip)
{
	strcpy(xzg.sN, sn);
	strcpy(xzg.sg1, SG1);
	strcpy(xzg.sg2, SG2);
	xzg.xnt=double(Xnt);
	xzg.xTg1=T1;
	xzg.xTg2=T2;
	xzg.tpL =double(tip);
	Fsboi.Write(&xzg, sizeof(xzg));
}
void ZapFsboi(double x, double y, double z)
{
	zrd=x;	Fsboi.Write(&zrd, sizeof(zrd));
	zrd=y;	Fsboi.Write(&zrd, sizeof(zrd));
	zrd=z;	Fsboi.Write(&zrd, sizeof(zrd));
}
//======== Получить инф. о текущем п/разделе ===//
//Возв: -1, если без п/р-ов, иначе номер п/р-ла //
int GetTaskInf(Izdel *p, CString &sc, CString &sn)
{
	CString s1, s2, s3;
	int n=p->GetPodRz();
	if(p->MaxPz(p->GetRazdIz()))
	   p->GetPodr(n, s1, s2, s3);
	else 
	{
		n=-1;
		s1=p->GetNamRz();
		s3=p->GetComRz();
	}
	sc=s3; sn=s1;
	return n;	
}
//==============================================//

//======== Конструктор / Деструктор ==========// 
ANLZ::ANLZ(Izdel* pi, DataIz* pd, CDC* pDC)
{
	pI=pi;
	pD=pd;
	pC=pDC;
	nBndrIsx=0;
	pD->InitTskRes();
	pDmt = pD->GetpDM();
	pMat=NULL;
	nMatr=pI->IsPodrMat();
	if(nMatr>1)
	{   CString s; s.Format("dmt%d",nMatr);
	    pMat= new CDmtr(pI, s);
	}
	naP  = 0;
	SarP = "";
	pDsp = NULL;
}

ANLZ::~ANLZ()
{
	if(pMat != NULL) delete pMat;
}

//====== Анализ параметра на интервале =======//
CString ANLZ::Checking(int Npar, int Nbnd)
{
	ErrorKod = 0;
	StatePar="";
	ADD1=0;
	if(Npar != nparP) isigp=2;
	nparP = Npar;
	if(pD->DATp[Npar].alg==99) return "";   //Выход для пустых имен параметров(не для /M)
	pD->GetDataInt(Npar, Nbnd);
	
	ParName=srm(pD->DATp[Npar].Nazv,0);
	//===================================================//
	(*pDsp).m_ST7.SetWindowText(snm(Npar+1,0));
	(*pDsp).m_ST1.SetWindowText(srm(pD->DATp[Npar].Nazv,0));
	//===================================================//
	CString sMatr;
	int nMtr;
	if(pMat == NULL) {nMtr = pDmt->GetNmOfNp(Npar); sMatr=pDmt->GetNameMat(nMtr);}
	else             {nMtr = pMat->GetNmOfNp(Npar); sMatr=pMat->GetNameMat(nMtr);}
	//===================================================//
	
	short n1=pD->streat.m1;
	short n2=pD->streat.m2;
	short na=pD->streat.nf;

	short nk1=pD->streat.nk1; if(nk1<0) nk1=0;
	short nk2=pD->streat.nk2; if(nk2<0) nk2=0;

//	long tt1=long(pD->mnk[nk1]*1000);
//	long tt2=long(pD->mnk[nk2]*1000);

	long tt1=long(nk1*10);
	long tt2=long(nk2*10);

	CString Sa =pD->streat.sa;
	           	pD->MakeArg(na, Sa);
	CString	Sar=pD->streat.sarg;
	short prKV = Sa.Find('[');	
	//TRACE("\n Checking: ParName=%s Npar=%d Nbnd=%d na=%d Sar=%s\n",
		//	ParName,Npar,Nbnd,na,Sar);
	RemarkStr.na=na;
	RemarkStr.Npar=Npar;
	RemarkStr.ng1=n1;
	RemarkStr.ng2=n2;
	RemarkStr.nk1=nk1;
	RemarkStr.nk2=nk2;
	strcpy(RemarkStr.Sar, Sar);

	tnI=pD->tgr[n1].t+tt1;
	tkI=pD->tgr[n2].t-tt2;
	//====================================================//
	(*pDsp).m_STM1.SetWindowText("ИНТЕРВАЛ: "+snm(tnI*0.001,2)+"  "+snm(tkI*0.001,2));
	//====================================================//
	//TRACE("\nChecking tnI=%ld tkI=%ld tgr1=%ld tgr2=%ld pr1=%d pr2=%d\n",
	//tnI,tkI,pD->tgr[n1].t,pD->tgr[n2].t,pD->tgr[n1].pr,pD->tgr[n2].pr);


	if((pD->tgr[n1].pr)+(pD->tgr[n2].pr)==0)
	{
		if(na>0)
		{
		  CheckCom(Npar, na, Sar, tnI, tkI);
		  //=============== для [a:b]    ===========//
		  if(prKV == 0 && ErrorKod !=0)
		  {
			ErrorKod = 0;
			CheckCom(Npar, naP, SarP, tnI, tkI);
		  }
		  //========================================//
		  if(ErrorKod>=0 && pD->DATp[Npar].alg != 98)
		  {
			  double Utek=pD->level(Npar,tnI, tkI);
	                     pD->Lev(pD->GetNTask(),Npar,Nbnd,Utek,1);
		  }
		}
	}
	else ErrorKod=8;
	naP=na; SarP=Sar;
	RemarkStr.ADD1=ADD1;
	//===============================================//
	(*pDsp).m_STM1.SetWindowText("  ");
	//===============================================//
	

	if(na==10 || na>99)                     return Sar;

	if(pI->IsPodrMat() && nBndrIsx != Nbnd) return "";

	WrResult(StatePar, abs(ErrorKod), "", 0, sMatr);
	                                        return Sar;
}
//=========== Получение массива значений=============//
long ANLZ::ARRAY(short np, long tn, long tk, 
						ArrFL &P, ArrLG &T, short eps)
{
	long j=0, ti, tp, k=pI->Interval(np, tn, tk);
	if(k<0) return 0;
	double pi, pp=pD->FisV(np, 0, tp); 
	P.RemoveAll();
	T.RemoveAll();
	P.Add(-1);	//P[0]
	T.Add(tp);	//T[0]
	for(long i=1; i<=k+1; ++i)
	{
		pi=pD->FisV(np, i, ti);
		if((ti-tp>eps && P[j] != pp) || eps<0)
		{
			j++;
			P.Add(pp);
			T.Add(tp);
		}
		if(pi!=pp || eps<0) {pp=pi; tp=ti;}
	}
	return j;
}
//================== Начало оценки================//
int ANLZ::start(int& k)
{
	nparP=-1;
	//============================================//
	CString sf=pI->FormFileNameRS("r");
	//============================================//
	nFRep=IDYES;
	if(_access(sf,0)==0)
	{
	 nFRep=AfxMessageBox(
		 "РЕЗУЛЬТАТЫ АНАЛИЗА УЖЕ СУЩЕСТВУЮТ. ПОВТОРИТЬ АНАЛИЗ?",
	               	            	MB_YESNO | MB_ICONQUESTION);
	}
   	//============================================//
	//CSize sr = ConvToL(CSize(1000, 700));
	//pC->FillSolidRect(CRect(0, 0, sr.cx, sr.cy), RGB(0xff, 0xff, 0xff));
	
	int kR=(*pI).MaxPz((*pI).GetRazdIz());
	//=============== Окно протокола анализа =====//
    CWnd* pWnd = pC->GetWindow();  
	if(pWnd != NULL)
	{	
		pWnd->GetClientRect(&Area);
		pDsp = new CDspAn;
      if((*pDsp).GetSafeHwnd()==0)
	     (*pDsp).Create(Area, "АНАЛИЗ РАЗДЕЛА:  "+pI->GetNamRz());
	}
    //============================================//
	k = kR ? kR : 1; 
	//============================================//
	pI->RdCTL();
	//============================================//
	if(nFRep==IDYES)
	{
	//============ Подготовка к работе с Lev =====//
		int maxP=0, maxB=0;
		for(int i=0; i<k; ++i)
		{
			if(pD->SetTask0(i)<0) continue;
			if(maxP<pD->NParm) maxP=pD->NParm;
			if(maxB<pD->NBndr) maxB=pD->NBndr;
		}
		pD->OpenLev(0);
		pD->ZagLev(k, maxP, maxB);
	//============================================//
		FReport.Open(sf,CFile::modeCreate | 
					    CFile::modeWrite  | CFile::typeBinary);
		  Fsboi.Open(pI->FormFileNameRS("e"),
						CFile::modeCreate | 
					    CFile::modeWrite  | CFile::typeBinary);
	//============================================//
		DeleteFile(pI->FormFileNameRS("g"));
		DeleteFile(pI->FormFileNameRS("a"));
		DeleteFile(pI->FormFileNameRS("i"));
		DeleteFile(pI->FormFileNameRS("j"));
		DeleteFile(pI->FormFileNameRS("k"));
		DeleteFile(pI->FormFileNameRS("u"));
		DeleteFile(pI->FormFileNameRS("v"));
		DeleteFile(pI->FormFileNameRS("w"));
		DeleteFile(pI->FormFileNameRS("d"));
		AppTxtFile("Анализ раздела: "+pI->GetNamRz(),pI->FormFileNameRS("d"),"");
	}
	//============================================//
	long tn, tk;
	pI->OpenFileTmi(tn, tk);
	pD->OpenTXPI();
	pD->AddBound("ТНПР",tn);
	pD->AddBound("ТКПР",tk);
//	pD->AddBound("TBound",pD->TBound);
	//===========================================//	
	CString sAnc;
	float   xAnc;
	pD->GetAnchor(sAnc, xAnc);
	//TRACE("\nsAnc=%s xAnc=%.2f\n",sAnc,xAnc);
	pD->AddBound(sAnc, long(xAnc*1000));
	//==========================================//
	return nFRep==IDYES ? 1:0;
}

//======== Запись на файл результатов ==========//
void ANLZ::WrResult(CString State, short Er, 
					CString Se, short nR, CString Sd)
{
	strcpy(RemarkStr.State,State);
	strcpy(RemarkStr.Serror,Se);
	strcpy(RemarkStr.SDop,Sd);
	RemarkStr.ErrKod=Er;
	RemarkStr.ResAn=nR;
	FReport.Write(&RemarkStr,sizeof(RemarkStr));
}
//==== Проверка значения и форматирование ========//
short ANLZ::checkV(double zz, float A, float B, CString &s)
{
	short  Nm = 0;
	int r, kf, mp[4]={1,10,100,1000};
	CString sz = zz<0 ? "-" : "";
	double z = fabs(zz);
    //--------------------------- Шишнин
	if(z < 100 || (B-A < 50    && B-A>0))	   Nm=1;  //26.05.16
	if(z < 1   || (B-A < 2     && B-A>0))      Nm=2;
	if            (B-A < 0.201 && B-A>0)	   Nm=3;  //30.01.18
	kf = mp[Nm];
	//CString sss; sss.Format("zz=%.2f Nm=%d", zz, Nm);AfxMessageBox(sss);
	if((r=int(z*kf + 0.5))%kf == 0)       Nm=0;
	z = double(r) / kf;
	if(z == 0) sz = "";
	 s = sz + snm(z, Nm);
	zz = atof(s);
	//if(ParName.Right(2)==" в")  s= s+"/"+snm(zz*0.0625f,1)+"в";
	
	double AA=A-0.000001;
	double BB=B+0.000001;
	
	if(zz<AA) return 1;
	if(zz>BB) return 2;
	  		  return 0;
}
//============ Подсчет числа переключений ========//
short ANLZ::Numb(short Npar, long tn, long tk, short eps)
{

	short n1=0, Md=2;
	long  tp, tt;
	long  Kizm = pI->Interval(Npar, tn, tk);
	int Mt, Mp=pI->Izm(Npar, 0, tp);
	for(long i=1; i<=Kizm+1; ++i)
	{
		Mt =pI->Izm(Npar, i, tt);
		if(Mp != Md && tt-tp>eps) { n1+=Mp; Md=Mp; }
		if(Mt != Mp) {Mp=Mt; tp=tt; }
	}
	return n1;
}
//== Проверка всех значений пар-ра (manal, msig) ==//
void ANLZ::CheckFunc(short Npar, long k,  double Yopt, float mi,
			           float ma,   float de, float podr)
//================================================//
// Вход:  Yopt - тек. уровень; mi - arg1;  ma - arg2;
//          de - наводка заданная;
// Выход: ADD1-время начала подработки;
//		  Er=12 - выход за минимум
//		  Er=14 - выход за максимум
//================================================//
{
   short MaxErr=14, MinErr=12, nd, n1, n2, N0, n0p=0, n1p, n2p, ndp, Tbn;
   double               min=mi-0.5f,   max=ma+0.5f,   dev=de+0.5f;
   if(fabs(Yopt)<100) { min=mi-0.05f,  max=ma+0.05f,  dev=de+0.05f;}
   if(fabs(Yopt)<1  ) { min=mi-0.005f, max=ma+0.005f, dev=de+0.005f;}
   short nalg = GetNA();
// BOOL iSGN = Yopt==mi && mi==ma && de==0;	
   BOOL iSGN = (pD->DATp[Npar].alg == 1) ? 1:0;
//CString sss; sss.Format("Npar=%d iSGN=%d alg=%d de=%.2f sa=%s",Npar,iSGN,pD->DATp[Npar].alg,de,pD->streat.sa);AfxMessageBox(sss);

   BOOL Sit = (pD->GetTSit(Npar))>0 || pD->DATp[Npar].alg==6;
   short NlkNk = pD->DATp[Npar].NlkNk, nMt,ts=0;
   double Tdev1,Tdev, Tmin, Tmax;
   double F, T, TD, T1, T2, tp=0, pp;
   double dmd, dm1, dm2, d0, d;
   long TL;
   int Ndev1;
   //===========================================================//
   CString sCom, sNam;
   int nE, bE, pFirst=0;
   int nPd=GetTaskInf(pI, sCom, sNam);
   BOOL iE;
   int Tpout = pD->DATp[Npar].TipL;
   nE=sCom.Find("/E");
   bE=sCom.Find("/B");
   //===========================================================//
   if(NlkNk>99)
   {
	   nMt = pDmt->PskDMatr(NlkNk - NlkNk % 100);
	   if(nMt>-1) ts  = pDmt->GetTsitMat(nMt);
   }
        if(ts == 5)		Tbn = 1000;  //======= длит. сбоя для СИТ 615,732.
   else if(ts == 3)		Tbn = 345;   //======= длит. сбоя для СИТ DMSL-Б.
   else if(de == ZEROM) Tbn = 0;	 //======= конт. все сбои (/N)
   else if(iSGN && (nalg == 12 || nalg == 13)) {Tbn=0; bE=0;}   // сигн. ==\D, --\D
   else                 Tbn = pD->TBound;                       //== длит из TBound
   
   if (srm(pI->GetNameIz(),0) == "732SZI")  
   {   
						Tbn = 30;    //======= длит. сбоя для СЗИ732. --- Шишнин 24.10.18
   }                                 
   //===========================================================//
   if(Sit)
   {
		Tdev=Tmin=Tmax=-1;  Tdev1=0; Ndev1=0;
		for(long i=1; i<=k; ++i)
		{
			F=pD->FisV(Npar, i, TL); T = TL * 0.001;
			nd = (F < Yopt - dev || F > Yopt + dev)? 1 : 0;
			n1 = (F<min)? 1 : 0;
			n2 = (F>max)? 1 : 0;
			N0 = 4*nd+2*n1+n2;
			Tdev+=nd;
			Tmin+=n1;
			Tmax+=n2;
			if(nd) TD=T;
			if(n1) T1=T;
			if(n2) T2=T;
		}
   }
   else
   {
		Tdev1=Tdev=Tmin=Tmax=0; Ndev1=0;
		dmd=dm1=dm2=0;
		for(long i=0; i<=k+1; ++i)
		{
			F=pD->FisV(Npar, i, TL); T = TL * 0.001f;
			nd = (F < Yopt - dev || F > Yopt + dev)? 1 : 0;
			n1 = (F<min)? 1 : 0;
			n2 = (F>max)? 1 : 0;
			N0 = 4*nd+2*n1+n2;
			d0=T-tp;
			if(n0p != N0 || i == k+1 || i==0)
			{
				if(d0 > Tbn * 0.001 && i>0)
				{
					d=ndp*d0; Tdev+=d; if(d>dmd){dmd=d0; TD=tp;}
					d=n1p*d0; Tmin+=d; if(d>dm1){dm1=d0; T1=tp;}
					d=n2p*d0; Tmax+=d; if(d>dm2){dm2=d0; T2=tp;}
				}
				//========== Запись одиночных сбоев =========//
				else if(i>0)
				{
				  //============= Подсчет един. отклонений =============//
				  if(n0p && ts==0 && Tbn>0 && d0>=0.005 && (!iSGN || nE<0)) 
				  { 
					  Tdev1+=d0; Ndev1++; if(TD<0.001) TD=tp;
					
					// CString sss;  sss.Format("Npar=%d d0=%.4f Ndev1=%d tnI=%.2f" ,
					 //						    Npar,   d0,     Ndev1,   tnI*0.001);
					  //AfxMessageBox(sss);
				  }
				  //====================================================//
				  if(bE<0)
				  {
					//if(i>0 && i<k+1 && iSGN && d0>0 && long(tp*1000)>tnI)
					//if(nE<0) iE=1; else iE= (i<k+1) && (long(tp*1000)>tnI);
					iE = nE<0 ? 1 : (i<k+1) && (long(tp*1000)>tnI);
					if(iSGN && d0>0 && ndp>0 && iE)
					{
						if(!pFirst) 
						{   CString s, s1, s2;
							s=ParName;
							s1=pD->tgr[pD->streat.m1].nameG;
							s2=pD->tgr[pD->streat.m2].nameG;
							ZagFsboi(s, s1, s2, nPd, tnI*0.001, tkI*0.001, Tpout);
							pFirst=1;
						}
						ZapFsboi(tp, d0, pp);
					}
				  }
				}
				//===========================================//
				tp=T;
				pp=F;
			}
			n0p=N0; ndp=nd; n1p=n1; n2p=n2;
		}
   }
   //======== Учет един. срабатываний =============//
   if(!iSGN)
   {
	   if(Xpod > pD->TBound*0.001+0.001){ Tdev+=Tdev1; Tdev1=0; Ndev1=0;} // \D
   }
   //====================== errors ================//
   ErrorKod = 0;
	if((Tmin>0 || Tmax>0) && !iSGN )
	{
					       ADD1=T2; ErrorKod = MaxErr;
	     if(Tmin > Tmax){  ADD1=T1; ErrorKod = MinErr; }
	}
	else if(Tdev > podr){  ADD1=TD; ErrorKod = 2;}
	else
	{ 
		if(Ndev1 > int(Tint*0.1)+1) 
		{ 
			ADD1=Ndev1; ErrorKod=34; 
		}
	}
	//CString sss; sss.Format("Npar=%d Tdev=%.2f Ndev1=%d  ",Npar,Tdev,Ndev1);AfxMessageBox(sss);
	//=============================================//
	if(pFirst) ZapFsboi(-1.0,-1.0,-1.0);
}
//================================================//
short naps;
//=========== Оценка поведения параметра =========//
void ANLZ::CheckCom(short Npar, short na, CString Sar,
								long tN, long tK)
//================================================//
//Вход:   Npar, na, Sar, tN, tK
//Выход:  StatePar    - состояние пар-ра
//		  ErrorKod - код ошибки
//        Add1     - время замечания
//================================================//
{
	short npTip = pD->DATp[Npar].alg;
	short   Sit = pD->GetTSit(Npar);
	long tn=tN, tk=tK;
	//=============================//
	pD->MakeArg(na,Sar);
	//=============================//
	arg1=pD->streat.arg1,
	arg2=pD->streat.arg2, 
	arg3=pD->streat.arg3, 
	arg4=pD->streat.arg4; 
	arg5=pD->streat.arg5;
	star=pD->streat.star;
	if(star==2) { arg1+=UrovTek;  arg2+=UrovTek; }
	//============================//
	long TKS=pI->GetTKSECT();
	int  Ls;
	if(tk>TKS) tk=TKS;
	Tint=float(tk-tn) * 0.001f;
	//============================//
	if( npTip==98)
	{
		float TintB = Tint; 
		CString s = pD->DATp[Npar].PT;
		if(s.Find("T")>-1 || s.Find("Т")>-1)
		{   
			TintB = pD->GetTBrt(tk);
			if(TintB == ZERO) {ErrorKod=-26; return;}
			TintB = TintB - pD->GetTBrt(tn);
			if(TintB < -80000) TintB+= 86400;
		}
		//s.Format(" %.2f %.2f %ld %ld",pD->GetTBrt(tk),pD->GetTBrt(tn), tk, tn);
		//AfxMessageBox(s);
		
		StatePar=snm(TintB,2);
		short           j=checkV(TintB, arg1, arg2, StatePar);
		if(na==24 && j) j=checkV(TintB, arg3, arg4, StatePar);
		if(j && na != 30) ErrorKod=-23;
								return;
	}
	if(Tint<=0) {ErrorKod=-23;	return;}
	NumV=pI->Interval(Npar,tn,tk);
	
	//CString sss; 	
	//sss.Format("CheckCom: Npar=%d na=%d Sar=%s tn=%ld  tk=%ld  NumV=%ld",Npar,na,Sar,tn,tk,NumV);
	//if(Npar==12)AfxMessageBox(sss);

	if(NumV==-2){ErrorKod=-9;   return;}
	dev=2;
	Xpod= Sit ? 2.5f :( pD->TBound )* 0.001f;
//	TRACE("\nCheckCom: Npar=%d na=%d Sar=%s\n",Npar,na,Sar);
	//================================================//
	switch(na)
	{							//  A:B,  A
	case 1:  case 28:			Manal(Npar,tn,tk);break;
								//  A/B, a:b/A
	case 11: case 20: dev=-ZERO;Manal(Npar,tn,tk);break;
								//  a:b/N
	case 31:          dev=ZEROM;Manal(Npar,tn,tk);break;
								//  A:B/C
	case 6:	dev=arg3;			Manal(Npar,tn,tk);break;
								//  A:B\D
	case 7:			  Xpod=arg3;Manal(Npar,tn,tk);break;	
								//  A:B/C\D
	case 9: dev=arg3; Xpod=arg4;Manal(Npar,tn,tk);break;
								//	A,B/C A,B/C,D 
	case 8: dev=arg3;			meandr(Npar);     break;
								//Нестандартная
	case 10: case 27:							  break;
								// Сигнальный
	case 2:  case 3:	Ls=int(pD->level(Npar,tn, tk)+.4999999);
						msig(Npar, Ls);			  break;
								// +/-
	case 4:  case 5:	Ls=int(pD->level(Npar,tn ,tk)+.4999999);
						if(isigp==2) { isigp=1-Ls;   naps=0; }
						if(na !=naps){ isigp=1-isigp;naps=na;}
						arg1 = float(isigp);
						msig(Npar, Ls);  break;
								// ==\D, --\D
	case 12: case 13:	Ls=int(pD->level(Npar,tn, tk)+.4999999);
						Xpod=arg2;
						msig(Npar, Ls);					   break;
								// возрастание
	case 14:			vozubiv(Npar, 0);				   break;
								// убывание
	case 15:			vozubiv(Npar, 1);				   break;
								// -=A:B
	case 16:			mperek(Npar, tn, tk);			   break;
								// -=A
	case 17: arg2=arg1;	mperek(Npar, tn, tk);			   break;
								// MX *A:B, MN *A:B
	case 18: case 19:	maxmin(Npar);					   break;
								// ДПН
	case 21:			dpn(Npar);						   break;
								//CCK(A,B)
	case 22:            CCK(Npar);                         break;
								// U1:D1,U2:D2/C  Два диапазона
	case 24: dev=arg5;	DubManal(Npar,tn,tk);			   break;
								// КД(для матриц)
	case 25: Xpod=pD->TBound; kd(Npar, Sar, tnI, tkI);     break; 
								// МГН(m, n))
	case 29:            Magnit(Npar);                      break;
	case 30: 			ZnachP(Npar, tnI, tkI);			   break;
	case 32:											   break;	
	}
	return;
}
//============ Установить номер п/раздела ========//
int ANLZ::SetTask(int n)
{
		if(pD->SetTask0(n)<0) return -1;
		//=======================================//
		CString sN;
		CSize sr;
		int k;
		if(k = pI->MaxPz(pI->GetRazdIz())) 
		{
			   sN = pI->GetPodNam(n);
					   
			  (*pDsp).AddPodr(sN);
			   
			  sN = "п/раздел: "+ sN;
		}
	    else   sN = "";    
		AppTxtFile(sN,pI->FormFileNameRS("d"),GetDustbin()+"ErrTsk");
		//=======================================//
		pI->SetDATp(&(pD->DATp));
		//======== Число параметров =============//   
		(*pDsp).m_ST3.SetWindowText(snm(pD->NParm,0));
		(*pDsp).m_ST7.SetWindowText("    ");
		(*pDsp).m_ST1.SetWindowText("  ");
		//=======================================//
		(*pDsp).m_STM1.SetWindowText("ПОИСК ГРАНИЦ");
		//=======================================//
		RemarkStr.AnGr = pD->bounds();
		//=======================================//
		(*pDsp).m_STM1.SetWindowText("            ");
		//=======================================//
		RemarkStr.Ntsk = n;
		return pD->NParm;
}
//============= Оценка аналогового пар-ра ========//
void ANLZ::Manal(short Npar, long tn, long tk)
{
	double Utek = pD->level(Npar,tn,tk); 
	if(Utek==ZERO)	{ ErrorKod=-9;  return; }
	if(star == 1) UrovTek = Utek;
	if( checkV(Utek, arg1, arg2, StatePar ))
					{ 
						ErrorKod= 1;  return; 
					}
	
	//CString sss; sss.Format("Npar=%d Utek=%.2f arg1=%.2f arg2=%.2f",Npar,Utek,arg1,arg2);AfxMessageBox(sss);

	CheckFunc(Npar, NumV, Utek, arg1, arg2, dev, Xpod);
}
//=============== Оценка меандра =================//
void ANLZ::meandr(short Npar)
{
/*
	// старый алгоритм //
    long T1=0, T2=0, tp, T;
	double xp=pD->FisV(Npar, 0, tp);
	for(long Li=1; Li<=NumV+1; ++Li)
	{
		double x=pD->FisV(Npar, Li, T);
		if(fabs(xp - arg1)<=dev)
		{
			T1+=(T-tp);
			StatePar=snm(xp,0);
		}
		else if (fabs(xp - arg2)<=dev)
			T2+=(T-tp);
		xp=x;tp=T;
	}
	float x1=T1*0.1f/Tint,
		  x2=T2*0.1f/Tint;

	if(fabs(x1-50)+fabs(x2-50)>6) ErrorKod=6;
*/
//  новый алгоритм   //
//==========================================
//		CStdioFile f;
//		f.Open("g:\\xxxx",CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText);
//		f.SeekToEnd();
//		char sp[80];
//==========================================
	#define ZEROT -99999999
	int nr, nrp=-1, Nck=0, Ner=0, Nall=0, PiEr;
	int pr, prp, first=0;
	//---------------------------------------------------- Шишнин 23.06.16 100 -> 50
	
	long t, tp=ZEROT, dt=50, d, dlt=int(arg4*1000), eps2=50;
	double u, up=ZERO, xp, eps1=10;
	if(dlt==0) eps2=100000; // нет контроля длит. в случ. A,B/C
		t = tnI;
		while(t < tkI)
		{
			u=pD->level(Npar, t, t+dt);
			if(fabs(u-up)>eps1 && up>ZERO )
			{
				long tt;
				long k = pI->Interval(Npar, t-dt, t+dt);
				//=================================================
				//sprintf(sp, "Npar=%d k=%ld t=%ld dt=%ld up=%8.2f tp=%ld dlt=%ld\n",Npar,k,t,dt,up,tp,dlt);
				//f.WriteString(sp);
				//=================================================
				xp = up;
				for(long i=0; i<=k; ++i)
				{
					double x=pD->FisV(Npar, i, tt);
					if(fabs(x-xp)>eps1)
					{	nr=-1;
						PiEr=0;
						if(tp != ZEROT)
						{
							double uu=pD->level(Npar, tp, tt);
							d=tt-tp;
							if(fabs(uu-arg1)<dev)
							{
								if(labs(d-dlt)<eps2){ nr=0; pr=TestLev(Npar,arg1,dev,tp,tt);
													  if(pr) PiEr=2;
													}
								else{PiEr=3;}
							}
							else if(fabs(uu-arg2)<dev)
							{
								if(labs(d-dlt)<eps2){ nr=1; pr=TestLev(Npar,arg2,dev,tp,tt);
													  if(pr) PiEr=2;
													}
								else{PiEr=3;}
							}
							else
							{PiEr=1;}
							//=====================================================
							//sprintf(sp, "tt=%8.2f  tp=%8.2f x=%8.1f nr=%d  PiEr=%d  Npar=%d\n",
							//	         tt*0.001, tp*.001, x,      nr,    PiEr,    Npar);
							//f.WriteString(sp);
							//=====================================================
							if(nr==1 || nr==0){ Nall++; }
							nrp=nr; prp=pr;
							if(PiEr) {
										if(!first){ ADD1=tp*0.001f; first=PiEr;}
									    Ner++;
									}
						}
						tp=tt;
						break;
					}
					xp=x;
				}
			}
			t+=dt;
			up=u;
		}
		StatePar.Format("%dц./ %dзам.", Nall, Ner);
											//------------------------ Шишнин 14.04.17 
		if(Nall==0) { Ner=1; first=3; ADD1=tnI*0.001f; } 	
		if(Ner) {
			      switch(first)
				  {
				   case 1: ErrorKod=6; break; // Неверн. уровень
				   case 2: ErrorKod=6; break; // Выход за допуск
				   case 3: ErrorKod=6; break; // Неверн. длит.
				  }
				}
//=================================
//	f.Close();
//=================================
}
//=============== Оценка сигнального пар-ра ======//
void ANLZ::msig(short Npar, int Ls)
{
	StatePar = Ls ? "ЗАМКНУТ" : "РАЗОМКНУТ";
	if(Ls != int(arg1)) { ErrorKod=1; return;}
	CheckFunc(Npar, NumV,arg1,arg1,arg1,0,Xpod);
}
//======= Оценка ВОЗРАСТАНИЯ/УБЫВАНИЯ ============//
void ANLZ::vozubiv(short Npar, short j)
{
	long T, k0=0;
	double k=0, Kext, eps=arg2;
//==========================================
//		CStdioFile f;
//		f.Open("g:\\xxxx",CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText);
//		f.SeekToEnd();
//		char sp[80];
//==========================================
	StatePar="КОНСТАНТА";
	Kext= j==0 ? -99999 : 99999;
	if(NumV ==0) return;
	double ip1=pD->FisV(Npar,0,T);
	for(long Li=1; Li<=NumV; ++Li)
	{
		double ip2=pD->FisV(Npar, Li, T);	
		double d = ip2-ip1;
		k+=d; 
		ip1=ip2;
		if(j==0)
		{
			if(k>Kext) Kext=k;
			if(k<Kext-eps){ k0++; if(k0==1)ADD1=T*0.001f;}
		}
		else
		{
			if(k<Kext) Kext=k;
			if(k>Kext+eps){ k0++; if(k0==1)ADD1=T*0.001f;}
		}
//=================================================
//sprintf(sp, "Npar=%d k=%8.1f k0=%8.1f d=%6.1f Kext=%8.1f T=%6.2f\n",Npar,k,k0,d,Kext,T*0.001);
//f.WriteString(sp);
//=================================================
	}
	if(k>0) StatePar="ВОЗРАСТАНИЕ";
	if(k<0)	StatePar="УБЫВАНИЕ";
	//TRACE("\n vosubiv: k0=%d k=%d\n",k0,k);				
	if(k0>0) ErrorKod = 27;									// ЗАМЕЧАНИЕ
	else if(sigN(double(k)) != sigN(0.5 - j)) ErrorKod=32;  // ЗАМ.К ВОЗР/УБЫВ.
//=================================
//	f.Close();
//=================================
}
//=============== Вычисление знака(х) ============//
short ANLZ::sigN(double x)
{
	return x<0 ? -1 : ((x>0)? 1 : 0);
}
//========= Оценка числа переключений ============//
void ANLZ::mperek(short Npar, long tn, long tk)
{
	short n1=Numb(Npar, tn, tk, pD->TBound);
	StatePar.Format("%d" , n1);
	if(n1>arg2 || n1<arg1) ErrorKod=4;
}
//========= Оценка mах/min========================//
void ANLZ::maxmin(short Npar)
{
	double maxp=ZERO, minp=-ZERO, u;
	long T;
	for(long Li=0; Li<=NumV+1; ++Li)
	{
		u=pD->FisV(Npar, Li, T);
		u=atof(snm(u,1));
		if(u>maxp) maxp=u;
		if(u<minp) minp=u;
	}
	u=(arg4 > 0.5f)? maxp : minp;	// arg4==1 max, arg4==0 min
	StatePar=snm(u,1);
	if( u > arg2 || u < arg1) ErrorKod=24;
}
//============ Оценка ДПН   ======================//
void ANLZ::dpn(short Npar)
{
	double max=0, min=256;
	long T;
	for(long Li=0; Li<=NumV; ++Li)
	{
		double P=pD->FisV(Npar, Li, T);
		if(P<min) min=P;
		if(P>max) max=P;
	}
	StatePar=snm(max, 0);
  if(min > arg2 && arg2 !=0) ErrorKod=21; return;
  if(max<80 && Tint >200)	 ErrorKod=22;
}
//============= Оценка КД ========================//
void ANLZ::kd(short Npar, CString Sar, long tn, long tk)
{
	long TU1[8], T1[8], T0[8], TPP[8], Tp0, T ,TD;
	short nup, nu, m;
	for(int i=0; i<8; ++i)
		TU1[i]=T1[i]=T0[i]=TPP[i]=0;
	long iznp=pI->Izm(Npar, 0,Tp0);
	for(long nizm=1; nizm<=NumV+1; ++nizm)
	{
		long izn = pI->Izm(Npar, nizm, T);
			  TD = T - Tp0;
		       m = 0x80;
		for(int i=0; i<8; ++i)
		{
			nup = iznp & m;
			 nu = izn  & m;
			 TPP[i]+=TD;
			 if(nup)
			 {
				  TU1[i]+=TD;
				  if(TPP[i]>T1[i]) T1[i]=TPP[i];
			 }
			 else if(TPP[i]>T0[i]) T0[i]=TPP[i];
			 if(nup != nu) TPP[i]=0;
			 m>>=1;
		}
		Tp0=T; iznp=izn;
	}
	CString s, sp;
	double P1;
	const double PMn = 0.5, PMx = 0.95;
	for(i=0; i<8; ++i)
	{
		sp=s=Sar.Mid(i, 1);
		if( s != "*")
		{
			P1=double(TU1[i])/(tk-tn)*100;
			if     (P1<PMn) sp="0";
			else if(P1>PMx) sp="1";
			     else       sp="E";
			if(sp=="0"  && T1[i]>Xpod) sp="E";
			if(sp=="1"  && T0[i]>Xpod) sp="E";
		}
		if(s != "C" && s != sp || sp == "E") ErrorKod=1;
		StatePar+=sp;
	}
}
//===================== Магнит ====================//
void ANLZ::Magnit(short Npar)
{
//==========================================
//		CStdioFile f;
//		f.Open("g:\\xxxx",CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText);
//		f.SeekToEnd();
//		char sp[80];
//==========================================
#define ZEROT -99999999
	int nr, nrp=-1,nrpp=-1, Nck=0, Ner=0, Nall=0;
	int pr, prp, prpp;

		double U1=1.5,       U2=101.5,	 u1 =1.5,   u2=24,    u3=101.5,
			   Eu1=3.5,      Eu2=3.5,    eu1=3.5,   eu2=6,    eu3=3.5;
		long   D1=1500,      D2=500,     d1 =500,   d2=1000,  d3=500,
			   Ed1=450,      Ed2=150,    ed1=150,   ed2=300,  ed3=150;

					
		long t, tp=ZEROT, dt=100, d;
	
		double u, up=ZERO, xp, eps1=10;
		
		t = tnI;
		while(t < tkI)
		{
			u=pD->level(Npar, t, t+dt);
						
			if(fabs(u-up)>eps1 && up>ZERO )
			{
				long tt;
				long k = pI->Interval(Npar, t-dt, t+dt);
				//=================================================
				//sprintf(sp, "Npar=%d k=%ld t=%ld dt=%ld\n",Npar,k,t,dt);
				//f.WriteString(sp);
				//=================================================
				xp = up;
				for(long i=0; i<=k; ++i)
				{
					double x=pD->FisV(Npar, i, tt);
					if(fabs(x-xp)>eps1)
					{	nr=-1;
						if(tp != ZEROT)
						{
							double uu=pD->level(Npar, tp, tt);
							d=tt-tp;
							if(arg2==1)
							{
								if(fabs(uu-U1)<Eu1)
								{
									if(labs(d-D1)<Ed1){ nr=0; pr=TestLev(Npar,U1,Eu1,tp,tt);}
								}
								else if(fabs(uu-U2)<Eu2)
								{
									if(labs(d-D2)<Ed2){ nr=1; pr=TestLev(Npar,U2,Eu2,tp,tt);}
								}
								//=====================================================
								//sprintf(sp, "%8.2f %8.1f %d    %d\n",tt*.001,x,nr,Npar);
								//f.WriteString(sp);
								//=====================================================
								if(nr==1 && nrp==0){ Nall++; 
								                     if((pr+prp) == 0) Nck++;
													}
								if(nr==-1) Ner++;
								nrp=nr; prp=pr;
							}
							else
							{
								if(fabs(uu-u1)<eu1)
								{
									if(labs(d-d1)<ed1) { nr=0; pr=TestLev(Npar,u1,eu1,tp,tt);}
								}
								else if(fabs(uu-u2)<eu2)
								{
									if(labs(d-d2)<ed2) { nr=1; pr=TestLev(Npar,u2,eu2,tp,tt);}
								}
								else if(fabs(uu-u3)<eu3)
								{
									if(labs(d-d3)<ed3) { nr=2; pr=TestLev(Npar,u3,eu3,tp,tt);}
								}
								if(nr==2 && nrp==1 && nrpp==0){ Nall++;
																if((pr+prp+prpp)==0) Nck++;
																}
								if(nr==-1) Ner++;
								nrpp=nrp; prpp=prp;
								nrp=nr;   prp=pr;
							}
						}
						tp=tt;
						break;
					}
					xp=x;
				}
			}
			t+=dt;
			up=u;
		}
		StatePar.Format("%d/%d цикл.", Nck, Nall);
		if(Nck < arg3) ErrorKod=28;
//=================================
//	f.Close();
//=================================
}
//============ Отображение тек.состояния оценки ==//
void ANLZ::DispPar(short n, short i)
{
}
//============== Конец оценки ====================//
void ANLZ::finish()
{
	(*pDsp).m_STM1.SetWindowText("ПОДГОТОВКА ДОКУМЕНТОВ");
	if(pDsp != NULL) {(*pDsp).DestroyWindow(); delete(pDsp); pDsp=NULL;}
	if(nFRep==IDYES) { FReport.Close(); Fsboi.Close();}
	pD->CloseLev();
	pD->CloseTXPI();
	pI->CloseFileTmi();
}

long ANLZ::GettkI()
{
	return tkI;
}

long ANLZ::GettnI()
{
	return tnI;
}
//=== Получить значение аргумента n ==============//
float ANLZ::GetArg(int n)
{
	float x;
	switch(n)
	{
	case 1: x=pD->streat.arg1; break;
	case 2: x=pD->streat.arg2; break;
	case 3: x=pD->streat.arg3; break;
	case 4: x=pD->streat.arg4; break;
	case 5: x=pD->streat.arg5; break;
	default:x=-1;
	}
	return x;
}

int ANLZ::GetNA()
{
	return pD->streat.nf;
}

void ANLZ::CCK(short Npar)
{
	BOOL first = TRUE;
	float x1 = arg2,
		  x2 = arg3;
	long  t, ip, Ner=0, pp = pI->Izm(Npar, 1, t);
	CString s;
	for(long i=2; i<=NumV; i++)
	{
		ip = pI->Izm(Npar, i, t);
		if(ip != pp+1 && (pp != int(x2) || ip != int(x1)))
		{
			Ner++;
			if(first)
			{
				s.Format("%ld %ld",ip,pp);
				ADD1=t*0.001f;
				ErrorKod=2;
				first = FALSE;
			}
		}
		pp = ip;
	}
	if(Ner==0)   StatePar.Format("%ld зн",(NumV ? NumV : 1));
	else   {     StatePar.Format("%ld/ ",Ner); StatePar+=s;}
}
//== Преобразовать координаты из пик. в лог.ед.==//
//CSize ANLZ::ConvToL(CSize s) 
//{
//	CSize sz = s;
//	sz.cy = -sz.cy;
//	pC->DPtoLP(&sz);
//	return sz;
//}

//======= Вывод значения без анализа =============//
int ANLZ::ZnachP(short Npar, long tn, long tk) 
{
	double v, u = pD->level(Npar, tn, tk);
	CString s;
	int n = 1;
	v=fabs(u);
	if(v>1000)n=0;
	if(v<1)   n=2;
	if(v<0.1) n=3;
	if((int(v*1000+0.5))%1000 == 0) n=0;
	if(n==0 && v<0.01) u=0;					// исключить "-0"
	StatePar = snm(u, n);
	return 0;
}
//===== Проверка выхода пар-ра за допуск на интервале =======//
int ANLZ::TestLev(short np, double U, double E, long t1, long t2)
{
	int  Ter=0, nd, n0p=0;
	long tp=0, t, d, d0, k = pI->Interval(np, t1, t2);
	for(long i=0; i<=k+1; ++i)
	{
		double F = pD->FisV(np, i, t);
		nd = fabs(F - U)>E ? 1:0;
		d0 = t - tp;
		if(n0p != nd || i == k+1 || i == 0)
		{
			if(d0 > pD->TBound  && i>0)
			{  d = n0p * d0; Ter+=d; }
			tp = t;
		}
		n0p = nd;
	}
	return (Ter > 0 ? 1 : 0);
}

void ANLZ::DubManal(short Npar, long tn, long tk)
{
	double Utek = pD->level(Npar,tn,tk); 
	if(Utek==ZERO)	{ ErrorKod=-9;  return; }
	if(star == 1) UrovTek = Utek;
	short k = checkV(Utek, arg1, arg2, StatePar );
	if(k)
	{
		if(checkV(Utek, arg3, arg4, StatePar ))
		{ ErrorKod= 1;  return; }
	}

	float a1, a2;
	if(k) {a1=arg3; a2=arg4;}
	else  {a1=arg1; a2=arg2;}
	CheckFunc(Npar, NumV, Utek, a1, a2, dev, Xpod);
}

void ANLZ::SetADD1(float x)
{
	RemarkStr.ADD1=x;
}
