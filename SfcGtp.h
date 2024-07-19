#pragma once
class SfcGtp
{
public:
	SfcGtp(void);
	virtual ~SfcGtp(void);
	void CreateChildProcess(TCHAR appName[], TCHAR cmdLine[], TCHAR appDir[]);
	void WriteToPipe(CString str);
	void ReadFromPipe(CHAR chBuf[], DWORD& dwRead);
	void ErrorExit(PTSTR);
	bool LoadEngine(int type);
	void CloseEngine(void);
	//获取GTP消息
	CString* GetMsg(int& count);
	// 分割字符串为字符数组
	static CString* SplitString(CString strSource, CString strSeperator, int& count);
public:
	HANDLE m_hChildStd_IN_Rd = NULL;
	HANDLE m_hChildStd_IN_Wr = NULL;
	HANDLE m_hChildStd_OUT_Rd = NULL;
	HANDLE m_hChildStd_OUT_Wr = NULL;

	HANDLE m_hInputFile = NULL;
	int m_Id;
	int m_iType;
	CString m_sEngineName;
	bool m_bEngineLoaded;
	CString m_AppName;
	CString m_CmdLine;
	CString m_CmdLine1;
	CString m_AppDir;
};

