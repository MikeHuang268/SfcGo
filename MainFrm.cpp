
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "SfcGo.h"

#include "MainFrm.h"
#include "SfcGoDoc.h"
#include "SfcGoView.h"
#include "DlgNotify.h"
#include "mmsystem.h"
//#include "afxcom_.h"
//#include <mciapi.h>

extern int iScwd,iScht;//屏幕分辨率
extern CString strSysDirectry;//系统目录
extern CString strDirectry;//数据目录
extern CString strOutputDirectry;//输出目录
extern CString Version;//版本号
extern CString Edition;//版本
extern int iLanguage;//语言
extern int iCpuNum;//cpu（核）数
extern bool volatile bAnalysing;//正在分析中
extern CImage imBackImg;//背景图片
extern int iState;//功能状态，0-空闲，1-死活题
extern int iBoardSizeState;//棋盘大小，0-9X9，1-13X13，2-19X19
extern CRect ctRect;//客户区大小
DlgNotify* pDlgNotify;//信息提示

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_COMMAND(ID_M_SH, &CMainFrame::OnMSh)
	ON_UPDATE_COMMAND_UI(ID_M_SH, &CMainFrame::OnUpdateMSh)
	ON_COMMAND(ID_M_PLAY, &CMainFrame::OnMPlay)
	ON_UPDATE_COMMAND_UI(ID_M_PLAY, &CMainFrame::OnUpdateMPlay)
	ON_COMMAND(ID_M_PERSISTENCESTUDY, &CMainFrame::OnMPersistencestudy)
	ON_UPDATE_COMMAND_UI(ID_M_PERSISTENCESTUDY, &CMainFrame::OnUpdateMPersistencestudy)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	pDlgNotify = new DlgNotify;
}

CMainFrame::~CMainFrame()
{
	delete pDlgNotify;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar, AFX_IDW_DOCKBAR_RIGHT);

	m_wndToolBar.ShowWindow(SW_HIDE);
	m_wndStatusBar.ShowWindow(SW_HIDE);

#ifndef _DEBUG
	PlaySound(strSysDirectry + "\\Bgm.wav", NULL, SND_ASYNC);
#endif // !_DEBUG

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->hwnd==m_hWndMDIClient && pMsg->message==WM_PAINT)
		PostMessage(WM_PAINT);

	return CMDIFrameWnd::PreTranslateMessage(pMsg);
}


void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CMDIFrameWnd::OnPaint()
	//HBITMAP hBitmap=imBackImg.Detach(); // 获得位图句柄 用以转换 
	/*CBitmap bmp;
	BITMAP szbmp;
	bmp.DeleteObject();
	bmp.Attach(hBitmap);
	bmp.GetObject(sizeof(BITMAP),&szbmp);
	CSize size(szbmp.bmWidth,szbmp.bmHeight);
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	CBitmap *oldbitmap=memdc.SelectObject(&bmp);
	CBitmap *oldbmp=memdc.SelectObject(&bmp);
	StretchBlt(dc.m_hDC,0,0,rect.Width(),rect.Height(),memdc.m_hDC,0,0,size.cx,size.cy,SRCCOPY);*/
	//imBackImg.Draw(dc.m_hDC,rect);
	//dc.DeleteDC();
	/*memdc.SelectObject(oldbitmap);

	memdc.DeleteDC();

	dc.DeleteDC();*/
	//CImage img;
	//img.Load(strSysDirectry+"\\mainback.jpg");
	//img.Draw(dc.m_hDC,rect);
	/*HBITMAP hBitmap=img.Detach(); // 获得位图句柄 用以转换 
	CBitmap bmp;
	BITMAP szbmp;
	bmp.DeleteObject();
	bmp.Attach(hBitmap);
	bmp.GetObject(sizeof(BITMAP),&szbmp);
	CSize size(szbmp.bmWidth,szbmp.bmHeight);
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	CBitmap *oldbitmap=memdc.SelectObject(&bmp);
	CBitmap *oldbmp=memdc.SelectObject(&bmp);
	//CDC *pDC=CDC::FromHandle(img.GetDC());img.ReleaseDC();
	StretchBlt(dc,0,0,rect.Width(),rect.Height(),memdc.m_hDC,0,0,size.cx,size.cy,SRCCOPY);*/
	//dc.DeleteDC();
	//img.ReleaseDC();
	//memdc.SelectObject(oldbitmap);

	//memdc.DeleteDC();

	//dc.DeleteDC();

	//CMDIFrameWnd::OnPaint();
	CRect rect;
	GetClientRect(&rect);
	CDC Dc;
	Dc.m_hDC=::GetDC(m_hWndMDIClient);
	imBackImg.Draw(Dc.m_hDC,rect);
	//ReleaseDC(&Dc);
	//imBackImg.Draw(dc.m_hDC, rect);
	ReleaseDC(&dc);
}


void CMainFrame::OnMSh()
{
	pDlgNotify->m_sNotify = "正在加载引擎，请稍候······";
	if (iLanguage == 0)
		pDlgNotify->m_sNotify = "Loading engine, please wait...";
	pDlgNotify->Create(IDD_NOTIFY, this);
	pDlgNotify->ShowWindow(SW_SHOW);
	pDlgNotify->UpdateWindow();
	iState = 1;
    POSITION pos;                                         
    ASSERT( AfxGetApp() != NULL );  
    pos = AfxGetApp()->GetFirstDocTemplatePosition();  
    CDocument *pNewDoc = AfxGetApp()->GetNextDocTemplate( pos )->OpenDocumentFile( NULL );     
  
    pNewDoc->SetTitle("死活分析"); 
	if (iLanguage == 0)
		pNewDoc->SetTitle("Tesuji analysis");
    pos = pNewDoc->GetFirstViewPosition();                           //获得pNewDoc的视图  
    //CFormView *pView = (CFormView *)pNewDoc->GetNextView(pos);      
	CSfcGoView *pView = (CSfcGoView *)pNewDoc->GetNextView(pos);   
	//pView->m_iState=1;
	pView->btnBz.SetWindowTextA("摆  子");
 
    //CRect rt;  
    //pView->GetClientRect(rt);                                //获取客户区域  
	//GetClientRect(rt);
	//pView->MoveWindow(rt);
	
}


void CMainFrame::OnUpdateMSh(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CMainFrame::OnMPlay()
{
	/*/MediaPlayer
	MCI_OPEN_PARMS mciOpen;

	MCIERROR mciError;

	mciOpen.lpstrDeviceType = NULL;// "mpegvideo";
	CString str= strSysDirectry + "\\bgm.mp3";
	mciOpen.lpstrElementName = str;// strSysDirectry + "\\bgm.mp3";
	mciError = mciSendCommand(0, MCI_OPEN, MCI_NOTIFY | MCI_OPEN_ELEMENT, (DWORD)&mciOpen);
	UINT DeviceID = mciOpen.wDeviceID;

	MCI_PLAY_PARMS mciPlay;



	mciError = mciSendCommand(DeviceID, MCI_PLAY, MCI_FROM, (DWORD)&mciPlay);*/
	//pDlgNotify->DestroyWindow();
	//return;
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_RIGHT);
	iState = 2;
	POSITION pos;                                         
	ASSERT( AfxGetApp() != NULL );  
	pos = AfxGetApp()->GetFirstDocTemplatePosition();  
	CDocument *pNewDoc = AfxGetApp()->GetNextDocTemplate( pos )->OpenDocumentFile( NULL );     

	pNewDoc->SetTitle("人机对弈");  
	if (iLanguage == 0)
		pNewDoc->SetTitle("Play with computer");
	pos = pNewDoc->GetFirstViewPosition();                           //获得pNewDoc的视图  
	//CFormView *pView = (CFormView *)pNewDoc->GetNextView(pos);      
	CSfcGoView *pView = (CSfcGoView *)pNewDoc->GetNextView(pos); 
	//pView->m_iState=2;
	pView->btnBz.SetWindowTextA("开始对弈");
	pView->m_cmbMb.ResetContent();
	pView->m_cmbMb.AddString("分先");
	pView->m_cmbMb.AddString("让先");//让二子;让三子;让四子;让五子;让六子;让七子;让八子;让九子;");
	pView->m_cmbMb.AddString("让二子");
	pView->m_cmbMb.AddString("让三子");
	pView->m_cmbMb.AddString("让四子");
	pView->m_cmbMb.AddString("让五子");
	pView->m_cmbMb.AddString("让六子");
	pView->m_cmbMb.AddString("让七子");
	pView->m_cmbMb.AddString("让八子");
	pView->m_cmbMb.AddString("让九子");
	pView->m_cmbMb.SetCurSel(0);
	pView->m_btnAna.SetWindowTextA("悔  棋");
	pView->m_radBlack.SetWindowTextA("玩家执黑");
	pView->m_radInturn.EnableWindow(FALSE);

	//CRect rt;  
	//pView->GetClientRect(rt); 	//获取客户区域  
	//GetClientRect(rt);
	//pView->MoveWindow(rt);
	//pView->OnSize(8, rt.Width(), rt.Height());
	//pView->CloseWindow();
	//pView->ShowWindow(SW_SHOWMAXIMIZED);
}


void CMainFrame::OnUpdateMPlay(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CMainFrame::OnMPersistencestudy()
{
	pDlgNotify->m_sNotify = "正在加载引擎，请稍候······";
	if (iLanguage == 0)
		pDlgNotify->m_sNotify = "Loading engine, please wait...";
	pDlgNotify->Create(IDD_NOTIFY, this);
	pDlgNotify->ShowWindow(SW_SHOW);
	pDlgNotify->UpdateWindow();
	iState = 3;
	POSITION pos;
	ASSERT(AfxGetApp() != NULL);
	pos = AfxGetApp()->GetFirstDocTemplatePosition();
	CDocument* pNewDoc = AfxGetApp()->GetNextDocTemplate(pos)->OpenDocumentFile(NULL);

	pNewDoc->SetTitle("序盘研究");
	if (iLanguage == 0)
		pNewDoc->SetTitle("Persistence study");
	pos = pNewDoc->GetFirstViewPosition();                           //获得pNewDoc的视图  
	CSfcGoView* pView = (CSfcGoView*)pNewDoc->GetNextView(pos);
	pView->btnBz.SetWindowTextA("摆  子");

}


void CMainFrame::OnUpdateMPersistencestudy(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}
