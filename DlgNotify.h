#pragma once


// DlgNotify 对话框

class DlgNotify : public CDialogEx
{
	DECLARE_DYNAMIC(DlgNotify)

public:
	DlgNotify(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgNotify();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOTIFY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	//CString m_sNotify = "正在加载引擎，请稍候······";
	CString m_sNotify;
};
