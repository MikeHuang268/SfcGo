#pragma once


// DlgSetKomi �Ի���

class DlgSetKomi : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSetKomi)

public:
	DlgSetKomi(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgSetKomi();

// �Ի�������
	enum { IDD = IDD_SETKOMI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_fKomi;
};
