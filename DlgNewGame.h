#pragma once


// DlgNewGame 对话框

class DlgNewGame : public CDialogEx
{
	DECLARE_DYNAMIC(DlgNewGame)

public:
	DlgNewGame(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgNewGame();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWGAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 执黑棋弈者
	int m_iHuman1;
	// 执白棋弈者，TRUE则为人，FALSE则为电脑
	int m_iHuman2;
	// 执黑方电脑水平控件
	CComboBox m_cmbLevel1;
	// 执黑棋电脑水平
	int m_iLevel1;
	// 执黑棋电脑思考时长控件
	CComboBox m_cmbTime1;
	// 执黑棋电脑思考时长
	int m_iTime1;
	// 执白棋电脑水平控件
	CComboBox m_cmbLevel2;
	// 执白棋电脑水平
	int m_iLevel2;
	// 执白棋思考时长控件
	CComboBox m_cmbTime2;
	// 执白棋电脑思考时长
	int m_iTime2;
	// //棋盘大小
	int m_iBoardSize;
	// 贴目设置控件
	CComboBox m_cmbKomi;
	// 贴目设置
	int m_iKomi;
	// 让子设置控件
	CComboBox m_cmbHandicap;
	// 让子设置
	int m_iHandicap;
	// 围棋规则，0-中国，1-日本，2-韩国
	int m_iRule;
	// 显示棋盘坐标
	BOOL m_bCoord;
	// 显示落子动画
	BOOL m_bAnimate;
	// 显示电脑思考进度条
	BOOL m_bThinkProgram;
	// 播放落子声
	BOOL m_bPutStone;
	// 播放提子声
	BOOL m_bCapture;
	// 播放从棋盒里拾取棋子的声音
	BOOL m_bPickStone;
	// 播放按计时钟的声音
	BOOL m_bPushClock;
	// 播放读秒声
	BOOL m_bByo;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadhuman1();
	afx_msg void OnBnClickedRadhuman2();
	afx_msg void OnCbnSelchangeCmbhandicap();
	// 黑棋引擎选择控件
	CComboBox m_cmbEngine1;
	// 黑棋引擎选择
	int m_iEngine1;
	// 白棋引擎选择控件
	CComboBox m_cmbEngine2;
	// 白棋引擎选择
	int m_iEngine2;
	afx_msg void OnCbnSelchangeCmbengine1();
	afx_msg void OnCbnSelchangeCmbengine2();
	afx_msg void OnCbnSelchangeCmblevel1();
	afx_msg void OnCbnSelchangeCmblevel2();
	// 规则设定控件
	CComboBox m_cmbRule;
	afx_msg void OnCbnSelchangeCmbrule();
	// 对局类型
	int m_iCombat;
	afx_msg void OnCbnSelchangeCmbcombat();
	// 对局类型控件
	CComboBox m_cmbCombat;
	// 对局类型提示信息
	CStatic m_sTs;
	// 对局类型提示
	CString m_sCombatTs;
	//是否加载了棋谱
	bool m_bSgfLoaded=false;
};
