// DlgSetKomi.cpp : 实现文件
//

#include "stdafx.h"
#include "SfcGo.h"
#include "DlgSetKomi.h"
#include "afxdialogex.h"


// DlgSetKomi 对话框

IMPLEMENT_DYNAMIC(DlgSetKomi, CDialogEx)

DlgSetKomi::DlgSetKomi(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgSetKomi::IDD, pParent)
	, m_fKomi(0)
{

}

DlgSetKomi::~DlgSetKomi()
{
}

void DlgSetKomi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_fKomi);
}


BEGIN_MESSAGE_MAP(DlgSetKomi, CDialogEx)
END_MESSAGE_MAP()


// DlgSetKomi 消息处理程序
