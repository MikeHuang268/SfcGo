
// MainFrm.cpp : CMainFrame ���ʵ��
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

extern int iScwd,iScht;//��Ļ�ֱ���
extern CString strSysDirectry;//ϵͳĿ¼
extern CString strDirectry;//����Ŀ¼
extern CString strOutputDirectry;//���Ŀ¼
extern CString Version;//�汾��
extern CString Edition;//�汾
extern int iLanguage;//����
extern int iCpuNum;//cpu���ˣ���
extern bool volatile bAnalysing;//���ڷ�����
extern CImage imBackImg;//����ͼƬ
extern int iState;//����״̬��0-���У�1-������
extern int iBoardSizeState;//���̴�С��0-9X9��1-13X13��2-19X19
extern CRect ctRect;//�ͻ�����С
DlgNotify* pDlgNotify;//��Ϣ��ʾ

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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
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
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������Ҫ��ͣ������������ɾ��������
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������



BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->hwnd==m_hWndMDIClient && pMsg->message==WM_PAINT)
		PostMessage(WM_PAINT);

	return CMDIFrameWnd::PreTranslateMessage(pMsg);
}


void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CMDIFrameWnd::OnPaint()
	//HBITMAP hBitmap=imBackImg.Detach(); // ���λͼ��� ����ת�� 
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
	/*HBITMAP hBitmap=img.Detach(); // ���λͼ��� ����ת�� 
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
	pDlgNotify->m_sNotify = "���ڼ������棬���Ժ򡤡���������";
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
  
    pNewDoc->SetTitle("�������"); 
	if (iLanguage == 0)
		pNewDoc->SetTitle("Tesuji analysis");
    pos = pNewDoc->GetFirstViewPosition();                           //���pNewDoc����ͼ  
    //CFormView *pView = (CFormView *)pNewDoc->GetNextView(pos);      
	CSfcGoView *pView = (CSfcGoView *)pNewDoc->GetNextView(pos);   
	//pView->m_iState=1;
	pView->btnBz.SetWindowTextA("��  ��");
 
    //CRect rt;  
    //pView->GetClientRect(rt);                                //��ȡ�ͻ�����  
	//GetClientRect(rt);
	//pView->MoveWindow(rt);
	
}


void CMainFrame::OnUpdateMSh(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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

	pNewDoc->SetTitle("�˻�����");  
	if (iLanguage == 0)
		pNewDoc->SetTitle("Play with computer");
	pos = pNewDoc->GetFirstViewPosition();                           //���pNewDoc����ͼ  
	//CFormView *pView = (CFormView *)pNewDoc->GetNextView(pos);      
	CSfcGoView *pView = (CSfcGoView *)pNewDoc->GetNextView(pos); 
	//pView->m_iState=2;
	pView->btnBz.SetWindowTextA("��ʼ����");
	pView->m_cmbMb.ResetContent();
	pView->m_cmbMb.AddString("����");
	pView->m_cmbMb.AddString("����");//�ö���;������;������;������;������;������;�ð���;�þ���;");
	pView->m_cmbMb.AddString("�ö���");
	pView->m_cmbMb.AddString("������");
	pView->m_cmbMb.AddString("������");
	pView->m_cmbMb.AddString("������");
	pView->m_cmbMb.AddString("������");
	pView->m_cmbMb.AddString("������");
	pView->m_cmbMb.AddString("�ð���");
	pView->m_cmbMb.AddString("�þ���");
	pView->m_cmbMb.SetCurSel(0);
	pView->m_btnAna.SetWindowTextA("��  ��");
	pView->m_radBlack.SetWindowTextA("���ִ��");
	pView->m_radInturn.EnableWindow(FALSE);

	//CRect rt;  
	//pView->GetClientRect(rt); 	//��ȡ�ͻ�����  
	//GetClientRect(rt);
	//pView->MoveWindow(rt);
	//pView->OnSize(8, rt.Width(), rt.Height());
	//pView->CloseWindow();
	//pView->ShowWindow(SW_SHOWMAXIMIZED);
}


void CMainFrame::OnUpdateMPlay(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
}


void CMainFrame::OnMPersistencestudy()
{
	pDlgNotify->m_sNotify = "���ڼ������棬���Ժ򡤡���������";
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

	pNewDoc->SetTitle("�����о�");
	if (iLanguage == 0)
		pNewDoc->SetTitle("Persistence study");
	pos = pNewDoc->GetFirstViewPosition();                           //���pNewDoc����ͼ  
	CSfcGoView* pView = (CSfcGoView*)pNewDoc->GetNextView(pos);
	pView->btnBz.SetWindowTextA("��  ��");

}


void CMainFrame::OnUpdateMPersistencestudy(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
}
