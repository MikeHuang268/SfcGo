#pragma once

struct Data_Stone//棋子
{
	int x;//棋盘横坐标
	int y;//棋盘纵坐标
	int stringid;//所属棋串id
	int dragonid;//所属棋群id
	int color;//颜色
	int shape;//棋形
	int lzcount;//松散相连棋子
	int lzxs[16];//连接棋子横坐标
	int lzys[16];//连接棋子纵坐标
};

struct Data_String//棋块
{
	int color=0;//颜色
	int zcount=0;//子数
	int xs[361];//所属棋子在棋盘上的横坐标
	int ys[361];//所属棋子在棋盘上的纵坐标
	int air=0;//气数
	int airxs[180];//气横坐标
	int airys[180];//气纵坐标
	int lkcount=0;//相连棋块数
	int lkid[100];//相连棋快id
	int dragonid=0;//棋群id
};

struct Data_Dragon//棋群
{
	int color=0;//颜色
	int kcount=0;//下属棋块数
	int stringids[180];//下属棋块id
	int air=0;//气数
	int airxs[180];//气横坐标
	int airys[180];//气纵坐标
	int wair=0;
	int nair=0;
	int eye=0;//眼数
	int yxcount=0;//眼型数
	int yxids[50];//眼型id
	bool surrounded=false;//是否被包围
	bool alive=false;//是否活棋
};

struct Data_Cal//计算结果
{
	int result;//结果
	int xs[361];//着法横坐标
	int ys[361];//着法纵坐标
	int count;//着法数
};

struct Data_Yx//眼型
{
	int color=0;//颜色
	int ykcount=0;//眼型数
	int ykxs[50];
	int ykys[50];
	char name[32];//名称
	int xline;
	int yline;
	int calcount;//计算结果数
	Data_Cal cals[10];//计算结果
};

struct Data_GoRecord//着手记录
{
	int x;//棋盘横坐标
	int y;//棋盘纵坐标
	int color=0;//颜色
};

struct Data_GoInfo//围棋对局信息
{
	int boardsize;//棋盘大小
	int board[19][19];//棋盘数组，棋子的颜色，0-空，1-白，2-黑
	Data_Stone stones[19][19];//棋子数组
	Data_Stone laststone;//最后落子
	Data_Stone lastcapturestone;//最后吃子
	Data_String strings[180];//棋块数组
	int dragoncount;//棋群数
	Data_Dragon dragons[100];//棋群数组
	Data_Yx yxs[100];//眼型数组
	int gocolor;//下一着手方颜色
	int gocount;//着子记录数
	int recallstartid;//回溯起始ID
	int fixedstone;//固定棋子数，可能是对局中的让子或死活题中已摆放的棋子
	Data_GoRecord gorecord[500];//着子记录
	int anacount;//分析记录数
	Data_GoRecord anarecord[500];//分析记录
	int blackcount;//黑子数
	int whitecount;//白字数
	int blackcaptured;//黑子被吃数
	int whitecaptured;//白子被吃数
	void Init(int bsize)//初始化，bsize-棋盘大小
	{
		boardsize=bsize;
		for(int i=0;i<bsize;i++)
		{
			for(int j=0;j<bsize;j++)
			{
				board[i][j]=0;
				stones[i][j].color=0;
			}
		}
		for (int i = 0; i < 180; i++)
		{
			strings[i].color = 0;
		}
		for (int i = 0; i < 100; i++)
		{
			dragons[i].color = 0;
			yxs[i].color = 0;
		}
		laststone.color=0;
		lastcapturestone.color=0;
		dragoncount=0;
		gocolor=2;
		gocount=0;
		recallstartid=0;
		fixedstone = 0;
		anacount=0;
		blackcount=0;
		whitecount=0;
		blackcaptured=0;
		whitecaptured=0;
	}
};
class Sfc
{
public:
	Sfc(void);
	virtual ~Sfc(void);
	//计算数组均值
	static double XmCal(double x[], int first, int length);
	//计算数组方差
	static double XdCal(double x[], int first, int length);
	//对数组进行升序排序，参数bcs为真时，同时返回数组下标的排序
	static void Qs_Array(double *qs_as,int qs_first,int qs_last,int *qs_nums,bool bcs);
	//按行读取文本文件，并按指定字符分割成字符串数组
	static bool ReadLine(FILE *fp,char *c,CString strings[]);
	//重写，按行读取文本文件，按空字符分割成count个字符串数组。主意：count大于一行实有的字符串数时会读出错误结果
	static bool ReadLine(FILE *fp,int count,CString strings[]);
	//读取系统配置文件
	static bool ReadSysIni();
	//写入系统配置文件
	static bool WriteSysIni();
	//将yyyy-mm-ddThh:mm:ss字符串格式转化为时间
	static CTime GetTimeFromString(CString string);
	//着子
	static bool PlayStone(int x,int y,int color, Data_GoInfo &goinfo);
	//在棋盘上摆放棋子
	static void AddStone(int x,int y,int color, Data_GoInfo &goinfo);
	//移除棋子
	static void RemoveStone(int x,int y, Data_GoInfo &goinfo);
	//判断是否吃子点
	static bool IsCapturePoint(int x, int y, int color, Data_GoInfo &goinfo);
	//判断禁着点
	static bool IsFobidenPoint(int x,int y,int color, Data_GoInfo &goinfo);
	//判断非劫争禁着点
	static bool IsNoKoFobidenPoint(int x,int y,int color, Data_GoInfo &goinfo);
	//判断劫争点
	static bool IsKoPoint(int x, int y, int color, Data_GoInfo &goinfo);
	//判断劫争禁着点
	static bool IsKoFobidenPoint(int x, int y, int color, Data_GoInfo &goinfo);
	//判断虎口
	static bool IsTermsInside(int x, int y, int color, Data_GoInfo &goinfo);
	//判断单虎口
	static bool IsTermInside(int x, int y, int color, Data_GoInfo &goinfo);
	//判断扑劫点（即虎口相对）
	static bool IsPutKoPoint(int x, int y, int color, Data_GoInfo &goinfo);
	//判断真眼（单目眼）
	static bool IsTrueEye1(int x, int y, int color, Data_GoInfo &goinfo);
	//棋子和棋块相连
	static bool StoneLinkToString(int x,int y,int color,int stringid, Data_GoInfo &goinfo);
	//判断棋子间的连接，x，y为棋子或空点，x0，y0必须为棋子
	static bool StoneLinkToStone(int x,int y,int color,int x0,int y0,int board[19][19]);
	//判断棋子间的连接，x，y为棋子或空点，x0，y0必须为棋子
	static bool StoneLinkToStone(int x,int y,int color,int x0,int y0, Data_GoInfo &goinfo);
	//判断棋块之间的松散连接
	static bool StringLinkToString(int stringid1,int stringid2, Data_GoInfo &goinfo);
	//判断棋块和棋群是否相连
	static bool StringLinkToDragon(int stringid, int dragonid, Data_GoInfo &goinfo);
	//计算棋子
	static void CalStone(int x, int y, Data_GoInfo &goinfo);
	//计算棋块
	static void CalString(int stringid, Data_GoInfo &goinfo);
	//计算棋块周围点（不一定是气），并存入air里
	static void CalStringAroundToAir(int stringid, Data_GoInfo &goinfo);
	//计算棋子和周边己方棋子的关系，决定加入块或创建快
	static void CalStoneAround(int x, int y, int color, Data_GoInfo &goinfo);
	//计算棋子松散相连情况，并存入lzcount和lzxs，lzys
	static void CalStoneLink(int x, int y, Data_GoInfo &goinfo);
	//计算移除棋子产生的分断
	static void CalStoneRemoveDispart(int x,int y, Data_GoInfo &goinfo);
	//计算移除棋子为对方恢复的连接
	static void CalStoneRemoveLink(int x,int y);//*
	//计算棋子分断情况
	static void CalStoneDispart(int x,int y, Data_GoInfo &goinfo);
	//计算周围对方棋子被分断情况
	static void CalStoneAroundDispart(int x,int y, Data_GoInfo &goinfo);
	//计算落子周围对方棋块气数变化
	static void CalStoneAroundAir(int x, int y, Data_GoInfo &goinfo);
	//判断棋块间间接相连
	static bool StringIndirectLinkToString(int stringid1, int stringid2, Data_GoInfo &goinfo);
	//递归判断棋块间间接连接
	static bool StringILToString(int stringid1,int stringid2, int &ilcount, int ils[180], Data_GoInfo &goinfo);
	//将单个棋子分断情况加入棋块
	static void AddStoneDispartToString(int x/*被分断棋子x坐标*/,int y/*被分断棋子y坐标*/,int stringid, Data_GoInfo &goinfo);
	//为新下棋子的周围棋子加上连接
	static void AddStoneRoundLink(int x,int y, Data_GoInfo &goinfo);
	//将单个棋子连接加入棋块
	static void AddStoneLinkToString(int x,int y,int stringid, Data_GoInfo &goinfo);
	//合并棋块连接
	static void CombStringLink(int stringid1,int stringid2, Data_GoInfo &goinfo);
	//根据棋块创建新群
	static void CreateDragon(int stringid, Data_GoInfo &goinfo);
	//合并棋群,原则上是大的合并小的，返回合并后的棋群id
	static int CombDragon(int dragonid1, int dragonid2, Data_GoInfo &goinfo);
	//分断群为含本棋块和不含的两个群
	static void DispartDragon(int stringid, Data_GoInfo &goinfo);
	//创建新块
	static void CreateString(int x,int y,int color, Data_GoInfo &goinfo);
	//合并棋块,原则上是大的合并小的
	static void CombString(int stringid1,int stringid2, Data_GoInfo &goinfo);
	//计算棋块的气
	static int GetStringAir(int stringid, Data_GoInfo &goinfo);
	//将棋子添加到棋块
	static void AddStoneToString(int x,int y,int stringid, Data_GoInfo &goinfo);
	//将棋块添加到棋群
	static void AddStringToDragon(int stringid,int dragonid, Data_GoInfo &goinfo);
	//将棋子移出棋块
	static void RemoveStoneFromString(int x,int y,int stringid, Data_GoInfo &goinfo);
	//根据给定的棋子递归计算棋块
	static int CalStoneToString(int x,int y, Data_GoInfo &goinfo);
	//根据给定的棋块计算棋群
	static int CalStringToDragon(int stringid, Data_GoInfo &goinfo);
	//将棋块移出棋群
	static void RemoveStringFromDragon(int stringid, int dragonid, Data_GoInfo &goinfo);
	//计算棋群气数
	static int GetDragonAir(int dragonid, Data_GoInfo &goinfo);
	//计算棋群眼位
	void CalQqEye(int qqid);
	//复制围棋对局信息
	void CopyGoInfo(Data_GoInfo* psource_goinfo, Data_GoInfo* pdest_goinfo);
	//悔棋，num-悔棋步数
	static void Undo(int num, Data_GoInfo& goinfo);
	//获取棋群范围
	static CRect GetDragonArea(int dragonid, Data_GoInfo& goinfo);
	//判断棋群是否被包围
	static bool DragonSurrounded(int dragonid, Data_GoInfo& goinfo);
};

