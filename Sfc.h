#pragma once

struct Data_Stone//����
{
	int x;//���̺�����
	int y;//����������
	int stringid;//�����崮id
	int dragonid;//������Ⱥid
	int color;//��ɫ
	int shape;//����
	int lzcount;//��ɢ��������
	int lzxs[16];//�������Ӻ�����
	int lzys[16];//��������������
};

struct Data_String//���
{
	int color=0;//��ɫ
	int zcount=0;//����
	int xs[361];//���������������ϵĺ�����
	int ys[361];//���������������ϵ�������
	int air=0;//����
	int airxs[180];//��������
	int airys[180];//��������
	int lkcount=0;//���������
	int lkid[100];//�������id
	int dragonid=0;//��Ⱥid
};

struct Data_Dragon//��Ⱥ
{
	int color=0;//��ɫ
	int kcount=0;//���������
	int stringids[180];//�������id
	int air=0;//����
	int airxs[180];//��������
	int airys[180];//��������
	int wair=0;
	int nair=0;
	int eye=0;//����
	int yxcount=0;//������
	int yxids[50];//����id
	bool surrounded=false;//�Ƿ񱻰�Χ
	bool alive=false;//�Ƿ����
};

struct Data_Cal//������
{
	int result;//���
	int xs[361];//�ŷ�������
	int ys[361];//�ŷ�������
	int count;//�ŷ���
};

struct Data_Yx//����
{
	int color=0;//��ɫ
	int ykcount=0;//������
	int ykxs[50];
	int ykys[50];
	char name[32];//����
	int xline;
	int yline;
	int calcount;//��������
	Data_Cal cals[10];//������
};

struct Data_GoRecord//���ּ�¼
{
	int x;//���̺�����
	int y;//����������
	int color=0;//��ɫ
};

struct Data_GoInfo//Χ��Ծ���Ϣ
{
	int boardsize;//���̴�С
	int board[19][19];//�������飬���ӵ���ɫ��0-�գ�1-�ף�2-��
	Data_Stone stones[19][19];//��������
	Data_Stone laststone;//�������
	Data_Stone lastcapturestone;//������
	Data_String strings[180];//�������
	int dragoncount;//��Ⱥ��
	Data_Dragon dragons[100];//��Ⱥ����
	Data_Yx yxs[100];//��������
	int gocolor;//��һ���ַ���ɫ
	int gocount;//���Ӽ�¼��
	int recallstartid;//������ʼID
	int fixedstone;//�̶��������������ǶԾ��е����ӻ����������Ѱڷŵ�����
	Data_GoRecord gorecord[500];//���Ӽ�¼
	int anacount;//������¼��
	Data_GoRecord anarecord[500];//������¼
	int blackcount;//������
	int whitecount;//������
	int blackcaptured;//���ӱ�����
	int whitecaptured;//���ӱ�����
	void Init(int bsize)//��ʼ����bsize-���̴�С
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
	//���������ֵ
	static double XmCal(double x[], int first, int length);
	//�������鷽��
	static double XdCal(double x[], int first, int length);
	//����������������򣬲���bcsΪ��ʱ��ͬʱ���������±������
	static void Qs_Array(double *qs_as,int qs_first,int qs_last,int *qs_nums,bool bcs);
	//���ж�ȡ�ı��ļ�������ָ���ַ��ָ���ַ�������
	static bool ReadLine(FILE *fp,char *c,CString strings[]);
	//��д�����ж�ȡ�ı��ļ��������ַ��ָ��count���ַ������顣���⣺count����һ��ʵ�е��ַ�����ʱ�����������
	static bool ReadLine(FILE *fp,int count,CString strings[]);
	//��ȡϵͳ�����ļ�
	static bool ReadSysIni();
	//д��ϵͳ�����ļ�
	static bool WriteSysIni();
	//��yyyy-mm-ddThh:mm:ss�ַ�����ʽת��Ϊʱ��
	static CTime GetTimeFromString(CString string);
	//����
	static bool PlayStone(int x,int y,int color, Data_GoInfo &goinfo);
	//�������ϰڷ�����
	static void AddStone(int x,int y,int color, Data_GoInfo &goinfo);
	//�Ƴ�����
	static void RemoveStone(int x,int y, Data_GoInfo &goinfo);
	//�ж��Ƿ���ӵ�
	static bool IsCapturePoint(int x, int y, int color, Data_GoInfo &goinfo);
	//�жϽ��ŵ�
	static bool IsFobidenPoint(int x,int y,int color, Data_GoInfo &goinfo);
	//�жϷǽ������ŵ�
	static bool IsNoKoFobidenPoint(int x,int y,int color, Data_GoInfo &goinfo);
	//�жϽ�����
	static bool IsKoPoint(int x, int y, int color, Data_GoInfo &goinfo);
	//�жϽ������ŵ�
	static bool IsKoFobidenPoint(int x, int y, int color, Data_GoInfo &goinfo);
	//�жϻ���
	static bool IsTermsInside(int x, int y, int color, Data_GoInfo &goinfo);
	//�жϵ�����
	static bool IsTermInside(int x, int y, int color, Data_GoInfo &goinfo);
	//�ж��˽ٵ㣨��������ԣ�
	static bool IsPutKoPoint(int x, int y, int color, Data_GoInfo &goinfo);
	//�ж����ۣ���Ŀ�ۣ�
	static bool IsTrueEye1(int x, int y, int color, Data_GoInfo &goinfo);
	//���Ӻ��������
	static bool StoneLinkToString(int x,int y,int color,int stringid, Data_GoInfo &goinfo);
	//�ж����Ӽ�����ӣ�x��yΪ���ӻ�յ㣬x0��y0����Ϊ����
	static bool StoneLinkToStone(int x,int y,int color,int x0,int y0,int board[19][19]);
	//�ж����Ӽ�����ӣ�x��yΪ���ӻ�յ㣬x0��y0����Ϊ����
	static bool StoneLinkToStone(int x,int y,int color,int x0,int y0, Data_GoInfo &goinfo);
	//�ж����֮�����ɢ����
	static bool StringLinkToString(int stringid1,int stringid2, Data_GoInfo &goinfo);
	//�ж�������Ⱥ�Ƿ�����
	static bool StringLinkToDragon(int stringid, int dragonid, Data_GoInfo &goinfo);
	//��������
	static void CalStone(int x, int y, Data_GoInfo &goinfo);
	//�������
	static void CalString(int stringid, Data_GoInfo &goinfo);
	//���������Χ�㣨��һ����������������air��
	static void CalStringAroundToAir(int stringid, Data_GoInfo &goinfo);
	//�������Ӻ��ܱ߼������ӵĹ�ϵ�����������򴴽���
	static void CalStoneAround(int x, int y, int color, Data_GoInfo &goinfo);
	//����������ɢ���������������lzcount��lzxs��lzys
	static void CalStoneLink(int x, int y, Data_GoInfo &goinfo);
	//�����Ƴ����Ӳ����ķֶ�
	static void CalStoneRemoveDispart(int x,int y, Data_GoInfo &goinfo);
	//�����Ƴ�����Ϊ�Է��ָ�������
	static void CalStoneRemoveLink(int x,int y);//*
	//�������ӷֶ����
	static void CalStoneDispart(int x,int y, Data_GoInfo &goinfo);
	//������Χ�Է����ӱ��ֶ����
	static void CalStoneAroundDispart(int x,int y, Data_GoInfo &goinfo);
	//����������Χ�Է���������仯
	static void CalStoneAroundAir(int x, int y, Data_GoInfo &goinfo);
	//�ж�����������
	static bool StringIndirectLinkToString(int stringid1, int stringid2, Data_GoInfo &goinfo);
	//�ݹ��ж�����������
	static bool StringILToString(int stringid1,int stringid2, int &ilcount, int ils[180], Data_GoInfo &goinfo);
	//���������ӷֶ�����������
	static void AddStoneDispartToString(int x/*���ֶ�����x����*/,int y/*���ֶ�����y����*/,int stringid, Data_GoInfo &goinfo);
	//Ϊ�������ӵ���Χ���Ӽ�������
	static void AddStoneRoundLink(int x,int y, Data_GoInfo &goinfo);
	//�������������Ӽ������
	static void AddStoneLinkToString(int x,int y,int stringid, Data_GoInfo &goinfo);
	//�ϲ��������
	static void CombStringLink(int stringid1,int stringid2, Data_GoInfo &goinfo);
	//������鴴����Ⱥ
	static void CreateDragon(int stringid, Data_GoInfo &goinfo);
	//�ϲ���Ⱥ,ԭ�����Ǵ�ĺϲ�С�ģ����غϲ������Ⱥid
	static int CombDragon(int dragonid1, int dragonid2, Data_GoInfo &goinfo);
	//�ֶ�ȺΪ�������Ͳ���������Ⱥ
	static void DispartDragon(int stringid, Data_GoInfo &goinfo);
	//�����¿�
	static void CreateString(int x,int y,int color, Data_GoInfo &goinfo);
	//�ϲ����,ԭ�����Ǵ�ĺϲ�С��
	static void CombString(int stringid1,int stringid2, Data_GoInfo &goinfo);
	//����������
	static int GetStringAir(int stringid, Data_GoInfo &goinfo);
	//��������ӵ����
	static void AddStoneToString(int x,int y,int stringid, Data_GoInfo &goinfo);
	//�������ӵ���Ⱥ
	static void AddStringToDragon(int stringid,int dragonid, Data_GoInfo &goinfo);
	//�������Ƴ����
	static void RemoveStoneFromString(int x,int y,int stringid, Data_GoInfo &goinfo);
	//���ݸ��������ӵݹ�������
	static int CalStoneToString(int x,int y, Data_GoInfo &goinfo);
	//���ݸ�������������Ⱥ
	static int CalStringToDragon(int stringid, Data_GoInfo &goinfo);
	//������Ƴ���Ⱥ
	static void RemoveStringFromDragon(int stringid, int dragonid, Data_GoInfo &goinfo);
	//������Ⱥ����
	static int GetDragonAir(int dragonid, Data_GoInfo &goinfo);
	//������Ⱥ��λ
	void CalQqEye(int qqid);
	//����Χ��Ծ���Ϣ
	void CopyGoInfo(Data_GoInfo* psource_goinfo, Data_GoInfo* pdest_goinfo);
	//���壬num-���岽��
	static void Undo(int num, Data_GoInfo& goinfo);
	//��ȡ��Ⱥ��Χ
	static CRect GetDragonArea(int dragonid, Data_GoInfo& goinfo);
	//�ж���Ⱥ�Ƿ񱻰�Χ
	static bool DragonSurrounded(int dragonid, Data_GoInfo& goinfo);
};

