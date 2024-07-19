
// SfcGoView.h : CSfcGoView 类的接口
//

#pragma once

#include "resource.h"
#include "afxwin.h"
//#include "sgftree.h"
#include "SfcGtp.h"
#include "SgfTree.h"
//extern "C"
//{
//#include "sgftree.h"
//}

//#define STDPOS(i) m_iBoardSize-i-1
#define STDPOS(i,j) j,i//m_iBoardSize-j-1,m_iBoardSize-i-1

typedef struct {
	CString game_name = "";
	CString game_comment = "";
	int handicap;
	int to_move;		/* whose move it currently is */
	SGFTree game_record;	/* Game record in sgf format. */
	int computer_player;	/* BLACK, WHITE, or EMPTY (used as BOTH) */
} Gameinfo;

class CSfcGoView : public CFormView
{
protected: // 仅从序列化创建
	CSfcGoView();
	DECLARE_DYNCREATE(CSfcGoView)

public:
	enum{ IDD = IDD_SFCGO_FORM };

// 特性
public:
	CSfcGoDoc* GetDocument() const;

// 操作
public:
	bool AddStone(int x, int y, int color);//落子
	//玩家着手
	int PlayerMove(int x,int y,int color); 
	//电脑着手
	int ComputerMove();
	//将通用棋子坐标标识转换为SfcGo坐标
	void Trans(CString str, int& x, int& y);
	//设置棋力，0为最低
	bool SetLevel(int level) const;

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CSfcGoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

private:
	//绘棋盘
	void PaintBoard(); 
	//绘棋子
	void PaintQz(int x,int y,int color); 
	//绘最后一个棋子
	void PaintLastQz(int x,int y,int color); 
	//绘最后一个棋子
	void PaintLastQz(); 
	//绘最后一步棋
	void WriteLastGo(); 
	//绘制着子顺序，在复盘状态中使用
	void PaintIdx(int id); 
	//绘制棋子标志
	void PaintStoneSignal(int x, int y, int color, CString s);
	//输出信息
	void OutputInfo(); 
	//移除棋子
	bool RemoveStone(int x,int y);
	//电脑着手的后继处理
	int ComputerMove2();
	//设置引擎棋盘大小
	bool SetEngineBoardSize(int num);
	//清空引擎棋盘
	bool ClearEngineBoard();
	//设置对弈规则，0-中国规则，1-日本，2-韩国
	bool SetRule(int ruleid);
	//设置引擎时间，分别是规定时间、读秒时间、读秒时间内须走步数，时间均以秒计算
	bool SetTimes(int maintime, int byotime, int stones);
	//设置引擎固定让子
	bool SetEngineFixedHandicap(int handicap);
	//设置棋盘大小
	bool SetBoardSize(int num); 
	//设置让子数
	bool SetHandicap(int num); 
	//设置贴目
	bool SetKomi(float komi);
	//从引擎复制棋盘
	void CopyBoard(); 
	//复制本地棋盘
	void CopyLocalBoard();
	//PASS一手
	int DoPass(); 
	//清除棋盘
	void ClearBoard(); 
	//提子
	int DoCapture(int pos, int color, int captures[]);
	//死活攻击，maxsizepos-要攻击的棋块，scount-可下着手点数，smoves-可下着手点，maxmoves-分析出的最佳着手点，mcounts-本轮需分析的着手点数，将从可下着手点中随机抽取，
	//sdepth-分析深度，max_sdepth-最大分析深度，达到时递归函数将返回
	int LifeDeathAttack(int maxsizepos, int scount, int smoves[100], int color, int maxmoves[100], int mcounts[100], int sdepth, int max_sdepth);
	//死活攻击1，轮到防守方着手，但不同于死活防守函数，maxsizepos-要攻击的棋块，scount-可下着手点数，smoves-可下着手点，maxmoves-分析出的最佳着手点，
	//mcounts-本轮需分析的着手点数，将从可下着手点中随机抽取，sdepth-分析深度，max_sdepth-最大分析深度，达到时递归函数将返回
	int LifeDeathAttack1(int maxsizepos, int scount, int smoves[100], int color, int maxmoves[100], int mcounts[100], int sdepth, int max_sdepth);
	//死活防守，maxsizepos-要防守的棋块，scount-可下着手点数，smoves-可下着手点，maxmoves-分析出的最佳着手点，mcounts-本轮需分析的着手点数，将从可下着手点中随机抽取，
	//sdepth-分析深度，max_sdepth-最大分析深度，达到时递归函数将返回
	int LifeDeathDefend(int maxsizepos, int scount, int smoves[100], int color, int maxmoves[100], int mcounts[100], int sdepth, int max_sdepth);
	//死活防守1，轮到攻击方着手，但不同于死活攻击函数，maxsizepos-要攻击的棋块，scount-可下着手点数，smoves-可下着手点，maxmoves-分析出的最佳着手点，
	//mcounts-本轮需分析的着手点数，将从可下着手点中随机抽取，sdepth-分析深度，max_sdepth-最大分析深度，达到时递归函数将返回
	int LifeDeathDefend1(int maxsizepos, int scount, int smoves[100], int color, int maxmoves[100], int mcounts[100], int sdepth, int max_sdepth);
	//将棋盘记录入SGF树中
	void RecordBoard(SGFNode* node);
	//初始化SFG树
	void InitSgf(Gameinfo* ginfo);
	//进行结束游戏的操作
	int EndGame(Gameinfo* gameinfo, int reason);
	//清除游戏信息
	void GameinfoClear(Gameinfo* gameinfo);
	//将棋子坐标及颜色转换为通用标识
	CString TransXY(int x, int y, int color);
	//将棋子坐标转换为通用标识
	CString TransXY(int x, int y);
	//从引擎获取形势判断分数，为正则白优胜
	float GetScore();
	//从GoRecord转换为SGFTree
	int GoRecordToSgf(int gocount, Data_GoRecord gorecord[], int fixedstone, SGFTree* tree);
	//从SGFTree转换为GoRecord
	int SgfToGoRecord(SGFTree* tree, int& gocount, Data_GoRecord gorecord[], int& fixedstone);
	//从SGF数据获取着手
	void GetSgfMove(SGFProperty* prop, int& x, int& y, int& color);
	//放置让子
	void PlaceFixedHandicap(int handicap);
	//绘制信息栏及按钮
	void PaintInfo();
	//绘制输出信息，如轮谁着手等
	void PaintOutputInfo();
	//绘制按钮,buttonid=0-新棋局/PASS，1-打开棋谱/悔棋，2-保存棋谱/支招，3-暂停/继续，4-形势判断，5-退出/交换对局，6-认输
	//10-回到最初，11-快退5步，12-后退1步，13-前进一步，14-快进5步，15-进到最后
	void PaintButton(int buttonid);
	//绘制着手记录等
	void PaintMoveRec();
	//绘制支招棋子
	void PaintHintStone();
	//新对局/PASS
	void OnNew();
	//打开棋谱/悔棋
	void OnOpen();
	//保存棋谱/支招
	void OnSave();
	//暂停/继续棋局
	void OnReopen();
	//形势判断
	void OnArea();
	//退出/认输
	void OnExit();
	//回到最初
	void OnGoFirst();
	//后退五步
	void OnGoFiveBack();
	//后退
	void OnGoBack();
	//前进
	void OnGoForward();
	//前进五步
	void OnGoFiveForward();
	//前进到底
	void OnGoLast();
	//PASS
	void OnPass();
	//悔棋
	void OnRetract();
	//支招
	void OnHint();
	//暂停
	void OnPause();
	//交换对局
	void OnChangeStone();
	//认输
	void OnResign();
	//创建SGF树头
	void CreateSgfHead(SGFTree* tree, int boardsize, float komi, int handicap);
	//获取SGF对弈双方信息，如为SfcGo棋谱则返回true
	bool GetSgfPlayerInfo(SGFProperty* prop);
	//获取等级对应的头衔
	CString GetLevelTitle(int lvl);
	//获取等级对应的头衔
	CString GetLevelFullTitle(int lvl);
	//获取对局结果
	CString GetGameResult();
	//进行死活分析
	void OnLifeDeathAna();
	//计算死活题着手点范围
	CRect GetLifeDeathArea();
	//获取死活分析着手范围字符串
	CString GetLifeDeathAllowedMoveString(int targetdragonid);
	//判断棋子间的连接，x，y可以是空白点，x0,y0必须是棋子
	bool StoneLinkToStone(int x, int y, int color, int x0, int y0, int board[19][19]);
	//判断棋子或空白点和棋群之间的连接
	bool StoneLinkToDragon(int x, int y, int color, int dragonid);
	//获取棋群范围
	CRect GetDragonArea(int dragonid);
	//获取棋群周围和内部的空白点
	int GetDragonPoints(int dragonid, int xs[361], int ys[361]);
	//获取死活分析着手范围
	int GetLifeDeathAllowedMoves(int color, int xs[361], int ys[361]);
	//获取棋盘上所有棋子的坐标
	int GetStonesFromBoard(int xs[361], int ys[361]);
	//显示死活题功能面板
	void ShowLifeDeathPanel();
	//显示分析着手
	void ShowAnaMove();
	//保存胜率数据到文件
	void SaveWinRate(CString filename);
	//从文件读取胜率数据
	void ReadWinRate(CString filename);
	//执行序盘研究时AI分析按钮的操作
	void OnPersistenceAna();
	//执行返回按钮的操作
	void OnReturn();
	//更新前进/后退等按钮
	void UpdateBackForwardButton();
	//暂存着手用时和胜率
	void SaveMoveRecs();
	//恢复着手用时和胜率
	void RestroreMoveRecs();
	//计算对弈用时
	void CalGameTime();
	//根据前进/后退（movenum值为负）的步数来计算对弈用时
	void CalGameTime(int movenum);
	//死活练习难度选择
	void OnDifficulty();
	//继续上次的死活题
	bool OnContinueQuest();
	//处理摆黑子按钮
	void OnPutBlack();
	//处理摆白子按钮
	void OnPutWhite();
	//处理黑先按钮
	void OnBlackFirst();
	//处理白先按钮
	void OnWhiteFirst();
	//处理研究按钮
	void OnStudy();
	//获取SGFTree里当前节点所有变招
	int GetSgfVariation(SGFTree* tree, int movecounts[100], CString* movess[100], CString* commentss[100], float* winrates);
	//处理死活题查看答案按钮
	void OnSolution();
	//复制SGFTREE
	void CopySgfTree(SGFTree* pdesttree, SGFTree sourcetree);
	//根据当前的棋步在SGFTREE中查找下一步，成功返回true，失败返回false
	bool GetSgfTreeMove(SGFTree* tree, int movecount, CString* moves, int& x, int& y, int& color, CString& comment);
	//处理重做按钮
	void OnRedo();
	//改变死活题难度
	void ChangeDiffculty(int lvl);
	//全盘分析
	void OnAnaAll();
	//用分析结果来设置着手胜率（分数）
	void SetMoveWinRateFromAna();
	//保存单步用时、胜率、标准胜率等数据到SGFTree
	void SgfSaveData(SGFTree* tree);
	//计算着手分数字特征
	void CalMoveScoreMD(double& xm1, double& xd1, double& xm2, double& xd2);
	//在棋盘上绘制标识
	void PaintLabel();
	//将SGF格式着手转换为SFC格式
	void TransSgf(CString move, int& x, int& y);

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMBoard13();
	afx_msg void OnUpdateMBoard13(CCmdUI *pCmdUI);
	afx_msg void OnMBoard19();
	afx_msg void OnUpdateMBoard19(CCmdUI *pCmdUI);
	afx_msg void OnMBoard9();
	afx_msg void OnUpdateMBoard9(CCmdUI *pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	BOOL m_bBlack;
	CComboBox m_cmbMb;
	int m_iMb;
	CEdit m_eOutput;
	CString m_strOutput;
	afx_msg void OnBnClickedBtnbz();
	afx_msg void OnBnClickedBtnana();
	afx_msg void OnBnClickedBtnexit();
	int m_iState; //功能状态，1-死活分析，2-人机对弈
	int m_iState1; //功能状态，0-初始状态，1-等待玩家落子，2-电脑着手，忙碌；3-暂停；4-电脑支招/死活分析状态，忙碌；5-分析完毕；6-查看分析着手状态；11-死活题摆子状态；12-死活题载入棋谱后状态；13-死活题研究状态；14-死活练习状态；
	int m_iOldState1;//功能状态的备份
	bool m_bInTurn;	//交替落子
	CButton btnBz;
	virtual void OnDraw(CDC* /*pDC*/);
	int m_iPasses;
	bool m_bSgf_initialized;
	bool m_bResignation_allowed;
	int m_iBoardSize; //棋盘大小
	int m_iBoard[19][19]; //棋盘数组
	int m_iGoCount; //对局记录数
	int m_iOldGoCount;//暂存的对局记录数
	int m_iGoCountMax;//棋谱最大记录
	int m_iOldGoCountMax;//暂存的棋谱最大记录
	Data_GoRecord m_GoRecord[500]; //对局/摆子记录
	Data_GoRecord m_OldGoRecord[500];//暂存的对局/摆子记录
	CRect m_rBoardBack;//棋盘背景区域
	CRect m_BoardRect; //棋盘区域
	int m_iGap; //棋格间隙
	int m_iColor; //摆子方，1-白，2-黑
	bool m_bRecall; //复盘标志
	int m_iRecallStartId; //复盘起始位
	int m_iRecallId;//复盘当前位置
	float m_fWhiteScore, m_fBlackScore;//双方得分
	float m_fBlackWinRate, m_fWhiteWinRate;//双方胜率
	int m_iHandiCap;//让子数
	float m_fKomi;//贴目
	int m_iFixedStone;//固定棋子数
	int m_iOldFixedStone;//保存的固定棋子数
	bool m_bPicked;//已经拿起棋子
	int m_bMouseMoveCount;//鼠标移动次数
	int m_iCx, m_iCy, m_iCcolor;//电脑着手点及颜色
	int m_iProgress;//进度条进度
	bool m_bPaused;//是否已暂停
	bool m_bSelfPlay;//是否引擎自战
	bool m_bEngineDual;//是否引擎对战
	CString* m_sMoveRecs;//着手坐标记录（标准模式）
	CString* m_sMoveTimeRecs;//着手用时
	float* m_fMoveWinRates;//着手胜率
	float* m_fStdMoveWinRates;//标准（最佳）着手胜率
	CString* m_OldMoveRecs;//暂存的着手记录
	CString* m_sOldMoveTimeRecs;//暂存的着手用时
	float* m_fOldMoveWinRates;//暂存的着手胜率
	int m_iFirstColor;//先着者颜色
	int m_iMoveCount;//着手数
	int m_iOldMoveCount;//暂存的着手数
	CString* m_sAnaMoveRecs;//分析着手坐标记录
	int* m_iAnaMoveVisits;//分析着手访问节点数
	float* m_fAnaMoveWinRates;//分析着手胜率
	int m_iAnaMoveCount;//分析着手数
	int m_iOldAnaMoveCount;//暂存的分析手数
	bool m_bAnaed;//指示是否已经分析过
	CString m_sBlackName;//执黑者名字
	//CString m_sBlackTitle;//执黑者头衔
	CString m_sWhiteName;//执白者名字
	//CString m_sWhiteTitle;//执白者头衔
	//int m_iBlackLevel;//执黑者等级
	//int m_iWhiteLevel;//执白者等级
	bool m_bSgfLoaded;//载入了棋谱
	bool m_bSfcSgfLoaded;//载入了SfcGo产生的棋谱
	CString m_sResult;//对局结果
	bool m_bGameOver;//对局是否结束
	bool m_bReOpen;//是否是重开对局
	int m_iLifeDeathMoveCounts[100];
	CString* m_sLifeDeathMovess[100];
	CString* m_sLifeDeathMoveCommentss[100];
	CString m_sLifeDeathCmd;//死活分析命令
	bool m_bShowLifeDeathPanel;//是否显示死活功能面板
	int m_iMoveRecHeight;//着手记录高度
	int m_iAnaMoveId;//分析着手记录ID
	int m_iAnaMoveStartId;//分析着手显示开始ID
	int m_iADColor = 1;//待攻/防棋群颜色
	int m_iCombat = 0;//对局类型，0-自由对局，1-挑战赛
	bool m_bShowRecSize;//是否有屏幕空间显示胜率图表、分析、着手记录等
	bool m_bShowInfoSize;//是否有屏幕空间显示对局信息、功能按钮等
	bool m_bDifficulty;//是否正处于死活练习难度选择状态
	bool m_bAnswered;//死活题已经解答
	bool m_bAnaAll;//是否正在全盘分析
	bool m_bAllAnaed;//是否已经全盘分析过
	int m_iLabelCount;//标记数
	bool m_bCaptured;
	CString* m_sLabels;//标记列表
	HCURSOR m_hBlackCursor;//黑棋子游标
	HCURSOR m_hWhiteCursor;//白棋子游标
	CRect m_rBlackInfo;//黑棋信息区域
	CRect m_rWhiteInfo;//白棋信息区域
	CRect m_rBlackTime;//黑棋时间区域
	CRect m_rWhiteTime;//白棋时间区域
	CRect m_rProgressBar;//进度条区域
	CRect m_rPeriodString;//单步用时字符区域
	CRect m_rPeriodTime;//单步用时区域
	CRect m_rPlayInfo;//游戏信息区域
	CRect m_rOutputInfo;//信息输出区域，包括轮谁先走等等
	CRect m_rOtherInfo;//其他信息输出区域，如胜率等
	CRect m_rToolBox;//工具箱区域
	CRect m_rNew;//新对局/PASS按钮区域
	CRect m_rOpen;//打开棋谱/悔棋按钮区域
	CRect m_rSave;//保存棋谱支招按钮区域
	CRect m_rReopen;//暂停/继续棋局按钮区域
	CRect m_rArea;//形势判断按钮区域
	CRect m_rExit;//退出/交换对局按钮区域
	CRect m_rGoFirst;//回到最初按钮区域
	CRect m_rGoFiveBack;//后退五步按钮区域
	CRect m_rGoBack;//后退按钮区域
	CRect m_rGoForward;//前进按钮区域
	CRect m_rGoFiveForward;//前进五步按钮区域
	CRect m_rGoLast;//前进到底按钮区域
	CRect m_rResign;//认输按钮区域
	CRect m_rWinRateChart;//胜率图表区域
	CRect m_rAnaMove;//分析着手区域
	CRect m_rMoveRec;//着手记录区域
	CRect m_rPanel;//死活题功能面板区域
	CRect m_rTesuji;//手筋练习按钮区域
	CRect m_rElementary;//初级死活按钮区域
	CRect m_rMiddle;//中级死活按钮区域
	CRect m_rAdvanced;//高级死活按钮区域
	CRect m_rPutBlack;//摆放黑子按钮区域
	CRect m_rPutWhite;//摆放白子按钮区域
	CRect m_rBlackFirst;//黑先按钮区域
	CRect m_rWhiteFirst;//白先按钮区域
	int m_iStateNew;//新对局/PASS按钮状态，0-normal, 1-hover, 2-down, 3-disable
	int m_iStateOpen;//打开棋谱/悔棋按钮状态，0-normal, 1-hover, 2-down, 3-disable
	int m_iStateSave;//保存/支招按钮状态，0-normal, 1-hover, 2-down, 3-disable
	int m_iStateReopen;//继续/暂停按钮状态，0-normal, 1-hover, 2-down, 3-disable
	int m_iStateArea;//形势判断按钮状态，0-normal, 1-hover, 2-down, 3-disable
	int m_iStateExit;//退出/交换按钮状态，0-normal, 1-hover, 2-down, 3-disable
	int m_iStateGoFirst;//回到最初按钮状态，0-normal, 1-hover, 2-down, 3-disable
	int m_iStateGoFiveBack;
	int m_iStateGoBack;
	int m_iStateGoForward;
	int m_iStateGoFiveForward;
	int m_iStateGoLast;
	int m_iStateResign;//认输按钮状态，0-normal, 1-hover, 2-down, 3-disable
	int m_iStateTesuji;//手筋练习按钮状态
	int m_iStateElemantary;//初级死活按钮状态
	int m_iStateMiddle;//中级死活按钮状态
	int m_iStateAdvanced;//高级死活按钮状态
	int m_iStatePutBlack;//摆放黑子按钮状态
	int m_iStatePutWhite;//摆放白子按钮状态
	int m_iStateBlackFirst;//黑先按钮状态
	int m_iStateWhiteFirst;//白先按钮状态
	int m_iMainTime;//对弈规定时间
	int m_iByoTime;//读秒时间
	int m_iByoStones;//读秒落子数
	int m_iComputerThinkTime;//电脑思考时间
	int m_iComputerThinkTime2;//引擎自战或对战时第二引擎思考时间
	int m_iComputerByoTime;//电脑读秒时间，在maintime为0时可设置电脑单步时间
	int m_iComputerByoTime2;//引擎自战或对战时第二引擎读秒时间，在maintime为0时可设置单步时间
	int m_iComputerByoStones;//电脑读秒落子数
	CString m_sPlayInfo;//游戏信息
	CString m_sOutputInfo;//输出信息
	CString m_sOtherInfo;//其他信息
	CTime m_StartTime;//对弈开始时间
	CTime m_PauseStartTime;//对弈暂停开始时间
	CTimeSpan m_PauseTime;//对弈暂停总时间
	CTimeSpan m_BlackTime;//黑棋用时
	CTimeSpan m_WhiteTime;//白棋用时
	CTimeSpan m_PeriodTime;//单步用时
	Data_GoInfo m_GoInfo;
	Gameinfo m_Gameinfo;
	SGFTree m_Sgftree;
	SGFTree m_Sgftree1;
	CString m_sSfgFileName;//读入的棋谱文件
	CString m_sSgfPathName;//读入的棋谱文件全名（含路径）
	char m_OutFileName[255];
	SfcGtp* m_pEngine1 = nullptr, * m_pEngine2 = nullptr, * m_pEngine = nullptr;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedRadblack();
	afx_msg void OnBnClickedRadwhite();
	afx_msg void OnViewRecall();
	afx_msg void OnUpdateViewRecall(CCmdUI *pCmdUI);
	afx_msg void OnCbnSelchangeCmbmb();
	CButton m_btnAna;
	CButton m_radBlack;
	CButton m_btnScore;
	CButton m_radWhite;
	CButton m_radInturn;
	afx_msg void OnMKomi();
	afx_msg void OnUpdateMKomi(CCmdUI *pCmdUI);
	CButton m_btnExit;
	int m_iMaxSizePos;//死活分析的目标点
	afx_msg void OnBnClickedRadinturn();
	afx_msg void OnBnClickedBtnscore();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMCoord();
	afx_msg void OnMAnimate();
	afx_msg void OnMThinkprogress();
	afx_msg void OnMPutstonesound();
	afx_msg void OnMCapturestonesound();
	afx_msg void OnMPickstonesound();
	afx_msg void OnMPushclocksound();
	afx_msg void OnMByosound();
	afx_msg void OnUpdateMCoord(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMAnimate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMThinkprogress(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMPutstonesound(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMCapturestonesound(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMPickstonesound(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMPushclocksound(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMByosound(CCmdUI* pCmdUI);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMShowwinrate();
	afx_msg void OnUpdateMShowwinrate(CCmdUI* pCmdUI);
	afx_msg void OnMShowana();
	afx_msg void OnUpdateMShowana(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMShowmoverec(CCmdUI* pCmdUI);
	afx_msg void OnMShowinfo();
	afx_msg void OnUpdateMShowinfo(CCmdUI* pCmdUI);
	afx_msg void OnMShowmoverec();
	afx_msg void OnMLe();
	afx_msg void OnUpdateMLe(CCmdUI* pCmdUI);
	afx_msg void OnMLz();
	afx_msg void OnUpdateMLz(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // SfcGoView.cpp 中的调试版本
inline CSfcGoDoc* CSfcGoView::GetDocument() const
   { return reinterpret_cast<CSfcGoDoc*>(m_pDocument); }
#endif

