// DlgNewGame.cpp: 实现文件
//

//#include "pch.h"
#include "stdafx.h"
#include "SfcGo.h"
#include "DlgNewGame.h"
#include "afxdialogex.h"


extern int iEngineNum;//引擎数
extern CString sEngineNames[10];//引擎名称
extern int iLanguage;//语言
extern CString sMsg, sThinkMsg;
// DlgNewGame 对话框

IMPLEMENT_DYNAMIC(DlgNewGame, CDialogEx)

DlgNewGame::DlgNewGame(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEWGAME, pParent)
	, m_iHuman1(0)
	, m_iHuman2(0)
	, m_iLevel1(0)
	, m_iTime1(0)
	, m_iLevel2(0)
	, m_iTime2(0)
	, m_iBoardSize(0)
	, m_iKomi(0)
	, m_iHandicap(0)
	, m_iRule(0)
	, m_bCoord(FALSE)
	, m_bAnimate(FALSE)
	, m_bThinkProgram(FALSE)
	, m_bPutStone(FALSE)
	, m_bCapture(FALSE)
	, m_bPickStone(FALSE)
	, m_bPushClock(FALSE)
	, m_bByo(FALSE)
	, m_iEngine1(0)
	, m_iEngine2(0)
	, m_iCombat(0)
	, m_sCombatTs(_T("\n    自由对局的胜负不影响你的等级，请放松练习。"))
{

}

DlgNewGame::~DlgNewGame()
{
}

void DlgNewGame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADHUMAN1, m_iHuman1);
	DDX_Radio(pDX, IDC_RADHUMAN2, m_iHuman2);
	DDX_Control(pDX, IDC_CMBLEVEL1, m_cmbLevel1);
	DDX_CBIndex(pDX, IDC_CMBLEVEL1, m_iLevel1);
	DDX_Control(pDX, IDC_CMBTIME1, m_cmbTime1);
	DDX_CBIndex(pDX, IDC_CMBTIME1, m_iTime1);
	DDX_Control(pDX, IDC_CMBLEVEL2, m_cmbLevel2);
	DDX_CBIndex(pDX, IDC_CMBLEVEL2, m_iLevel2);
	DDX_Control(pDX, IDC_CMBTIME2, m_cmbTime2);
	DDX_CBIndex(pDX, IDC_CMBTIME2, m_iTime2);
	DDX_CBIndex(pDX, IDC_CMBBOARDSIZE, m_iBoardSize);
	DDX_Control(pDX, IDC_CMBKOMI, m_cmbKomi);
	DDX_CBIndex(pDX, IDC_CMBKOMI, m_iKomi);
	DDX_Control(pDX, IDC_CMBHANDICAP, m_cmbHandicap);
	DDX_CBIndex(pDX, IDC_CMBHANDICAP, m_iHandicap);
	DDX_CBIndex(pDX, IDC_CMBRULE, m_iRule);
	DDX_Check(pDX, IDC_CHKCOORD, m_bCoord);
	DDX_Check(pDX, IDC_CHKANIMAT, m_bAnimate);
	DDX_Check(pDX, IDC_CHKTHINKPROGRAM, m_bThinkProgram);
	DDX_Check(pDX, IDC_CHKPUTSTONG, m_bPutStone);
	DDX_Check(pDX, IDC_CHKCAPTURE, m_bCapture);
	DDX_Check(pDX, IDC_CHKPICKSTONE, m_bPickStone);
	DDX_Check(pDX, IDC_CHKPUSHCLOCK, m_bPushClock);
	DDX_Check(pDX, IDC_CHKBYO, m_bByo);
	DDX_Control(pDX, IDC_CMBENGINE1, m_cmbEngine1);
	DDX_CBIndex(pDX, IDC_CMBENGINE1, m_iEngine1);
	DDX_Control(pDX, IDC_CMBENGINE2, m_cmbEngine2);
	DDX_CBIndex(pDX, IDC_CMBENGINE2, m_iEngine2);
	DDX_Control(pDX, IDC_CMBRULE, m_cmbRule);
	DDX_CBIndex(pDX, IDC_CMBCOMBAT, m_iCombat);
	DDX_Control(pDX, IDC_CMBCOMBAT, m_cmbCombat);
	DDX_Control(pDX, IDC_STATTS, m_sTs);
	DDX_Text(pDX, IDC_STATTS, m_sCombatTs);
}


BEGIN_MESSAGE_MAP(DlgNewGame, CDialogEx)
	ON_BN_CLICKED(IDC_RADHUMAN1, &DlgNewGame::OnBnClickedRadhuman1)
	ON_BN_CLICKED(IDC_RADCOMPUTER1, &DlgNewGame::OnBnClickedRadhuman1)
	ON_BN_CLICKED(IDC_RADHUMAN2, &DlgNewGame::OnBnClickedRadhuman2)
	ON_BN_CLICKED(IDC_RADCOMPUTER2, &DlgNewGame::OnBnClickedRadhuman2)
	ON_CBN_SELCHANGE(IDC_CMBHANDICAP, &DlgNewGame::OnCbnSelchangeCmbhandicap)
	ON_CBN_SELCHANGE(IDC_CMBENGINE1, &DlgNewGame::OnCbnSelchangeCmbengine1)
	ON_CBN_SELCHANGE(IDC_CMBENGINE2, &DlgNewGame::OnCbnSelchangeCmbengine2)
	ON_CBN_SELCHANGE(IDC_CMBLEVEL1, &DlgNewGame::OnCbnSelchangeCmblevel1)
	ON_CBN_SELCHANGE(IDC_CMBLEVEL2, &DlgNewGame::OnCbnSelchangeCmblevel2)
	ON_CBN_SELCHANGE(IDC_CMBRULE, &DlgNewGame::OnCbnSelchangeCmbrule)
	ON_CBN_SELCHANGE(IDC_CMBCOMBAT, &DlgNewGame::OnCbnSelchangeCmbcombat)
END_MESSAGE_MAP()


// DlgNewGame 消息处理程序


BOOL DlgNewGame::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	for (int i = 0; i < iEngineNum; i++)
	{
		m_cmbEngine1.AddString(sEngineNames[i]);
		m_cmbEngine2.AddString(sEngineNames[i]);
	}
	m_cmbEngine1.SetCurSel(m_iEngine1);
	m_cmbEngine2.SetCurSel(m_iEngine2);
	if (m_iHuman1==0)
	{
		m_cmbLevel1.EnableWindow(FALSE);
		m_cmbTime1.EnableWindow(FALSE);
		m_cmbEngine1.EnableWindow(FALSE);
	}
	if (m_iHuman2==0)
	{
		m_cmbLevel2.EnableWindow(FALSE);
		m_cmbTime2.EnableWindow(FALSE);
		m_cmbEngine2.EnableWindow(FALSE);
	}
	if (m_bSgfLoaded)
		m_cmbCombat.EnableWindow(FALSE);
	if (iLanguage == 0)
	{
		m_sCombatTs = "Free match does not affect your rank, relax and injoy it!";
		UpdateData(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void DlgNewGame::OnBnClickedRadhuman1()
{
	UpdateData(TRUE);
	if (m_iHuman1 == 0)
	{
		m_cmbLevel1.EnableWindow(FALSE);
		m_cmbTime1.EnableWindow(FALSE);
		m_cmbEngine1.EnableWindow(FALSE);
	}
	else
	{
		m_cmbLevel1.EnableWindow(TRUE);
		m_cmbTime1.EnableWindow(TRUE);
		m_cmbEngine1.EnableWindow(TRUE);
		if (m_iEngine1 == 0 && m_iLevel1 < 13)
		{
			m_iEngine1 = 1;
			m_iRule = 0;
		}
		else if (m_iEngine1 == 1 && m_iLevel1 > 21)
		{
			m_iEngine1 = 0;
		}
		UpdateData(FALSE);
	}
}


void DlgNewGame::OnBnClickedRadhuman2()
{
	UpdateData(TRUE);
	if (m_iHuman2 == 0)
	{
		m_cmbLevel2.EnableWindow(FALSE);
		m_cmbTime2.EnableWindow(FALSE);
		m_cmbEngine2.EnableWindow(FALSE);
	}
	else
	{
		m_cmbLevel2.EnableWindow(TRUE);
		m_cmbTime2.EnableWindow(TRUE);
		m_cmbEngine2.EnableWindow(TRUE);
		if (m_iEngine2 == 0 && m_iLevel2 < 13)
		{
			m_iEngine2 = 1;
			m_iRule = 0;
		}
		else if (m_iEngine2 == 1 && m_iLevel2 > 21)
		{
			m_iEngine2 = 0;
		}
		UpdateData(FALSE);
	}
}


void DlgNewGame::OnCbnSelchangeCmbhandicap()
{
	UpdateData(TRUE);
	if (m_iHandicap == 0)
	{
		if (m_iRule == 0)
			m_iKomi = 35;
		else
			m_iKomi = 33;
	}
	else
		m_iKomi = 20;
	UpdateData(FALSE);
}


void DlgNewGame::OnCbnSelchangeCmbengine1()
{
	int id = m_cmbEngine1.GetCurSel();
	int lvl = m_cmbLevel1.GetCurSel();
	if (id == 0)
	{
		if (lvl < 13 && m_iEngine1 == 1)
		{
			CString msg = "该引擎最低棋力为职业二段，您要将电脑棋力调整至该等级吗？";
			if (iLanguage == 0)
				msg = "The lowerest level of this engine is profession 2 dan, will you change computer to this level?";
			if (MessageBox(msg, sMsg, MB_YESNO) != IDYES)
			{
				m_cmbEngine1.SetCurSel(m_iEngine1);
				return;
			}
			m_iLevel1 = 13;
			m_cmbLevel1.SetCurSel(m_iLevel1);
		}
		/*m_cmbLevel1.ResetContent();
		m_cmbLevel1.AddString("职业三段");
		m_cmbLevel1.AddString("职业四段");
		m_cmbLevel1.AddString("职业五段");
		m_cmbLevel1.AddString("职业六段");
		m_cmbLevel1.AddString("职业七段");
		m_cmbLevel1.AddString("职业八段");
		m_cmbLevel1.AddString("职业九段");
		m_cmbLevel1.AddString("棋圣");*/
	}
	else if (id == 1)
	{
		if (lvl > 21 && m_iEngine1 == 0)
		{
			CString msg = "该引擎最高棋力为名人，您要将电脑棋力调整至该等级吗？";
			if (iLanguage == 0)
				msg = "The highest level of this engine is Meijin, will you change computer to this level?";
			if (MessageBox(msg, sMsg, MB_YESNO) != IDYES)
			{
				m_cmbEngine1.SetCurSel(m_iEngine1);
				return;
			}
			m_iLevel1 = 21;
			m_cmbLevel1.SetCurSel(m_iLevel1);
		}
		//Leelaz时只能为中国规则
		m_cmbRule.SetCurSel(0);
		m_iRule = 0;
	}
	m_iEngine1 = id;
	/*else if (iEngineTypes[id] == 1)
	{
		if (iEngineTypes[m_iEngine1] == 0)
		{
			m_cmbLevel1.ResetContent();
			m_cmbLevel1.AddString("五级");
			m_cmbLevel1.AddString("四级");
			m_cmbLevel1.AddString("三级");
			m_cmbLevel1.AddString("二级");
			m_cmbLevel1.AddString("一级");
			m_cmbLevel1.AddString("业余一段");
			m_cmbLevel1.AddString("业余二段");
			m_cmbLevel1.AddString("业余三段");
			m_cmbLevel1.AddString("业余四段");
			m_cmbLevel1.AddString("业余五段");
			m_cmbLevel1.AddString("业余六段");
			m_cmbLevel1.AddString("业余七段");
			m_cmbLevel1.AddString("职业初段");
			m_cmbLevel1.AddString("职业二段");
			m_cmbLevel1.AddString("职业三段");
			m_cmbLevel1.AddString("职业四段");
			m_cmbLevel1.AddString("职业五段");
			m_cmbLevel1.AddString("职业六段");
			m_cmbLevel1.AddString("职业七段");
			m_cmbLevel1.AddString("职业八段");
			m_cmbLevel1.AddString("职业九段");
			m_cmbLevel1.AddString("棋圣");
			m_iLevel1 += 13;
		}
	}*/
}


void DlgNewGame::OnCbnSelchangeCmbengine2()
{
	int id = m_cmbEngine2.GetCurSel();
	int lvl = m_cmbLevel2.GetCurSel();
	if (id == 0)
	{
		if (lvl < 13 && m_iEngine2 == 1)
		{
			CString msg = "该引擎最低棋力为职业二段，您要将电脑棋力调整至该等级吗？";
			if (iLanguage == 0)
				msg = "The lowerest level of this engine is profession 2 dan, will you change computer to this level?";
			if (MessageBox(msg, sMsg, MB_YESNO) != IDYES)
			{
				m_cmbEngine2.SetCurSel(m_iEngine2);
				return;
			}
			m_iLevel2 = 13;
			m_cmbLevel2.SetCurSel(m_iLevel2);
		}
	}
	else if (id == 1)
	{
		if (lvl > 21 && m_iEngine2 == 0)
		{
			CString msg = "该引擎最高棋力为名人，您要将电脑棋力调整至该等级吗？";
			if (iLanguage == 0)
				msg = "The highest level of this engine is Meijin, will you change computer to this level?";
			if (MessageBox(msg, sMsg, MB_YESNO) != IDYES)
			{
				m_cmbEngine2.SetCurSel(m_iEngine2);
				return;
			}
			m_iLevel2 = 21;
			m_cmbLevel2.SetCurSel(m_iLevel2);
		}
		//Leelaz时只能为中国规则
		m_cmbRule.SetCurSel(0);
		m_iRule = 0;
	}
	m_iEngine2 = id;
}


void DlgNewGame::OnCbnSelchangeCmblevel1()
{
	int id = m_cmbEngine1.GetCurSel();
	int lvl = m_cmbLevel1.GetCurSel();
	if (id == 0 && lvl < 13)
	{
		m_iEngine1 = 1;
		m_cmbEngine1.SetCurSel(m_iEngine1);
		m_iRule = 0;
		m_cmbRule.SetCurSel(m_iRule);
	}
	else if (id == 1 && lvl > 21)
	{
		m_iEngine1 = 0;
		m_cmbEngine1.SetCurSel(m_iEngine1);
	}
}


void DlgNewGame::OnCbnSelchangeCmblevel2()
{
	int id = m_cmbEngine2.GetCurSel();
	int lvl = m_cmbLevel2.GetCurSel();
	if (id == 0 && lvl < 13)
	{
		m_iEngine2 = 1;
		m_cmbEngine2.SetCurSel(m_iEngine2);
		m_iRule = 0;
		m_cmbRule.SetCurSel(m_iRule);
	}
	else if (id == 1 && lvl > 21)
	{
		m_iEngine2 = 0;
		m_cmbEngine2.SetCurSel(m_iEngine2);
	}
}


void DlgNewGame::OnCbnSelchangeCmbrule()
{
	int rule = m_cmbRule.GetCurSel();
	if (rule != 0)
	{
		int id1 = m_cmbEngine1.GetCurSel();
		int id2 = m_cmbEngine2.GetCurSel();
		if (id1 == 1 && m_cmbEngine1.IsWindowEnabled() || id2 == 1 && m_cmbEngine2.IsWindowEnabled())
		{
			CString msg = "Leelaz引擎只能使用中国规则！";
			if (iLanguage == 0)
				msg = "Engine Leelaz uses Chinese rule only!";
			MessageBox(msg, sMsg);
			m_cmbRule.SetCurSel(0);
			m_iRule = 0;
			return;
		}
	}
	UpdateData(TRUE);
	if (m_iHandicap == 0)
	{
		if (m_iRule == 0)
			m_iKomi = 35;
		else
			m_iKomi = 33;
	}
	else
		m_iKomi = 20;
	UpdateData(FALSE);
}


void DlgNewGame::OnCbnSelchangeCmbcombat()
{
	UpdateData(TRUE);
	//int id = m_cmbCombat.GetCurSel();
	if (iLanguage == 0)
	{
		if (m_iCombat == 0)
			m_sCombatTs = "Free match does not affect your rank, relax and injoy it!";
		else
			m_sCombatTs = "Winning the challenge will allow you to level up.";
	}
	else
	{
		if (m_iCombat == 0)
			m_sCombatTs = "\n    自由对局的胜负不影响你的等级，请放松练习。";
		else
			m_sCombatTs = "    挑战赛胜利可以让你提升等级。加油，祝你早日成为棋圣！";
	}
	//m_iCombat = id;
	UpdateData(FALSE);
}
