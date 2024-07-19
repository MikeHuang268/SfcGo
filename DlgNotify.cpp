// DlgNotify.cpp: 实现文件
//

#include "stdafx.h"
#include "SfcGo.h"
#include "DlgNotify.h"
#include "afxdialogex.h"


// DlgNotify 对话框

IMPLEMENT_DYNAMIC(DlgNotify, CDialogEx)

DlgNotify::DlgNotify(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NOTIFY, pParent)
	, m_sNotify(_T(""))
{

}

DlgNotify::~DlgNotify()
{
}

void DlgNotify::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sNotify);
}


BEGIN_MESSAGE_MAP(DlgNotify, CDialogEx)
END_MESSAGE_MAP()


// DlgNotify 消息处理程序


BOOL DlgNotify::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//GetDlgItem(IDC_EDIT1)->SetWindowTextA(m_sNotify);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
