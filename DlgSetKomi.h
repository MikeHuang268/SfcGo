#pragma once


// DlgSetKomi 对话框

class DlgSetKomi : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSetKomi)

public:
	DlgSetKomi(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgSetKomi();

// 对话框数据
	enum { IDD = IDD_SETKOMI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_fKomi;
};
