
// SfcGoView.h : CSfcGoView ��Ľӿ�
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
protected: // �������л�����
	CSfcGoView();
	DECLARE_DYNCREATE(CSfcGoView)

public:
	enum{ IDD = IDD_SFCGO_FORM };

// ����
public:
	CSfcGoDoc* GetDocument() const;

// ����
public:
	bool AddStone(int x, int y, int color);//����
	//�������
	int PlayerMove(int x,int y,int color); 
	//��������
	int ComputerMove();
	//��ͨ�����������ʶת��ΪSfcGo����
	void Trans(CString str, int& x, int& y);
	//����������0Ϊ���
	bool SetLevel(int level) const;

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CSfcGoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

private:
	//������
	void PaintBoard(); 
	//������
	void PaintQz(int x,int y,int color); 
	//�����һ������
	void PaintLastQz(int x,int y,int color); 
	//�����һ������
	void PaintLastQz(); 
	//�����һ����
	void WriteLastGo(); 
	//��������˳���ڸ���״̬��ʹ��
	void PaintIdx(int id); 
	//�������ӱ�־
	void PaintStoneSignal(int x, int y, int color, CString s);
	//�����Ϣ
	void OutputInfo(); 
	//�Ƴ�����
	bool RemoveStone(int x,int y);
	//�������ֵĺ�̴���
	int ComputerMove2();
	//�����������̴�С
	bool SetEngineBoardSize(int num);
	//�����������
	bool ClearEngineBoard();
	//���ö��Ĺ���0-�й�����1-�ձ���2-����
	bool SetRule(int ruleid);
	//��������ʱ�䣬�ֱ��ǹ涨ʱ�䡢����ʱ�䡢����ʱ�������߲�����ʱ����������
	bool SetTimes(int maintime, int byotime, int stones);
	//��������̶�����
	bool SetEngineFixedHandicap(int handicap);
	//�������̴�С
	bool SetBoardSize(int num); 
	//����������
	bool SetHandicap(int num); 
	//������Ŀ
	bool SetKomi(float komi);
	//�����渴������
	void CopyBoard(); 
	//���Ʊ�������
	void CopyLocalBoard();
	//PASSһ��
	int DoPass(); 
	//�������
	void ClearBoard(); 
	//����
	int DoCapture(int pos, int color, int captures[]);
	//�������maxsizepos-Ҫ��������飬scount-�������ֵ�����smoves-�������ֵ㣬maxmoves-��������������ֵ㣬mcounts-��������������ֵ��������ӿ������ֵ��������ȡ��
	//sdepth-������ȣ�max_sdepth-��������ȣ��ﵽʱ�ݹ麯��������
	int LifeDeathAttack(int maxsizepos, int scount, int smoves[100], int color, int maxmoves[100], int mcounts[100], int sdepth, int max_sdepth);
	//�����1���ֵ����ط����֣�����ͬ��������غ�����maxsizepos-Ҫ��������飬scount-�������ֵ�����smoves-�������ֵ㣬maxmoves-��������������ֵ㣬
	//mcounts-��������������ֵ��������ӿ������ֵ��������ȡ��sdepth-������ȣ�max_sdepth-��������ȣ��ﵽʱ�ݹ麯��������
	int LifeDeathAttack1(int maxsizepos, int scount, int smoves[100], int color, int maxmoves[100], int mcounts[100], int sdepth, int max_sdepth);
	//������أ�maxsizepos-Ҫ���ص���飬scount-�������ֵ�����smoves-�������ֵ㣬maxmoves-��������������ֵ㣬mcounts-��������������ֵ��������ӿ������ֵ��������ȡ��
	//sdepth-������ȣ�max_sdepth-��������ȣ��ﵽʱ�ݹ麯��������
	int LifeDeathDefend(int maxsizepos, int scount, int smoves[100], int color, int maxmoves[100], int mcounts[100], int sdepth, int max_sdepth);
	//�������1���ֵ����������֣�����ͬ�������������maxsizepos-Ҫ��������飬scount-�������ֵ�����smoves-�������ֵ㣬maxmoves-��������������ֵ㣬
	//mcounts-��������������ֵ��������ӿ������ֵ��������ȡ��sdepth-������ȣ�max_sdepth-��������ȣ��ﵽʱ�ݹ麯��������
	int LifeDeathDefend1(int maxsizepos, int scount, int smoves[100], int color, int maxmoves[100], int mcounts[100], int sdepth, int max_sdepth);
	//�����̼�¼��SGF����
	void RecordBoard(SGFNode* node);
	//��ʼ��SFG��
	void InitSgf(Gameinfo* ginfo);
	//���н�����Ϸ�Ĳ���
	int EndGame(Gameinfo* gameinfo, int reason);
	//�����Ϸ��Ϣ
	void GameinfoClear(Gameinfo* gameinfo);
	//���������꼰��ɫת��Ϊͨ�ñ�ʶ
	CString TransXY(int x, int y, int color);
	//����������ת��Ϊͨ�ñ�ʶ
	CString TransXY(int x, int y);
	//�������ȡ�����жϷ�����Ϊ�������ʤ
	float GetScore();
	//��GoRecordת��ΪSGFTree
	int GoRecordToSgf(int gocount, Data_GoRecord gorecord[], int fixedstone, SGFTree* tree);
	//��SGFTreeת��ΪGoRecord
	int SgfToGoRecord(SGFTree* tree, int& gocount, Data_GoRecord gorecord[], int& fixedstone);
	//��SGF���ݻ�ȡ����
	void GetSgfMove(SGFProperty* prop, int& x, int& y, int& color);
	//��������
	void PlaceFixedHandicap(int handicap);
	//������Ϣ������ť
	void PaintInfo();
	//���������Ϣ������˭���ֵ�
	void PaintOutputInfo();
	//���ư�ť,buttonid=0-�����/PASS��1-������/���壬2-��������/֧�У�3-��ͣ/������4-�����жϣ�5-�˳�/�����Ծ֣�6-����
	//10-�ص������11-����5����12-����1����13-ǰ��һ����14-���5����15-�������
	void PaintButton(int buttonid);
	//�������ּ�¼��
	void PaintMoveRec();
	//����֧������
	void PaintHintStone();
	//�¶Ծ�/PASS
	void OnNew();
	//������/����
	void OnOpen();
	//��������/֧��
	void OnSave();
	//��ͣ/�������
	void OnReopen();
	//�����ж�
	void OnArea();
	//�˳�/����
	void OnExit();
	//�ص����
	void OnGoFirst();
	//�����岽
	void OnGoFiveBack();
	//����
	void OnGoBack();
	//ǰ��
	void OnGoForward();
	//ǰ���岽
	void OnGoFiveForward();
	//ǰ������
	void OnGoLast();
	//PASS
	void OnPass();
	//����
	void OnRetract();
	//֧��
	void OnHint();
	//��ͣ
	void OnPause();
	//�����Ծ�
	void OnChangeStone();
	//����
	void OnResign();
	//����SGF��ͷ
	void CreateSgfHead(SGFTree* tree, int boardsize, float komi, int handicap);
	//��ȡSGF����˫����Ϣ����ΪSfcGo�����򷵻�true
	bool GetSgfPlayerInfo(SGFProperty* prop);
	//��ȡ�ȼ���Ӧ��ͷ��
	CString GetLevelTitle(int lvl);
	//��ȡ�ȼ���Ӧ��ͷ��
	CString GetLevelFullTitle(int lvl);
	//��ȡ�Ծֽ��
	CString GetGameResult();
	//�����������
	void OnLifeDeathAna();
	//�������������ֵ㷶Χ
	CRect GetLifeDeathArea();
	//��ȡ����������ַ�Χ�ַ���
	CString GetLifeDeathAllowedMoveString(int targetdragonid);
	//�ж����Ӽ�����ӣ�x��y�����ǿհ׵㣬x0,y0����������
	bool StoneLinkToStone(int x, int y, int color, int x0, int y0, int board[19][19]);
	//�ж����ӻ�հ׵����Ⱥ֮�������
	bool StoneLinkToDragon(int x, int y, int color, int dragonid);
	//��ȡ��Ⱥ��Χ
	CRect GetDragonArea(int dragonid);
	//��ȡ��Ⱥ��Χ���ڲ��Ŀհ׵�
	int GetDragonPoints(int dragonid, int xs[361], int ys[361]);
	//��ȡ����������ַ�Χ
	int GetLifeDeathAllowedMoves(int color, int xs[361], int ys[361]);
	//��ȡ�������������ӵ�����
	int GetStonesFromBoard(int xs[361], int ys[361]);
	//��ʾ�����⹦�����
	void ShowLifeDeathPanel();
	//��ʾ��������
	void ShowAnaMove();
	//����ʤ�����ݵ��ļ�
	void SaveWinRate(CString filename);
	//���ļ���ȡʤ������
	void ReadWinRate(CString filename);
	//ִ�������о�ʱAI������ť�Ĳ���
	void OnPersistenceAna();
	//ִ�з��ذ�ť�Ĳ���
	void OnReturn();
	//����ǰ��/���˵Ȱ�ť
	void UpdateBackForwardButton();
	//�ݴ�������ʱ��ʤ��
	void SaveMoveRecs();
	//�ָ�������ʱ��ʤ��
	void RestroreMoveRecs();
	//���������ʱ
	void CalGameTime();
	//����ǰ��/���ˣ�movenumֵΪ�����Ĳ��������������ʱ
	void CalGameTime(int movenum);
	//������ϰ�Ѷ�ѡ��
	void OnDifficulty();
	//�����ϴε�������
	bool OnContinueQuest();
	//����ں��Ӱ�ť
	void OnPutBlack();
	//����ڰ��Ӱ�ť
	void OnPutWhite();
	//������Ȱ�ť
	void OnBlackFirst();
	//������Ȱ�ť
	void OnWhiteFirst();
	//�����о���ť
	void OnStudy();
	//��ȡSGFTree�ﵱǰ�ڵ����б���
	int GetSgfVariation(SGFTree* tree, int movecounts[100], CString* movess[100], CString* commentss[100], float* winrates);
	//����������鿴�𰸰�ť
	void OnSolution();
	//����SGFTREE
	void CopySgfTree(SGFTree* pdesttree, SGFTree sourcetree);
	//���ݵ�ǰ���岽��SGFTREE�в�����һ�����ɹ�����true��ʧ�ܷ���false
	bool GetSgfTreeMove(SGFTree* tree, int movecount, CString* moves, int& x, int& y, int& color, CString& comment);
	//����������ť
	void OnRedo();
	//�ı��������Ѷ�
	void ChangeDiffculty(int lvl);
	//ȫ�̷���
	void OnAnaAll();
	//�÷����������������ʤ�ʣ�������
	void SetMoveWinRateFromAna();
	//���浥����ʱ��ʤ�ʡ���׼ʤ�ʵ����ݵ�SGFTree
	void SgfSaveData(SGFTree* tree);
	//�������ַ���������
	void CalMoveScoreMD(double& xm1, double& xd1, double& xm2, double& xd2);
	//�������ϻ��Ʊ�ʶ
	void PaintLabel();
	//��SGF��ʽ����ת��ΪSFC��ʽ
	void TransSgf(CString move, int& x, int& y);

// ���ɵ���Ϣӳ�亯��
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
	int m_iState; //����״̬��1-���������2-�˻�����
	int m_iState1; //����״̬��0-��ʼ״̬��1-�ȴ�������ӣ�2-�������֣�æµ��3-��ͣ��4-����֧��/�������״̬��æµ��5-������ϣ�6-�鿴��������״̬��11-���������״̬��12-�������������׺�״̬��13-�������о�״̬��14-������ϰ״̬��
	int m_iOldState1;//����״̬�ı���
	bool m_bInTurn;	//��������
	CButton btnBz;
	virtual void OnDraw(CDC* /*pDC*/);
	int m_iPasses;
	bool m_bSgf_initialized;
	bool m_bResignation_allowed;
	int m_iBoardSize; //���̴�С
	int m_iBoard[19][19]; //��������
	int m_iGoCount; //�Ծּ�¼��
	int m_iOldGoCount;//�ݴ�ĶԾּ�¼��
	int m_iGoCountMax;//��������¼
	int m_iOldGoCountMax;//�ݴ����������¼
	Data_GoRecord m_GoRecord[500]; //�Ծ�/���Ӽ�¼
	Data_GoRecord m_OldGoRecord[500];//�ݴ�ĶԾ�/���Ӽ�¼
	CRect m_rBoardBack;//���̱�������
	CRect m_BoardRect; //��������
	int m_iGap; //����϶
	int m_iColor; //���ӷ���1-�ף�2-��
	bool m_bRecall; //���̱�־
	int m_iRecallStartId; //������ʼλ
	int m_iRecallId;//���̵�ǰλ��
	float m_fWhiteScore, m_fBlackScore;//˫���÷�
	float m_fBlackWinRate, m_fWhiteWinRate;//˫��ʤ��
	int m_iHandiCap;//������
	float m_fKomi;//��Ŀ
	int m_iFixedStone;//�̶�������
	int m_iOldFixedStone;//����Ĺ̶�������
	bool m_bPicked;//�Ѿ���������
	int m_bMouseMoveCount;//����ƶ�����
	int m_iCx, m_iCy, m_iCcolor;//�������ֵ㼰��ɫ
	int m_iProgress;//����������
	bool m_bPaused;//�Ƿ�����ͣ
	bool m_bSelfPlay;//�Ƿ�������ս
	bool m_bEngineDual;//�Ƿ������ս
	CString* m_sMoveRecs;//���������¼����׼ģʽ��
	CString* m_sMoveTimeRecs;//������ʱ
	float* m_fMoveWinRates;//����ʤ��
	float* m_fStdMoveWinRates;//��׼����ѣ�����ʤ��
	CString* m_OldMoveRecs;//�ݴ�����ּ�¼
	CString* m_sOldMoveTimeRecs;//�ݴ��������ʱ
	float* m_fOldMoveWinRates;//�ݴ������ʤ��
	int m_iFirstColor;//��������ɫ
	int m_iMoveCount;//������
	int m_iOldMoveCount;//�ݴ��������
	CString* m_sAnaMoveRecs;//�������������¼
	int* m_iAnaMoveVisits;//�������ַ��ʽڵ���
	float* m_fAnaMoveWinRates;//��������ʤ��
	int m_iAnaMoveCount;//����������
	int m_iOldAnaMoveCount;//�ݴ�ķ�������
	bool m_bAnaed;//ָʾ�Ƿ��Ѿ�������
	CString m_sBlackName;//ִ��������
	//CString m_sBlackTitle;//ִ����ͷ��
	CString m_sWhiteName;//ִ��������
	//CString m_sWhiteTitle;//ִ����ͷ��
	//int m_iBlackLevel;//ִ���ߵȼ�
	//int m_iWhiteLevel;//ִ���ߵȼ�
	bool m_bSgfLoaded;//����������
	bool m_bSfcSgfLoaded;//������SfcGo����������
	CString m_sResult;//�Ծֽ��
	bool m_bGameOver;//�Ծ��Ƿ����
	bool m_bReOpen;//�Ƿ����ؿ��Ծ�
	int m_iLifeDeathMoveCounts[100];
	CString* m_sLifeDeathMovess[100];
	CString* m_sLifeDeathMoveCommentss[100];
	CString m_sLifeDeathCmd;//�����������
	bool m_bShowLifeDeathPanel;//�Ƿ���ʾ��������
	int m_iMoveRecHeight;//���ּ�¼�߶�
	int m_iAnaMoveId;//�������ּ�¼ID
	int m_iAnaMoveStartId;//����������ʾ��ʼID
	int m_iADColor = 1;//����/����Ⱥ��ɫ
	int m_iCombat = 0;//�Ծ����ͣ�0-���ɶԾ֣�1-��ս��
	bool m_bShowRecSize;//�Ƿ�����Ļ�ռ���ʾʤ��ͼ�����������ּ�¼��
	bool m_bShowInfoSize;//�Ƿ�����Ļ�ռ���ʾ�Ծ���Ϣ�����ܰ�ť��
	bool m_bDifficulty;//�Ƿ�������������ϰ�Ѷ�ѡ��״̬
	bool m_bAnswered;//�������Ѿ����
	bool m_bAnaAll;//�Ƿ�����ȫ�̷���
	bool m_bAllAnaed;//�Ƿ��Ѿ�ȫ�̷�����
	int m_iLabelCount;//�����
	bool m_bCaptured;
	CString* m_sLabels;//����б�
	HCURSOR m_hBlackCursor;//�������α�
	HCURSOR m_hWhiteCursor;//�������α�
	CRect m_rBlackInfo;//������Ϣ����
	CRect m_rWhiteInfo;//������Ϣ����
	CRect m_rBlackTime;//����ʱ������
	CRect m_rWhiteTime;//����ʱ������
	CRect m_rProgressBar;//����������
	CRect m_rPeriodString;//������ʱ�ַ�����
	CRect m_rPeriodTime;//������ʱ����
	CRect m_rPlayInfo;//��Ϸ��Ϣ����
	CRect m_rOutputInfo;//��Ϣ������򣬰�����˭���ߵȵ�
	CRect m_rOtherInfo;//������Ϣ���������ʤ�ʵ�
	CRect m_rToolBox;//����������
	CRect m_rNew;//�¶Ծ�/PASS��ť����
	CRect m_rOpen;//������/���尴ť����
	CRect m_rSave;//��������֧�а�ť����
	CRect m_rReopen;//��ͣ/������ְ�ť����
	CRect m_rArea;//�����жϰ�ť����
	CRect m_rExit;//�˳�/�����Ծְ�ť����
	CRect m_rGoFirst;//�ص������ť����
	CRect m_rGoFiveBack;//�����岽��ť����
	CRect m_rGoBack;//���˰�ť����
	CRect m_rGoForward;//ǰ����ť����
	CRect m_rGoFiveForward;//ǰ���岽��ť����
	CRect m_rGoLast;//ǰ�����װ�ť����
	CRect m_rResign;//���䰴ť����
	CRect m_rWinRateChart;//ʤ��ͼ������
	CRect m_rAnaMove;//������������
	CRect m_rMoveRec;//���ּ�¼����
	CRect m_rPanel;//�����⹦���������
	CRect m_rTesuji;//�ֽ���ϰ��ť����
	CRect m_rElementary;//�������ť����
	CRect m_rMiddle;//�м����ť����
	CRect m_rAdvanced;//�߼����ť����
	CRect m_rPutBlack;//�ڷź��Ӱ�ť����
	CRect m_rPutWhite;//�ڷŰ��Ӱ�ť����
	CRect m_rBlackFirst;//���Ȱ�ť����
	CRect m_rWhiteFirst;//���Ȱ�ť����
	int m_iStateNew;//�¶Ծ�/PASS��ť״̬��0-normal, 1-hover, 2-down, 3-disable
	int m_iStateOpen;//������/���尴ť״̬��0-normal, 1-hover, 2-down, 3-disable
	int m_iStateSave;//����/֧�а�ť״̬��0-normal, 1-hover, 2-down, 3-disable
	int m_iStateReopen;//����/��ͣ��ť״̬��0-normal, 1-hover, 2-down, 3-disable
	int m_iStateArea;//�����жϰ�ť״̬��0-normal, 1-hover, 2-down, 3-disable
	int m_iStateExit;//�˳�/������ť״̬��0-normal, 1-hover, 2-down, 3-disable
	int m_iStateGoFirst;//�ص������ť״̬��0-normal, 1-hover, 2-down, 3-disable
	int m_iStateGoFiveBack;
	int m_iStateGoBack;
	int m_iStateGoForward;
	int m_iStateGoFiveForward;
	int m_iStateGoLast;
	int m_iStateResign;//���䰴ť״̬��0-normal, 1-hover, 2-down, 3-disable
	int m_iStateTesuji;//�ֽ���ϰ��ť״̬
	int m_iStateElemantary;//�������ť״̬
	int m_iStateMiddle;//�м����ť״̬
	int m_iStateAdvanced;//�߼����ť״̬
	int m_iStatePutBlack;//�ڷź��Ӱ�ť״̬
	int m_iStatePutWhite;//�ڷŰ��Ӱ�ť״̬
	int m_iStateBlackFirst;//���Ȱ�ť״̬
	int m_iStateWhiteFirst;//���Ȱ�ť״̬
	int m_iMainTime;//���Ĺ涨ʱ��
	int m_iByoTime;//����ʱ��
	int m_iByoStones;//����������
	int m_iComputerThinkTime;//����˼��ʱ��
	int m_iComputerThinkTime2;//������ս���սʱ�ڶ�����˼��ʱ��
	int m_iComputerByoTime;//���Զ���ʱ�䣬��maintimeΪ0ʱ�����õ��Ե���ʱ��
	int m_iComputerByoTime2;//������ս���սʱ�ڶ��������ʱ�䣬��maintimeΪ0ʱ�����õ���ʱ��
	int m_iComputerByoStones;//���Զ���������
	CString m_sPlayInfo;//��Ϸ��Ϣ
	CString m_sOutputInfo;//�����Ϣ
	CString m_sOtherInfo;//������Ϣ
	CTime m_StartTime;//���Ŀ�ʼʱ��
	CTime m_PauseStartTime;//������ͣ��ʼʱ��
	CTimeSpan m_PauseTime;//������ͣ��ʱ��
	CTimeSpan m_BlackTime;//������ʱ
	CTimeSpan m_WhiteTime;//������ʱ
	CTimeSpan m_PeriodTime;//������ʱ
	Data_GoInfo m_GoInfo;
	Gameinfo m_Gameinfo;
	SGFTree m_Sgftree;
	SGFTree m_Sgftree1;
	CString m_sSfgFileName;//����������ļ�
	CString m_sSgfPathName;//����������ļ�ȫ������·����
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
	int m_iMaxSizePos;//���������Ŀ���
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

#ifndef _DEBUG  // SfcGoView.cpp �еĵ��԰汾
inline CSfcGoDoc* CSfcGoView::GetDocument() const
   { return reinterpret_cast<CSfcGoDoc*>(m_pDocument); }
#endif

