
// SfcGoView.cpp : CSfcGoView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SfcGo.h"
#endif


#include "SfcGoDoc.h"
#include "SfcGoView.h"
#include "math.h"
//#include "Sfc.h"
#include "DlgSetKomi.h"
#include "DlgNewGame.h"
#include "mmsystem.h"
#include "DlgNotify.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


extern int iScwd,iScht;//屏幕分辨率
extern CString strSysDirectry;//系统目录
extern CString strDirectry;//数据目录
extern CString strImgDirectry;//图像文件目录
extern CString strOutputDirectry;//输出目录
extern CString Version;//版本号
extern CString Edition;//版本
extern int iLanguage;//语言
extern int iCpuNum;//cpu（核）数
extern bool volatile bAnalysing;//正在分析中
extern CString sPlayerName;//玩家名
extern int iPlayerLevel;//玩家等级
extern int iEngineNum;//引擎数
extern int iEngineTypes[10];//引擎ID
extern CString sEngineNames[10];//引擎名称
extern CString sEngineAppNames[10];//引擎执行文件名
extern CString sEngineAppDirs[10];//引擎目录
extern CString sEngineCmdLines[10];//引擎命令行
extern CString sEngineCmdLines1[10];//引擎命令行1，供死活分析或较强棋力
extern int iPlayer1;//黑棋弈者，0-玩家，1-电脑
extern int iLevel1;//电脑执黑时的等级，1-初段，10-棋圣
extern int iTime1;//电脑执黑时的思考时长，0-15秒，1-30秒，2-60秒，3-120秒
extern int iEngine1;//黑棋引擎选择
extern int iPlayer2;//白棋奕者，，0-玩家，1-电脑
extern int iLevel2;//电脑执白时的等级，1-初段，10-棋圣
extern int iTime2;//电脑执白时的思考时长，0-15秒，1-30秒，2-60秒，3-120秒
extern int iEngine2;//白棋引擎选择
extern int iRule;//对弈规则，0-中国，1-日本，2-韩国
extern int iBoard;//棋盘规格，0-19路，1-13路，2-9路
extern int iKomi;//贴目，0-倒贴10目，40-贴10目
extern int iHandi;//让子数，0-分先，1-定先，2以上-让子数
extern bool bCoord;//是否画棋盘坐标
extern bool bAnimate;//是否有落子动画
extern bool bThinkProgress;//是否显示电脑思考进度
extern bool bShowInfo;//是否显示信息和工具栏
extern bool bShowWinRate;//是否显示胜率图
extern bool bShowAna;//是否显示分析着手
extern bool bShowMoveRec;//是否显示着手记录
extern bool bPutStoneSound;//是否播放落子声音
extern bool bCaptureSound;//是否播放提子声音
extern bool bPickStoneSound;//是否播放从棋盒中拾子的声音
extern bool bPushClockSound;//是否播放按计时钟的声音
extern bool bByoSound;//是否播放读秒声
extern int iLDlevel;//死活题等级，0-手筋，1-初级，2-中级，3-高级
extern int iQuest0;//手筋练习当前题号
extern int iQuest1;//初级死活当前题号
extern int iQuest2;//中级死活当前题号
extern int iQuest3;//高级死活当前题号
extern int iQuestMax0;//手筋练习最大题号
extern int iQuestMax1;//初级死活最大题号
extern int iQuestMax2;//中级死活最大题号
extern int iQuestMax3;//高级死活最大题号
extern int iState;//功能状态，0-空闲，1-死活题
extern int iBoardSizeState;//棋盘大小，0-9X9，1-13X13，2-19X19
extern int iBoardSize;//棋盘大小
extern CImage imBoardImg;//棋盘背景图片
extern CImage imBlackStone;//黑棋子图片
extern CImage imWhiteStone;//白棋子图片
extern CImage imBlackInfo;//黑棋方信息图片
extern CImage imWhiteInfo;//白棋方信息图片
extern CImage imProgressBar;//用时/思考进度图片
extern CImage imPlayInfo;//对局信息图片
extern CImage imToolBox;//工具箱图片
extern CImage imBackGound;//对局地面背景图片
extern CImage imNewNormal;//新对局图片
extern CImage imNewHover;//新对局鼠标悬停图片
extern CImage imNewDown;//新对局鼠标按下图片
extern CImage imNewDisable;//新对局按钮禁用图片
extern CImage imOpenNormal;//打开棋谱按钮图片
extern CImage imOpenHover;
extern CImage imOpenDown;
extern CImage imOpenDisable;
extern CImage imOpenNormal0;//打开棋谱按钮图片
extern CImage imOpenHover0;
extern CImage imOpenDown0;
extern CImage imOpenDisable0;
extern CImage imSaveNormal;//保存按钮图片
extern CImage imSaveHover;
extern CImage imSaveDown;
extern CImage imSaveDisable;
extern CImage imReopenNormal;//继续对局按钮图片
extern CImage imReopenHover;
extern CImage imReopenDown;
extern CImage imReopenDisable;
extern CImage imAreaNormal;//形势判断按钮图片
extern CImage imAreaHover;
extern CImage imAreaDown;
extern CImage imAreaDisable;
extern CImage imAreaNormal0;//形势判断按钮图片
extern CImage imAreaHover0;
extern CImage imAreaDown0;
extern CImage imAreaDisable0;
extern CImage imResignNormal;//退出/认输按钮图片
extern CImage imResignHover;
extern CImage imResignDown;
extern CImage imResignDisable;
extern CImage imGoFirstNormal;//回到最初按钮图片
extern CImage imGoFirstHover;
extern CImage imGoFirstDown;
extern CImage imGoFirstDisable;
extern CImage imGoFiveBackNormal;//后退五步按钮图片
extern CImage imGoFiveBackHover;
extern CImage imGoFiveBackDown;
extern CImage imGoFiveBackDisable;
extern CImage imGoBackNormal;//后退按钮图片
extern CImage imGoBackHover;
extern CImage imGoBackDown;
extern CImage imGoBackDisable;
extern CImage imGoForwardNormal;//前进按钮图片
extern CImage imGoForwardHover;
extern CImage imGoForwardDown;
extern CImage imGoForwardDisable;
extern CImage imGoFiveForwardNormal;//前进五步按钮图片
extern CImage imGoFiveForwardHover;
extern CImage imGoFiveForwardDown;
extern CImage imGoFiveForwardDisable;
extern CImage imGoLastNormal;//前进到底按钮图片
extern CImage imGoLastHover;
extern CImage imGoLastDown;
extern CImage imGoLastDisable;
extern CImage imExitNormal;//退出按钮图片
extern CImage imExitHover;
extern CImage imExitDown;
extern CImage imExitDisable;
extern CImage imPassNormal;//PASS按钮图片
extern CImage imPassHover;
extern CImage imPassDown;
extern CImage imPassDisable;
extern CImage imRetractNormal;//悔棋按钮图片
extern CImage imRetractHover;
extern CImage imRetractDown;
extern CImage imRetractDisable;
extern CImage imHintNormal;//支招按钮图片
extern CImage imHintHover;
extern CImage imHintDown;
extern CImage imHintDisable;
extern CImage imPauseNormal;//暂停按钮图片
extern CImage imPauseHover;
extern CImage imPauseDown;
extern CImage imPauseDisable;
extern CImage imChangeStoneNormal;//交换对局
extern CImage imChangeStoneHover;
extern CImage imChangeStoneDown;
extern CImage imChangeStoneDisable;
extern CImage imRecDesk;//着手记录桌图片
extern CImage imRec;//着手记录图片
extern CImage imRecSelected;//选中着手记录图片
extern CImage imChart;//胜率图表图片
extern CImage imRecTitle;//记录标题图片
//extern CImage imEmptyNormal;//空按钮图片
//extern CImage imEmptyHover;
//extern CImage imEmptyDown;
//extern CImage imEmptyDisable;
extern CImage imPutStoneNormal;//摆子出题按钮图片
extern CImage imPutStoneHover;
extern CImage imPutStoneDown;
extern CImage imPutStoneDisable;
extern CImage imContinueNormal;//继续做题按钮图片
extern CImage imContinueHover;
extern CImage imContinueDown;
extern CImage imContinueDisabel;
extern CImage imDifficultyNormal;//难度选择按钮图片
extern CImage imDifficultyHover;
extern CImage imDifficultyDown;
extern CImage imDifficultyDisable;
extern CImage imTesujiNormal;//手筋练习按钮图片
extern CImage imTesujiHover;
extern CImage imElementaryNormal;//初级死活按钮图片
extern CImage imElementaryHover;
extern CImage imMiddleNormal;//中级死活按钮图片
extern CImage imMiddleHover;
extern CImage imAdvancedNormal;//高级死活按钮图片
extern CImage imAdvanceeHover;
extern CImage imPutBlackNormal;//摆放黑子按钮图片
extern CImage imPutBlackHover;
extern CImage imPutBlackDown;
extern CImage imPutBlackDisable;
extern CImage imPutWhiteNormal;//摆放白子按钮图片
extern CImage imPutWhiteHover;
extern CImage imPutWhiteDown;
extern CImage imPutWhiteDisable;
extern CImage imBlackFirstNormal;//黑先按钮图片
extern CImage imBlackFirstHover;
extern CImage imBlackFirstDown;
extern CImage imBlackFirstDisable;
extern CImage imWhiteFirstNormal;//白先按钮图片
extern CImage imWhiteFirstHover;
extern CImage imWhiteFirstDown;
extern CImage imWhiteFirstDisable;
extern CImage imStudyNormal;//研究按钮图片
extern CImage imStudyHover;
extern CImage imStudyDown;
extern CImage imStudyDisable;
extern CImage imSolveNormal;//死活分析开始做题按钮图片
extern CImage imSolveHover;
extern CImage imSolveDown;
extern CImage imSolveDisable;
extern CImage imAIanaNormal;//AI分析按钮图片
extern CImage imAIanaHover;
extern CImage imAIanaDown;
extern CImage imAIanaDisable;
extern CImage imPutStoneStudyNormal;//摆子研究按钮图片
extern CImage imPutStoneStudyHover;
extern CImage imPutStoneStudyDown;
extern CImage imPutStoneStudyDisable;
extern CImage imPassMoveNormal;//PASS一手按钮图片
extern CImage imPassMoveHover;
extern CImage imPassMoveDown;
extern CImage imPassMoveDisable;
extern CImage imSolutionNormal;//查看死活题解答按钮图片
extern CImage imSolutionHover;
extern CImage imSolutionDown;
extern CImage imSolutionDisable;
extern CImage imRedoNormal;//重做按钮图片
extern CImage imRedoHover;
extern CImage imRedoDown;
extern CImage imRedoDisable;
extern CImage imSolveNormal2;//死活分析解题小按钮
extern CImage imSolveHover2;
extern CImage imSolveDown2;
extern CImage imSolveDisable2;
extern CImage imStudyNormal2;//死活题研究小按钮
extern CImage imStudyHover2;
extern CImage imStudyDown2;
extern CImage imStudyDisable2;
extern CImage imAnaAllNormal;//全盘分析按钮图片
extern CImage imAnaAllHover;
extern CImage imAnaAllDown;
extern CImage imAnaAllDisable;
extern CImage imReturnNormal;//返回按钮图片
extern CImage imReturnHover;
extern CImage imReturnDown;
extern CImage imReturnDisabel;
//extern CImage imStoneEffect;
extern CRect ctRect;//客户区大小
//static int passes=0;
//static int sgf_initialized=0;
//static int resignation_allowed=1;
/* Unreasonable score used to detect missing information. */
//#define NO_SCORE 4711
/* Keep track of the score estimated before the last computer move. */
//static int current_score_estimate = NO_SCORE;
//int SgfToGoRecord(SGFTree *tree, int &gocount, Data_GoRecord gorecord[], int &recallstartid); //从SGFTree转换为GoRecord
unsigned int iRandomSeed=100;
//float fKomi = 6.5;
int iLevel = 0;
char bLife_death = 0;
int iMcount = 0;
int Dmoves[361];
CCriticalSection csCs;//线程临界点
int iThreadState = 0;//线程状态，0-未启动，1-运行中
int iEngineId=0;//正在运行的Engine的ID
int iBlackEngineId = 0, iWhiteEngineId = 1;
int iEngineThreadState=0;//Engine线程状态，0-空闲，1-工作中，2-任务完成
CString sMsg,sThinkMsg;
extern DlgNotify* pDlgNotify;//信息提示

/*判断是否为棋盘上的点*/
/*static bool OnBoard(int x, int y)
{
	return x>=0 && x<iBoardSize && y>=0 && y<iBoardSize;
}
*/
/*计算棋群相关空白点（着手点）*/
/*/static int GetDragonMoves(int board[19][19], int pos, int* dmoves)
{
	int org=dragon[pos].origin,color=dragon[pos].color, mcount=0,mpos;
	for(int i=0;i<iBoardSize;i++)
	{
		for(int j=0;j<iBoardSize;j++)
		{
			if(board[i][j]!=0)
				continue;
			bool bmark=false;
			for(int k=0;k<iBoardSize;k++)
			{
				for(int l=0;l<iBoardSize;l++)
				{
					mpos=POS(k,l);
					if(dragon[mpos].origin!=org)
						continue;
					if(StoneLinkToStone(i,j,color,k,l,board))
					{
						dmoves[mcount]=POS(i,j);
						mcount++;
						bmark=true;
						break;
					}
				}
				if(bmark)
					break;
			}
		}
	}
	return mcount;
}*/

/*UINT PlayStoneSound(LPVOID pParam)
{
	PlaySound(strSysDirectry + "\\PickStone.wav", NULL, SND_SYNC);
	return 0;
}*/

UINT PlayerMoveThread(LPVOID pParam)
{
	CSingleLock sl(&csCs);
	CSfcGoView* pView;
	int x, y, color;
	sl.Lock();
	{
		pView = (CSfcGoView*)pParam;
		x = pView->m_iCx;
		y = pView->m_iCy;
		color = pView->m_iColor;
	}
	sl.Unlock();
	pView->PlayerMove(x, y, color);
	return 0;
}

UINT ComputerMoveThread(LPVOID pParam)
{
	CSingleLock sl(&csCs);
	CSfcGoView* pView;
	int threadstate = 1;
	while (threadstate == 1)
	{
		Sleep(250);
		sl.Lock();
		{
			threadstate = iThreadState;
		}
		sl.Unlock();
	}
	sl.Lock();
	{
		pView = (CSfcGoView*)pParam;
	}
	sl.Unlock();
	pView->ComputerMove();
	return 0;
}

//获取引擎着手及分析结果
UINT GetEngineMove(LPVOID pParam)
{
	CSingleLock sl(&csCs);
	CSfcGoView* pView;
	SfcGtp* pengine = nullptr;
	CString msg, str1, str2, str0="";
	CString* strs = nullptr;
	int count, x = -10, y = -10, count0;
	int color, boardsize;// , len;
	float winrate = -1;
	CString* anamovs = new CString[100];
	int* anavisits = new int[100];
	float* anawinrates = new float[100];
	int anacount = 0;
	int state = 0;
	CString cmdline;
	sl.Lock();
	{
		pView = (CSfcGoView*)pParam;
		if (iEngineId == 0)
			pengine = pView->m_pEngine1;
		if (iEngineId == 1)
			pengine = pView->m_pEngine2;
		color = pView->m_iCcolor;
		boardsize = pView->m_iBoardSize;
		state = pView->m_iState;
		cmdline = pView->m_sLifeDeathCmd;
	}
	sl.Unlock();
	switch (pengine->m_Id)
	{
	case 0://katago
		msg = "kata-genmove_analyze";
		if (color == 1)
			msg += " W ";
		else
			msg += " B ";
		msg += "50";
		if (state == 1)//死活分析
			msg += cmdline;
		msg += "\r\n";
		pengine->WriteToPipe(msg);
		strs = pengine->GetMsg(count);
		//get move
		for (int i = count-1; i >= 0; i--)
		{
			if (strs[i].GetLength() > 7 && strs[i].Left(4) == "play")
			{
				str1 = strs[i];
				str1.TrimRight();
				str1 = str1.Right(str1.GetLength() - 5);
				pView->Trans(str1, x, y);
				break;
			}
		}
		//get win rate and analyze infomation
		//str2 = "info move " + str1;
		//len = str2.GetLength();
		if (x >= 0 && x < boardsize)
		{
			/*for (int i = count - 1; i >= 0; i--)
			{
				if (strs[i].GetLength() > 40 && strs[i].Left(len) == str2)
				{
					int count1;
					CString* strs1 = SfcGtp::SplitString(strs[i], " ", count1);
					for (int j = 0; j < count1; j++)
					{
						if (strs1[j] == "winrate")
						{
							winrate = atof(strs1[j + 1]);
							break;
						}
					}
					delete[] strs1;
					break;
				}
			}*/
			for (int i = count - 1; i >= 0; i--)
			{
				if (strs[i].GetLength() > 40 && strs[i].Left(9) == "info move")
				{
					/*CString move = strs[i].Left(13);
					move = move.Right(3).TrimRight();
					int j;
					for (j = 0; j < anacount; j++)
						if (anamovs[j] == move)
							break;
					if (j < anacount)
						continue;
					anamovs[anacount] = move;*/
					int count1;
					CString* strs1 = SfcGtp::SplitString(strs[i], " ", count1);
					for (int j = 0; j < count1-40; j++)
					{
						if (strs1[j] == "info" && strs1[j + 1] == "move")
						{
							anamovs[anacount] = strs1[j + 2];
							j += 2;
							continue;
						}
						if (strs1[j] == "visits")
						{
							anavisits[anacount] = atoi(strs1[j + 1]);
							j++;
							continue;
						}
						if (strs1[j] == "winrate")
						{
							anawinrates[anacount] = atof(strs1[j + 1]);
							if (anamovs[anacount] == str1)
								winrate = anawinrates[anacount];
							anacount++;
							if (anacount >= 100)
								break;
							j++;
						}
					}
					delete[] strs1;
					break;
				}
			}
		}
		delete[] strs;
		break;
	case 1://leela
		msg = "lz-genmove_analyze";//"genmove";
		if (color == 1)
			msg += " W ";
		else
			msg += " B ";
		msg += "50\r\n";
		pengine->WriteToPipe(msg);
		//strs0 = new CString[10000];
		count0 = 0;
		while (x < -2 || x >= boardsize || y >= boardsize)
		{
			strs = pengine->GetMsg(count);
			for (int i = count-1; i >= 0; i--)
			{
				if (strs[i].GetLength() > 7 && strs[i].Left(4) == "play")//(strs[i].GetLength() >= 4 && strs[i].Left(1) == "=")
				{
					str1 = strs[i];
					str1.TrimRight();
					str1 = str1.Right(str1.GetLength() - 5);
					pView->Trans(str1, x, y);
					//if (str1.GetLength() <= 8)
						//pView->Trans(str1.Right(str1.GetLength() - 2), x, y);
					if (x >= -2 && x < boardsize && y < boardsize)
						break;
				}
			}
			for (int i = count - 1; i >= 0; i--)
			{
				if (strs[i].GetLength() > 40 && strs[i].Left(9) == "info move")
				{
					str0 = strs[i];
					break;
				}
			}
			delete[] strs;
		}
		//get win rate
		if (x >= 0 && x < boardsize)
		{
			int count1;
			CString* strs1 = SfcGtp::SplitString(str0, " ", count1);
			for (int j = 0; j < count1 - 40; j++)
			{
				if (strs1[j] == "info" && strs1[j + 1] == "move")
				{
					anamovs[anacount] = strs1[j + 2];
					j += 2;
					continue;
				}
				if (strs1[j] == "visits")
				{
					anavisits[anacount] = atoi(strs1[j + 1]);
					j++;
					continue;
				}
				if (strs1[j] == "winrate")
				{
					anawinrates[anacount] = atof(strs1[j + 1])/10000;
					if (anamovs[anacount] == str1)
						winrate = anawinrates[anacount];
					anacount++;
					if (anacount >= 100)
						break;
					j++;
				}
			}
			delete[] strs1;
			/*for (int i = count0 - 1; i >= 0; i--)
			{
				if (strs0[i].GetLength() > 40 && strs0[i].Left(len) == str2)
				{
					int count1;
					CString* strs1 = SfcGtp::SplitString(strs0[i], " ", count1);
					for (int j = 0; j < count1; j++)
					{
						if (strs1[j] == "winrate")
						{
							winrate = atof(strs1[j + 1]) / 10000;
							break;
						}
					}
					delete[] strs1;
					break;
				}
			}
			for (int i = count0 - 1; i >= 0; i--)
			{
				if (strs0[i].GetLength() > 40 && strs0[i].Left(9) == "info move")
				{
					CString move = strs0[i].Left(13);
					move = move.Right(3).TrimRight();
					int j;
					for (j = 0; j < anacount; j++)
						if (anamovs[j] == move)
							break;
					if (j < anacount)
						continue;
					anamovs[anacount] = move;
					int count1;
					CString* strs1 = SfcGtp::SplitString(strs0[i], " ", count1);
					for (j = 3; j < count1; j++)
					{
						if (strs1[j] == "visits")
						{
							anavisits[anacount] = atoi(strs1[j + 1]);
							j++;
							continue;
						}
						if (strs1[j] == "winrate")
						{
							anawinrates[anacount] = atof(strs1[j + 1]) / 10000;
							anacount++;
							break;
						}
					}
					delete[] strs1;
					if (anacount >= 100)
						break;
				}
			}*/
		}
		//delete[] strs0;
		break;
	}
	sl.Lock();
	{
		pView->m_iCx = x;
		pView->m_iCy = y;
		iEngineThreadState = 2;
		if (winrate >= 0)
		{
			color == BLACK ? pView->m_fBlackWinRate = winrate : pView->m_fWhiteWinRate = winrate;
			if (!pView->m_bSelfPlay && !pView->m_bEngineDual)
			{
				color == BLACK ? pView->m_fWhiteWinRate = 1 - winrate : pView->m_fBlackWinRate = 1 - winrate;
			}
		}
		pView->m_iAnaMoveCount = anacount;
		if (anacount > 0)
		{
			for (int i = 0; i < anacount; i++)
			{
				pView->m_sAnaMoveRecs[i] = anamovs[i];
				pView->m_iAnaMoveVisits[i] = anavisits[i];
				pView->m_fAnaMoveWinRates[i] = anawinrates[i];
			}
		}
	}
	sl.Unlock();
	delete[] anamovs;
	delete[] anavisits;
	delete[] anawinrates;
	return 0;
}

//获取引擎分析结果
UINT GetEngineAna(LPVOID pParam)
{
	CSingleLock sl(&csCs);
	CSfcGoView* pView;
	SfcGtp* pengine = nullptr;
	CString msg, str1, str2, str0 = "";
	CString* strs = nullptr;
	int count, x = -10, y = -10, count0;
	int color, boardsize;// , len;
	CString* anamovs = new CString[100];
	int* anavisits = new int[100];
	float* anawinrates = new float[100];
	int anacount = 0;
	int lifedeathmovecounts[100];
	CString* lifedeathmovess[100];
	for (int i = 0; i < 100; i++)
	{
		lifedeathmovecounts[i] = 0;
		lifedeathmovess[i] = new CString[50];
	}
	int lvl = 0;
	int state = 0;
	CString cmdline;
	sl.Lock();
	{
		pView = (CSfcGoView*)pParam;
		if (iEngineId == 0)
			pengine = pView->m_pEngine1;
		if (iEngineId == 1)
			pengine = pView->m_pEngine2;
		color = pView->m_iColor;
		if (pView->m_iState1 == 2)
			color = OTHER_COLOR(color);
		boardsize = pView->m_iBoardSize;
		lvl = iLevel;
		state = pView->m_iState;
		cmdline = pView->m_sLifeDeathCmd;
	}
	sl.Unlock();
	//非katago需先设定分析棋力
	if (pengine->m_Id != 0 && lvl < 21)
	{
		pView->SetLevel(21);
	}
	//开始分析
	msg = "lz-analyze";
	if (color == 1)
		msg += " W ";
	else
		msg += " B ";
	msg += "50";
	if (state == 1)//死活分析
		msg += cmdline;
	msg += "\r\n";
	pengine->WriteToPipe(msg);
	strs = pengine->GetMsg(count);
	for (int i = count - 1; i >= 0; i--)
	{
		if (strs[i].GetLength() > 40 && strs[i].Left(9) == "info move")
		{
			int count1;
			CString* strs1 = SfcGtp::SplitString(strs[i], " ", count1);
			for (int j = 0; j < count1; j++)
			{
				if (strs1[j] == "info" && strs1[j + 1] == "move")
				{
					anamovs[anacount] = strs1[j + 2];
					j += 2;
					continue;
				}
				if (strs1[j] == "visits")
				{
					anavisits[anacount] = atoi(strs1[j + 1]);
					j++;
					continue;
				}
				if (strs1[j] == "winrate")
				{
					anawinrates[anacount] = atof(strs1[j + 1]);
					anacount++;
					if (anacount >= 100)
						break;
					j++;
					continue;
				}
				//if (state == 1)//死活分析，获取后继着手
				//{
					if (strs1[j] == "pv")
					{
						j++;
						for (; j < count1; j++)
						{
							if (strs1[j] == "info")
							{
								j--;
								break;
							}
							lifedeathmovess[anacount - 1][lifedeathmovecounts[anacount - 1]] = strs1[j];
							lifedeathmovecounts[anacount - 1]++;
						}
					}
				//}
			}
			delete[] strs1;
			break;
		}
	}
	delete[] strs;
	for (int i = 0; i < anacount; i++)
			anawinrates[i] /= 10000;
	//恢复分析棋力
	if (pengine->m_Id != 0 && lvl < 21)
		pView->SetLevel(lvl);
	sl.Lock();
	{
		pView->m_iAnaMoveCount = anacount;
		if (anacount > 0)
		{
			for (int i = 0; i < anacount; i++)
			{
				pView->m_sAnaMoveRecs[i] = anamovs[i];
				pView->m_iAnaMoveVisits[i] = anavisits[i];
				pView->m_fAnaMoveWinRates[i] = anawinrates[i];
			}
		}
		//if (state == 1)//死活分析，记录后继着手
		//{
			for (int i = 0; i < anacount; i++)
			{
				pView->m_iLifeDeathMoveCounts[i] = lifedeathmovecounts[i];
				for (int j = 0; j < lifedeathmovecounts[i]; j++)
					pView->m_sLifeDeathMovess[i][j] = lifedeathmovess[i][j];
			}
		//}
		iEngineThreadState = 2;
	}
	sl.Unlock();
	delete[] anamovs;
	delete[] anavisits;
	delete[] anawinrates;
	for (int i = 0; i < 100; i++)
		delete[] lifedeathmovess[i];
	return 0;
}

//棋子移动动画
UINT StoneMove(LPVOID pParam)
{
	CPoint point;
	GetCursorPos(&point);
	CSingleLock sl(&csCs);
	CSfcGoView* pView;
	int x, y, color,cx,cy,left,top;
	CRect rect;
	sl.Lock();
	{
		pView = (CSfcGoView*)pParam;
		pView->GetClientRect(rect);
		x = pView->m_iCx;
		y = pView->m_iCy;
		color = pView->m_iCcolor;
		//int sx = rect.Height() / 22,sy=sx;
		//int w = rect.Height() - 2 * sx;
		//int edge = w / (pView->m_iBoardSize + 1);
		//w = edge * (pView->m_iBoardSize + 1);
		//int leftedge = (rect.Width() - (w + edge * 10)) / 2;
		//sx = leftedge;
		//cx = edge + sx + x * edge; -edge / 2 - 1;// +1;//edge*2/5;
		//cy = edge + sy + y * edge; -edge / 2 - 1;// +1;// edge * 2 / 5;
		cx = pView->m_BoardRect.left + x * pView->m_iGap;
		cy = pView->m_BoardRect.top + y * pView->m_iGap;
		//int w = pView->m_iGap + 4;
		if ((pView->m_bSelfPlay || pView->m_bEngineDual) && color == BLACK)//引擎对决时，黑棋从玩家方（右下角）出现
		{
			left = pView->m_BoardRect.right;
			top = pView->m_BoardRect.bottom;
		}
		else//其他时候，棋子从对方（左上角）出现
		{
			left = pView->m_BoardRect.left;
			top = pView->m_BoardRect.top;
		}
		pView->ClientToScreen(rect);
	}
	sl.Unlock();
	//int top = rect.Height() / 22, left = top;
	int pi = 5;
	int n = (cx - left) / 5;
	if (n < 0)
		n = -n;
	int n1 = n * 3 / 8;
	int n2 = n - n1;
	SetCursorPos(rect.left+left, rect.top+top);
	/*MOUSEINPUT input;
	input.dx = 0;
	input.dy = 0;
	input.dwExtraInfo = NULL;
	input.dwFlags = MOUSEEVENTF_MOVE;
	input.mouseData = NULL;
	input.time = 0*/;
	/*if (color == 1)
		SetCursor(pView->m_hWhiteCursor);
	else if (color == 2)
		SetCursor(pView->m_hBlackCursor);*/
	for (int i = 1; i <= n1; i++)
	{
		Sleep(10);
		//input.dwExtraInfo = cx / 100.0;
		//input.dy = cy / 100.0;
		//SendInput(INPUT_MOUSE, input, 1);
		mouse_event(MOUSEEVENTF_MOVE, (cx - left)*.8 / n1, (cy - top)*.8 / n1, 0, 0);
		SetCursorPos(rect.left + left + (cx - left)*.8 * i / n1, rect.top + top + (cy - top)*.8 * i / n1);

	}
	for (int i = 1; i <= n2; i++)
	{
		Sleep(10);
		//input.dwExtraInfo = cx / 100.0;
		//input.dy = cy / 100.0;
		//SendInput(INPUT_MOUSE, input, 1);
		mouse_event(MOUSEEVENTF_MOVE, (cx-left)*.2/n2, (cy-top)*.2/n2,0,0);
		SetCursorPos(rect.left+left+ (cx - left) * .8 +(cx-left)*.2 * i / n2, rect.top+top+ (cy - top) * .8 +(cy-top)*.2 * i / n2);

	}
	pView->AddStone(x, y, color);
	sl.Lock();
	{
		iThreadState = 0;
		if (!pView->m_bSelfPlay && !pView->m_bEngineDual && !pView->m_bPaused)
			pView->m_iState1 = 1;
	}
	sl.Unlock();
	SetCursorPos(point.x, point.y);
	return 0;
}

// CSfcGoView

IMPLEMENT_DYNCREATE(CSfcGoView, CFormView)

BEGIN_MESSAGE_MAP(CSfcGoView, CFormView)
	ON_COMMAND(ID_M_BOARD13, &CSfcGoView::OnMBoard13)
	ON_UPDATE_COMMAND_UI(ID_M_BOARD13, &CSfcGoView::OnUpdateMBoard13)
	ON_COMMAND(ID_M_BOARD19, &CSfcGoView::OnMBoard19)
	ON_UPDATE_COMMAND_UI(ID_M_BOARD19, &CSfcGoView::OnUpdateMBoard19)
	ON_COMMAND(ID_M_BOARD9, &CSfcGoView::OnMBoard9)
	ON_UPDATE_COMMAND_UI(ID_M_BOARD9, &CSfcGoView::OnUpdateMBoard9)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTNBZ, &CSfcGoView::OnBnClickedBtnbz)
	ON_BN_CLICKED(IDC_BTNANA, &CSfcGoView::OnBnClickedBtnana)
	ON_BN_CLICKED(IDC_BTNEXIT, &CSfcGoView::OnBnClickedBtnexit)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_RADBLACK, &CSfcGoView::OnBnClickedRadblack)
	ON_BN_CLICKED(IDC_RADWHITE, &CSfcGoView::OnBnClickedRadwhite)
	ON_COMMAND(ID_VIEW_RECALL, &CSfcGoView::OnViewRecall)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RECALL, &CSfcGoView::OnUpdateViewRecall)
	ON_CBN_SELCHANGE(IDC_CMBMB, &CSfcGoView::OnCbnSelchangeCmbmb)
	ON_COMMAND(ID_M_KOMI, &CSfcGoView::OnMKomi)
	ON_UPDATE_COMMAND_UI(ID_M_KOMI, &CSfcGoView::OnUpdateMKomi)
	ON_BN_CLICKED(IDC_RADINTURN, &CSfcGoView::OnBnClickedRadinturn)
	ON_BN_CLICKED(IDC_BTNSCORE, &CSfcGoView::OnBnClickedBtnscore)
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEHOVER()
	ON_WM_TIMER()
	ON_COMMAND(ID_M_COORD, &CSfcGoView::OnMCoord)
	ON_COMMAND(ID_M_ANIMATE, &CSfcGoView::OnMAnimate)
	ON_COMMAND(ID_M_THINKPROGRESS, &CSfcGoView::OnMThinkprogress)
	ON_COMMAND(ID_M_PUTSTONESOUND, &CSfcGoView::OnMPutstonesound)
	ON_COMMAND(ID_M_CAPTURESTONESOUND, &CSfcGoView::OnMCapturestonesound)
	ON_COMMAND(ID_M_PICKSTONESOUND, &CSfcGoView::OnMPickstonesound)
	ON_COMMAND(ID_M_PUSHCLOCKSOUND, &CSfcGoView::OnMPushclocksound)
	ON_COMMAND(ID_M_BYOSOUND, &CSfcGoView::OnMByosound)
	ON_UPDATE_COMMAND_UI(ID_M_COORD, &CSfcGoView::OnUpdateMCoord)
	ON_UPDATE_COMMAND_UI(ID_M_ANIMATE, &CSfcGoView::OnUpdateMAnimate)
	ON_UPDATE_COMMAND_UI(ID_M_THINKPROGRESS, &CSfcGoView::OnUpdateMThinkprogress)
	ON_UPDATE_COMMAND_UI(ID_M_PUTSTONESOUND, &CSfcGoView::OnUpdateMPutstonesound)
	ON_UPDATE_COMMAND_UI(ID_M_CAPTURESTONESOUND, &CSfcGoView::OnUpdateMCapturestonesound)
	ON_UPDATE_COMMAND_UI(ID_M_PICKSTONESOUND, &CSfcGoView::OnUpdateMPickstonesound)
	ON_UPDATE_COMMAND_UI(ID_M_PUSHCLOCKSOUND, &CSfcGoView::OnUpdateMPushclocksound)
	ON_UPDATE_COMMAND_UI(ID_M_BYOSOUND, &CSfcGoView::OnUpdateMByosound)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_M_SHOWMOVEREC, &CSfcGoView::OnMShowmoverec)
	ON_UPDATE_COMMAND_UI(ID_M_SHOWINFO, &CSfcGoView::OnUpdateMShowinfo)
	ON_COMMAND(ID_M_SHOWINFO, &CSfcGoView::OnMShowinfo)
	ON_UPDATE_COMMAND_UI(ID_M_SHOWMOVEREC, &CSfcGoView::OnUpdateMShowmoverec)
	ON_UPDATE_COMMAND_UI(ID_M_SHOWANA, &CSfcGoView::OnUpdateMShowana)
	ON_COMMAND(ID_M_SHOWANA, &CSfcGoView::OnMShowana)
	ON_UPDATE_COMMAND_UI(ID_M_SHOWWINRATE, &CSfcGoView::OnUpdateMShowwinrate)
	ON_COMMAND(ID_M_SHOWWINRATE, &CSfcGoView::OnMShowwinrate)
	ON_COMMAND(ID_M_LE, &CSfcGoView::OnMLe)
	ON_UPDATE_COMMAND_UI(ID_M_LE, &CSfcGoView::OnUpdateMLe)
	ON_COMMAND(ID_M_LZ, &CSfcGoView::OnMLz)
	ON_UPDATE_COMMAND_UI(ID_M_LZ, &CSfcGoView::OnUpdateMLz)
END_MESSAGE_MAP()

// CSfcGoView 构造/析构

CSfcGoView::CSfcGoView()
	: CFormView(CSfcGoView::IDD)
	, m_bBlack(FALSE)
	, m_iMb(0)
	, m_strOutput(_T(""))
	, m_iState(0)
	, m_iState1(0)
	, m_iBoardSize(19)
{
	// TODO: 在此处添加构造代码
	m_iPasses = 0;
	m_bSgf_initialized = false;
	m_bResignation_allowed = true;
	m_iHandiCap = 0;
	m_iFixedStone = 0;
	m_iGoCount = 0;
	m_iGoCountMax = 0;
	m_iOldGoCount = 0;
	m_iOldGoCountMax = 0;
	m_fKomi = 6.5;
	if (iRule == 0)
		m_fKomi = 7.5;
	m_bPicked = true;
	m_bMouseMoveCount = 0;
	m_iStateNew = 0;
	m_iStateOpen = 0;
	m_iStateSave = 3;
	m_iStateReopen = 3;
	m_iStateArea = 3;
	m_iStateExit = 0;
	m_iStateGoFirst = 0;
	m_iStateGoFiveBack = 0;
	m_iStateGoBack = 0;
	m_iStateGoForward = 0;
	m_iStateGoFiveForward = 0;
	m_iStateGoLast = 0;
	m_iStateResign = 0;
	m_iProgress = 0;
	m_sPlayInfo = "";
	m_sOutputInfo = "";
	m_sOtherInfo = "";
	m_fBlackScore = 0;
	m_fBlackWinRate = 0.5;
	m_fWhiteScore = 0;
	m_fWhiteWinRate = 0.5;
	m_bPaused = false;
	m_bSelfPlay = false;
	m_bEngineDual = false;
	m_sMoveRecs = new CString[500];
	m_sMoveTimeRecs = new CString[500];
	m_fMoveWinRates = new float[500] {0};
	m_fStdMoveWinRates = new float[500] {0};
	m_OldMoveRecs = new CString[500];
	m_sOldMoveTimeRecs = new CString[500];
	m_fOldMoveWinRates = new float[500] {0};
	m_sAnaMoveRecs = new CString[100];
	m_iAnaMoveVisits = new int[100] {0};
	m_fAnaMoveWinRates = new float[100] {0};
	m_iMoveCount = 0;
	m_iOldMoveCount = 0;
	m_iAnaMoveCount = 0;
	m_iOldAnaMoveCount = 0;
	m_iFirstColor = BLACK;
	m_bAnaed = false;
	m_bSgfLoaded = false;
	m_bSfcSgfLoaded = false;
	m_bGameOver = false;
	m_bReOpen = false;
	m_bShowLifeDeathPanel = false;
	for (int i = 0; i < 100; i++)
	{
		m_iLifeDeathMoveCounts[i] = 0;
		m_sLifeDeathMovess[i] = new CString[50];
		m_sLifeDeathMoveCommentss[i] = new CString[50];
	}
	m_iAnaMoveId = 0;
	m_iAnaMoveStartId = 0;
	m_bShowRecSize = true;
	m_bShowInfoSize = true;
	m_bDifficulty = false;
	m_iStateBlackFirst = 0;
	m_iStateWhiteFirst = 0;
	m_bAnswered = false;
	m_bAnaAll = false;
	m_bAllAnaed = false;
	m_bCaptured = false;
	m_iLabelCount = 0;
	m_sLabels = new CString[100];
	sgftree_clear(&m_Sgftree);
	sgftree_clear(&m_Sgftree1);
}

CSfcGoView::~CSfcGoView()
{
	/* Free the sgf tree and prepare for a new game. */
	//sgfFreeNode(sgftree.root);
	//sgftree_clear(&sgftree);
	//sgftreeCreateHeaderNode(&sgftree, board_size, komi, m_Gameinfo.handicap);
	//sgf_initialized = 0;

	//gameinfo_clear(&m_Gameinfo);

	/*/reading_cache_clear();
	reading_cache_free();
	
	clear_persistent_caches();
	persistent_cache_free();
	if(dragon2)
	{
		free(dragon2);
		dragon2=nullptr;
	}
	owl_stack_free();*/
	if (m_pEngine1 != nullptr)
	{
		delete m_pEngine1;
		m_pEngine1 = nullptr;
	}
	if (m_pEngine2 != nullptr)
	{
		delete m_pEngine2;
		m_pEngine2 = nullptr;
	}
	delete[] m_sMoveRecs;
	delete[] m_sMoveTimeRecs;
	delete[] m_fMoveWinRates;
	delete[] m_fStdMoveWinRates;
	delete[] m_OldMoveRecs;
	delete[] m_sOldMoveTimeRecs;
	delete[] m_fOldMoveWinRates;
	delete[] m_sAnaMoveRecs;
	delete[] m_iAnaMoveVisits;
	delete[] m_fAnaMoveWinRates;
	for (int i = 0; i < 100; i++)
	{
		delete[] m_sLifeDeathMovess[i];
		delete[] m_sLifeDeathMoveCommentss[i];
	}
	sgfFreeNode(m_Sgftree.root);
	sgfFreeNode(m_Sgftree1.root);
	sgftree_clear(&m_Sgftree);
	sgftree_clear(&m_Sgftree1);
}

void CSfcGoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADBLACK, m_bBlack);
	DDX_Control(pDX, IDC_CMBMB, m_cmbMb);
	DDX_CBIndex(pDX, IDC_CMBMB, m_iMb);
	DDX_Control(pDX, IDC_OUTPUT, m_eOutput);
	DDX_Text(pDX, IDC_OUTPUT, m_strOutput);
	DDX_Control(pDX, IDC_BTNBZ, btnBz);
	DDX_Control(pDX, IDC_BTNANA, m_btnAna);
	DDX_Control(pDX, IDC_RADBLACK, m_radBlack);
	DDX_Control(pDX, IDC_BTNEXIT, m_btnExit);
	DDX_Control(pDX, IDC_BTNSCORE, m_btnScore);
	DDX_Control(pDX, IDC_RADWHITE, m_radWhite);
	DDX_Control(pDX, IDC_RADINTURN, m_radInturn);
}

BOOL CSfcGoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	//cs.style |= WS_VISIBLE | WS_MAXIMIZE;
	return CFormView::PreCreateWindow(cs);
}

void CSfcGoView::OnInitialUpdate()
{
	/*time_t rawtime;
	tm lctime;
	time(&rawtime);
	localtime_s(&lctime, &rawtime);
	int yr = lctime.tm_year;
	yr = lctime.tm_mon;*/
	//GetParentFrame()->RecalcLayout();
	//ResizeParentToFit();
	//CString tmpstr;
	//tmpstr.Format("黑：%3.0f%%", 0.5234*100);
	/*CString strt = "B13\r";
	CString strt1 = strt.TrimRight();
	int a, b;
	Trans(strt1, a, b);*/

	//初始化GoInfo
	m_GoInfo.Init(19);
	
	m_iColor=2;

	m_bInTurn=false;

	m_iMb=0;
	for(int i=0;i<19;i++)
	{
		for(int j=0;j<19;j++)
			m_iBoard[i][j]=0;
	}
	m_iGoCount=0;
	m_iGoCountMax = 0;
	m_bRecall=false;
	m_iRecallStartId=0;
	m_iFixedStone = 0;
	//计算棋盘区域
	CRect rect;
	GetClientRect(rect);
	//画棋盘背景
	int x=rect.Height()/22,y=x,w=rect.Height()-2*x,h=w;
	//画棋盘线
	int edge=w/(m_iBoardSize+1);
	w = edge * (m_iBoardSize + 1);
	h = w;
	int leftedge = (rect.Width() - (w + edge * 10)) / 2;
	x = leftedge;
	//边框
	x+=edge;y+=edge;w-=2*edge;h=w;
	m_BoardRect.SetRect(x,y,x+w,y+h);
	m_iGap=edge;
	//if (m_iState == 1)
	//	return;
	//初始化gnugo引擎
	//set_random_seed(HASH_RANDOM_SEED);
	//reading_cache_init(128 * 1024 * 1024);
	//set_random_seed(time(NULL));
	//persistent_cache_init();
	//clear_board();

	//transformation_init();
	//dfa_match_init();
	//choose_mc_patterns(NULL);

	//clear_approxlib_cache();
	//clear_accuratelib_cache();


	//init_gnugo(1024,time(NULL));
	//mandated_depth=30;
	//初始化引擎
	m_iState = iState;
	if (iPlayer1 != 0)
		iLevel = iLevel1;
	else
		iLevel = iLevel2;
	if (iPlayer1 == 0)
		iLevel1 = iPlayerLevel;
	if (iPlayer2 == 0)
		iLevel2 = iPlayerLevel;
	//if (iPlayer1 == 0)
		m_sBlackName = sPlayerName;
	//if (iPlayer2 == 0)
		m_sWhiteName = sPlayerName;
	//if (iPlayer1 != 0 && iPlayer2 != 0)
	//	m_bEngineDual = true;
	if (m_iState == 1 || m_iState==3)//死活分析或序盘研究时，预加载引擎
	{
		int engineid = 0;
		CString sdir = strDirectry + "\\Engine\\" + sEngineAppDirs[engineid];
		m_pEngine1 = new SfcGtp();
		//m_pEngine1 = new SfcGtp();
		//m_pEngine->m_iType = iEngineTypes[engineid];
		m_pEngine1->m_AppName = sdir + "\\" + sEngineAppNames[engineid];
		m_pEngine1->m_AppDir = sdir;
		m_pEngine1->m_CmdLine = sdir + "\\" + sEngineAppNames[engineid] + " " + sEngineCmdLines[engineid];
		m_pEngine1->m_CmdLine1 = sdir + "\\" + sEngineAppNames[engineid] + " " + sEngineCmdLines1[engineid];
		m_pEngine1->m_Id = engineid;
		m_pEngine1->LoadEngine(1);
		iEngineId = 0;
		m_iComputerByoTime = 15;//分析15秒
		m_iComputerThinkTime = m_iComputerByoTime;
		m_iComputerByoStones = 1;
		iLevel = 23;//以最高级别进行死活分析
		SetLevel(iLevel);
		SetRule(iRule);
		SetBoardSize(m_iBoardSize);
		ClearBoard();
		SetHandicap(m_iHandiCap);
		SetKomi(m_fKomi);
		SetTimes(0, m_iComputerThinkTime, m_iComputerByoStones);
	}
	/*/return;
	m_pEngine1 = new SfcGtp();
	m_pEngine1->m_iType = 0;
	m_pEngine1->m_sEngineName = "KataGo";
	m_pEngine1->m_AppName = "E:\\Game\\KataGo\\katago.exe";
	m_pEngine1->m_AppDir = "E:\\Game\\KataGo";
	m_pEngine1->m_CmdLine = "E:\\Game\\KataGo\\katago.exe gtp -model kata1-b18c384nbt-s7709731328-d3715293823.bin.gz -config SfcGo.cfg";
	m_pEngine1->m_CmdLine1 = "E:\\Game\\KataGo\\katago.exe gtp -model kata1-b18c384nbt-s7709731328-d3715293823.bin.gz -config SfcGo_LifeDeth.cfg";
	m_pEngine1->LoadEngine(0);
	//CString str = "name\r\n";
	//m_pEngine1->WriteToPipe(str);
	//int count;
	//CString* strs = m_pEngine1->GetMsg(count);
	//Sleep(3000);
	//CHAR chBuf[8192];
	//DWORD dwRead;
	//m_pEngine1->ReadFromPipe(chBuf, dwRead);
	//chBuf[dwRead] = 0;
	//CString str = chBuf;
	//m_strOutput = str;
	SetBoardSize(m_iBoardSize);
	SetKomi(m_fKomi);
	//加载第二引擎
	m_pEngine2 = new SfcGtp();
	m_pEngine2->m_iType = 1;
	m_pEngine2->m_sEngineName = "Leela";
	m_pEngine2->m_AppName = "E:\\Game\\Leela\\leelaz.exe";
	m_pEngine2->m_AppDir = "E:\\Game\\Leela";
	m_pEngine2->m_CmdLine = "E:\\Game\\Leela\\leelaz.exe --gtp --noponder -w E:\\Game\\Leela\\networks\\weights.txt";
	m_pEngine2->m_CmdLine1 = "E:\\Game\\Leela\\leelaz.exe --gtp --noponder -w E:\\Game\\Leela\\networks\\best-network.txt";
	m_pEngine2->LoadEngine(1);
	//Sleep(3000);
	//m_pEngine2->ReadFromPipe(chBuf, dwRead);
	//str = chBuf;
	CString str = "name\r\n";
	SfcGtp* pengine;
	pengine = m_pEngine1;
	pengine->WriteToPipe(str);
	int count;
	CString* strs = pengine->GetMsg(count);
	pengine = m_pEngine2;
	pengine->WriteToPipe(str);
	strs = pengine->GetMsg(count);*/

	m_Gameinfo.handicap = 0;
	m_Gameinfo.to_move = BLACK;
	//sgftree_clear(&m_Gameinfo.game_record);
	//sgftree_clear(&m_Sgftree);
	//sgftree_clear(&m_Sgftree1);
	//GameinfoClear(&m_Gameinfo);

	/* Info relevant to the computer player. */
	m_Gameinfo.computer_player = WHITE; /* Make an assumption. */
	//resignation_allowed = 1;
	/*/test
	SetTimes(3600, 600, 5);
	int color = m_Gameinfo.to_move;
	m_iCcolor = color;
	iEngineId = 0;
	iEngineThreadState = 1;
	AfxBeginThread(GetEngineMove, this);
	Sleep(3000);
	m_pEngine1->WriteToPipe("stop\r\n");*/
	/*str.Format("komi %3.1f\r\n", fKomi);
	m_pEngine1->WriteToPipe(str);
	m_strOutput += str;
	int count;
	CString* strs = m_pEngine1->GetMsg(count);
	for (int i = 0; i < count; i++)
		m_strOutput += strs[i]+"\n";
	str.Format("boardsize %d\r\n", iBoardSize);
	m_pEngine1->WriteToPipe(str);
	m_strOutput += str;
	strs = m_pEngine1->GetMsg(count);
	for (int i = 0; i < count; i++)
		m_strOutput += strs[i]+"\n";*/
	//启用按钮
	if (m_iState == 1)
	{
		m_iStateSave = 0;
		m_iStateReopen = 0;
	}
	//禁用前进/后退按钮
	m_iStateGoBack = 3;
	m_iStateGoFirst = 3;
	m_iStateGoFiveBack = 3;
	m_iStateGoFiveForward = 3;
	m_iStateGoForward = 3;
	m_iStateGoLast = 3;
	sMsg = "腾飞围棋提示";
	if (iLanguage == 0)
		sMsg = "SfcGo Notify";
	sThinkMsg = "腾飞围棋正在思考......";
	if (iLanguage == 0)
		sThinkMsg = "SfcGo is thinking...";
	//关掉提示对话框
	if(iState==1 || iState==3)
		pDlgNotify->DestroyWindow();
	UpdateData(FALSE);
}


// CSfcGoView 诊断

#ifdef _DEBUG
void CSfcGoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSfcGoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSfcGoDoc* CSfcGoView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSfcGoDoc)));
	return (CSfcGoDoc*)m_pDocument;
}
#endif //_DEBUG


// CSfcGoView 消息处理程序


void CSfcGoView::OnMBoard13()
{
	if(iBoardSizeState!=1)
	{
		if(m_iState1>0)
		{
			CString msg = "不能在对局中更改棋盘大小！";
			if (iLanguage == 0)
				msg = "Can not change board size while playing!";
			MessageBox(msg,sMsg,MB_ICONMASK);
			return;
		}
		SetBoardSize(13);
		this->Invalidate();
	}
}


void CSfcGoView::OnUpdateMBoard13(CCmdUI *pCmdUI)
{
	if(iBoardSizeState==1)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
	pCmdUI->Enable(m_iState1==0);
}


void CSfcGoView::OnMBoard19()
{
	if(iBoardSizeState!=2)
	{
		if(m_iState1>0)
		{
			CString msg = "不能在对局中更改棋盘大小！";
			if (iLanguage == 0)
				msg = "Can not change board size while playing!";
			MessageBox(msg, sMsg, MB_ICONMASK);
			return;
		}
		SetBoardSize(19);
		this->Invalidate();
	}
}


void CSfcGoView::OnUpdateMBoard19(CCmdUI *pCmdUI)
{
	if(iBoardSizeState==2)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
	pCmdUI->Enable(m_iState1==0);
}




void CSfcGoView::OnMBoard9()
{
	if(iBoardSizeState!=0)
	{
		if(m_iState1>0)
		{
			CString msg = "不能在对局中更改棋盘大小！";
			if (iLanguage == 0)
				msg = "Can not change board size while playing!";
			MessageBox(msg, sMsg, MB_ICONMASK);
			return;
		}
		SetBoardSize(9);
		this->Invalidate();
	}
}


void CSfcGoView::OnUpdateMBoard9(CCmdUI *pCmdUI)
{
	if(iBoardSizeState==0)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
	pCmdUI->Enable(m_iState1==0);
}


void CSfcGoView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if (float(cx) / cy > 39.0 / 22)
	{
		m_bShowRecSize = true;
		m_bShowInfoSize = true;
	}
	else if (float(cx) / cy > 30.0 / 22)
	{
		m_bShowRecSize = false;
		m_bShowInfoSize = true;
	}
	else
	{
		m_bShowRecSize = false;
		m_bShowInfoSize = false;
	}
	/*int x, y, x1, x2, y1, y2, y3 = 0, y4 = 0, w, h;
	x1=cy/20;
	y1=x1;
	x2=cy;
	y2=10;
	w=cx-cy-10;
	h=cy-20;
	//CRect rt;
	//GetClientRect(rt);
	CWnd *pWnd;
	CRect rect,rt;
	pWnd=GetDlgItem(IDC_GRPPANEL);
	if(pWnd)
	{
		pWnd->GetWindowRect(rect);
		ScreenToClient(rect);
		pWnd->MoveWindow(x2,y2,w,h);
	}
	pWnd=GetDlgItem(IDC_RADBLACK);
	if(pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x=x2+(rt.left-rect.left);
		y=y2+(rt.top-rect.top);
		pWnd->MoveWindow(x,y,rt.right-rt.left,rt.bottom-rt.top);
	}
	pWnd=GetDlgItem(IDC_RADWHITE);
	if(pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x=x2+(rt.left-rect.left);
		y=y2+(rt.top-rect.top);
		pWnd->MoveWindow(x,y,rt.right-rt.left,rt.bottom-rt.top);
	}
	pWnd=GetDlgItem(IDC_RADINTURN);
	if(pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x=x2+(rt.left-rect.left);
		y=y2+(rt.top-rect.top);
		pWnd->MoveWindow(x,y,rt.right-rt.left,rt.bottom-rt.top);
	}
	pWnd=GetDlgItem(IDC_CMBMB);
	if(pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x=x2+(rt.left-rect.left);
		y=y2+(rt.top-rect.top);
		pWnd->MoveWindow(x,y,rt.right-rt.left,rt.bottom-rt.top);
	}
	pWnd=GetDlgItem(IDC_STAT);
	if(pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x=x2+(rt.left-rect.left);
		y3=cy-10-(rect.bottom-rt.bottom)-rt.Height();
		pWnd->MoveWindow(x,y3,rt.Width(),rt.Height());
	}
	pWnd=GetDlgItem(IDC_BTNBZ);
	if(pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x=x2+w/6-rt.Width()/2;
		//y4=cy-10-(rect.bottom-rt.bottom)-rt.Height();
		y4=cy-20-rt.Height();
		pWnd->MoveWindow(x,y4,rt.Width(),rt.Height());
	}
	pWnd=GetDlgItem(IDC_BTNANA);
	if(pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x=x2+w/3-rt.Width()/2;
		pWnd->MoveWindow(x,y4,rt.Width(),rt.Height());
	}
	pWnd=GetDlgItem(IDC_BTNEXIT);
	if(pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x=x2+w/2-rt.Width()/2;
		pWnd->MoveWindow(x,y4,rt.Width(),rt.Height());
	}
	pWnd = GetDlgItem(IDC_BTNSCORE);
	if (pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x = x2 + w*2 / 3 - rt.Width() / 2;
		pWnd->MoveWindow(x, y4, rt.Width(), rt.Height());
	}
	pWnd = GetDlgItem(IDC_BTNSUSPEND);
	if (pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x = x2 + w*5 / 6 - rt.Width() / 2;
		pWnd->MoveWindow(x, y4, rt.Width(), rt.Height());
	}
	pWnd=GetDlgItem(IDC_OUTPUT);
	if(pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x=x2+10;
		y=y2+(rt.top-rect.top);
		w=cx-cy-30;
		h=y3-10-y;
		pWnd->MoveWindow(x,y,w,h);
	}
	//计算棋盘区域
	GetClientRect(rect);
	//画棋盘背景
	x=rect.Height()/22,y=x,w=rect.Height()-2*x,h=w;
	//画棋盘线
	int edge=w/(m_iBoardSize+1);
	w = edge * (m_iBoardSize + 1);
	h = w;
	int leftedge = (rect.Width() - (w + edge * 10)) / 2;
	x = leftedge;
	//边框
	x+=edge;y+=edge;w-=2*edge;h=w;
	m_BoardRect.SetRect(x,y,x+w,y+h);
	m_iGap=edge;*/
}


void CSfcGoView::OnBnClickedBtnbz()
{
	//m_hBlackCursor = AfxGetApp()->LoadCursorA(IDC_CURSOR1);
	//m_hBlackCursor = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
	//SetCursor(m_hBlackCursor);
	if(m_iState==1)//死活分析
	{
		m_iMaxSizePos=-1;
		if(m_iState1==0)
		{
			ClearBoard();
			m_iState1=1;
			m_sOutputInfo = "正在摆子";
			InvalidateRect(m_rOutputInfo);
			SetDlgItemText(IDC_STAT,"正在摆子");
			btnBz.SetWindowTextA("清  盘");
		}
		else
		{
			ClearBoard();
			//SGFTree tree;
			sgftree_clear(&m_Sgftree);
			CString filename=strDirectry;
			filename+="\\Life-death\\sh.sgf";
			char *fpname=filename.GetBuffer(filename.GetLength());
			filename.ReleaseBuffer();
			//strcpy_s(fpname,filename.GetLength(),filename);
			sgftree_readfile(&m_Sgftree,fpname);
			SgfToGoRecord(&m_Sgftree,m_iGoCount,m_GoRecord,m_iFixedStone);
			for(int i=0;i<m_iFixedStone;i++)
				m_iBoard[m_GoRecord[i].x][m_GoRecord[i].y]=m_GoRecord[i].color;
			SgfToGoRecord(&m_Sgftree,m_GoInfo.gocount,m_GoInfo.gorecord,m_GoInfo.fixedstone);
			for(int i=0;i<m_GoInfo.fixedstone;i++)
				Sfc::AddStone(m_GoInfo.gorecord[i].x,m_GoInfo.gorecord[i].y,m_GoInfo.gorecord[i].color,m_GoInfo);
			//sgfFreeNode(tree.root);
			//将sgf文件内容装入引擎
			/*CString str = "loadsgf ";
			str += filename;
			str += "\r\n";
			m_pEngine1->WriteToPipe(str);
			m_strOutput += str;
			int count;
			CString* strs = m_pEngine1->GetMsg(count);
			for (int i = 0; i < count; i++)
				m_strOutput += strs[i] + "\n";*/
			PaintBoard();
			/*ClearBoard();
			m_iState1=0;
			SetDlgItemText(IDC_STAT,"就绪");
			btnBz.SetWindowTextA("摆  子");
			PaintBoard();*/
		}
	}
	else if(m_iState==2)//人机对弈
	{
		if(m_iState1==0)//初始化，开始对弈
		{
			m_hBlackCursor = (HCURSOR)LoadImage(NULL, strSysDirectry + "\\blackstone.ico", IMAGE_ICON, m_iGap+4, m_iGap+4, LR_LOADFROMFILE);
			m_hWhiteCursor = (HCURSOR)LoadImage(NULL, strSysDirectry + "\\whitestone.ico", IMAGE_ICON, m_iGap+4, m_iGap+4, LR_LOADFROMFILE);
			iRandomSeed = unsigned int(time(NULL));
			bLife_death=0;
			m_cmbMb.EnableWindow(FALSE);
			m_iState1=1;
			//m_iColor=2;
			//sgftree_clear(&m_Sgftree);
			//GameinfoClear(&m_Gameinfo);
			/* Initialize and empty sgf tree if there was no infile. */
			//sgftreeCreateHeaderNode(&m_Sgftree, iBoardSize, m_fKomi, m_iHandiCap);
			CreateSgfHead(&m_Sgftree, iBoardSize, m_fKomi, m_iHandiCap);

			/* Set the game_record to be identical to the loaded one or the
			* newly created empty sgf tree.
			*/
			m_Gameinfo.game_record = m_Sgftree;
			SetDlgItemText(IDC_STAT,"对弈中");
			btnBz.SetWindowTextA("PASS");
			m_btnExit.SetWindowTextA("认  输");
			m_Gameinfo.computer_player=OTHER_COLOR(m_iColor);
			strcpy_s(m_OutFileName,"recordtest.sgf");
			//SetHandicap(m_iMb);
			//if(m_iMb>0)
			//	SetKomi(0);
			//m_iGoCount=0;
			//PaintBoard();
			if (m_Gameinfo.computer_player == m_Gameinfo.to_move)
			{
				m_bPicked = true;
				ComputerMove();
			}
			else
			{
				m_bPicked = false;
			}
		}
		else if(m_iState1==1)//PASS一手
		{
			DoPass();
			if(m_iPasses>=2)//两次PASS，对弈结束
			{
				m_iPasses = 0;
				//ascii_endgame(&m_Gameinfo,0);
				m_iState1=0;
				//m_iColor=0;
				m_cmbMb.EnableWindow(TRUE);
				SetDlgItemText(IDC_STAT,"就绪");
				btnBz.SetWindowTextA("开始对弈");
				m_btnExit.SetWindowTextA("退  出");
			}
		}
	}
}


void CSfcGoView::OnBnClickedBtnana()
{
	/*return;
	m_GoInfo.boardsize=9;
	Sfc::PlayStone(4,4,2,m_GoInfo);
	Sfc::PlayStone(6,2,1,m_GoInfo);
	Sfc::PlayStone(7,2,2,m_GoInfo);
	Sfc::PlayStone(7,3,1,m_GoInfo);
	Sfc::PlayStone(8,3,2,m_GoInfo);
	Sfc::PlayStone(7,4,1,m_GoInfo);
	Sfc::PlayStone(6,3,2,m_GoInfo);
	Sfc::PlayStone(6,1,1,m_GoInfo);
	Sfc::PlayStone(7,5,2,m_GoInfo);
	Sfc::PlayStone(8,4,1,m_GoInfo);
	Sfc::PlayStone(6,4,2,m_GoInfo);
	Sfc::PlayStone(8,2,1,m_GoInfo);
	Sfc::PlayStone(7,1,2,m_GoInfo);
	Sfc::PlayStone(6,1,1,m_GoInfo);
	Sfc::PlayStone(8,2,2,m_GoInfo);
	Sfc::PlayStone(7,4,1,m_GoInfo);
	Sfc::PlayStone(6,2,2,m_GoInfo);*/
	if (m_iState == 1 && m_iState1 == 1)
	{
		//sgftreeCreateHeaderNode(&m_Sgftree, iBoardSize, m_fKomi, m_iHandiCap);

		/* Set the game_record to be identical to the loaded one or the
		* newly created empty sgf tree.
		*/
		//保存盘面至文件
		CString filename = strDirectry;
		filename += "\\Life-death\\sh.sgf";
		char* tmpstring = filename.GetBuffer();
		if (tmpstring) {
			/* discard newline */
			//tmpstring[strlen(tmpstring) - 1] = 0;
			//InitSgf(ginfo);
			writesgf(m_Sgftree.root, tmpstring);
		}
		//将sgf文件内容装入引擎
		CString str = "loadsgf ";
		str += filename;
		str += "\r\n";
		m_pEngine1->WriteToPipe(str);
		m_strOutput += str;
		int count;
		CString* strs = m_pEngine1->GetMsg(count);
		for (int i = 0; i < count; i++)
			m_strOutput += strs[i] + "\n";
		m_Gameinfo.game_record = m_Sgftree;
		SetDlgItemText(IDC_STAT, "对弈中");
		btnBz.SetWindowTextA("PASS");
		m_btnExit.SetWindowTextA("认  输");
		if (m_iMb == 0)
			m_iColor = 2;
		else
			m_iColor = 1;
		m_Gameinfo.computer_player = m_iColor;
		m_Gameinfo.to_move = m_iColor;
		m_iColor = OTHER_COLOR(m_iColor);
		strcpy_s(m_OutFileName, "recordtest.sgf");
		m_iFixedStone = m_iGoCount;
		ComputerMove();
	}
	else if(m_iState==2 && m_iState1==1)//人机对弈,悔棋
	{
		int num=min(2,m_iGoCount-m_iHandiCap);
		if (num>0) {
			for (int i = 0; i < num; i++)
			{
				CString str = "undo\r\n";
				m_pEngine1->WriteToPipe(str);
				m_strOutput += str;
				int count;
				CString* strs = m_pEngine1->GetMsg(count);
				for (int i = 0; i < count; i++)
					m_strOutput += strs[i] + "\n";
			}
			sgftreeAddComment(&m_Sgftree, "undone");
			sgftreeBack(&m_Sgftree);
			//m_Gameinfo.to_move = OTHER_COLOR(m_Gameinfo.to_move);
			m_iGoCount-=num;
			m_GoInfo.Init(m_iBoardSize);
			for (int j = 0; j < m_iGoCount; j++)
				Sfc::PlayStone(m_GoRecord[j].x, m_GoRecord[j].y, m_GoRecord[j].color, m_GoInfo);
			for (int j = 0; j < m_iBoardSize; j++)
				for (int k = 0; k < m_iBoardSize; k++)
					m_iBoard[j][k] = m_GoInfo.board[j][k];
			//CopyBoard();
			PaintBoard();
		}
		else
			MessageBox("悔棋失败！");
	}
}


void CSfcGoView::OnBnClickedBtnexit()
{
	if(m_iState==2 && m_iState1==1)//认输
	{
		EndGame(&m_Gameinfo,1);
		m_iState1=0;
		//m_iColor=0;
		m_cmbMb.EnableWindow(TRUE);
		SetDlgItemText(IDC_STAT,"就绪");
		btnBz.SetWindowTextA("开始对弈");
		m_btnExit.SetWindowTextA("退  出");
	}
	else
		GetParentFrame()->SendMessage(WM_CLOSE);
}

void CSfcGoView::PaintMoveRec()
{
	CDC* pDC = GetDC();
	pDC->SetStretchBltMode(HALFTONE);
	CString s = "玩家胜率";
	if (iLanguage == 0)
		s = "Player win rate";
	if (m_bSelfPlay || m_bEngineDual || m_iState == 3)
	{
		s = "双方胜率";
		if (iLanguage == 0)
			s = "Both sides win rates";
	}
	CSize size = pDC->GetTextExtent(s);
	int x, y, w, h, h1, w1, x1, y1;
	int edge = m_rBoardBack.Width() / (m_iBoardSize + 1);
	w = 8 * edge;
	x = m_rBoardBack.left - edge - w;
	y = m_rBoardBack.top;
	h = m_rBoardBack.Height();
	h1 = max(w / 16, size.cy);
	m_iMoveRecHeight = h1;
	CRect inforect(x, y, x + w, y + h);
	//胜率图表标题
	if(bShowWinRate && m_iState!=1)
		imProgressBar.Draw(pDC->m_hDC, x, y, w, h1);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(186, 186, 186));
	int edge1 = (h1 - size.cy) / 2;
	x1 = x + (w - size.cx) / 2;
	y1 = y + edge1;
	if(bShowWinRate && m_iState!=1)
		pDC->TextOutA(x1, y1, s);
	//胜率图表
	y += h1;
	h = edge * 4-4;
	m_rWinRateChart.SetRect(x, y, x + w, y + h);
	if(bShowWinRate && m_iState!=1)
		imChart.Draw(pDC->m_hDC, m_rWinRateChart);
	m_rPanel.SetRect(x, y - h1, x + w, y + h);
	//分析着手
	y += 2;
	y += h;
	h = w / 2;
	if(bShowAna)
		imRecDesk.Draw(pDC->GetSafeHdc(), x, y, w, h);
	w1 = (w - 8) / 3;
	//分析记录标题
	//imRecTitle.Draw(pDC->GetSafeHdc(), x, y, w, h1);
	if (m_iState == 1 && m_iState1 == 6 && !m_bAnaed)//显示死活题答案
	{
		s = "招式";
		if (iLanguage == 0)
			s = "Move";
		x1 = x + 4;
		y1 = y + edge1;
		if (bShowAna)
			pDC->TextOutA(x1, y1, s);
		s = "结果";
		if (iLanguage == 0)
			s = "Result";
		x1 = x + w1;
		if (bShowAna)
			pDC->TextOutA(x1, y1, s);
	}
	else
	{
		s = "候选招数";
		if (iLanguage == 0)
			s = "Move";
		x1 = x + 4;
		y1 = y + edge1;
		if (bShowAna)
			pDC->TextOutA(x1, y1, s);
		s = "访问节点";
		if (iLanguage == 0)
			s = "Visits";
		x1 = x + w1;
		if (bShowAna)
			pDC->TextOutA(x1, y1, s);
		s = "分值";
		if (iLanguage == 0)
			s = "Score";
		x1 += w1;
		size = pDC->GetTextExtent("0");
		x1 += size.cx;
		if (bShowAna)
			pDC->TextOutA(x1, y1, s);
	}


	m_rAnaMove.SetRect(x, y + h1, x + w, y + h);
	//着手记录
	y += h;
	y += 2;
	h = m_rBoardBack.bottom - y+2;
	if(bShowMoveRec)
		imRecDesk.Draw(pDC->GetSafeHdc(), x,y,w,h);
	//着手记录标题
	//imRecTitle.Draw(pDC->GetSafeHdc(), x, y, w, h1);
	s = "棋步";
	if (iLanguage == 0)
		s = "Move";
	x1 = x + 4;
	y1 = y + edge1;
	if (bShowMoveRec)
		pDC->TextOutA(x1, y1, s);
	s = "时间";
	if (iLanguage == 0)
		s = "Time";
	x1 = x + w1;
	if (bShowMoveRec)
		pDC->TextOutA(x1, y1, s);
	s = "分值";
	if (iLanguage == 0)
		s = "Score";
	x1 += w1;
	x1 += size.cx;
	if (bShowMoveRec)
		pDC->TextOutA(x1, y1, s);
	m_rMoveRec.SetRect(x, y+h1, x + w, y + h-h1-2);
	
	//开始画分析记录
	pDC->SetTextColor(RGB(50, 50, 50));
	x = m_rAnaMove.left;
	//int n = min(6, m_rAnaMove.Height() / size.cy);
	int n = m_rAnaMove.Height() / m_iMoveRecHeight;
	if (bShowAna)
	{
		for (int i = 0; i < n && i + m_iAnaMoveStartId < m_iAnaMoveCount; i++)
		{
			y = m_rAnaMove.top + h1 * i;
			if (i + m_iAnaMoveStartId == m_iAnaMoveId)
				imRecSelected.Draw(pDC->GetSafeHdc(), x, y, w, h1);
			else
				imRec.Draw(pDC->GetSafeHdc(), x, y, w, h1);
			x1 = x + 4;
			y1 = y + edge1;
			s = m_sAnaMoveRecs[i + m_iAnaMoveStartId];
			pDC->TextOutA(x1, y1, s);
			if (m_iState == 1 && m_iState1 == 6 && !m_bAnaed)//显示死活题答案
			{
				s = m_sLifeDeathMoveCommentss[i + m_iAnaMoveStartId][m_iLifeDeathMoveCounts[i + m_iAnaMoveStartId] - 1];
				x1 = x + w1;
				pDC->TextOutA(x1, y1, s);
			}
			else
			{
				s.Format("%d", m_iAnaMoveVisits[i + m_iAnaMoveStartId]);
				x1 = x + w1;
				pDC->TextOutA(x1, y1, s);
				s.Format("%6.2f", m_fAnaMoveWinRates[i + m_iAnaMoveStartId] * 100);
				x1 += w1;
				pDC->TextOutA(x1, y1, s);
			}
		}
	}
	//画着手记录
	//n = min(22, m_rMoveRec.Height() / size.cy);
	n = m_rMoveRec.Height() / m_iMoveRecHeight;
	int m = max(m_iMoveCount - n, 0);
	if (bShowMoveRec)
	{
		for (int i = m; i < m_iMoveCount; i++)
		{
			y = m_rMoveRec.top + h1 * (i - m);
			imRec.Draw(pDC->GetSafeHdc(), x, y, w, h1);
			x1 = x + 4;
			y1 = y + edge1;
			s = m_sMoveRecs[i];
			pDC->TextOutA(x1, y1, s);
			int color = BLACK;
			if (s.Left(1) == "W")
				color = WHITE;
			s = m_sMoveTimeRecs[i];
			x1 = x + w1;
			pDC->TextOutA(x1, y1, s);
			if (m_fMoveWinRates[i] >= 0)
			{
				if (m_bSelfPlay || m_bEngineDual || color == m_Gameinfo.computer_player || m_iState==3)
					s.Format("%6.2f", m_fMoveWinRates[i] * 100);
				else
					s = "  -";
				x1 += w1;
				pDC->TextOutA(x1, y1, s);
			}
		}
	}
	//画胜率图表
	if (bShowWinRate && m_iState!=1 && m_iMoveCount > 2)
	{
		x = m_rWinRateChart.left + 2;
		y = m_rWinRateChart.top + 2;
		h = m_rWinRateChart.Height() - 4;
		w = m_rWinRateChart.Width() - 4;
		n = m_iMoveCount / 10 * 10 + 10;
		n /= 2;
		float w2 = float(w) / n;
		m = 0;
		//m = max(m_iMoveCount - n * 2, 0);
		//if (m_GoRecord[m].color != m_iFirstColor)
		//	m++;
		CPen redPen;
		redPen.CreatePen(PS_SOLID, 2, RGB(200, 0, 0));
		CPen bluePen;
		bluePen.CreatePen(PS_SOLID, 2, RGB(0, 0, 200));
		CPen greenPen;
		greenPen.CreatePen(PS_SOLID, 2, RGB(0, 200, 0));
		//先着方胜率曲线
		if (m_bSelfPlay || m_bEngineDual || m_iFirstColor == m_Gameinfo.computer_player || m_iState==3)
		{
			m_iFirstColor == BLACK ? pDC->SelectObject(&bluePen) : pDC->SelectObject(redPen);
			x1 = x;
			if(m_bSelfPlay || m_bEngineDual || m_iState == 3)
				y1 = y + (1 - m_fMoveWinRates[m]) * h;
			else
				y1 = y + m_fMoveWinRates[m] * h;
			pDC->MoveTo(x1, y1);
			for (int i = m + 2; i < m_iMoveCount; i+=2)
			{
				float rate = m_fMoveWinRates[i];
				//对玩家胜率在不同阶段以不同颜色表示
				if (!m_bSelfPlay && !m_bEngineDual && m_iState != 3)
				{
					float rate0 = 1 - m_fMoveWinRates[i - 2];
					rate = 1 - rate;
					x1 = x + w2 * i / 2;
					y1 = y + (1 - rate) * h;
					if (rate0 >= 0.6)
					{
						pDC->SelectObject(&bluePen);
						if (rate < 0.6)
						{
							int x2 = x + w2 * (i - 2) / 2 + (rate0 - 0.6) / (rate0 - rate) * w2 / 2;
							int y2 = y + (1 - 0.6) * h;
							pDC->LineTo(x2, y2);
							pDC->SelectObject(&greenPen);
						}
						if (rate <= 0.4)
						{
							int x2 = x + w2 * (i - 2) / 2 + (rate0 - 0.4) / (rate0 - rate) * w2 / 2;
							int y2 = y + (1 - 0.4) * h;
							pDC->LineTo(x2, y2);
							pDC->SelectObject(&redPen);
						}
					}
					else if (rate0 <= 0.4)
					{
						pDC->SelectObject(&redPen);
						if (rate > 0.4)
						{
							int x2 = x + w2 * (i - 2) / 2 + (0.4-rate0) / (rate-rate0) * w2;
							int y2 = y + (1 - 0.4) * h;
							pDC->LineTo(x2, y2);
							pDC->SelectObject(&greenPen);
						}
						if (rate >= 0.6)
						{
							int x2 = x + w2 * (i - 2) / 2 + (0.6-rate0) / (rate-rate0) * w2;
							int y2 = y + (1 - 0.6) * h;
							pDC->LineTo(x2, y2);
							pDC->SelectObject(&bluePen);
						}
					}
					else
					{
						pDC->SelectObject(&greenPen);
						if (rate >= 0.6)
						{
							int x2 = x + w2 * (i - 2) / 2 + (0.6 - rate0) / (rate - rate0) * w2 / 2;
							int y2 = y + (1 - 0.6) * h;
							pDC->LineTo(x2, y2);
							pDC->SelectObject(&bluePen);
						}
						if (rate <= 0.4)
						{
							int x2 = x + w2 * (i - 2) / 2 + (rate0 - 0.4) / (rate0 - rate) * w2 / 2;
							int y2 = y + (1 - 0.4) * h;
							pDC->LineTo(x2, y2);
							pDC->SelectObject(&redPen);
						}
					}
					/*if (rate >= 0.6)
						pDC->SelectObject(&bluePen);
					else if (rate <= 0.4)
						pDC->SelectObject(&redPen);
					else
						pDC->SelectObject(&greenPen);*/
					pDC->LineTo(x1, y1);
				}
				else
				{
					x1 = x + w2 * i / 2;
					y1 = y + (1 - rate) * h;
					pDC->LineTo(x1, y1);
				}
			}
		}
		//后着方胜率曲线
		if (m_bSelfPlay || m_bEngineDual || m_iFirstColor != m_Gameinfo.computer_player || m_iState == 3)
		{
			m_iFirstColor == WHITE ? pDC->SelectObject(&bluePen) : pDC->SelectObject(redPen);
			x1 = x;
			if (m_bSelfPlay || m_bEngineDual || m_iState == 3)
				y1 = y + (1 - m_fMoveWinRates[m + 1]) * h;
			else
				y1 = y + m_fMoveWinRates[m + 1] * h;
			pDC->MoveTo(x1, y1);
			for (int i = m + 3; i < m_iMoveCount; i+=2)
			{
				float rate = m_fMoveWinRates[i];
				//对玩家胜率在不同阶段以不同颜色表示
				if (!m_bSelfPlay && !m_bEngineDual && m_iState != 3)
				{
					float rate0 = 1 - m_fMoveWinRates[i - 2];
					rate = 1 - rate;
					x1 = x + w2 * i / 2;
					y1 = y + (1 - rate) * h;
					if (rate0 >= 0.6)
					{
						pDC->SelectObject(&bluePen);
						if (rate < 0.6)
						{
							int x2 = x + w2 * (i - 2) / 2 + (rate0 - 0.6) / (rate0 - rate) * w2 / 2;
							int y2 = y + (1 - 0.6) * h;
							pDC->LineTo(x2, y2);
							pDC->SelectObject(&greenPen);
						}
						if (rate <= 0.4)
						{
							int x2 = x + w2 * (i - 2) / 2 + (rate0 - 0.4) / (rate0 - rate) * w2 / 2;
							int y2 = y + (1 - 0.4) * h;
							pDC->LineTo(x2, y2);
							pDC->SelectObject(&redPen);
						}
					}
					else if (rate0 <= 0.4)
					{
						pDC->SelectObject(&redPen);
						if (rate > 0.4)
						{
							int x2 = x + w2 * (i - 2) / 2 + (0.4 - rate0) / (rate - rate0) * w2;
							int y2 = y + (1 - 0.4) * h;
							pDC->LineTo(x2, y2);
							pDC->SelectObject(&greenPen);
						}
						if (rate >= 0.6)
						{
							int x2 = x + w2 * (i - 2) / 2 + (0.6 - rate0) / (rate - rate0) * w2;
							int y2 = y + (1 - 0.6) * h;
							pDC->LineTo(x2, y2);
							pDC->SelectObject(&bluePen);
						}
					}
					else
					{
						pDC->SelectObject(&greenPen);
						if (rate >= 0.6)
						{
							int x2 = x + w2 * (i - 2) / 2 + (0.6 - rate0) / (rate - rate0) * w2 / 2;
							int y2 = y + (1 - 0.6) * h;
							pDC->LineTo(x2, y2);
							pDC->SelectObject(&bluePen);
						}
						if (rate <= 0.4)
						{
							int x2 = x + w2 * (i - 2) / 2 + (rate0 - 0.4) / (rate0 - rate) * w2 / 2;
							int y2 = y + (1 - 0.4) * h;
							pDC->LineTo(x2, y2);
							pDC->SelectObject(&redPen);
						}
					}
					/*if (rate >= 0.6)
						pDC->SelectObject(&bluePen);
					else if (rate <= 0.4)
						pDC->SelectObject(&redPen);
					else
						pDC->SelectObject(&greenPen);*/
					pDC->LineTo(x1, y1);
				}
				else
				{
					x1 = x + w2 * i / 2;
					y1 = y + (1 - rate) * h;
					pDC->LineTo(x1, y1);
				}
			}
		}
		redPen.DeleteObject();
		bluePen.DeleteObject();
		greenPen.DeleteObject();
	}
	ReleaseDC(pDC);
}

void CSfcGoView::PaintInfo()
{
	int x, y, w, h;
	/*CRect rect, rt;
	GetClientRect(rect);
	//棋盘背景区
	x = rect.Height() / 22, y = x, w = rect.Height() - 2 * x;
	int edge = w / (m_iBoardSize + 1);
	w = edge * (m_iBoardSize + 1);
	h = w;
	int leftedge = (rect.Width() - (w + edge * 10)) / 2;
	x = leftedge;*/
	//信息区
	int edge = m_rBoardBack.Width() / (m_iBoardSize + 1);
	x = m_rBoardBack.right + edge;
	y = m_rBoardBack.top;
	//x += w + edge;
	w = 8 * edge;// 9 * edge;
	h = m_rBoardBack.Height();
	CRect inforect(x, y, x + w, y + h);
	//画黑白棋信息
	CDC* pDC = GetDC();
	pDC->SetStretchBltMode(HALFTONE);
	w = 3.8 * edge;// 4 * edge;
	m_rBlackInfo.SetRect(x, y, x + w, y + w);
	imBlackInfo.Draw(pDC->GetSafeHdc(), x, y, w, w);
	//imBlackInfo.Draw(pDC->m_hDC, x, y, w, w);
	x += 4.2 * edge;// 5 * edge;
	m_rWhiteInfo.SetRect(x, y, x + w, y + w);
	imWhiteInfo.Draw(pDC->GetSafeHdc(), x, y, w, w);
	//imWhiteInfo.Draw(pDC->m_hDC, x, y, w, w);
	//pDC->SetStretchBltMode(HALFTONE);
	//画进度条
	w = inforect.Width();
	h = w / 7.7;
	y += edge * 3.5;
	x = inforect.left;
	m_rProgressBar.SetRect(x, y, x + w, y + h);
	imProgressBar.Draw(pDC->GetSafeHdc(), x, y, w, h);
	//画游戏信息
	y += h;
	h = w / 2.8;
	m_rPlayInfo.SetRect(x, y, x + w, y + h);
	imPlayInfo.Draw(pDC->GetSafeHdc(), x, y, w, h);
	//画工具箱
	y += h + 2;
	h = inforect.bottom - y;
	m_rToolBox.SetRect(x, y, x + w, y + h);
	imToolBox.Draw(pDC->GetSafeHdc(), m_rToolBox);
	//画新对局/PASS按钮
	x += 2;
	y += 6;
	w -= 4;
	h = (h - 12) / 7;
	m_rNew.SetRect(x, y, x + w, y + h);
	PaintButton(0);
	//画黑先按钮
	m_rBlackFirst.SetRect(x, y, x + w / 2, y + h);
	PaintButton(20);
	//画白先按钮
	m_rWhiteFirst.SetRect(x + w / 2, y, x + w, y + h);
	PaintButton(21);
	//画打开棋谱/悔棋按钮
	y += h;
	m_rOpen.SetRect(x, y, x + w, y + h);
	PaintButton(1);
	//画保存棋谱/支招按钮
	y += h;
	m_rSave.SetRect(x, y, x + w, y + h);
	PaintButton(2);
	//画暂停/继续棋局按钮
	y += h;
	m_rReopen.SetRect(x, y, x + w, y + h);
	PaintButton(3);
	//画手筋练习按钮
	int w1 = w * 3 / 4, h1 = h * 3 / 4;
	int x1 = m_rBoardBack.right - 2*w, y1 = y - h;
	m_rTesuji.SetRect(x1, y1, x1 + w1, y1 + h1);
	PaintButton(16);
	//初级死活按钮
	x1 += w;
	m_rElementary.SetRect(x1, y1, x1 + w1, y1 + h1);
	PaintButton(17);
	//中级死活按钮
	x1 -= w;
	y1 = y + h / 2;
	m_rMiddle.SetRect(x1, y1, x1 + w1, y1 + h1);
	PaintButton(18);
	//高级死活按钮
	x1 += w;
	m_rAdvanced.SetRect(x1, y1, x1 + w1, y1 + h1);
	PaintButton(19);
	//画形势判断按钮
	y += h;
	m_rArea.SetRect(x, y, x + w, y + h);
	PaintButton(4);
	//画退出/交换对局按钮
	y += h;
	m_rExit.SetRect(x, y, x + w, y + h);
	PaintButton(5);
	//画认输按钮
	y += h;
	m_rResign.SetRect(x, y, x + w, y + h);
	//画摆放黑子按钮
	m_rPutBlack.SetRect(x, y, x + w / 2, y + h);
	PaintButton(22);
	//画摆放白子按钮
	m_rPutWhite.SetRect(x + w / 2, y, x + w, y + h);
	PaintButton(23);
	//画回到最初按钮
	w1 = w / 6;
	m_rGoFirst.SetRect(x, y, x + w1, y + h);
	//画后退五步按钮
	x += w1;
	m_rGoFiveBack.SetRect(x, y, x + w1, y + h);
	//画后退按钮
	x += w1;
	m_rGoBack.SetRect(x, y, x + w1, y + h);
	//画前进按钮
	x += w1;
	m_rGoForward.SetRect(x, y, x + w1, y + h);
	//画前进五步按钮
	x += w1;
	m_rGoFiveForward.SetRect(x, y, x + w1, y + h);
	//画前进到底按钮
	x += w1;
	m_rGoLast.SetRect(x, y, x + w1, y + h);
	if(m_iState==2 && m_iState1>0 && m_iState1!=3)
		PaintButton(6);
	else if (m_iState1 == 11)
	{
		PaintButton(22);
		PaintButton(23);
	}
	else
	{
		PaintButton(10);
		PaintButton(11);
		PaintButton(12);
		PaintButton(13);
		PaintButton(14);
		PaintButton(15);
	}
	//输出黑棋即时信息
	pDC->SetTextColor(RGB(186, 186, 186));
	pDC->SetBkMode(TRANSPARENT);
	CString s=m_sBlackName;
	CString slv = GetLevelTitle(iLevel1);
	if (iPlayer1 == 1)
	{
		if (m_bEngineDual)
		{
			int id = iEngine1;
			if (m_pEngine1 != nullptr && m_pEngine2 != nullptr)
			{
				if (iBlackEngineId == 0)
					id = m_pEngine1->m_Id;
				else
					id = m_pEngine2->m_Id;
			}
			s = sEngineNames[id] + slv;
		}
		else
		{
			s = "腾飞围棋" + slv;
			if (iLanguage == 0)
				s = "SfcGo" + slv;
		}
	}
	else
		s += slv;
	CSize size = pDC->GetTextExtent(s);
	x = (m_rBlackInfo.left+m_rBlackInfo.right)/2-size.cx/2;
	y = m_rBlackInfo.top + edge;
	pDC->TextOutA(x, y, s);
	s.Format("提子数量%3d", m_GoInfo.whitecaptured);
	if (iLanguage == 0)
		s.Format("Captured%3d", m_GoInfo.whitecaptured);
	size = pDC->GetTextExtent(s);
	x = (m_rBlackInfo.left + m_rBlackInfo.right) / 2 - size.cx / 2;
	y += edge / 2;
	pDC->TextOutA(x, y, s);
	s = "用时";
	if (iLanguage == 0)
		s = "Time used ";
	x = m_rBlackInfo.left + edge / 2;
	y += edge / 2;
	pDC->TextOutA(x, y, s);
	s = "00:00:00";
	size = pDC->GetTextExtent(s);
	s.Format("%02d:%02d:%02d", m_BlackTime.GetHours(), m_BlackTime.GetMinutes(), m_BlackTime.GetSeconds());
	x = m_rBlackInfo.right - edge / 2 - size.cx;
	m_rBlackTime.SetRect(x, y, x + size.cx, y + size.cy);
	pDC->TextOutA(x, y, s);
	//输出白棋即时信息
	pDC->SetTextColor(RGB(0, 0, 0));
	slv = GetLevelTitle(iLevel2);
	s = "腾飞围棋" + slv;
	if (iLanguage == 0)
		s = "SfcGo" + slv;
	if (iPlayer2 == 0)
		s = m_sWhiteName + slv;
	else if (m_bEngineDual)
	{
		int id = iEngine2;
		if (m_pEngine1 != nullptr && m_pEngine2 != nullptr)
		{
			if (iWhiteEngineId == 0)
				id = m_pEngine1->m_Id;
			else
				id = m_pEngine2->m_Id;
		}
		s = sEngineNames[id] + slv;
	}
	size = pDC->GetTextExtent(s);
	x = (m_rWhiteInfo.left + m_rWhiteInfo.right) / 2 - size.cx / 2;
	y = m_rWhiteInfo.top + edge;
	pDC->TextOutA(x, y, s);
	s.Format("提子数量%3d", m_GoInfo.blackcaptured);
	if (iLanguage == 0)
		s.Format("Captured%3d", m_GoInfo.blackcaptured);
	size = pDC->GetTextExtent(s);
	x = (m_rWhiteInfo.left + m_rWhiteInfo.right) / 2 - size.cx / 2;
	y += edge / 2;
	pDC->TextOutA(x, y, s);
	s = "用时";
	if (iLanguage == 0)
		s = "Time used ";
	x = m_rWhiteInfo.left + edge / 2;
	y += edge / 2;
	pDC->TextOutA(x, y, s);
	s = "00:00:00";
	size = pDC->GetTextExtent(s);
	s.Format("%02d:%02d:%02d", m_WhiteTime.GetHours(), m_WhiteTime.GetMinutes(), m_WhiteTime.GetSeconds());
	x = m_rWhiteInfo.right - edge / 2 - size.cx;
	m_rWhiteTime.SetRect(x, y, x + size.cx, y + size.cy);
	pDC->TextOutA(x, y, s);
	//进度条
	if (bThinkProgress && m_iProgress>0)
	{
		w = m_rProgressBar.Width() * m_iProgress / 100.0;
		CBrush blueBrush;
		blueBrush.CreateSolidBrush(RGB(0, 0, 200));
		pDC->SelectObject(blueBrush);
		pDC->Rectangle(m_rProgressBar.left, m_rProgressBar.top, m_rProgressBar.left + w, m_rProgressBar.bottom);
	}
	//单步用时
	pDC->SetTextColor(RGB(186, 186, 186));
	s = "单步用时 00:00:00";
	if (iLanguage == 0)
		s = "Period time 00:00:00";
	size = pDC->GetTextExtent(s);
	x = m_rProgressBar.left + (m_rProgressBar.Width() - size.cx) / 2;
	int edge1 = (m_rProgressBar.bottom - m_rProgressBar.top - size.cy) / 2;
	y = m_rProgressBar.top + edge1;
	m_rPeriodString.SetRect(x, y, x + size.cx, y + size.cy);
	if (m_iState1 == 4)
	{
		s = "剩余时间";
		if (iLanguage == 0)
			s = "Time remaining ";
	}
	else
	{
		s = "单步用时";
		if (iLanguage == 0)
			s = "Period time";
	}
	pDC->TextOutA(x, y, s);
	s = "00:00:00";
	size = pDC->GetTextExtent(s);
	s.Format("%02d:%02d:%02d", m_PeriodTime.GetHours(), m_PeriodTime.GetMinutes(), m_PeriodTime.GetSeconds());
	x = m_rPeriodString.right - size.cx;
	m_rPeriodTime.SetRect(x, y, x + size.cx, y + size.cy);
	pDC->TextOutA(x, y, s);
	//游戏信息
	pDC->SetTextColor(RGB(50, 50, 50));
	s = "";
	if (m_iState != 1)
	{
		switch (iRule)
		{
		case 0:
			s = "中国规则    ";
			break;
		case 1:
			s = "日本规则    ";
			break;
		case 2:
			s = "韩国规则    ";
			break;
		}
		s += "贴目： ";
		CString s1 = "无";
		if (m_fKomi != 0)
		{
			int nkomi = int(m_fKomi);
			s1.Format("%d目", nkomi);
			if (m_fKomi - 0.4 > nkomi)
				s1 += "半";
		}
		s += s1;
		s += "    让子： ";
		if (m_iHandiCap == 0)
		{
			if (m_fKomi > 0)
				s += "互先";
			else
				s += "定先";
		}
		if (m_iHandiCap >= 2)
		{
			s1.Format("%d子", m_iHandiCap);
			s += s1;
		}
		if (iLanguage == 0)
		{
			switch (iRule)
			{
			case 0:
				s = "Chinese rule    ";
				break;
			case 1:
				s = "Japanese rule    ";
				break;
			case 2:
				s = "Korean rule    ";
				break;
			}
			s += "Komi: ";
			CString s1 = "None";
			if (m_fKomi != 0)
			{
				s1.Format("%4.1f", m_fKomi);
			}
			s += s1;
			s += "    Handicap:  ";
			if (m_iHandiCap == 0)
			{
					s += "Even";
			}
			if (m_iHandiCap >= 2)
			{
				s1.Format("%d", m_iHandiCap);
				s += s1;
			}
		}
	}
	else//死活分析
	{
		s = m_sPlayInfo;
	}
	size = pDC->GetTextExtent(s);
	x = m_rPlayInfo.left + (m_rPlayInfo.Width() - size.cx) / 2;
	y = m_rPlayInfo.top + edge1;
	pDC->TextOutA(x, y, s);
	s = m_sOutputInfo;
	size = pDC->GetTextExtent(s);
	x = m_rPlayInfo.left + (m_rPlayInfo.Width() - size.cx) / 2;
	y += edge / 2;
	m_rOutputInfo.SetRect(m_rPlayInfo.left, y, m_rPlayInfo.right, y + size.cy);
	pDC->TextOutA(x, y, s);
	s = m_sOtherInfo;
	size = pDC->GetTextExtent(s);
	x = m_rPlayInfo.left + (m_rPlayInfo.Width() - size.cx) / 2;
	y += edge / 2;
	m_rOtherInfo.SetRect(m_rPlayInfo.left, y, m_rPlayInfo.right, y + size.cy);
	pDC->TextOutA(x, y, s);
	//CFont font;
	//font.CreateFontA(m_iGap / 2, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	//CDC* pDC = GetDC();
	//CFont* oldfont = pDC->SelectObject(&font);
	//pDC->SetBkColor(BLACK);
	//int cx = m_rBlackInfo.left + m_iGap / 2;
	//int cy = (m_rBlackInfo.top + m_rBlackInfo.bottom) / 2;
	//CRect rt(cx, cy, size.cx + cx, size.cy + cy);
	//InvalidateRect(rt);
	//UpdateWindow();
	//pDC->DrawText
	//pDC->TextOutA(cx, cy, s);
	//pDC->SelectObject(oldfont);
	//font.DeleteObject();
	//ReleaseDC(pDC);

	ReleaseDC(pDC);
}

void CSfcGoView::PaintOutputInfo()
{
	CDC* pDC = GetDC();
	CString s = m_sOutputInfo;
	CSize size = pDC->GetTextExtent(s);
	int x = m_rOutputInfo.left + (m_rOutputInfo.Width() - size.cx) / 2;
	int y = m_rOutputInfo.top;
	pDC->SetTextColor(RGB(50, 50, 50));
	pDC->SetBkColor(RGB(226, 226, 226));
	pDC->TextOutA(x, y, s);
	ReleaseDC(pDC);
}

void CSfcGoView::PaintBoard()
{
	CRect rect,rt;
	GetClientRect(rect);
	//确定棋盘线数
	int boardwidth=m_iBoardSize;
	CDC *pDC=GetDC();
	//画棋盘背景
	int x=rect.Height()/22,y=x,w=rect.Height()-2*x;
	int edge=w/(boardwidth+1);
	w = edge * (boardwidth + 1);
	int w1 = 8 * edge;
	int h = w;
	int leftedge = (rect.Width() - w) / 2;//(rect.Width() - (w + edge * 10)) / 2;
	if ((!m_bShowRecSize || !bShowWinRate && !bShowAna && !bShowMoveRec) && m_bShowInfoSize && bShowInfo)
		leftedge = (rect.Width() - (w + w1 + edge)) / 2;
	else if (m_bShowRecSize && (bShowWinRate || bShowAna || bShowMoveRec) && (!m_bShowInfoSize || !bShowInfo))
		leftedge = (rect.Width() - (w + w1 + edge)) / 2 + w1 + edge;
	x = leftedge;
	m_rBoardBack.SetRect(x, y, x + w, y + h);
	pDC->SetStretchBltMode(HALFTONE);
	imBoardImg.Draw(pDC->GetSafeHdc(),m_rBoardBack);
	//画棋盘线
	pDC->SelectStockObject(BLACK_PEN);
	pDC->SelectStockObject(NULL_BRUSH);
	//边框
	x+=edge;y+=edge;w-=2*edge;h=w;
	pDC->Rectangle(x,y,x+w,y+h);
	pDC->Rectangle(x-1,y-1,x+w+1,y+h+1);
	m_BoardRect.SetRect(x,y,x+w,y+h);
	if (edge != m_iGap)
	{
		m_iGap=edge;
		if (m_iState1 > 0 && m_iState1<3)
		{
			m_hBlackCursor = (HCURSOR)LoadImage(NULL, strSysDirectry + "\\blackstone.ico", IMAGE_ICON, m_iGap + 4, m_iGap + 4, LR_LOADFROMFILE);
			m_hWhiteCursor = (HCURSOR)LoadImage(NULL, strSysDirectry + "\\whitestone.ico", IMAGE_ICON, m_iGap + 4, m_iGap + 4, LR_LOADFROMFILE);
		}
	}
	//网格
	for(int i=1;i<boardwidth-1;i++)
	{
		pDC->MoveTo(x,y+i*edge);
		pDC->LineTo(x+w,y+i*edge);
		pDC->MoveTo(x+i*edge,y);
		pDC->LineTo(x+i*edge,y+h);
	}
	//画坐标
//#ifdef DEBUG
	if (bCoord)
	{
		pDC->SetBkMode(TRANSPARENT);
		for (int i = 0; i < boardwidth; i++)
		{
			CString str;
			if (i <= 7)
				str.Format("%c", i + 'A');
			else
				str.Format("%c", i + 'B');
			pDC->TextOutA(x + i * edge - 5, y - 20 - edge, str);
			pDC->TextOutA(x + i * edge - 5, y + h + 5 + edge, str);
			str.Format("%d", 19 - i);
			pDC->TextOutA(x - 20 - edge, y + i * edge - 10, str);
			pDC->TextOutA(x + w + 5 + edge, y + i * edge - 10, str);
		}
	}
//#endif
	//画座点
	pDC->SelectStockObject(BLACK_BRUSH);
	switch (iBoardSizeState)
	{
	case 0:
		pDC->Ellipse(x+2*edge-4,y+2*edge-4,x+2*edge+4,y+2*edge+4);
		pDC->Ellipse(x+6*edge-4,y+2*edge-4,x+6*edge+4,y+2*edge+4);
		pDC->Ellipse(x+2*edge-4,y+6*edge-4,x+2*edge+4,y+6*edge+4);
		pDC->Ellipse(x+6*edge-4,y+6*edge-4,x+6*edge+4,y+6*edge+4);
		pDC->Ellipse(x+4*edge-4,y+4*edge-4,x+4*edge+4,y+4*edge+4);
		break;
	case 1:
		pDC->Ellipse(x+3*edge-4,y+3*edge-4,x+3*edge+4,y+3*edge+4);
		pDC->Ellipse(x+9*edge-4,y+3*edge-4,x+9*edge+4,y+3*edge+4);
		pDC->Ellipse(x+3*edge-4,y+9*edge-4,x+3*edge+4,y+9*edge+4);
		pDC->Ellipse(x+9*edge-4,y+9*edge-4,x+9*edge+4,y+9*edge+4);
		pDC->Ellipse(x+6*edge-4,y+6*edge-4,x+6*edge+4,y+6*edge+4);
		break;
	case 2:
	pDC->Ellipse(x+3*edge-4,y+3*edge-4,x+3*edge+4,y+3*edge+4);
	pDC->Ellipse(x+9*edge-4,y+3*edge-4,x+9*edge+4,y+3*edge+4);
	pDC->Ellipse(x+15*edge-4,y+3*edge-4,x+15*edge+4,y+3*edge+4);
	pDC->Ellipse(x+3*edge-4,y+9*edge-4,x+3*edge+4,y+9*edge+4);
	pDC->Ellipse(x+9*edge-4,y+9*edge-4,x+9*edge+3,y+9*edge+4);
	pDC->Ellipse(x+15*edge-4,y+9*edge-4,x+15*edge+3,y+9*edge+4);
	pDC->Ellipse(x+3*edge-4,y+15*edge-4,x+3*edge+3,y+15*edge+4);
	pDC->Ellipse(x+9*edge-4,y+15*edge-4,x+9*edge+3,y+15*edge+4);
	pDC->Ellipse(x+15*edge-4,y+15*edge-4,x+15*edge+3,y+15*edge+4);
		break;
	default:
		break;
	}
	ReleaseDC(pDC);
	for(int i=0;i<m_iBoardSize;i++)
	{
		for(int j=0;j<m_iBoardSize;j++)
			PaintQz(i,j,m_iBoard[i][j]);
	}
	//if(m_iState!=1 || m_iState==1 && m_bInTurn)//死活分析时，无需显示最后棋子
		PaintLastQz();
	if(m_bRecall || m_iState1==6 || m_iState==1 && m_iState1>2 && m_iState1<11)
	{
		for(int i=m_iFixedStone;i<m_iGoCount;i++)
			PaintIdx(i);
	}
	//PaintQz(3, 3, 2);
}

void CSfcGoView::PaintQz(int x,int y,int color)
{
	if (x >= 0 && x < m_iBoardSize && y >= 0 && y < m_iBoardSize && color>0)
	{
		CRect rect;
		GetClientRect(rect);
		//int sx=rect.Height()/22,sy=sx;
		//int w=rect.Height()-2*sx;
		//int edge=w/(m_iBoardSize+1);
		//int leftedge = (rect.Width() - (w + edge * 10)) / 2;
		//sx = leftedge;
		//int cx = edge + sx + x * edge -edge / 2;// +1;//edge*2/5;
		//int cy = edge + sy + y * edge -edge / 2;// +1;// edge * 2 / 5;
		//w = edge+4;// -2;
		int cx = m_BoardRect.left + x * m_iGap - m_iGap / 2 - 2;
		int cy = m_BoardRect.top + y * m_iGap - m_iGap / 2 - 2;
		int w = m_iGap + 4;
		CDC* pDC = GetDC();
		CRect rt(cx, cy, w, w);
		//CRgn rg;
		//rg.CreateEllipticRgn(rt.left,rt.top,rt.right,rt.bottom);
		//pDC->SelectClipRgn(&rg);
		//rg.DeleteObject();
		pDC->SetStretchBltMode(HALFTONE);
		if (color == 1)
		{
			//imStoneEffect.Draw(pDC->m_hDC, cx, cy, w, w);
			imWhiteStone.Draw(pDC->GetSafeHdc(), cx, cy, w, w);
		}
		else
			imBlackStone.Draw(pDC->GetSafeHdc(), cx, cy, w, w);
		//imBlackStone.Draw(pDC->m_hDC, x, y, w*10, w*10);
		//imWhiteStone.Draw(pDC->m_hDC, x, y, w*10, w*10);
		//pDC->SelectStockObject(NULL_BRUSH);
		//imBlackStone.Draw(pDC->m_hDC,rt);
		/*CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap bmp;
		if(color==1)
			bmp.LoadBitmap(IDB_WHITESTONE);
		else
			bmp.LoadBitmap(IDB_BLACKSTONE);
		BITMAP bitp;
		bmp.GetBitmap(&bitp);
		CBitmap *poldbmp=memDC.SelectObject(&bmp);
		//pDC->BitBlt(cx,cy,w,w,&memDC,0,0,SRCAND);
		//pDC->StretchBlt(cx,cy,w,w,&memDC,0,0,bitp.bmWidth,bitp.bmHeight,SRCCOPY);
		//HBITMAP hbmp;
		//hbmp=(HBITMAP)LoadImage(NULL,strSysDirectry+"\\stone.jpg",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		//HDC hdcBmp=NULL;
		//SelectObject(hdcBmp,bmp.m_hObject);
		//CImage img;
		//img.Load(strSysDirectry+"\\whitestone.bmp");
		//memDC.SelectObject(img);
		COLORREF rgb=memDC.GetPixel(1,1);
		pDC->TransparentBlt(cx,cy,w,w,&memDC,0,0,bitp.bmHeight,bitp.bmHeight,rgb);
		memDC.SelectObject(poldbmp);
		ReleaseDC(&memDC);*/
		//if(color==1)
		//	pDC->SelectStockObject(WHITE_BRUSH);
		//else
		//	pDC->SelectStockObject(BLACK_BRUSH);
		//pDC->Ellipse(cx,cy,cx+w,cy+w);
		ReleaseDC(pDC);
	}
}

void CSfcGoView::PaintLastQz(int x,int y,int color)
{
	if (x >= 0 && x < m_iBoardSize && y >= 0 && y < m_iBoardSize && color>0)
	{
		//CRect rect;
		//GetClientRect(rect);
		//int sx=rect.Height()/22,sy=sx;
		//int w=rect.Height()-2*sx;
		//int edge=w/(m_iBoardSize+1);
		//int leftedge = (rect.Width() - (w + edge * 10)) / 2;
		//sx = leftedge;
		//int cx = edge + sx + x * edge;// -edge / 2 - 2;// +1;//edge*2/5;
		//int cy = edge + sy + y * edge;// -edge / 2 - 2;// +1;// edge * 2 / 5;
		//w = edge+4;// -2;
		int cx = m_BoardRect.left + x * m_iGap - m_iGap / 2 - 2;
		int cy = m_BoardRect.top + y * m_iGap - m_iGap / 2 - 2;
		int w = m_iGap + 4;
		CDC* pDC = GetDC();
		//CRect rt(cx,cy,w,w);
		//CRgn rg;
		//rg.CreateEllipticRgn(rt.left,rt.top,rt.right,rt.bottom);
		//pDC->SelectClipRgn(&rg);
		//rg.DeleteObject();
		pDC->SetStretchBltMode(HALFTONE);
		if (color == 1)
			imWhiteStone.Draw(pDC->GetSafeHdc(), cx, cy, w, w);
		else
			imBlackStone.Draw(pDC->GetSafeHdc(), cx, cy, w, w);
		ReleaseDC(pDC);
		PaintStoneSignal(x, y, color, "*");
		//pDC->SelectStockObject(NULL_BRUSH);
		//imBlackStone.Draw(pDC->m_hDC,rt);
		/*CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap bmp;
		bmp.LoadBitmap(IDB_BLACKSTONE);
		BITMAP bitp;
		bmp.GetBitmap(&bitp);
		CBitmap *poldbmp=memDC.SelectObject(&bmp);
		//pDC->BitBlt(cx,cy,w,w,&memDC,0,0,SRCAND);
		pDC->StretchBlt(cx,cy,w,w,&memDC,0,0,bitp.bmWidth,bitp.bmHeight,SRCCOPY);
		ReleaseDC(&memDC);*/
		//if(color==1)
		//	pDC->SelectStockObject(WHITE_BRUSH);
		//else
		//	pDC->SelectStockObject(BLACK_BRUSH);
		//pDC->Ellipse(cx,cy,cx+w,cy+w);
		//CBrush redBrush;
		//redBrush.CreateSolidBrush(RGB(255, 0, 0));
		//pDC->SelectObject(redBrush);
		//pDC->Rectangle(cx + w / 4, cy + w / 4, cx + w * 3 / 4, cy + w * 3 / 4);
		//ReleaseDC(pDC);
	}
}

void CSfcGoView::PaintLastQz()
{
	if (m_iGoCount <= 0)
		return;
	if (m_iState == 2 ||m_iState==1 && m_iState1!=11 || m_iState==3)
	{
		if (m_iGoCount > m_iFixedStone)
		{
			int id = m_iGoCount - 1;
			//最后几步是PASS的不显示
			while (m_GoRecord[id].x < 0)
				id--;
			//PaintLastQz(m_GoRecord[m_iGoCount-1].x,m_GoRecord[m_iGoCount-1].y,m_GoRecord[m_iGoCount-1].color);
			PaintQz(m_GoRecord[id].x, m_GoRecord[id].y, m_GoRecord[id].color);
			//if (m_iState == 2)//对局时显示末位棋子坐标
				PaintIdx(id);
		}
	}
	else if (m_iState == 1 && m_iState1==1)//死活题摆子时显示棋子标识
	{
		PaintQz(m_GoRecord[m_iGoCount - 1].x, m_GoRecord[m_iGoCount - 1].y, m_GoRecord[m_iGoCount - 1].color);
		PaintStoneSignal(m_GoRecord[m_iGoCount - 1].x, m_GoRecord[m_iGoCount - 1].y, m_GoRecord[m_iGoCount - 1].color, "X");//
	}
}

void CSfcGoView::PaintIdx(int id)
{
	if(id>=m_iFixedStone && id<m_iGoCount)
	{
		int x = m_GoRecord[id].x;
		int y = m_GoRecord[id].y;
		int color = m_GoRecord[id].color;
		if (x < 0 || x >= m_iBoardSize || y < 0 || y >= m_iBoardSize || color <= 0)
			return;
		CString s;
		s.Format("%d",id+1-m_iFixedStone);
		CFont font;
		//font=new CFont;
		font.CreateFontA(m_iGap/2,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,_T("Arial"));
		CDC *pDC=GetDC();
		CFont *oldfont=pDC->SelectObject(&font);
		if(color==1)
			pDC->SetTextColor(RGB(0,0,0));
		else
			pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		CSize size=pDC->GetTextExtent(s);
		int cx=m_BoardRect.left+x*m_iGap;
		int cy=m_BoardRect.top+y*m_iGap;
		cx-=size.cx/2;
		cy-=size.cy/2;
		pDC->TextOutA(cx,cy,s);
		pDC->SelectObject(oldfont);
		font.DeleteObject();
		ReleaseDC(pDC);
	}
}

void CSfcGoView::PaintStoneSignal(int x, int y, int color, CString s)
{
	CFont font;
	font.CreateFontA(m_iGap / 2, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	CDC* pDC = GetDC();
	CFont* oldfont = pDC->SelectObject(&font);
	if (color == 1)
		pDC->SetTextColor(RGB(0, 0, 0));
	else
		pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkMode(TRANSPARENT);
	CSize size = pDC->GetTextExtent(s);
	int cx = m_BoardRect.left + x * m_iGap;
	int cy = m_BoardRect.top + y * m_iGap;
	cx -= size.cx / 2;
	cy -= size.cy / 2;
	pDC->TextOutA(cx, cy, s);
	pDC->SelectObject(oldfont);
	font.DeleteObject();
	ReleaseDC(pDC);

}

void CSfcGoView::PaintHintStone()
{
	if (m_iState1 != 5)
		return;
	CDC* pDC = GetDC();
	int x, y, cx, cy, w;
	CString s;
	CSize size;
	CBrush whiteBrush, darkBrush;
	whiteBrush.CreateSolidBrush(RGB(150, 150, 150));
	darkBrush.CreateSolidBrush(RGB(76, 76, 76));
	CFont font;
	font.CreateFontA(m_iGap / 2, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	CFont* oldfont = pDC->SelectObject(&font);
	if (m_iColor == BLACK)
	{
		pDC->SelectObject(darkBrush);
		pDC->SetTextColor(RGB(186, 186, 186));
	}
	else
	{
		pDC->SelectObject(whiteBrush);
		pDC->SetTextColor(RGB(76, 76, 76));
	}
	pDC->SetBkMode(TRANSPARENT);
	for (int i = 0; i < m_iAnaMoveCount; i++)
	{
		//棋子
		Trans(m_sAnaMoveRecs[i], x, y);
		cx = m_BoardRect.left + x * m_iGap - m_iGap / 2;
		cy = m_BoardRect.top + y * m_iGap - m_iGap / 2;
		w = m_iGap;
		pDC->Ellipse(cx,cy,cx+w,cy+w);
		//胜率
		s.Format("%d", (int)(m_fAnaMoveWinRates[i] * 100));
		size = pDC->GetTextExtent(s);
		cx = m_BoardRect.left + x * m_iGap;
		cy = m_BoardRect.top + y * m_iGap;
		cx -= size.cx / 2;
		cy -= size.cy / 2;
		pDC->TextOutA(cx, cy, s);
	}
	pDC->SelectObject(oldfont);
	font.DeleteObject();
	whiteBrush.DeleteObject();
	darkBrush.DeleteObject();
	ReleaseDC(pDC);
}

void CSfcGoView::OnDraw(CDC* pDC)
{
	// TODO: 在此添加专用代码和/或调用基类
	CRect rect, rt;
	GetClientRect(rect);
	pDC->SetStretchBltMode(HALFTONE);
	imBackGound.Draw(pDC->GetSafeHdc(), rect);
	ReleaseDC(pDC);
	PaintBoard();
	if(m_bShowInfoSize && bShowInfo)
		PaintInfo();
	if(m_bShowRecSize && (bShowWinRate || bShowAna || bShowMoveRec))
		PaintMoveRec();
	PaintHintStone();
	PaintLabel();
	//if(m_iState==1 && m_iState1>0)//(m_bShowLifeDeathPanel)
		//ShowLifeDeathPanel();
}

void CSfcGoView::WriteLastGo()
{
	int x=m_GoRecord[m_iGoCount-1].x;
	int y=m_GoRecord[m_iGoCount-1].y;
	int color=m_GoRecord[m_iGoCount-1].color;
	if (x < 0 || x >= m_iBoardSize || y < 0 || y >= m_iBoardSize || color <= 0)
		return;
	m_iBoard[x][y]=color;
	if(m_iGoCount>m_iFixedStone+1)
	{
		PaintQz(m_GoRecord[m_iGoCount-2].x,m_GoRecord[m_iGoCount-2].y,m_GoRecord[m_iGoCount-2].color);
		if(m_bRecall)
			PaintIdx(m_iGoCount-2);
	}
	//if (m_iState == 1 && m_iState1 == 11)//死活分析摆子时最后一步显示为矩形标志
	//	PaintLastQz(x, y, color);
	//else
		PaintLastQz();
	if(m_bRecall)
		PaintIdx(m_iGoCount-1);
}

void CSfcGoView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 落子
	if(point.x>=m_BoardRect.left-m_iGap/4 && point.x<=m_BoardRect.right+m_iGap/4 && point.y>m_BoardRect.top-m_iGap/4 && point.y<m_BoardRect.bottom+m_iGap/4)
	{
		int x=int((point.x-m_BoardRect.left+m_iGap/2)/m_iGap);
		int y=int((point.y-m_BoardRect.top+m_iGap/2)/m_iGap);
		bool acted=false;
		if(m_iState==1)//死活分析
		{
			switch (m_iState1)
			{
			case 0:
				break;
			case 11://摆子状态
				if(m_iBoard[x][y]>=1)
				{
					m_iMaxSizePos=POS(x,y);
					//MessageBox("已选定攻击/防守目标");
				}
				else
				{
					if (Sfc::PlayStone(x, y, m_iColor, m_GoInfo))//有提子情况
					{
						CString msg = "摆子时不能有提子！";
						if (iLanguage == 0)
							msg = "Can not capture while put stone!";
						MessageBox(msg);
						Sfc::Undo(1,m_GoInfo);
						return;
					}
					m_GoInfo.fixedstone++;
					AddStone(x, y, m_iColor);
					m_iFixedStone++;
					sgftreeAddStone(&m_Sgftree, m_iColor, STDPOS(x, y));
					//WriteLastGo();
					if(m_bInTurn)//交替摆子
					{
						m_iColor=OTHER_COLOR(m_iColor);
					}
					//else
					//{
					//	InitSgf(&m_Gameinfo);
					//	sgftreeAddStone(&m_Sgftree, m_iColor, STDPOS(x, y));
					//	Sfc::AddStone(x,y,m_iColor,m_GoInfo);
					//	AddStone(x,y,m_iColor);
					//}
				}
				/*if(m_iBoard[x][y]<1)
				{
				m_GoRecord[m_iGoCount].x=x;
				m_GoRecord[m_iGoCount].y=y;
				m_GoRecord[m_iGoCount].color=m_iColor;
				m_iGoCount++;
				add_stone(POS(x,y),m_iColor);
				WriteLastGo();
				//acted=true;
				}*/
				break;
			case 13://研究状态
				Sfc::PlayStone(x, y, m_iColor, m_GoInfo);
				AddStone(x, y, m_iColor);
				m_iGoCountMax = m_iGoCount;
				//WriteLastGo();
				if (m_bInTurn)//交替摆子
				{
					m_iColor = OTHER_COLOR(m_iColor);
				}
				UpdateBackForwardButton();
				break;
			case 1://等待玩家应对
				if (!m_bAnswered)
				{
					m_iState1 = 2;
					//PlayerMove(x, y, m_iColor);
					m_iCx = x; m_iCy = y;
					AfxBeginThread(PlayerMoveThread, this);
				}
				break;
			default:
				break;
			}
		}
		else if(m_iState==2)//人机对弈
		{
			switch (m_iState1)
			{
			case 0:
				break;
			case 1://等待玩家落子
				m_iState1=2;
				//PlayerMove(x,y,m_iColor);
				m_iCx = x; m_iCy = y;
				AfxBeginThread(PlayerMoveThread, this);
				break;
			default:
				break;
			}
		}
		else if (m_iState == 3)//序盘研究
		{
			switch (m_iState1)
			{
			case 0:
				break;
			case 5:
				int i;
				for (i = 0; i < m_iAnaMoveCount; i++)
					if (m_sAnaMoveRecs[i] == TransXY(x, y))
						break;
				if (i < m_iAnaMoveCount)
				{
					m_iAnaMoveId = i;
					ShowAnaMove();
					InvalidateRect(m_rMoveRec);
					UpdateWindow();
				}
				break;
			case 21:
				if (m_iBoard[x][y] >= 1)
				{
					m_iMaxSizePos = POS(x, y);
					//MessageBox("已选定攻击/防守目标");
				}
				else
				{
					Sfc::PlayStone(x, y, m_iColor, m_GoInfo);
					if(AddStone(x, y, m_iColor))
						m_iGoCountMax++;
					//sgftreeAddStone(&m_Sgftree, m_iColor, STDPOS(x, y));
					if (m_bInTurn)//交替摆子
					{
						m_iColor = OTHER_COLOR(m_iColor);
					}
					m_Gameinfo.to_move = m_iColor;
					UpdateBackForwardButton();
					UpdateWindow();
				}
				break;
			}
		}
		if(acted)
			OutputInfo();
	}
	//点击按钮
	if (m_rToolBox.PtInRect(point))
	{
		if (m_iStateNew == 1)
		{
			m_iStateNew = 2;
			PaintButton(0);
		}
		if (m_iStateOpen == 1)
		{
			m_iStateOpen = 2;
			PaintButton(1);
		}
		if (m_iStateSave == 1)
		{
			m_iStateSave = 2;
			PaintButton(2);
		}
		if (m_iStateReopen == 1)
		{
			m_iStateReopen = 2;
			PaintButton(3);
		}
		if (m_iStateArea == 1)
		{
			m_iStateArea = 2;
			PaintButton(4);
		}
		if (m_iStateExit == 1)
		{
			m_iStateExit = 2;
			PaintButton(5);
		}
		if (m_iStateResign == 1)
		{
			m_iStateResign = 2;
			PaintButton(6);
		}
		if (m_iStateGoFirst == 1)
		{
			m_iStateGoFirst = 2;
			PaintButton(10);
		}
		if (m_iStateGoFiveBack == 1)
		{
			m_iStateGoFiveBack = 2;
			PaintButton(11);
		}
		if (m_iStateGoBack == 1)
		{
			m_iStateGoBack = 2;
			PaintButton(12);
		}
		if (m_iStateGoForward == 1)
		{
			m_iStateGoForward = 2;
			PaintButton(13);
		}
		if (m_iStateGoFiveForward == 1)
		{
			m_iStateGoFiveForward = 2;
			PaintButton(14);
		}
		if (m_iStateGoLast == 1)
		{
			m_iStateGoLast = 2;
			PaintButton(15);
		}
		if (m_iStateBlackFirst == 1)
		{
			m_iStateBlackFirst = 2;
			PaintButton(20);
		}
		if (m_iStateWhiteFirst == 1)
		{
			m_iStateWhiteFirst = 2;
			PaintButton(21);
		}
		if (m_iStatePutBlack == 1)
		{
			m_iStatePutBlack = 2;
			PaintButton(22);
		}
		if (m_iStatePutWhite == 1)
		{
			m_iStatePutWhite = 2;
			PaintButton(22);
		}
	}
	CFormView::OnLButtonDown(nFlags, point);
}


void CSfcGoView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(point.x>=m_BoardRect.left-m_iGap/4 && point.x<=m_BoardRect.right+m_iGap/4 && point.y>m_BoardRect.top-m_iGap/4 && point.y<m_BoardRect.bottom+m_iGap/4)
	{
		int x=int((point.x-m_BoardRect.left+m_iGap/2)/m_iGap);
		int y=int((point.y-m_BoardRect.top+m_iGap/2)/m_iGap);
		if(m_iState==1)//死活分析
		{
			switch (m_iState1)
			{
			case 0:
				if (m_bDifficulty)
				{
					m_bDifficulty = false;
					m_iStateNew = 0;
					m_iStateOpen = 0;
					m_iStateSave = 0;
					m_iStateReopen = 0;
					m_iStateExit = 0;
					Invalidate();
					UpdateWindow();
				}
				break;
			case 11://摆子状态
				RemoveStone(x,y);
				//Sfc::RemoveStone(x,y,m_GoInfo);
				/*if(m_iBoard[x][y]>0)
				{
				for(int i=0;i<m_iGoCount;i++)
				{
				if(m_GoRecord[i].x==x && m_GoRecord[i].y==y)
				{
				for(int j=i;j<m_iGoCount-1;j++)
				{
				m_GoRecord[j]=m_GoRecord[j+1];
				}
				m_iGoCount--;
				m_iBoard[x][y]=0;
				remove_stone(POS(x,y));
				PaintBoard();
				WriteLastGo();
				break;
				}
				}
				}*/
				break;
			default:
				break;
			}
		}
		else if (m_iState == 3)//序盘研究
		{
			if (m_iState1 == 5 || m_iState1 == 6 || m_iState1 == 21 || m_iState1 == 22)
				OnReturn();
			else if (m_iState1 == 0)
				OnExit();
		}
	}

	CFormView::OnRButtonDown(nFlags, point);
}


void CSfcGoView::OnBnClickedRadblack()
{
	m_iColor=2;
	m_bInTurn=false;
	if (m_iState == 2 && m_iState1 == 1)//交换对弈双方
	{
		m_Gameinfo.computer_player = OTHER_COLOR(m_iColor);
		if (m_Gameinfo.computer_player == m_Gameinfo.to_move)
		{
			SetDlgItemText(IDC_STAT, sThinkMsg);
			m_btnAna.EnableWindow(FALSE);
			m_radBlack.EnableWindow(FALSE);
			m_radWhite.EnableWindow(FALSE);
			m_btnScore.EnableWindow(FALSE);
			m_iStateReopen = 3;
			UpdateData(FALSE);
			ComputerMove();
		}
	}
}


void CSfcGoView::OnBnClickedRadwhite()
{
	m_iColor=1;
	m_bInTurn=false;
	if (m_iState == 2 && m_iState1 == 1)//交换对弈双方
	{
		m_Gameinfo.computer_player = OTHER_COLOR(m_iColor);
		if (m_Gameinfo.computer_player == m_Gameinfo.to_move)
		{
			SetDlgItemText(IDC_STAT, sThinkMsg);
			m_btnAna.EnableWindow(FALSE);
			m_radBlack.EnableWindow(FALSE);
			m_radWhite.EnableWindow(FALSE);
			m_btnScore.EnableWindow(FALSE);
			m_iStateReopen = 3;
			UpdateData(FALSE);
			ComputerMove();
		}
	}
	m_radWhite.SetCheck(BST_CHECKED);
	m_bBlack = FALSE;
	m_radBlack.SetCheck(BST_UNCHECKED);
}


void CSfcGoView::OnViewRecall()
{
	m_bRecall=!m_bRecall;
	PaintBoard();
}


void CSfcGoView::OnUpdateViewRecall(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bRecall);
}

bool CSfcGoView::AddStone(int x,int y,int color)
{
	if(x<0 || m_iBoard[x][y]<1)
	{
		//if(m_iState==1 && m_iState1==1 && !m_bInTurn)//摆子状态
			//add_stone(POS(x,y),color);
		m_GoRecord[m_iGoCount].x=x;
		m_GoRecord[m_iGoCount].y=y;
		m_GoRecord[m_iGoCount].color=color;
		m_iGoCount++;
		//人机对弈状态判断是否出现提子
		bool bcaptured = false;
		if (x >= 0)//非pass
		{
			if (m_iState==3 || m_iState == 2 || m_iState == 1 && (m_bInTurn || m_bSgfLoaded))
			{
				for (int i = 0; i < m_iBoardSize; i++)
				{
					for (int j = 0; j < m_iBoardSize; j++)
					{
						/*if(m_iBoard[i][j]>0 && board[POS(i,j)]==0)
						{
							m_iBoard[i][j]=0;
							bcaptured=true;
						}*/
						if (m_iBoard[i][j] > 0 && m_GoInfo.board[i][j] == 0)
						{
							bcaptured = true;
							//if (m_iBoard[i][j] == 2)
							//	m_GoInfo.blackcaptured++;
							//else
							//	m_GoInfo.whitecaptured++;
						}
						m_iBoard[i][j] = m_GoInfo.board[i][j];
					}
				}
			}
			if (bcaptured)
			{
				InvalidateRect(m_BoardRect);
				UpdateWindow();
				//PaintBoard();
			}
			else
				WriteLastGo();
		}
		if (m_iState1 == 11 || m_iState1 == 13 || m_iState1 == 21)//正在摆子
		{
			if (m_iState1 == 13 || m_iState1 == 21)
			{
				m_sMoveRecs[m_iMoveCount] = TransXY(x, y, color);
				m_sMoveTimeRecs[m_iMoveCount].Format("%02d:%02d:%02d", m_PeriodTime.GetHours(), m_PeriodTime.GetMinutes(), m_PeriodTime.GetSeconds());
				if (color == BLACK)
					m_fMoveWinRates[m_iMoveCount] = m_fBlackWinRate;
				else
					m_fMoveWinRates[m_iMoveCount] = m_fWhiteWinRate;
				m_iMoveCount++;
			}
			InvalidateRect(m_rBoardBack);
			//UpdateBackForwardButton();
			//UpdateWindow();
			if (bPutStoneSound)
				PlaySound(strSysDirectry + "\\Stone.wav", NULL, SND_ASYNC);
			if (bcaptured && bCaptureSound)
			{
				Sleep(500);
				PlaySound(strSysDirectry + "\\Capture.wav", NULL, SND_ASYNC);
			}
		}
		else if (m_iState1 > 0 && m_iState1 < 3)
		{
			if (x >= 0)
			{
				if (bPushClockSound)
				{
					if (bPutStoneSound)
						PlaySound(strSysDirectry + "\\Stone.wav", NULL, SND_SYNC);
					if (bcaptured && bCaptureSound)
					{
						Sleep(500);
						PlaySound(strSysDirectry + "\\Capture.wav", NULL, SND_SYNC);
					}
					PlaySound(strSysDirectry + "\\PushClock.wav", NULL, SND_SYNC);
				}
				else
				{
					if (bPutStoneSound)
						PlaySound(strSysDirectry + "\\Stone.wav", NULL, SND_ASYNC);
					if (bcaptured && bCaptureSound)
					{
						Sleep(500);
						PlaySound(strSysDirectry + "\\Capture.wav", NULL, SND_ASYNC);
					}
				}
			}
			//计时
			KillTimer(color);
			CTime t = GetTickCount64();
			//time_t t1 = m_StartTime.GetTime();
			CTimeSpan ts = (t.GetTime() - m_StartTime.GetTime()) / 1000;
			if (color == 2)
				m_BlackTime = ts - m_WhiteTime;//m_BlackTime.GetSeconds
			else
				m_WhiteTime = ts - m_BlackTime;
			if (!m_bSelfPlay && !m_bEngineDual && color != m_iColor)
			{
				m_sOutputInfo = "轮玩家着子";
				if (iLanguage == 0)
					m_sOutputInfo = "Waiting for player's move";
				InvalidateRect(m_rOutputInfo);
				//PaintOutputInfo();
				m_sOtherInfo.Format("黑棋胜率：%3.0f%%  白棋胜率：%3.0f%%", m_fBlackWinRate * 100, m_fWhiteWinRate * 100);
				if (iLanguage == 0)
					m_sOtherInfo.Format("Black WR：%3.0f%%  White WR：%3.0f%%", m_fBlackWinRate * 100, m_fWhiteWinRate * 100);
				InvalidateRect(m_rOtherInfo);
				m_iStateNew = 0;
				m_iStateReopen = 0;
				if (m_iCombat == 0)
				{
					m_iStateOpen = 0;
					m_iStateSave = 0;
					m_iStateArea = 0;
					m_iStateExit = 0;
				}
				m_iStateResign = 0;
				this->InvalidateRect(m_rToolBox);
				UpdateWindow();
				//PaintButton(0);
				//PaintButton(1);
				//PaintButton(2);
				//PaintButton(4);
				//PaintButton(5);
				//PaintButton(6);
			}
			m_sMoveRecs[m_iMoveCount] = TransXY(x, y, color);
			m_sMoveTimeRecs[m_iMoveCount].Format("%02d:%02d:%02d", m_PeriodTime.GetHours(), m_PeriodTime.GetMinutes(), m_PeriodTime.GetSeconds());
			if (color == BLACK)
				m_fMoveWinRates[m_iMoveCount] = m_fBlackWinRate;
			else
				m_fMoveWinRates[m_iMoveCount] = m_fWhiteWinRate;
			m_iMoveCount++;
			m_PeriodTime = CTimeSpan(0, 0, 0, 0);
			SetTimer(OTHER_COLOR(color), 1000, NULL);
		}
		else
			m_bCaptured = bcaptured;
		return true;
	}
	return false;
}

bool CSfcGoView::RemoveStone(int x,int y)
{
	if(m_iBoard[x][y]>0)
	{
		m_iBoard[x][y]=0;
		if(m_iState1==11)//摆子状态
		{
			for(int i=m_iGoCount-1;i>=0;i--)
			{
				if (m_GoRecord[i].x == x && m_GoRecord[i].y == y)
				{
					for (int j = i; j < m_iGoCount - 1; j++)
					{
						m_GoRecord[j] = m_GoRecord[j + 1];
					}
					m_iGoCount--;
					m_GoInfo.Init(m_iBoardSize);
					for (int j = 0; j < m_iGoCount; j++)
						Sfc::PlayStone(m_GoRecord[j].x, m_GoRecord[j].y, m_GoRecord[j].color, m_GoInfo);
					CopyLocalBoard();
					InvalidateRect(m_rBoardBack);
					break;
				}
			}
		}
		return true;
	}
	return false;
}

void CSfcGoView::OutputInfo()
{
	//make_worms();
	//make_dragons(0);
	CString str,str1;
	str.Format("总手数：%d",m_iGoCount);
	if (iLanguage == 0)
		str.Format("Move count:%d", m_iGoCount);
	int x=m_GoRecord[m_iGoCount-1].x;
	int y=m_GoRecord[m_iGoCount-1].y;
	int pos=POS(x,y);
	//int id=dragon[pos].id;
	//str1.Format("\n棋群：%d",dragon2[id].adjacent[0]);
	//str1.Format("\n棋群：%d",dragon2[0].adjacent);
	str+=str1;
	m_strOutput+=str;
	UpdateData(FALSE);
	//m_eOutput.Invalidate();
	//make_worms();
	//make_dragons(0);
	//dragon2[0].adjacent;
	

}

CString CSfcGoView::TransXY(int x, int y, int color)
{
	CString str,str1;
	if (color == 1)
		str = "W ";
	else
		str = "B ";
	if (x == -1)
		str1 = "pass";
	else if (x == -2)
		str1 = "resign";
	else if (x <= 7)
		str1.Format("%c%d", x + 'A',m_iBoardSize-y);
	else
		str1.Format("%c%d", x + 'B',m_iBoardSize-y);
	str += str1;
	return str;
}

CString CSfcGoView::TransXY(int x, int y)
{
	CString str1;
	if (x == -1)
		str1 = "pass";
	else if (x == -2)
		str1 = "resign";
	else if (x <= 7)
		str1.Format("%c%d", x + 'A', m_iBoardSize - y);
	else
		str1.Format("%c%d", x + 'B', m_iBoardSize - y);
	return str1;
}

void CSfcGoView::Trans(CString str, int& x, int& y)
{
	char c = str[0];
	if (str == "pass" || c == '0')//pass
	{
		x = -1;
		return;
	}
	else if (str == "resign")
	{
		x = -2;
		return;
	}
	if (c < 'I')
		x = c - 'A';
	else
		x = c - 'B';
	y = m_iBoardSize-atoi(str.Right(str.GetLength() - 1));
}

//玩家着手
int CSfcGoView::PlayerMove(int x,int y,int color)
{
	m_iPasses = 0;
	m_Gameinfo.to_move=color;
	m_bAnaed = false;
	/*int move = POS(x, y);

	if (move == NO_MOVE) {
		//printf("\nInvalid move: %s\n", command);
		m_iState1=1;
		return 0;
	}*/

	//int passes = 0;
	//TRACE("\nyour move: %1m\n\n", move);
	//InitSgf(&m_Gameinfo);
	//gnugo_play_move(move, m_Gameinfo.to_move);
	//sgffile_add_debuginfo(sgftree.lastnode, 0.0);
	sgftreeAddPlay(&m_Sgftree, m_Gameinfo.to_move, STDPOS(x, y));
	//sgffile_output(&sgftree);

	/*if (opt_showboard) {
		ascii_showboard();
		printf("GNU Go is thinking...\n");
	}*/
	SetDlgItemText(IDC_STAT,sThinkMsg);
	/*m_sOutputInfo = "腾飞围棋正在思考......";
	InvalidateRect(m_rPlayInfo);
	m_iStateNew = 3;
	m_iStateOpen = 3;
	m_iStateSave = 3;
	m_iStateReopen = 3;
	m_iStateArea = 3;
	m_iStateExit = 3;
	m_iStateResign = 3;
	this->InvalidateRect(m_rToolBox);
	this->UpdateWindow();*/
	Sfc::PlayStone(x,y,color,m_GoInfo);
	AddStone(x,y,color);

	SfcGtp* pengine;
	if (iEngineId == 0)
		pengine = m_pEngine1;
	else
		pengine = m_pEngine2;
	CString msg = "play "+TransXY(x, y, color);
	msg += "\r\n";
	pengine->WriteToPipe(msg);
	int count;
	CString* strs=pengine->GetMsg(count);
	delete[] strs;
	if (m_iState == 1 && (m_iOldState1==12 || m_iOldState1==14))//死活分析做题时尝试按答案走
	{
		CString comment="";
		int color1 = color;
		if (GetSgfTreeMove(&m_Sgftree1, m_iMoveCount, m_sMoveRecs, x, y, color1, comment))
		{
			if (x == -1)//解题完毕
			{
				KillTimer(OTHER_COLOR(m_iColor));
				m_bAnswered = true;
				m_sOutputInfo = "解题完毕";
				if (iLanguage == 0)
					m_sOutputInfo = "Resolved";
			}
			if(x>=0)
			{
					m_sOutputInfo = sThinkMsg;
					InvalidateRect(m_rOutputInfo);
					this->UpdateWindow();
				color = OTHER_COLOR(m_Gameinfo.to_move);
				msg = "play " + TransXY(x, y, color);
				msg += "\r\n";
				pengine->WriteToPipe(msg);
				strs = pengine->GetMsg(count);
				delete[] strs;
				Sfc::PlayStone(x, y, color, m_GoInfo);
				if (bPickStoneSound)//拾子声
					PlaySound(strSysDirectry + "\\PickStone.wav", NULL, SND_SYNC);
				m_iCx = x;
				m_iCy = y;
				m_iCcolor = color;
				if (bAnimate)//落子动画
				{
					iThreadState = 1;
					AfxBeginThread(StoneMove, this);
				}
				else
				{
					Sleep(500);
					AddStone(x, y, color);
				}
				sgftreeAddPlay(&m_Sgftree, color, STDPOS(x, y));
			if (color1 == -1)
			{
				KillTimer(OTHER_COLOR(color));
				m_bAnswered = true;
				m_sOutputInfo = "解题完毕";
				if (iLanguage == 0)
					m_sOutputInfo = "Resolved";
			}
			}
			m_sOtherInfo = comment;
			if (!bAnimate)
				m_iState1 = 1;
			m_bPicked = false;
			InvalidateRect(m_rOtherInfo);
			UpdateWindow();
			return 1;
		}
	}
	//UpdateData(FALSE);
	/*if (force) {
		m_Gameinfo.computer_player = OTHER_COLOR(m_Gameinfo.computer_player);
		m_Gameinfo.to_move = OTHER_COLOR(m_Gameinfo.to_move);
		sgftreeAddComment(&sgftree, "forced");
		return 0;
	}*/

	m_Gameinfo.to_move = OTHER_COLOR(m_Gameinfo.to_move);
	return ComputerMove();
}

//电脑着手
int CSfcGoView::ComputerMove()
{
	if (!m_bSelfPlay && !m_bEngineDual)
	{
		m_sOutputInfo = sThinkMsg;
		InvalidateRect(m_rOutputInfo);
		//PaintOutputInfo();
		m_iStateNew = 3;
		m_iStateOpen = 3;
		m_iStateSave = 3;
		//m_iStateReopen = 3;
		m_iStateArea = 3;
		m_iStateExit = 3;
		m_iStateResign = 3;
		this->InvalidateRect(m_rToolBox);
		this->UpdateWindow();
		//PaintButton(0);
		//PaintButton(1);
		//PaintButton(2);
		//PaintButton(4);
		//PaintButton(5);
		//PaintButton(6);
	}
	else
	{
		if (m_Gameinfo.to_move == BLACK)
		{
			m_sOutputInfo = "轮黑方走";
			if (iLanguage == 0)
				m_sOutputInfo = "Waiting for black's move";
		}
		else
		{
			m_sOutputInfo = "轮白方走";
			if (iLanguage == 0)
				m_sOutputInfo = "Waiting for white's move";
		}
		//InvalidateRect(m_rOutputInfo);
		/*CDC* pDC = GetDC();
		CString s = m_sOutputInfo;
		CSize size = pDC->GetTextExtent(s);
		int x = m_rOutputInfo.left + (m_rOutputInfo.Width() - size.cx) / 2;
		int y = m_rOutputInfo.top;
		pDC->SetTextColor(RGB(50, 50, 50));
		pDC->SetBkColor(RGB(226, 226, 226));
		pDC->TextOutA(x, y, s);*/
		m_sOtherInfo.Format("黑棋胜率：%3.0f%%  白棋胜率：%3.0f%%", m_fBlackWinRate*100, m_fWhiteWinRate*100);
		if (iLanguage == 0)
			m_sOtherInfo.Format("Black WR：%3.0f%%  White WR：%3.0f%%", m_fBlackWinRate * 100, m_fWhiteWinRate * 100);
		/*s = m_sOtherInfo;
		size = pDC->GetTextExtent(s);
		x = m_rOtherInfo.left + (m_rOtherInfo.Width() - size.cx) / 2;
		y = m_rOtherInfo.top;
		pDC->TextOutA(x, y, s);
		ReleaseDC(pDC);*/
	}
	m_PeriodTime = CTimeSpan(0, 0, 0, 0);
	//SetTimer(m_Gameinfo.to_move, 1000, NULL);
	//int move;
	//float move_value;
	//int resign=0;
	//int resignation_declined = 0;
	//float upper_bound, lower_bound;

	//InitSgf(&m_Gameinfo);
	int color = m_Gameinfo.to_move;
	m_iCcolor = color;
	if (m_bSelfPlay)
	{
		if (iLevel1 != iLevel2)
		{
			if (color == BLACK)
				SetLevel(iLevel1);
			else
				SetLevel(iLevel2);
		}
		if (m_iComputerThinkTime != m_iComputerThinkTime2)
		{
			if(color==BLACK)
				SetTimes(0, m_iComputerThinkTime, m_iComputerByoStones);
			else
				SetTimes(0, m_iComputerThinkTime2, m_iComputerByoStones);
		}
	}
	else if (m_bEngineDual)
	{
		if (color == BLACK)
			iEngineId = iBlackEngineId;
		else
			iEngineId = iWhiteEngineId;
	}
	iEngineThreadState = 1;
	//if(m_iState==2)//人机对弈
		AfxBeginThread(GetEngineMove, this);
	//else//死活分析
	//	AfxBeginThread(GetEngineAna, this);
	/*CString msg = "kata-genmove_analyze";
	if (color == 1)
		msg += " W ";
	else
		msg += " B ";
	msg += "50\r\n";
	m_pEngine1->WriteToPipe(msg);
	m_strOutput += msg;
	UpdateData(FALSE);
	int count,x=-1,y;
	CString* strs = m_pEngine1->GetMsg(count);
	CString str1;
	for (int i = 0; i < count; i++)
	{
		if (strs[i].GetLength() > 7 && strs[i].Left(4) == "play")
		{
			str1 = strs[i];
			str1.TrimRight();
			Trans(str1.Right(str1.GetLength()-5), x, y);
			break;
		}
	}
	m_strOutput += str1 + "\r\n";
	if (x < -2 || x>=m_iBoardSize)
	{
		MessageBox("获取着手出错!");
		return 1;
	}
	if (x == -1)//pass
	{
		y = -1;
		passes++;
		if(passes<2)
			MessageBox("腾飞围棋PASS一手");
	}
	else if (x == -2)//resign
	{
		y = -2;
		MessageBox("腾飞围棋认输！");
		resign = 1;
	}
	else
	{
		Sfc::PlayStone(x, y, color, m_GoInfo);
		if(bPickStoneSound)//拾子声
			PlaySound(strSysDirectry + "\\PickStone.wav", NULL, SND_SYNC);
		//PlaySound(strSysDirectry + "\\PickStone.wav", NULL, SND_ASYNC);
		m_iCx = x;
		m_iCy = y;
		m_iCcolor = color;
		if (bAnimate)//落子动画
		{
			iThreadState = 1;
			AfxBeginThread(StoneMove, this);
		}
		else
			AddStone(x, y, color);
	}

	if (resignation_allowed && resign) {
		int state = EndGame(&m_Gameinfo, 2);
		m_iState1=0;
		//m_iColor=0;
		m_cmbMb.EnableWindow(TRUE);
		SetDlgItemText(IDC_STAT,"就绪");
		btnBz.SetWindowTextA("开始对弈");
		m_btnExit.SetWindowTextA("退  出");
		if (state != -1)
		{
			UpdateData(FALSE);
			return state;
		}

		resignation_allowed = 0;
		resignation_declined = 1;
	}

	//if (showscore) {
		//gnugo_estimate_score(&upper_bound, &lower_bound);
		//current_score_estimate = (int) ((lower_bound + upper_bound) / 2.0);
	//}

	//mprintf("%s(%d): %1m\n", color_to_string(m_Gameinfo.to_move),
		//movenum + 1, move);
	//if (is_pass(move))
		//(passes)++;
	//else
		//passes = 0;

	//gnugo_play_move(move, m_Gameinfo.to_move);
	//sgffile_add_debuginfo(sgftree.lastnode, move_value);
	sgftreeAddPlay(&m_Sgftree, m_Gameinfo.to_move, STDPOS(x,y));
	//if (resignation_declined)
		//sgftreeAddComment(&sgftree, "GNU Go resignation was declined");
	//sgffile_output(&sgftree);
	m_Gameinfo.to_move = OTHER_COLOR(m_Gameinfo.to_move);
	m_iState1=1;
	if (m_iState == 1)//死活分析
	{
		CopyBoard();
		m_iState1 = 3;
		PaintBoard();
	}
	SetDlgItemText(IDC_STAT,"轮玩家着子");
	m_iStateNew = 0;
	m_iStateOpen = 0;
	m_iStateSave = 0;
	m_iStateReopen = 0;
	m_iStateArea = 0;
	m_iStateExit = 0;
	m_iStateResign = 0;
	this->InvalidateRect(m_rToolBox);
	if(passes>=2)//两次PASS，对弈结束
	{
		EndGame(&m_Gameinfo,0);
		m_iState1=0;
		//m_iColor=0;
		m_cmbMb.EnableWindow(TRUE);
		SetDlgItemText(IDC_STAT,"就绪");
		btnBz.SetWindowTextA("开始对弈");
		m_btnExit.SetWindowTextA("退  出");
	}
	//UpdateData(FALSE);
	m_bPicked = false;
	this->UpdateWindow();*/
	return 0;
}

int CSfcGoView::ComputerMove2()
{
	if (m_bPaused)//处理暂停
	{
		m_PauseStartTime = GetTickCount64();
		KillTimer(m_Gameinfo.to_move);
		m_iState1 = 3;
		m_iStateNew = 0;
		m_iStateOpen = 0;
		//if (m_iCombat == 0)
			m_iStateSave = 0;
		m_iStateReopen = 0;
		if(m_iCombat==0)
			m_iStateArea = 0;
		m_iStateExit = 0;
		m_iStateResign = 0;
		m_sOutputInfo = "对弈暂停";
		if (iLanguage == 0)
			m_sOutputInfo = "Game paused";
		InvalidateRect(m_rPlayInfo);
		InvalidateRect(m_rToolBox);
		pDlgNotify->DestroyWindow();
	}
	bool gameended = false;
	int move;
	int resign = 0;
	int resignation_declined = 0;
	int color = m_Gameinfo.to_move;
	int x = m_iCx, y=m_iCy;
	if (m_iState == 1)//死活分析
	{
		//m_iCx = -1, m_iCy = -1;
		int x1, y1, xs[361], ys[361];
		int count = GetLifeDeathAllowedMoves(m_iADColor, xs, ys);
		for (int i = 0; i < m_iAnaMoveCount; i++)
		{
			Trans(m_sAnaMoveRecs[i], x1, y1);
			int j;
			for (j = 0; j < count; j++)
			{
				if (x1 == xs[j] && y1 == ys[j])
					break;
			}
			if (j < count)
			{
				m_iCx = x1;
				m_iCy = y1;
				break;
			}
		}
		if (m_iCx >= 0 && m_iCx < m_iBoardSize)
		{
			if (m_iCx != x || m_iCy != y)
			{
				x = m_iCx, y = m_iCy;
				CString msg = "undo\r\n";
				m_pEngine1->WriteToPipe(msg);
				int count;
				CString* strs = m_pEngine1->GetMsg(count);
				msg = "play " + TransXY(m_iCx, m_iCy, color);
				msg += "\r\n";
				m_pEngine1->WriteToPipe(msg);
				count;
				strs = m_pEngine1->GetMsg(count);
				delete[] strs;
			}
		}
		else
		{
			KillTimer(color);
			CString msg = "解题成功！";
			if (iLanguage == 0)
				msg = "Resolved!";
			MessageBox(msg);
			m_iState1 = 12;
			m_iGoCountMax = m_iGoCount;
			m_cmbMb.EnableWindow(TRUE);
			m_sOutputInfo = "解题结束";
			if (iLanguage == 0)
				m_sOutputInfo = msg;
			InvalidateRect(m_rPlayInfo);
			m_iStateNew = 0;
			m_iStateOpen = 0;
			m_iStateSave = 0;
			m_iStateReopen = 0;
			m_iStateArea = 0;
			m_iStateExit = 0;
			m_iStateResign = 0;
			this->InvalidateRect(m_rToolBox);
			this->UpdateWindow();
			return 0;
		}
	}
	if (x < -2 || x >= m_iBoardSize)
	{
		CString msg = "获取着手出错!";
		if (iLanguage == 0)
			msg = "Sorry, We have a erro while getting moves.";
		MessageBox(msg);
		return 1;
	}
	if (x == -2)//resign
	{
		y = -2;
		m_GoRecord[m_iGoCount].x = -2;
		m_GoRecord[m_iGoCount].y = -2;
		m_GoRecord[m_iGoCount].color = color;
		m_iGoCount++;
		color == BLACK ? m_sMoveRecs[m_iMoveCount] = "B" : m_sMoveRecs[m_iMoveCount] = "W";
		m_sMoveRecs[m_iMoveCount] += " resign";
		m_sMoveTimeRecs[m_iMoveCount].Format("%02d:%02d:%02d", m_PeriodTime.GetHours(), m_PeriodTime.GetMinutes(), m_PeriodTime.GetSeconds());
		m_fMoveWinRates[m_iMoveCount] = color == BLACK ? m_fBlackWinRate : m_fWhiteWinRate;
		m_iMoveCount++;
		CString strresign = "腾飞围棋认输！";
		if (iLanguage == 0)
			strresign = "SfcGo resign!";
		if (m_bEngineDual)
		{
			int id = 0;
			if (iEngineId == 0)
				id = m_pEngine1->m_Id;
			else
				id = m_pEngine2->m_Id;
			strresign = sEngineNames[id] + "认输！";
			if (iLanguage == 0)
				strresign = sEngineNames[id] + "resign!";
		}
		else if (m_bSelfPlay)
		{
			if (color == BLACK)
			{
				strresign = "黑方认输！";
				if (iLanguage == 0)
					strresign = "Black resign!";
			}
			else
			{
				strresign = "白方认输！";
				if (iLanguage == 0)
					strresign = "White resign!";
			}
		}
		if (m_bEngineDual || m_bSelfPlay)
			PlaySound(strSysDirectry + "\\Alarm.wav", NULL, SND_ASYNC);
		MessageBox(strresign);
		resign = 1;
	}
	else
	{
		if (x == -1)//pass
		{
			KillTimer(color);
			y = -1;
			m_GoRecord[m_iGoCount].x = -1;
			m_GoRecord[m_iGoCount].y = -1;
			m_GoRecord[m_iGoCount].color = color;
			m_iGoCount++;
			color == BLACK ? m_sMoveRecs[m_iMoveCount] = "B" : m_sMoveRecs[m_iMoveCount] = "W";
			m_sMoveRecs[m_iMoveCount] += " pass";
			m_sMoveTimeRecs[m_iMoveCount].Format("%02d:%02d:%02d", m_PeriodTime.GetHours(), m_PeriodTime.GetMinutes(), m_PeriodTime.GetSeconds());
			m_fMoveWinRates[m_iMoveCount] = color == BLACK ? m_fBlackWinRate : m_fWhiteWinRate;
			m_iMoveCount++;
			m_iPasses++;
			if (m_iPasses < 2)
			{
				if (!m_bEngineDual && !m_bSelfPlay)
				{
					CString msg = "腾飞围棋PASS一手";
					if (iLanguage == 0)
						msg = "SfcGo played a pass move";
					MessageBox(msg);
				}
				CTime t = GetTickCount64();
				CTimeSpan ts = (t.GetTime() - m_StartTime.GetTime()) / 1000;
				if (color == 2)
					m_BlackTime = ts - m_WhiteTime;//m_BlackTime.GetSeconds
				else
					m_WhiteTime = ts - m_BlackTime;
				m_PeriodTime = CTimeSpan(0, 0, 0, 0);
				SetTimer(OTHER_COLOR(color), 1000, NULL);
			}
		}
		else
		{
			m_iPasses = 0;
			Sfc::PlayStone(x, y, color, m_GoInfo);
			if (bPickStoneSound && !m_bPaused)//拾子声
				PlaySound(strSysDirectry + "\\PickStone.wav", NULL, SND_SYNC);
			//PlaySound(strSysDirectry + "\\PickStone.wav", NULL, SND_ASYNC);
			m_iCx = x;
			m_iCy = y;
			m_iCcolor = color;
			if (bAnimate && !m_bPaused)//落子动画
			{
				iThreadState = 1;
				AfxBeginThread(StoneMove, this);
			}
			else
				AddStone(x, y, color);
		}
		if (m_bEngineDual)
		{
			SfcGtp* pengine;
			if (iEngineId == 1)
				pengine = m_pEngine1;
			else
				pengine = m_pEngine2;
			CString msg = "play " + TransXY(x, y, color);
			msg += "\r\n";
			pengine->WriteToPipe(msg);
			int count;
			CString* strs = pengine->GetMsg(count);
			delete[] strs;
		}
	}
	if(m_bPaused)
		m_iGoCountMax = m_iGoCount;
	//for (int i = 0; i < count; i++)
		//m_strOutput += strs[i] + "\n";
	/* Generate computer move. */
	//if (autolevel_on)
		//adjust_level_offset(m_Gameinfo.to_move);
	//move = genmove(m_Gameinfo.to_move, &move_value, &resign);

	/*examine_position1(EXAMINE_ALL, 0);
	//make_dragons1(0);
	move=83;
	move_value=75;
	resign=0;
	return 0;*/

	if (m_bResignation_allowed && resign) {
		if (m_bEngineDual || m_bSelfPlay)
			PlaySound(strSysDirectry + "\\Alarm.wav", NULL, SND_ASYNC);
		EndGame(&m_Gameinfo, 2);
		m_iState1 = 0;
		m_iGoCountMax = m_iGoCount;
		//m_iColor=0;
		m_cmbMb.EnableWindow(TRUE);
		SetDlgItemText(IDC_STAT, "就绪");
		btnBz.SetWindowTextA("开始对弈");
		m_btnExit.SetWindowTextA("退  出");

		/* The opponent declined resignation. Remember not to resign again. */
		//resignation_allowed = 0;
		//resignation_declined = 1;
		//m_sOutputInfo = "";
		InvalidateRect(m_rPlayInfo);
		m_iStateNew = 0;
		m_iStateOpen = 0;
		m_iStateSave = 0;
		m_iStateReopen = 0;
		m_iStateArea = 0;
		m_iStateExit = 0;
		m_iStateResign = 0;
		this->InvalidateRect(m_rToolBox);
		this->UpdateWindow();
		gameended = true;
	}

	//if (showscore) {
		//gnugo_estimate_score(&upper_bound, &lower_bound);
		//current_score_estimate = (int) ((lower_bound + upper_bound) / 2.0);
	//}

	//mprintf("%s(%d): %1m\n", color_to_string(m_Gameinfo.to_move),
		//movenum + 1, move);
	//if (is_pass(move))
		//(m_iPasses)++;
	//else
		//m_iPasses = 0;

	//gnugo_play_move(move, m_Gameinfo.to_move);
	//sgffile_add_debuginfo(sgftree.lastnode, move_value);
	sgftreeAddPlay(&m_Sgftree, m_Gameinfo.to_move, STDPOS(x, y));
	//if (resignation_declined)
		//sgftreeAddComment(&sgftree, "GNU Go resignation was declined");
	//sgffile_output(&sgftree);
	/*if (!is_pass(move))
	{
		Sfc::PlayStone(I(move),J(move),m_Gameinfo.to_move,m_GoInfo);
		AddStone(I(move),J(move),m_Gameinfo.to_move);
	}
	else if(m_iPasses<2)
	{
		MessageBox("腾飞围棋PASS一手");
	}*/
	if(!m_bPaused && !m_bSelfPlay && !m_bEngineDual && !gameended && !bAnimate)
		m_iState1 = 1;
	/*if (m_iState == 1)//死活分析
	{
		CopyBoard();
		m_iState1 = 3;
		PaintBoard();
	}*/
	SetDlgItemText(IDC_STAT, "轮玩家着子");
	/*m_sOutputInfo = "轮玩家着子";
	InvalidateRect(m_rPlayInfo);
	m_iStateNew = 0;
	m_iStateOpen = 0;
	m_iStateSave = 0;
	m_iStateReopen = 0;
	m_iStateArea = 0;
	m_iStateExit = 0;
	m_iStateResign = 0;
	this->InvalidateRect(m_rToolBox);*/
	if (m_iPasses >= 2)//两次PASS，对弈结束
	{
		m_iPasses = 0;
		EndGame(&m_Gameinfo, 0);
		m_iState1 = 0;
		m_iGoCountMax = m_iGoCount;
		//m_iColor=0;
		m_cmbMb.EnableWindow(TRUE);
		SetDlgItemText(IDC_STAT, "就绪");
		btnBz.SetWindowTextA("开始对弈");
		m_btnExit.SetWindowTextA("退  出");
		//m_sOutputInfo = "";
		InvalidateRect(m_rPlayInfo);
		m_iStateNew = 0;
		m_iStateOpen = 0;
		m_iStateSave = 0;
		m_iStateReopen = 0;
		m_iStateArea = 0;
		m_iStateExit = 0;
		m_iStateResign = 0;
		this->InvalidateRect(m_rToolBox);
		this->UpdateWindow();
		gameended = true;
	}
	else
		m_Gameinfo.to_move = OTHER_COLOR(m_Gameinfo.to_move);
	//UpdateData(FALSE);
	//m_iProgress = 0;
	m_bPicked = false;
	//this->UpdateWindow();
	if ((m_bSelfPlay || m_bEngineDual) && !gameended)
		AfxBeginThread(ComputerMoveThread, this);
	return 0;
}
//设置引擎棋盘大小
bool CSfcGoView::SetEngineBoardSize(int num)
{
	SfcGtp* pengine;
	if (iEngineId == 0)
		pengine = m_pEngine1;
	else
		pengine = m_pEngine2;
	CString str;
	str.Format("boardsize %d\r\n", num);
	pengine->WriteToPipe(str);
	int count;
	CString* strs = pengine->GetMsg(count);
	delete[] strs;
	return true;
}

bool CSfcGoView::ClearEngineBoard()
{
	SfcGtp* pengine;
	if (iEngineId == 0)
		pengine = m_pEngine1;
	else
		pengine = m_pEngine2;
	CString str = "clear_board\r\n";
	pengine->WriteToPipe(str);
	int count;
	CString* strs = pengine->GetMsg(count);
	delete[] strs;
	return true;
}

//设置棋力，0为最低
bool CSfcGoView::SetLevel(int level) const
{
	SfcGtp* pengine;
	if (iEngineId == 0)
		pengine = m_pEngine1;
	else
		pengine = m_pEngine2;
	int byotime = m_iComputerByoTime;
	if (m_bEngineDual && iEngineId != iBlackEngineId)
		byotime = m_iComputerByoTime2;
	CString str;
	CString* strs;
	int count;
	int serchthreads = 1;
	int visits = 1;
	//int playouts = 1;
	float maxtime = 0.1;
	switch (pengine->m_Id)
	{
	case 0://katago
		switch (level)
		{
		case 0:
			visits = 1;
			break;
		case 1:
			serchthreads = 1;
			visits = 1;
			//playouts = 2;
			maxtime = 0.1;
			break;
		case 2:
			visits = 1;
			break;
		case 3:
			visits = 1;
			break;
		case 4:
			visits = 1;
			break;
		case 5:
			visits = 1;
			break;
		case 6:
			visits = 1;
			break;
		case 7:
			visits = 1;
			break;
		case 8:
			visits = 1;
			break;
		case 9:
			visits = 1;
			break;
		case 10:
			visits = 1;
			break;
		case 11:
			serchthreads = 1;
			visits = 1;
			//playouts = 2;
			maxtime = 0.1;
			break;
		case 12:
			visits = 1;
			break;
		case 13://二段
			visits = 1;
			break;
		case 14://三段
			visits = 3;
			break;
		case 15://四段
			visits = 7;
			break;
		case 16://五段
			visits = 10;
			break;
		case 17://六段
			visits = 25;
			break;
		case 18://七段
			visits = 40;
			break;
		case 19://八段
			visits = 200;
			break;
		case 20://九段
			visits = 300;
			break;
		case 21://名人
			visits = 500;
			break;
		case 22://棋圣
			visits = 3000;
			break;
		case 23://棋灵王
			switch (byotime)
			{
			case 5:
				visits = 4000;
				break;
			case 15:
				visits = 10000;
				break;
			case 30:
				visits = 20000;
				break;
			case 60:
				visits = 40000;
				break;
			case 90:
				visits = 60000;
				break;
			case 120:
				visits = 100000;
				break;
			}
			break;
		}
		//str.Format("kata-set-param numSearchThreads %d\r\n", serchthreads);
		//pengine->WriteToPipe(str);
		//strs = pengine->GetMsg(count);
		str.Format("kata-set-param maxVisits %d\r\n", visits);
		pengine->WriteToPipe(str);
		strs = pengine->GetMsg(count);
		delete[] strs;
		//str.Format("kata-set-param maxPlayouts %d\r\n", playouts);
		//pengine->WriteToPipe(str);
		//strs = pengine->GetMsg(count);
		//str.Format("kata-set-param maxTime %f\r\n", maxtime);
		//pengine->WriteToPipe(str);
		//strs = pengine->GetMsg(count);
		break;
	case 1://leela
		switch (level)
		{
		case 0://五级
			visits = 1;
			break;
		case 1://四级
			visits = 3;
			break;
		case 2://三级
			visits = 5;
			break;
		case 3://二级
			visits = 9;
			break;
		case 4://一级
			visits = 14;
			break;
		case 5://业一
			visits = 22;
			break;
		case 6://业二
			visits = 30;
			break;
		case 7://业三
			visits = 34;
			break;
		case 8://业四
			visits = 38;
			break;
		case 9://业五
			visits = 46;
			break;
		case 10://业六
			visits = 5;
			break;
		case 11://业七
			visits = 10;
			break;
		case 12://初段
			visits = 15;
			break;
		case 13://二段
			visits = 25;
			break;
		case 14://三段
			visits = 35;
			break;
		case 15://四段
			visits = 200;
			break;
		case 16://五段
			visits = 300;
			break;
		case 17://六段
			visits = 600;
			break;
		case 18://七段
			visits = 3000;
			break;
		case 19://八段
			visits = 6000;
			break;
		case 20://九段
			visits = 10000;
			break;
		case 21://名人
			visits = 22000;
			break;
		case 22://棋圣
			visits = 25000;
			break;
		case 23://棋灵王
			visits = 30000;
			break;
		}
		str.Format("lz-setoption name visits value %d\r\n", visits);
		pengine->WriteToPipe(str);
		strs = pengine->GetMsg(count);
		delete[] strs;
		break;
	}
	return true;
}

bool CSfcGoView::SetRule(int ruleid)
{
	SfcGtp* pengine;
	if (iEngineId == 0)
		pengine = m_pEngine1;
	else
		pengine = m_pEngine2;
	if (pengine->m_Id != 0)
		return false;
	CString str = "kata-set-rules ";
	switch (ruleid)
	{
	case 0:
		str += "chinese\r\n";
		break;
	case 1:
		str += "japanese\r\n";
		break;
	case 2:
		str += "korean\r\n";
		break;
	}
	int count;
	CString* strs = nullptr;
	if (iEngineId == 0)
	{
		pengine->WriteToPipe(str);
		strs = pengine->GetMsg(count);
	}
	else
	{
		pengine->WriteToPipe(str);
		strs = pengine->GetMsg(count);
	}
	delete[] strs;
	return true;
}

//设置引擎时间，分别是规定时间、读秒时间、读秒时间内须走步数
bool CSfcGoView::SetTimes(int maintime, int byotime, int stones)
{
	SfcGtp* pengine;
	if (iEngineId == 0)
		pengine = m_pEngine1;
	else
		pengine = m_pEngine2;
	CString str;
	str.Format("time_settings %d %d %d\r\n", maintime, byotime, stones);
	pengine->WriteToPipe(str);
	int count;
	CString* strs = pengine->GetMsg(count);
	delete[] strs;
	return true;
}

//设置引擎固定让子
bool CSfcGoView::SetEngineFixedHandicap(int handicap)
{
	if (handicap < 2 || handicap>9)
		return false;
	SfcGtp* pengine;
	if (iEngineId == 0)
		pengine = m_pEngine1;
	else
		pengine = m_pEngine2;
	CString str;
	str.Format("fixed_handicap %d\r\n", handicap);
	pengine->WriteToPipe(str);
	int count;
	CString* strs = pengine->GetMsg(count);
	delete[] strs;
	return true;
}

//设置棋盘大小
bool CSfcGoView::SetBoardSize(int num)
{
	iBoardSizeState=0;
	if(num==13)
		iBoardSizeState=1;
	else if(num==19)
		iBoardSizeState=2;
	iBoardSize=num;
	m_iBoardSize=num;
	/* Init board. */
	//board_size = num;
	ClearBoard();
	m_GoInfo.Init(num);
	SfcGtp* pengine;
	if (iEngineId == 0)
		pengine = m_pEngine1;
	else
		pengine = m_pEngine2;
	CString str;
	str.Format("boardsize %d\r\n", iBoardSize);
	pengine->WriteToPipe(str);
	int count;
	CString* strs = pengine->GetMsg(count);
	delete[] strs;
	/* In case max handicap changes on smaller board. */
	/*if(m_iState==2)
	{
		m_Gameinfo.handicap = place_fixed_handicap(m_Gameinfo.handicap);
		sgfOverwritePropertyInt(sgftree.root, "SZ", board_size);
		sgfOverwritePropertyInt(sgftree.root, "HA", m_Gameinfo.handicap);
	}*/
	return true;
}

//设置让子数
bool CSfcGoView::SetHandicap(int num)
{
	  /* Init board. */
	  ClearBoard();
	  //if (num == 0)
		//  SetKomi(6.5);
	  //else
		//  SetKomi(0);
	  if (num == 1)
		  num = 0;
	  m_iHandiCap = num;
	  m_Gameinfo.handicap = num;
	  m_iFixedStone = num;
	  if (num >= 2 && num <= 9)
	  {
		  SfcGtp* pengine;
		  if (iEngineId == 0)
			  pengine = m_pEngine1;
		  else
			  pengine = m_pEngine2;
		  CString str;
		  str.Format("fixed_handicap %d\r\n", num);
		  pengine->WriteToPipe(str);
		  int count;
		  CString* strs = pengine->GetMsg(count);
		  for (int i = 0; i < count; i++)
		  {
			  if (strs[i].Left(1) == "=")
			  {
				  int count1;
				  CString* strs1 = SfcGtp::SplitString(strs[i], " ", count1);
				  for (int j = 1; j < count1; j++)
				  {
					  if (strs1[j].GetLength() >= 2)
					  {
						  int x, y;
						  Trans(strs1[j], x, y);
						  int color = 2;//Always black
						  Sfc::PlayStone(x, y, color, m_GoInfo);
						  //m_iBoard[x][y] = color;
						  AddStone(x, y, color);
					  }
				  }
			  }
		  }
		  delete[] strs;
	  }
	  //PaintBoard();
	  /* Place stones on board but don't record sgf
	   * in case we change more info. */
	  if (num >= 2)
		  m_Gameinfo.to_move = 1;
	  else
		  m_Gameinfo.to_move = 2;
      //m_Gameinfo.to_move = (m_Gameinfo.handicap ? WHITE : BLACK);
	  //CopyBoard();
	  return true;
}

bool CSfcGoView::SetKomi(float komi)
{
	m_fKomi = komi;
	SfcGtp* pengine;
	if (iEngineId == 0)
		pengine = m_pEngine1;
	else
		pengine = m_pEngine2;
	CString str;
	str.Format("komi %3.1f\r\n", m_fKomi);
	pengine->WriteToPipe(str);
	int count;
	CString* strs = pengine->GetMsg(count);
	delete[] strs;
	return true;
}
//从引擎复制棋盘
void CSfcGoView::CopyBoard()
{
	SfcGtp* pengine;
	if (iEngineId == 0)
		pengine = m_pEngine1;
	else
		pengine = m_pEngine2;
	CString str = "showboard\r\n";
	pengine->WriteToPipe(str);
	int count;
	CString* strs = pengine->GetMsg(count);
	for (int i = 0; i < count; i++)
	{
		if (strs[i].Left(10) == "   A B C D")
		{
			i++;
			for (int j = 0; j < 19; j++)
			{
				for (int k = 0; k < 19; k++)
				{
					if (strs[i+j][3+k*2] == '.')
						m_iBoard[k][j] = 0;
					else if (strs[i + j][3 + k * 2] == 'X')
						m_iBoard[k][j] = BLACK;
					else
						m_iBoard[k][j] = WHITE;
				}
			}
			break;
		}
	}
	delete[] strs;
	for (int i = 0; i < m_iBoardSize; i++)
		for (int j = 0; j < m_iBoardSize; j++)
			m_GoInfo.board[i][j] = m_iBoard[i][j];
	/*m_GoInfo.Init(m_iBoardSize);
	for (int i = 0; i < m_iGoCount; i++)
	{
		Sfc::PlayStone(m_GoRecord[i].x, m_GoRecord[i].y, m_GoRecord[i].color, m_GoInfo);
		AddStone(m_GoRecord[i].x, m_GoRecord[i].y, m_GoRecord[i].color);
		//int x = m_GoRecord[i].x;
		//m_iBoard[m_GoRecord[i].x][m_GoRecord[i].y] = m_GoRecord[i].color;
	}*/
	//for(int i=0;i<m_iBoardSize;i++)
	//{
		//for(int j=0;j<m_iBoardSize;j++)
			//m_iBoard[i][j]=board[POS(i,j)];
	//}
}

void CSfcGoView::OnCbnSelchangeCmbmb()
{
	UpdateData(TRUE);
	if (m_iState == 1)//死活分析
	{
		if (m_iMb == 0)
			m_iColor = 2;
		else
			m_iColor = 1;
		m_bAnaed = false;
	}
	if(m_iState==2)
	{
		if (m_iMb == m_iHandiCap || m_iMb>9)
			return;
		if(m_iState1>0)
		{
			MessageBox("不能在对弈中改变让子数！");
			return;
		}
		SetHandicap(m_iMb);
		PaintBoard();
	}
	UpdateData(FALSE);
}

//PASS一手
int CSfcGoView::DoPass()
{
  m_iPasses++;
  //InitSgf(&m_Gameinfo);
  //gnugo_play_move(PASS_MOVE, m_Gameinfo.to_move);
  //sgffile_add_debuginfo(sgftree.lastnode, 0.0);
  //sgftreeAddPlay(&sgftree, m_Gameinfo.to_move, -1, -1);
  //sgffile_output(&sgftree);

  /*if (force) {
    m_Gameinfo->computer_player = OTHER_COLOR(m_Gameinfo->computer_player);
    sgftreeAddComment(&sgftree, "forced");
    return 0;
  }*/
  if (m_iPasses >= 2)//两次PASS，对弈结束
  {
	  m_iState1 = 0;
	  EndGame(&m_Gameinfo, 0);
	  m_iGoCountMax = m_iGoCount;
	  //m_sOutputInfo = "";
	  InvalidateRect(m_rPlayInfo);
	  this->InvalidateRect(m_rToolBox);
	  this->UpdateWindow();
  }
  else
  {
	  m_Gameinfo.to_move = OTHER_COLOR(m_Gameinfo.to_move);
	  ComputerMove();
  }
  return 1;
}


//设置贴目
void CSfcGoView::OnMKomi()
{
	DlgSetKomi dlg;
	dlg.m_fKomi=m_fKomi;
	if(dlg.DoModal()==IDOK)
	{
		if (m_fKomi != dlg.m_fKomi)
			SetKomi(dlg.m_fKomi);
	}
}


void CSfcGoView::OnUpdateMKomi(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!(m_iState==2 && m_iGoCount>0));
}

//从SGF数据获取着手
void CSfcGoView::GetSgfMove(SGFProperty* prop, int& x, int& y, int& color)
{
	if (strlen(prop->value) < 2)
	{
		x = -1;
		y = -1;
	}
	else
	{
		x = prop->value[0] - 'a';
		y = prop->value[1] - 'a';
	}
	if (x < -1 || x>=m_iBoardSize)
	{
		x = -1;
		y = -1;
	}
	color = prop->name == SGFAB ? BLACK : WHITE;
}

//放置让子
void CSfcGoView::PlaceFixedHandicap(int handicap)
{
	if (handicap < 2)
		return;
	/*m_iBoard[3][15] = BLACK;
	m_iBoard[15][3] = BLACK;
	if (handicap >= 3)
		m_iBoard[3][3] = BLACK;
	if (handicap >= 4)
		m_iBoard[15][15] = BLACK;
	if (handicap == 5 || handicap == 7 || handicap == 9)
		m_iBoard[9][9] = BLACK;
	if (handicap >= 6)
	{
		m_iBoard[9][3] = BLACK;
		m_iBoard[9][15] = BLACK;
	}
	if (handicap >= 8)
	{
		m_iBoard[3][9] = BLACK;
		m_iBoard[15][9] = BLACK;
	}*/
	m_iGoCount = 0;
	m_GoRecord[m_iGoCount].x = 3;
	m_GoRecord[m_iGoCount].y = 15;
	m_GoRecord[m_iGoCount].color = BLACK;
	m_iGoCount++;
	m_GoRecord[m_iGoCount].x = 15;
	m_GoRecord[m_iGoCount].y = 3;
	m_GoRecord[m_iGoCount].color = BLACK;
	m_iGoCount++;
	if (handicap >= 3)
	{
		m_GoRecord[m_iGoCount].x = 3;
		m_GoRecord[m_iGoCount].y = 3;
		m_GoRecord[m_iGoCount].color = BLACK;
		m_iGoCount++;
	}
	if (handicap >= 4)
	{
		m_GoRecord[m_iGoCount].x = 15;
		m_GoRecord[m_iGoCount].y = 15;
		m_GoRecord[m_iGoCount].color = BLACK;
		m_iGoCount++;
	}
	if (handicap == 5 || handicap == 7 || handicap == 9)
	{
		m_GoRecord[m_iGoCount].x = 9;
		m_GoRecord[m_iGoCount].y = 9;
		m_GoRecord[m_iGoCount].color = BLACK;
		m_iGoCount++;
	}
	if (handicap >= 6)
	{
		m_GoRecord[m_iGoCount].x = 9;
		m_GoRecord[m_iGoCount].y = 3;
		m_GoRecord[m_iGoCount].color = BLACK;
		m_iGoCount++;
		m_GoRecord[m_iGoCount].x = 9;
		m_GoRecord[m_iGoCount].y = 15;
		m_GoRecord[m_iGoCount].color = BLACK;
		m_iGoCount++;
	}
	if (handicap >= 8)
	{
		m_GoRecord[m_iGoCount].x = 3;
		m_GoRecord[m_iGoCount].y = 9;
		m_GoRecord[m_iGoCount].color = BLACK;
		m_iGoCount++;
		m_GoRecord[m_iGoCount].x = 15;
		m_GoRecord[m_iGoCount].y = 9;
		m_GoRecord[m_iGoCount].color = BLACK;
		m_iGoCount++;
	}
	m_iFixedStone = handicap;
}
//从GoRecord转换为SGFTree
int CSfcGoView::GoRecordToSgf(int gocount, Data_GoRecord gorecord[], int fixedstone, SGFTree* tree)
{
	sgfFreeNode(tree->root);
	sgftree_clear(tree);
	//sgftreeCreateHeaderNode(tree, iBoardSize, m_fKomi, m_iHandiCap);
	CreateSgfHead(tree, iBoardSize, m_fKomi, m_iHandiCap);
	//sgf_write_header(m_Sgftree.root, 1, iRandomSeed, m_fKomi,
		//m_iHandiCap, iLevel, iRule);
	for(int i=0;i<fixedstone;i++)
		sgftreeAddStone(tree, gorecord[i].color, STDPOS(gorecord[i].x, gorecord[i].y));
	for(int i=fixedstone;i<gocount;i++)
		sgftreeAddPlay(tree, gorecord[i].color, STDPOS(gorecord[i].x, gorecord[i].y));
	//sgfAddStone
	return 0;
}

//从SGFTree转换为GoRecord
int CSfcGoView::SgfToGoRecord(SGFTree* tree, int& gocount, Data_GoRecord gorecord[], int& fixedstone)
{
	m_bSfcSgfLoaded = false;
  int bs;
  int next = BLACK;
  int untilmove = -1; //* Neither a valid move nor pass. 
  int until = 9999;
  CString str;
  char* cs;
  int x,y,color;
  gocount=0;
  fixedstone=0;
  
  if (!sgfGetIntProperty(tree->root, "SZ", &bs))
    bs = 19;

  if (bs>19 || bs<0)
    return EMPTY;
  m_iBoardSize = bs;

  int handicap = 0;
  if (sgfGetIntProperty(tree->root, "HA", &handicap) && handicap > 1)
    next = WHITE;
  m_Gameinfo.handicap = handicap;
  //PlaceFixedHandicap(m_Gameinfo.handicap);
  //gocount = handicap;
  //fixedstone = handicap;
  if (handicap > bs * bs - 1 || handicap < 0) {
    //gprintf(" Handicap HA[%d] is unreasonable.\n Modify SGF file.\n",
	  //  handicap);
    return EMPTY;
  }
  
  //gnugo_clear_board(bs);

  if (!sgfGetFloatProperty(tree->root, "KM", &m_fKomi)) {
    if (m_Gameinfo.handicap == 0)
      m_fKomi = 6.5;
    else
      m_fKomi = 0.0;
  }

  m_Gameinfo.game_name = "";
  m_Gameinfo.game_comment = "";
  if (sgfGetCharProperty(tree->root, "GN", &cs))
	  m_Gameinfo.game_name = cs;
  if (sgfGetCharProperty(tree->root, "C ", &cs))
	  m_Gameinfo.game_comment = cs;
  for (tree->lastnode = NULL; sgftreeForward(tree);) {
    SGFProperty *prop;
    //int move;
      
    for (prop = tree->lastnode->props; prop; prop = prop->next) {
      //DEBUG(DEBUG_LOADSGF, "%c%c[%s]\n", prop->name & 0xff, (prop->name >> 8), prop->value);
      switch (prop->name) {
	  //case SGFGN:
		//  m_Gameinfo.game_name = prop->value;
		  //break;
	  case SGFEV:
		  str = prop->value;
		  if (str == "Combat")
			  m_iCombat = 1;
		  else
			  m_iCombat = 0;
		  break;
	  case SGFRU:
		  str = prop->value;
		  if (str == "Japanese")
			  iRule = 1;
		  else if (str == "Korean")
			  iRule = 2;
		  else
			  iRule = 0;
		  break;
	  case SGFPB://对弈黑方信息
	  case SGFPW://对弈白方信息
	  {
		  bool bsfcsgfloaded = GetSgfPlayerInfo(prop);
		  m_bSfcSgfLoaded = m_bSfcSgfLoaded || bsfcsgfloaded;
	  }
		  break;
	  case SGFRE://对弈结果
		  m_bGameOver = true;
		  m_sResult = prop->value;
		  break;
      case SGFAB://固定黑子
      case SGFAW://固定白子
		GetSgfMove(prop, x, y, color);
		gorecord[gocount].x=x;
		gorecord[gocount].y=y;
		gorecord[gocount].color=color;
		gocount++;
		fixedstone++;
		break;
	      
      case SGFPL://待着手方
	if (prop->value[0] == 'w'
	    || prop->value[0] == 'W'
	    || prop->value[0] == '2')
	  next = WHITE;
	else
	  next = BLACK;
	/*if (next == WHITE) {
	  PlaceFixedHandicap(m_Gameinfo.handicap);
	  sgfOverwritePropertyInt(tree->root, "HA", handicap);
	  fixedstone += handicap;
	}*/
	break;
	      
      case SGFW://白方着手
      case SGFB://黑方着手
	next = prop->name == SGFW ? WHITE : BLACK;
	/*if (next == WHITE) {
	  PlaceFixedHandicap(m_Gameinfo.handicap);
	  sgfOverwritePropertyInt(tree->root, "HA", handicap);
	  fixedstone = handicap;
	}*/

	/*move = get_sgfmove(prop);
	if (move == untilmove || movenum == until - 1) {
	  m_Gameinfo.to_move = next;
	  sgftreeBack(tree);
	  return next;
	}

	move = rotate1(move, 0);
	x=I(move);
	y=J(move);*/
	GetSgfMove(prop, x, y, color);
	color=next;
	gorecord[gocount].x = x;
	gorecord[gocount].y = y;
	gorecord[gocount].color = color;
	gocount++;
	next = OTHER_COLOR(next);
	/*if (move == PASS_MOVE || board[move] == EMPTY) {
	  gnugo_play_move(move, next);
		gorecord[gocount].x=x;
		gorecord[gocount].y=y;
		gorecord[gocount].color=color;
		gocount++;
	  next = OTHER_COLOR(next);
	}
	else {
	  gprintf("WARNING: Move off board or on occupied position found in sgf-file.\n");
	  gprintf("Move at %1m ignored, trying to proceed.\n", move);
	  m_Gameinfo.to_move = next;
	  return next;
	}*/

	break;

	  case SGFPT://单步用时
		  m_sMoveTimeRecs[gocount - fixedstone - 1] = prop->value;
		  break;
	  case SGFMS://着手得分
		  m_fMoveWinRates[gocount - fixedstone - 1] = atof(prop->value);
		  break;
	  case SGFSS://着手标准分
		  m_fStdMoveWinRates[gocount - fixedstone - 1] = atof(prop->value);
		  break;

      case SGFIL:
	/*move = rotate1(get_sgfmove(prop), 0);

	if (board_size > 1)
	{
	  int move_color;

	  if (ON_BOARD(NORTH(move)))
	    move_color = OTHER_COLOR(board[NORTH(move)]);
	  else 
	    move_color = OTHER_COLOR(board[SOUTH(move)]);
	  if (is_ko(move, move_color, NULL))
	    board_ko_pos = move;
	}*/
	break;
      }
    }
  }
  m_Gameinfo.to_move = next;
  return next;
}

//清除棋盘
void CSfcGoView::ClearBoard()
{
	SfcGtp* pengine;
	if (iEngineId == 0)
		pengine = m_pEngine1;
	else
		pengine = m_pEngine2;
	//clear_board();
	m_iGoCount=0;
	m_iRecallStartId=0;
	m_iFixedStone = 0;
	for(int i=0;i<m_iBoardSize;i++)
	{
		for(int j=0;j<m_iBoardSize;j++)
			m_iBoard[i][j]=0;
	}
	m_GoInfo.Init(m_iBoardSize);
	if (pengine != nullptr)
	{
		CString str = "clear_board\r\n";
		pengine->WriteToPipe(str);
		int count;
		CString* strs = pengine->GetMsg(count);
		delete[] strs;
	}
	//UpdateData(FALSE);
}

//计算当color方在x,y处落子时可能出现的提子，strs存储了被提的棋块信息，返回值为被提到棋块数
int CSfcGoView::DoCapture(int pos, int color, int captures[])
{
	//int pos=POS(x,y);
	int other = OTHER_COLOR(color);
	int n=0;

	//ASSERT1(board[pos] == EMPTY, pos);
	//worm[pos].liberties
	//string[0].color=0;

	/*if (board[SOUTH(pos)] == other && worm[SOUTH(pos)].liberties == 1)
	{
		for(int i=BOARDMIN;i<BOARDMAX;i++)
		{
			if(worm[i].origin==worm[SOUTH(pos)].origin)
			{
				captures[n]=i;
				n++;
			}
		}
	}

	if (board[WEST(pos)] == other && worm[WEST(pos)].liberties == 1)
	{
		for(int i=BOARDMIN;i<BOARDMAX;i++)
		{
			if(worm[i].origin==worm[WEST(pos)].origin)
			{
				captures[n]=i;
				n++;
			}
		}
	}

	if (board[NORTH(pos)] == other && worm[NORTH(pos)].liberties == 1)
	{
		for(int i=BOARDMIN;i<BOARDMAX;i++)
		{
			if(worm[i].origin==worm[NORTH(pos)].origin)
			{
				captures[n]=i;
				n++;
			}
		}
	}

	if (board[EAST(pos)] == other && worm[EAST(pos)].liberties == 1)
	{
		for(int i=BOARDMIN;i<BOARDMAX;i++)
		{
			if(worm[i].origin==worm[EAST(pos)].origin)
			{
				captures[n]=i;
				n++;
			}
		}
	}

	if(n>0)
	{
		for(int i=0;i<n;i++)
			remove_stone(captures[i]);
	}*/
	return n;
}

//死活攻击，maxsizepos-要攻击的棋块，scount-可下着手点数，smoves-可下着手点，maxmoves-分析出的最佳着手点，mcounts-本轮需分析的着手点数，将从可下着手点中随机抽取，
//sdepth-分析深度，max_sdepth-最大分析深度，达到时递归函数将返回；返回值-总着手值
int CSfcGoView::LifeDeathAttack(int maxsizepos, int scount, int smoves[100], int color, int maxmoves[100], int mcounts[100], int sdepth, int max_sdepth)
{
	int totalvalue=0,maxmovevalue=-1;
	int maxmoves1[100];
	int mcount=mcounts[sdepth];
	int *moves=(int*)calloc(mcount,sizeof(int));
	//获取所有合法着手
	int scount1=0,smoves1[100];
	/*for (int i = 0; i<scount; i++)
	{
		if(is_legal(smoves[i],color))
		{
			smoves1[scount1]=smoves[i];
			scount1++;
		}
	}
	//产生本轮着手
	if(scount1>mcount)
	{
		//随机抽取本轮着手
		for(int i=0;i<mcount;i++)
		{
			do
			{
				int pos=smoves1[rand()%scount1];
				bool b=false;
				for(int j=0;j<i;j++)
				{
					if(pos==moves[j])
					{
						b=true;
						break;
					}
				}
				if(!b)
				{
					moves[i]=pos;
					break;
				}
			}while(true);
		}
	}
	else
	{
		mcount=scount1;
		for(int i=0;i<mcount;i++)
			moves[i]=smoves1[i];
	}
	for(int i=0;i<mcount;i++)
	{
		//计算可能的提子
		int captures[BOARDMAX];
		int capture_num=do_capture(moves[i],color,captures);
		add_stone(moves[i],color);
		int movevalue,testmove=-1;
		if(sdepth==max_sdepth)
		{
			//silent_examine_position(EXAMINE_DRAGONS_WITHOUT_OWL);
			int testresult,testkworm;
			movevalue=owl_attack(maxsizepos,&testmove,&testresult,&testkworm);
		}
		else
		{
			int smoves2[100];
			for(int j=0;j<scount;j++)
				smoves2[j]=smoves[j];
			int scount2=scount;
			if(capture_num>0)
			{
				for(int j=0;j<capture_num;j++)
					smoves2[scount2+j]=captures[j];
				scount2+=capture_num;
			}
			movevalue=LifeDeathAttack1(maxsizepos,scount2,smoves2,OTHER_COLOR(color),maxmoves1,mcounts,sdepth+1,max_sdepth);
		}
		totalvalue+=movevalue;
		remove_stone(moves[i]);
		for(int j=0;j<capture_num;j++)
			add_stone(captures[j],OTHER_COLOR(color));
		if(movevalue>maxmovevalue)
		{
			maxmovevalue=movevalue;
			maxmoves[sdepth]=moves[i];
			for(int j=sdepth+1;j<=max_sdepth;j++)
				maxmoves[j]=maxmoves1[j];
			if(sdepth==max_sdepth)
				maxmoves[max_sdepth+1]=testmove;
			if(maxmovevalue>=5)
				break;
		}
	}*/
	free(moves);
	return maxmovevalue;
}

//死活攻击1，轮到防守方着手，但不同于死活防守函数，maxsizepos-要攻击的棋块，scount-可下着手点数，smoves-可下着手点，maxmoves-分析出的最佳着手点，
//mcounts-本轮需分析的着手点数，将从可下着手点中随机抽取，sdepth-分析深度，max_sdepth-最大分析深度，达到时递归函数将返回
int CSfcGoView::LifeDeathAttack1(int maxsizepos, int scount, int smoves[100], int color, int maxmoves[100], int mcounts[100], int sdepth, int max_sdepth)
{
	int totalvalue=0,minmovevalue=100000000;
	int maxmoves1[100];
	int mcount=mcounts[sdepth];
	/*int* moves = (int*)calloc(mcount, sizeof(int));
	//获取所有合法着手
	int scount1=0,smoves1[100];
	for(int i=0;i<scount;i++)
	{
		if(is_legal(smoves[i],color))
		{
			smoves1[scount1]=smoves[i];
			scount1++;
		}
	}
	//产生本轮着手
	if(scount1>mcount)
	{
		//随机抽取本轮着手
		for(int i=0;i<mcount;i++)
		{
			do
			{
				int pos=smoves1[rand()%scount1];
				bool b=false;
				for(int j=0;j<i;j++)
				{
					if(pos==moves[j])
					{
						b=true;
						break;
					}
				}
				if(!b)
				{
					moves[i]=pos;
					break;
				}
			}while(true);
		}
	}
	else
	{
		mcount=scount1;
		for(int i=0;i<mcount;i++)
			moves[i]=smoves1[i];
	}
	for(int i=0;i<mcount;i++)
	{
		//计算可能的提子
		int captures[BOARDMAX];
		int capture_num=do_capture(moves[i],color,captures);
		add_stone(moves[i],color);
		int movevalue,testmove=-1;
		if(sdepth==max_sdepth)
		{
			//silent_examine_position(EXAMINE_DRAGONS_WITHOUT_OWL);
			int testresult,testkworm;
			movevalue=owl_attack(maxsizepos,&testmove,&testresult,&testkworm);
		}
		else
		{
			int smoves2[100];
			for(int j=0;j<scount;j++)
				smoves2[j]=smoves[j];
			int scount2=scount;
			if(capture_num>0)
			{
				for(int j=0;j<capture_num;j++)
					smoves2[scount2+j]=captures[j];
				scount2+=capture_num;
			}
			movevalue=LifeDeathAttack(maxsizepos,scount2,smoves2,OTHER_COLOR(color),maxmoves1,mcounts,sdepth+1,max_sdepth);
		}
		totalvalue+=movevalue;
		remove_stone(moves[i]);
		for(int j=0;j<capture_num;j++)
			add_stone(captures[j],OTHER_COLOR(color));
		if(movevalue<minmovevalue)
		{
			minmovevalue=movevalue;
			maxmoves[sdepth]=moves[i];
			for(int j=sdepth+1;j<=max_sdepth;j++)
				maxmoves[j]=maxmoves1[j];
			if(sdepth==max_sdepth)
				maxmoves[max_sdepth+1]=testmove;
			if(minmovevalue<5)
				break;
		}
	}
	free(moves);*/
	return minmovevalue;
}

//死活防守，maxsizepos-要防守的棋块，scount-可下着手点数，smoves-可下着手点，maxmoves-分析出的最佳着手点，mcounts-本轮需分析的着手点数，将从可下着手点中随机抽取，
//sdepth-分析深度，max_sdepth-最大分析深度，达到时递归函数将返回
int CSfcGoView::LifeDeathDefend(int maxsizepos, int scount, int smoves[100], int color, int maxmoves[100], int mcounts[100], int sdepth, int max_sdepth)
{
	int totalvalue=0,maxmovevalue=-1;
	int maxmoves1[100];
	int mcount=mcounts[sdepth];
	/*int* moves = (int*)calloc(mcount, sizeof(int));
	//获取所有合法着手
	int scount1=0,smoves1[100];
	for(int i=0;i<scount;i++)
	{
		if(is_legal(smoves[i],color))
		{
			smoves1[scount1]=smoves[i];
			scount1++;
		}
	}
	//产生本轮着手
	if(scount1>mcount)
	{
		//随机抽取本轮着手
		for(int i=0;i<mcount;i++)
		{
			do
			{
				int pos=smoves1[rand()%scount1];
				bool b=false;
				for(int j=0;j<i;j++)
				{
					if(pos==moves[j])
					{
						b=true;
						break;
					}
				}
				if(!b)
				{
					moves[i]=pos;
					break;
				}
			}while(true);
		}
	}
	else
	{
		mcount=scount1;
		for(int i=0;i<mcount;i++)
			moves[i]=smoves1[i];
	}
	for(int i=0;i<mcount;i++)
	{
		//计算可能的提子
		int captures[BOARDMAX];
		int capture_num=do_capture(moves[i],color,captures);
		add_stone(moves[i],color);
		int movevalue;
		if(sdepth==max_sdepth)
		{
			//silent_examine_position(EXAMINE_DRAGONS_WITHOUT_OWL);
			int testmove,testresult,testkworm;
			movevalue=owl_defend(maxsizepos,&testmove,&testresult,&testkworm);
		}
		else
		{
			int smoves2[100];
			for(int j=0;j<scount;j++)
				smoves2[j]=smoves[j];
			int scount2=scount;
			if(capture_num>0)
			{
				for(int j=0;j<capture_num;j++)
					smoves2[scount2+j]=captures[j];
				scount2+=capture_num;
			}
			movevalue=LifeDeathDefend1(maxsizepos,scount2,smoves2,OTHER_COLOR(color),maxmoves1,mcounts,sdepth+1,max_sdepth);
		}
		totalvalue+=movevalue;
		remove_stone(moves[i]);
		for(int j=0;j<capture_num;j++)
			add_stone(captures[j],OTHER_COLOR(color));
		if(movevalue>maxmovevalue)
		{
			maxmovevalue=movevalue;
			maxmoves[sdepth]=moves[i];
			for(int j=sdepth+1;j<=max_sdepth;j++)
				maxmoves[j]=maxmoves1[j];
			if(maxmovevalue>=5)
				break;
		}
	}
	free(moves);*/
	return maxmovevalue;
}

//死活防守1，轮到攻击方着手，但不同于死活攻击函数，maxsizepos-要攻击的棋块，scount-可下着手点数，smoves-可下着手点，maxmoves-分析出的最佳着手点，
//mcounts-本轮需分析的着手点数，将从可下着手点中随机抽取，sdepth-分析深度，max_sdepth-最大分析深度，达到时递归函数将返回
int CSfcGoView::LifeDeathDefend1(int maxsizepos, int scount, int smoves[100], int color, int maxmoves[100], int mcounts[100], int sdepth, int max_sdepth)
{
	int totalvalue=0,minmovevalue=100000000;
	int maxmoves1[100];
	int mcount=mcounts[sdepth];
	/*int* moves = (int*)calloc(mcount, sizeof(int));
	//获取所有合法着手
	int scount1=0,smoves1[100];
	for(int i=0;i<scount;i++)
	{
		if(is_legal(smoves[i],color))
		{
			smoves1[scount1]=smoves[i];
			scount1++;
		}
	}
	//产生本轮着手
	if(scount1>mcount)
	{
		//随机抽取本轮着手
		for(int i=0;i<mcount;i++)
		{
			do
			{
				int pos=smoves1[rand()%scount1];
				bool b=false;
				for(int j=0;j<i;j++)
				{
					if(pos==moves[j])
					{
						b=true;
						break;
					}
				}
				if(!b)
				{
					moves[i]=pos;
					break;
				}
			}while(true);
		}
	}
	else
	{
		mcount=scount1;
		for(int i=0;i<mcount;i++)
			moves[i]=smoves1[i];
	}
	for(int i=0;i<mcount;i++)
	{
		//计算可能的提子
		int captures[BOARDMAX];
		int capture_num=do_capture(moves[i],color,captures);
		add_stone(moves[i],color);
		int movevalue;
		if(sdepth==max_sdepth)
		{
			//silent_examine_position(EXAMINE_DRAGONS_WITHOUT_OWL);
			int testmove,testresult,testkworm;
			movevalue=owl_defend(maxsizepos,&testmove,&testresult,&testkworm);
		}
		else
		{
			int smoves2[100];
			for(int j=0;j<scount;j++)
				smoves2[j]=smoves[j];
			int scount2=scount;
			if(capture_num>0)
			{
				for(int j=0;j<capture_num;j++)
					smoves2[scount2+j]=captures[j];
				scount2+=capture_num;
			}
			movevalue=LifeDeathDefend(maxsizepos,scount2,smoves2,OTHER_COLOR(color),maxmoves1,mcounts,sdepth+1,max_sdepth);
		}
		totalvalue+=movevalue;
		remove_stone(moves[i]);
		for(int j=0;j<capture_num;j++)
			add_stone(captures[j],OTHER_COLOR(color));
		if(movevalue<minmovevalue)
		{
			minmovevalue=movevalue;
			maxmoves[sdepth]=moves[i];
			for(int j=sdepth+1;j<=max_sdepth;j++)
				maxmoves[j]=maxmoves1[j];
			if(minmovevalue<5)
				break;
		}
	}
	free(moves);*/
	return minmovevalue;
}


void CSfcGoView::OnBnClickedRadinturn()
{
	m_bInTurn=true;
}

float CSfcGoView::GetScore()
{
	SfcGtp* pengine;
	if (iEngineId == 0)
		pengine = m_pEngine1;
	else
		pengine = m_pEngine2;
	CString str = "final_score\r\n";
	pengine->WriteToPipe(str);
	m_strOutput += str;
	int count;
	CString* strs = pengine->GetMsg(count);
	for (int i = 0; i < count; i++)
	{
		if (strs[i].GetLength() > 3 && strs[i][0] == '=')
		{
			str = strs[i].Right(strs[i].GetLength() - 2).Trim();
			break;
		}
	}
	delete[] strs;
	CString str1 = str.Right(str.GetLength() - 2);
	float result = atof(str1);
	if (str[0] == 'B')
		result = -result;
	UpdateData(FALSE);
	return result;
}


void CSfcGoView::OnBnClickedBtnscore()
{
	float result = GetScore();
	CString str = "";
	if (result > 0)
		str += "白胜";
	else if (result < 0)
		str += "黑胜";
	else
		str += "平局";
	if (result != 0)
	{
		CString str1;
		str1.Format("%5.1f目", abs(result));
		str += str1;
	}
	MessageBox(str, "判断结果");
}


void CSfcGoView::RecordBoard(SGFNode* node)
{
	int i, j;

	if (node)
		for (i = 0; i < iBoardSize; i++)
			for (j = 0; j < iBoardSize; j++)
				if (m_iBoard[i][j] == BLACK)
					sgfAddStone(node, BLACK, STDPOS(i, j));
}

/*
 * Write sgf root node.
 */

void CSfcGoView::InitSgf(Gameinfo* ginfo)
{
	if (m_bSgf_initialized)
		return;
	m_bSgf_initialized = true;

	//sgf_write_header(m_Sgftree.root, 1, iRandomSeed, m_fKomi,
		//ginfo->handicap, iLevel, iRule);
	if (ginfo->handicap > 0)
		RecordBoard(m_Sgftree.root);
}

/* Communicates with user after a game has ended. */
int CSfcGoView::EndGame(Gameinfo* ginfo, int reason)
{
	//char line[80];
	//char *line_ptr;
	//char *command;
	KillTimer(ginfo->to_move);
	char* tmpstring;
	int state = 0;
	CString str, str1;
	float result;
	bool win = false;
	if (reason == 0) {		/* Two passes, game is over. */
		//who_wins(ginfo->computer_player, stdout);
		//printf("\nIf you disagree, we may count the game together.\n");

		//str.Format("数目结果：\n白棋%5.1f，黑棋%5.1f",white_score,-black_score);
		result = GetScore();//(m_fWhiteScore+m_fBlackScore)/2.0;
		sgftreeWriteResult(&m_Sgftree, result, 1);
		str = "数目结果：";
		if (result == 0.0)
			str1 = "双方和棋";
		else if (result > 0.0)
		{
			str1.Format("白胜%5.1f目。", result);
			if (m_iColor == WHITE)
				win = true;
		}
		else
		{
			str1.Format("黑胜%5.1f目。", -result);
			if (m_iColor == BLACK)
				win = true;
		}
		if (iLanguage == 0)
		{
			str = "Result:";
			if (result == 0.0)
				str1 = "Draw";
			else if (result > 0.0)
			{
				str1.Format("White win %5.1f.", result);
				if (m_iColor == WHITE)
					win = true;
			}
			else
			{
				str1.Format("Black win %5.1f.", -result);
				if (m_iColor == BLACK)
					win = true;
			}
		}
		str += str1;
	}
	else {
		int color = OTHER_COLOR(ginfo->to_move);
		if (m_bSelfPlay || m_bEngineDual)
		{
			if (color == BLACK)
				str = "黑中盘获胜！";
			else
				str = "白中盘获胜！";
		}
		else
		{
			if (reason == 1)		/* Our opponent has resigned. */
				//printf("GNU Go wins by resignation.\n");
				str = "腾飞围棋中盘获胜！";
			else
			{			/* We have resigned. */
				//printf("You win by resignation.\n");
				str = "玩家中盘获胜！";
				win = true;
			}
		}
		if (iLanguage == 0)
		{
			if (m_bSelfPlay || m_bEngineDual)
			{
				if (color == BLACK)
					str = "Black win!";
				else
					str = "White win!";
			}
			else
			{
				if (reason == 1)		/* Our opponent has resigned. */
					//printf("GNU Go wins by resignation.\n");
					str = "SfcGo win!";
				else
				{			/* We have resigned. */
					//printf("You win by resignation.\n");
					str = "Player win!";
					win = true;
				}
			}
		}
		//printf("Result: %c+Resign\n\n", color == WHITE ? 'W' : 'B');
		sgftreeWriteResult(&m_Sgftree, color == WHITE ? 1000.0 : -1000.0, 1);
	}
	m_bGameOver = true;
	m_sOutputInfo = "对弈结束，" + str;
	if (iLanguage == 0)
		m_sOutputInfo = "Game end, " + str;
	if (m_bSelfPlay || m_bEngineDual)
		win = false;
	if(win)
		PlaySound(strSysDirectry + "\\Win.wav", NULL, SND_ASYNC);
	if (win && m_iCombat == 1)
	{
		MessageBox(str);
		iPlayerLevel++;
		Sfc::WriteSysIni();
		PlaySound(strSysDirectry + "\\LevelUp.wav", NULL, SND_ASYNC);
		str = "恭喜！你已成功晋升为" + GetLevelFullTitle(iLevel) + "！";
		if(iLanguage==0)
			str="Congratulation! You have level up to " + GetLevelFullTitle(iLevel) + "!";
		MessageBox(str);
		str = "Save game record?";
	}
	else
	{
		str1 = "\n是否保存为棋谱？";
		if (iLanguage == 0)
			str1 = "\nSave game record?";
		str += str1;
	}
	if (AfxMessageBox(str, MB_YESNO) == IDYES)
	{
		char sgfFilters[255];
		//if (iLanguage == 0)
			strcpy(sgfFilters, "Go record file (*.sgf)|*.sgf|All Files (*.*)|*.*||");
		//else
			//strcpy(sgfFilters, "棋谱文件 (*.sgf)|*.sgf|All Files (*.*)|*.*||");
		CFileDialog filedlg(FALSE, "", ".sgf", OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, sgfFilters);
		if (filedlg.DoModal() == IDOK)
		{
			CString fileName = filedlg.GetPathName();//.GetFileName();
			tmpstring = fileName.GetBuffer();
			if (tmpstring) {
				/* discard newline */
				//tmpstring[strlen(tmpstring) - 1] = 0;
				//InitSgf(ginfo);
				SgfSaveData(&m_Sgftree);
				writesgf(m_Sgftree.root, tmpstring);
				//保存胜率数据
				if (fileName.Right(4) == ".sgf")
					fileName = fileName.Left(fileName.GetLength() - 4);
				fileName += ".wrt";
				SaveWinRate(fileName);
				m_iStateSave = 3;
			}
		}
	}
	m_iCombat = 0;
	/*while (state == 0) {
		printf("You may optionally save the game as an SGF file.\n\n");
		printf("Type \"save <filename>\" to save,\n");
		if (reason == 0)
			printf("     \"count\" to recount,\n");
		else if (reason == 2)
			printf("     \"continue\" to decline resignation and continue the game,\n");
		printf("     \"quit\" to quit\n");
		printf(" or  \"game\" to play again\n");

		line_ptr = line;
		if (!fgets(line, 80, stdin))
			break;

		command = strtok(line_ptr, "");
		switch (get_command(command)) {
		case CMD_SAVE:
			strtok(command, " ");
			tmpstring = strtok(NULL, " ");
			if (tmpstring) {
				/* discard newline */
				/*tmpstring[strlen(tmpstring) - 1] = 0;
				init_sgf(ginfo);
				writesgf(sgftree.root, tmpstring);
			}
			else
				printf("Please specify filename\n");
			break;

		case COUNT:
			if (reason == 0)
				ascii_count(ginfo);
			break;

		case CONTINUE:
			state = -1;
			break;

		case NEW:
			state = 1;
			break;

		case QUIT:
			state = 2;
			break;

		default:
			state = 0;
		}
	}*/

	return state;
}

void CSfcGoView::GameinfoClear(Gameinfo* ginfo)
{
	ClearBoard();
	ginfo->handicap = 0;
	ginfo->to_move = BLACK;
	sgfFreeNode(m_Sgftree.root);
	sgfFreeNode(ginfo->game_record.root);
	sgftree_clear(&ginfo->game_record);

	/* Info relevant to the computer player. */
	ginfo->computer_player = WHITE; /* Make an assumption. */
}


void CSfcGoView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CSingleLock sl(&csCs);
	int threadstate = 0;
	sl.Lock();
	threadstate = iThreadState;
	sl.Unlock();
	if (threadstate == 1)//电脑正在移动棋子
	{
		if (point.x >= m_BoardRect.left - m_iGap && point.x <= m_BoardRect.right + m_iGap && point.y > m_BoardRect.top - m_iGap && point.y < m_BoardRect.bottom + m_iGap)
		{
			if (m_iCcolor == 1)
				SetCursor(m_hWhiteCursor);
			else if (m_iCcolor == 2)
				SetCursor(m_hBlackCursor);
		}
	}
	else
	{
		if (m_iState == 2 && m_iState1 == 1 || m_iState==1 && (m_iState1==1 || m_iState1==11 || m_iState1==13) && !m_bAnswered || m_iState==3 && m_iState1==21)
		{
			//if (m_iState1 == 1)//轮玩家着子
			//{
				if (!m_bPicked)
					m_bMouseMoveCount++;
				if (m_bMouseMoveCount >= 2)
				{
					if(bPickStoneSound)
						PlaySound(strSysDirectry + "\\PickStone.wav", NULL, SND_ASYNC);
					//AfxBeginThread(PlayStoneSound, NULL);
					m_bPicked = true;
					m_bMouseMoveCount = 0;
				}
				if (m_rBoardBack.PtInRect(point))//(point.x >= m_BoardRect.left - m_iGap && point.x <= m_BoardRect.right + m_iGap && point.y > m_BoardRect.top - m_iGap && point.y < m_BoardRect.bottom + m_iGap)
				{
					if (m_bPicked)
					{
						if (m_iColor == 1)
							SetCursor(m_hWhiteCursor);
						else if (m_iColor == 2)
							SetCursor(m_hBlackCursor);
					}
					/*else if (m_bMouseMoveCount >= 2)
					{
						if (m_iColor == 1)
							SetCursor(m_hWhiteCursor);
						else if (m_iColor == 2)
							SetCursor(m_hBlackCursor);
					}*/
				}
			//}
		}
		//if (m_rToolBox.PtInRect(point))//准备处理按钮
		//{
			//新局/PASS/黑先按钮
		if (m_iState1 == 11 || m_iState1==12 || m_iState1==14)
		{
			if (m_rBlackFirst.PtInRect(point))
			{
				if (m_iStateBlackFirst == 0)
				{
					m_iStateBlackFirst = 1;
					PaintButton(20);
				}
			}
			else
			{
				if (m_iStateBlackFirst == 1)
				{
					m_iStateBlackFirst = 0;
					PaintButton(20);
				}
			}
			if (m_rWhiteFirst.PtInRect(point))
			{
				if (m_iStateWhiteFirst == 0)
				{
					m_iStateWhiteFirst = 1;
					PaintButton(21);
				}
			}
			else
			{
				if (m_iStateWhiteFirst == 1)
				{
					m_iStateWhiteFirst = 0;
					PaintButton(21);
				}
			}
		}
		else
		{
			if (m_rNew.PtInRect(point))
			{
				if (m_iStateNew == 0)
				{
					m_iStateNew = 1;
					PaintButton(0);
				}
			}
			else
			{
				if (m_iStateNew == 1)
				{
					m_iStateNew = 0;
					PaintButton(0);
				}
			}
		}
			//打开棋谱/悔棋按钮
			if (m_rOpen.PtInRect(point))
			{
				if (m_iStateOpen == 0)
				{
					m_iStateOpen = 1;
					PaintButton(1);
				}
			}
			else
			{
				if (m_iStateOpen == 1)
				{
					m_iStateOpen = 0;
					PaintButton(1);
				}
			}
			//保存棋谱/支招按钮
			if (m_rSave.PtInRect(point))
			{
				if (m_iStateSave == 0)
				{
					m_iStateSave = 1;
					PaintButton(2);
				}
			}
			else
			{
				if (m_iStateSave == 1)
				{
					m_iStateSave = 0;
					PaintButton(2);
				}
			}
			//暂停/继续棋局按钮
			if (m_rReopen.PtInRect(point))
			{
				if (m_iStateReopen == 0)
				{
					m_iStateReopen = 1;
					PaintButton(3);
				}
			}
			else
			{
				if (m_iStateReopen == 1)
				{
					m_iStateReopen = 0;
					PaintButton(3);
				}
			}
			//形势判断按钮
			if (m_rArea.PtInRect(point))
			{
				if (m_iStateArea == 0)
				{
					m_iStateArea = 1;
					PaintButton(4);
				}
			}
			else
			{
				if (m_iStateArea == 1)
				{
					m_iStateArea = 0;
					PaintButton(4);
				}
			}
			//退出/交换按钮
			if (m_rExit.PtInRect(point))
			{
				if (m_iStateExit == 0)
				{
					m_iStateExit = 1;
					PaintButton(5);
				}
			}
			else
			{
				if (m_iStateExit == 1)
				{
					m_iStateExit = 0;
					PaintButton(5);
				}
			}
			if (m_iState == 2 && m_iState1 > 0 && m_iState1<3)
			{
				//认输按钮
				if (m_rResign.PtInRect(point))
				{
					if (m_iStateResign == 0)
					{
						m_iStateResign = 1;
						PaintButton(6);
					}
				}
				else
				{
					if (m_iStateResign == 1)
					{
						m_iStateResign = 0;
						PaintButton(6);
					}
				}
			}
			else if (m_iState1 == 11)//摆放黑子/白子按钮
			{
				if (m_rPutBlack.PtInRect(point))
				{
					if (m_iStatePutBlack == 0)
					{
						m_iStatePutBlack = 1;
						PaintButton(22);
					}
				}
				else
				{
					if (m_iStatePutBlack == 1)
					{
						m_iStatePutBlack = 0;
						PaintButton(22);
					}
				}
				if (m_rPutWhite.PtInRect(point))
				{
					if (m_iStatePutWhite == 0)
					{
						m_iStatePutWhite = 1;
						PaintButton(23);
					}
				}
				else
				{
					if (m_iStatePutWhite == 1)
					{
						m_iStatePutWhite = 0;
						PaintButton(23);
					}
				}
			}
			else
			{
				//回到最初按钮
				if (m_rGoFirst.PtInRect(point))
				{
					if (m_iStateGoFirst == 0)
					{
						m_iStateGoFirst = 1;
						PaintButton(10);
					}
				}
				else
				{
					if (m_iStateGoFirst == 1)
					{
						m_iStateGoFirst = 0;
						PaintButton(10);
					}
				}
				//后退五步按钮
				if (m_rGoFiveBack.PtInRect(point))
				{
					if (m_iStateGoFiveBack == 0 || m_iStateGoFiveBack==2)
					{
						m_iStateGoFiveBack = 1;
						PaintButton(11);
					}
				}
				else
				{
					if (m_iStateGoFiveBack == 1 || m_iStateGoFiveBack == 2)
					{
						m_iStateGoFiveBack = 0;
						PaintButton(11);
					}
				}
				//后退按钮
				if (m_rGoBack.PtInRect(point))
				{
					if (m_iStateGoBack == 0 || m_iStateGoBack==2)
					{
						m_iStateGoBack = 1;
						PaintButton(12);
					}
				}
				else
				{
					if (m_iStateGoBack == 1 || m_iStateGoBack == 2)
					{
						m_iStateGoBack = 0;
						PaintButton(12);
					}
				}
				//前进按钮
				if (m_rGoForward.PtInRect(point))
				{
					if (m_iStateGoForward == 0 || m_iStateGoForward==2)
					{
						m_iStateGoForward = 1;
						PaintButton(13);
					}
				}
				else
				{
					if (m_iStateGoForward == 1 || m_iStateGoForward == 2)
					{
						m_iStateGoForward = 0;
						PaintButton(13);
					}
				}
				//前进五步按钮
				if (m_rGoFiveForward.PtInRect(point))
				{
					if (m_iStateGoFiveForward == 0 || m_iStateGoFiveForward==2)
					{
						m_iStateGoFiveForward = 1;
						PaintButton(14);
					}
				}
				else
				{
					if (m_iStateGoFiveForward == 1 || m_iStateGoFiveForward == 2)
					{
						m_iStateGoFiveForward = 0;
						PaintButton(14);
					}
				}
				//前进到底按钮
				if (m_rGoLast.PtInRect(point))
				{
					if (m_iStateGoLast == 0)
					{
						m_iStateGoLast = 1;
						PaintButton(15);
					}
				}
				else
				{
					if (m_iStateGoLast == 1)
					{
						m_iStateGoLast = 0;
						PaintButton(15);
					}
				}
			}
		//}
		if (m_bDifficulty)//处于死活练习难度选择状态
		{
			//手筋练习按钮
			if(m_rTesuji.PtInRect(point))
			{
				if (m_iStateTesuji == 0)
				{
					m_iStateTesuji = 1;
					PaintButton(16);
				}
			}
			else
			{
				if (m_iStateTesuji == 1)
				{
					m_iStateTesuji = 0;
					PaintButton(16);
				}
			}
			//初级死活按钮
			if (m_rElementary.PtInRect(point))
			{
				if (m_iStateElemantary == 0)
				{
					m_iStateElemantary = 1;
					PaintButton(17);
				}
			}
			else
			{
				if (m_iStateElemantary == 1)
				{
					m_iStateElemantary = 0;
					PaintButton(17);
				}
			}
			//中级死活按钮
			if (m_rMiddle.PtInRect(point))
			{
				if (m_iStateMiddle == 0)
				{
					m_iStateMiddle = 1;
					PaintButton(18);
				}
			}
			else
			{
				if (m_iStateMiddle == 1)
				{
					m_iStateMiddle = 0;
					PaintButton(18);
				}
			}
			//高级死活按钮
			if (m_rAdvanced.PtInRect(point))
			{
				if (m_iStateAdvanced == 0)
				{
					m_iStateAdvanced = 1;
					PaintButton(19);
				}
			}
			else
			{
				if (m_iStateAdvanced == 1)
				{
					m_iStateAdvanced = 0;
					PaintButton(19);
				}
			}
		}
	}
	/*//处理MouseHover
	TRACKMOUSEEVENT tme = { 0 };
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_HOVER | TME_LEAVE;
	tme.dwHoverTime = 50;
	tme.hwndTrack = this->m_hWnd;
	if (TrackMouseEvent(&tme)) {}*/
	CFormView::OnMouseMove(nFlags, point);
}


BOOL CSfcGoView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//SetCursor(m_hBlackCursor);

	return CFormView::OnSetCursor(pWnd, nHitTest, message);
}


void CSfcGoView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//按钮操作
	if (m_rToolBox.PtInRect(point))
	{
		if (m_iStateNew == 2 && m_rNew.PtInRect(point))//按下新局/PASS按钮
		{
			if (m_iState == 1 && m_iState1 == 0 || m_iState == 2 && (m_iState1 == 0 || m_iState1 == 3) || m_iState == 3 && m_iState1 == 0)
				OnNew();
			else if (m_iState == 1)//查看死活题答案
				OnSolution();
			else if (m_iState1 == 22)//全盘分析
				OnAnaAll();
			else
				OnPass();
		}
		if (m_iStateOpen == 2 && m_rOpen.PtInRect(point))//按下打开棋谱/悔棋按钮
		{
			if (m_iState == 1 && (m_iState1==0 || m_iState1==12 || m_iState1 == 14) || m_iState == 2 && (m_iState1 == 0 || m_iState1 == 3) || m_iState == 3 && (m_iState1 == 0 || m_iState1==22))
				OnOpen();
			else if (m_iState==1 && m_iState1==11 || m_iState == 3)//保存
				OnSave();
			else//悔棋
				OnRetract();
		}
		if (m_iStateSave == 2 && m_rSave.PtInRect(point))//按下保存棋谱/支招按钮
		{
			if (m_iState == 2 && (m_iState1 == 0 || m_iState1 == 3))//保存
				OnSave();
			else if (m_iState == 3)//序盘研究时AI分析
				OnPersistenceAna();
			else if (m_iState == 1 && m_iState1 == 0)//继续上次的死活题
				OnContinueQuest();
			else if (m_iState1 == 11 || m_iState1 == 12 || m_iState1 == 14)//研究
				OnStudy();
			else if (m_iState == 1 && (m_iState1==1 || m_iState1==13))//死活题时重做按钮
				OnRedo();
			else//人机对弈时AI支招按钮
				OnHint();
		}
		if (m_iStateReopen == 2 && m_rReopen.PtInRect(point))//按下暂停/继续按钮
		{
			if (m_iState == 2 && (m_iState1 == 0 || m_iState1 == 3))
				OnReopen();
			else if (m_iState == 1 && m_iState1 == 0)//按下难度选择按钮
				OnDifficulty();
			else if (m_iState1 == 11 || m_iState1 == 12 || m_iState1 == 14)//开始解题
				OnNew();
			else if (m_iState == 1 && m_iState1 == 1)//研究
			{
				OnReturn();
				OnStudy();
			}
			else if (m_iState1 == 13)//做题
			{
				OnReturn();
				OnNew();
			}
			else
				OnPause();
		}
		if (m_iStateArea == 2 && m_rArea.PtInRect(point))//按下形势判断按钮
		{
			if (m_iState == 1)//死活题时AI分析按钮
				OnLifeDeathAna();
			else
				OnArea();
		}
		if (m_iStateExit == 2 && m_rExit.PtInRect(point))//按下退出/交换对局按钮
		{
			if (m_iState == 1 && m_iState1==0 || m_iState == 2 && (m_iState1 == 0 || m_iState1 == 3) || m_iState == 3 && m_iState1 == 0)
				OnExit();
			else if (m_iState==1 || m_iState == 3)//返回
				OnReturn();
			else
				OnChangeStone();
		}
		if (m_iStateResign == 2 && m_rResign.PtInRect(point))//按下认输按钮
		{
			OnResign();
		}
		if (m_iStateGoFirst == 2 && m_rGoFirst.PtInRect(point))//按下回到最初按钮
		{
			OnGoFirst();
		}
		if (m_iStateGoFiveBack == 2 && m_rGoFiveBack.PtInRect(point))//按下后退五步按钮
		{
			OnGoFiveBack();
		}
		if (m_iStateGoBack == 2 && m_rGoBack.PtInRect(point))//按下后退按钮
		{
			OnGoBack();
		}
		if (m_iStateGoForward == 2 && m_rGoForward.PtInRect(point))//按下前进按钮
		{
			OnGoForward();
		}
		if (m_iStateGoFiveForward == 2 && m_rGoFiveForward.PtInRect(point))//按下前进五步按钮
		{
			OnGoFiveForward();
		}
		if (m_iStateGoLast == 2 && m_rGoLast.PtInRect(point))//按下前进到底按钮
		{
			OnGoLast();
		}
		if (m_iStateBlackFirst == 2 && m_rBlackFirst.PtInRect(point))//按下黑先按钮
		{
			OnBlackFirst();
		}
		if (m_iStateWhiteFirst == 2 && m_rWhiteFirst.PtInRect(point))//按下白先按钮
		{
			OnWhiteFirst();
		}
		if (m_iStatePutBlack == 2 && m_rPutBlack.PtInRect(point))//按下摆放黑子按钮
		{
			OnPutBlack();
		}
		if (m_iStatePutWhite == 2 && m_rPutWhite.PtInRect(point))//按下摆放白子按钮
		{
			OnPutWhite();
		}
	}
	else if ((m_iState1 == 5 || m_iState1==6) && m_rAnaMove.PtInRect(point))//分析着手查看
	{
		int id = (point.y - m_rAnaMove.top) / m_iMoveRecHeight + m_iAnaMoveStartId;
		if (id != m_iAnaMoveId || m_iState1==5)
		{
			m_iAnaMoveId = id;
			ShowAnaMove();
			InvalidateRect(m_rMoveRec);
			UpdateWindow();
		}
	}
	if (m_iState == 1 && m_iState1 == 0)//改变死活题难度按钮
	{
		if (m_iStateTesuji == 1 && m_rTesuji.PtInRect(point))//按下手筋练习按钮
			ChangeDiffculty(0);
		if (m_iStateElemantary == 1 && m_rElementary.PtInRect(point))//按下初级死活按钮
			ChangeDiffculty(1);
		if (m_iStateMiddle == 1 && m_rMiddle.PtInRect(point))//按下中级死活按钮
			ChangeDiffculty(2);
		if (m_iStateAdvanced == 1 && m_rAdvanced.PtInRect(point))//按下高级死活按钮
			ChangeDiffculty(3);
	}
	CFormView::OnLButtonUp(nFlags, point);
}


void CSfcGoView::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*if (m_iStateNew != 1 && m_rNew.PtInRect(point))
	{
		m_iStateNew = 1;
		PaintButton(0);
	}*/
	CFormView::OnMouseHover(nFlags, point);
}

void CSfcGoView::PaintButton(int buttonid)
{
	CDC* pDC = GetDC();
	pDC->SetStretchBltMode(HALFTONE);
	switch (buttonid)
	{
	case 0:
		if (m_iState == 2 && (m_iState1 == 0 || m_iState1 == 3))//新局按钮
		{
			switch (m_iStateNew)
			{
			case 0:
				imNewNormal.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 1:
				imNewHover.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 2:
				imNewDown.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 3:
				imNewDisable.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			}
		}
		else if (m_iState == 1 && m_iState1 == 0)//摆子出题按钮
		{
			switch (m_iStateNew)
			{
			case 0:
				imPutStoneNormal.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 1:
				imPutStoneHover.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 2:
				imPutStoneDown.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 3:
				imPutStoneDisable.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			}
		}
		else if (m_iState == 3 && m_iState1 == 0)//摆子研究按钮
		{
			switch (m_iStateNew)
			{
			case 0:
				imPutStoneStudyNormal.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 1:
				imPutStoneStudyHover.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 2:
				imPutStoneStudyDown.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 3:
				imPutStoneStudyDisable.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			}
		}
		else if (m_iState1 == 22 || m_iOldState1==22)//全盘分析按钮
		{
			switch (m_iStateNew)
			{
			case 0:
				imAnaAllNormal.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 1:
				imAnaAllHover.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 2:
				imAnaAllDown.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 3:
				imAnaAllDisable.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			}
		}
		else if (m_iState1 == 11 || m_iState1==12 || m_iState1 == 14)//死活摆子或读谱时不显示此按钮
		{

		}
		else if (m_iState == 1)//死活题查看答案按钮
		{
			switch (m_iStateNew)
			{
			case 0:
				imSolutionNormal.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 1:
				imSolutionHover.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 2:
				imSolutionDown.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 3:
				imSolutionDisable.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			}
		}
		else if (m_iState == 1 || m_iState == 3)//PASS一手按钮
		{
			switch (m_iStateNew)
			{
			case 0:
				imPassMoveNormal.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 1:
				imPassMoveHover.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 2:
				imPassMoveDown.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 3:
				imPassMoveDisable.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			}
		}
		else//PASS按钮
		{
			switch (m_iStateNew)
			{
			case 0:
				imPassNormal.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 1:
				imPassHover.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 2:
				imPassDown.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			case 3:
				imPassDisable.Draw(pDC->GetSafeHdc(), m_rNew);
				break;
			}
		}
		break;
	case 1:
		if (m_iState==1 && (m_iState1==0 || m_iState1==12) || m_iState == 2 && (m_iState1 == 0 || m_iState1 == 3) || m_iState==3 && (m_iState1==0 || m_iState1==22))//打开棋谱
		{
			if (iLanguage == 1 && m_iState == 2 && (m_iState1 == 0 || m_iState1==3))//显示“旧的回忆按钮”
			{
				switch (m_iStateOpen)
				{
				case 0:
					imOpenNormal0.Draw(pDC->GetSafeHdc(), m_rOpen);
					break;
				case 1:
					imOpenHover0.Draw(pDC->GetSafeHdc(), m_rOpen);
					break;
				case 2:
					imOpenDown0.Draw(pDC->GetSafeHdc(), m_rOpen);
					break;
				case 3:
					imOpenDisable0.Draw(pDC->GetSafeHdc(), m_rOpen);
					break;
				}
			}
			else//显示“打开棋谱按钮”
			{
				switch (m_iStateOpen)
				{
				case 0:
					imOpenNormal.Draw(pDC->GetSafeHdc(), m_rOpen);
					break;
				case 1:
					imOpenHover.Draw(pDC->GetSafeHdc(), m_rOpen);
					break;
				case 2:
					imOpenDown.Draw(pDC->GetSafeHdc(), m_rOpen);
					break;
				case 3:
					imOpenDisable.Draw(pDC->GetSafeHdc(), m_rOpen);
					break;
				}
			}
		}
		else if (m_iState1==11 || m_iState1 == 21 || m_iState==3 && (m_iState1==4 || m_iState1==5 || m_iState1==6))//摆子状态显示保存按钮
		{
			switch (m_iStateOpen)
			{
			case 0:
				imSaveNormal.Draw(pDC->GetSafeHdc(), m_rOpen);
				break;
			case 1:
				imSaveHover.Draw(pDC->GetSafeHdc(), m_rOpen);
				break;
			case 2:
				imSaveDown.Draw(pDC->GetSafeHdc(), m_rOpen);
				break;
			case 3:
				imSaveDisable.Draw(pDC->GetSafeHdc(), m_rOpen);
				break;
			}
		}
		else if (m_iState1 == 14)//做题主界面不显示此按钮
		{

		}
		else//悔棋按钮
		{
			switch (m_iStateOpen)
			{
			case 0:
				imRetractNormal.Draw(pDC->GetSafeHdc(), m_rOpen);
				break;
			case 1:
				imRetractHover.Draw(pDC->GetSafeHdc(), m_rOpen);
				break;
			case 2:
				imRetractDown.Draw(pDC->GetSafeHdc(), m_rOpen);
				break;
			case 3:
				imRetractDisable.Draw(pDC->GetSafeHdc(), m_rOpen);
				break;
			}
		}
		break;
	case 2:
		if (m_iState == 2 && (m_iState1 == 0 || m_iState1 == 3))//保存棋谱
		{
			switch (m_iStateSave)
			{
			case 0:
				imSaveNormal.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			case 1:
				imSaveHover.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			case 2:
				imSaveDown.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			case 3:
				imSaveDisable.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			}
		}
		else if (m_iState == 1 && m_iState1 == 0)//继续做题
		{
			switch (m_iStateSave)
			{
			case 0:
				imContinueNormal.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			case 1:
				imContinueHover.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			case 2:
				imContinueDown.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			case 3:
				imContinueDisabel.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			}
		}
		else if (m_iState1 == 11 || m_iState1 == 12 || m_iState1 == 14)//死活题研究按钮
		{
			switch (m_iStateSave)
			{
			case 0:
				imStudyNormal.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			case 1:
				imStudyHover.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			case 2:
				imStudyDown.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			case 3:
				imStudyDisable.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			}
		}
		else if (m_iState1 == 21 || m_iState1 == 22 || m_iState == 3 && (m_iState1==4 || m_iState1 == 5 || m_iState1 == 6))//AI分析按钮
		{
			switch (m_iStateSave)
			{
			case 0:
				imAIanaNormal.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			case 1:
				imAIanaHover.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			case 2:
				imAIanaDown.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			case 3:
				imAIanaDisable.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			}
		}
		else if (m_iState == 1 && (m_iState1 == 1 || m_iState1 == 2 || m_iState1==13))//死活解题时显示重做按钮
		{
			switch (m_iStateSave)
			{
			case 0:
				imRedoNormal.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			case 1:
				imRedoHover.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			case 2:
				imRedoDown.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			case 3:
				imRedoDisable.Draw(pDC->GetSafeHdc(), m_rSave);
				break;
			}
		}
		else if (m_iState==1 || m_iState == 3 && m_iState1 == 0)//序盘研究主界面不显示此按钮
		{

		}
		else//支招按钮
		{
			if (m_iState1 == 5 || m_iState1 == 6)
			{
				switch (m_iStateSave)
				{
				case 0:
					imReturnNormal.Draw(pDC->GetSafeHdc(), m_rSave);
					break;
				case 1:
					imReturnHover.Draw(pDC->GetSafeHdc(), m_rSave);
					break;
				case 2:
					imReturnDown.Draw(pDC->GetSafeHdc(), m_rSave);
					break;
				case 3:
					imReturnDisabel.Draw(pDC->GetSafeHdc(), m_rSave);
					break;
				}
			}
			else
			{
				switch (m_iStateSave)
				{
				case 0:
					imHintNormal.Draw(pDC->GetSafeHdc(), m_rSave);
					break;
				case 1:
					imHintHover.Draw(pDC->GetSafeHdc(), m_rSave);
					break;
				case 2:
					imHintDown.Draw(pDC->GetSafeHdc(), m_rSave);
					break;
				case 3:
					imHintDisable.Draw(pDC->GetSafeHdc(), m_rSave);
					break;
				}
			}
		}
		break;
	case 3://暂停/继续棋局按钮
		if (m_iState == 2 && (m_iState1 == 0 || m_iState1 == 3))//继续
		{
			switch (m_iStateReopen)
			{
			case 0:
				imReopenNormal.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			case 1:
				imReopenHover.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			case 2:
				imReopenDown.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			case 3:
				imReopenDisable.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			}
		}
		else if (m_iState == 1 && m_iState1 == 0)//死活练习难度选择
		{
			switch (m_iStateReopen)
			{
			case 0:
				imDifficultyNormal.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			case 1:
				imDifficultyHover.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			case 2:
				imDifficultyDown.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			case 3:
				imDifficultyDisable.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			}
		}
		else if (m_iState1 == 11 || m_iState1 == 12 || m_iState1 == 14)//死活分析开始做题按钮
		{
			switch (m_iStateReopen)
			{
			case 0:
				imSolveNormal.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			case 1:
				imSolveHover.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			case 2:
				imSolveDown.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			case 3:
				imSolveDisable.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			}
		}
		else if (m_iState == 1 && (m_iState1 == 1 || m_iState1 == 2))//死活分析做题时显示研究按钮
		{
			switch (m_iStateReopen)
			{
			case 0:
				imStudyNormal2.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			case 1:
				imStudyHover2.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			case 2:
				imStudyDown2.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			case 3:
				imStudyDisable2.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			}
		}
		else if (m_iState1 == 13)//死活分析研究时显示做题按钮
		{
			switch (m_iStateReopen)
			{
			case 0:
				imSolveNormal2.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			case 1:
				imSolveHover2.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			case 2:
				imSolveDown2.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			case 3:
				imSolveDisable2.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			}
		}
		else if (m_iState==1 || m_iState == 3)//序盘研究主界面不显示此按钮
		{

		}
		else
		{
			switch (m_iStateReopen)
			{
			case 0:
				imPauseNormal.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			case 1:
				imPauseHover.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			case 2:
				imPauseDown.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			case 3:
				imPauseDisable.Draw(pDC->GetSafeHdc(), m_rReopen);
				break;
			}
		}
		break;
	case 4://形势判断/AI死活分析按钮
		if (m_iState == 2)
		{
			if (m_iState1 == 0 || m_iState1==3)
			{
				switch (m_iStateArea)
				{
				case 0:
					imAreaNormal0.Draw(pDC->GetSafeHdc(), m_rArea);
					break;
				case 1:
					imAreaHover0.Draw(pDC->GetSafeHdc(), m_rArea);
					break;
				case 2:
					imAreaDown0.Draw(pDC->GetSafeHdc(), m_rArea);
					break;
				case 3:
					imAreaDisable0.Draw(pDC->GetSafeHdc(), m_rArea);
					break;
				}
			}
			else
			{
				switch (m_iStateArea)
				{
				case 0:
					imAreaNormal.Draw(pDC->GetSafeHdc(), m_rArea);
					break;
				case 1:
					imAreaHover.Draw(pDC->GetSafeHdc(), m_rArea);
					break;
				case 2:
					imAreaDown.Draw(pDC->GetSafeHdc(), m_rArea);
					break;
				case 3:
					imAreaDisable.Draw(pDC->GetSafeHdc(), m_rArea);
					break;
				}
			}
		}
		else if (m_iState1 == 11 || m_iState1 == 12 || m_iState1 == 14)//AI分析按钮
		{
			switch (m_iStateArea)
			{
			case 0:
				imAIanaNormal.Draw(pDC->GetSafeHdc(), m_rArea);
				break;
			case 1:
				imAIanaHover.Draw(pDC->GetSafeHdc(), m_rArea);
				break;
			case 2:
				imAIanaDown.Draw(pDC->GetSafeHdc(), m_rArea);
				break;
			case 3:
				imAIanaDisable.Draw(pDC->GetSafeHdc(), m_rArea);
				break;
			}
		}
		else if (m_iState == 3 || m_iState==1)//序盘研究/死活分析主界面不显示此按钮
		{

		}
		else
		{
			switch (m_iStateArea)
			{
			case 0:
				imHintNormal.Draw(pDC->GetSafeHdc(), m_rArea);
				break;
			case 1:
				imHintHover.Draw(pDC->GetSafeHdc(), m_rArea);
				break;
			case 2:
				imHintDown.Draw(pDC->GetSafeHdc(), m_rArea);
				break;
			case 3:
				imHintDisable.Draw(pDC->GetSafeHdc(), m_rArea);
				break;
			}
		}
		break;
	case 5://退出/交换按钮
		if (m_iState==1 || m_iState == 2 && (m_iState1 == 0 || m_iState1 == 3) || m_iState==3)//退出
		{
			switch (m_iStateExit)
			{
			case 0:
				imExitNormal.Draw(pDC->GetSafeHdc(), m_rExit);
				break;
			case 1:
				imExitHover.Draw(pDC->GetSafeHdc(), m_rExit);
				break;
			case 2:
				imExitDown.Draw(pDC->GetSafeHdc(), m_rExit);
				break;
			case 3:
				imExitDisable.Draw(pDC->GetSafeHdc(), m_rExit);
				break;
			}
		}
		else
		{
			switch (m_iStateExit)
			{
			case 0:
				imChangeStoneNormal.Draw(pDC->GetSafeHdc(), m_rExit);
				break;
			case 1:
				imChangeStoneHover.Draw(pDC->GetSafeHdc(), m_rExit);
				break;
			case 2:
				imChangeStoneDown.Draw(pDC->GetSafeHdc(), m_rExit);
				break;
			case 3:
				imChangeStoneDisable.Draw(pDC->GetSafeHdc(), m_rExit);
				break;
			}
		}
		break;
	case 6://认输按钮
		switch (m_iStateResign)
		{
		case 0:
			imResignNormal.Draw(pDC->GetSafeHdc(), m_rResign);
			break;
		case 1:
			imResignHover.Draw(pDC->GetSafeHdc(), m_rResign);
			break;
		case 2:
			imResignDown.Draw(pDC->GetSafeHdc(), m_rResign);
			break;
		case 3:
			imResignDisable.Draw(pDC->GetSafeHdc(), m_rResign);
			break;
		}
		break;
	case 10://回到最初按钮
		switch (m_iStateGoFirst)
		{
		case 0:
			imGoFirstNormal.Draw(pDC->GetSafeHdc(), m_rGoFirst);
			break;
		case 1:
			imGoFirstHover.Draw(pDC->GetSafeHdc(), m_rGoFirst);
			break;
		case 2:
			imGoFirstDown.Draw(pDC->GetSafeHdc(), m_rGoFirst);
			break;
		case 3:
			imGoFirstDisable.Draw(pDC->GetSafeHdc(), m_rGoFirst);
			break;
		}
		break;
	case 11://后退五步按钮
		switch (m_iStateGoFiveBack)
		{
		case 0:
			imGoFiveBackNormal.Draw(pDC->GetSafeHdc(), m_rGoFiveBack);
			break;
		case 1:
			imGoFiveBackHover.Draw(pDC->GetSafeHdc(), m_rGoFiveBack);
			break;
		case 2:
			imGoFiveBackDown.Draw(pDC->GetSafeHdc(), m_rGoFiveBack);
			break;
		case 3:
			imGoFiveBackDisable.Draw(pDC->GetSafeHdc(), m_rGoFiveBack);
			break;
		}
		break;
	case 12://后退按钮
		switch (m_iStateGoBack)
		{
		case 0:
			imGoBackNormal.Draw(pDC->GetSafeHdc(), m_rGoBack);
			break;
		case 1:
			imGoBackHover.Draw(pDC->GetSafeHdc(), m_rGoBack);
			break;
		case 2:
			imGoBackDown.Draw(pDC->GetSafeHdc(), m_rGoBack);
			break;
		case 3:
			imGoBackDisable.Draw(pDC->GetSafeHdc(), m_rGoBack);
			break;
		}
		break;
	case 13://前进按钮
		switch (m_iStateGoForward)
		{
		case 0:
			imGoForwardNormal.Draw(pDC->GetSafeHdc(), m_rGoForward);
			break;
		case 1:
			imGoForwardHover.Draw(pDC->GetSafeHdc(), m_rGoForward);
			break;
		case 2:
			imGoForwardDown.Draw(pDC->GetSafeHdc(), m_rGoForward);
			break;
		case 3:
			imGoForwardDisable.Draw(pDC->GetSafeHdc(), m_rGoForward);
			break;
		}
		break;
	case 14://前进五步按钮
		switch (m_iStateGoFiveForward)
		{
		case 0:
			imGoFiveForwardNormal.Draw(pDC->GetSafeHdc(), m_rGoFiveForward);
			break;
		case 1:
			imGoFiveForwardHover.Draw(pDC->GetSafeHdc(), m_rGoFiveForward);
			break;
		case 2:
			imGoFiveForwardDown.Draw(pDC->GetSafeHdc(), m_rGoFiveForward);
			break;
		case 3:
			imGoFiveForwardDisable.Draw(pDC->GetSafeHdc(), m_rGoFiveForward);
			break;
		}
		break;
	case 15://前进到底按钮
		switch (m_iStateGoLast)
		{
		case 0:
			imGoLastNormal.Draw(pDC->GetSafeHdc(), m_rGoLast);
			break;
		case 1:
			imGoLastHover.Draw(pDC->GetSafeHdc(), m_rGoLast);
			break;
		case 2:
			imGoLastDown.Draw(pDC->GetSafeHdc(), m_rGoLast);
			break;
		case 3:
			imGoLastDisable.Draw(pDC->GetSafeHdc(), m_rGoLast);
			break;
		}
		break;
	case 16://手筋练习按钮
		if (m_bDifficulty)
		{
			switch (m_iStateTesuji)
			{
			case 0:
				imTesujiNormal.Draw(pDC->GetSafeHdc(), m_rTesuji);
				break;
			case 1:
				imTesujiHover.Draw(pDC->GetSafeHdc(), m_rTesuji);
				break;
			}
		}
		break;
	case 17://初级死活按钮
		if (m_bDifficulty)
		{
			switch (m_iStateElemantary)
			{
			case 0:
				imElementaryNormal.Draw(pDC->GetSafeHdc(), m_rElementary);
				break;
			case 1:
				imElementaryHover.Draw(pDC->GetSafeHdc(), m_rElementary);
				break;
			}
		}
		break;
	case 18://中级死活按钮
		if (m_bDifficulty)
		{
			switch (m_iStateMiddle)
			{
			case 0:
				imMiddleNormal.Draw(pDC->GetSafeHdc(), m_rMiddle);
				break;
			case 1:
				imMiddleHover.Draw(pDC->GetSafeHdc(), m_rMiddle);
				break;
			}
		}
		break;
	case 19://高级死活按钮
		if (m_bDifficulty)
		{
			switch (m_iStateAdvanced)
			{
			case 0:
				imAdvancedNormal.Draw(pDC->GetSafeHdc(), m_rAdvanced);
				break;
			case 1:
				imAdvanceeHover.Draw(pDC->GetSafeHdc(), m_rAdvanced);
				break;
			}
		}
		break;
	case 20://黑先按钮
		if (m_iState1 == 11 || m_iState1==12 || m_iState1 == 14)
		{
			switch (m_iStateBlackFirst)
			{
			case 0:
				imBlackFirstNormal.Draw(pDC->GetSafeHdc(), m_rBlackFirst);
				break;
			case 1:
				imBlackFirstHover.Draw(pDC->GetSafeHdc(), m_rBlackFirst);
				break;
			case 2:
				imBlackFirstDown.Draw(pDC->GetSafeHdc(), m_rBlackFirst);
				break;
			case 3:
				imBlackFirstDisable.Draw(pDC->GetSafeHdc(), m_rBlackFirst);
				break;
			}
		}
		break;
	case 21://白先按钮
		if (m_iState1 == 11 || m_iState1==12 || m_iState1 == 14)
		{
			switch (m_iStateWhiteFirst)
			{
			case 0:
				imWhiteFirstNormal.Draw(pDC->GetSafeHdc(), m_rWhiteFirst);
				break;
			case 1:
				imWhiteFirstHover.Draw(pDC->GetSafeHdc(), m_rWhiteFirst);
				break;
			case 2:
				imWhiteFirstDown.Draw(pDC->GetSafeHdc(), m_rWhiteFirst);
				break;
			case 3:
				imWhiteFirstDisable.Draw(pDC->GetSafeHdc(), m_rWhiteFirst);
				break;
			}
		}
		break;
	case 22://摆放黑子按钮
		if (m_iState1 == 11)
		{
			switch (m_iStatePutBlack)
			{
			case 0:
				imPutBlackNormal.Draw(pDC->GetSafeHdc(), m_rPutBlack);
				break;
			case 1:
				imPutBlackHover.Draw(pDC->GetSafeHdc(), m_rPutBlack);
				break;
			case 2:
				imPutBlackDown.Draw(pDC->GetSafeHdc(), m_rPutBlack);
				break;
			case 3:
				imPutBlackDisable.Draw(pDC->GetSafeHdc(), m_rPutBlack);
				break;
			}
		}
		break;
	case 23://摆放白子按钮
		if (m_iState1 == 11)
		{
			switch (m_iStatePutWhite)
			{
			case 0:
				imPutWhiteNormal.Draw(pDC->GetSafeHdc(), m_rPutWhite);
				break;
			case 1:
				imPutWhiteHover.Draw(pDC->GetSafeHdc(), m_rPutWhite);
				break;
			case 2:
				imPutWhiteDown.Draw(pDC->GetSafeHdc(), m_rPutWhite);
				break;
			case 3:
				imPutWhiteDisable.Draw(pDC->GetSafeHdc(), m_rPutWhite);
				break;
			}
		}
		break;
	}
	ReleaseDC(pDC);
}

void CSfcGoView::OnNew()
{
	if (m_iState == 1)//死活分析
	{
		m_iLabelCount = 0;
		m_iMaxSizePos = -1;
		if (m_iState1 == 0)//开始摆子
		{
			ClearBoard();
			sgfFreeNode(m_Sgftree.root);
			sgftree_clear(&m_Sgftree);
			//sgftreeCreateHeaderNode(&m_Sgftree, iBoardSize, m_fKomi, m_iHandiCap);
			CreateSgfHead(&m_Sgftree, iBoardSize, m_fKomi, m_iHandiCap);
			m_bSgf_initialized = false;
			InitSgf(&m_Gameinfo);
			m_Gameinfo.game_record = m_Sgftree;
			m_iState1 = 11;
			m_sOutputInfo = "正在摆子";
			if (iLanguage == 0)
				m_sOutputInfo = "Putting stone";
			InvalidateRect(m_rOutputInfo);
			SetDlgItemText(IDC_STAT, "正在摆子");
			btnBz.SetWindowTextA("清  盘");
			m_hBlackCursor = (HCURSOR)LoadImage(NULL, strSysDirectry + "\\blackstone.ico", IMAGE_ICON, m_iGap + 4, m_iGap + 4, LR_LOADFROMFILE);
			m_hWhiteCursor = (HCURSOR)LoadImage(NULL, strSysDirectry + "\\whitestone.ico", IMAGE_ICON, m_iGap + 4, m_iGap + 4, LR_LOADFROMFILE);
			m_iStateNew = 0;
			m_iStateArea = 0;
			m_iStatePutBlack = 2;
			m_iStatePutWhite = 0;
			m_iStateBlackFirst = 2;
			m_iStateWhiteFirst = 0;
			m_iColor = BLACK;
			Invalidate();
			UpdateWindow();
		}
		else//摆子完毕，开始解题
		{
			m_bAnswered = false;
			m_iAnaMoveCount = 0;
			m_iOldFixedStone = m_iFixedStone;
			m_iFixedStone = m_iGoCount;
			m_iOldState1 = m_iState1;
			//暂存着手记录
			m_iOldGoCount = m_iGoCount;
			m_iOldGoCountMax = m_iGoCountMax;
			memcpy(m_OldGoRecord, m_GoRecord, sizeof(Data_GoRecord) * m_iGoCountMax);
			SaveMoveRecs();
			m_bRecall = false;
			m_hBlackCursor = (HCURSOR)LoadImage(NULL, strSysDirectry + "\\blackstone.ico", IMAGE_ICON, m_iGap + 4, m_iGap + 4, LR_LOADFROMFILE);
			m_hWhiteCursor = (HCURSOR)LoadImage(NULL, strSysDirectry + "\\whitestone.ico", IMAGE_ICON, m_iGap + 4, m_iGap + 4, LR_LOADFROMFILE);
			CString filename = strSysDirectry;
			filename += "\\tmp.sgf";
			char* fpname = filename.GetBuffer();
			//writesgf(m_Sgftree.root, fpname);
			//保存SGFTREE
			//sgfFreeNode(m_Sgftree1.root);
			//sgftree_clear(&m_Sgftree1);
			//sgftree_readfile(&m_Sgftree1, fpname);
			//将局面转储为临时文件
			GoRecordToSgf(m_iGoCount, m_GoRecord, m_iFixedStone, &m_Sgftree);
			if (m_iState1 == 11)//摆子状态，备份棋谱
			{
				CopySgfTree(&m_Sgftree1, m_Sgftree);
			}
			writesgf(m_Sgftree.root, fpname);
			CString str = "loadsgf ";
			str += filename;
			str += "\r\n";
			m_pEngine1->WriteToPipe(str);
			int count;
			CString* strs = m_pEngine1->GetMsg(count);
			delete[] strs;
			SetLevel(20);//设电脑棋力为九段以加快思考速度
			m_iComputerThinkTime = 5;//设置电脑思考5秒
			SetTimes(0, m_iComputerThinkTime, m_iComputerByoStones);
			m_sLifeDeathCmd = " allow ";
			m_sLifeDeathCmd += "B ";//设置电脑着手限制
			CString allowedmove = GetLifeDeathAllowedMoveString(1);
			m_sLifeDeathCmd += allowedmove;
			m_sLifeDeathCmd += " 20";//最大分析深度为20步
			m_sLifeDeathCmd += " allow W ";
			m_sLifeDeathCmd += allowedmove;
			m_sLifeDeathCmd += " 20";//最大分析深度为20步
			m_Gameinfo.game_record = m_Sgftree;
			if (m_iStateBlackFirst == 2)
			{
				m_iColor = BLACK;
				iPlayer1 = 0;
				iLevel1 = iPlayerLevel;
				iPlayer2 = 1;
				iLevel2 = iLevel;
			}
			else
			{
				m_iColor = WHITE;
				iPlayer2 = 0;
				iLevel2 = iPlayerLevel;
				iPlayer1 = 1;
				iLevel1 = iLevel;
			}
			//m_Gameinfo.to_move = OTHER_COLOR(m_iColor);
			m_iFirstColor = m_iColor;
			m_bPaused = false;
			m_bPicked = false;
			m_iState1 = 1;
			if (m_iOldState1 == 12 || m_iOldState1==14)
				m_iStateNew = 0;
			else
				m_iStateNew = 3;
			m_iStateSave = 0;
			m_iStateReopen = 0;
			m_iStateArea = 0;
			UpdateBackForwardButton();
			m_sOutputInfo = "轮玩家着手";
			//InvalidateRect(m_rPlayInfo);
			//InvalidateRect(m_rToolBox);
			this->Invalidate();
			this->UpdateWindow();
			//计时开始，准备对弈
			m_StartTime = GetTickCount64();
			m_PauseTime = CTimeSpan(0, 0, 0, 0);
			m_BlackTime = CTimeSpan(0, 0, 0, 0);
			m_WhiteTime = CTimeSpan(0, 0, 0, 0);
			m_PeriodTime = CTimeSpan(0, 0, 0, 0);
			SetTimer(m_Gameinfo.to_move, 1000, NULL);
		}
	}
	else if (m_iState == 2)//人机对弈
	{
		if (m_iState1 == 3)
		{
			CString msg = "对奕尚未结束，您要中断此局并开始新一轮对弈吗？";
			if (iLanguage == 0)
				msg = "Game is not end, do you want to ignor this game and open a new one?";
			if (MessageBox(msg, sMsg, MB_YESNO) != IDYES)
			{
				m_iStateNew = 0;
				return;
			}
			m_iState1 = 0;
		}
		if (m_iState1 == 0)//初始化，开始对弈
		{
			if (!m_bReOpen)
			{
				m_bSgfLoaded = false;
				m_bSfcSgfLoaded = false;
			}
			m_bReOpen = false;
			//对局模式选择
			if (!m_bSfcSgfLoaded)
			{
				DlgNewGame dlg;
				dlg.m_iHuman1 = iPlayer1;
				dlg.m_iLevel1 = iLevel1;
				dlg.m_iTime1 = iTime1;
				dlg.m_iEngine1 = iEngine1;
				dlg.m_iHuman2 = iPlayer2;
				dlg.m_iLevel2 = iLevel2;
				dlg.m_iTime2 = iTime2;
				dlg.m_iEngine2 = iEngine2;
				dlg.m_iRule = iRule;
				dlg.m_iBoardSize = iBoard;
				dlg.m_iKomi = iKomi;
				dlg.m_iHandicap = iHandi;
				dlg.m_bCoord = bCoord;
				dlg.m_bAnimate = bAnimate;
				dlg.m_bThinkProgram = bThinkProgress;
				dlg.m_bPutStone = bPutStoneSound;
				dlg.m_bCapture = bCaptureSound;
				dlg.m_bPickStone = bPickStoneSound;
				dlg.m_bPushClock = bPushClockSound;
				dlg.m_bByo = bByoSound;
				dlg.m_bSgfLoaded = m_bSgfLoaded;
				if (dlg.DoModal() != IDOK)
				{
					m_iStateNew = 0;
					InvalidateRect(m_rNew);
					return;
				}
				m_iCombat = 0;
				if (dlg.m_iCombat == 1 && (dlg.m_iHuman1==0 || dlg.m_iHuman2==0))
				{
					int lvl = dlg.m_iLevel1;
					if (dlg.m_iHuman2 != 0)
						lvl = dlg.m_iLevel2;
					CString title = GetLevelFullTitle(lvl);
					if (iLanguage == 0)
					{
						title = " level " + title;
					}
					else
					{
						if (lvl < 12)
							title += "水平";
						else if (lvl < 21)
							title += "位";
						else
							title += "头衔";
					}
					CString msg = "你选择了挑战赛模式，这将使你在胜利后获得相应等级奖励。\r\n你确定已经准备好要挑战" + title + "了吗？";
					if (iLanguage == 0)
						msg = "You have selected combat mode. You will be reward a higher level after winning this game.\r\nAre you sure to chanllenge" + title + "?";
					if (MessageBox(msg, sMsg, MB_YESNO) != IDYES)
					{
						m_iStateNew = 0;
						InvalidateRect(m_rNew);
						return;
					}
					m_iCombat = dlg.m_iCombat;
				}
				iPlayer1 = dlg.m_iHuman1;
				iLevel1 = dlg.m_iLevel1;
				iTime1 = dlg.m_iTime1;
				iEngine1 = dlg.m_iEngine1;
				iPlayer2 = dlg.m_iHuman2;
				iLevel2 = dlg.m_iLevel2;
				iTime2 = dlg.m_iTime2;
				iEngine2 = dlg.m_iEngine2;
				iRule = dlg.m_iRule;
				iBoard = dlg.m_iBoardSize;
				iKomi = dlg.m_iKomi;
				iHandi = dlg.m_iHandicap;
				bCoord = dlg.m_bCoord;
				bAnimate = dlg.m_bAnimate;
				bThinkProgress = dlg.m_bThinkProgram;
				bPutStoneSound = dlg.m_bPutStone;
				bCaptureSound = dlg.m_bCapture;
				bPickStoneSound = dlg.m_bPickStone;
				bPushClockSound = dlg.m_bPushClock;
				bByoSound = dlg.m_bByo;
				if (iPlayer1 == 0)
					iLevel1 = iPlayerLevel;
				else if (iPlayer2 == 0)
					iLevel2 = iPlayerLevel;
				//保存选项到系统文件
				Sfc::WriteSysIni();
			}
			//将选项转换为内部参数
			m_bGameOver = false;
			m_bSelfPlay = false;
			m_bEngineDual = false;
			if (iPlayer1 == 1 && iPlayer2 == 1)
			{
				if (iEngine1 == iEngine2)
					m_bSelfPlay = true;
				else
					m_bEngineDual = true;
			}
			else
			{
				if (iPlayer1 == 0)
				{
					if (!m_bSgfLoaded)
					{
						m_sBlackName = sPlayerName;
						iLevel1 = iPlayerLevel;
					}
					m_iColor = 2;
				}
				else
				{
					if (!m_bSgfLoaded)
					{
						m_sWhiteName = sPlayerName;
						iLevel2 = iPlayerLevel;
					}
					m_iColor = 1;
				}
			}
			m_iMainTime = 0;
			m_iByoTime = 0;
			m_iByoStones = 0;
			m_iByoTime = 10;
			m_iByoStones = 1;
			m_iComputerByoStones = 1;
			iLevel = iLevel1;
			if (iPlayer1 == 0)
				iLevel = iLevel2;
			int t = iTime1;
			if (iPlayer1 == 0)
				t = iTime2;
			switch (t)
			{
			case 0:
				m_iComputerThinkTime = 5;
				break;
			case 1:
				m_iComputerThinkTime = 15;
				break;
			case 2:
				m_iComputerThinkTime = 30;
				break;
			case 3:
				m_iComputerThinkTime = 60;
				break;
			case 4:
				m_iComputerThinkTime = 90;
				break;
			case 5:
				m_iComputerThinkTime = 120;
				break;
			}
			m_iComputerByoTime = m_iComputerThinkTime;
			if (bPickStoneSound)
				m_iComputerThinkTime-=2;
			if (bAnimate)
				m_iComputerThinkTime--;
			if (bPushClockSound)
				m_iComputerThinkTime--;
			switch (iBoard)
			{
			case 0:
				m_iBoardSize = 19;
				break;
			case 1:
				m_iBoardSize = 13;
				break;
			case 2:
				m_iBoardSize = 9;
				break;
			}
			m_fKomi = (iKomi * 0.5) - 10;
			m_iHandiCap = iHandi;
			if (m_iHandiCap == 1)
				m_iHandiCap = 0;
			//根据设置选项来启动引擎
			iEngineId = 0;
			int engineid = iEngine1;
			if (iPlayer1 == 0 && iPlayer2 == 1)
				engineid = iEngine2;
			int type = 0;//引擎加载参数
			if (engineid == 1 && iLevel > 9)
				type = 1;
			bool loaded = false, loaded1 = true;
			if (m_pEngine1 != nullptr && m_pEngine1->m_Id==engineid && m_pEngine1->m_iType == type || m_pEngine2 != nullptr && m_pEngine2->m_Id == engineid && m_pEngine2->m_iType == type)
				loaded = true;
			if (loaded && !(m_pEngine1 != nullptr && m_pEngine1->m_Id == engineid && m_pEngine1->m_iType == type))
				iEngineId = 1;
			if (!loaded)
			{
				pDlgNotify->m_sNotify = "正在加载引擎，请稍候······";
				if(iLanguage==0)
					pDlgNotify->m_sNotify = "Loading engine, please wait...";
				pDlgNotify->Create(IDD_NOTIFY, this);
				pDlgNotify->ShowWindow(SW_SHOW);
				pDlgNotify->UpdateWindow();
				if (m_pEngine1 == nullptr)
					iEngineId = 0;
				else if (m_pEngine2 == nullptr)
					iEngineId = 1;
				else
				{
					if (m_pEngine1->m_Id == engineid)
						iEngineId = 0;
					else if (m_pEngine2->m_Id == engineid)
						iEngineId = 1;
					else
						iEngineId = 0;
					if (iEngineId == 0)
						delete m_pEngine1;
					else
						delete m_pEngine2;
					Sleep(1000);//等待引擎退出
				}
				CString sdir = strDirectry + "\\Engine\\" + sEngineAppDirs[engineid];
				m_pEngine = new SfcGtp();
				//m_pEngine1 = new SfcGtp();
				//m_pEngine->m_iType = iEngineTypes[engineid];
				m_pEngine->m_AppName = sdir + "\\" + sEngineAppNames[engineid];
				m_pEngine->m_AppDir = sdir;
				m_pEngine->m_CmdLine = sdir + "\\" + sEngineAppNames[engineid] + " " + sEngineCmdLines[engineid];
				m_pEngine->m_CmdLine1 = sdir + "\\" + sEngineAppNames[engineid] + " " + sEngineCmdLines1[engineid];
				m_pEngine->m_Id = engineid;
				m_pEngine->LoadEngine(type);
				//Sleep(3000);
				//CHAR chBuf[8192];
				//DWORD dwRead;
				//m_pEngine->ReadFromPipe(chBuf, dwRead);
				if (iEngineId == 0)
					m_pEngine1 = m_pEngine;
				else
					m_pEngine2 = m_pEngine;
			}
			//CString str;
			//CString* strs;
			//float pda = -3.0;
			//str.Format("kata-set-param playoutDoublingAdvantage %3.1f\r\n", pda);
			//m_pEngine1->WriteToPipe(str);
			//int count;
			//CString* strs = m_pEngine1->GetMsg(count);
			/*int serchthreads = 1;
			str.Format("kata-set-param numSearchThreads %d\r\n", serchthreads);
			m_pEngine1->WriteToPipe(str);
			strs = m_pEngine1->GetMsg(count);

			int visits = 2;
			str.Format("kata-set-param maxVisits %d\r\n", visits);
			m_pEngine1->WriteToPipe(str);
			strs = m_pEngine1->GetMsg(count);
			int playouts = 1;
			str.Format("kata-set-param maxPlayouts %d\r\n", playouts);
			m_pEngine1->WriteToPipe(str);
			strs = m_pEngine1->GetMsg(count);
			float maxtime = 0.1;
			str.Format("kata-set-param maxTime %3.1f\r\n", maxtime);
			m_pEngine1->WriteToPipe(str);
			strs = m_pEngine1->GetMsg(count);*/
			SetLevel(iLevel);
			SetRule(iRule);
			if (!m_bSgfLoaded)
			{
				SetBoardSize(m_iBoardSize);
				ClearBoard();
				SetHandicap(m_iHandiCap);
			}
			else
			{
				SetEngineBoardSize(m_iBoardSize);
				ClearEngineBoard();
				SetEngineFixedHandicap(m_iHandiCap);
			}
			SetKomi(m_fKomi);
			SetTimes(0, m_iComputerThinkTime, m_iComputerByoStones);
			t = iTime2;
			switch (t)
			{
			case 0:
				m_iComputerThinkTime2 = 5;
				break;
			case 1:
				m_iComputerThinkTime2 = 15;
				break;
			case 2:
				m_iComputerThinkTime2 = 30;
				break;
			case 3:
				m_iComputerThinkTime2 = 60;
				break;
			case 4:
				m_iComputerThinkTime2 = 120;
				break;
			}
			m_iComputerByoTime2 = m_iComputerThinkTime2;
			if (bPickStoneSound)
				m_iComputerThinkTime2 -= 2;
			if (bAnimate)
				m_iComputerThinkTime2--;
			if (bPushClockSound)
				m_iComputerThinkTime2--;
			//引擎对战设置
			if (m_bEngineDual)
			{
				iBlackEngineId = iEngineId;
				if (iBlackEngineId == 0)
					iWhiteEngineId = 1;
				else
					iWhiteEngineId = 0;
				//加载第二引擎
				engineid = iEngine2;
				type = 0;//引擎加载参数
				if (engineid == 1 && iLevel >= 9)
					type = 1;
				loaded1 = false;
				if (m_pEngine1 != nullptr && m_pEngine1->m_Id == engineid && m_pEngine1->m_iType == type || m_pEngine2 != nullptr && m_pEngine2->m_Id == engineid && m_pEngine2->m_iType == type)
					loaded1 = true;
				if (!loaded1)
				{
					if (loaded)
					{
						pDlgNotify->m_sNotify = "正在加载引擎，请稍候······";
						if (iLanguage == 0)
							pDlgNotify->m_sNotify = "Loading engine, please wait...";
						pDlgNotify->Create(IDD_NOTIFY, this);
						pDlgNotify->ShowWindow(SW_SHOW);
						pDlgNotify->UpdateWindow();
					}
					if (iWhiteEngineId == 0 && m_pEngine1 != nullptr)
					{
						delete m_pEngine1;
						Sleep(1000);
					}
					else if (iWhiteEngineId == 1 && m_pEngine2 != nullptr)
					{
						delete m_pEngine2;
						Sleep(1000);
					}
					CString sdir = strDirectry + "\\Engine\\" + sEngineAppDirs[engineid];
					m_pEngine = new SfcGtp();
					//m_pEngine1 = new SfcGtp();
					//m_pEngine->m_iType = iEngineTypes[engineid];
					m_pEngine->m_AppName = sdir + "\\" + sEngineAppNames[engineid];
					m_pEngine->m_AppDir = sdir;
					m_pEngine->m_CmdLine = sdir + "\\" + sEngineAppNames[engineid] + " " + sEngineCmdLines[engineid];
					m_pEngine->m_CmdLine1 = sdir + "\\" + sEngineAppNames[engineid] + " " + sEngineCmdLines1[engineid];
					m_pEngine->m_Id = engineid;
					m_pEngine->LoadEngine(type);
					//Sleep(3000);
					//CHAR chBuf[8192];
					//DWORD dwRead;
					//m_pEngine->ReadFromPipe(chBuf, dwRead);
					if (iWhiteEngineId == 0)
						m_pEngine1 = m_pEngine;
					else
						m_pEngine2 = m_pEngine;
				}
				/*CString sdir = strDirectry;
				sdir += "\\Engine\\KataGo";
				m_pEngine2 = new SfcGtp();
				m_pEngine2->m_AppName = sdir + "\\katago.exe";
				m_pEngine2->m_AppDir = sdir;
				m_pEngine2->m_CmdLine = sdir + "\\katago.exe gtp -model kata1-b18c384nbt-s7709731328-d3715293823.bin.gz -config SfcGo.cfg";
				m_pEngine2->m_CmdLine1 = sdir + "\\katago.exe gtp -model kata1-b18c384nbt-s7709731328-d3715293823.bin.gz -config SfcGo_LifeDeth.cfg";
				m_pEngine2->LoadEngine(0);
				Sleep(3000);
				CHAR chBuf[8192];
				DWORD dwRead;
				m_pEngine2->ReadFromPipe(chBuf, dwRead);*/
				//根据设置选项来设置引擎
				//CString str;
				//CString* strs;
				//float pda = -3.0;
				//str.Format("kata-set-param playoutDoublingAdvantage %3.1f\r\n", pda);
				//m_pEngine1->WriteToPipe(str);
				//int count;
				//CString* strs = m_pEngine1->GetMsg(count);
				/*int serchthreads = 16;
				str.Format("kata-set-param numSearchThreads %d\r\n", serchthreads);
				m_pEngine1->WriteToPipe(str);
				strs = m_pEngine1->GetMsg(count);

				int visits = 100;
				str.Format("kata-set-param maxVisits %d\r\n", visits);
				m_pEngine2->WriteToPipe(str);
				strs = m_pEngine2->GetMsg(count);
				int playouts = 80;
				str.Format("kata-set-param maxPlayouts %d\r\n", playouts);
				m_pEngine2->WriteToPipe(str);
				strs = m_pEngine2->GetMsg(count);
				float maxtime = 2;
				str.Format("kata-set-param maxTime %3.1f\r\n", maxtime);
				m_pEngine2->WriteToPipe(str);
				strs = m_pEngine2->GetMsg(count);*/
				iEngineId = iWhiteEngineId;
				SetLevel(iLevel2);
				SetRule(iRule);
				SetEngineBoardSize(m_iBoardSize);
				ClearEngineBoard();
				SetEngineFixedHandicap(m_iHandiCap);
				SetKomi(m_fKomi);
				/*str.Format("boardsize %d\r\n", iBoardSize);
				m_pEngine2->WriteToPipe(str);
				strs = m_pEngine2->GetMsg(count);
				str = "clear_board\r\n";
				m_pEngine2->WriteToPipe(str);
				strs = m_pEngine2->GetMsg(count);
				if (m_iHandiCap >= 2 && m_iHandiCap <= 9)
				{
					str.Format("fixed_handicap %d\r\n", m_iHandiCap);
					m_pEngine2->WriteToPipe(str);
					strs = m_pEngine2->GetMsg(count);
				}*/
				SetTimes(0, m_iComputerThinkTime2, m_iComputerByoStones);
			}
			if (!loaded || !loaded1)
				pDlgNotify->DestroyWindow();
			m_hBlackCursor = (HCURSOR)LoadImage(NULL, strSysDirectry + "\\blackstone.ico", IMAGE_ICON, m_iGap + 4, m_iGap + 4, LR_LOADFROMFILE);
			m_hWhiteCursor = (HCURSOR)LoadImage(NULL, strSysDirectry + "\\whitestone.ico", IMAGE_ICON, m_iGap + 4, m_iGap + 4, LR_LOADFROMFILE);
			iRandomSeed = unsigned int(time(NULL));
			bLife_death = 0;
			m_cmbMb.EnableWindow(FALSE);
			m_iState1 = 1;
			//m_iColor=2;
			//sgftree_clear(&m_Sgftree);
			//GameinfoClear(&m_Gameinfo);
			/* Initialize and empty sgf tree if there was no infile. */
			if (!m_bSgfLoaded)//初始化SGF树
			{
				sgfFreeNode(m_Sgftree.root);
				sgftree_clear(&m_Sgftree);
				//sgftreeCreateHeaderNode(&m_Sgftree, iBoardSize, m_fKomi, m_iHandiCap);
				CreateSgfHead(&m_Sgftree, iBoardSize, m_fKomi, m_iHandiCap);
				m_bSgf_initialized = false;
				InitSgf(&m_Gameinfo);
			}
			else//引擎载入SGF文件
			{
				CString filename = strSysDirectry;
				filename += "\\tmp.sgf";
				CString str = "loadsgf ";
				str += filename;
				str += "\r\n";
				iEngineId == 0 ? m_pEngine1->WriteToPipe(str) : m_pEngine2->WriteToPipe(str);
				int count;
				CString* strs = nullptr;
				iEngineId == 0 ? strs=m_pEngine1->GetMsg(count) : strs=m_pEngine2->GetMsg(count);
				delete[] strs;
			}
			/* Set the game_record to be identical to the loaded one or the
			* newly created empty sgf tree.
			*/
			m_Gameinfo.game_record = m_Sgftree;
			m_Gameinfo.computer_player = OTHER_COLOR(m_iColor);
			strcpy_s(m_OutFileName, "recordtest.sgf");
			if (m_iCombat == 1)
			{
				m_iStateOpen = 3;
				m_iStateSave = 3;
				m_iStateArea = 3;
				m_iStateExit = 3;
			}
			else
			{
				m_iStateOpen = 0;
				m_iStateSave = 0;
				m_iStateArea = 0;
				m_iStateExit = 0;
			}
			m_iStateReopen = 0;
			m_bPaused = false;
			SetDlgItemText(IDC_STAT, "对弈中");
			m_iAnaMoveCount = 0;
			if (!m_bSgfLoaded)
			{
				m_iMoveCount = 0;
				m_iFirstColor = m_Gameinfo.to_move;
			}
			else
			{
				if (m_iHandiCap >= 2)
					m_iFirstColor = WHITE;
				else
					m_iFirstColor = BLACK;
			}
			if (!m_bSelfPlay && !m_bEngineDual && m_Gameinfo.computer_player != m_Gameinfo.to_move)
			{
				m_sOutputInfo = "轮玩家着子";
				if (iLanguage == 0)
					m_sOutputInfo = "Waiting for player's move";
			}
			else
			{
				m_sOutputInfo = sThinkMsg;
				m_iState1 = 2;
			}
			if (m_bSelfPlay || m_bEngineDual)
			{
				m_sOutputInfo = "轮黑方走";
				if (iLanguage == 0)
					m_sOutputInfo = "Waiting for black's move";
				m_iStateNew = 3;
				m_iStateOpen = 3;
				m_iStateSave = 3;
				//m_iStateReopen = 3;
				m_iStateArea = 3;
				m_iStateExit = 3;
				m_iStateResign = 3;
			}
			this->Invalidate();
			this->UpdateWindow();
			//计时开始，准备对弈
			m_StartTime = GetTickCount64();
			m_PauseTime = CTimeSpan(0, 0, 0, 0);
			m_BlackTime = CTimeSpan(0, 0, 0, 0);
			m_WhiteTime = CTimeSpan(0, 0, 0, 0);
			m_PeriodTime = CTimeSpan(0, 0, 0, 0);
			//SetTimer(0, 1000, NULL);
			SetTimer(m_Gameinfo.to_move, 1000, NULL);
			if (m_bSelfPlay || m_bEngineDual || m_Gameinfo.computer_player == m_Gameinfo.to_move)
			{
				m_bPicked = true;
				ComputerMove();
			}
			else
			{
				//m_PeriodTime = CTimeSpan(0, 0, 0, 0);
				m_bPicked = false;
			}
		}
	}
	else if (m_iState == 3)//序盘研究
	{
		if (m_iState1 == 0)//开始摆子
		{
			m_bGameOver = false;
			ClearBoard();
			sgfFreeNode(m_Sgftree.root);
			sgftree_clear(&m_Sgftree);
			CreateSgfHead(&m_Sgftree, iBoardSize, m_fKomi, m_iHandiCap);
			m_bSgf_initialized = false;
			InitSgf(&m_Gameinfo);
			m_Gameinfo.game_record = m_Sgftree;
			m_iOldState1 = m_iState1;
			m_iState1 = 21;
			m_sOutputInfo = "正在摆子";
			if (iLanguage == 0)
				m_sOutputInfo = "Putting stone";
			InvalidateRect(m_rOutputInfo);
			m_hBlackCursor = (HCURSOR)LoadImage(NULL, strSysDirectry + "\\blackstone.ico", IMAGE_ICON, m_iGap + 4, m_iGap + 4, LR_LOADFROMFILE);
			m_hWhiteCursor = (HCURSOR)LoadImage(NULL, strSysDirectry + "\\whitestone.ico", IMAGE_ICON, m_iGap + 4, m_iGap + 4, LR_LOADFROMFILE);
			m_iStateNew = 0;
			m_iStateOpen = 0;
			m_iStateSave = 0;
			m_iColor = BLACK;
			m_bInTurn = true;
			InvalidateRect(m_rToolBox);
		}
	}
}

void CSfcGoView::OnOpen()
{
	//char sgfFilters[] =
	//	"棋谱文件 (*.sgf)|*.sgf|All Files (*.*)|*.*||";
	char sgfFilters[255];
	//if (iLanguage == 0)
		strcpy(sgfFilters, "Go record file (*.sgf)|*.sgf|All Files (*.*)|*.*||");
	//else
	//	strcpy(sgfFilters, "棋谱文件 (*.sgf)|*.sgf|All Files (*.*)|*.*||");
	CFileDialog filedlg(TRUE, "", ".sgf", OFN_PATHMUSTEXIST, sgfFilters);
	if (filedlg.DoModal() == IDOK)
	{
		CString filename = filedlg.GetPathName();
		char* fpname = filename.GetBuffer();
		if (fpname)
		{
			//ClearBoard();
			sgfFreeNode(m_Sgftree.root);
			sgftree_clear(&m_Sgftree);
			sgftree_readfile(&m_Sgftree, fpname);
			//备份棋谱
			CopySgfTree(&m_Sgftree1, m_Sgftree);
			m_bGameOver = false;
			for (int i = 0; i < m_iGoCountMax; i++)
			{
				m_sMoveTimeRecs[i] = "";
				m_fMoveWinRates[i] = 0;
				m_fStdMoveWinRates[i] = 0;
			}
			SgfToGoRecord(&m_Sgftree, m_iGoCount, m_GoRecord, m_iFixedStone);
			if (!m_bSfcSgfLoaded)
				m_iCombat = 0;
			m_iHandiCap = m_Gameinfo.handicap;
			m_GoInfo.Init(m_iBoardSize);
			m_GoInfo.fixedstone = m_iFixedStone;
			m_iMoveCount = 0;
			//for (int i = 0; i < m_iFixedStone; i++)
			//	m_iBoard[m_GoRecord[i].x][m_GoRecord[i].y] = m_GoRecord[i].color;
			//SgfToGoRecord(&m_Sgftree, m_GoInfo.gocount, m_GoInfo.gorecord, m_GoInfo.fixedstone);
			//for (int i = 0; i < m_GoInfo.fixedstone; i++)
			//	Sfc::AddStone(m_GoInfo.gorecord[i].x, m_GoInfo.gorecord[i].y, m_GoInfo.gorecord[i].color, m_GoInfo);
			//for(int i=0;i<m_iFixedStone;i++)
			//	Sfc::PlayStone(m_GoRecord[i].x, m_GoRecord[i].y, m_GoRecord[i].color, m_GoInfo);
			for (int i = 0; i < m_iGoCount; i++)
				Sfc::PlayStone(m_GoRecord[i].x, m_GoRecord[i].y, m_GoRecord[i].color,m_GoInfo);
			for (int i = 0; i < m_iBoardSize; i++)
				for (int j = 0; j < m_iBoardSize; j++)
					m_iBoard[i][j] = m_GoInfo.board[i][j];
			for (int i = 0; i < m_iGoCount; i++)
			{
				if (i >= m_iFixedStone)
				{
					m_sMoveRecs[m_iMoveCount] = TransXY(m_GoRecord[i].x, m_GoRecord[i].y, m_GoRecord[i].color);
					/*m_sMoveTimeRecs[m_iMoveCount].Format("%02d:%02d:%02d", m_PeriodTime.GetHours(), m_PeriodTime.GetMinutes(), m_PeriodTime.GetSeconds());
					if (m_GoRecord[i].color == BLACK)
						m_fMoveWinRates[m_iMoveCount] = m_fBlackWinRate;
					else
						m_fMoveWinRates[m_iMoveCount] = m_fWhiteWinRate;*/
					m_iMoveCount++;
				}
			}
			m_iGoCountMax = m_iGoCount;
			m_bRecall = true;
			//m_iRecallStartId = 0;
			m_iRecallId = m_iGoCountMax - 1;
			if (m_iGoCount > m_iFixedStone)
				m_iFirstColor = m_GoRecord[m_iFixedStone].color;
			m_bSelfPlay = false;
			m_bEngineDual = false;
			if (m_bSfcSgfLoaded)
			{
				//设置对局双方信息
				if (iPlayer1 == 1 && iPlayer2 == 1)
				{
					if (iEngine1 == iEngine2)
						m_bSelfPlay = true;
					else
						m_bEngineDual = true;
				}
				else
				{
					if (iPlayer1 == 1)
						m_Gameinfo.computer_player = BLACK;
					else
						m_Gameinfo.computer_player = WHITE;
				}
				/*/读取胜率
				if (filename.Right(4) == ".sgf")
					filename = filename.Left(filename.GetLength() - 4);
				filename += ".wrt";
				ReadWinRate(filename);*/
			}
			m_iStateReopen = 0;
			m_iStateArea = 0;
			if (m_iState == 2)
				m_iStateArea = 3;
			m_iStateGoBack = 0;
			m_iStateGoFiveBack = 0;
			m_iStateGoFirst = 0;
			m_iStateGoForward = 3;
			m_iStateGoFiveForward = 3;
			m_iStateGoLast = 3;
			if (m_iGoCount == m_iFixedStone)
			{
				m_iStateGoBack = 3;
				m_iStateGoFiveBack = 3;
				m_iStateGoFirst = 3;
			}
			m_bSgfLoaded = true;
			//暂存着手记录
			m_iOldGoCount = m_iGoCount;
			m_iOldGoCountMax = m_iGoCountMax;
			memcpy(m_OldGoRecord, m_GoRecord, sizeof(Data_GoRecord) * m_iGoCountMax);
			SaveMoveRecs();
			//保存棋谱文件名
			m_sSfgFileName = filedlg.GetFileName();
			m_sSgfPathName = filename;
			if (m_iState == 1)
			{
				m_sPlayInfo = "棋谱文件：" + m_sSfgFileName;
				if (iLanguage == 0)
					m_sPlayInfo = "File: " + m_sSfgFileName;
				m_sOtherInfo = m_Gameinfo.game_name + m_Gameinfo.game_comment;
				m_iStateArea = 0;
			}
			else
			{
				m_sOtherInfo = "棋谱文件：" + m_sSfgFileName;
				if (iLanguage == 0)
					m_sOtherInfo = "File: " + m_sSfgFileName;
			}
			//显示对局信息
			if (m_bGameOver)
			{
				m_sOutputInfo = "对弈结束，" + GetGameResult();
				if (iLanguage == 0)
					m_sOutputInfo = "Game ended, " + GetGameResult();
			}
			else
			{
				m_Gameinfo.to_move == BLACK ? m_sOutputInfo = "轮黑方着子" : m_sOutputInfo = "轮白方着子";
				if (iLanguage == 0)
					m_Gameinfo.to_move == BLACK ? m_sOutputInfo = "Waiting for black's move" : m_sOutputInfo = "Waiting for white's move";
			}
			if (m_iState == 1)//死活分析
			{
				OnGoFirst();
				if (m_Gameinfo.game_name.Find("白先", 0) >= 0 || m_Gameinfo.game_comment.Find("白先", 0) >= 0)
					m_Gameinfo.to_move = WHITE;
				else
					m_Gameinfo.to_move = BLACK;
				m_Gameinfo.to_move == BLACK ? m_sOutputInfo = "轮黑方着子" : m_sOutputInfo = "轮白方着子";
				if (iLanguage == 0)
					m_Gameinfo.to_move == BLACK ? m_sOutputInfo = "Waiting for black's move" : m_sOutputInfo = "Waiting for white's move";
				m_iFirstColor = m_Gameinfo.to_move;
				m_iColor = m_Gameinfo.to_move;
				if (m_iColor == BLACK)
				{
					m_iStateBlackFirst = 2;
					m_iStateWhiteFirst = 0;
				}
				else
				{
					m_iStateBlackFirst = 0;
					m_iStateWhiteFirst = 2;
				}
				m_iColor == BLACK ? m_cmbMb.SetCurSel(0) : m_cmbMb.SetCurSel(1);
				m_iMb = m_cmbMb.GetCurSel();
				m_bShowLifeDeathPanel = true;
				m_bAnaed = false;
				m_iState1 = 12;
			}
			else if (m_iState == 3)//序盘研究
			{
				CalGameTime();
				m_iColor = m_Gameinfo.to_move;
				m_bAnaed = false;
				if (filename.Right(13) == "_Analyzed.sgf")
				{
					m_bAnaed = true;
					m_bAllAnaed = true;
				}
				m_iState1 = 22;
				m_iStateNew = 0;
				m_iStateOpen = 0;
				m_iStateSave = 0;
				m_iStateExit = 0;
			}
			Invalidate();
			//PaintBoard();
		}

	}
	//strcpy_s(fpname,filename.GetLength(),filename);
	//sgfFreeNode(tree.root);
	//将sgf文件内容装入引擎
	/*CString str = "loadsgf ";
	str += filename;
	str += "\r\n";
	m_pEngine1->WriteToPipe(str);
	m_strOutput += str;
	int count;
	CString* strs = m_pEngine1->GetMsg(count);
	for (int i = 0; i < count; i++)
		m_strOutput += strs[i] + "\n";*/
	m_iStateOpen = 0;
}

void CSfcGoView::OnSave()
{
	if(m_iState1==21)//序盘研究-摆子状态
		GoRecordToSgf(m_iGoCount, m_GoRecord, m_iHandiCap, &m_Sgftree);
	//char sgfFilters[] =
	//	"棋谱文件 (*.sgf)|*.sgf|All Files (*.*)|*.*||";
	char sgfFilters[255];
	//if (iLanguage == 0)
		strcpy(sgfFilters, "Go record file (*.sgf)|*.sgf|All Files (*.*)|*.*||");
	//else
	//	strcpy(sgfFilters, "棋谱文件 (*.sgf)|*.sgf|All Files (*.*)|*.*||");
	CFileDialog filedlg(FALSE, "", ".sgf", OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, sgfFilters);
	if (filedlg.DoModal() == IDOK)
	{
		CString fileName = filedlg.GetPathName();//.GetFileName();
		char *tmpstring = fileName.GetBuffer();
		if (tmpstring) {
			/* discard newline */
			//tmpstring[strlen(tmpstring) - 1] = 0;
			//InitSgf(ginfo);
			SgfSaveData(&m_Sgftree);
			writesgf(m_Sgftree.root, tmpstring);
			//保存胜率数据
			if (fileName.Right(4) == ".sgf")
				fileName = fileName.Left(fileName.GetLength() - 4);
			fileName += ".wrt";
			SaveWinRate(fileName);
			m_iStateSave = 3;
		}
		else
			m_iStateSave = 0;
	}
	else
		m_iStateSave = 0;
}

void CSfcGoView::OnReopen()
{
	bool reload = false;
	CString filename = strSysDirectry;
	filename += "\\tmp.sgf";
	if (m_iCombat == 1 && m_iGoCount < m_iGoCountMax)
		OnGoLast();
	if (m_iGoCount < m_iGoCountMax)
	{
		CString msg = "当前着手不是最后一步，要从这里开始对弈吗？";
		if (iLanguage == 0)
			msg = "Currunt move is not the last, do you want to play at this point?";
		if (AfxMessageBox(msg, MB_YESNO) != IDYES)
			return;
		GoRecordToSgf(m_iGoCount, m_GoRecord, m_iFixedStone, &m_Sgftree);
		char* fpname = filename.GetBuffer();
		writesgf(m_Sgftree.root, fpname);
		reload = true;
	}
	else
	{
		if (m_bGameOver)
		{
			CString msg = "对弈已经结束！";
			if (iLanguage == 0)
				msg = "Game ended!";
			MessageBox(msg, MB_OK);
			m_iStateReopen = 0;
			return;
		}
	}
	SfcGtp* pengine;
	if (iEngineId == 0)
		pengine = m_pEngine1;
	else
		pengine = m_pEngine2;
	if (m_iState1 == 0)//读取棋谱状态
	{
		if (!reload)
		{
			char* fpname = filename.GetBuffer();
			writesgf(m_Sgftree.root, fpname);
		}
		m_bReOpen = true;
		OnNew();
		m_bRecall = false;
		return;
	}
	else//暂停状态
	{
		if (reload)
		{
			CString str = "loadsgf ";
			str += filename;
			str += "\r\n";
			pengine->WriteToPipe(str);
			int count;
			CString* strs = pengine->GetMsg(count);
			delete[] strs;
			m_Gameinfo.game_record = m_Sgftree;
			m_Gameinfo.to_move = OTHER_COLOR(m_GoRecord[m_iGoCount - 1].color);
		}
		if (m_iCombat == 1)
		{
			m_iStateOpen = 3;
			m_iStateSave = 3;
			m_iStateArea = 3;
			m_iStateExit = 3;
		}
		else
		{
			m_iStateOpen = 0;
			m_iStateSave = 0;
			m_iStateArea = 0;
			m_iStateExit = 0;
		}
		CTime ts = GetTickCount64();
		m_PauseTime += (ts.GetTime() - m_PauseStartTime.GetTime()) / 1000;
		m_PeriodTime = CTimeSpan(0, 0, 0, 0);
		SetTimer(m_Gameinfo.to_move, 1000, NULL);
		m_bPaused = false;
	}
	if (m_bSelfPlay || m_bEngineDual || m_Gameinfo.computer_player == m_Gameinfo.to_move)
	{
		m_iState1 = 2;
		m_bPicked = true;
		ComputerMove();
	}
	else
	{
		m_bPicked = false;
	}
	m_iState1 = 1;
	m_iStateReopen = 0;
	m_sOutputInfo = "轮玩家着手";
	if (iLanguage == 0)
		m_sOutputInfo = "Waiting for player's move";
	InvalidateRect(m_rPlayInfo);
	InvalidateRect(m_rToolBox);
}

void CSfcGoView::OnArea()
{
	float result = GetScore();
	CString str = "";
	if (iLanguage == 0)
	{
		if (result > 0)
			str += "White win";
		else if (result < 0)
			str += "Black win";
		else
			str += "Even";
		if (result != 0)
		{
			CString str1;
			str1.Format("%5.1f", abs(result));
			str += str1;
		}
		MessageBox(str, "Result");
	}
	else
	{
		if (result > 0)
			str += "白胜";
		else if (result < 0)
			str += "黑胜";
		else
			str += "平局";
		if (result != 0)
		{
			CString str1;
			str1.Format("%5.1f目", abs(result));
			str += str1;
		}
		MessageBox(str, "判断结果");
	}
	m_iStateArea = 0;
}

void CSfcGoView::OnExit()
{
	CString str;
	if (iLanguage == 0)
	{
		str = "Exit ";
		switch (m_iState)
		{
		case 1:
			str += "tesuji analysis?";
			break;
		case 2:
			str += "playing with computer?";
			break;
		case 3:
			str += "persistence study?";
			break;
		}
	}
	else
	{
		str = "退出";
		switch (m_iState)
		{
		case 1:
			str += "死活分析";
			break;
		case 2:
			str += "人机对弈";
			break;
		case 3:
			str += "序盘研究";
			break;
		}
		str += "吗？";
	}
	if (MessageBox(str, sMsg, MB_YESNO) != IDYES)
		return;
	if (iState == 2 && m_iStateSave != 3)//Prompt save game
	{
		if (iLanguage == 0)
			str = "Save this game?";
		else
			str = "保存对局吗？";
		if (MessageBox(str, sMsg, MB_YESNO) == IDYES)
			OnSave();
	}
	GetParentFrame()->PostMessageA(WM_CLOSE, 0, 0);
	m_iStateExit = 0;
}

void CSfcGoView::OnPass()
{
	CString msg = "PASS一手吗？";
	if (iLanguage == 0)
		msg = "Play a pass move?";
	if (MessageBox(msg, sMsg, MB_YESNO) != IDYES)
		return;
	int color = m_iColor;
	m_GoRecord[m_iGoCount].x = -1;
	m_GoRecord[m_iGoCount].y = -1;
	m_GoRecord[m_iGoCount].color = color;
	m_iGoCount++;
	CString smove = "B";
	if (color == WHITE)
		smove = "W";
	smove += " pass";
	m_sMoveRecs[m_iMoveCount] = smove;
	m_sMoveTimeRecs[m_iMoveCount].Format("%02d:%02d:%02d", m_PeriodTime.GetHours(), m_PeriodTime.GetMinutes(), m_PeriodTime.GetSeconds());
	if (color == BLACK)
		m_fMoveWinRates[m_iMoveCount] = m_fBlackWinRate;
	else
		m_fMoveWinRates[m_iMoveCount] = m_fWhiteWinRate;
	m_iMoveCount++;
	if (m_iState == 3)
	{
		m_iColor = OTHER_COLOR(color);
		m_GoInfo.gocolor = m_iColor;
		m_Gameinfo.to_move = m_iColor;
		m_iStateNew = 0;
		return;
	}
	m_iPasses++;
	sgftreeAddPlay(&m_Sgftree, m_Gameinfo.to_move, -1, -1);
	if (m_iPasses >= 2)//两次PASS，对弈结束
	{
		m_iPasses = 0;
		EndGame(&m_Gameinfo, 0);
		m_iGoCountMax = m_iGoCount;
		m_iState1 = 0;
		SetDlgItemText(IDC_STAT, "就绪");
		//m_sOutputInfo = "";
		InvalidateRect(m_rPlayInfo);
		this->InvalidateRect(m_rToolBox);
		this->UpdateWindow();
	}
	else
	{
		SfcGtp* pengine;
		if (iEngineId == 0)
			pengine = m_pEngine1;
		else
			pengine = m_pEngine2;
		CString msg = "play "+smove+"\r\n";
		pengine->WriteToPipe(msg);
		int count;
		CString* strs = pengine->GetMsg(count);
		delete[] strs;
		KillTimer(color);
		CTime t = GetTickCount64();
		CTimeSpan ts = (t.GetTime() - m_StartTime.GetTime()) / 1000;
		if (color == 2)
			m_BlackTime = ts - m_WhiteTime;//m_BlackTime.GetSeconds
		else
			m_WhiteTime = ts - m_BlackTime;
		m_PeriodTime = CTimeSpan(0, 0, 0, 0);
		SetTimer(OTHER_COLOR(color), 1000, NULL);
		m_Gameinfo.to_move = OTHER_COLOR(m_Gameinfo.to_move);
		ComputerMove();
	}
}

void CSfcGoView::OnRetract()
{
	int num = min(2, m_iGoCount - m_iFixedStone);
	if (num > 0) {
		if (m_iState1 == 13)//研究状态每次悔棋一步
		{
			num = 1;
			m_iColor = OTHER_COLOR(m_iColor);
		}
		else//非研究状态需更新引擎和棋步树
		{
			SfcGtp* pengine;
			if (iEngineId == 0)
				pengine = m_pEngine1;
			else
				pengine = m_pEngine2;
			for (int i = 0; i < num; i++)
			{
				CString str = "undo\r\n";
				pengine->WriteToPipe(str);
				int count;
				CString* strs = pengine->GetMsg(count);
				delete[] strs;
			}
			sgftreeAddComment(&m_Sgftree, "undone");
			sgftreeBack(&m_Sgftree);
		}
		//m_Gameinfo.to_move = OTHER_COLOR(m_Gameinfo.to_move);
		m_iGoCount -= num;
		m_GoInfo.Init(m_iBoardSize);
		for (int j = 0; j < m_iGoCount; j++)
			Sfc::PlayStone(m_GoRecord[j].x, m_GoRecord[j].y, m_GoRecord[j].color, m_GoInfo);
		CopyLocalBoard();
		m_iMoveCount -= num;
		if (m_iState == 1)
			m_iAnaMoveCount = 0;
		//PaintBoard();
		InvalidateRect(m_rBoardBack);
	}
	//else
	//	MessageBox("悔棋失败！");
	m_iStateOpen = 1;
}

void CSfcGoView::OnHint()
{
	if (m_iState1 == 1)//开始分析
	{
		m_iOldFixedStone = m_iFixedStone;
		m_iFixedStone = m_iGoCount;
		m_iOldGoCount = m_iGoCount;
		m_iOldState1 = m_iState1;
		if (m_bAnaed)//当前局面已经分析过，直接显示结果
		{
			m_sOutputInfo = "分析结束";
			m_sOtherInfo = "点击候选着手表可以查看后继着手";
			if (iLanguage == 0)
			{
				m_sOutputInfo = "Analyze complete";
				m_sOtherInfo = "Click move candidate to show following moves";
			}
			m_iState1 = 5;
			m_iStateNew = 3;
			m_iStateOpen = 3;
			m_iStateSave = 1;
			m_iStateReopen = 3;
			m_iStateArea = 3;
			m_iStateExit = 3;
			m_iStateResign = 3;
			this->InvalidateRect(m_rToolBox);
			return;
		}
		m_PauseTime = m_PeriodTime;
		m_PeriodTime = CTimeSpan(m_iComputerByoTime);
		m_sOutputInfo = "腾飞围棋正在分析......";
		if (iLanguage == 0)
			m_sOutputInfo = "SfcGo is analyzing...";
		iEngineThreadState = 1;
		AfxBeginThread(GetEngineAna, this);
		m_iState1 = 4;
		m_iStateNew = 3;
		m_iStateOpen = 3;
		m_iStateSave = 0;
		m_iStateReopen = 3;
		m_iStateArea = 3;
		m_iStateExit = 3;
		m_iStateResign = 3;
		this->InvalidateRect(m_rToolBox);
	}
	else if (m_iState1 == 4)//正在分析，中断
	{
		m_sOutputInfo = "分析被中断";
		if (iLanguage == 0)
			m_sOutputInfo = "Analysis is broken";
		SfcGtp* pengine;
		if (iEngineId == 0)
			pengine = m_pEngine1;
		else
			pengine = m_pEngine2;
		CString str = "\r\n";
		pengine->WriteToPipe(str);
		//int count;
		//CString* strs = pengine->GetMsg(count);
		//delete[] strs;
	}
	else if(m_iState1==5 || m_iState1==6)//正在查看分析结果，点击返回对弈状态
	{
		//恢复棋盘
		m_iFixedStone = m_iOldFixedStone;
		m_iGoCount = m_iOldGoCount;
		m_iGoCountMax = m_iGoCount;
		m_GoInfo.Init(m_iBoardSize);
		for (int j = 0; j < m_iGoCount; j++)
			Sfc::PlayStone(m_GoRecord[j].x, m_GoRecord[j].y, m_GoRecord[j].color, m_GoInfo);
		for (int j = 0; j < m_iBoardSize; j++)
			for (int k = 0; k < m_iBoardSize; k++)
				m_iBoard[j][k] = m_GoInfo.board[j][k];
		m_iState1 = m_iOldState1;
		m_sOutputInfo = "轮玩家着手";
		if (iLanguage == 0)
			m_sOutputInfo = "Waiting for player's move";
		m_sOtherInfo = "";
		m_iStateNew = 0;
		m_iStateOpen = 0;
		m_iStateSave = 1;
		m_iStateReopen = 0;
		m_iStateArea = 0;
		m_iStateExit = 0;
		m_iStateResign = 0;
		m_iAnaMoveId = 0;
		m_iAnaMoveStartId = 0;
		this->InvalidateRect(m_rToolBox);
	}
	//m_iStateSave = 0;
}

void CSfcGoView::OnPause()
{
	if (m_bSelfPlay || m_bEngineDual || m_Gameinfo.to_move == m_Gameinfo.computer_player)
	{
		pDlgNotify->m_sNotify = "正在终止电脑思考过程，请等候······";
		if (iLanguage == 0)
			pDlgNotify->m_sNotify = "Ending thinking process of computer...";
		pDlgNotify->Create(IDD_NOTIFY, this);
		pDlgNotify->ShowWindow(SW_SHOW);
		pDlgNotify->UpdateWindow();
		m_bPaused = true;
		m_iStateNew = 3;
		m_iStateOpen = 3;
		m_iStateSave = 3;
		m_iStateReopen = 3;
		m_iStateArea = 3;
		m_iStateExit = 3;
		m_iStateResign = 3;
		this->InvalidateRect(m_rToolBox);
		return;
	}
	m_bPaused = true;
	m_iGoCountMax = m_iGoCount;
	m_PauseStartTime = GetTickCount64();
	KillTimer(m_Gameinfo.to_move);
	m_iState1 = 3;
	m_iStateNew = 0;
	m_iStateOpen = 0;
	m_iStateSave = 0;
	m_iStateReopen = 0;
	if(m_iCombat==0)
		m_iStateArea = 0;
	m_iStateExit = 0;
	m_iStateResign = 0;
	m_sOutputInfo = "对弈暂停";
	if (iLanguage == 0)
		m_sOutputInfo = "Game paused";
	InvalidateRect(m_rPlayInfo);
	InvalidateRect(m_rToolBox);
}

void CSfcGoView::OnChangeStone()
{
	int l = iPlayer1;
	iPlayer1 = iPlayer2;
	iPlayer2 = l;
	l = iLevel1;
	iLevel1 = iLevel2;
	iLevel2 = l;
	l = iTime1;
	iTime1 = iTime2;
	iTime2 = l;
	l = iEngine1;
	iEngine1 = iEngine2;
	iEngine2 = l;
	//保存选项到系统文件
	Sfc::WriteSysIni();
	CString name = m_sBlackName;
	m_sBlackName = m_sWhiteName;
	m_sWhiteName = name;
	m_Gameinfo.computer_player = m_iColor;
	m_iColor = OTHER_COLOR(m_iColor);
	Invalidate();
	if (m_Gameinfo.computer_player == m_Gameinfo.to_move)
	{
		SetDlgItemText(IDC_STAT, sThinkMsg);
		m_sOutputInfo = sThinkMsg;
		InvalidateRect(m_rPlayInfo);
		m_iStateNew = 3;
		m_iStateOpen = 3;
		m_iStateSave = 3;
		m_iStateReopen = 0;
		m_iStateArea = 3;
		m_iStateExit = 3;
		m_iStateResign = 3;
		this->InvalidateRect(m_rToolBox);
		this->UpdateWindow();
		//UpdateData(FALSE);
		ComputerMove();
	}
	m_iStateExit = 0;
}

void CSfcGoView::OnResign()
{
	EndGame(&m_Gameinfo, 1);
	m_iGoCountMax = m_iGoCount;
	m_iState1 = 0;
	m_iStateResign = 0;
	//m_sOutputInfo = "";
	InvalidateRect(m_rPlayInfo);
	this->InvalidateRect(m_rToolBox);
	this->UpdateWindow();
}
void CSfcGoView::OnGoFirst()
{
	if (m_iState1 == 14 || m_iState == 1 && m_iState1 == 1)
	{
		m_iStateGoBack = 3;
		m_iStateGoFiveBack = 3;
		m_iStateGoFirst = 3;
		switch (iLDlevel)
		{
		case 0:
			if (iQuest0 <= 1)
				return;
			else
				iQuest0 = 1;
			break;
		case 1:
			if (iQuest1 <= 1)
				return;
			else
				iQuest1 = 1;
			break;
		case 2:
			if (iQuest2 <= 1)
				return;
			else
				iQuest2 = 1;
			break;
		case 3:
			if (iQuest3 <= 1)
				return;
			else
				iQuest3 = 1;
			break;
		}
		if (m_iState1 == 1)
			KillTimer(m_iColor);
		int state = m_iState1;
		OnContinueQuest();
		if (state == 1)
			OnNew();
		return;
	}
	if (m_iGoCount == m_iFixedStone)
		return;
	//双方用时
	if (m_iState1 == 22)
	{
		m_BlackTime = CTimeSpan(0);
		m_WhiteTime = CTimeSpan(0);
	}
	m_iGoCount = m_iFixedStone;
	if (m_iState1 != 6)
		m_iMoveCount = 0;
	if (m_iState == 3)
		m_iMoveCount = m_iFixedStone;
	m_iRecallId = m_iGoCount-1;
	m_GoInfo.Init(m_iBoardSize);
	for (int j = 0; j < m_iGoCount; j++)
		Sfc::PlayStone(m_GoRecord[j].x, m_GoRecord[j].y, m_GoRecord[j].color, m_GoInfo);
	for (int j = 0; j < m_iBoardSize; j++)
		for (int k = 0; k < m_iBoardSize; k++)
			m_iBoard[j][k] = m_GoInfo.board[j][k];
	//GetLifeDeathAllowedMoveString(1);
	m_Gameinfo.to_move = m_GoInfo.gocolor;
	m_Gameinfo.to_move == BLACK ? m_sOutputInfo = "轮黑方着子" : m_sOutputInfo = "轮白方着子";
	if (iLanguage == 0)
		m_Gameinfo.to_move == BLACK ? m_sOutputInfo = "Waiting for black's move" : m_sOutputInfo = "Waiting for white's move";
	if (m_iState1 == 13)
		m_iColor = m_Gameinfo.to_move;
	PaintBoard();
	m_iStateGoFiveBack = 3;
	m_iStateGoBack = 3;
	m_iStateGoFirst = 3;
	InvalidateRect(m_rGoFiveBack);
	InvalidateRect(m_rGoBack);
	InvalidateRect(m_rGoFirst);
	if (m_iGoCount + 5 <= m_iGoCountMax)
	{
		m_iStateGoFiveForward = 0;
		InvalidateRect(m_rGoFiveForward);
	}
	if (m_iGoCount <= m_iGoCountMax)
	{
		m_iStateGoForward = 0;
		InvalidateRect(m_rGoForward);
		m_iStateGoLast = 0;
		InvalidateRect(m_rGoLast);
	}
	if (bPutStoneSound)
	{
		PlaySound(strSysDirectry + "\\Stone.wav", NULL, SND_ASYNC);
		Sleep(100);
		PlaySound(strSysDirectry + "\\Stone.wav", NULL, SND_ASYNC);
		Sleep(100);
		PlaySound(strSysDirectry + "\\Stone.wav", NULL, SND_ASYNC);
	}
	if (m_iState == 3 && m_iState1 == 22)
		m_bRecall = false;
}

void CSfcGoView::OnGoFiveBack()
{
	if (m_iState1 == 14 || m_iState == 1 && m_iState1 == 1)
	{
		switch (iLDlevel)
		{
		case 0:
			if (iQuest0 <= 1)
			{
				m_iStateGoBack = 3;
				m_iStateGoFiveBack = 3;
				m_iStateGoFirst = 3;
				return;
			}
			else
			{
				iQuest0 -= 5;
				if (iQuest0 <= 1)
				{
					iQuest0 = 1;
					m_iStateGoBack = 3;
					m_iStateGoFiveBack = 3;
					m_iStateGoFirst = 3;
				}
			}
			break;
		case 1:
			if (iQuest1 <= 1)
			{
				m_iStateGoBack = 3;
				m_iStateGoFiveBack = 3;
				m_iStateGoFirst = 3;
				return;
			}
			else
			{
				iQuest1 -= 5;
				if (iQuest1 <= 1)
				{
					iQuest1 = 1;
					m_iStateGoBack = 3;
					m_iStateGoFiveBack = 3;
					m_iStateGoFirst = 3;
				}
			}
			break;
		case 2:
			if (iQuest2 <= 1)
			{
				m_iStateGoBack = 3;
				m_iStateGoFiveBack = 3;
				m_iStateGoFirst = 3;
				return;
			}
			else
			{
				iQuest2 -= 5;
				if (iQuest2 <= 1)
				{
					iQuest2 = 1;
					m_iStateGoBack = 3;
					m_iStateGoFiveBack = 3;
					m_iStateGoFirst = 3;
				}
			}
			break;
		case 3:
			if (iQuest3 <= 1)
			{
				m_iStateGoBack = 3;
				m_iStateGoFiveBack = 3;
				m_iStateGoFirst = 3;
				return;
			}
			else
			{
				iQuest3 -= 5;
				if (iQuest3 <= 1)
				{
					iQuest3 = 1;
					m_iStateGoBack = 3;
					m_iStateGoFiveBack = 3;
					m_iStateGoFirst = 3;
				}
			}
			break;
		}
		if (m_iState1 == 1)
			KillTimer(m_iColor);
		int state = m_iState1;
		OnContinueQuest();
		if (state == 1)
			OnNew();
		return;
	}
	if (m_iGoCount < 5 + m_iFixedStone)
	{
		m_iStateGoFiveBack = 3;
		return;
	}
	//双方用时
	if (m_iState1 == 22)
	{
		CalGameTime(-5);
	}
	m_iRecallId -= 5;
	m_iGoCount -= 5;
	if (m_iState1 != 6 || m_iState == 3)
		m_iMoveCount -= 5;
	m_GoInfo.Init(m_iBoardSize);
	for (int j = 0; j < m_iGoCount; j++)
		Sfc::PlayStone(m_GoRecord[j].x, m_GoRecord[j].y, m_GoRecord[j].color, m_GoInfo);
	for (int j = 0; j < m_iBoardSize; j++)
		for (int k = 0; k < m_iBoardSize; k++)
			m_iBoard[j][k] = m_GoInfo.board[j][k];
	m_Gameinfo.to_move = m_GoInfo.gocolor;
	m_Gameinfo.to_move == BLACK ? m_sOutputInfo = "轮黑方着子" : m_sOutputInfo = "轮白方着子";
	if (iLanguage == 0)
		m_Gameinfo.to_move == BLACK ? m_sOutputInfo = "Waiting for black's move" : m_sOutputInfo = "Waiting for white's move";
	if (m_iState1 == 13)
		m_iColor = m_Gameinfo.to_move;
	PaintBoard();
	//m_iStateGoFiveBack = 1;
	if (m_iGoCount < 5+m_iFixedStone)
	{
		m_iStateGoFiveBack = 3;
		InvalidateRect(m_rGoFiveBack);
	}
	if (m_iGoCount <= m_iFixedStone)
	{
		m_iStateGoBack = 3;
		InvalidateRect(m_rGoBack);
		m_iStateGoFirst = 3;
		InvalidateRect(m_rGoFirst);
	}
	if (m_iGoCount + 5 <= m_iGoCountMax)
	{
		m_iStateGoFiveForward = 0;
		InvalidateRect(m_rGoFiveForward);
	}
	if (m_iGoCount <= m_iGoCountMax)
	{
		m_iStateGoForward = 0;
		InvalidateRect(m_rGoForward);
		m_iStateGoLast = 0;
		InvalidateRect(m_rGoLast);
	}
	if (bPutStoneSound)
	{
		PlaySound(strSysDirectry + "\\Stone.wav", NULL, SND_ASYNC);
		Sleep(100);
		PlaySound(strSysDirectry + "\\Stone.wav", NULL, SND_ASYNC);
	}
}

void CSfcGoView::OnGoBack()
{
	if (m_iState1 == 14 || m_iState == 1 && m_iState1 == 1)
	{
		switch (iLDlevel)
		{
		case 0:
			if (iQuest0 <= 1)
			{
				m_iStateGoBack = 3;
				m_iStateGoFiveBack = 3;
				m_iStateGoFirst = 3;
				return;
			}
			else
				iQuest0--;
			break;
		case 1:
			if (iQuest1 <= 1)
			{
				m_iStateGoBack = 3;
				m_iStateGoFiveBack = 3;
				m_iStateGoFirst = 3;
				return;
			}
			else
				iQuest1--;
			break;
		case 2:
			if (iQuest2 <= 1)
			{
				m_iStateGoBack = 3;
				m_iStateGoFiveBack = 3;
				m_iStateGoFirst = 3;
				return;
			}
			else
				iQuest2--;
			break;
		case 3:
			if (iQuest3 <= 1)
			{
				m_iStateGoBack = 3;
				m_iStateGoFiveBack = 3;
				m_iStateGoFirst = 3;
				return;
			}
			else
				iQuest3--;
			break;
		}
		if (m_iState1 == 1)
			KillTimer(m_iColor);
		int state = m_iState1;
		OnContinueQuest();
		if (state == 1)
			OnNew();
		return;
	}
	if (m_iGoCount <= 0)
	{
		m_iStateGoBack = 3;
		return;
	}
	//双方用时
	if (m_iState1 == 22)
	{
		CalGameTime(-1);
	}
	m_iRecallId--;
	m_iGoCount--;
	if (m_iState1 != 6 || m_iState == 3)
		m_iMoveCount--;
	m_GoInfo.Init(m_iBoardSize);
	for (int j = 0; j < m_iGoCount; j++)
		Sfc::PlayStone(m_GoRecord[j].x, m_GoRecord[j].y, m_GoRecord[j].color, m_GoInfo);
	for (int j = 0; j < m_iBoardSize; j++)
		for (int k = 0; k < m_iBoardSize; k++)
			m_iBoard[j][k] = m_GoInfo.board[j][k];
	m_Gameinfo.to_move = m_GoInfo.gocolor;
	m_Gameinfo.to_move == BLACK ? m_sOutputInfo = "轮黑方着子" : m_sOutputInfo = "轮白方着子";
	if (iLanguage == 0)
		m_Gameinfo.to_move == BLACK ? m_sOutputInfo = "Waiting for black's move" : m_sOutputInfo = "Waiting for white's move";
	if (m_iState1 == 13)
		m_iColor = m_Gameinfo.to_move;
	PaintBoard();
	//m_iStateGoBack = 1;
	if (m_iGoCount < 5+m_iFixedStone)
	{
		m_iStateGoFiveBack = 3;
		InvalidateRect(m_rGoFiveBack);
	}
	if (m_iGoCount <= m_iFixedStone)
	{
		m_iStateGoBack = 3;
		InvalidateRect(m_rGoBack);
		m_iStateGoFirst = 3;
		InvalidateRect(m_rGoFirst);
	}
	if (m_iGoCount + 5 <= m_iGoCountMax)
	{
		m_iStateGoFiveForward = 0;
		InvalidateRect(m_rGoFiveForward);
	}
	if (m_iGoCount <= m_iGoCountMax)
	{
		m_iStateGoForward = 0;
		InvalidateRect(m_rGoForward);
		m_iStateGoLast = 0;
		InvalidateRect(m_rGoLast);
	}
	if (bPutStoneSound)
		PlaySound(strSysDirectry + "\\Stone.wav", NULL, SND_ASYNC);
}

void CSfcGoView::OnGoForward()
{
	if (m_iState1 == 14 || m_iState == 1 && m_iState1 == 1)
	{
		switch (iLDlevel)
		{
		case 0:
			if (iQuest0 >= iQuestMax0)
			{
				m_iStateGoForward = 3;
				m_iStateGoFiveForward = 3;
				m_iStateGoLast = 3;
				return;
			}
			else
				iQuest0++;
			break;
		case 1:
			if (iQuest1 >= iQuestMax1)
			{
				m_iStateGoForward = 3;
				m_iStateGoFiveForward = 3;
				m_iStateGoLast = 3;
				return;
			}
			else
				iQuest1++;
			break;
		case 2:
			if (iQuest2 >= iQuestMax2)
			{
				m_iStateGoForward = 3;
				m_iStateGoFiveForward = 3;
				m_iStateGoLast = 3;
				return;
			}
			else
				iQuest2++;
			break;
		case 3:
			if (iQuest3 >= iQuestMax3)
			{
				m_iStateGoForward = 3;
				m_iStateGoFiveForward = 3;
				m_iStateGoLast = 3;
				return;
			}
			else
				iQuest3++;
			break;
		}
		if (m_iState1 == 1)
			KillTimer(m_iColor);
		int state = m_iState1;
		OnContinueQuest();
		if (state == 1)
			OnNew();
		return;
	}
	if (m_iGoCount >= m_iGoCountMax)
	{
		m_iStateGoForward = 3;
		return;
	}
	//双方用时
	if (m_iState1 == 22)
	{
		CalGameTime(1);
	}
	if (m_iState1 != 6 && m_iState1!=13 || m_iState == 3)
		m_iMoveCount++;
	m_iRecallId++;
	Sfc::PlayStone(m_GoRecord[m_iGoCount].x, m_GoRecord[m_iGoCount].y, m_GoRecord[m_iGoCount].color, m_GoInfo);
	AddStone(m_GoRecord[m_iGoCount].x, m_GoRecord[m_iGoCount].y, m_GoRecord[m_iGoCount].color);
	m_Gameinfo.to_move = m_GoInfo.gocolor;
	if (m_iGoCount >= m_iGoCountMax && m_bGameOver)
	{
		m_sOutputInfo = "对弈结束，" + GetGameResult();
		if (iLanguage == 0)
			m_sOutputInfo = "Game ended, " + GetGameResult();
	}
	else
	{
		m_Gameinfo.to_move == BLACK ? m_sOutputInfo = "轮黑方着子" : m_sOutputInfo = "轮白方着子";
		if (iLanguage == 0)
			m_Gameinfo.to_move == BLACK ? m_sOutputInfo = "Waiting for black's move" : m_sOutputInfo = "Waiting for white's move";
	}
	if (m_iState1 == 13)
		m_iColor = m_Gameinfo.to_move;
	//m_iStateGoForward = 1;
	if (m_iGoCount + 5 > m_iGoCountMax)
	{
		m_iStateGoFiveForward = 3;
		InvalidateRect(m_rGoFiveForward);
	}
	if (m_iGoCount >= m_iGoCountMax)
	{
		m_iStateGoForward = 3;
		InvalidateRect(m_rGoForward);
		m_iStateGoLast = 3;
		InvalidateRect(m_rGoLast);
	}
	if (m_iGoCount >= 5+m_iFixedStone)
	{
		m_iStateGoFiveBack = 0;
		InvalidateRect(m_rGoFiveBack);
	}
	if (m_iGoCount > m_iFixedStone)
	{
		m_iStateGoBack = 0;
		InvalidateRect(m_rGoBack);
		m_iStateGoFirst = 0;
		InvalidateRect(m_rGoFirst);
	}
	if (bPutStoneSound && m_iState1 != 21 && m_iState1 != 13)
		PlaySound(strSysDirectry + "\\Stone.wav", NULL, SND_ASYNC);
	if (m_bCaptured && bCaptureSound)
	{
		m_bCaptured = false;
		Sleep(500);
		PlaySound(strSysDirectry + "\\Capture.wav", NULL, SND_ASYNC);
	}
}

void CSfcGoView::OnGoFiveForward()
{
	if (m_iState1 == 14 || m_iState == 1 && m_iState1 == 1)
	{
		switch (iLDlevel)
		{
		case 0:
			if (iQuest0 >= iQuestMax0)
			{
				m_iStateGoForward = 3;
				m_iStateGoFiveForward = 3;
				m_iStateGoLast = 3;
				return;
			}
			else
			{
				iQuest0 += 5;
				if (iQuest0 >= iQuestMax0)
				{
					iQuest0 = iQuestMax0;
					m_iStateGoForward = 3;
					m_iStateGoFiveForward = 3;
					m_iStateGoLast = 3;
				}
			}
			break;
		case 1:
			if (iQuest1 >= iQuestMax1)
			{
				m_iStateGoForward = 3;
				m_iStateGoFiveForward = 3;
				m_iStateGoLast = 3;
				return;
			}
			else
			{
				iQuest1 += 5;
				if (iQuest1 >= iQuestMax1)
				{
					iQuest1 = iQuestMax1;
					m_iStateGoForward = 3;
					m_iStateGoFiveForward = 3;
					m_iStateGoLast = 3;
				}
			}
			break;
		case 2:
			if (iQuest2 >= iQuestMax2)
			{
				m_iStateGoForward = 3;
				m_iStateGoFiveForward = 3;
				m_iStateGoLast = 3;
				return;
			}
			else
			{
				iQuest2 += 5;
				if (iQuest2 >= iQuestMax2)
				{
					iQuest2 = iQuestMax2;
					m_iStateGoForward = 3;
					m_iStateGoFiveForward = 3;
					m_iStateGoLast = 3;
				}
			}
			break;
		case 3:
			if (iQuest3 >= iQuestMax3)
			{
				m_iStateGoForward = 3;
				m_iStateGoFiveForward = 3;
				m_iStateGoLast = 3;
				return;
			}
			else
			{
				iQuest3 += 5;
				if (iQuest3 >= iQuestMax3)
				{
					iQuest3 = iQuestMax3;
					m_iStateGoForward = 3;
					m_iStateGoFiveForward = 3;
					m_iStateGoLast = 3;
				}
			}
			break;
		}
		if (m_iState1 == 1)
			KillTimer(m_iColor);
		int state = m_iState1;
		OnContinueQuest();
		if (state == 1)
			OnNew();
		return;
	}
	if (m_iGoCount + 5 > m_iGoCountMax)
	{
		m_iStateGoFiveForward = 3;
		return;
	}
	//双方用时
	if (m_iState1 == 22)
	{
		CalGameTime(5);
	}
	if (m_iState1 != 6 && m_iState1 != 13 || m_iState == 3)
		m_iMoveCount += 5;
	bool bputstonesound = bPutStoneSound;
	bPutStoneSound = false;
	for (int i = 0; i < 5; i++)
	{
		Sfc::PlayStone(m_GoRecord[m_iGoCount].x, m_GoRecord[m_iGoCount].y, m_GoRecord[m_iGoCount].color, m_GoInfo);
		AddStone(m_GoRecord[m_iGoCount].x, m_GoRecord[m_iGoCount].y, m_GoRecord[m_iGoCount].color);
	}
	bPutStoneSound = bputstonesound;
	m_Gameinfo.to_move = m_GoInfo.gocolor;
	if (m_iGoCount >= m_iGoCountMax && m_bGameOver)
	{
		m_sOutputInfo = "对弈结束，" + GetGameResult();
		if (iLanguage == 0)
			m_sOutputInfo = "Game ended, " + GetGameResult();
	}
	else
	{
		m_Gameinfo.to_move == BLACK ? m_sOutputInfo = "轮黑方着子" : m_sOutputInfo = "轮白方着子";
		if (iLanguage == 0)
			m_Gameinfo.to_move == BLACK ? m_sOutputInfo = "Waiting for black's move" : m_sOutputInfo = "Waiting for white's move";
	}
	if (m_iState1 == 13)
		m_iColor = m_Gameinfo.to_move;
	m_iRecallId = m_iGoCount - 1;;
	//m_iStateGoFiveForward = 1;
	if (m_iGoCount + 5 > m_iGoCountMax)
	{
		m_iStateGoFiveForward = 3;
		InvalidateRect(m_rGoFiveForward);
	}
	if (m_iGoCount >= m_iGoCountMax)
	{
		m_iStateGoForward = 3;
		InvalidateRect(m_rGoForward);
		m_iStateGoLast = 3;
		InvalidateRect(m_rGoLast);
	}
	if (m_iGoCount >= 5+m_iFixedStone)
	{
		m_iStateGoFiveBack = 0;
		InvalidateRect(m_rGoFiveBack);
	}
	if (m_iGoCount > m_iFixedStone)
	{
		m_iStateGoBack = 0;
		InvalidateRect(m_rGoBack);
		m_iStateGoFirst = 0;
		InvalidateRect(m_rGoFirst);
	}
	if (bPutStoneSound)
	{
		PlaySound(strSysDirectry + "\\Stone.wav", NULL, SND_ASYNC);
		Sleep(100);
		PlaySound(strSysDirectry + "\\Stone.wav", NULL, SND_ASYNC);
	}
}

void CSfcGoView::OnGoLast()
{
	if (m_iState1 == 14 || m_iState == 1 && m_iState1 == 1)
	{
		m_iStateGoForward = 3;
		m_iStateGoFiveForward = 3;
		m_iStateGoLast = 3;
		switch (iLDlevel)
		{
		case 0:
			if (iQuest0 >= iQuestMax0)
				return;
			else
				iQuest0=iQuestMax0;
			break;
		case 1:
			if (iQuest1 >= iQuestMax1)
				return;
			else
				iQuest1 = iQuestMax1;
			break;
		case 2:
			if (iQuest2 >= iQuestMax2)
				return;
			else
				iQuest2 = iQuestMax2;
			break;
		case 3:
			if (iQuest3 >= iQuestMax3)
				return;
			else
				iQuest3 = iQuestMax3;
			break;
		}
		if (m_iState1 == 1)
			KillTimer(m_iColor);
		int state = m_iState1;
		OnContinueQuest();
		if (state == 1)
			OnNew();
		return;
	}
	if (m_iState1 != 6 && m_iState1 != 13 || m_iState == 3)
		m_iMoveCount = m_iGoCountMax - m_iFixedStone;
	//双方用时
	if (m_iState1 == 22)
	{
		CalGameTime();
	}
	bool bputstonesound = bPutStoneSound;
	bPutStoneSound = false;
	while (m_iGoCount < m_iGoCountMax)
	{
		Sfc::PlayStone(m_GoRecord[m_iGoCount].x, m_GoRecord[m_iGoCount].y, m_GoRecord[m_iGoCount].color, m_GoInfo);
		AddStone(m_GoRecord[m_iGoCount].x, m_GoRecord[m_iGoCount].y, m_GoRecord[m_iGoCount].color);
	}
	bPutStoneSound = bputstonesound;
	m_Gameinfo.to_move = m_GoInfo.gocolor;
	if (m_bGameOver)
	{
		m_sOutputInfo = "对弈结束，" + GetGameResult();
		if (iLanguage == 0)
			m_sOutputInfo = "Game ended, " + GetGameResult();
	}
	else
	{
		m_Gameinfo.to_move == BLACK ? m_sOutputInfo = "轮黑方着子" : m_sOutputInfo = "轮白方着子";
		if (iLanguage == 0)
			m_Gameinfo.to_move == BLACK ? m_sOutputInfo = "Waiting for black's move" : m_sOutputInfo = "Waiting for white's move";
	}
	if (m_iState1 == 13)
		m_iColor = m_Gameinfo.to_move;
	m_iRecallId = m_iGoCount - 1;
	m_iStateGoForward = 3;
	m_iStateGoFiveForward = 3;
	m_iStateGoLast = 3;
	InvalidateRect(m_rGoFiveForward);
	InvalidateRect(m_rGoForward);
	InvalidateRect(m_rGoLast);
	if (m_iGoCount >= 5+m_iFixedStone)
	{
		m_iStateGoFiveBack = 0;
		InvalidateRect(m_rGoFiveBack);
	}
	if (m_iGoCount > m_iFixedStone)
	{
		m_iStateGoBack = 0;
		InvalidateRect(m_rGoBack);
		m_iStateGoFirst = 0;
		InvalidateRect(m_rGoFirst);
	}
	if (bPutStoneSound)
	{
		PlaySound(strSysDirectry + "\\Stone.wav", NULL, SND_ASYNC);
		Sleep(100);
		PlaySound(strSysDirectry + "\\Stone.wav", NULL, SND_ASYNC);
		Sleep(100);
		PlaySound(strSysDirectry + "\\Stone.wav", NULL, SND_ASYNC);
	}
}


void CSfcGoView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC* pDC = GetDC();
	CString s;
	switch (nIDEvent)
	{
	case 1://白棋方计时
	{
		m_WhiteTime += CTimeSpan(0, 0, 0, 1);
		/*s.Format("%02d:%02d:%02d", m_WhiteTime.GetHours(), m_WhiteTime.GetMinutes(), m_WhiteTime.GetSeconds());
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkColor(RGB(186, 186, 186));
		pDC->TextOutA(m_rWhiteTime.left, m_rWhiteTime.top, s);*/
		//CFont font;
		//font.CreateFontA(m_iGap / 2, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
		//CDC* pDC = GetDC();
		//CFont* oldfont = pDC->SelectObject(&font);
		//if (m_GoRecord[id].color == 1)
		//else
		//	pDC->SetTextColor(RGB(255, 255, 255));
		//pDC->SetBkMode(TRANSPARENT);
		//CSize size = pDC->GetTextExtent(s);
		//int cx = m_rWhiteInfo.left + m_iGap / 2;
		//int cy = (m_rWhiteInfo.top + m_rWhiteInfo.bottom) / 2;
		//pDC->SelectObject(oldfont);
		//font.DeleteObject();
		//ReleaseDC(pDC);
		break;
	}
	case 2://黑棋方计时
	{
		m_BlackTime += CTimeSpan(0, 0, 0, 1);
		/*s.Format("%02d:%02d:%02d", m_BlackTime.GetHours(), m_BlackTime.GetMinutes(), m_BlackTime.GetSeconds());
		pDC->SetTextColor(RGB(186, 186, 186));
		pDC->SetBkColor(BLACK);
		pDC->TextOutA(m_rBlackTime.left, m_rBlackTime.top, s);*/
		//CString s;
		//CFont font;
		//font.CreateFontA(m_iGap / 2, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
		//CDC* pDC = GetDC();
		//CFont* oldfont = pDC->SelectObject(&font);
		//pDC->SetBkMode(TRANSPARENT);
		//CSize size = pDC->GetTextExtent(s);
		//int cx = m_rBlackInfo.left + m_iGap / 2;
		//int cy = (m_rBlackInfo.top + m_rBlackInfo.bottom) / 2;
		//CRect rt(cx, cy, size.cx + cx, size.cy + cy);
		//InvalidateRect(rt);
		//UpdateWindow();
		//pDC->DrawText
		//pDC->SelectObject(oldfont);
		//font.DeleteObject();
		//ReleaseDC(pDC);
	}
		break;
	}
	//进度条
	if (m_iState1 != 4)
		m_PeriodTime += CTimeSpan(0, 0, 0, 1);
	pDC->SetTextColor(RGB(186, 186, 186));
	if(!m_bSelfPlay && !m_bEngineDual && nIDEvent==m_iColor || nIDEvent==4)
	{
		if (m_iState1 == 1 || m_iState1==5)//等待玩家落子
		{
			//单步用时
			s.Format("%02d:%02d:%02d", m_PeriodTime.GetHours(), m_PeriodTime.GetMinutes(), m_PeriodTime.GetSeconds());
			pDC->SetBkColor(RGB(76, 76, 76));
			pDC->TextOutA(m_rPeriodTime.left, m_rPeriodTime.top, s);
			ReleaseDC(pDC);
		}
		else if (m_iState1 == 4)//分析中
		{
			ReleaseDC(pDC);
			m_PauseTime += CTimeSpan(1);
			CSingleLock sl(&csCs);
			int enginethreadstate = 0;
			sl.Lock();
			{
				enginethreadstate = iEngineThreadState;
			}
			if (enginethreadstate == 2)//分析结束
			{
				m_iProgress = 0;
				iEngineThreadState = 0;
				m_iAnaMoveStartId = 0;
				if (m_bAnaAll)
				{
					m_iState1 = 7;
					OnAnaAll();
					return;
				}
				m_PeriodTime = m_PauseTime;
				m_PauseTime = CTimeSpan(0, 0, 0, 0);
				m_bAnaed = true;
				m_sOutputInfo = "分析结束";
				//m_sOtherInfo = "点击AI支招按钮可返回对弈状态";
				m_sOtherInfo = "点击候选着手表可以查看后继着手";
				if (iLanguage == 0)
				{
					m_sOutputInfo = "Analyze complete";
					m_sOtherInfo = "Click move candidate to show following moves";
				}
				if (m_iState == 1)//死活分析
				{
					m_sOtherInfo = "点击候选着手表可以查看其他着手";
					if (iLanguage == 0)
						m_sOtherInfo = "Click move candidate to show other moves";
					//m_iState1 = m_iOldState1;
					m_iState1 = 6;
					int id = 0, x1, y1, xs[361], ys[361];
					int count = GetLifeDeathAllowedMoves(m_iADColor, xs, ys);
					for (int i = 0; i < m_iAnaMoveCount; i++)
					{
						Trans(m_sAnaMoveRecs[i], x1, y1);
						int j;
						for (j = 0; j < count; j++)
						{
							if (x1 == xs[j] && y1 == ys[j])
								break;
						}
						if (j < count)
						{
							id = i;
							break;
						}
					}
					m_iAnaMoveId = id;
					ShowAnaMove();
					m_iStateNew = 0;
					m_iStateOpen = 0;
					m_iStateSave = 0;
					m_iStateReopen = 0;
					m_iStateArea = 0;
					m_iStateExit = 0;
					m_iStateResign = 0;
				}
				else
				{
					m_iState1 = 5;
					m_iStateNew = 0;
					m_iStateOpen = 0;
					m_iStateExit = 0;
					m_iAnaMoveId = 0;
					if (m_iOldState1 == 22)
						m_iStateNew = 3;
					if (m_iState == 2)
					{
						m_iStateNew = 3;
						m_iStateOpen = 3;
						m_iStateExit = 3;
					}
				}
				m_iStateSave = 0;
				this->InvalidateRect(m_rToolBox);
				KillTimer(4);
			}
			else//正在分析
			{
				if (m_iProgress < 100)
				{
					m_PeriodTime -= CTimeSpan(1);
					int byotime = m_iComputerByoTime;
					int usedtime = m_iComputerByoTime - m_PeriodTime.GetTotalSeconds();
					m_iProgress = 100 * usedtime / byotime;
					if (m_iProgress >= 100)//已超时，发出指令中断分析
					{
						m_iProgress = 100;
						SfcGtp* pengine;
						if (iEngineId == 0)
							pengine = m_pEngine1;
						else
							pengine = m_pEngine2;
						CString str = "\r\n";
						pengine->WriteToPipe(str);
					}
				}
			}
			InvalidateRect(m_rProgressBar);
			UpdateWindow();
		}
	}
	else//电脑着手后继处理
	{
		CSingleLock sl(&csCs);
		int enginethreadstate = 0;
		sl.Lock();
		{
			enginethreadstate = iEngineThreadState;
		}
		sl.Unlock();
		if (enginethreadstate == 2)//电脑思考结束
		{
			ReleaseDC(pDC);
			iEngineThreadState = 0;
			ComputerMove2();
			if (m_iProgress > 0)
			{
				m_iProgress = 0;
				InvalidateRect(m_rProgressBar);
				UpdateWindow();
			}
		}
		else if (enginethreadstate == 1 && bThinkProgress)//电脑正在思考中
		{
			int byotime = m_iComputerByoTime;
			if ((m_bSelfPlay || m_bEngineDual) && nIDEvent == 1)
				byotime = m_iComputerByoTime2;
			m_iProgress = 100 * m_PeriodTime.GetTotalSeconds() / byotime;
			if (m_iState==1 && m_iProgress >= 100)//死活答题，分析已超时，发出指令中断分析
			{
				m_iProgress = 100;
				SfcGtp* pengine;
				if (iEngineId == 0)
					pengine = m_pEngine1;
				else
					pengine = m_pEngine2;
				CString str = "\r\n";
				pengine->WriteToPipe(str);
			}
			int w = m_rProgressBar.Width() * m_iProgress / 100.0;
			CBrush* poldBrush = pDC->GetCurrentBrush();
			CBrush blueBrush;
			blueBrush.CreateSolidBrush(RGB(0, 0, 200));
			pDC->SelectObject(blueBrush);
			pDC->Rectangle(m_rProgressBar.left, m_rProgressBar.top, m_rProgressBar.left + w, m_rProgressBar.bottom);
			s = "单步用时";
			if (iLanguage == 0)
				s = "Period time";
			pDC->SetBkMode(TRANSPARENT);
			pDC->TextOutA(m_rPeriodString.left, m_rPeriodString.top, s);
			pDC->SelectObject(poldBrush);
		}
		//单步用时
			if (!bThinkProgress || m_iProgress < 100 * (m_rPeriodTime.left - m_rProgressBar.left) / m_rProgressBar.Width())
			{
				s.Format("%02d:%02d:%02d", m_PeriodTime.GetHours(), m_PeriodTime.GetMinutes(), m_PeriodTime.GetSeconds());
				pDC->SetBkColor(RGB(76, 76, 76));
				pDC->SetBkMode(OPAQUE);
				pDC->TextOutA(m_rPeriodTime.left, m_rPeriodTime.top, s);
				ReleaseDC(pDC);
			}
			else
			{
				ReleaseDC(pDC);
				InvalidateRect(m_rPeriodTime);
				UpdateWindow();
			}
	}

	CFormView::OnTimer(nIDEvent);
}

//创建SGF树头
void CSfcGoView::CreateSgfHead(SGFTree* tree, int boardsize, float komi, int handicap)
{
	SGFNode* root = sgfNewNode();
	char* cs = "SfcGo:2.0";
	sgfAddProperty(root, "AP", cs);
	sgfAddPropertyInt(root, "SZ", boardsize);
	sgfAddPropertyFloat(root, "KM", komi);
	sgfAddPropertyInt(root, "HA", handicap);
	CString str = "";
	switch (iRule)
	{
	case 0:
		str = "Chinese";
		break;
	case 1:
		str = "Japanese";
		break;
	case 2:
		str = "Korean";
		break;
	}
	cs = str.GetBuffer();
	//strcpy_s(cs, str.GetLength(), str);
	sgfAddProperty(root, "RU", cs);
	if (m_iCombat == 1)
		str = "Combat";
	else
		str = "Training";
	cs = str.GetBuffer();
	sgfAddProperty(root, "EV", cs);
	str = m_sBlackName;
	if (iPlayer1 != 0)
	{
		str.Format("SfcGo lvl%d.%d.%d", iLevel1, iTime1, iEngine1);
	}
	else if (iLevel1 >= 0)
	{
		CString str1;
		str1.Format(" lvl%d", iLevel1);
		str += str1;
	}
	cs = str.GetBuffer();
	//strcpy_s(cs, str.GetLength(), str);
	sgfAddProperty(root, "PB", cs);
	str = m_sWhiteName;
	if (iPlayer2 != 0)
	{
		str.Format("SfcGo lvl%d.%d.%d", iLevel2, iTime2, iEngine2);
	}
	else if (iLevel2 >= 0)
	{
		CString str1;
		str1.Format(" lvl%d", iLevel2);
		str += str1;
	}
	cs = str.GetBuffer();
	//strcpy_s(cs,str.GetLength(), str);
	sgfAddProperty(root, "PW", cs);
	tree->root = root;
	tree->lastnode = root;
}

//获取SGF对弈双方信息
bool CSfcGoView::GetSgfPlayerInfo(SGFProperty* prop)
{
	CString name = prop->value;
	bool issfc = false;
	int lvl = -1;
	int t = 1;
	int engine = 0;
	int count;
	CString* strs = SfcGtp::SplitString(name, " ", count);
	if (count >= 2 && strs[1].Left(3) == "lvl")//判断是否为SfcGo棋谱
	{
		name = strs[0];
		if (name == "SfcGo")
		{
			CString* strs1 = SfcGtp::SplitString(strs[1].Right(strs[1].GetLength() - 3), ".", count);
			if (count >= 3)
			{
				lvl = atoi(strs1[0]);
				t = atoi(strs1[1]);
				engine = atoi(strs1[2]);
				if (prop->name == SGFPB)
				{
					iPlayer1 = 1;
					//iLevel1 = lvl;
					iTime1 = t;
					iEngine1 = engine;
				}
				else
				{
					iPlayer2 = 1;
					//iLevel2 = lvl;
					iTime2 = t;
					iEngine2 = engine;
				}
				if(iLanguage==1)
					name = "腾飞围棋";
				issfc = true;
			}
			delete[] strs1;
		}
		else
		{
			lvl = atoi(strs[1].Right(strs[1].GetLength() - 3));
		}
	}
	if(!issfc)
		prop->name == SGFPB ? iPlayer1 = 0 : iPlayer2 = 0;
	if (prop->name == SGFPB)
	{
		m_sBlackName = name;
		iLevel1 = lvl;
	}
	else
	{
		m_sWhiteName = name;
		iLevel2 = lvl;
	}
	delete[] strs;
	return issfc;
}

//获取等级对应的头衔
CString CSfcGoView::GetLevelTitle(int lvl)
{
	CString slv = "";
	if (iLanguage == 0)
	{
		switch (lvl)
		{
		case 0:
			slv = "(5 kyu)";
			break;
		case 1:
			slv = "(4 kyu)";
			break;
		case 2:
			slv = "(3 kyu)";
			break;
		case 3:
			slv = "(2 kyu)";
			break;
		case 4:
			slv = "(1 kyu)";
			break;
		case 5:
			slv = "(A1 dan)";
			break;
		case 6:
			slv = "(A2 dan)";
			break;
		case 7:
			slv = "(A3 dan)";
			break;
		case 8:
			slv = "(A4 dan)";
			break;
		case 9:
			slv = "(A5 dan)";
			break;
		case 10:
			slv = "(A6 dan)";
			break;
		case 11:
			slv = "(A7 dan)";
			break;
		case 12:
			slv = "(P1 dan)";
			break;
		case 13:
			slv = "(P2 dan)";
			break;
		case 14:
			slv = "(P3 dan)";
			break;
		case 15:
			slv = "(P4 dan)";
			break;
		case 16:
			slv = "(P5 dan)";
			break;
		case 17:
			slv = "(P6 dan)";
			break;
		case 18:
			slv = "(P7 dan)";
			break;
		case 19:
			slv = "(P8 dan)";
			break;
		case 20:
			slv = "(P9 dan)";
			break;
		case 21:
			slv = "(Meijin)";
			break;
		case 22:
			slv = "(Grandmaster)";
			break;
		case 23:
			slv = "(Go God)";
			break;
		}
	}
	else
	{
		switch (lvl)
		{
		case 0:
			slv = "（五级）";
			break;
		case 1:
			slv = "（四级）";
			break;
		case 2:
			slv = "（三级）";
			break;
		case 3:
			slv = "（二级）";
			break;
		case 4:
			slv = "（一级）";
			break;
		case 5:
			slv = "（业一）";
			break;
		case 6:
			slv = "（业二）";
			break;
		case 7:
			slv = "（业三）";
			break;
		case 8:
			slv = "（业四）";
			break;
		case 9:
			slv = "（业五）";
			break;
		case 10:
			slv = "（业六）";
			break;
		case 11:
			slv = "（业七）";
			break;
		case 12:
			slv = "（初段）";
			break;
		case 13:
			slv = "（二段）";
			break;
		case 14:
			slv = "（三段）";
			break;
		case 15:
			slv = "（四段）";
			break;
		case 16:
			slv = "（五段）";
			break;
		case 17:
			slv = "（六段）";
			break;
		case 18:
			slv = "（七段）";
			break;
		case 19:
			slv = "（八段）";
			break;
		case 20:
			slv = "（九段）";
			break;
		case 21:
			slv = "（名人）";
			break;
		case 22:
			slv = "（棋圣）";
			break;
		case 23:
			slv = "（棋灵王）";
			break;
		}
	}
	return slv;
}

//获取等级对应的头衔
CString CSfcGoView::GetLevelFullTitle(int lvl)
{
	if (iLanguage == 0)
		return GetLevelTitle(lvl);
	CString slv = "";
	switch (lvl)
	{
	case 0:
		slv = "（五级）";
		break;
	case 1:
		slv = "（四级）";
		break;
	case 2:
		slv = "（三级）";
		break;
	case 3:
		slv = "（二级）";
		break;
	case 4:
		slv = "（一级）";
		break;
	case 5:
		slv = "（业余一段）";
		break;
	case 6:
		slv = "（业余二段）";
		break;
	case 7:
		slv = "（业余三段）";
		break;
	case 8:
		slv = "（业余四段）";
		break;
	case 9:
		slv = "（业余五段）";
		break;
	case 10:
		slv = "（业余六段）";
		break;
	case 11:
		slv = "（业余七段）";
		break;
	case 12:
		slv = "（职业初段）";
		break;
	case 13:
		slv = "（职业二段）";
		break;
	case 14:
		slv = "（职业三段）";
		break;
	case 15:
		slv = "（职业四段）";
		break;
	case 16:
		slv = "（职业五段）";
		break;
	case 17:
		slv = "（职业六段）";
		break;
	case 18:
		slv = "（职业七段）";
		break;
	case 19:
		slv = "（职业八段）";
		break;
	case 20:
		slv = "（职业九段）";
		break;
	case 21:
		slv = "（名人）";
		break;
	case 22:
		slv = "（棋圣）";
		break;
	case 23:
		slv = "（棋灵王）";
		break;
	}
	return slv;
}

CString CSfcGoView::GetGameResult()
{
	CString str = "";
	if (m_bGameOver)
	{
		if (iLanguage == 0)
		{
			if (m_sResult.Right(2) == "+0")
				str = "Draw";
			else
			{
				m_sResult.Left(1) == "B" ? str = "Black " : str = "White ";
				if (m_sResult.Right(1) == "R")
					str += "win";
				else
				{
					str += "win " + m_sResult.Right(m_sResult.GetLength() - 2);
				}
			}
		}
		else
		{
			if (m_sResult.Right(2) == "+0")
				str = "和棋";
			else
			{
				m_sResult.Left(1) == "B" ? str = "黑" : str = "白";
				if (m_sResult.Right(1) == "R")
					str += "中盘胜";
				else
				{
					str += "胜" + m_sResult.Right(m_sResult.GetLength() - 2) + "目";
				}
			}
		}
	}
	return str;
}

void CSfcGoView::OnLifeDeathAna()
{
	if (m_iState1 == 11 || m_iState1==12 || m_iState1 == 14)//开始分析
	{
		m_iOldFixedStone = m_iFixedStone;
		m_iFixedStone = m_iGoCount;
		m_iOldGoCount = m_iGoCount;
		m_iOldState1 = m_iState1;
		if (m_bAnaed)//当前局面已经分析过，直接显示结果
		{
			m_sOutputInfo = "分析结束";
			m_sOtherInfo = "点击候选着手表可以查看其他着手";
			if (iLanguage == 0)
			{
				m_sOutputInfo = "Analyze complete";
				m_sOtherInfo = "Click move candidate to show other moves";
			}
			m_iState1 = 6;
			m_iStateNew = 3;
			m_iStateOpen = 3;
			m_iStateSave = 3;
			m_iStateReopen = 3;
			m_iStateArea = 1;
			m_iStateExit = 0;
			m_iStateResign = 3;
			m_iAnaMoveCount = m_iOldAnaMoveCount;
			ShowAnaMove();
			this->InvalidateRect(m_rToolBox);
			return;
		}
		if (m_iStateBlackFirst == 2)
			m_iColor = BLACK;
		else
			m_iColor = WHITE;
		m_iComputerThinkTime = 15;//设置电脑思考5秒
		m_iComputerByoTime = m_iComputerThinkTime;
		SetTimes(0, m_iComputerThinkTime, m_iComputerByoStones);
		iLevel = 23;
		SetLevel(iLevel);//设最高电脑棋力
		if (m_iColor == BLACK)
		{
			iPlayer1 = 1;
			iLevel1 = iLevel;
			iPlayer2 = 0;
			iLevel2 = iPlayerLevel;
		}
		else
		{
			iPlayer2 = 1;
			iLevel2 = iLevel;
			iPlayer1 = 0;
			iLevel1 = iPlayerLevel;
		}
		//将局面导入引擎
		CString filename = strSysDirectry;
		filename += "\\tmp.sgf";
		GoRecordToSgf(m_iGoCount, m_GoRecord, m_iFixedStone, &m_Sgftree);
		char* fpname = filename.GetBuffer();
		writesgf(m_Sgftree.root, fpname);
		CString str = "loadsgf ";
		str += filename;
		str += "\r\n";
		m_pEngine1->WriteToPipe(str);
		int count;
		CString* strs = m_pEngine1->GetMsg(count);
		delete[] strs;
		m_sLifeDeathCmd = " allow ";
		//m_Gameinfo.to_move == BLACK ? m_sLifeDethCmd += "B " : m_sLifeDethCmd += "W ";
		m_sLifeDeathCmd += "B ";
		CString allowedmove=GetLifeDeathAllowedMoveString(1);
		m_sLifeDeathCmd += allowedmove;
		m_sLifeDeathCmd += " 20";//最大分析深度为20步
		m_sLifeDeathCmd += " allow W ";
		m_sLifeDeathCmd += allowedmove;
		m_sLifeDeathCmd += " 20";//最大分析深度为20步
		//m_iColor = m_Gameinfo.to_move;
		//m_Gameinfo.game_record = m_Sgftree;
		//m_Gameinfo.to_move = OTHER_COLOR(m_GoRecord[m_iGoCount - 1].color);

		m_PauseTime = m_PeriodTime;
		m_PeriodTime = CTimeSpan(m_iComputerByoTime);
		m_sOutputInfo = "佐为（棋灵王）正在为你分析......";
		if (iLanguage == 0)
			m_sOutputInfo = "Sai (Go God) is analyzing for you...";
		m_sOtherInfo = "";
		iEngineThreadState = 1;
		AfxBeginThread(GetEngineAna, this);
		SetTimer(4, 1000, NULL);
		m_iState1 = 4;
		m_iStateNew = 3;
		m_iStateOpen = 3;
		m_iStateSave = 3;
		m_iStateReopen = 3;
		m_iStateArea = 0;
		m_iStateExit = 3;
		m_iStateResign = 3;
		this->InvalidateRect(m_rToolBox);
	}
	else if (m_iState1 == 4)//正在分析，中断
	{
		m_sOutputInfo = "分析被中断";
		if (iLanguage == 0)
			m_sOutputInfo = "Analyzing is broken";
		CString str = "\r\n";
		m_pEngine1->WriteToPipe(str);
		//int count;
		//CString* strs = pengine->GetMsg(count);
		//delete[] strs;
	}
	m_iStateArea = 0;
}

//计算死活题着手点范围
CRect CSfcGoView::GetLifeDeathArea()
{
	int x1 = -1, y1 = -1, x2 = - 1, y2 = - 1;
	for (int i = 0; i < m_iBoardSize; i++)
	{
		for (int j = 0; j < m_iBoardSize; j++)
		{
			if (m_iBoard[i][j] != 0)
			{
				x1 = i;
				break;
			}
		}
		if (x1 >= 0)
			break;
	}
	for (int i = m_iBoardSize - 1; i >= 0; i--)
	{
		for (int j = 0; j < m_iBoardSize; j++)
		{
			if (m_iBoard[i][j] != 0)
			{
				x2 = i;
				break;
			}
		}
		if (x2 >= 0)
			break;
	}
	for (int j = 0; j < m_iBoardSize; j++)
	{
		for (int i = 0; i < m_iBoardSize; i++)
		{
			if (m_iBoard[i][j] != 0)
			{
				y1 = j;
				break;
			}
		}
		if (y1 >= 0)
			break;
	}
	for (int j = m_iBoardSize - 1; j >= 0; j--)
	{
		for (int i = 0; i < m_iBoardSize; i++)
		{
			if (m_iBoard[i][j] != 0)
			{
				y2 = j;
				break;
			}
		}
		if (y2 >= 0)
			break;
	}
	if (x1 > 0)
		x1--;
	if (y1 > 0)
		y1--;
	if (x2 < m_iBoardSize - 1)
		x2++;
	if (y2 < m_iBoardSize - 1)
		y2++;
	CRect rect = CRect(x1, y1, x2, y2);
	return rect;
}

//获取死活分析着手范围字符串
CString CSfcGoView::GetLifeDeathAllowedMoveString(int targetdragonid)
{
	CRect moverect = GetLifeDeathArea();
	CString movestring = "";
	for (int x = moverect.left; x <= moverect.right; x++)
	{
		for (int y = moverect.top; y <= moverect.bottom; y++)
		{
			movestring += TransXY(x, y);
			if (x < moverect.right || y < moverect.bottom)
				movestring += ",";
		}
	}
	/*
	int xs[361], ys[361];
	int count = GetDragonPoints(targetdragonid, xs, ys);
	for (int i = 0; i < count; i++)
		movestring += TransXY(xs[i], ys[i]) + ",";
	count = GetStonesFromBoard(xs, ys);
	for (int i = 0; i < count - 1; i++)
	{
		movestring += TransXY(xs[i], ys[i]) + ",";
	}
	movestring += TransXY(xs[count - 1], ys[count - 1]);*/
	return movestring;
}

//判断棋子间的连接，以及着手
bool CSfcGoView::StoneLinkToStone(int x, int y, int color, int x0, int y0, int board[19][19])
{
	if (color != board[x0][y0])
		return false;
	int othercolor = OTHER_COLOR(color);
	//直接相连
	if ((x - 1 == x0 || x + 1 == x0) && y == y0 || x == x0 && (y - 1 == y0 || y + 1 == y0))
		return true;
	//小尖相连
	if (x - 1 == x0 && y - 1 == y0)
	{
		return true;//断点着手
		if (board[x - 1][y] != othercolor)
		{
			if (x == 1 || y == iBoardSize - 1) return true;
			else if (board[x][y - 1] != othercolor) return true;
		}
		else if ((x == iBoardSize - 1 || y == 1) && board[x][y - 1] != othercolor) return true;
	}
	if (x - 1 == x0 && y + 1 == y0)
	{
		return true;
		if (board[x - 1][y] != othercolor)
		{
			if (x == 1 || y == 0) return true;
			else if (board[x][y + 1] != othercolor) return true;
		}
		else if ((x == iBoardSize - 1 || y == iBoardSize - 2) && board[x][y + 1] != othercolor) return true;
	}
	if (x + 1 == x0 && y - 1 == y0)
	{
		return true;
		if (board[x][y - 1] != othercolor)
		{
			if (x == 0 || y == 1) return true;
			else if (board[x + 1][y] != othercolor) return true;
		}
		else if ((x == iBoardSize - 2 || y == iBoardSize - 1) && board[x + 1][y] != othercolor)
			return true;
	}
	if (x + 1 == x0 && y + 1 == y0)
	{
		return true;
		if (board[x][y + 1] != othercolor)
		{
			if (x == 0 || y == iBoardSize - 2) return true;
			else if (board[x + 1][y] != othercolor) return true;
		}
		else if ((x == iBoardSize - 2 || y == 0) && board[x + 1][y] != othercolor) return true;
	}
	//单关相连
	if (x - 2 == x0 && y == y0)
	{
		//if (board[x - 1][y] != othercolor || board[x - 1][y + 1] != othercolor || board[x - 1][y - 1] != othercolor)
		//	return true;
		//else
		//	return false;
		if (board[x - 1][y] != othercolor)
		{
			if (y < 2)
			{
				if (board[x - 1][y + 1] != othercolor) return true;
			}
			else if (y > 16)
			{
				if (board[x - 1][y - 1] != othercolor) return true;
			}
			else if (board[x - 1][y + 1] != othercolor && board[x - 1][y - 1] != othercolor) return true;
		}
	}
	if (x + 2 == x0 && y == y0)
	{
		//if (board[x + 1][y] != othercolor || board[x + 1][y + 1] != othercolor || board[x + 1][y - 1] != othercolor)
		//	return true;
		//else
		//	return false;
		if (board[x + 1][y] != othercolor)
		{
			if (y < 2)
			{
				if (board[x + 1][y + 1] != othercolor) return true;
			}
			else if (y > 16)
			{
				if (board[x + 1][y - 1] != othercolor) return true;
			}
			else if (board[x + 1][y + 1] != othercolor && board[x + 1][y - 1] != othercolor) return true;
		}
	}
	if (y - 2 == y0 && x == x0)
	{
		//if (board[x][y-1] != othercolor || board[x - 1][y - 1] != othercolor || board[x + 1][y - 1] != othercolor)
		//	return true;
		//else
		//	return false;
		if (board[x][y - 1] != othercolor)
		{
			if (x < 2)
			{
				if (board[x + 1][y - 1] != othercolor) return true;
			}
			else if (x > 16)
			{
				if (board[x - 1][y - 1] != othercolor) return true;
			}
			else if (board[x + 1][y - 1] != othercolor && board[x - 1][y - 1] != othercolor) return true;
		}
	}
	if (y + 2 == y0 && x == x0)
	{
		//if (board[x][y + 1] != othercolor || board[x - 1][y + 1] != othercolor || board[x + 1][y + 1] != othercolor)
		//	return true;
		//else
		//	return false;
		if (board[x][y + 1] != othercolor)
		{
			if (x < 2)
			{
				if (board[x + 1][y + 1] != othercolor) return true;
			}
			else if (x > 16)
			{
				if (board[x - 1][y + 1] != othercolor) return true;
			}
			else if (board[x + 1][y + 1] != othercolor && board[x - 1][y + 1] != othercolor) return true;
		}
	}
	//小飞相连
	if (x - 2 == x0 && y - 1 == y0)
	{
		if (board[x - 1][y - 1] != othercolor
			&& board[x - 1][y] != othercolor
			&& (y < 2 || board[x - 1][y - 2] != othercolor)
			&& (y > 17 || board[x - 1][y + 1] != othercolor))
			return true;
	}
	if (x - 2 == x0 && y + 1 == y0)
	{
		if (board[x - 1][y + 1] != othercolor
			&& board[x - 1][y] != othercolor
			&& (y < 1 || board[x - 1][y - 1] != othercolor)
			&& (y > 16 || board[x - 1][y + 2] != othercolor))
			return true;
	}
	if (x - 1 == x0 && y - 2 == y0)
	{
		if (board[x - 1][y - 1] != othercolor
			&& board[x][y - 1] != othercolor
			&& (x < 2 || board[x - 2][y - 1] != othercolor)
			&& (x > 17 || board[x + 1][y - 1] != othercolor))
			return true;
	}
	if (x + 1 == x0 && y - 2 == y0)
	{
		if (board[x][y - 1] != othercolor
			&& board[x + 1][y - 1] != othercolor
			&& (x < 1 || board[x - 1][y - 1] != othercolor)
			&& (x > 16 || board[x + 2][y - 1] != othercolor))
			return true;
	}
	if (x + 2 == x0 && y - 1 == y0)
	{
		if (board[x + 1][y - 1] != othercolor
			&& board[x + 1][y] != othercolor
			&& (y < 2 || board[x + 1][y - 2] != othercolor)
			&& (y > 17 || board[x + 1][y + 1] != othercolor))
			return true;
	}
	if (x + 2 == x0 && y + 1 == y0)
	{
		if (board[x + 1][y + 1] != othercolor
			&& board[x + 1][y] != othercolor
			&& (y < 1 || board[x + 1][y - 1] != othercolor)
			&& (y > 16 || board[x + 1][y + 2] != othercolor))
			return true;
	}
	if (x - 1 == x0 && y + 2 == y0)
	{
		if (board[x - 1][y + 1] != othercolor
			&& board[x][y + 1] != othercolor
			&& (x < 2 || board[x - 2][y + 1] != othercolor)
			&& (x > 17 || board[x + 1][y + 1] != othercolor))
			return true;
	}
	if (x + 1 == x0 && y + 2 == y0)
	{
		if (board[x][y + 1] != othercolor
			&& board[x + 1][y + 1] != othercolor
			&& (x < 1 || board[x - 1][y + 1] != othercolor)
			&& (x > 16 || board[x + 2][y + 1] != othercolor)) return true;
	}
	return false;
}

//判断棋子或空白点和棋群之间的连接
bool CSfcGoView::StoneLinkToDragon(int x, int y, int color, int dragonid)
{
	if (color != m_GoInfo.dragons[dragonid].color)
		return	false;
	for (int i = 0; i < m_GoInfo.dragons[dragonid].kcount; i++)
	{
		for (int j = 0; j < m_GoInfo.strings[m_GoInfo.dragons[dragonid].stringids[i]].zcount; j++)
		{
			if (StoneLinkToStone(x, y, color, m_GoInfo.strings[m_GoInfo.dragons[dragonid].stringids[i]].xs[j], m_GoInfo.strings[m_GoInfo.dragons[dragonid].stringids[i]].ys[j], m_GoInfo.board))
				return true;
		}
	}
	return false;
}

//获取棋群范围
CRect CSfcGoView::GetDragonArea(int dragonid)
{
	int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
	int color = m_GoInfo.dragons[dragonid].color;
	for (int i = 0; i < m_iBoardSize; i++)
	{
		for (int j = 0; j < m_iBoardSize; j++)
		{
			if (m_GoInfo.stones[i][j].color==color && m_GoInfo.stones[i][j].dragonid == dragonid)
			{
				x1 = i;
				break;
			}
		}
		if (x1 >= 0)
			break;
	}
	for (int i = m_iBoardSize - 1; i >= 0; i--)
	{
		for (int j = 0; j < m_iBoardSize; j++)
		{
			if (m_GoInfo.stones[i][j].color == color && m_GoInfo.stones[i][j].dragonid == dragonid)
			{
				x2 = i;
				break;
			}
		}
		if (x2 >= 0)
			break;
	}
	for (int j = 0; j < m_iBoardSize; j++)
	{
		for (int i = 0; i < m_iBoardSize; i++)
		{
			if (m_GoInfo.stones[i][j].color == color && m_GoInfo.stones[i][j].dragonid == dragonid)
			{
				y1 = j;
				break;
			}
		}
		if (y1 >= 0)
			break;
	}
	for (int j = m_iBoardSize - 1; j >= 0; j--)
	{
		for (int i = 0; i < m_iBoardSize; i++)
		{
			if (m_GoInfo.stones[i][j].color == color && m_GoInfo.stones[i][j].dragonid == dragonid)
			{
				y2 = j;
				break;
			}
		}
		if (y2 >= 0)
			break;
	}
	CRect rect = CRect(x1, y1, x2, y2);
	return rect;
}

//获取棋群周围和内部的空白点
int CSfcGoView::GetDragonPoints(int dragonid, int xs[361], int ys[361])
{
	CRect rect = GetDragonArea(dragonid);
	int x1 = rect.left, y1 = rect.top, x2 = rect.right, y2 = rect.bottom;
	x1 = max(x1 - 2, 0);
	y1 = max(y1 - 2, 0);
	x2 = min(x2 + 2, m_iBoardSize - 1);
	y2 = min(y2 + 2, m_iBoardSize - 1);
	int color = m_GoInfo.dragons[dragonid].color;
	int count = 0;
	for (int x = x1; x <= x2; x++)
	{
		for (int y = y1; y <= y2; y++)
		{
			if (m_GoInfo.board[x][y]==0 && StoneLinkToDragon(x, y, color, dragonid))
			{
				xs[count] = x;
				ys[count] = y;
				count++;
			}
		}
	}
	return count;
}

//获取死活分析着手范围
int CSfcGoView::GetLifeDeathAllowedMoves(int color, int xs[361], int ys[361])
{
	int count = 0, count0 = 0;
	int xs1[361], ys1[361];
	int i = 0, dragoncount = 0;
	while (dragoncount < m_GoInfo.dragoncount)
	{
		if (m_GoInfo.dragons[i].color>0)
		{
			if (Sfc::DragonSurrounded(i, m_GoInfo))//m_GoInfo.dragons[i].color == color)
			{
				int count1 = GetDragonPoints(i, xs1, ys1);
				for (int j = 0; j < count1; j++)
				{
					int k;
					for (k = 0; k < count0; k++)
					{
						if (xs[k] == xs1[j] && ys[k] == ys1[j])
							break;
					}
					if (k == count0)
					{
						xs[count] = xs1[j];
						ys[count] = ys1[j];
						count++;
					}
				}
				count0 = count;
			}
			dragoncount++;
		}
		i++;
	}
	return count;
}

//获取棋盘上所有棋子的坐标
int CSfcGoView::GetStonesFromBoard(int xs[361], int ys[361])
{
	int count = 0;
	for (int x = 0; x < m_GoInfo.boardsize; x++)
	{
		for (int y = 0; y < m_GoInfo.boardsize; y++)
		{
			if (m_GoInfo.board[x][y] != 0)
			{
				xs[count] = x;
				ys[count] = y;
				count++;
			}
		}
	}
	return count;
}

void CSfcGoView::ShowLifeDeathPanel()
{
	int x, y, x1, x2, y1, y2, y3 = 0, y4 = 0, w, h;
	//CRect rt;
	//GetClientRect(rt);
	CWnd* pWnd;
	CRect rect, rt;
	pWnd = GetDlgItem(IDC_GRPPANEL);
	if (pWnd)
	{
		pWnd->GetWindowRect(rect);
		ScreenToClient(rect);
		//pWnd->MoveWindow(x2,y2,w,h);
		pWnd->MoveWindow(m_rPanel);
		pWnd->SetLayeredWindowAttributes(RGB(245, 245, 245), 255, 2);
		pWnd->ShowWindow(SW_SHOW);
		//CDC* pDC = GetDC();
		//pDC->FillSolidRect(rect, RGB(240, 240, 240));
		//ReleaseDC(pDC);
	}
	pWnd = GetDlgItem(IDC_STATTARGET);
	if (pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x = m_rPanel.left + (rt.left - rect.left) * m_rPanel.Width() / rect.Width();
		y = m_rPanel.top + (rt.top - rect.top) * m_rPanel.Height() / rect.Height();
		pWnd->MoveWindow(x, y, rt.right - rt.left, rt.bottom - rt.top);
		pWnd->ShowWindow(SW_SHOW);
	}
	pWnd = GetDlgItem(IDC_CMBMB);
	if (pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x = m_rPanel.left + (rt.left - rect.left) * m_rPanel.Width() / rect.Width();
		y = m_rPanel.top + (rt.top - rect.top) * m_rPanel.Height() / rect.Height();
		pWnd->MoveWindow(x, y, rt.right - rt.left, rt.bottom - rt.top);
		pWnd->ShowWindow(SW_SHOW);
	}
	pWnd = GetDlgItem(IDC_STATPUTSTONE);
	if (pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x = m_rPanel.left + (rt.left - rect.left) * m_rPanel.Width() / rect.Width();
		y = m_rPanel.top + (rt.top - rect.top) * m_rPanel.Height() / rect.Height();
		pWnd->MoveWindow(x, y, rt.right - rt.left, rt.bottom - rt.top);
		pWnd->ShowWindow(SW_SHOW);
	}
	pWnd = GetDlgItem(IDC_RADBLACK);
	if (pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x = m_rPanel.left + (rt.left - rect.left) * m_rPanel.Width() / rect.Width();
		y = m_rPanel.top + (rt.top - rect.top) * m_rPanel.Height() / rect.Height();
		pWnd->MoveWindow(x, y, rt.right - rt.left, rt.bottom - rt.top);
		pWnd->ShowWindow(SW_SHOW);
	}
	pWnd = GetDlgItem(IDC_RADWHITE);
	if (pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x = m_rPanel.left + (rt.left - rect.left) * m_rPanel.Width() / rect.Width();
		y = m_rPanel.top + (rt.top - rect.top) * m_rPanel.Height() / rect.Height();
		pWnd->MoveWindow(x, y, rt.right - rt.left, rt.bottom - rt.top);
		pWnd->ShowWindow(SW_SHOW);
	}
	pWnd = GetDlgItem(IDC_RADINTURN);
	if (pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x = m_rPanel.left + (rt.left - rect.left) * m_rPanel.Width() / rect.Width();
		y = m_rPanel.top + (rt.top - rect.top) * m_rPanel.Height() / rect.Height();
		pWnd->MoveWindow(x, y, rt.right - rt.left, rt.bottom - rt.top);
		pWnd->ShowWindow(SW_SHOW);
	}
	/*pWnd = GetDlgItem(IDC_RADWHITE);
	if (pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x = x2 + (rt.left - rect.left);
		y = y2 + (rt.top - rect.top);
		pWnd->MoveWindow(x, y, rt.right - rt.left, rt.bottom - rt.top);
	}
	pWnd = GetDlgItem(IDC_RADINTURN);
	if (pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x = x2 + (rt.left - rect.left);
		y = y2 + (rt.top - rect.top);
		pWnd->MoveWindow(x, y, rt.right - rt.left, rt.bottom - rt.top);
	}
	pWnd = GetDlgItem(IDC_CMBMB);
	if (pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x = x2 + (rt.left - rect.left);
		y = y2 + (rt.top - rect.top);
		pWnd->MoveWindow(x, y, rt.right - rt.left, rt.bottom - rt.top);
	}
	pWnd = GetDlgItem(IDC_STAT);
	if (pWnd)
	{
		pWnd->GetWindowRect(rt);
		ScreenToClient(rt);
		x = x2 + (rt.left - rect.left);
		//y3=cy-10-(rect.bottom-rt.bottom)-rt.Height();
		pWnd->MoveWindow(x, y3, rt.Width(), rt.Height());
	}
	*/
}

void CSfcGoView::ShowAnaMove()
{
	m_iState1 = 6;
	if (m_iGoCount > m_iFixedStone)
	{
		//关掉落子声
		bool bputstonesound = bPutStoneSound;
		bPutStoneSound = false;
		OnGoFirst();
		bPutStoneSound = bputstonesound;
	}
	int x, y, color = m_iColor;
	/*int id = 0, x1, y1, xs[361], ys[361];
	int count = GetLifeDeathAllowedMoves(m_iADColor, xs, ys);
	for (int i = 0; i < m_iAnaMoveCount; i++)
	{
		Trans(m_sAnaMoveRecs[i], x1, y1);
		int j;
		for (j = 0; j < count; j++)
		{
			if (x1 == xs[j] && y1 == ys[j])
				break;
		}
		if (j < count)
		{
			id = j;
			break;
		}
	}*/
	//记录胜率
	if (m_iState == 3)
	{
		if (color == BLACK)
		{
			m_fBlackWinRate = m_fAnaMoveWinRates[m_iAnaMoveId];
			m_fWhiteWinRate = 1 - m_fBlackWinRate;
		}
		else
		{
			m_fWhiteWinRate = m_fAnaMoveWinRates[m_iAnaMoveId];
			m_fBlackWinRate = 1 - m_fWhiteWinRate;
		}
	}
	for (int i = 0; i < m_iLifeDeathMoveCounts[m_iAnaMoveId]; i++)
	{
		Trans(m_sLifeDeathMovess[m_iAnaMoveId][i], x, y);
		Sfc::PlayStone(x, y, color, m_GoInfo);
		AddStone(x, y, color);
		color = OTHER_COLOR(color);
	}
	//增加着手记录
	if (m_iState == 3)
	{
		m_iMoveCount = m_iFixedStone;
		for (int i = 0; i < m_iGoCount; i++)
		{
			if (i >= m_iFixedStone)
			{
				m_sMoveRecs[m_iMoveCount] = TransXY(m_GoRecord[i].x, m_GoRecord[i].y, m_GoRecord[i].color);
				m_sMoveTimeRecs[m_iMoveCount].Format("%02d:%02d:%02d", m_PeriodTime.GetHours(), m_PeriodTime.GetMinutes(), m_PeriodTime.GetSeconds());
				if (m_GoRecord[i].color == BLACK)
					m_fMoveWinRates[m_iMoveCount] = m_fBlackWinRate;
				else
					m_fMoveWinRates[m_iMoveCount] = m_fWhiteWinRate;
				m_iMoveCount++;
			}
		}
	}
	m_iGoCountMax = m_iGoCount;
	m_iStateGoBack = 0;
	m_iStateGoFirst = 0;
	m_iStateGoFiveBack = 0;
	m_iStateGoForward = 3;
	m_iStateGoFiveForward = 3;
	m_iStateGoLast = 3;
}

//复制本地棋盘
void CSfcGoView::CopyLocalBoard()
{
	for (int j = 0; j < m_iBoardSize; j++)
		for (int k = 0; k < m_iBoardSize; k++)
			m_iBoard[j][k] = m_GoInfo.board[j][k];
}


void CSfcGoView::OnMCoord()
{
	bCoord = !bCoord;
	Sfc::WriteSysIni();
	Invalidate();
}


void CSfcGoView::OnUpdateMCoord(CCmdUI* pCmdUI)
{
	if (bCoord)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CSfcGoView::OnMAnimate()
{
	bAnimate = !bAnimate;
	Sfc::WriteSysIni();
}


void CSfcGoView::OnUpdateMAnimate(CCmdUI* pCmdUI)
{
	if(bAnimate)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}


void CSfcGoView::OnMThinkprogress()
{
	bThinkProgress = !bThinkProgress;
	Sfc::WriteSysIni();
}

void CSfcGoView::OnUpdateMThinkprogress(CCmdUI* pCmdUI)
{
	if (bThinkProgress)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}


void CSfcGoView::OnMPutstonesound()
{
	bPutStoneSound = !bPutStoneSound;
	Sfc::WriteSysIni();
}


void CSfcGoView::OnUpdateMPutstonesound(CCmdUI* pCmdUI)
{
	if (bPutStoneSound)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}


void CSfcGoView::OnMCapturestonesound()
{
	bCaptureSound = !bCaptureSound;
	Sfc::WriteSysIni();
}

void CSfcGoView::OnUpdateMCapturestonesound(CCmdUI* pCmdUI)
{
	if (bCaptureSound)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}


void CSfcGoView::OnMPickstonesound()
{
	bPickStoneSound = !bPickStoneSound;
	Sfc::WriteSysIni();
}

void CSfcGoView::OnUpdateMPickstonesound(CCmdUI* pCmdUI)
{
	if (bPickStoneSound)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}


void CSfcGoView::OnMPushclocksound()
{
	bPushClockSound = !bPushClockSound;
	Sfc::WriteSysIni();
}


void CSfcGoView::OnUpdateMPushclocksound(CCmdUI* pCmdUI)
{
	if (bPushClockSound)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}


void CSfcGoView::OnMByosound()
{
	bByoSound = !bByoSound;
	Sfc::WriteSysIni();
}

void CSfcGoView::OnUpdateMByosound(CCmdUI* pCmdUI)
{
	if (bByoSound)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

//保存胜率数据到文件
void CSfcGoView::SaveWinRate(CString filename)
{
	errno_t err;
	FILE* fp;
	if ((err = fopen_s(&fp, filename, "w")) != 0)
	{
		CString msg = "无法写入胜率数据文件！";
		if (iLanguage == 0)
			msg = "Can not write to win rate data file!";
		AfxMessageBox(msg, NULL, MB_OK);
		return;
	}
	CString str, str1;
	for (int i = 0; i < m_iMoveCount; i++)
	{
		str = m_sMoveTimeRecs[i];
		str1.Format(" %6.4f %6.4f\r\n", m_fMoveWinRates[i], m_fStdMoveWinRates[i]);
		str += str1;
		int len = str.GetLength();
		fwrite(str, len, 1, fp);
	}
	fclose(fp);
}

//从文件读取胜率数据
void CSfcGoView::ReadWinRate(CString filename)
{
	errno_t err;
	FILE* fp;
	if ((err = fopen_s(&fp, filename, "rb")) != 0)
	{
		//AfxMessageBox("读取胜率数据文件失败！", NULL, MB_OK);
		return;
	}
	//char cs[2048];
	//CString str;
	int count = 0;
	CString strs[255];
	bool success;
	do
	{
		//success = fgets(cs, 2048, fp);
		//str = cs;
		//m_fMoveWinRates[count] = atof(str.Trim());
		success = Sfc::ReadLine(fp, " ", strs);
		if (strs[0].GetLength() == 8)
		{
			m_sMoveTimeRecs[count] = strs[0];
			m_fMoveWinRates[count] = atof(strs[1]);
			m_fStdMoveWinRates[count] = atof(strs[2]);
			count++;
		}
		
	} while (success);
	fclose(fp);
}


BOOL CSfcGoView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (m_iState1 == 6)
	{
		CPoint point = pt;
		ScreenToClient(&point);
		if (PtInRect(m_rAnaMove, point))
		{
			int oldid = m_iAnaMoveId;
			m_iAnaMoveId -= zDelta / WHEEL_DELTA;
			m_iAnaMoveId = min(m_iAnaMoveCount - 1, max(0, m_iAnaMoveId));
			if (m_iAnaMoveId != oldid)
			{
				if (m_iAnaMoveId < m_iAnaMoveStartId)
					m_iAnaMoveStartId = m_iAnaMoveId;
				else
				{
					int n = m_rAnaMove.Height() / m_iMoveRecHeight;
					if (m_iAnaMoveId - m_iAnaMoveStartId + 1 > n)
						m_iAnaMoveStartId = m_iAnaMoveId + 1 - n;
				}
				InvalidateRect(m_rAnaMove);
				ShowAnaMove();
				InvalidateRect(m_rMoveRec);
				UpdateWindow();
			}
		}
	}

	return CFormView::OnMouseWheel(nFlags, zDelta, pt);
}


void CSfcGoView::OnMShowwinrate()
{
	bShowWinRate = !bShowWinRate;
	//Sfc::WriteSysIni();
	Invalidate();
}


void CSfcGoView::OnUpdateMShowwinrate(CCmdUI* pCmdUI)
{
	if (bShowWinRate)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}


void CSfcGoView::OnMShowana()
{
	bShowAna = !bShowAna;
	//Sfc::WriteSysIni();
	Invalidate();
}


void CSfcGoView::OnUpdateMShowana(CCmdUI* pCmdUI)
{
	if (bShowAna)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CSfcGoView::OnMShowmoverec()
{
	bShowMoveRec = !bShowMoveRec;
	//Sfc::WriteSysIni();
	Invalidate();
}

void CSfcGoView::OnUpdateMShowmoverec(CCmdUI* pCmdUI)
{
	if (bShowMoveRec)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}


void CSfcGoView::OnMShowinfo()
{
	bShowInfo = !bShowInfo;
	//Sfc::WriteSysIni();
	Invalidate();
}


void CSfcGoView::OnUpdateMShowinfo(CCmdUI* pCmdUI)
{
	if (bShowInfo)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

//序盘分析
void CSfcGoView::OnPersistenceAna()
{
	m_bAnaAll = false;
	if (m_iState1 == 21 || m_iState1 == 22 || m_iState1==5 || m_iState1==6)//开始分析
	{
		if (m_bAllAnaed && m_iState1 == 22)//该棋谱已经全盘分析过
		{
			//寻找当前节点
			m_Sgftree.lastnode = m_Sgftree.root;
			for (int i = 0; i < m_iGoCount - m_iFixedStone; i++)
				sgftreeForward(&m_Sgftree);
			//获取分析结果
			m_iAnaMoveCount = GetSgfVariation(&m_Sgftree, m_iLifeDeathMoveCounts, m_sLifeDeathMovess, m_sLifeDeathMoveCommentss, m_fAnaMoveWinRates);
			for (int i = 0; i < m_iAnaMoveCount; i++)
			{
				m_sAnaMoveRecs[i] = m_sLifeDeathMovess[i][0];
				m_iAnaMoveVisits[i] = 0;
				//m_fAnaMoveWinRates[i] = 0;
			}
			m_iColor = m_Gameinfo.to_move;
			m_iFixedStone = m_iGoCount;
			m_iOldGoCount = m_iGoCount;
			m_iOldState1 = m_iState1;
			m_iState1 = 5;
			m_iAnaMoveStartId = 0;
			m_iAnaMoveId = 0;
			//ShowAnaMove();
			m_iStateNew = 3;
			m_iStateOpen = 3;
			m_iStateSave = 1;
			m_iStateReopen = 3;
			m_iStateArea = 3;
			m_iStateExit = 0;
			m_iStateResign = 3;
			Invalidate();
			UpdateWindow();
			return;
		}
		else if (m_bAnaed && m_iGoCount==0)//当前局面已经分析过，直接显示结果
		{
			m_sOutputInfo = "分析结束";
			m_sOtherInfo = "点击候选着手表可以查看后继着手";
			if (iLanguage == 0)
			{
				m_sOutputInfo = "Analyze complete";
				m_sOtherInfo = "Click move candidate to show following moves";
			}
			m_iState1 = 6;
			m_iStateNew = 0;
			m_iStateOpen = 0;
			m_iStateSave = 1;
			m_iStateReopen = 3;
			m_iStateArea = 3;
			m_iStateExit = 0;
			m_iStateResign = 3;
			this->InvalidateRect(m_rToolBox);
			return;
		}
		//m_iOldFixedStone = m_iFixedStone;
		m_iFixedStone = m_iGoCount;
		if (m_iState1 == 21 || m_iState1 == 22)
		{
			m_iOldGoCount = m_iGoCount;
			m_iOldState1 = m_iState1;
		}
		m_iComputerThinkTime = 15;//设置电脑思考5秒
		//m_iComputerThinkTime = 5;//设置电脑思考5秒
		m_iComputerByoTime = m_iComputerThinkTime;
		SetTimes(0, m_iComputerThinkTime, m_iComputerByoStones);
		iLevel = 23;
		//iLevel = 21;
		SetLevel(iLevel);//设最高电脑棋力
		m_iColor = m_Gameinfo.to_move;
		if (m_iColor == BLACK)
		{
			iPlayer1 = 1;
			iLevel1 = iLevel;
			iPlayer2 = 0;
			iLevel2 = iPlayerLevel;
		}
		else
		{
			iPlayer2 = 1;
			iLevel2 = iLevel;
			iPlayer1 = 0;
			iLevel1 = iPlayerLevel;
		}
		//将局面导入引擎
		CString filename = strSysDirectry;
		filename += "\\tmp.sgf";
		GoRecordToSgf(m_iGoCount, m_GoRecord, m_iHandiCap, &m_Sgftree);
		char* fpname = filename.GetBuffer();
		writesgf(m_Sgftree.root, fpname);
		CString str = "loadsgf ";
		str += filename;
		str += "\r\n";
		m_pEngine1->WriteToPipe(str);
		int count;
		CString* strs = m_pEngine1->GetMsg(count);
		delete[] strs;
		m_PauseTime = m_PeriodTime;
		m_PeriodTime = CTimeSpan(m_iComputerByoTime);
		m_sOutputInfo = "佐为（棋灵王）正在为你分析......";
		if (iLanguage == 0)
			m_sOutputInfo = "Sai (Go God) is analyzing for you...";
		m_sOtherInfo = "";
		iEngineThreadState = 1;
		AfxBeginThread(GetEngineAna, this);
		SetTimer(4, 1000, NULL);
		m_iState1 = 4;
		m_iStateNew = 3;
		m_iStateOpen = 3;
		m_iStateSave = 0;
		m_iStateReopen = 3;
		m_iStateArea = 3;
		m_iStateExit = 3;
		m_iStateResign = 3;
		m_iStateGoBack = 3;
		m_iStateGoFiveBack = 3;
		m_iStateGoFirst = 3;
		m_iStateGoForward = 3;
		m_iStateGoFiveForward = 3;
		m_iStateGoLast = 3;
		this->InvalidateRect(m_rToolBox);
	}
	else if (m_iState1 == 4)//正在分析，提前停止
	{
		m_sOutputInfo = "分析被中断";
		if (iLanguage == 0)
			m_sOutputInfo = "Analyzing is broken";
		CString str = "\r\n";
		m_pEngine1->WriteToPipe(str);
		//int count;
		//CString* strs = pengine->GetMsg(count);
		//delete[] strs;
	}
	/*else if (m_iState1 == 5 || m_iState1 == 6)//正在查看分析结果，点击返回对弈状态
	{
		//恢复棋盘
		m_iFixedStone = m_iOldFixedStone;
		m_iGoCount = m_iOldGoCount;
		m_iGoCountMax = m_iGoCount;
		m_GoInfo.Init(m_iBoardSize);
		for (int j = 0; j < m_iGoCount; j++)
			Sfc::PlayStone(m_GoRecord[j].x, m_GoRecord[j].y, m_GoRecord[j].color, m_GoInfo);
		for (int j = 0; j < m_iBoardSize; j++)
			for (int k = 0; k < m_iBoardSize; k++)
				m_iBoard[j][k] = m_GoInfo.board[j][k];
		m_iState1 = m_iOldState1;
		m_sOutputInfo = "轮玩家着手";
		m_sOtherInfo = "";
		m_iStateNew = 0;
		m_iStateOpen = 0;
		m_iStateSave = 0;
		m_iStateReopen = 0;
		m_iStateArea = 1;
		m_iStateExit = 0;
		m_iStateResign = 0;
		m_iStateGoBack = 0;
		m_iStateGoFiveBack = 0;
		m_iStateGoFirst = 0;
		m_iStateGoForward = 3;
		m_iStateGoFiveForward = 3;
		m_iStateGoLast = 3;
		if (m_iGoCount == m_iFixedStone)
		{
			m_iStateGoBack = 3;
			m_iStateGoFiveBack = 3;
			m_iStateGoFirst = 3;
		}
		m_iAnaMoveId = 0;
		m_iAnaMoveStartId = 0;
		this->InvalidateRect(m_rBoardBack);
		this->InvalidateRect(m_rToolBox);
	}*/
}

//执行返回按钮的操作
void CSfcGoView::OnReturn()
{
	switch (m_iState)
	{
	case 1:
		if (m_iState1 == 11 || m_iState1 == 12 || m_iState1 == 14)//摆子或读谱状态
		{
			//保存做题状态
			if (m_iState1 == 14)
				Sfc::WriteSysIni();
			//恢复棋盘
			m_GoInfo.Init(m_iBoardSize);
			CopyLocalBoard();
			m_iGoCount = 0;
			m_iGoCountMax = 0;
			m_iFixedStone = 0;
			m_iMoveCount = 0;
			m_iAnaMoveCount = 0;
			m_iState1 = 0;
			//禁用前进/后退按钮
			UpdateBackForwardButton();
			m_iStateNew = 0;
			m_iStateOpen = 0;
			m_iStateSave = 0;
			m_iStateReopen = 0;
			m_iStateExit = 1;
		}
		else //if (m_iState1 == 5 || m_iState1 == 6)//正在查看分析结果，点击返回对弈状态
		{
			//恢复棋盘
			m_iFixedStone = m_iOldFixedStone;
			m_iGoCount = m_iOldGoCount;
			m_iGoCountMax = m_iOldGoCountMax;
			memcpy(m_GoRecord, m_OldGoRecord, sizeof(Data_GoRecord) * m_iGoCountMax);
			m_GoInfo.Init(m_iBoardSize);
			for (int j = 0; j < m_iGoCount; j++)
				Sfc::PlayStone(m_GoRecord[j].x, m_GoRecord[j].y, m_GoRecord[j].color, m_GoInfo);
			CopyLocalBoard();
			if (m_iState1 == 5 || m_iState1 == 6)
				m_iOldAnaMoveCount = m_iAnaMoveCount;
			m_iState1 = m_iOldState1;
			RestroreMoveRecs();
			m_iMoveCount = m_iGoCount - m_iFixedStone;
			m_iAnaMoveCount = 0;
			m_sOtherInfo = "";
			if (m_iState1 == 11)
			{
				m_sOutputInfo = "正在摆子";
				if (iLanguage == 0)
					m_sOutputInfo = "Putting stone";
			}
			else if (m_iState1 == 12 || m_iState1==14)
				m_sOtherInfo = m_Gameinfo.game_name + m_Gameinfo.game_comment;
			//else if(m_iState!=1)
				//m_sOtherInfo = "棋谱文件：" + m_sSfgFileName;
			if (m_iStateBlackFirst == 2)
				m_Gameinfo.to_move = 2;
			else
				m_Gameinfo.to_move = 1;
			m_iColor = m_Gameinfo.to_move;
			m_bRecall = true;
			m_iStateNew = 0;
			m_iStateOpen = 0;
			m_iStateSave = 0;
			m_iStateReopen = 0;
			m_iStateArea = 1;
			m_iStateExit = 0;
			m_iStateResign = 0;
			UpdateBackForwardButton();
			m_iAnaMoveId = 0;
			m_iAnaMoveStartId = 0;
			this->InvalidateRect(m_rBoardBack);
			this->InvalidateRect(m_rToolBox);
		}
		//m_bAnswered = false;
		m_iLabelCount = 0;
		m_iStateExit = 1;
		break;
	case 2:
		break;
	case 3:
		if (m_iState1 == 21 || m_iState1==22)//摆子或打谱状态
		{
			//恢复棋盘
			m_GoInfo.Init(m_iBoardSize);
			CopyLocalBoard();
			m_iStateOpen = 0;
			m_iGoCount = 0;
			m_iGoCountMax = 0;
			m_iFixedStone = 0;
			m_iMoveCount = 0;
			m_iAnaMoveCount = 0;
			m_iState1 = 0;
			//禁用前进/后退按钮
			UpdateBackForwardButton();
			m_iStateExit = 1;
		}
		else if (m_iState1 == 5)
		{
			if (m_iOldState1 == 21)
			{
				m_iFixedStone = m_iHandiCap;
				m_iGoCount = m_iOldGoCount;
				m_iGoCountMax = m_iGoCount;
				m_iMoveCount = m_iGoCount - m_iFixedStone;
				m_GoInfo.Init(m_iBoardSize);
				for (int j = 0; j < m_iGoCount; j++)
					Sfc::PlayStone(m_GoRecord[j].x, m_GoRecord[j].y, m_GoRecord[j].color, m_GoInfo);
				CopyLocalBoard();
				m_sOutputInfo = "正在摆子";
				if (iLanguage == 0)
					m_sOutputInfo = "Putting stone";
				m_sOtherInfo = "";
			}
			else if (m_iOldState1 == 22)
			{
				m_iFixedStone = m_iHandiCap;
				m_iGoCount = m_iOldGoCount;
				m_iGoCountMax = m_iOldGoCountMax;
				memcpy(m_GoRecord, m_OldGoRecord, sizeof(Data_GoRecord) * m_iGoCountMax);
				m_GoInfo.Init(m_iBoardSize);
				m_GoInfo.fixedstone = m_iFixedStone;
				for (int i = 0; i < m_iGoCount; i++)
					Sfc::PlayStone(m_GoRecord[i].x, m_GoRecord[i].y, m_GoRecord[i].color, m_GoInfo);
				CopyLocalBoard();
				m_iRecallId = m_iGoCountMax - 1;
				RestroreMoveRecs();
				m_iMoveCount = m_iGoCount - m_iFixedStone;
				m_sOtherInfo = "棋谱文件：" + m_sSfgFileName;
				if (iLanguage == 0)
					m_sOtherInfo = "File: " + m_sSfgFileName;
				//备份棋谱
				CopySgfTree(&m_Sgftree, m_Sgftree1);
				m_iStateNew = 0;
			}
			m_iState1 = m_iOldState1;
			UpdateBackForwardButton();
			m_iStateExit = 1;
			m_iAnaMoveId = 0;
			m_iAnaMoveStartId = 0;
		}
		else if(m_iState1==6)
		{
			m_iGoCount = m_iFixedStone;
			m_iGoCountMax = m_iGoCount;
			m_iMoveCount = m_iGoCount-m_iHandiCap;
			m_GoInfo.Init(m_iBoardSize);
			for (int j = 0; j < m_iGoCount; j++)
				Sfc::PlayStone(m_GoRecord[j].x, m_GoRecord[j].y, m_GoRecord[j].color, m_GoInfo);
			CopyLocalBoard();
			m_iState1 = 5;
			UpdateBackForwardButton();
			m_iStateExit = 1;
		}
		break;
	}
	Invalidate();
	UpdateWindow();
}

//更新前进/后退等按钮
void CSfcGoView::UpdateBackForwardButton()
{
	if (m_iState1 == 14 || m_iState1==1 && m_iOldState1==14)
	{
		m_iStateGoBack = 0;
		m_iStateGoFiveBack = 0;
		m_iStateGoFirst = 0;
		m_iStateGoForward = 0;
		m_iStateGoFiveForward = 0;
		m_iStateGoLast = 0;
		return;
	}
	else if (m_iState1 == 1 || m_iState1==13)
	{
		m_iStateGoBack = 3;
		m_iStateGoFiveBack = 3;
		m_iStateGoFirst = 3;
		m_iStateGoForward = 3;
		m_iStateGoFiveForward = 3;
		m_iStateGoLast = 3;
		return;
	}
	if (m_iGoCount < m_iFixedStone + 5)
		m_iStateGoFiveBack = 3;
	else
		m_iStateGoFiveBack = 0;
	if (m_iGoCount <= m_iFixedStone)
	{
		m_iStateGoBack = 3;
		m_iStateGoFirst = 3;
	}
	else
	{
		m_iStateGoBack = 0;
		m_iStateGoFirst = 0;
	}
	if (m_iGoCount > m_iGoCountMax - 5)
		m_iStateGoFiveForward = 3;
	else
		m_iStateGoFiveForward = 0;
	if (m_iGoCount >= m_iGoCountMax)
	{
		m_iStateGoForward = 3;
		m_iStateGoLast = 3;
	}
	else
	{
		m_iStateGoForward = 0;
		m_iStateGoLast = 0;
	}
	//InvalidateRect(m_rToolBox);
}

void CSfcGoView::SaveMoveRecs()
{
	m_iOldMoveCount = m_iMoveCount;
	for (int i = 0; i < m_iMoveCount; i++)
	{
		m_OldMoveRecs[i] = m_sMoveRecs[i];
		m_sOldMoveTimeRecs[i] = m_sMoveTimeRecs[i];
		m_fOldMoveWinRates[i] = m_fMoveWinRates[i];
	}
}

void CSfcGoView::RestroreMoveRecs()
{
	m_iMoveCount = m_iOldMoveCount;
	for (int i = 0; i < m_iMoveCount; i++)
	{
		m_sMoveRecs[i] = m_OldMoveRecs[i];
		m_sMoveTimeRecs[i] = m_sOldMoveTimeRecs[i];
		m_fMoveWinRates[i] = m_fOldMoveWinRates[i];
	}
}

void CSfcGoView::CalGameTime()
{
	m_BlackTime = CTimeSpan(0);
	m_WhiteTime = CTimeSpan(0);
	for (int i = 0; i < m_iMoveCount; i++)
	{
		int h = atoi(m_sMoveTimeRecs[i].Left(2));
		int m = atoi(m_sMoveTimeRecs[i].Left(5).Right(2));
		int s = atoi(m_sMoveTimeRecs[i].Right(2));
		if (m_sMoveRecs[i].Left(1)=="B")
			m_BlackTime += CTimeSpan(0, h, m, s);
		else
			m_WhiteTime += CTimeSpan(0, h, m, s);
	}
}

void CSfcGoView::CalGameTime(int movenum)
{
	int num = abs(movenum);
	int startid = m_iMoveCount;
	if (movenum < 0)
		startid -= num;
	for (int i = 0; i < num; i++)
	{
		int h = atoi(m_sMoveTimeRecs[startid + i].Left(2));
		int m = atoi(m_sMoveTimeRecs[startid + i].Left(5).Right(2));
		int s = atoi(m_sMoveTimeRecs[startid + i].Right(2));
		if (movenum > 0)
		{
			if (m_sMoveRecs[startid + i].Left(1) == "B")
				m_BlackTime += CTimeSpan(0, h, m, s);
			else
				m_WhiteTime += CTimeSpan(0, h, m, s);
		}
		else
		{
			if (m_sMoveRecs[startid + i].Left(1) == "B")
				m_BlackTime -= CTimeSpan(0, h, m, s);
			else
				m_WhiteTime -= CTimeSpan(0, h, m, s);
		}
	}
}

void CSfcGoView::OnDifficulty()
{
	m_bDifficulty = !m_bDifficulty;
	if (m_bDifficulty)
	{
		m_iStateNew = 3;
		m_iStateOpen = 3;
		m_iStateSave = 3;
		m_iStateExit = 3;
		m_iStateTesuji = 0;
		m_iStateElemantary = 0;
		m_iStateMiddle = 0;
		m_iStateAdvanced = 0;
	}
	else
	{
		m_iStateNew = 0;
		m_iStateOpen = 0;
		m_iStateSave = 0;
		m_iStateExit = 0;
		m_iStateTesuji = 3;
		m_iStateElemantary = 3;
		m_iStateMiddle = 3;
		m_iStateAdvanced = 3;
	}
	m_iStateReopen = 1;
	Invalidate();
	UpdateWindow();
}

bool CSfcGoView::OnContinueQuest()
{
	CString filename = strDirectry + "\\Life-death\\";
	CString str;
	switch (iLDlevel)
	{
	case 0:
		str.Format("%05d_Tesuji.sgf", iQuest0);
		filename += "Tesuji\\" + str;
		break;
	case 1:
		str.Format("%05d_Elementary.sgf", iQuest1);
		filename += "Elementary\\" + str;
		break;
	case 2:
		str.Format("%05d_Middle.sgf", iQuest2);
		filename += "Middle\\" + str;
		break;
	case 3:
		str.Format("%05d_Advanced.sgf", iQuest3);
		filename += "Advanced\\" + str;
		break;
	}
	char* fpname = filename.GetBuffer();
	if (fpname)
	{
		sgfFreeNode(m_Sgftree.root);
		sgftree_clear(&m_Sgftree);
		if (!sgftree_readfile(&m_Sgftree, fpname))
			return false;
		m_bGameOver = false;
		m_bAnswered = false;
		SgfToGoRecord(&m_Sgftree, m_iGoCount, m_GoRecord, m_iFixedStone);
		m_iHandiCap = m_Gameinfo.handicap;
		m_GoInfo.Init(m_iBoardSize);
		m_GoInfo.fixedstone = m_iFixedStone;
		m_iMoveCount = 0;
		for (int i = 0; i < m_iGoCount; i++)
			Sfc::PlayStone(m_GoRecord[i].x, m_GoRecord[i].y, m_GoRecord[i].color, m_GoInfo);
		CopyLocalBoard();
		for (int i = 0; i < m_iGoCount; i++)
		{
			if (i >= m_iFixedStone)
			{
				m_sMoveRecs[m_iMoveCount] = TransXY(m_GoRecord[i].x, m_GoRecord[i].y, m_GoRecord[i].color);
				m_sMoveTimeRecs[m_iMoveCount].Format("%02d:%02d:%02d", m_PeriodTime.GetHours(), m_PeriodTime.GetMinutes(), m_PeriodTime.GetSeconds());
				if (m_GoRecord[i].color == BLACK)
					m_fMoveWinRates[m_iMoveCount] = m_fBlackWinRate;
				else
					m_fMoveWinRates[m_iMoveCount] = m_fWhiteWinRate;
				m_iMoveCount++;
			}
		}
		m_iGoCountMax = m_iGoCount;
		m_bRecall = true;
		//m_iRecallStartId = 0;
		m_iRecallId = m_iGoCountMax - 1;
		m_bSelfPlay = false;
		m_bEngineDual = false;
		m_iStateReopen = 0;
		m_iStateArea = 0;
		m_bSgfLoaded = true;
		m_iLabelCount = 0;
		//暂存着手记录
		m_iOldGoCount = m_iGoCount;
		m_iOldGoCountMax = m_iGoCountMax;
		memcpy(m_OldGoRecord, m_GoRecord, sizeof(Data_GoRecord) * m_iGoCountMax);
		SaveMoveRecs();
		//保存棋谱文件名
		m_sSfgFileName = filename;
		switch (iLDlevel)
		{
		case 0:
			str.Format("手筋练习第%d题", iQuest0);
			break;
		case 1:
			str.Format("初级死活第%d题", iQuest1);
			break;
		case 2:
			str.Format("中级死活第%d题", iQuest2);
			break;
		case 3:
			str.Format("高级死活第%d题", iQuest3);
			break;
		}
		if (iLanguage == 0)
		{
			switch (iLDlevel)
			{
			case 0:
				str.Format("Tesuji question No. %d", iQuest0);
				break;
			case 1:
				str.Format("Elementary question No. %d", iQuest1);
				break;
			case 2:
				str.Format("Middle question No. %d", iQuest2);
				break;
			case 3:
				str.Format("Advanced question No. %d", iQuest3);
				break;
			}
		}
			m_sPlayInfo = str;
			m_sOtherInfo = m_Gameinfo.game_name + m_Gameinfo.game_comment;
			m_iStateArea = 0;
			//备份棋谱
			CopySgfTree(&m_Sgftree1, m_Sgftree);
			int state = m_iState1;
			m_iState1 = 0;
			bool bputstonesound = bPutStoneSound;
			bPutStoneSound = false;
			OnGoFirst();
			bPutStoneSound = bputstonesound;
			m_iState1 = state;
			m_sOutputInfo = "轮玩家着手";
			if (iLanguage == 0)
				m_sOutputInfo = "Waiting for player's move";
			if (m_Gameinfo.game_name.Find("白先", 0) >= 0 || m_Gameinfo.game_comment.Find("白先", 0) >= 0)
				m_Gameinfo.to_move = WHITE;
			else
				m_Gameinfo.to_move = BLACK;
			m_iFirstColor = m_Gameinfo.to_move;
			//m_Gameinfo.to_move == BLACK ? m_sOutputInfo = "轮黑方着子" : m_sOutputInfo = "轮白方着子";
			m_iColor = m_Gameinfo.to_move;
			if (m_iColor == BLACK)
			{
				m_iStateBlackFirst = 2;
				m_iStateWhiteFirst = 0;
			}
			else
			{
				m_iStateBlackFirst = 0;
				m_iStateWhiteFirst = 2;
			}
			m_bAnaed = false;
			m_iState1 = 14;
			UpdateBackForwardButton();
		Invalidate();
	}
	m_iStateSave = 0;
	return true;
}

void CSfcGoView::OnPutBlack()
{
	m_iColor = 2;
	m_bInTurn = false;
	m_iStatePutWhite = 0;
	InvalidateRect(m_rPutBlack);
	UpdateWindow();
}

void CSfcGoView::OnPutWhite()
{
	m_iColor = 1;
	m_bInTurn = false;
	m_iStatePutBlack = 0;
	InvalidateRect(m_rPutWhite);
	UpdateWindow();
}

void CSfcGoView::OnBlackFirst()
{
	if (m_iState1 == 14)
	{
		m_iStateBlackFirst = 0;
		return;
	}
	m_Gameinfo.to_move = 2;
	m_iColor = 2;
	m_bAnaed = false;
	m_iStateWhiteFirst = 0;
	m_iStatePutBlack = 2;
	m_iStatePutWhite = 0;
	Invalidate();
	UpdateWindow();
}

void CSfcGoView::OnWhiteFirst()
{
	if (m_iState1 == 14)
	{
		m_iStateWhiteFirst = 0;
		return;
	}
	m_Gameinfo.to_move = 1;
	m_iColor = 1;
	m_bAnaed = false;
	m_iStateBlackFirst = 0;
	m_iStatePutBlack = 0;
	m_iStatePutWhite = 2;
	Invalidate();
	UpdateWindow();
}

void CSfcGoView::OnStudy()
{
	m_iLabelCount = 0;
	if (m_iState1 == 1)
		KillTimer(m_iColor);
	m_bAnswered = false;
	m_iOldFixedStone = m_iFixedStone;
	m_iFixedStone = m_iGoCount;
	m_iOldState1 = m_iState1;
	//暂存着手记录
	m_iOldGoCount = m_iGoCount;
	m_iOldGoCountMax = m_iGoCountMax;
	memcpy(m_OldGoRecord, m_GoRecord, sizeof(Data_GoRecord) * m_iGoCountMax);
	SaveMoveRecs();
	m_iGoCountMax = m_iGoCount;
	m_bInTurn = true;
	m_bRecall = false;
	int state = m_iState1;
	m_iState1 = 0;
	bool bputstonesound = bPutStoneSound;
	bPutStoneSound = false;
	OnGoFirst();
	bPutStoneSound = bputstonesound;
	m_iState1 = state;
	m_sOutputInfo = "正在研究";
	if (iLanguage == 0)
		m_sOutputInfo = "Studying";
	m_hBlackCursor = (HCURSOR)LoadImage(NULL, strSysDirectry + "\\blackstone.ico", IMAGE_ICON, m_iGap + 4, m_iGap + 4, LR_LOADFROMFILE);
	m_hWhiteCursor = (HCURSOR)LoadImage(NULL, strSysDirectry + "\\whitestone.ico", IMAGE_ICON, m_iGap + 4, m_iGap + 4, LR_LOADFROMFILE);
	m_iState1 = 13;
	m_iStateSave = 0;
	UpdateBackForwardButton();
	Invalidate();
	UpdateWindow();
}

int CSfcGoView::GetSgfVariation(SGFTree* tree, int movecounts[100], CString* movess[100], CString* commentss[100], float* winrates)
{
	int x, y, color, count = 0;
	SGFNode* node = tree->lastnode->child;
	SGFProperty* prop;
	while (node != NULL)
	{
		int gocount = 0;
		SGFNode* lastnode = node;
		while (lastnode != NULL)
		{
			for (prop = lastnode->props; prop; prop = prop->next)
			{
				switch (prop->name) {
				case SGFW://白方着手
				case SGFB://黑方着手
					GetSgfMove(prop, x, y, color);
					color = prop->name == SGFW ? WHITE : BLACK;
					movess[count][gocount] = TransXY(x, y);
					commentss[count][gocount] = "";
					break;
				case SGFC://评价
					commentss[count][gocount] = prop->value;
					break;
				case SGFMS://着手得分
					if(gocount==0)
						winrates[count] = atof(prop->value);
					break;
				}
			}
			gocount++;
			if (gocount >= 50)
				break;
			lastnode = lastnode->child;
		}
		movecounts[count] = gocount;
		count++;
		node = node->next;
	}
	return count;
}

void CSfcGoView::OnSolution()
{
	int state = m_iState1;
	m_iState1 = 0;
	bool bputstonesound = bPutStoneSound;
	bPutStoneSound = false;
	OnGoFirst();
	bPutStoneSound = bputstonesound;
	m_iState1 = state;
	if (m_iStateBlackFirst == 2)
		m_Gameinfo.to_move = 2;
	else
		m_Gameinfo.to_move = 1;
	m_iColor = m_Gameinfo.to_move;
	//获取答案
	m_Sgftree1.lastnode = m_Sgftree1.root;
	m_iAnaMoveCount = GetSgfVariation(&m_Sgftree1, m_iLifeDeathMoveCounts, m_sLifeDeathMovess, m_sLifeDeathMoveCommentss, m_fAnaMoveWinRates);
	for (int i = 0; i < m_iAnaMoveCount; i++)
	{
		m_sAnaMoveRecs[i] = m_sLifeDeathMovess[i][0];
		m_iAnaMoveVisits[i] = 0;
		m_fAnaMoveWinRates[i] = 0;
	}
	m_iState1 = 6;
	m_iAnaMoveStartId = 0;
	m_iAnaMoveId = 0;
	ShowAnaMove();
	m_iStateNew = 3;
	m_iStateOpen = 3;
}

void CSfcGoView::CopySgfTree(SGFTree* pdesttree, SGFTree sourcetree)
{
	CString filename = strSysDirectry;
	filename += "\\tmp1.sgf";
	char* fpname = filename.GetBuffer();
	writesgf(sourcetree.root, fpname);
	sgfFreeNode(pdesttree->root);
	sgftree_clear(pdesttree);
	sgftree_readfile(pdesttree, fpname);
}

bool CSfcGoView::GetSgfTreeMove(SGFTree* tree, int movecount, CString* moves, int& x, int& y, int& color, CString& comment)
{
	SGFNode* node = tree->root->child;
	SGFProperty* prop;
	m_iLabelCount = 0;
	bool found = false;
	while (node != NULL)
	{
		int id = 0;
		SGFNode* lastnode = node;
		while (lastnode != NULL)
		{
			prop = lastnode->props;
			if (prop->name == SGFW || prop->name == SGFB)
			{
				GetSgfMove(prop, x, y, color);
				color = prop->name == SGFW ? WHITE : BLACK;
				if (moves[id] != TransXY(x, y, color))
				{
					lastnode = lastnode->next;
					if (lastnode)
						continue;
					else
						break;
				}
				prop = prop->next;
				while (prop!=NULL)
				{
					if (prop->name == SGFC)
					{
						comment = prop->value;
						break;
					}
					prop = prop->next;
				}
			}
			id++;
			if (id >= movecount)
			{
				found = true;
				break;
			}
			lastnode = lastnode->child;
		}
		if (found)
		{
			lastnode = lastnode->child;
			if (lastnode)
			{
				for (prop = lastnode->props; prop; prop = prop->next)
				{
					if (prop->name == SGFW || prop->name == SGFB)
					{
						GetSgfMove(prop, x, y, color);
						color = prop->name == SGFW ? WHITE : BLACK;
					}
					else if (prop->name == SGFC)
					{
						comment = prop->value;
					}
					else if (prop->name == SGFLB)
					{
						m_sLabels[m_iLabelCount] = prop->value;
						m_iLabelCount++;
					}
				}
				if (lastnode->child == NULL)
					color = -1;
			}
			else
				x = -1;
			break;
		}
		node = node->next;
	}
	return found;
}

void CSfcGoView::OnRedo()
{
	int state = m_iState1;
	OnReturn();
	switch (state)
	{
	case 1:
		OnNew();
		break;
	case 13:
		OnStudy();
		break;
	}
	m_iColor = m_iFirstColor;
}

void CSfcGoView::ChangeDiffculty(int lvl)
{
	iLDlevel = lvl;
	m_bDifficulty = false;
	m_iStateExit = 0;
	m_iStateTesuji = 3;
	m_iStateElemantary = 3;
	m_iStateMiddle = 3;
	m_iStateAdvanced = 3;
	OnContinueQuest();
	Invalidate();
	UpdateWindow();
}

void CSfcGoView::OnAnaAll()
{
	if (m_iState1 == 22)//开始分析
	{
		if (m_bAllAnaed)//本棋谱已经分析过，直接显示结果
		{
			/*/重设着手分
			for (int i = 0; i < m_iMoveCount - 1; i++)
			{
				if (m_fMoveWinRates[i] != m_fStdMoveWinRates[i])
					m_fMoveWinRates[i] = 1 - m_fStdMoveWinRates[i + 1];
			}*/
			//计算着手胜率偏差数字特征
			double xm1, xd1, xm2, xd2;
			CalMoveScoreMD(xm1, xd1, xm2, xd2);
			if (iLanguage == 0)
			{
				CString str = "Overall analyze complete! The estimated rank scores are:\n";
				CString str1;
				str1.Format("Both: %6.2f，\n", (xm1 + xm2) / 2);
				str += str1;
				if (m_iFirstColor == BLACK)
					str += "Black: ";
				else
					str += "White: ";
				str1.Format("Mean %6.2f, Var %5.2f,\n", xm1, xd1);
				str += str1;
				if (m_iFirstColor == BLACK)
					str += "White: ";
				else
					str += "Black: ";
				str1.Format("Mean %6.2f,Var %5.2f。", xm2, xd2);
				str += str1;
				MessageBox(str, sMsg);
				m_sOutputInfo = "Analyze completed";
				m_sOtherInfo = "Click move candidate to show following moves";
			}
			else
			{
				CString str = "全盘分析完毕！估算着手等级分为\n";
				CString str1;
				str1.Format("全盘：%6.2f，\n", (xm1 + xm2) / 2);
				str += str1;
				if (m_iFirstColor == BLACK)
					str += "黑方：";
				else
					str += "白方：";
				str1.Format("均值%6.2f,方差%5.2f,\n", xm1, xd1);
				str += str1;
				if (m_iFirstColor == BLACK)
					str += "白方：";
				else
					str += "黑方：";
				str1.Format("均值%6.2f,方差%5.2f。", xm2, xd2);
				str += str1;
				MessageBox(str, "腾飞围棋提示");
				m_sOutputInfo = "分析结束";
				m_sOtherInfo = "点击候选着手表可以查看后继着手";
			}
			m_iStateNew = 0;
			m_iStateOpen = 0;
			m_iStateSave = 1;
			m_iStateReopen = 3;
			m_iStateArea = 3;
			m_iStateExit = 0;
			m_iStateResign = 3;
			this->InvalidateRect(m_rToolBox);
			return;
		}
		int mt = (m_iGoCountMax - m_iFixedStone) / 10 + 1;
		CString str;
		str.Format("将对该局中所有着手进行分析，并估算等级分，大约需要%d分钟。\n你确定要进行全盘分析吗？", mt);
		if (iLanguage == 0)
			str.Format("This will analyze all moves in the game and estimate rank scores, take about %d minutes.\nAre you sure?", mt);
		if (MessageBox(str, sMsg, MB_YESNO) != IDYES)
			return;
		//暂存着手记录
		m_iOldGoCount = m_iGoCount;
		m_iOldGoCountMax = m_iGoCountMax;
		memcpy(m_OldGoRecord, m_GoRecord, sizeof(Data_GoRecord) * m_iGoCountMax);
		m_iMoveCount = 0;
		SetRule(iRule);
		SetBoardSize(m_iBoardSize);
		//ClearBoard();
		SetHandicap(m_iHandiCap);
		SetKomi(m_fKomi);
		m_iComputerThinkTime = 5;//设置电脑思考5秒
		m_iComputerByoTime = m_iComputerThinkTime;
		SetTimes(0, m_iComputerThinkTime, m_iComputerByoStones);
		iLevel = 23;
		//iLevel = 21;
		SetLevel(iLevel);//设最高电脑棋力

		//初始化SGFTree
		sgfFreeNode(m_Sgftree.root);
		sgftree_clear(&m_Sgftree);
		CreateSgfHead(&m_Sgftree, iBoardSize, m_fKomi, m_iHandiCap);
		m_bSgf_initialized = false;
		InitSgf(&m_Gameinfo);
		m_Gameinfo.game_record = m_Sgftree;

		m_iFirstColor = m_Gameinfo.to_move;
		m_iColor = m_Gameinfo.to_move;
		m_PauseTime = m_PeriodTime;
		m_PeriodTime = CTimeSpan(m_iComputerByoTime);
		m_sOutputInfo = "腾飞围棋正在为你进行全盘分析......";
		m_sOtherInfo.Format("距分析结束还需：%d分钟", mt);
		if (iLanguage == 0)
		{
			m_sOutputInfo = "SfcGo is taking a overall analysis for you...";
			m_sOtherInfo.Format("Time needed to complete this task: %d minutes", mt);
		}
		iEngineThreadState = 1;
		AfxBeginThread(GetEngineAna, this);
		SetTimer(4, 1000, NULL);
		m_bAnaAll = true;
		m_bAnaed = false;
		m_bRecall = false;
		m_iOldState1 = m_iState1;
		m_iState1 = 4;
		m_iStateNew = 3;
		m_iStateOpen = 3;
		m_iStateSave = 3;
		m_iStateReopen = 3;
		m_iStateArea = 3;
		m_iStateExit = 3;
		m_iStateResign = 3;
		m_iStateGoBack = 3;
		m_iStateGoFiveBack = 3;
		m_iStateGoFirst = 3;
		m_iStateGoForward = 3;
		m_iStateGoFiveForward = 3;
		m_iStateGoLast = 3;
		this->InvalidateRect(m_rToolBox);
	}
	else if (m_iState1 == 4)//正在分析，提前停止
	{
		m_sOutputInfo = "分析被中断";
		if (iLanguage == 0)
			m_sOutputInfo = "Analyzing is broken";
		m_sOtherInfo = "";
		CString str = "\r\n";
		m_pEngine1->WriteToPipe(str);
		m_bAnaAll = false;
		m_bRecall = true;
	}
	else if (m_iState1 == 7)//全盘分析中，刚分析完上一着手，准备继续分析
	{
		int id = m_iGoCount;
		int x = m_GoRecord[id].x, y = m_GoRecord[id].y, color = m_GoRecord[id].color;
		Sfc::PlayStone(x, y, color, m_GoInfo);
		AddStone(x, y, color);
		SetMoveWinRateFromAna();
		m_iMoveCount++;
		//写入SGFTree
		SGFNode* lastnode = m_Sgftree.lastnode;
		SGFNode* node;
		//当前着手
		sgftreeAddPlay(&m_Sgftree, m_Gameinfo.to_move, STDPOS(x, y));
		//变招
		for (int i = 0; i < m_iAnaMoveCount; i++)
		{
			if (TransXY(x, y) != m_sAnaMoveRecs[i])
			{
				node = lastnode;
				int x1=-1, y1=-1,color1=color;
				for (int j = 0; j < m_iLifeDeathMoveCounts[i]; j++)
				{
					Trans(m_sLifeDeathMovess[i][j], x1, y1);
					node=sgfAddPlayLast(node, color1, STDPOS(x1, y1));
					//记录得分（胜率）
					if (j == 0)
					{
						char cs[10];
						sprintf_s(cs, 10, "%6.4f", m_fAnaMoveWinRates[i]);
						sgfAddProperty(node, "MS", cs);
					}
					color1 = OTHER_COLOR(color1);
				}
			}
		}
		SfcGtp* pengine;
		if (iEngineId == 0)
			pengine = m_pEngine1;
		else
			pengine = m_pEngine2;
		CString msg = "play " + TransXY(x, y, color);
		msg += "\r\n";
		pengine->WriteToPipe(msg);
		int count;
		CString* strs = pengine->GetMsg(count);
		delete[] strs;
		if (m_iGoCount == m_iOldGoCountMax)//分析完毕
		{
			KillTimer(4);
			//保存数据到SGFTree
			SgfSaveData(&m_Sgftree);
			//保存对弈结果
			if (m_bGameOver)
				sgfOverwriteProperty(m_Sgftree.root, "RE", m_sResult);
			//保存棋谱文件
			CString filename = m_sSgfPathName.Left(m_sSgfPathName.GetLength() - 4) + "_Analyzed.sgf";
			char* cs = filename.GetBuffer();
			writesgf(m_Sgftree.root, cs);
			filename = filename.Left(filename.GetLength() - 4) + ".wrt";
			SaveWinRate(filename);
			//计算着手胜率偏差数字特征
			double xm1, xd1, xm2, xd2;
			CalMoveScoreMD(xm1, xd1, xm2, xd2);
			m_bAnaAll = false;
			m_bAnaed = true;
			m_bAllAnaed = true;
			m_bRecall = true;
			m_iState1 = 22;
			m_iStateNew = 0;
			m_iStateOpen = 0;
			m_iStateSave = 0;
			m_iStateReopen = 0;
			m_iStateArea = 0;
			m_iStateExit = 0;
			m_iStateResign = 0;
			UpdateBackForwardButton();
			m_sOtherInfo = "";
			PlaySound(strSysDirectry + "\\Alarm.wav", NULL, SND_ASYNC);
			if (iLanguage == 0)
			{
				m_sOutputInfo = "Analyze completed";
				CString str = "Overall analyze complete! The estimated rank scores are:\n";
				CString str1;
				str1.Format("Both: %6.2f，\n", (xm1 + xm2) / 2);
				str += str1;
				if (m_iFirstColor == BLACK)
					str += "Black: ";
				else
					str += "White: ";
				str1.Format("Mean %6.2f, Var %5.2f,\n", xm1, xd1);
				str += str1;
				if (m_iFirstColor == BLACK)
					str += "White: ";
				else
					str += "Black: ";
				str1.Format("Mean %6.2f,Var %5.2f。", xm2, xd2);
				str += str1;
				MessageBox(str, sMsg);
			}
			else
			{
				m_sOutputInfo = "分析完毕";
				CString str = "全盘分析完毕！估算等级分为\n";
				CString str1;
				str1.Format("全盘：%6.2f，\n", (xm1 + xm2) / 2);
				str += str1;
				if (m_iFirstColor == BLACK)
					str += "黑方：";
				else
					str += "白方：";
				str1.Format("均值%6.2f,方差%5.2f,\n", xm1, xd1);
				str += str1;
				if (m_iFirstColor == BLACK)
					str += "白方：";
				else
					str += "黑方：";
				str1.Format("均值%6.2f,方差%5.2f。", xm2, xd2);
				str += str1;
				MessageBox(str, "腾飞围棋提示");
			}
			Invalidate();
			UpdateWindow();
			return;
		}
		int mt = (m_iGoCountMax - m_iGoCount) / 10 + 1;
		m_sOtherInfo.Format("距分析结束还需：%d分钟", mt);
		if (iLanguage == 0)
			m_sOtherInfo.Format("Time needed to complete this task: %d minutes", mt);
		m_Gameinfo.to_move = m_GoRecord[m_iGoCount].color;
		m_iColor = m_Gameinfo.to_move;
		m_iState1 = 4;
		m_PeriodTime = CTimeSpan(m_iComputerByoTime);
		iEngineThreadState = 1;
		AfxBeginThread(GetEngineAna, this);
	}
}

void CSfcGoView::SetMoveWinRateFromAna()
{
	//当前着手
	m_fMoveWinRates[m_iMoveCount] = -0.001;
	for (int i = 0; i < m_iAnaMoveCount; i++)
	{
		if (m_sAnaMoveRecs[i] == m_sMoveRecs[m_iMoveCount].Right(m_sMoveRecs[m_iMoveCount].GetLength()-2))
		{
			m_fMoveWinRates[m_iMoveCount] = m_fAnaMoveWinRates[i];
			break;
		}
	}
	//若当前胜率无法设置且为最后一手，以上一最佳着手来设置
	if (m_fMoveWinRates[m_iMoveCount] < 0 && m_iGoCount == m_iOldGoCountMax && m_iMoveCount>0)
		m_fMoveWinRates[m_iMoveCount] = 1 - m_fStdMoveWinRates[m_iMoveCount - 1];
	//前一着手若未设置（值为负）或非最佳着手，以本次最佳着手来设置其分值
	if (m_iMoveCount > 0 && m_fMoveWinRates[m_iMoveCount - 1] < 0)// || m_fMoveWinRates[m_iMoveCount-1]!=m_fStdMoveWinRates[m_iMoveCount-1]))
	{
		m_fMoveWinRates[m_iMoveCount - 1] = 1 - m_fAnaMoveWinRates[0];
	}
	//存储标准着手胜率
	m_fStdMoveWinRates[m_iMoveCount] = m_fAnaMoveWinRates[0];
}

void CSfcGoView::SgfSaveData(SGFTree* tree)
{
	tree->lastnode = tree->root->child;
	int id = 0;
	char cs[10];
	while (tree->lastnode != NULL && id < m_iMoveCount)
	{
		strcpy(cs, m_sMoveTimeRecs[id]);
		sgfAddProperty(tree->lastnode, "PT", cs);
		sprintf_s(cs, 10, "%6.4f", m_fMoveWinRates[id]);
		sgfAddProperty(tree->lastnode, "MS", cs);
		sprintf_s(cs, 10, "%6.4f", m_fStdMoveWinRates[id]);
		sgfAddProperty(tree->lastnode, "SS", cs);
		sgftreeForward(tree);
		id++;
	}
}

void CSfcGoView::CalMoveScoreMD(double& xm1, double& xd1, double& xm2, double& xd2)
{
	//计算着手胜率偏差数字特征
	double* xs = new double[500];
	//先着方
	int count = 0;
	for (int i = 0; i < m_iMoveCount; i += 2)
	{
		xs[count] = m_fMoveWinRates[i] / m_fStdMoveWinRates[i];
		if (xs[count] > 1.2)
			xs[count] = 1.2;
		//if(m_fStdMoveWinRates[i]>0.01)
			count++;
	}
	xm1 = Sfc::XmCal(xs, 0, count);
	xd1 = Sfc::XdCal(xs, 0, count);
	//转换为等级分
	xm1 = (1 - 4 * (1-xm1)) * 100;
	xd1 = sqrt(xd1) * 400;
	//xm1 = (1 + 5 * xm1) * 100;
	//xd1 = sqrt(xd1) * 500;
	//后着方
	count = 0;
	for (int i = 1; i < m_iMoveCount; i += 2)
	{
		xs[count] = m_fMoveWinRates[i] / m_fStdMoveWinRates[i];
		if (xs[count] > 1.2)
			xs[count] = 1.2;
		//if(m_fStdMoveWinRates[i]>0.01)
			count++;
	}
	xm2 = Sfc::XmCal(xs, 0, count);
	xd2 = Sfc::XdCal(xs, 0, count);
	//转换为等级分
	xm2 = (1 - 4 * (1-xm2)) * 100;
	xd2 = sqrt(xd2) * 400;
	//xm2 = (1 + 5 * xm2) * 100;
	//xd2 = sqrt(xd2) * 500;
	delete[] xs;
}

void CSfcGoView::PaintLabel()
{
	if (m_iLabelCount > 0)
	{
		CFont font;
		font.CreateFontA(m_iGap / 2, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
		CDC* pDC = GetDC();
		CFont* oldfont = pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(0, 0, 255));
		pDC->SetBkMode(TRANSPARENT);
		for (int i = 0; i < m_iLabelCount; i++)
		{
			int x, y;
			TransSgf(m_sLabels[i], x, y);
			CString s = m_sLabels[i].Right(m_sLabels[i].GetLength() - 3);
			CSize size = pDC->GetTextExtent(s);
			int cx = m_BoardRect.left + x * m_iGap;
			int cy = m_BoardRect.top + y * m_iGap;
			cx -= size.cx / 2;
			cy -= size.cy / 2;
			pDC->TextOutA(cx, cy, s);
		}
		pDC->SelectObject(oldfont);
		font.DeleteObject();
		ReleaseDC(pDC);
	}
}

void CSfcGoView::TransSgf(CString move, int& x, int& y)
{
	if (move.GetLength() < 2)
	{
		x = -1;
		y = -1;
	}
	else
	{
		x = move[0] - 'a';
		y = move[1] - 'a';
	}
	if (x < -1)
	{
		x = -1;
		y = -1;
	}
}


void CSfcGoView::OnMLe()
{
	if (iLanguage != 0)
	{
		iLanguage = 0;
		Sfc::WriteSysIni();
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
		CSfcGoApp::DestroyImg();
		CSfcGoApp::LoadImg();
		MessageBox("必须重启程序才能使切换语言操作完全生效！", sMsg);
		Invalidate();
	}
}


void CSfcGoView::OnUpdateMLe(CCmdUI* pCmdUI)
{
	if (iLanguage==0)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}


void CSfcGoView::OnMLz()
{
	if (iLanguage != 1)
	{
		iLanguage = 1;
		Sfc::WriteSysIni();
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
		CSfcGoApp::DestroyImg();
		CSfcGoApp::LoadImg();
		/*SetThreadUILanguage(MAKELANGID(LANG_CHINESE_SIMPLIFIED, SUBLANG_CHINESE_SIMPLIFIED));
		CMenu menu;
		menu.LoadMenuA(IDR_SfcGoTYPE);
		this->SetMenu(&menu);
		this->DrawMenuBar();
		menu.Detach();*/
		MessageBox("You mush restart this application to complete language switching!", sMsg);
		Invalidate();
	}
}


void CSfcGoView::OnUpdateMLz(CCmdUI* pCmdUI)
{
	if (iLanguage == 1)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
