
// SfcGo.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "SfcGo.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "SfcGoDoc.h"
#include "SfcGoView.h"
//#include "Sfc.h"
#include "direct.h"

/*/gnugo����
extern "C"
{
	#include "gnugo.h"
	#include "liberty.h"
};*/

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int iScwd,iScht;//��Ļ�ֱ���
CString strSysDirectry;//ϵͳĿ¼
CString strDirectry;//����Ŀ¼
CString strImgDirectry;//ͼ���ļ�Ŀ¼
CString strOutputDirectry;//���Ŀ¼
CString Version;//�汾��
CString Edition;//�汾
int iLanguage = 1;//����
int iCpuNum;//cpu���ˣ���
CString sPlayerName;//�����
int iPlayerLevel;//��ҵȼ�
int iEngineNum = 1;//������
int iEngineTypes[10];//����ID
CString sEngineNames[10];//��������
CString sEngineAppNames[10];//����ִ���ļ���
CString sEngineAppDirs[10];//����Ŀ¼
CString sEngineCmdLines[10];//����������
CString sEngineCmdLines1[10];//����������1��������������ǿ����
int iPlayer1 = 0;//�������ߣ�0-��ң�1-����
int iLevel1 = 0;//����ִ��ʱ�ĵȼ���1-���Σ�10-��ʥ
int iTime1 = 0;//����ִ��ʱ��˼��ʱ����0-15�룬1-30�룬2-60�룬3-120��
int iEngine1 = 1;//��������ѡ��
int iPlayer2 = 1;//�������ߣ���0-��ң�1-����
int iLevel2 = 0;//����ִ��ʱ�ĵȼ���1-���Σ�10-��ʥ
int iTime2 = 0;//����ִ��ʱ��˼��ʱ����0-15�룬1-30�룬2-60�룬3-120��
int iEngine2 = 1;//��������ѡ��
int iRule = 0;//���Ĺ���0-�й���1-�ձ���2-����
int iBoard = 0;//���̹��0-19·��1-13·��2-9·
int iKomi = 35;//��Ŀ��0-����10Ŀ��40-��10Ŀ
int iHandi = 0;//��������0-���ȣ�1-���ȣ�2����-������
bool bCoord = true;//�Ƿ���������
bool bAnimate = true;//�Ƿ������Ӷ���
bool bThinkProgress = true;//�Ƿ���ʾ����˼������
bool bShowInfo = true;//�Ƿ���ʾ��Ϣ�͹�����
bool bShowWinRate = true;//�Ƿ���ʾʤ��ͼ
bool bShowAna = true;//�Ƿ���ʾ��������
bool bShowMoveRec = true;//�Ƿ���ʾ���ּ�¼
bool bPutStoneSound = true;//�Ƿ񲥷���������
bool bCaptureSound = true;//�Ƿ񲥷���������
bool bPickStoneSound = true;//�Ƿ񲥷Ŵ������ʰ�ӵ�����
bool bPushClockSound = true;//�Ƿ񲥷Ű���ʱ�ӵ�����
bool bByoSound = true;//�Ƿ񲥷Ŷ�����
int iLDlevel=0;//������ȼ���0-�ֽ1-������2-�м���3-�߼�
int iQuest0=1;//�ֽ���ϰ��ǰ���
int iQuest1=1;//�������ǰ���
int iQuest2=1;//�м����ǰ���
int iQuest3=1;//�߼����ǰ���
int iQuestMax0=366;//�ֽ���ϰ������
int iQuestMax1=441;//��������������
int iQuestMax2=450;//�м�����������
int iQuestMax3=433;//�߼�����������
bool bLog = false;;//�Ƿ��¼��־
bool volatile bAnalysing=false;//���ڷ�����
CImage imBackImg;//����ͼƬ
CImage imBoardImg;//���̱���ͼƬ
CImage imBlackStone;//������ͼƬ
CImage imWhiteStone;//������ͼƬ
CImage imBlackInfo;//���巽��ϢͼƬ
CImage imWhiteInfo;//���巽��ϢͼƬ
CImage imProgressBar;//��ʱ/˼������ͼƬ
CImage imPlayInfo;//�Ծ���ϢͼƬ
CImage imToolBox;//������ͼƬ
CImage imBackGound;//�Ծֵ��汳��ͼƬ
CImage imNewNormal;//�¶Ծְ�ťͼƬ
CImage imNewHover;//�¶Ծ������ͣͼƬ
CImage imNewDown;//�¶Ծ���갴��ͼƬ
CImage imNewDisable;//�¶Ծְ�ť����ͼƬ
CImage imOpenNormal;//�����װ�ťͼƬ
CImage imOpenHover;
CImage imOpenDown;
CImage imOpenDisable;
CImage imOpenNormal0;//�����װ�ťͼƬ
CImage imOpenHover0;
CImage imOpenDown0;
CImage imOpenDisable0;
CImage imSaveNormal;//���水ťͼƬ
CImage imSaveHover;
CImage imSaveDown;
CImage imSaveDisable;
CImage imReopenNormal;//�����Ծְ�ťͼƬ
CImage imReopenHover;
CImage imReopenDown;
CImage imReopenDisable;
CImage imAreaNormal;//�����жϰ�ťͼƬ
CImage imAreaHover;
CImage imAreaDown;
CImage imAreaDisable;
CImage imAreaNormal0;//�����жϰ�ťͼƬ
CImage imAreaHover0;
CImage imAreaDown0;
CImage imAreaDisable0;
CImage imResignNormal;//���䰴ťͼƬ
CImage imResignHover;
CImage imResignDown;
CImage imResignDisable;
CImage imGoFirstNormal;//�ص������ťͼƬ
CImage imGoFirstHover;
CImage imGoFirstDown;
CImage imGoFirstDisable;
CImage imGoFiveBackNormal;//�����岽��ťͼƬ
CImage imGoFiveBackHover;
CImage imGoFiveBackDown;
CImage imGoFiveBackDisable;
CImage imGoBackNormal;//���˰�ťͼƬ
CImage imGoBackHover;
CImage imGoBackDown;
CImage imGoBackDisable;
CImage imGoForwardNormal;//ǰ����ťͼƬ
CImage imGoForwardHover;
CImage imGoForwardDown;
CImage imGoForwardDisable;
CImage imGoFiveForwardNormal;//ǰ���岽��ťͼƬ
CImage imGoFiveForwardHover;
CImage imGoFiveForwardDown;
CImage imGoFiveForwardDisable;
CImage imGoLastNormal;//ǰ�����װ�ťͼƬ
CImage imGoLastHover;
CImage imGoLastDown;
CImage imGoLastDisable;
CImage imExitNormal;//�˳���ťͼƬ
CImage imExitHover;
CImage imExitDown;
CImage imExitDisable;
CImage imPassNormal;//PASS��ťͼƬ
CImage imPassHover;
CImage imPassDown;
CImage imPassDisable;
CImage imRetractNormal;//���尴ťͼƬ
CImage imRetractHover;
CImage imRetractDown;
CImage imRetractDisable;
CImage imHintNormal;//֧�а�ťͼƬ
CImage imHintHover;
CImage imHintDown;
CImage imHintDisable;
CImage imPauseNormal;//��ͣ��ťͼƬ
CImage imPauseHover;
CImage imPauseDown;
CImage imPauseDisable;
CImage imChangeStoneNormal;//�����Ծ�
CImage imChangeStoneHover;
CImage imChangeStoneDown;
CImage imChangeStoneDisable;
CImage imRecDesk;//���ּ�¼��ͼƬ
CImage imRec;//���ּ�¼ͼƬ
CImage imRecSelected;//ѡ�����ּ�¼ͼƬ
CImage imChart;//ʤ��ͼ��ͼƬ
CImage imRecTitle;//��¼����ͼƬ
//CImage imEmptyNormal;//�հ�ťͼƬ
//CImage imEmptyHover;
//CImage imEmptyDown;
//CImage imEmptyDisable;
CImage imPutStoneNormal;//���ӳ��ⰴťͼƬ
CImage imPutStoneHover;
CImage imPutStoneDown;
CImage imPutStoneDisable;
CImage imContinueNormal;//�������ⰴťͼƬ
CImage imContinueHover;
CImage imContinueDown;
CImage imContinueDisabel;
CImage imDifficultyNormal;//�Ѷ�ѡ��ťͼƬ
CImage imDifficultyHover;
CImage imDifficultyDown;
CImage imDifficultyDisable;
CImage imTesujiNormal;//�ֽ���ϰ��ťͼƬ
CImage imTesujiHover;
CImage imElementaryNormal;//�������ťͼƬ
CImage imElementaryHover;
CImage imMiddleNormal;//�м����ťͼƬ
CImage imMiddleHover;
CImage imAdvancedNormal;//�߼����ťͼƬ
CImage imAdvanceeHover;
CImage imPutBlackNormal;//�ڷź��Ӱ�ťͼƬ
CImage imPutBlackHover;
CImage imPutBlackDown;
CImage imPutBlackDisable;
CImage imPutWhiteNormal;//�ڷŰ��Ӱ�ťͼƬ
CImage imPutWhiteHover;
CImage imPutWhiteDown;
CImage imPutWhiteDisable;
CImage imBlackFirstNormal;//���Ȱ�ťͼƬ
CImage imBlackFirstHover;
CImage imBlackFirstDown;
CImage imBlackFirstDisable;
CImage imWhiteFirstNormal;//���Ȱ�ťͼƬ
CImage imWhiteFirstHover;
CImage imWhiteFirstDown;
CImage imWhiteFirstDisable;
CImage imStudyNormal;//�о���ťͼƬ
CImage imStudyHover;
CImage imStudyDown;
CImage imStudyDisable;
CImage imSolveNormal;//���������ʼ���ⰴťͼƬ
CImage imSolveHover;
CImage imSolveDown;
CImage imSolveDisable;
CImage imAIanaNormal;//AI������ťͼƬ
CImage imAIanaHover;
CImage imAIanaDown;
CImage imAIanaDisable;
CImage imPutStoneStudyNormal;//�����о���ťͼƬ
CImage imPutStoneStudyHover;
CImage imPutStoneStudyDown;
CImage imPutStoneStudyDisable;
CImage imPassMoveNormal;//PASSһ�ְ�ťͼƬ
CImage imPassMoveHover;
CImage imPassMoveDown;
CImage imPassMoveDisable;
CImage imSolutionNormal;//�鿴��������ťͼƬ
CImage imSolutionHover;
CImage imSolutionDown;
CImage imSolutionDisable;
CImage imRedoNormal;//������ťͼƬ
CImage imRedoHover;
CImage imRedoDown;
CImage imRedoDisable;
CImage imSolveNormal2;//�����������С��ť
CImage imSolveHover2;
CImage imSolveDown2;
CImage imSolveDisable2;
CImage imStudyNormal2;//�������о�С��ť
CImage imStudyHover2;
CImage imStudyDown2;
CImage imStudyDisable2;
CImage imAnaAllNormal;//ȫ�̷�����ťͼƬ
CImage imAnaAllHover;
CImage imAnaAllDown;
CImage imAnaAllDisable;
CImage imReturnNormal;//���ذ�ťͼƬ
CImage imReturnHover;
CImage imReturnDown;
CImage imReturnDisabel;
//CImage imStoneEffect;
int iState=0;//����״̬��0-���У�1-������
int iBoardSizeState=2;//���̴�С��0-9X9��1-13X13��2-19X19
int iBoardSize=19;//���̴�С
CRect ctRect;//�ͻ�����С

// CSfcGoApp

BEGIN_MESSAGE_MAP(CSfcGoApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CSfcGoApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CSfcGoApp ����

CSfcGoApp::CSfcGoApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("SfcGo.AppID.Version2.0"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CSfcGoApp ����

CSfcGoApp theApp;


// CSfcGoApp ��ʼ��

BOOL CSfcGoApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();
	iScwd=GetSystemMetrics(SM_CXSCREEN);
	iScht=GetSystemMetrics(SM_CYSCREEN);
	if(iScwd<800||iScht<600){
		AfxMessageBox(_T("�˳������ʾ���ֱ�����Ҫ��,\n�뽫�ֱ��ʵ���800x600����!"),NULL,MB_OK);
		exit(0);
	}
	//ȷ������Ŀ¼
	char str[_MAX_PATH];
	_getcwd(str,_MAX_PATH);
	strSysDirectry=str;
	strDirectry=str;
	strOutputDirectry=str;
	strSysDirectry+="\\Sys";
	strDirectry+="\\Data";
	strOutputDirectry+="\\Output";
	//��ȡϵͳ�����ļ�
	Sfc::ReadSysIni();
	strImgDirectry = strDirectry + "\\Img";
	switch (iLanguage)
	{
	case 0:
		strImgDirectry += "\\en";
		break;
	case 1:
		strImgDirectry += "\\cn";
		break;
	}
	//��ȡͼƬ
	imBackImg.Load(strDirectry+"\\Img\\mainback.jpg");
	imBoardImg.Load(strDirectry+"\\Img\\wqboard.jpg");
	imBlackStone.Load(strDirectry+"\\Img\\blackstone.png");
	imWhiteStone.Load(strDirectry+"\\Img\\whitestone.png");
	imBlackInfo.Load(strDirectry + "\\Img\\blackinfo.png");
	imWhiteInfo.Load(strDirectry + "\\Img\\whiteinfo.png");
	imProgressBar.Load(strDirectry + "\\Img\\progressbar.png");
	imPlayInfo.Load(strDirectry + "\\Img\\playinfo.png");
	imToolBox.Load(strDirectry + "\\Img\\toolbox.jpg");
	imBackGound.Load(strDirectry + "\\Img\\background.jpg");
	imGoFirstNormal.Load(strDirectry + "\\Img\\GoFirst_Normal.jpg");
	imGoFirstHover.Load(strDirectry + "\\Img\\GoFirst_Hover.jpg");
	imGoFirstDown.Load(strDirectry + "\\Img\\GoFirst_Down.jpg");
	imGoFirstDisable.Load(strDirectry + "\\Img\\GoFirst_Disable.jpg");
	imGoFiveBackNormal.Load(strDirectry + "\\Img\\GoFiveBack_Normal.jpg");
	imGoFiveBackHover.Load(strDirectry + "\\Img\\GoFiveBack_Hover.jpg");
	imGoFiveBackDown.Load(strDirectry + "\\Img\\GoFiveBack_Down.jpg");
	imGoFiveBackDisable.Load(strDirectry + "\\Img\\GoFiveBack_Disable.jpg");
	imGoBackNormal.Load(strDirectry + "\\Img\\GoBack_Normal.jpg");
	imGoBackHover.Load(strDirectry + "\\Img\\GoBack_Hover.jpg");
	imGoBackDown.Load(strDirectry + "\\Img\\GoBack_Down.jpg");
	imGoBackDisable.Load(strDirectry + "\\Img\\GoBack_Disable.jpg");
	imGoForwardNormal.Load(strDirectry + "\\Img\\GoForward_Normal.jpg");
	imGoForwardHover.Load(strDirectry + "\\Img\\GoForward_Hover.jpg");
	imGoForwardDown.Load(strDirectry + "\\Img\\GoForward_Down.jpg");
	imGoForwardDisable.Load(strDirectry + "\\Img\\GoForward_Disable.jpg");
	imGoFiveForwardNormal.Load(strDirectry + "\\Img\\GoFiveForward_Normal.jpg");
	imGoFiveForwardHover.Load(strDirectry + "\\Img\\GoFiveForward_Hover.jpg");
	imGoFiveForwardDown.Load(strDirectry + "\\Img\\GoFiveForward_Down.jpg");
	imGoFiveForwardDisable.Load(strDirectry + "\\Img\\GoFiveForward_Disable.jpg");
	imGoLastNormal.Load(strDirectry + "\\Img\\GoLast_Normal.jpg");
	imGoLastHover.Load(strDirectry + "\\Img\\GoLast_Hover.jpg");
	imGoLastDown.Load(strDirectry + "\\Img\\GoLast_Down.jpg");
	imGoLastDisable.Load(strDirectry + "\\Img\\GoLast_Disable.jpg");
	imRecDesk.Load(strDirectry + "\\Img\\RecDesk.jpg");
	imRec.Load(strDirectry + "\\Img\\Rec.jpg");
	imRecSelected.Load(strDirectry + "\\Img\\Rec_Selected.jpg");
	imChart.Load(strDirectry + "\\Img\\Chart.jpg");
	imRecTitle.Load(strDirectry + "\\Img\\RecTitle.jpg");
	//imEmptyNormal.Load(strDirectry + "\\Img\\Empty_Normal.jpg");
	//imEmptyHover.Load(strDirectry + "\\Img\\Empty_Hover.jpg");
	//imEmptyDown.Load(strDirectry + "\\Img\\Empty_Down.jpg");
	//imEmptyDisable.Load(strDirectry + "\\Img\\Empty_Disable.jpg");
	LoadImg();
	//imStoneEffect.Load(strDirectry + "\\Img\\stoneEffect.tif");
	//��ʼ�������
	srand(unsigned int(time(NULL)));
	/*/��ʼ��gnugo����
	time_t t=time(NULL);
	init_gnugo(128,time_t(NULL));*/

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��

	if (iLanguage == 0)
	{
		SetThreadUILanguage(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
	}
	else
	{
		SetThreadUILanguage(MAKELANGID(LANG_CHINESE_SIMPLIFIED, SUBLANG_CHINESE_SIMPLIFIED));
	}
	SetRegistryKey(_T("SfcGo"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_SfcGoTYPE,
		RUNTIME_CLASS(CSfcGoDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CSfcGoView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand=CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);



	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �������ѳ�ʼ���������ʾ����������и���
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	AfxGetMainWnd()->PostMessageA(WM_PAINT);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CSfcGoApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CSfcGoApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CSfcGoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CSfcGoApp ��Ϣ�������


void CSfcGoApp::LoadImg()
{
	imNewNormal.Load(strImgDirectry + "\\New_Normal.jpg");
	imNewHover.Load(strImgDirectry + "\\New_Hover.jpg");
	imNewDown.Load(strImgDirectry + "\\New_Down.jpg");
	imNewDisable.Load(strImgDirectry + "\\New_Disable.jpg");
	imOpenNormal.Load(strImgDirectry + "\\Open_Normal.jpg");
	imOpenHover.Load(strImgDirectry + "\\Open_Hover.jpg");
	imOpenDown.Load(strImgDirectry + "\\Open_Down.jpg");
	imOpenDisable.Load(strImgDirectry + "\\Open_Disable.jpg");
	imSaveNormal.Load(strImgDirectry + "\\Save_Normal.jpg");
	imSaveHover.Load(strImgDirectry + "\\Save_Hover.jpg");
	imSaveDown.Load(strImgDirectry + "\\Save_Down.jpg");
	imSaveDisable.Load(strImgDirectry + "\\Save_Disable.jpg");
	imReopenNormal.Load(strImgDirectry + "\\Reopen_Normal.jpg");
	imReopenHover.Load(strImgDirectry + "\\Reopen_Hover.jpg");
	imReopenDown.Load(strImgDirectry + "\\Reopen_Down.jpg");
	imReopenDisable.Load(strImgDirectry + "\\Reopen_Disable.jpg");
	imAreaNormal.Load(strImgDirectry + "\\Area_Normal.jpg");
	imAreaHover.Load(strImgDirectry + "\\Area_Hover.jpg");
	imAreaDown.Load(strImgDirectry + "\\Area_Down.jpg");
	imAreaDisable.Load(strImgDirectry + "\\Area_Disable.jpg");
	imResignNormal.Load(strImgDirectry + "\\Resignation_Normal.jpg");
	imResignHover.Load(strImgDirectry + "\\Resignation_Hover.jpg");
	imResignDown.Load(strImgDirectry + "\\Resignation_Down.jpg");
	imResignDisable.Load(strImgDirectry + "\\Resignation_Disable.jpg");
	imExitNormal.Load(strImgDirectry + "\\EditEnd_Normal.jpg");
	imExitHover.Load(strImgDirectry + "\\EditEnd_Hover.jpg");
	imExitDown.Load(strImgDirectry + "\\EditEnd_Down.jpg");
	imExitDisable.Load(strImgDirectry + "\\EditEnd_Disable.jpg");
	imChangeStoneNormal.Load(strImgDirectry + "\\ChangeStone_Normal.jpg");
	imChangeStoneHover.Load(strImgDirectry + "\\ChangeStone_Hover.jpg");
	imChangeStoneDown.Load(strImgDirectry + "\\ChangeStone_Down.jpg");
	imChangeStoneDisable.Load(strImgDirectry + "\\ChangeStone_Disable.jpg");
	imPassNormal.Load(strImgDirectry + "\\Pass_Normal.jpg");
	imPassHover.Load(strImgDirectry + "\\Pass_Hover.jpg");
	imPassDown.Load(strImgDirectry + "\\Pass_Down.jpg");
	imPassDisable.Load(strImgDirectry + "\\Pass_Disable.jpg");
	imPauseNormal.Load(strImgDirectry + "\\Pause_Normal.jpg");
	imPauseHover.Load(strImgDirectry + "\\Pause_Hover.jpg");
	imPauseDown.Load(strImgDirectry + "\\Pause_Down.jpg");
	imPauseDisable.Load(strImgDirectry + "\\Pause_Disable.jpg");
	imRetractNormal.Load(strImgDirectry + "\\Retract_Normal.jpg");
	imRetractHover.Load(strImgDirectry + "\\Retract_Hover.jpg");
	imRetractDown.Load(strImgDirectry + "\\Retract_Down.jpg");
	imRetractDisable.Load(strImgDirectry + "\\Retract_Disable.jpg");
	imHintNormal.Load(strImgDirectry + "\\Hint_Normal.jpg");
	imHintHover.Load(strImgDirectry + "\\Hint_Hover.jpg");
	imHintDown.Load(strImgDirectry + "\\Hint_Down.jpg");
	imHintDisable.Load(strImgDirectry + "\\Hint_Disable.jpg");
	imPutStoneNormal.Load(strImgDirectry + "\\PutStone_Normal.jpg");
	imPutStoneHover.Load(strImgDirectry + "\\PutStone_Hover.jpg");
	imPutStoneDown.Load(strImgDirectry + "\\PutStone_Down.jpg");
	imPutStoneDisable.Load(strImgDirectry + "\\PutStone_Disable.jpg");
	imContinueNormal.Load(strImgDirectry + "\\Continue_Normal.jpg");
	imContinueHover.Load(strImgDirectry + "\\Continue_Hover.jpg");
	imContinueDown.Load(strImgDirectry + "\\Continue_Down.jpg");
	imContinueDisabel.Load(strImgDirectry + "\\Continue_Disable.jpg");
	imDifficultyNormal.Load(strImgDirectry + "\\Difficulty_Normal.jpg");
	imDifficultyHover.Load(strImgDirectry + "\\Difficulty_Hover.jpg");
	imDifficultyDown.Load(strImgDirectry + "\\Difficulty_Down.jpg");
	imDifficultyDisable.Load(strImgDirectry + "\\Difficulty_Disable.jpg");
	imTesujiNormal.Load(strImgDirectry + "\\Tesuji_Normal.jpg");
	imTesujiHover.Load(strImgDirectry + "\\Tesuji_Hover.jpg");
	imElementaryNormal.Load(strImgDirectry + "\\Elementary_Normal.jpg");
	imElementaryHover.Load(strImgDirectry + "\\Elementary_Hover.jpg");
	imMiddleNormal.Load(strImgDirectry + "\\Middle_Normal.jpg");
	imMiddleHover.Load(strImgDirectry + "\\Middle_Hover.jpg");
	imAdvancedNormal.Load(strImgDirectry + "\\Advanced_Normal.jpg");
	imAdvanceeHover.Load(strImgDirectry + "\\Advanced_Hover.jpg");
	imPutBlackNormal.Load(strImgDirectry + "\\PutBlack_Normal.jpg");
	imPutBlackHover.Load(strImgDirectry + "\\PutBlack_Hover.jpg");
	imPutBlackDown.Load(strImgDirectry + "\\PutBlack_Down.jpg");
	imPutBlackDisable.Load(strImgDirectry + "\\PutBlack_Disable.jpg");
	imPutWhiteNormal.Load(strImgDirectry + "\\PutWhite_Normal.jpg");
	imPutWhiteHover.Load(strImgDirectry + "\\PutWhite_Hover.jpg");
	imPutWhiteDown.Load(strImgDirectry + "\\PutWhite_Down.jpg");
	imPutWhiteDisable.Load(strImgDirectry + "\\PutWhite_Disable.jpg");
	imBlackFirstNormal.Load(strImgDirectry + "\\BlackFirst_Normal.jpg");
	imBlackFirstHover.Load(strImgDirectry + "\\BlackFirst_Hover.jpg");
	imBlackFirstDown.Load(strImgDirectry + "\\BlackFirst_Down.jpg");
	imBlackFirstDisable.Load(strImgDirectry + "\\BlackFirst_Disable.jpg");
	imWhiteFirstNormal.Load(strImgDirectry + "\\WhiteFirst_Normal.jpg");
	imWhiteFirstHover.Load(strImgDirectry + "\\WhiteFirst_Hover.jpg");
	imWhiteFirstDown.Load(strImgDirectry + "\\WhiteFirst_Down.jpg");
	imWhiteFirstDisable.Load(strImgDirectry + "\\WhiteFirst_Disable.jpg");
	imStudyNormal.Load(strImgDirectry + "\\Study_Normal.jpg");
	imStudyHover.Load(strImgDirectry + "\\Study_Hover.jpg");
	imStudyDown.Load(strImgDirectry + "\\Study_Down.jpg");
	imStudyDisable.Load(strImgDirectry + "\\Study_Disable.jpg");
	imSolveNormal.Load(strImgDirectry + "\\Solve_Normal.jpg");
	imSolveHover.Load(strImgDirectry + "\\Solve_Hover.jpg");
	imSolveDown.Load(strImgDirectry + "\\Solve_Down.jpg");
	imSolveDisable.Load(strImgDirectry + "\\Solve_Disable.jpg");
	imAIanaNormal.Load(strImgDirectry + "\\AIana_Normal.jpg");
	imAIanaHover.Load(strImgDirectry + "\\AIana_Hover.jpg");
	imAIanaDown.Load(strImgDirectry + "\\AIana_Down.jpg");
	imAIanaDisable.Load(strImgDirectry + "\\AIana_Disable.jpg");
	imPutStoneStudyNormal.Load(strImgDirectry + "\\PutStoneStudy_Normal.jpg");
	imPutStoneStudyHover.Load(strImgDirectry + "\\PutStoneStudy_Hover.jpg");
	imPutStoneStudyDown.Load(strImgDirectry + "\\PutStoneStudy_Down.jpg");
	imPutStoneStudyDisable.Load(strImgDirectry + "\\PutStoneStudy_Disable.jpg");
	imPassMoveNormal.Load(strImgDirectry + "\\PassMove_Normal.jpg");
	imPassMoveHover.Load(strImgDirectry + "\\PassMove_Hover.jpg");
	imPassMoveDown.Load(strImgDirectry + "\\PassMove_Down.jpg");
	imPassMoveDisable.Load(strImgDirectry + "\\PassMove_Disable.jpg");
	imSolutionNormal.Load(strImgDirectry + "\\Solution_Normal.jpg");
	imSolutionHover.Load(strImgDirectry + "\\Solution_Hover.jpg");
	imSolutionDown.Load(strImgDirectry + "\\Solution_Down.jpg");
	imSolutionDisable.Load(strImgDirectry + "\\Solution_Disable.jpg");
	imRedoNormal.Load(strImgDirectry + "\\Redo_Normal.jpg");
	imRedoHover.Load(strImgDirectry + "\\Redo_Hover.jpg");
	imRedoDown.Load(strImgDirectry + "\\Redo_Down.jpg");
	imRedoDisable.Load(strImgDirectry + "\\Redo_Disable.jpg");
	imSolveNormal2.Load(strImgDirectry + "\\Solve2_Normal.jpg");
	imSolveHover2.Load(strImgDirectry + "\\Solve2_Hover.jpg");
	imSolveDown2.Load(strImgDirectry + "\\Solve2_Down.jpg");
	imSolveDisable2.Load(strImgDirectry + "\\Solve2_Disable.jpg");
	imStudyNormal2.Load(strImgDirectry + "\\Study2_Normal.jpg");
	imStudyHover2.Load(strImgDirectry + "\\Study2_Hover.jpg");
	imStudyDown2.Load(strImgDirectry + "\\Study2_Down.jpg");
	imStudyDisable2.Load(strImgDirectry + "\\Study2_Disable.jpg");
	imAnaAllNormal.Load(strImgDirectry + "\\AnaAll_Normal.jpg");
	imAnaAllHover.Load(strImgDirectry + "\\AnaAll_Hover.jpg");
	imAnaAllDown.Load(strImgDirectry + "\\AnaAll_Down.jpg");
	imAnaAllDisable.Load(strImgDirectry + "\\AnaAll_Disable.jpg");
	imAreaNormal0.Load(strImgDirectry + "\\Area0_Normal.jpg");
	imAreaHover0.Load(strImgDirectry + "\\Area0_Hover.jpg");
	imAreaDown0.Load(strImgDirectry + "\\Area0_Down.jpg");
	imAreaDisable0.Load(strImgDirectry + "\\Area0_Disable.jpg");
	imReturnNormal.Load(strImgDirectry + "\\Return_Normal.jpg");
	imReturnHover.Load(strImgDirectry + "\\Return_Hover.jpg");
	imReturnDown.Load(strImgDirectry + "\\Return_Down.jpg");
	imReturnDisabel.Load(strImgDirectry + "\\Return_Disable.jpg");
	if (iLanguage == 1)
	{
		imOpenNormal0.Load(strImgDirectry + "\\Open0_Normal.jpg");
		imOpenHover0.Load(strImgDirectry + "\\Open0_Hover.jpg");
		imOpenDown0.Load(strImgDirectry + "\\Open0_Down.jpg");
		imOpenDisable0.Load(strImgDirectry + "\\Open0_Disable.jpg");
	}
}

void CSfcGoApp::DestroyImg()
{
	imNewNormal.Destroy();
	imNewHover.Destroy();
	imNewDown.Destroy();
	imNewDisable.Destroy();
	imOpenNormal.Destroy();
	imOpenHover.Destroy();
	imOpenDown.Destroy();
	imOpenDisable.Destroy();
	imSaveNormal.Destroy();
	imSaveHover.Destroy();
	imSaveDown.Destroy();
	imSaveDisable.Destroy();
	imReopenNormal.Destroy();
	imReopenHover.Destroy();
	imReopenDown.Destroy();
	imReopenDisable.Destroy();
	imAreaNormal.Destroy();
	imAreaHover.Destroy();
	imAreaDown.Destroy();
	imAreaDisable.Destroy();
	imAreaNormal0.Destroy();
	imAreaHover0.Destroy();
	imAreaDown0.Destroy();
	imAreaDisable0.Destroy();
	imResignNormal.Destroy();
	imResignHover.Destroy();
	imResignDown.Destroy();
	imResignDisable.Destroy();
	imExitNormal.Destroy();
	imExitHover.Destroy();
	imExitDown.Destroy();
	imExitDisable.Destroy();
	imChangeStoneNormal.Destroy();
	imChangeStoneHover.Destroy();
	imChangeStoneDown.Destroy();
	imChangeStoneDisable.Destroy();
	imPassNormal.Destroy();
	imPassHover.Destroy();
	imPassDown.Destroy();
	imPassDisable.Destroy();
	imPauseNormal.Destroy();
	imPauseHover.Destroy();
	imPauseDown.Destroy();
	imPauseDisable.Destroy();
	imRetractNormal.Destroy();
	imRetractHover.Destroy();
	imRetractDown.Destroy();
	imRetractDisable.Destroy();
	imHintNormal.Destroy();
	imHintHover.Destroy();
	imHintDown.Destroy();
	imHintDisable.Destroy();
	imPutStoneNormal.Destroy();
	imPutStoneHover.Destroy();
	imPutStoneDown.Destroy();
	imPutStoneDisable.Destroy();
	imContinueNormal.Destroy();
	imContinueHover.Destroy();
	imContinueDown.Destroy();
	imContinueDisabel.Destroy();
	imDifficultyNormal.Destroy();
	imDifficultyHover.Destroy();
	imDifficultyDown.Destroy();
	imDifficultyDisable.Destroy();
	imTesujiNormal.Destroy();
	imTesujiHover.Destroy();
	imElementaryNormal.Destroy();
	imElementaryHover.Destroy();
	imMiddleNormal.Destroy();
	imMiddleHover.Destroy();
	imAdvancedNormal.Destroy();
	imAdvanceeHover.Destroy();
	imPutBlackNormal.Destroy();
	imPutBlackHover.Destroy();
	imPutBlackDown.Destroy();
	imPutBlackDisable.Destroy();
	imPutWhiteNormal.Destroy();
	imPutWhiteHover.Destroy();
	imPutWhiteDown.Destroy();
	imPutWhiteDisable.Destroy();
	imBlackFirstNormal.Destroy();
	imBlackFirstHover.Destroy();
	imBlackFirstDown.Destroy();
	imBlackFirstDisable.Destroy();
	imWhiteFirstNormal.Destroy();
	imWhiteFirstHover.Destroy();
	imWhiteFirstDown.Destroy();
	imWhiteFirstDisable.Destroy();
	imStudyNormal.Destroy();
	imStudyHover.Destroy();
	imStudyDown.Destroy();
	imStudyDisable.Destroy();
	imSolveNormal.Destroy();
	imSolveHover.Destroy();
	imSolveDown.Destroy();
	imSolveDisable.Destroy();
	imAIanaNormal.Destroy();
	imAIanaHover.Destroy();
	imAIanaDown.Destroy();
	imAIanaDisable.Destroy();
	imPutStoneStudyNormal.Destroy();
	imPutStoneStudyHover.Destroy();
	imPutStoneStudyDown.Destroy();
	imPutStoneStudyDisable.Destroy();
	imPassMoveNormal.Destroy();
	imPassMoveHover.Destroy();
	imPassMoveDown.Destroy();
	imPassMoveDisable.Destroy();
	imSolutionNormal.Destroy();
	imSolutionHover.Destroy();
	imSolutionDown.Destroy();
	imSolutionDisable.Destroy();
	imRedoNormal.Destroy();
	imRedoHover.Destroy();
	imRedoDown.Destroy();
	imRedoDisable.Destroy();
	imSolveNormal2.Destroy();
	imSolveHover2.Destroy();
	imSolveDown2.Destroy();
	imSolveDisable2.Destroy();
	imStudyNormal2.Destroy();
	imStudyHover2.Destroy();
	imStudyDown2.Destroy();
	imStudyDisable2.Destroy();
	imAnaAllNormal.Destroy();
	imAnaAllHover.Destroy();
	imAnaAllDown.Destroy();
	imAnaAllDisable.Destroy();
	imReturnNormal.Destroy();
	imReturnHover.Destroy();
	imReturnDown.Destroy();
	imReturnDisabel.Destroy();
	imOpenNormal0.Destroy();
	imOpenHover0.Destroy();
	imOpenDown0.Destroy();
	imOpenDisable0.Destroy();
}
