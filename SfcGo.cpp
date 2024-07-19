
// SfcGo.cpp : 定义应用程序的类行为。
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

/*/gnugo引擎
extern "C"
{
	#include "gnugo.h"
	#include "liberty.h"
};*/

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int iScwd,iScht;//屏幕分辨率
CString strSysDirectry;//系统目录
CString strDirectry;//数据目录
CString strImgDirectry;//图像文件目录
CString strOutputDirectry;//输出目录
CString Version;//版本号
CString Edition;//版本
int iLanguage = 1;//语言
int iCpuNum;//cpu（核）数
CString sPlayerName;//玩家名
int iPlayerLevel;//玩家等级
int iEngineNum = 1;//引擎数
int iEngineTypes[10];//引擎ID
CString sEngineNames[10];//引擎名称
CString sEngineAppNames[10];//引擎执行文件名
CString sEngineAppDirs[10];//引擎目录
CString sEngineCmdLines[10];//引擎命令行
CString sEngineCmdLines1[10];//引擎命令行1，供死活分析或较强棋力
int iPlayer1 = 0;//黑棋弈者，0-玩家，1-电脑
int iLevel1 = 0;//电脑执黑时的等级，1-初段，10-棋圣
int iTime1 = 0;//电脑执黑时的思考时长，0-15秒，1-30秒，2-60秒，3-120秒
int iEngine1 = 1;//黑棋引擎选择
int iPlayer2 = 1;//白棋奕者，，0-玩家，1-电脑
int iLevel2 = 0;//电脑执白时的等级，1-初段，10-棋圣
int iTime2 = 0;//电脑执白时的思考时长，0-15秒，1-30秒，2-60秒，3-120秒
int iEngine2 = 1;//白棋引擎选择
int iRule = 0;//对弈规则，0-中国，1-日本，2-韩国
int iBoard = 0;//棋盘规格，0-19路，1-13路，2-9路
int iKomi = 35;//贴目，0-倒贴10目，40-贴10目
int iHandi = 0;//让子数，0-分先，1-定先，2以上-让子数
bool bCoord = true;//是否画棋盘坐标
bool bAnimate = true;//是否有落子动画
bool bThinkProgress = true;//是否显示电脑思考进度
bool bShowInfo = true;//是否显示信息和工具栏
bool bShowWinRate = true;//是否显示胜率图
bool bShowAna = true;//是否显示分析着手
bool bShowMoveRec = true;//是否显示着手记录
bool bPutStoneSound = true;//是否播放落子声音
bool bCaptureSound = true;//是否播放提子声音
bool bPickStoneSound = true;//是否播放从棋盒中拾子的声音
bool bPushClockSound = true;//是否播放按计时钟的声音
bool bByoSound = true;//是否播放读秒声
int iLDlevel=0;//死活题等级，0-手筋，1-初级，2-中级，3-高级
int iQuest0=1;//手筋练习当前题号
int iQuest1=1;//初级死活当前题号
int iQuest2=1;//中级死活当前题号
int iQuest3=1;//高级死活当前题号
int iQuestMax0=366;//手筋练习最大题号
int iQuestMax1=441;//初级死活最大题号
int iQuestMax2=450;//中级死活最大题号
int iQuestMax3=433;//高级死活最大题号
bool bLog = false;;//是否记录日志
bool volatile bAnalysing=false;//正在分析中
CImage imBackImg;//背景图片
CImage imBoardImg;//棋盘背景图片
CImage imBlackStone;//黑棋子图片
CImage imWhiteStone;//白棋子图片
CImage imBlackInfo;//黑棋方信息图片
CImage imWhiteInfo;//白棋方信息图片
CImage imProgressBar;//用时/思考进度图片
CImage imPlayInfo;//对局信息图片
CImage imToolBox;//工具箱图片
CImage imBackGound;//对局地面背景图片
CImage imNewNormal;//新对局按钮图片
CImage imNewHover;//新对局鼠标悬停图片
CImage imNewDown;//新对局鼠标按下图片
CImage imNewDisable;//新对局按钮禁用图片
CImage imOpenNormal;//打开棋谱按钮图片
CImage imOpenHover;
CImage imOpenDown;
CImage imOpenDisable;
CImage imOpenNormal0;//打开棋谱按钮图片
CImage imOpenHover0;
CImage imOpenDown0;
CImage imOpenDisable0;
CImage imSaveNormal;//保存按钮图片
CImage imSaveHover;
CImage imSaveDown;
CImage imSaveDisable;
CImage imReopenNormal;//继续对局按钮图片
CImage imReopenHover;
CImage imReopenDown;
CImage imReopenDisable;
CImage imAreaNormal;//形势判断按钮图片
CImage imAreaHover;
CImage imAreaDown;
CImage imAreaDisable;
CImage imAreaNormal0;//形势判断按钮图片
CImage imAreaHover0;
CImage imAreaDown0;
CImage imAreaDisable0;
CImage imResignNormal;//认输按钮图片
CImage imResignHover;
CImage imResignDown;
CImage imResignDisable;
CImage imGoFirstNormal;//回到最初按钮图片
CImage imGoFirstHover;
CImage imGoFirstDown;
CImage imGoFirstDisable;
CImage imGoFiveBackNormal;//后退五步按钮图片
CImage imGoFiveBackHover;
CImage imGoFiveBackDown;
CImage imGoFiveBackDisable;
CImage imGoBackNormal;//后退按钮图片
CImage imGoBackHover;
CImage imGoBackDown;
CImage imGoBackDisable;
CImage imGoForwardNormal;//前进按钮图片
CImage imGoForwardHover;
CImage imGoForwardDown;
CImage imGoForwardDisable;
CImage imGoFiveForwardNormal;//前进五步按钮图片
CImage imGoFiveForwardHover;
CImage imGoFiveForwardDown;
CImage imGoFiveForwardDisable;
CImage imGoLastNormal;//前进到底按钮图片
CImage imGoLastHover;
CImage imGoLastDown;
CImage imGoLastDisable;
CImage imExitNormal;//退出按钮图片
CImage imExitHover;
CImage imExitDown;
CImage imExitDisable;
CImage imPassNormal;//PASS按钮图片
CImage imPassHover;
CImage imPassDown;
CImage imPassDisable;
CImage imRetractNormal;//悔棋按钮图片
CImage imRetractHover;
CImage imRetractDown;
CImage imRetractDisable;
CImage imHintNormal;//支招按钮图片
CImage imHintHover;
CImage imHintDown;
CImage imHintDisable;
CImage imPauseNormal;//暂停按钮图片
CImage imPauseHover;
CImage imPauseDown;
CImage imPauseDisable;
CImage imChangeStoneNormal;//交换对局
CImage imChangeStoneHover;
CImage imChangeStoneDown;
CImage imChangeStoneDisable;
CImage imRecDesk;//着手记录桌图片
CImage imRec;//着手记录图片
CImage imRecSelected;//选中着手记录图片
CImage imChart;//胜率图表图片
CImage imRecTitle;//记录标题图片
//CImage imEmptyNormal;//空按钮图片
//CImage imEmptyHover;
//CImage imEmptyDown;
//CImage imEmptyDisable;
CImage imPutStoneNormal;//摆子出题按钮图片
CImage imPutStoneHover;
CImage imPutStoneDown;
CImage imPutStoneDisable;
CImage imContinueNormal;//继续做题按钮图片
CImage imContinueHover;
CImage imContinueDown;
CImage imContinueDisabel;
CImage imDifficultyNormal;//难度选择按钮图片
CImage imDifficultyHover;
CImage imDifficultyDown;
CImage imDifficultyDisable;
CImage imTesujiNormal;//手筋练习按钮图片
CImage imTesujiHover;
CImage imElementaryNormal;//初级死活按钮图片
CImage imElementaryHover;
CImage imMiddleNormal;//中级死活按钮图片
CImage imMiddleHover;
CImage imAdvancedNormal;//高级死活按钮图片
CImage imAdvanceeHover;
CImage imPutBlackNormal;//摆放黑子按钮图片
CImage imPutBlackHover;
CImage imPutBlackDown;
CImage imPutBlackDisable;
CImage imPutWhiteNormal;//摆放白子按钮图片
CImage imPutWhiteHover;
CImage imPutWhiteDown;
CImage imPutWhiteDisable;
CImage imBlackFirstNormal;//黑先按钮图片
CImage imBlackFirstHover;
CImage imBlackFirstDown;
CImage imBlackFirstDisable;
CImage imWhiteFirstNormal;//白先按钮图片
CImage imWhiteFirstHover;
CImage imWhiteFirstDown;
CImage imWhiteFirstDisable;
CImage imStudyNormal;//研究按钮图片
CImage imStudyHover;
CImage imStudyDown;
CImage imStudyDisable;
CImage imSolveNormal;//死活分析开始做题按钮图片
CImage imSolveHover;
CImage imSolveDown;
CImage imSolveDisable;
CImage imAIanaNormal;//AI分析按钮图片
CImage imAIanaHover;
CImage imAIanaDown;
CImage imAIanaDisable;
CImage imPutStoneStudyNormal;//摆子研究按钮图片
CImage imPutStoneStudyHover;
CImage imPutStoneStudyDown;
CImage imPutStoneStudyDisable;
CImage imPassMoveNormal;//PASS一手按钮图片
CImage imPassMoveHover;
CImage imPassMoveDown;
CImage imPassMoveDisable;
CImage imSolutionNormal;//查看死活题解答按钮图片
CImage imSolutionHover;
CImage imSolutionDown;
CImage imSolutionDisable;
CImage imRedoNormal;//重做按钮图片
CImage imRedoHover;
CImage imRedoDown;
CImage imRedoDisable;
CImage imSolveNormal2;//死活分析解题小按钮
CImage imSolveHover2;
CImage imSolveDown2;
CImage imSolveDisable2;
CImage imStudyNormal2;//死活题研究小按钮
CImage imStudyHover2;
CImage imStudyDown2;
CImage imStudyDisable2;
CImage imAnaAllNormal;//全盘分析按钮图片
CImage imAnaAllHover;
CImage imAnaAllDown;
CImage imAnaAllDisable;
CImage imReturnNormal;//返回按钮图片
CImage imReturnHover;
CImage imReturnDown;
CImage imReturnDisabel;
//CImage imStoneEffect;
int iState=0;//功能状态，0-空闲，1-死活题
int iBoardSizeState=2;//棋盘大小，0-9X9，1-13X13，2-19X19
int iBoardSize=19;//棋盘大小
CRect ctRect;//客户区大小

// CSfcGoApp

BEGIN_MESSAGE_MAP(CSfcGoApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CSfcGoApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CSfcGoApp 构造

CSfcGoApp::CSfcGoApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("SfcGo.AppID.Version2.0"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CSfcGoApp 对象

CSfcGoApp theApp;


// CSfcGoApp 初始化

BOOL CSfcGoApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();
	iScwd=GetSystemMetrics(SM_CXSCREEN);
	iScht=GetSystemMetrics(SM_CYSCREEN);
	if(iScwd<800||iScht<600){
		AfxMessageBox(_T("此程序对显示器分辨率有要求,\n请将分辨率调至800x600以上!"),NULL,MB_OK);
		exit(0);
	}
	//确定工作目录
	char str[_MAX_PATH];
	_getcwd(str,_MAX_PATH);
	strSysDirectry=str;
	strDirectry=str;
	strOutputDirectry=str;
	strSysDirectry+="\\Sys";
	strDirectry+="\\Data";
	strOutputDirectry+="\\Output";
	//读取系统配置文件
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
	//读取图片
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
	//初始化随机数
	srand(unsigned int(time(NULL)));
	/*/初始化gnugo引擎
	time_t t=time(NULL);
	init_gnugo(128,time_t(NULL));*/

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名

	if (iLanguage == 0)
	{
		SetThreadUILanguage(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
	}
	else
	{
		SetThreadUILanguage(MAKELANGID(LANG_CHINESE_SIMPLIFIED, SUBLANG_CHINESE_SIMPLIFIED));
	}
	SetRegistryKey(_T("SfcGo"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_SfcGoTYPE,
		RUNTIME_CLASS(CSfcGoDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CSfcGoView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// 创建主 MDI 框架窗口
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand=CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 主窗口已初始化，因此显示它并对其进行更新
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	AfxGetMainWnd()->PostMessageA(WM_PAINT);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CSfcGoApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CSfcGoApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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

// 用于运行对话框的应用程序命令
void CSfcGoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CSfcGoApp 消息处理程序


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
