#pragma once

class CTmiFile
{
private:
	std::ifstream FileUsi;
	std::ofstream FileKCB, FileKCBWorkTime;

	int k;
	
public:
	CTmiFile(void);
	~CTmiFile(void);
	CString ReadStr(int length);
	CString ReadKadr(int lk);
	void OpenUsiFile(CString path);
	void OpenTxtFile(CString path);
	void WriteToFileString(CString Info);
	void WriteToFileTitle(struct Title); 

	void PrintfTellg();

	int RetEof();
};

