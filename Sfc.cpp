#include "stdafx.h"
#include "Sfc.h"

extern CString strSysDirectry;//ϵͳĿ¼
extern CString strDirectry;//����Ŀ¼
extern CString strImgDirectry;//ͼ���ļ�Ŀ¼
extern CString strOutputDirectry;//���Ŀ¼
extern CString Version;//�汾��
extern CString Edition;//�汾
extern int iLanguage;//����
extern int iCpuNum;//cpu���ˣ���
extern bool volatile bAnalysing;//���ڷ�����
extern CString sPlayerName;//�����
extern int iPlayerLevel;//��ҵȼ�
extern int iEngineNum;//������
extern int iEngineTypes[10];//����ID
extern CString sEngineNames[10];//��������
extern CString sEngineAppNames[10];//����ִ���ļ���
extern CString sEngineAppDirs[10];//����Ŀ¼
extern CString sEngineCmdLines[10];//����������
extern CString sEngineCmdLines1[10];//����������1��������������ǿ����
extern int iPlayer1;//�������ߣ�0-��ң�1-����
extern int iLevel1;//����ִ��ʱ�ĵȼ���1-���Σ�10-��ʥ
extern int iTime1;//����ִ��ʱ��˼��ʱ����0-15�룬1-30�룬2-60�룬3-120��
extern int iEngine1;//��������ѡ��
extern int iPlayer2;//�������ߣ���0-��ң�1-����
extern int iLevel2;//����ִ��ʱ�ĵȼ���1-���Σ�10-��ʥ
extern int iTime2;//����ִ��ʱ��˼��ʱ����0-15�룬1-30�룬2-60�룬3-120��
extern int iEngine2;//��������ѡ��
extern int iRule;//���Ĺ���0-�й���1-�ձ���2-����
extern int iBoard;//���̹��0-19·��1-13·��2-9·
extern int iKomi;//��Ŀ��0-����10Ŀ��40-��10Ŀ
extern int iHandi;//��������0-���ȣ�1-���ȣ�2����-������
extern bool bCoord;//�Ƿ���������
extern bool bAnimate;//�Ƿ������Ӷ���
extern bool bThinkProgress;//�Ƿ���ʾ����˼������
extern bool bPutStoneSound;//�Ƿ񲥷���������
extern bool bCaptureSound;//�Ƿ񲥷���������
extern bool bPickStoneSound;//�Ƿ񲥷Ŵ������ʰ�ӵ�����
extern bool bPushClockSound;//�Ƿ񲥷Ű���ʱ�ӵ�����
extern bool bByoSound;//�Ƿ񲥷Ŷ�����
extern int iLDlevel;//������ȼ���0-�ֽ1-������2-�м���3-�߼�
extern int iQuest0;//�ֽ���ϰ��ǰ���
extern int iQuest1;//�������ǰ���
extern int iQuest2;//�м����ǰ���
extern int iQuest3;//�߼����ǰ���

/* Colors and komaster states. */
enum colors {
	EMPTY,
	WHITE,
	BLACK,
	GRAY,
	GRAY_WHITE,
	GRAY_BLACK,
	WEAK_KO,
	NUM_KOMASTER_STATES
};

#define COLOR_NAMES \
	"empty", \
	"white", \
	"black", \
	"gray", \
	"gray_white", \
	"gray_black", \
	"weak_ko"

#define OTHER_COLOR(color)      (WHITE+BLACK-(color))
#define IS_STONE(arg)           ((arg) == WHITE || (arg) == BLACK)

Sfc::Sfc(void)
{
}


Sfc::~Sfc(void)
{
}

double Sfc::XmCal(double x[], int first, int length)
{
	double xm = 0;
	for (int i = 0; i < length; i++) xm += x[first + i];
	xm = xm / length;
	return xm;
}

double Sfc::XdCal(double x[], int first, int length)
{
	double xm = XmCal(x, first, length);
	double xd = 0;
	for (int i = 0; i < length; i++) xd += (x[first + i] - xm) * (x[first + i] - xm);
	xd = xd / length;
	return xd;
}

//����������������򣬲���bcsΪ��ʱ��ͬʱ���������±������
void Sfc::Qs_Array(double *qs_as,int qs_first,int qs_last,int *qs_nums,bool bcs)
{
	register int qs_i,qs_j;
	int num;
	double qs_x;
	double qs_y;
	qs_i=qs_first;
	qs_j=qs_last;
	qs_x=qs_as[(qs_first+qs_last)/2];
	do{
		while(qs_as[qs_i]<qs_x&&qs_i<qs_last) qs_i++;
		while(qs_as[qs_j]>qs_x&&qs_j>qs_first) qs_j--;
		if(qs_i<=qs_j){
			qs_y=qs_as[qs_i];
			qs_as[qs_i]=qs_as[qs_j];
			qs_as[qs_j]=qs_y;
			if(bcs)
			{
				num=qs_nums[qs_i];
				qs_nums[qs_i]=qs_nums[qs_j];
				qs_nums[qs_j]=num;
			}
			qs_i++;
			qs_j--;
		}
	}
	while(qs_i<=qs_j);
	if(qs_j>qs_first) Qs_Array(qs_as,qs_first,qs_j,qs_nums,bcs);
	if(qs_i<qs_last) Qs_Array(qs_as,qs_i,qs_last,qs_nums,bcs);
}

//���ж�ȡ�ı��ļ�������ָ���ַ��ָ���ַ�������
bool Sfc::ReadLine(FILE *fp,char *c,CString strings[])
{
	//CString *goinfo.strings=(CString *)calloc(255,sizeof(CString));
	char cs[2048],cs1[2048];
	int count,i=0,j,k,l,len=strlen(c);
	bool retl=true;
	do
	{
		char c1=fgetc(fp);
		if(c1=='\n' || c1==-1)
		{
			if(c1==-1) retl=false;
			break;
		}
		cs[i]=c1;
		i++;
	}while(true);
	cs[i]='\0';
	if (len == 0)//�ָ��Ϊ��ʱ�����зָ�
	{
		strings[0] = cs;
		strings[1] = "";
		return retl;
	}
	count=i;l=0;
	for(i=0;i<count;i++)
	{
		for(j=i;j<count;j++)
		{
			bool logic=false;
			for(int i1=0;i1<len;i1++)
			{
				if(cs[j]!=c[i1])
				{
					logic=true;
					break;
				}
			}
			if(logic) break;
		}
		for(k=j;k<count;k++)
		{
			bool logic=false;
			for(int i1=0;i1<len;i1++)
			{
				if(cs[k]==c[i1])
				{
					logic=true;
					break;
				}
			}
			if(logic) break;
			//if(cs[k]==c) break;
			cs1[k-j]=cs[k];
		}
		cs1[k-j]='\0';
		CString string=cs1;
		strings[l]=string.Trim();
		if(strings[l].GetLength()>0)
			l++;
		i=k;
	}
	strings[l]="";
	return retl;
}

//��д�����ж�ȡ�ı��ļ��������ַ��ָ��count���ַ������顣���⣺count����һ��ʵ�е��ַ�����ʱ�����������
bool Sfc::ReadLine(FILE *fp,int count,CString strings[])
{
	for(int i=0;i<count;i++) fscanf_s(fp,"%s",strings[i]);
	//����
	char c='a';
	do
	{
		c=fgetc(fp);
	}while(c!='\n' && c!=-1);
	if(c==-1) return false;
	return true;
}

//��ȡϵͳ�����ļ�
bool Sfc::ReadSysIni()
{
	errno_t err;
	FILE *fp;
	if((err=fopen_s(&fp,strSysDirectry+"\\Sys.ini","rb"))!=0)
	{
		AfxMessageBox("Read file sys.ini failed",NULL,MB_OK);
		return false;
	}
	int enginenum = 0;
	CString strings[255];
	bool success;
	do
	{
		success=ReadLine(fp,"=",strings);
		if(strings[0]=="Version")
		{
			Version=strings[1];
			continue;
		}
		if(strings[0]=="Edition")
		{
			Edition=strings[1];
			continue;
		}
		if (strings[0] == "Language")
		{
			if (strings[1] == "EN")
				iLanguage = 0;
			else if (strings[1] == "CN")
				iLanguage = 1;
			continue;
		}
		if(strings[0]=="CpuNum")
		{
			iCpuNum=atoi(strings[1])-1;
			if(iCpuNum<=0)
				iCpuNum=1;
			continue;
		}
		if (strings[0] == "PlayerName")
		{
			sPlayerName = strings[1];
			continue;
		}
		if (strings[0] == "PlayerLevel")
		{
			iPlayerLevel = atoi(strings[1]);
			continue;
		}
		if (strings[0] == "EngineType")
		{
			iEngineTypes[enginenum] = atoi(strings[1]);
			continue;
		}
		if (strings[0] == "EngineName")
		{
			sEngineNames[enginenum] = strings[1];
			continue;
		}
		if (strings[0] == "EngineAppName")
		{
			sEngineAppNames[enginenum] = strings[1];
			continue;
		}
		if (strings[0] == "EngineAppDir")
		{
			sEngineAppDirs[enginenum] = strings[1];
			continue;
		}
		if (strings[0] == "EngineCmdLine")
		{
			sEngineCmdLines[enginenum] = strings[1];
			continue;
		}
		if (strings[0] == "EngineCmdLine1")
		{
			sEngineCmdLines1[enginenum] = strings[1];
			enginenum++;
			continue;
		}
		if (strings[0] == "Player1")
		{
			iPlayer1 = atoi(strings[1]);
			continue;
		}
		if (strings[0] == "Level1")
		{
			iLevel1 = atoi(strings[1]);
			continue;
		}
		if (strings[0] == "Time1")
		{
			iTime1 = atoi(strings[1]);
			continue;
		}
		if (strings[0] == "Engine1")
		{
			iEngine1 = atoi(strings[1]);
			continue;
		}
		if (strings[0] == "Player2")
		{
			iPlayer2 = atoi(strings[1]);
			continue;
		}
		if (strings[0] == "Level2")
		{
			iLevel2 = atoi(strings[1]);
			continue;
		}
		if (strings[0] == "Time2")
		{
			iTime2 = atoi(strings[1]);
			continue;
		}
		if (strings[0] == "Engine2")
		{
			iEngine2 = atoi(strings[1]);
			continue;
		}
		if (strings[0] == "Rule")
		{
			iRule = atoi(strings[1]);
			continue;
		}
		if (strings[0] == "Board")
		{
			iBoard = atoi(strings[1]);
			continue;
		}
		if (strings[0] == "Komi")
		{
			iKomi = atoi(strings[1]);
			continue;
		}
		if (strings[0] == "Handi")
		{
			iHandi = atoi(strings[1]);
			continue;
		}
		if (strings[0] == "Coord")
		{
			bCoord = (atoi(strings[1]) != 0);
			continue;
		}
		if (strings[0] == "Animate")
		{
			bAnimate = (atoi(strings[1]) != 0);
			continue;
		}
		if (strings[0] == "ThinkProgress")
		{
			bThinkProgress = (atoi(strings[1]) != 0);
			continue;
		}
		if (strings[0] == "PutStoneSound")
		{
			bPutStoneSound = (atoi(strings[1]) != 0);
			continue;
		}
		if (strings[0] == "CaptureSound")
		{
			bCaptureSound = (atoi(strings[1]) != 0);
			continue;
		}
		if (strings[0] == "PickStoneSound")
		{
			bPickStoneSound = (atoi(strings[1]) != 0);
			continue;
		}
		if (strings[0] == "PushClockSound")
		{
			bPushClockSound = (atoi(strings[1]) != 0);
			continue;
		}
		if (strings[0] == "ByoSound")
		{
			bByoSound = (atoi(strings[1]) != 0);
			continue;
		}
		if (strings[0] == "LDlevel")
		{
			iLDlevel = atoi(strings[1]);
			continue;
		}
		if (strings[0] == "Quest0")
		{
			iQuest0 = atoi(strings[1]);
			continue;
		}
		if (strings[0] == "Quest1")
		{
			iQuest1 = atoi(strings[1]);
			continue;
		}
		if (strings[0] == "Quest2")
		{
			iQuest2 = atoi(strings[1]);
			continue;
		}
		if (strings[0] == "Quest3")
		{
			iQuest3 = atoi(strings[1]);
			continue;
		}
	}while(success);
	fclose(fp);
	iEngineNum = enginenum;
	return true;
}

//д��ϵͳ�����ļ�
bool Sfc::WriteSysIni()
{
	errno_t err;
	FILE *fp;
	if((err=fopen_s(&fp,strSysDirectry+"\\Sys.ini","w"))!=0)
	{
		CString msg = "�޷�д��ϵͳ�����ļ���";
		if (iLanguage == 0)
			msg = "Cannot write file sys.ini";
		AfxMessageBox(msg,NULL,MB_OK);
		return false;
	}
	CString str="Version=";
	int len=str.GetLength();
	fwrite(str,sizeof(char),len,fp);
	str=Version;
	str+="\n";
	len=str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str="Edition=";
	len=str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str=Edition;
	str+="\n";
	len=str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str = "Language=";
	switch (iLanguage)
	{
	case 0:
		str += "EN";
		break;
	case 1:
		str += "CN";
		break;
	}
	str += "\n";
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("CpuNum=%d\n", iCpuNum + 1);
	len=str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str = "PlayerName=" + sPlayerName+"\n";
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("PlayerLevel=%d\n", iPlayerLevel);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	for (int i = 0; i < iEngineNum; i++)
	{
		str.Format("EngineType=%d\n", iEngineTypes[i]);
		len = str.GetLength();
		fwrite(str, sizeof(char), len, fp);
		str = "EngineName=" + sEngineNames[i] + "\n";
		len = str.GetLength();
		fwrite(str, sizeof(char), len, fp);
		str = "EngineAppName="+sEngineAppNames[i] + "\n";
		len = str.GetLength();
		fwrite(str, sizeof(char), len, fp);
		str = "EngineAppDir="+sEngineAppDirs[i] + "\n";
		len = str.GetLength();
		fwrite(str, sizeof(char), len, fp);
		str = "EngineCmdLine="+sEngineCmdLines[i] + "\n";
		len = str.GetLength();
		fwrite(str, sizeof(char), len, fp);
		str = "EngineCmdLine1="+sEngineCmdLines1[i] + "\n";
		len = str.GetLength();
		fwrite(str, sizeof(char), len, fp);
	}
	str.Format("Player1=%d\n", iPlayer1);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("Level1=%d\n", iLevel1);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("Time1=%d\n", iTime1);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("Engine1=%d\n", iEngine1);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("Player2=%d\n", iPlayer2);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("Level2=%d\n", iLevel2);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("Time2=%d\n", iTime2);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("Engine2=%d\n", iEngine2);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("Rule=%d\n", iRule);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("Board=%d\n", iBoard);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("Komi=%d\n", iKomi);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("Handi=%d\n", iHandi);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("Coord=%d\n", bCoord ? 1 : 0);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("Animate=%d\n", bAnimate ? 1 : 0);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("ThinkProgress=%d\n", bThinkProgress ? 1 : 0);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("PutStoneSound=%d\n", bPutStoneSound ? 1 : 0);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("CaptureSound=%d\n", bCaptureSound ? 1 : 0);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("PickStoneSound=%d\n", bPickStoneSound ? 1 : 0);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("PushClockSound=%d\n", bPushClockSound ? 1 : 0);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("ByoSound=%d\n", bByoSound ? 1 : 0);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("LDlevel=%d\n", iLDlevel);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("Quest0=%d\n", iQuest0);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("Quest1=%d\n", iQuest1);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("Quest2=%d\n", iQuest2);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	str.Format("Quest3=%d\n", iQuest3);
	len = str.GetLength();
	fwrite(str, sizeof(char), len, fp);
	fclose(fp);
	return true;
}

//��yyyy-mm-ddThh:mm:ss�ַ�����ʽת��Ϊʱ��
CTime Sfc::GetTimeFromString(CString string)
{
	int id0,id,year,month,day,hour,minute,second;
	char cs[10];
	//year
	CString string1=string.Left(4);
	year=atoi(string1);
	//month
	for(id=5;id<7;id++)
	{
		if(string[id]=='-') break;
		cs[id-5]=string[id];
	}
	cs[id-5]='\0';
	month=atoi(cs);
	//day
	id0=id+1;
	for(id=id0;id<id0+2;id++)
	{
		if(string[id]=='T') break;
		cs[id-id0]=string[id];
	}
	cs[id-id0]='\0';
	day=atoi(cs);
	//hour
	id0=id+1;
	cs[0]=string[id0];
	cs[1]=string[id0+1];
	cs[2]='\0';
	hour=atoi(cs);
	//minute
	id0=id0+3;
	cs[0]=string[id0];
	cs[1]=string[id0+1];
	cs[2]='\0';
	minute=atoi(cs);
	//second
	id0=id0+3;
	cs[0]=string[id0];
	cs[1]=string[id0+1];
	cs[2]='\0';
	second=atoi(cs);
	CTime ct(year,month,day,hour,minute,second);
	return ct;
}

//����
bool Sfc::PlayStone(int x,int y,int color, Data_GoInfo &goinfo)
{
	if (x < 0 || x >= goinfo.boardsize || y<0 || y>goinfo.boardsize)
		return false;
	if (color != BLACK && color != WHITE)
		return false;
	goinfo.gorecord[goinfo.gocount].color = color;
	goinfo.gorecord[goinfo.gocount].x = x;
	goinfo.gorecord[goinfo.gocount].y = y;
	goinfo.gocount++;
	if(color==1) goinfo.whitecount++;
	else goinfo.blackcount++;
	int othercolor=OTHER_COLOR(color);
	goinfo.gocolor = othercolor;
	//����
	goinfo.board[x][y]=color;
	goinfo.stones[x][y].x=x;
	goinfo.stones[x][y].y=y;
	goinfo.stones[x][y].color=color;
	goinfo.stones[x][y].stringid=-1;
	//����������Ⱥ
	bool added=false;
	if(x>0 && goinfo.stones[x-1][y].color==color)
	{
		AddStoneToString(x,y,goinfo.stones[x-1][y].stringid,goinfo);
		added=true;
	}
	if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==color)
	{
		if(!added)
		{
			AddStoneToString(x,y,goinfo.stones[x+1][y].stringid,goinfo);
			added=true;
		}
		else
		{
			if(goinfo.stones[x+1][y].stringid!=goinfo.stones[x][y].stringid) CombString(goinfo.stones[x][y].stringid,goinfo.stones[x+1][y].stringid,goinfo);
		}
	}
	if(y>0 && goinfo.stones[x][y-1].color==color)
	{
		if(!added)
		{
			AddStoneToString(x,y,goinfo.stones[x][y-1].stringid,goinfo);
			added=true;
		}
		else
		{
			if(goinfo.stones[x][y-1].stringid!=goinfo.stones[x][y].stringid) CombString(goinfo.stones[x][y].stringid,goinfo.stones[x][y-1].stringid,goinfo);
		}
	}
	if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==color)
	{
		if(!added)
		{
			AddStoneToString(x,y,goinfo.stones[x][y+1].stringid,goinfo);
			added=true;
		}
		else
		{
			if(goinfo.stones[x][y+1].stringid!=goinfo.stones[x][y].stringid) CombString(goinfo.stones[x][y].stringid,goinfo.stones[x][y+1].stringid,goinfo);
		}
	}
	if(!added) CreateString(x,y,color,goinfo);
	//�ж��Ƿ����
	int aircount=0;
	int airxs[180];
	int airys[180];
	if(x>0 && goinfo.stones[x-1][y].color==othercolor && goinfo.strings[goinfo.stones[x-1][y].stringid].air==1)
	{
		int stringid=goinfo.stones[x-1][y].stringid;
		CalStringAroundToAir(stringid,goinfo);
		//Array.Copy(goinfo.strings[stringid].airxs,0,airxs,aircount,goinfo.strings[stringid].air);
		//Array.Copy(goinfo.strings[stringid].airys,0,airys,aircount,goinfo.strings[stringid].air);
		memcpy_s(airxs,goinfo.strings[stringid].air*sizeof(int),goinfo.strings[stringid].airxs,goinfo.strings[stringid].air*sizeof(int));
		memcpy_s(airys,goinfo.strings[stringid].air*sizeof(int),goinfo.strings[stringid].airys,goinfo.strings[stringid].air*sizeof(int));
		aircount+=goinfo.strings[stringid].air;
		RemoveStringFromDragon(stringid,goinfo.strings[stringid].dragonid,goinfo);
		goinfo.strings[stringid].color=0;
		goinfo.strings[stringid].lkcount=0;
		//goinfo.stringsCount--;
		for(int i=0;i<goinfo.strings[stringid].zcount;i++)
		{
			int x1=goinfo.strings[stringid].xs[i];
			int y1=goinfo.strings[stringid].ys[i];
			if (goinfo.stones[x1][y1].color != 0)
			{
				goinfo.stones[x1][y1].color == 2 ? goinfo.blackcaptured++ : goinfo.whitecaptured++;
			}
			goinfo.stones[x1][y1].color=0;
			goinfo.stones[x1][y1].lzcount=0;
			goinfo.stones[x1][y1].stringid=-1;
			goinfo.board[x1][y1]=0;
		}
	}
	if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==othercolor && goinfo.strings[goinfo.stones[x+1][y].stringid].air==1)
	{
		int stringid=goinfo.stones[x+1][y].stringid;
		CalStringAroundToAir(stringid,goinfo);
		//memcpy_s(airxs,goinfo.strings[stringid].air*sizeof(int),goinfo.strings[stringid].airxs,goinfo.strings[stringid].air*sizeof(int));
		//memcpy_s(airys,goinfo.strings[stringid].air*sizeof(int),goinfo.strings[stringid].airys,goinfo.strings[stringid].air*sizeof(int));
		//aircount+=goinfo.strings[stringid].air;
		for (int i = 0; i < goinfo.strings[stringid].air; i++)
		{
			int j;
			for (j = 0; j < aircount; j++)
			{
				if (airxs[j] == goinfo.strings[stringid].airxs[i] && airys[j] == goinfo.strings[stringid].airys[i])
					break;
			}
			if (j == aircount)
			{
				airxs[j] = goinfo.strings[stringid].airxs[i];
				airys[j] = goinfo.strings[stringid].airys[i];
				aircount++;
			}
		}
		RemoveStringFromDragon(stringid,goinfo.strings[stringid].dragonid,goinfo);
		goinfo.strings[stringid].color=0;
		goinfo.strings[stringid].lkcount=0;
		//goinfo.stringsCount--;
		for(int i=0;i<goinfo.strings[stringid].zcount;i++)
		{
			int x1=goinfo.strings[stringid].xs[i];
			int y1=goinfo.strings[stringid].ys[i];
			if (goinfo.stones[x1][y1].color != 0)
			{
				goinfo.stones[x1][y1].color == 2 ? goinfo.blackcaptured++ : goinfo.whitecaptured++;
			}
			goinfo.stones[x1][y1].color=0;
			goinfo.stones[x1][y1].lzcount=0;
			goinfo.stones[x1][y1].stringid=-1;
			goinfo.board[x1][y1]=0;
		}
	}
	if(y>0 && goinfo.stones[x][y-1].color==othercolor && goinfo.strings[goinfo.stones[x][y-1].stringid].air==1)
	{
		int stringid=goinfo.stones[x][y-1].stringid;
		CalStringAroundToAir(stringid,goinfo);
		//memcpy_s(airxs,goinfo.strings[stringid].air*sizeof(int),goinfo.strings[stringid].airxs,goinfo.strings[stringid].air*sizeof(int));
		//memcpy_s(airys,goinfo.strings[stringid].air*sizeof(int),goinfo.strings[stringid].airys,goinfo.strings[stringid].air*sizeof(int));
		//aircount+=goinfo.strings[stringid].air;
		for (int i = 0; i < goinfo.strings[stringid].air; i++)
		{
			int j;
			for (j = 0; j < aircount; j++)
			{
				if (airxs[j] == goinfo.strings[stringid].airxs[i] && airys[j] == goinfo.strings[stringid].airys[i])
					break;
			}
			if (j == aircount)
			{
				airxs[j] = goinfo.strings[stringid].airxs[i];
				airys[j] = goinfo.strings[stringid].airys[i];
				aircount++;
			}
		}
		RemoveStringFromDragon(stringid,goinfo.strings[stringid].dragonid,goinfo);
		goinfo.strings[stringid].color=0;
		goinfo.strings[stringid].lkcount=0;
		//goinfo.stringsCount--;
		for(int i=0;i<goinfo.strings[stringid].zcount;i++)
		{
			int x1=goinfo.strings[stringid].xs[i];
			int y1=goinfo.strings[stringid].ys[i];
			if (goinfo.stones[x1][y1].color != 0)
			{
				goinfo.stones[x1][y1].color == 2 ? goinfo.blackcaptured++ : goinfo.whitecaptured++;
			}
			goinfo.stones[x1][y1].color=0;
			goinfo.stones[x1][y1].lzcount=0;
			goinfo.stones[x1][y1].stringid=-1;
			goinfo.board[x1][y1]=0;
		}
	}
	if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==othercolor && goinfo.strings[goinfo.stones[x][y+1].stringid].air==1)
	{
		int stringid=goinfo.stones[x][y+1].stringid;
		CalStringAroundToAir(stringid,goinfo);
		//memcpy_s(airxs,goinfo.strings[stringid].air*sizeof(int),goinfo.strings[stringid].airxs,goinfo.strings[stringid].air*sizeof(int));
		//memcpy_s(airys,goinfo.strings[stringid].air*sizeof(int),goinfo.strings[stringid].airys,goinfo.strings[stringid].air*sizeof(int));
		//aircount+=goinfo.strings[stringid].air;
		for (int i = 0; i < goinfo.strings[stringid].air; i++)
		{
			int j;
			for (j = 0; j < aircount; j++)
			{
				if (airxs[j] == goinfo.strings[stringid].airxs[i] && airys[j] == goinfo.strings[stringid].airys[i])
					break;
			}
			if (j == aircount)
			{
				airxs[j] = goinfo.strings[stringid].airxs[i];
				airys[j] = goinfo.strings[stringid].airys[i];
				aircount++;
			}
		}
		RemoveStringFromDragon(stringid,goinfo.strings[stringid].dragonid,goinfo);
		goinfo.strings[stringid].color=0;
		goinfo.strings[stringid].lkcount=0;
		//goinfo.stringsCount--;
		for(int i=0;i<goinfo.strings[stringid].zcount;i++)
		{
			int x1=goinfo.strings[stringid].xs[i];
			int y1=goinfo.strings[stringid].ys[i];
			if (goinfo.stones[x1][y1].color != 0)
			{
				goinfo.stones[x1][y1].color == 2 ? goinfo.blackcaptured++ : goinfo.whitecaptured++;
			}
			goinfo.stones[x1][y1].color=0;
			goinfo.stones[x1][y1].lzcount=0;
			goinfo.stones[x1][y1].stringid=-1;
			goinfo.board[x1][y1]=0;
		}
	}
	if(aircount>0)//�г������
	{
		//ȷ����Ӱ������
		int qkcount=0;
		int stringids[180]{ 0 };
		for(int i=0;i<aircount;i++)
		{
			if (goinfo.stones[airxs[i]][airys[i]].stringid == -1)
				continue;
			int j;
			for(j=0;j<qkcount;j++)
			{
				if(goinfo.stones[airxs[i]][airys[i]].stringid==stringids[j]) break;
			}
			if(j==qkcount)
			{
				stringids[j]=goinfo.stones[airxs[i]][airys[i]].stringid;
				qkcount++;
			}
		}
		//���¼������
		for(int i=0;i<qkcount;i++)
		{
			CalString(stringids[i],goinfo);
			if(goinfo.strings[stringids[i]].dragonid>-1)
			{
				RemoveStringFromDragon(stringids[i],goinfo.strings[stringids[i]].dragonid,goinfo);
				goinfo.strings[stringids[i]].dragonid=-1;
			}
		}
		//������Ⱥ
		for(int i=0;i<qkcount;i++)
		{
			CalStringToDragon(stringids[i],goinfo);
		}
	}
	//�Է�
	CalStoneAroundDispart(x,y,goinfo);
	CalStoneAroundAir(x,y,goinfo);
	//���±�ʶ�������ӵ�dragonid
	for (int i = 0; i < goinfo.boardsize; i++)
	{
		for (int j = 0; j < goinfo.boardsize; j++)
			if(goinfo.stones[i][j].color>0)
				goinfo.stones[i][j].dragonid = goinfo.strings[goinfo.stones[i][j].stringid].dragonid;
	}
	return aircount > 0;
}

//�������ϰڷ�����
void Sfc::AddStone(int x,int y,int color, Data_GoInfo &goinfo)
{
	if (x < 0 || x >= goinfo.boardsize || y<0 || y>goinfo.boardsize)
		return;
	if (color != BLACK && color != WHITE)
		return;
	if(color==WHITE) goinfo.whitecount++;
	else goinfo.blackcount++;
	//����
	goinfo.board[x][y]=color;
	goinfo.stones[x][y].x=x;
	goinfo.stones[x][y].y=y;
	goinfo.stones[x][y].color=color;
	goinfo.stones[x][y].stringid=-1;
	//����������Ⱥ
	bool added=false;
	if(x>0 && goinfo.stones[x-1][y].color==color)
	{
		AddStoneToString(x,y,goinfo.stones[x-1][y].stringid,goinfo);
		added=true;
	}
	if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==color)
	{
		if(!added)
		{
			AddStoneToString(x,y,goinfo.stones[x+1][y].stringid,goinfo);
			added=true;
		}
		else
		{
			if(goinfo.stones[x+1][y].stringid!=goinfo.stones[x][y].stringid) CombString(goinfo.stones[x][y].stringid,goinfo.stones[x+1][y].stringid,goinfo);
		}
	}
	if(y>0 && goinfo.stones[x][y-1].color==color)
	{
		if(!added)
		{
			AddStoneToString(x,y,goinfo.stones[x][y-1].stringid,goinfo);
			added=true;
		}
		else
		{
			if(goinfo.stones[x][y-1].stringid!=goinfo.stones[x][y].stringid) CombString(goinfo.stones[x][y].stringid,goinfo.stones[x][y-1].stringid,goinfo);
		}
	}
	if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==color)
	{
		if(!added)
		{
			AddStoneToString(x,y,goinfo.stones[x][y+1].stringid,goinfo);
			added=true;
		}
		else
		{
			if(goinfo.stones[x][y+1].stringid!=goinfo.stones[x][y].stringid) CombString(goinfo.stones[x][y].stringid,goinfo.stones[x][y+1].stringid,goinfo);
		}
	}
	if(!added) CreateString(x,y,color,goinfo);
	//�Է�
	CalStoneAroundDispart(x,y,goinfo);
	CalStoneAroundAir(x,y,goinfo);
}

//�Ƴ�����
void Sfc::RemoveStone(int x,int y, Data_GoInfo &goinfo)
{
	RemoveStoneFromString(x,y,goinfo.stones[x][y].stringid,goinfo);
	//�����ܱߵ����仯
	//ȷ����Ӱ������
	int qkcount=0;
	int stringids[180];
	for(int i=-2;i<3;i++)
	{
		for(int j=-2;j<3;j++)
		{
			if(x+i<0 || x+i>goinfo.boardsize-1 || y+j<0 || y+j>goinfo.boardsize-1) continue;
			if(goinfo.stones[x+i][y+j].color==0) continue;
			int stringid=goinfo.stones[x+i][y+j].stringid;
			int k;
			for(k=0;k<qkcount;k++)
			{
				if(stringids[k]==stringid) break;
			}
			if(k==qkcount)
			{
				stringids[k]=stringid;
				qkcount++;
			}
		}
	}
	//���¼������
	for(int i=0;i<qkcount;i++)
	{
		CalString(stringids[i],goinfo);
		if(goinfo.strings[stringids[i]].dragonid>-1)
		{
			RemoveStringFromDragon(stringids[i],goinfo.strings[stringids[i]].dragonid,goinfo);
			goinfo.strings[stringids[i]].dragonid=-1;
		}
	}
	//������Ⱥ
	for(int i=0;i<qkcount;i++)
	{
		CalStringToDragon(stringids[i],goinfo);
	}
}

//���Ӻ��������
bool Sfc::StoneLinkToString(int x,int y,int color,int stringid,Data_GoInfo &goinfo)
{
	if(goinfo.strings[stringid].color!=color) return false;
	int othercolor=OTHER_COLOR(color);
	//С������
	if(x>0 && y>0)
	{
		if(goinfo.stones[x-1][y-1].stringid==stringid)
		{
			if(goinfo.stones[x-1][y].color!=othercolor)
			{
				if(x==goinfo.boardsize-1) return true;
				else if(goinfo.stones[x][y-1].color!=othercolor) return true;
			}
			else if(y==goinfo.boardsize-1 && goinfo.stones[x][y-1].color!=othercolor) return true;
		}
	}
	if(x>0 && y<goinfo.boardsize-1)
	{
		if(goinfo.stones[x-1][y+1].stringid==stringid)
		{
			if(goinfo.stones[x-1][y].color!=othercolor)
			{
				if(x==goinfo.boardsize-1) return true;
				else if(goinfo.stones[x][y+1].color!=othercolor) return true;
			}
			else if(y==0 && goinfo.stones[x][y+1].color!=othercolor) return true;
		}
	}
	if(x<goinfo.boardsize-1 && y>0)
	{
		if(goinfo.stones[x+1][y-1].stringid==stringid)
		{
			if(goinfo.stones[x][y-1].color!=othercolor)
			{
				if(x==0) return true;
				else if(goinfo.stones[x+1][y].color!=othercolor) return true;
			}
			else if(y==goinfo.boardsize-1 && goinfo.stones[x+1][y].color!=othercolor) return true;
		}
	}
	if(x<goinfo.boardsize-1 && y<goinfo.boardsize-1)
	{
		if(goinfo.stones[x+1][y+1].stringid==stringid)
		{
			if(goinfo.stones[x][y+1].color!=othercolor)
			{
				if(x==0) return true;
				else if(goinfo.stones[x+1][y].color!=othercolor) return true;
			}
			else if(y==goinfo.boardsize-1 && goinfo.stones[x+1][y].color!=othercolor) return true;
		}
	}
	//��������
	if(x>1)
	{
		if(goinfo.stones[x-2][y].stringid==stringid)
		{
			if(goinfo.stones[x-1][y].color!=othercolor)
			{
				if(y<2)
				{
					if(goinfo.stones[x-1][y+1].color!=othercolor) return true;
				}
				else if(y>goinfo.boardsize-3)
				{
					if(goinfo.stones[x-1][y-1].color!=othercolor) return true;
				}
				else if(goinfo.stones[x-1][y+1].color!=othercolor && goinfo.stones[x-1][y-1].color!=othercolor) return true;
			}
		}
	}
	if(x<goinfo.boardsize-2)
	{
		if(goinfo.stones[x+2][y].stringid==stringid)
		{
			if(goinfo.stones[x+1][y].color!=othercolor)
			{
				if(y<2)
				{
					if(goinfo.stones[x+1][y+1].color!=othercolor) return true;
				}
				else if(y>goinfo.boardsize-3)
				{
					if(goinfo.stones[x+1][y-1].color!=othercolor) return true;
				}
				else if(goinfo.stones[x+1][y+1].color!=othercolor && goinfo.stones[x+1][y-1].color!=othercolor) return true;
			}
		}
	}
	if(y>1)
	{
		if(goinfo.stones[x][y-2].stringid==stringid)
		{
			if(goinfo.stones[x][y-1].color!=othercolor)
			{
				if(x<2)
				{
					if(goinfo.stones[x+1][y-1].color!=othercolor) return true;
				}
				else if(x>goinfo.boardsize-3)
				{
					if(goinfo.stones[x-1][y-1].color!=othercolor) return true;
				}
				else if(goinfo.stones[x+1][y-1].color!=othercolor && goinfo.stones[x-1][y-1].color!=othercolor) return true;
			}
		}
	}
	if(y<goinfo.boardsize-2)
	{
		if(goinfo.stones[x][y+2].stringid==stringid)
		{
			if(goinfo.stones[x][y+1].color!=othercolor)
			{
				if(x<2)
				{
					if(goinfo.stones[x+1][y+1].color!=othercolor) return true;
				}
				else if(x>goinfo.boardsize-3)
				{
					if(goinfo.stones[x-1][y+1].color!=othercolor) return true;
				}
				else if(goinfo.stones[x+1][y+1].color!=othercolor && goinfo.stones[x-1][y+1].color!=othercolor) return true;
			}
		}
	}
	//С������
	return false;
}


//�ж����Ӽ����ɢ���ӣ�x��yΪ���ӻ�յ㣬x0��y0����Ϊ����
bool Sfc::StoneLinkToStone(int x,int y,int color,int x0,int y0, Data_GoInfo &goinfo)
{
	if(color!=goinfo.stones[x0][y0].color)
		return false;
	int othercolor=OTHER_COLOR(color);
	//ֱ������
	//if((x-1==x0 || x+1==x0) && y==y0 || x==x0 && (y-1==y0 || y+1==y0))
	//	return true;
	//С������
	if(x-1==x0 && y-1==y0)
	{
		if(goinfo.stones[x-1][y].color!=othercolor)
		{
			if(IsTermsInside(x-1,y,color,goinfo)) return true;
			else if(goinfo.stones[x][y-1].color!=othercolor) return true;
		}
		else if(goinfo.stones[x][y-1].color!=othercolor && IsTermsInside(x,y-1,color,goinfo)) return true;
	}
	if(x-1==x0 && y+1==y0)
	{
		if(goinfo.stones[x-1][y].color!=othercolor)
		{
			if(IsTermsInside(x-1,y,color,goinfo)) return true;
			else if(goinfo.stones[x][y+1].color!=othercolor) return true;
		}
		else if(goinfo.stones[x][y+1].color!=othercolor && IsTermsInside(x,y+1,color,goinfo)) return true;
	}
	if(x+1==x0 && y-1==y0)
	{
		if(goinfo.stones[x][y-1].color!=othercolor)
		{
			if(IsTermsInside(x,y-1,color,goinfo)) return true;
			else if(goinfo.stones[x+1][y].color!=othercolor) return true;
		}
		else if(goinfo.stones[x+1][y].color!=othercolor && IsTermsInside(x+1,y,color,goinfo)) return true;
	}
	if(x+1==x0 && y+1==y0)
	{
		if(goinfo.stones[x][y+1].color!=othercolor)
		{
			if(IsTermsInside(x,y+1,color,goinfo)) return true;
			else if(goinfo.stones[x+1][y].color!=othercolor) return true;
		}
		else if(goinfo.stones[x+1][y].color!=othercolor&& IsTermsInside(x+1,y,color,goinfo)) return true;
	}
	//��������
	if(x-2==x0 && y==y0)
	{
		if(goinfo.stones[x-1][y].color!=othercolor)
		{
			if(y<2)
			{
				if(goinfo.stones[x-1][y+1].color!=othercolor) return true;
			}
			else if(y>goinfo.boardsize-3)
			{
				if(goinfo.stones[x-1][y-1].color!=othercolor) return true;
			}
			else if(goinfo.stones[x-1][y+1].color!=othercolor && goinfo.stones[x-1][y-1].color!=othercolor) return true;
		}
	}
	if(x+2==x0 && y==y0)
	{
		if(goinfo.stones[x+1][y].color!=othercolor)
		{
			if(y<2)
			{
				if(goinfo.stones[x+1][y+1].color!=othercolor) return true;
			}
			else if(y>goinfo.boardsize-3)
			{
				if(goinfo.stones[x+1][y-1].color!=othercolor) return true;
			}
			else if(goinfo.stones[x+1][y+1].color!=othercolor && goinfo.stones[x+1][y-1].color!=othercolor) return true;
		}
	}
	if(y-2==y0 && x==x0)
	{
		if(goinfo.stones[x][y-1].color!=othercolor)
		{
			if(x<2)
			{
				if(goinfo.stones[x+1][y-1].color!=othercolor) return true;
			}
			else if(x>goinfo.boardsize-3)
			{
				if(goinfo.stones[x-1][y-1].color!=othercolor) return true;
			}
			else if(goinfo.stones[x+1][y-1].color!=othercolor && goinfo.stones[x-1][y-1].color!=othercolor) return true;
		}
	}
	if(y+2==y0 && x==x0)
	{
		if(goinfo.stones[x][y+1].color!=othercolor)
		{
			if(x<2)
			{
				if(goinfo.stones[x+1][y+1].color!=othercolor) return true;
			}
			else if(x>goinfo.boardsize-3)
			{
				if(goinfo.stones[x-1][y+1].color!=othercolor) return true;
			}
			else if(goinfo.stones[x+1][y+1].color!=othercolor && goinfo.stones[x-1][y+1].color!=othercolor) return true;
		}
	}
	//С������
	if(x-2==x0 && y-1==y0)
	{
		if(goinfo.stones[x-1][y-1].color!=othercolor
			&& goinfo.stones[x-1][y].color!=othercolor
			&& (y<2 || goinfo.stones[x-1][y-2].color!=othercolor)
			&& (y>goinfo.boardsize-2 || goinfo.stones[x-1][y+1].color!=othercolor))
			return true;
	}
	if(x-2==x0 && y+1==y0)
	{
		if(goinfo.stones[x-1][y+1].color!=othercolor
			&& goinfo.stones[x-1][y].color!=othercolor
			&& (y<1 || goinfo.stones[x-1][y-1].color!=othercolor)
			&& (y>goinfo.boardsize-3 || goinfo.stones[x-1][y+2].color!=othercolor))
			return true;
	}
	if(x-1==x0 && y-2==y0)
	{
		if(goinfo.stones[x-1][y-1].color!=othercolor
			&& goinfo.stones[x][y-1].color!=othercolor
			&& (x<2 || goinfo.stones[x-2][y-1].color!=othercolor)
			&& (x>goinfo.boardsize-2 || goinfo.stones[x+1][y-1].color!=othercolor))
			return true;
	}
	if(x+1==x0 && y-2==y0)
	{
		if(goinfo.stones[x][y-1].color!=othercolor
			&& goinfo.stones[x+1][y-1].color!=othercolor
			&& (x<1 || goinfo.stones[x-1][y-1].color!=othercolor)
			&& (x>goinfo.boardsize-3 || goinfo.stones[x+2][y-1].color!=othercolor))
			return true;
	}
	if(x+2==x0 && y-1==y0)
	{
		if(goinfo.stones[x+1][y-1].color!=othercolor
			&& goinfo.stones[x+1][y].color!=othercolor
			&& (y<2 || goinfo.stones[x+1][y-2].color!=othercolor)
			&& (y>goinfo.boardsize-2 || goinfo.stones[x+1][y+1].color!=othercolor))
			return true;
	}
	if(x+2==x0 && y+1==y0)
	{
		if(goinfo.stones[x+1][y+1].color!=othercolor
			&& goinfo.stones[x+1][y].color!=othercolor
			&& (y<1 || goinfo.stones[x+1][y-1].color!=othercolor)
			&& (y>goinfo.boardsize-3 || goinfo.stones[x+1][y+2].color!=othercolor))
			return true;
	}
	if(x-1==x0 && y+2==y0)
	{
		if(goinfo.stones[x-1][y+1].color!=othercolor
			&& goinfo.stones[x][y+1].color!=othercolor
			&& (x<2 || goinfo.stones[x-2][y+1].color!=othercolor)
			&& (x>goinfo.boardsize-2 || goinfo.stones[x+1][y+1].color!=othercolor))
			return true;
	}
	if(x+1==x0 && y+2==y0)
	{
		if(goinfo.stones[x][y+1].color!=othercolor
			&& goinfo.stones[x+1][y+1].color!=othercolor
			&& (x<1 || goinfo.stones[x-1][y+1].color!=othercolor)
			&& (x>goinfo.boardsize-3 || goinfo.stones[x+2][y+1].color!=othercolor)) return true;
	}
	return false;
}

//�ж��Ƿ���ӵ�
bool Sfc::IsCapturePoint(int x, int y, int color, Data_GoInfo &goinfo)
{
	int othercolor=OTHER_COLOR(color);
	if(x>0 && goinfo.stones[x-1][y].color==othercolor && goinfo.strings[goinfo.stones[x-1][y].stringid].air==1
		|| x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==othercolor && goinfo.strings[goinfo.stones[x+1][y].stringid].air==1
		|| y>0 && goinfo.stones[x][y-1].color==othercolor && goinfo.strings[goinfo.stones[x][y-1].stringid].air==1
		|| y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==othercolor && goinfo.strings[goinfo.stones[x][y+1].stringid].air==1)
		return true;
	return false;
}

//�жϽ��ŵ�
bool Sfc::IsFobidenPoint(int x,int y,int color,Data_GoInfo &goinfo)
{
	int othercolor=OTHER_COLOR(color);
	//�ж���յ����
	if(x-1>=0 && goinfo.stones[x-1][y].color==0 || x+1<=goinfo.boardsize-1 && goinfo.stones[x+1][y].color==0 || y-1>=0 && goinfo.stones[x][y-1].color==0 || y+1<=goinfo.boardsize-1 && goinfo.stones[x][y+1].color==0) return false;
	//�������ӵ����
	if((x==0 || goinfo.stones[x-1][y].color==othercolor) && (x==goinfo.boardsize-1 || goinfo.stones[x+1][y].color==othercolor) && (y==0 || goinfo.stones[x][y-1].color==othercolor) && (y==goinfo.boardsize-1 || goinfo.stones[x][y+1].color==othercolor))
	{
		if(x>0 && goinfo.stones[x-1][y].color==othercolor)
		{
			int stringid=goinfo.stones[x-1][y].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1 && goinfo.laststone.x==x-1 && goinfo.laststone.y==y)//����
					return true;
				else return false;
			}
		}
		if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==othercolor)
		{
			int stringid=goinfo.stones[x+1][y].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1 && goinfo.laststone.x==x+1 && goinfo.laststone.y==y)//����
					return true;
				else return false;
			}
		}
		if(y>0 && goinfo.stones[x][y-1].color==othercolor)
		{
			int stringid=goinfo.stones[x][y-1].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1 && goinfo.laststone.x==x && goinfo.laststone.y==y-1)//����
					return true;
				else return false;
			}
		}
		if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==othercolor)
		{
			int stringid=goinfo.stones[x][y+1].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1 && goinfo.laststone.x==x && goinfo.laststone.y==y+1)//����
					return true;
				else return false;
			}
		}
		return true;
	}
	//�������
	if(x>0 && goinfo.stones[x-1][y].color==color)
	{
		if(goinfo.strings[goinfo.stones[x-1][y].stringid].air>1) return false;
	}
	if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==color)
	{
		if(goinfo.strings[goinfo.stones[x+1][y].stringid].air>1) return false;
	}
	if(y>0 && goinfo.stones[x][y-1].color==color)
	{
		if(goinfo.strings[goinfo.stones[x][y-1].stringid].air>1) return false;
	}
	if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==color)
	{
		if(goinfo.strings[goinfo.stones[x][y+1].stringid].air>1) return false;
	}
	if(x>0 && goinfo.stones[x-1][y].color==othercolor)
	{
		if(goinfo.strings[goinfo.stones[x-1][y].stringid].air==1) return false;
	}
	if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==othercolor)
	{
		if(goinfo.strings[goinfo.stones[x+1][y].stringid].air==1) return false;
	}
	if(y>0 && goinfo.stones[x][y-1].color==othercolor)
	{
		if(goinfo.strings[goinfo.stones[x][y-1].stringid].air==1) return false;
	}
	if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==othercolor)
	{
		if(goinfo.strings[goinfo.stones[x][y+1].stringid].air==1) return false;
	}
	return true;
}

//�жϷǽ������ŵ�
bool Sfc::IsNoKoFobidenPoint(int x,int y,int color, Data_GoInfo &goinfo)
{
	//�Ѿ����ӵĵ㲻���ж�Ϊ�ǽ������ŵ�
	if(goinfo.stones[x][y].color!=0)
		return false;
	int othercolor=OTHER_COLOR(color);
	//�ж���յ����
	if(x-1>=0 && goinfo.stones[x-1][y].color==0
		|| x+1<=goinfo.boardsize-1 && goinfo.stones[x+1][y].color==0
		|| y-1>=0 && goinfo.stones[x][y-1].color==0
		|| y+1<=goinfo.boardsize-1 && goinfo.stones[x][y+1].color==0) return false;
	//�������ӵ����
	if((x==0 || goinfo.stones[x-1][y].color==othercolor)
		&& (x==goinfo.boardsize-1 || goinfo.stones[x+1][y].color==othercolor)
		&& (y==0 || goinfo.stones[x][y-1].color==othercolor)
		&& (y==goinfo.boardsize-1 || goinfo.stones[x][y+1].color==othercolor))
	{
		if(x>0 && goinfo.stones[x-1][y].color==othercolor && goinfo.strings[goinfo.stones[x-1][y].stringid].air==1
			|| x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==othercolor && goinfo.strings[goinfo.stones[x+1][y].stringid].air==1
			|| y>0 && goinfo.stones[x][y-1].color==othercolor && goinfo.strings[goinfo.stones[x][y-1].stringid].air==1
			|| y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==othercolor && goinfo.strings[goinfo.stones[x][y+1].stringid].air==1)
			return false;//�漰����������
		return true;
	}
	//�������
	if(x>0 && goinfo.stones[x-1][y].color==color)
	{
		if(goinfo.strings[goinfo.stones[x-1][y].stringid].air>1) return false;
	}
	if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==color)
	{
		if(goinfo.strings[goinfo.stones[x+1][y].stringid].air>1) return false;
	}
	if(y>0 && goinfo.stones[x][y-1].color==color)
	{
		if(goinfo.strings[goinfo.stones[x][y-1].stringid].air>1) return false;
	}
	if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==color)
	{
		if(goinfo.strings[goinfo.stones[x][y+1].stringid].air>1) return false;
	}
	if(x>0 && goinfo.stones[x-1][y].color==othercolor)
	{
		if(goinfo.strings[goinfo.stones[x-1][y].stringid].air==1) return false;
	}
	if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==othercolor)
	{
		if(goinfo.strings[goinfo.stones[x+1][y].stringid].air==1) return false;
	}
	if(y>0 && goinfo.stones[x][y-1].color==othercolor)
	{
		if(goinfo.strings[goinfo.stones[x][y-1].stringid].air==1) return false;
	}
	if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==othercolor)
	{
		if(goinfo.strings[goinfo.stones[x][y+1].stringid].air==1) return false;
	}
	return true;
}

//�жϽ�����
bool Sfc::IsKoPoint(int x, int y, int color, Data_GoInfo &goinfo)
{
	int othercolor=OTHER_COLOR(color);
	if((x==0 || goinfo.stones[x-1][y].color==othercolor) && (x==goinfo.boardsize-1 || goinfo.stones[x+1][y].color==othercolor) && (y==0 || goinfo.stones[x][y-1].color==othercolor) && (y==goinfo.boardsize-1 || goinfo.stones[x][y+1].color==othercolor))
	{
		if(x>0 && goinfo.stones[x-1][y].color==othercolor)
		{
			int stringid=goinfo.stones[x-1][y].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1)//����
					return true;
				return false;
			}
		}
		if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==othercolor)
		{
			int stringid=goinfo.stones[x+1][y].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1)//����
					return true;
				return false;
			}
		}
		if(y>0 && goinfo.stones[x][y-1].color==othercolor)
		{
			int stringid=goinfo.stones[x][y-1].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1)//����
					return true;
				return false;
			}
		}
		if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==othercolor)
		{
			int stringid=goinfo.stones[x][y+1].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==11)//����
					return true;
				return false;
			}
		}
		return false;
	}
	return false;
}

//�жϽ������ŵ�
bool Sfc::IsKoFobidenPoint(int x, int y, int color, Data_GoInfo &goinfo)
{
	int othercolor=OTHER_COLOR(color);
	if((x==0 || goinfo.stones[x-1][y].color==othercolor) && (x==goinfo.boardsize-1 || goinfo.stones[x+1][y].color==othercolor) && (y==0 || goinfo.stones[x][y-1].color==othercolor) && (y==goinfo.boardsize-1 || goinfo.stones[x][y+1].color==othercolor))
	{
		if(x>0 && goinfo.stones[x-1][y].color==othercolor)
		{
			int stringid=goinfo.stones[x-1][y].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1 && goinfo.laststone.x==x-1 && goinfo.laststone.y==y)//����
					return true;
				return false;
			}
		}
		if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==othercolor)
		{
			int stringid=goinfo.stones[x+1][y].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1 && goinfo.laststone.x==x+1 && goinfo.laststone.y==y)//����
					return true;
				return false;
			}
		}
		if(y>0 && goinfo.stones[x][y-1].color==othercolor)
		{
			int stringid=goinfo.stones[x][y-1].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1 && goinfo.laststone.x==x && goinfo.laststone.y==y-1)//����
					return true;
				return false;
			}
		}
		if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==othercolor)
		{
			int stringid=goinfo.stones[x][y+1].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1 && goinfo.laststone.x==x && goinfo.laststone.y==y+1)//����
					return true;
				return false;
			}
		}
		return false;
	}
	return false;
}

//�жϻ���
bool Sfc::IsTermsInside(int x, int y, int color, Data_GoInfo &goinfo)
{
	int othercolor=OTHER_COLOR(color);
	int air=0;
	if(x>0 && goinfo.stones[x-1][y].color==0)
		air++;
	if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==0)
		air++;
	if(y>0 && goinfo.stones[x][y-1].color==0)
		air++;
	if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==0)
		air++;
	//ֻ��һ��δ����Χʱ���ǻ���
	if(air!=1)
		return false;
	//�н�Ӧʱ�����㻢��
	if(x>0 && goinfo.stones[x-1][y].color==othercolor && goinfo.strings[goinfo.stones[x-1][y].stringid].air>=2
		|| x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==othercolor && goinfo.strings[goinfo.stones[x+1][y].stringid].air>=2
		|| y>0 && goinfo.stones[x][y-1].color==othercolor && goinfo.strings[goinfo.stones[x][y-1].stringid].air>=2
		|| y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==othercolor && goinfo.strings[goinfo.stones[x][y+1].stringid].air>=2)
		return false;
	return true;
}

//�жϵ�����
bool Sfc::IsTermInside(int x, int y, int color, Data_GoInfo &goinfo)
{
	int othercolor=OTHER_COLOR(color);
	int zcount=0;
	if(x==0 || goinfo.stones[x-1][y].color==color && goinfo.strings[goinfo.stones[x-1][y].stringid].air>1)
		zcount++;
	if(x==goinfo.boardsize-1 || goinfo.stones[x+1][y].color==color && goinfo.strings[goinfo.stones[x+1][y].stringid].air>1)
		zcount++;
	if(y==0 || goinfo.stones[x][y-1].color==color && goinfo.strings[goinfo.stones[x][y-1].stringid].air>1)
		zcount++;
	if(y==goinfo.boardsize-1 || goinfo.stones[x][y+1].color==color && goinfo.strings[goinfo.stones[x][y+1].stringid].air>1)
		zcount++;
	return zcount==3;
}

//�ж��˽ٵ㣨����������ԣ�
bool Sfc::IsPutKoPoint(int x, int y, int color, Data_GoInfo &goinfo)
{
	//�жϵ�����
	if(!IsTermInside(x,y,color,goinfo))
		return false;
	int othercolor=OTHER_COLOR(color);
	//�ж���Եĵ�����
	if(x>0 && goinfo.stones[x-1][y].color==0 && IsTermInside(x-1,y,othercolor,goinfo)
		|| x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==0 && IsTermInside(x+1,y,othercolor,goinfo)
		|| y>0 && goinfo.stones[x][y-1].color==0 && IsTermInside(x,y-1,othercolor,goinfo)
		|| y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==0 && IsTermInside(x,y+1,othercolor,goinfo))
		return true;
	return false;

}

//�ж����ۣ���Ŀ�ۣ�
bool Sfc::IsTrueEye1(int x, int y, int color, Data_GoInfo &goinfo)
{
	//�ж��Ƿ�Ŀ��
	if((x==0 || goinfo.stones[x-1][y].color==color)
		&& (x==goinfo.boardsize-1 || goinfo.stones[x+1][y].color==color)
		&& (y==0 || goinfo.stones[x][y-1].color==color)
		&& (y==goinfo.boardsize-1 || goinfo.stones[x][y+1].color==color))
	{
		int othercolor=OTHER_COLOR(color);
		//���ϵ��ۣ�ֻ��һ���������ռ�ݻ��ڱ���״̬�����ŵ�򻢿��ҷ��˽ٵ㣩
		if(x==0 && y==0)
			return goinfo.stones[x+1][y+1].color==color || IsNoKoFobidenPoint(x+1,y+1,othercolor,goinfo) || IsTermsInside(x+1,y+1,color,goinfo) && !IsPutKoPoint(x+1,y+1,color,goinfo);
		if(x==goinfo.boardsize-1 && y==0)
			return goinfo.stones[x-1][y+1].color==color || IsNoKoFobidenPoint(x-1,y+1,othercolor,goinfo) || IsTermsInside(x-1,y+1,color,goinfo) && !IsPutKoPoint(x-1,y+1,color,goinfo);
		if(x==0 && y==goinfo.boardsize-1)
			return goinfo.stones[x+1][y-1].color==color || IsNoKoFobidenPoint(x+1,y-1,othercolor,goinfo) || IsTermsInside(x+1,y-1,color,goinfo) && !IsPutKoPoint(x+1,y-1,color,goinfo);
		if(x==goinfo.boardsize-1 && y==goinfo.boardsize-1)
			return goinfo.stones[x-1][y-1].color==color || IsNoKoFobidenPoint(x-1,y-1,othercolor,goinfo) || IsTermsInside(x-1,y-1,color,goinfo) && !IsPutKoPoint(x-1,y-1,color,goinfo);
		//���ϵ��ۣ�������
		if(x==0)
		{
			return (goinfo.stones[x+1][y-1].color==color || IsNoKoFobidenPoint(x+1,y-1,othercolor,goinfo) || IsTermsInside(x+1,y-1,color,goinfo) && !IsPutKoPoint(x+1,y-1,color,goinfo))
				&& (goinfo.stones[x+1][y+1].color==color || IsNoKoFobidenPoint(x+1,y+1,othercolor,goinfo) || IsTermsInside(x+1,y+1,color,goinfo) && !IsPutKoPoint(x+1,y+1,color,goinfo));
		}
		if(x==goinfo.boardsize-1)
		{
			return (goinfo.stones[x-1][y-1].color==color || IsNoKoFobidenPoint(x-1,y-1,othercolor,goinfo) || IsTermsInside(x-1,y-1,color,goinfo) && !IsPutKoPoint(x-1,y-1,color,goinfo))
				&& (goinfo.stones[x-1][y+1].color==color || IsNoKoFobidenPoint(x-1,y+1,othercolor,goinfo) || IsTermsInside(x-1,y+1,color,goinfo) && !IsPutKoPoint(x-1,y+1,color,goinfo));
		}
		if(y==0)
		{
			return (goinfo.stones[x-1][y+1].color==color || IsNoKoFobidenPoint(x-1,y+1,othercolor,goinfo) || IsTermsInside(x-1,y+1,color,goinfo) && !IsPutKoPoint(x-1,y+1,color,goinfo))
				&& (goinfo.stones[x+1][y+1].color==color || IsNoKoFobidenPoint(x+1,y+1,othercolor,goinfo) || IsTermsInside(x+1,y+1,color,goinfo) && !IsPutKoPoint(x+1,y+1,color,goinfo));
		}
		if(y==goinfo.boardsize-1)
		{
			return (goinfo.stones[x-1][y-1].color==color || IsNoKoFobidenPoint(x-1,y-1,othercolor,goinfo) || IsTermsInside(x-1,y-1,color,goinfo) && !IsPutKoPoint(x-1,y-1,color,goinfo))
				&& (goinfo.stones[x+1][y-1].color==color || IsNoKoFobidenPoint(x+1,y-1,othercolor,goinfo) || IsTermsInside(x+1,y-1,color,goinfo) && !IsPutKoPoint(x+1,y-1,color,goinfo));
		}
		//�и����ۣ��ĸ�����ֻҪռ����������
		int jcount=0;
		if(goinfo.stones[x-1][y-1].color==color || IsNoKoFobidenPoint(x-1,y-1,othercolor,goinfo) || IsTermsInside(x-1,y-1,color,goinfo) && !IsPutKoPoint(x-1,y-1,color,goinfo))
			jcount++;
		if(goinfo.stones[x+1][y-1].color==color || IsNoKoFobidenPoint(x+1,y-1,othercolor,goinfo) || IsTermsInside(x+1,y-1,color,goinfo) && !IsPutKoPoint(x+1,y-1,color,goinfo))
			jcount++;
		if(goinfo.stones[x-1][y+1].color==color || IsNoKoFobidenPoint(x-1,y+1,othercolor,goinfo) || IsTermsInside(x-1,y+1,color,goinfo) && !IsPutKoPoint(x-1,y+1,color,goinfo))
			jcount++;
		if(goinfo.stones[x+1][y+1].color==color || IsNoKoFobidenPoint(x+1,y+1,othercolor,goinfo) || IsTermsInside(x+1,y+1,color,goinfo) && !IsPutKoPoint(x+1,y+1,color,goinfo))
			jcount++;
		return jcount>=3;
	}
	return false;
}

//�ж����֮�����ɢ����
bool Sfc::StringLinkToString(int stringid1,int stringid2, Data_GoInfo &goinfo)
{
	for(int i=0;i<goinfo.strings[stringid1].lkcount;i++)
	{
		if(goinfo.strings[stringid1].lkid[i]==stringid2) return true;
	}
	return false;
}

//�ж�������Ⱥ�Ƿ�����
bool Sfc::StringLinkToDragon(int stringid, int dragonid, Data_GoInfo &goinfo)
{
	if(goinfo.dragons[dragonid].kcount==1 && goinfo.dragons[dragonid].stringids[0]==stringid) return true;
	for(int i=0;i<goinfo.strings[stringid].lkcount;i++)
	{
		if(goinfo.strings[goinfo.strings[stringid].lkid[i]].dragonid==dragonid) return true;
	}
	return false;
}

//��������
void Sfc::CalStone(int x, int y, Data_GoInfo &goinfo)
{
	int color=1;
	goinfo.stones[x][y].x=x;
	goinfo.stones[x][y].y=y;
	goinfo.stones[x][y].color=color;
	if(x>0 && goinfo.stones[x-1][y].color==color) goinfo.stones[x][y].stringid=goinfo.stones[x-1][y].stringid;
	else if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==color) goinfo.stones[x][y].stringid=goinfo.stones[x+1][y].stringid;
	else if(y>0 && goinfo.stones[x][y-1].color==color) goinfo.stones[x][y].stringid=goinfo.stones[x][y-1].stringid;
	else if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==color) goinfo.stones[x][y].stringid=goinfo.stones[x][y+1].stringid;
	else
	{
		int stringid;
		for(stringid=0;stringid<100;stringid++)
		{
			if(goinfo.strings[stringid].color==0)
				break;
		}
		goinfo.stones[x][y].stringid=stringid;
		goinfo.strings[stringid].color=color;
		goinfo.strings[stringid].zcount=1;
		goinfo.strings[stringid].xs[0]=x;
		goinfo.strings[stringid].ys[0]=y;
		goinfo.strings[stringid].dragonid=-1;
		stringid++;
		bool linked=false;
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(i==1 && j==1) continue;
				if(goinfo.stones[x-1+i][y-1+j].color!=color) continue;
				if(goinfo.strings[goinfo.stones[x-1+i][y-1+j].stringid].dragonid==goinfo.strings[goinfo.stones[x][y].stringid].dragonid) continue;
				if(StoneLinkToStone(x,y,color,x-1+i,y-1+j,goinfo))
				{
					if(!linked)//����һ��Ⱥ
					{
						goinfo.strings[goinfo.stones[x][y].stringid].dragonid=goinfo.strings[goinfo.stones[x-1+i][y-1+j].stringid].dragonid;
						goinfo.dragons[goinfo.strings[goinfo.stones[x][y].stringid].dragonid].kcount++;
						goinfo.dragons[goinfo.strings[goinfo.stones[x][y].stringid].dragonid].stringids[goinfo.dragons[goinfo.strings[goinfo.stones[x][y].stringid].dragonid].kcount-1]=goinfo.stones[x][y].stringid;
					}
					else//���϶��Ⱥ
					{
						//Ǩ��Ⱥ
						//if(goinfo.strings[goinfo.stones[x][y].stringid].dragonid>
					}
				}
			}
		}
		for(int i=0;i<stringid;i++)
		{
			if(StoneLinkToString(x,y,color,i,goinfo))
			{
				goinfo.strings[goinfo.stones[x][y].stringid].dragonid=i;
				break;
			}
		}
		//if(i==stringid)
	}
}

//�������
void Sfc::CalString(int stringid, Data_GoInfo &goinfo)
{
	int x,y;
	goinfo.strings[stringid].lkcount=0;
	for(int i=0;i<goinfo.strings[stringid].zcount;i++)
	{
		x=goinfo.strings[stringid].xs[i];
		y=goinfo.strings[stringid].ys[i];
		CalStoneLink(x,y,goinfo);
		AddStoneLinkToString(x,y,stringid,goinfo);
	}
	GetStringAir(stringid,goinfo);
}

//���������Χ�㣨��һ����������������air��
void Sfc::CalStringAroundToAir(int stringid, Data_GoInfo &goinfo)
{
	int air=0;
	for(int i=0;i<goinfo.strings[stringid].zcount;i++)
	{
		int x=goinfo.strings[stringid].xs[i];
		int y=goinfo.strings[stringid].ys[i];
		if(x>0 && goinfo.stones[x-1][y].stringid!=stringid)
		{
			goinfo.strings[stringid].airxs[air]=x-1;
			goinfo.strings[stringid].airys[air]=y;
			air++;
		}
		if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].stringid!=stringid)
		{
			goinfo.strings[stringid].airxs[air]=x+1;
			goinfo.strings[stringid].airys[air]=y;
			air++;
		}
		if(y>0 && goinfo.stones[x][y-1].stringid!=stringid)
		{
			goinfo.strings[stringid].airxs[air]=x;
			goinfo.strings[stringid].airys[air]=y-1;
			air++;
		}
		if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].stringid!=stringid)
		{
			goinfo.strings[stringid].airxs[air]=x;
			goinfo.strings[stringid].airys[air]=y+1;
			air++;
		}
	}
	goinfo.strings[stringid].air=air;
}

//�������Ӻ��ܱ߼������ӵĹ�ϵ�����������򴴽���
void Sfc::CalStoneAround(int x, int y, int color, Data_GoInfo &goinfo)
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(i==1 && j==1) continue;
			if(x-1+i<0 || x-1+i>goinfo.boardsize-1 || y-1+j<0 || y-1+j>goinfo.boardsize-1) continue;
			if(x-1+i>0 && goinfo.stones[x-1+i-1][y-1+j].color==color) goinfo.stones[x-1+i][y].stringid=goinfo.stones[x-1+i-1][y].stringid;
			else if(x-1+i<goinfo.boardsize-1 && goinfo.stones[x-1+i+1][y].color==color) goinfo.stones[x-1+i][y].stringid=goinfo.stones[x-1+i+1][y].stringid;
			else if(y>0 && goinfo.stones[x-1+i][y-1].color==color) goinfo.stones[x-1+i][y].stringid=goinfo.stones[x][y-1].stringid;
			else if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==color) goinfo.stones[x][y].stringid=goinfo.stones[x][y+1].stringid;
			else CreateString(x,y,color,goinfo);
		}
	}
}

//����������ɢ���������������lzcount��lzxs��lzys
void Sfc::CalStoneLink(int x, int y, Data_GoInfo &goinfo)
{
	goinfo.stones[x][y].lzcount=0;
	for(int i=-2;i<3;i++)
	{
		if(x+i<0 || x+i>goinfo.boardsize-1) continue;
		for(int j=-2;j<3;j++)
		{
			if(y+j<0 || y+j>goinfo.boardsize-1) continue;
			if(i==-2 && j==-2 || i==2 && j==-2 || i==-2 && j==2 || i==2 && j==2 || i==-1 && j==0 || i==1 && j==0 || i==0 && j==-1 || i==0 && j==1) continue;
			if(StoneLinkToStone(x,y,goinfo.stones[x][y].color,x+i,y+j,goinfo))
			{
				goinfo.stones[x][y].lzxs[goinfo.stones[x][y].lzcount]=x+i;
				goinfo.stones[x][y].lzys[goinfo.stones[x][y].lzcount]=y+j;
				goinfo.stones[x][y].lzcount++;
			}
		}
	}
}

//�����Ƴ����Ӳ����ķֶ�
void Sfc::CalStoneRemoveDispart(int x,int y, Data_GoInfo &goinfo)
{
	int lkcount=0;
	int lkids[100];
	for(int i=0;i<goinfo.stones[x][y].lzcount;i++)
	{
		int j;
		int x0=goinfo.stones[x][y].lzxs[i];
		int y0=goinfo.stones[x][y].lzys[i];
		for(j=0;j<goinfo.stones[x0][y0].lzcount;j++)
		{
			if(goinfo.stones[x0][y0].lzxs[j]==x && goinfo.stones[x0][y0].lzys[j]==y)
			{
				for(int k=j;k<goinfo.stones[x0][y0].lzcount-1;k++)
				{
					goinfo.stones[x0][y0].lzxs[k]=goinfo.stones[x0][y0].lzxs[k+1];
					goinfo.stones[x0][y0].lzys[k]=goinfo.stones[x0][y0].lzys[k+1];
				}
				goinfo.stones[x0][y0].lzcount--;
				break;
			}
		}
		for(j=0;j<lkcount;j++)
		{
			if(lkids[j]==goinfo.stones[x0][y0].stringid) break;
		}
		if(j==lkcount)
		{
			lkids[j]=goinfo.stones[x0][y0].stringid;
			lkcount++;
		}
	}
	for(int i=0;i<lkcount;i++)
	{
		AddStoneDispartToString(x,y,lkids[i],goinfo);
	}
}

//�������ӷֶ����
void Sfc::CalStoneDispart(int x,int y, Data_GoInfo &goinfo)
{
	for(int i=0;i<goinfo.stones[x][y].lzcount;i++)
	{
		if(!StoneLinkToStone(x,y,goinfo.stones[x][y].color,goinfo.stones[x][y].lzxs[i],goinfo.stones[x][y].lzys[i],goinfo))
		{
			//ԭ����
			int x0=goinfo.stones[x][y].lzxs[i];
			int y0=goinfo.stones[x][y].lzys[i];
			for(int j=i;j<goinfo.stones[x][y].lzcount-1;j++)
			{
				goinfo.stones[x][y].lzxs[j]=goinfo.stones[x][y].lzxs[j+1];
				goinfo.stones[x][y].lzys[j]=goinfo.stones[x][y].lzys[j+1];
			}
			goinfo.stones[x][y].lzcount--;
			int k;
			for(k=0;k<goinfo.stones[x][y].lzcount;k++)
			{
				if(goinfo.stones[goinfo.stones[x][y].lzxs[k]][goinfo.stones[x][y].lzys[k]].stringid==goinfo.stones[x0][y0].stringid) break;
			}
			if(k==goinfo.stones[x][y].lzcount) AddStoneDispartToString(x0,y0,goinfo.stones[x][y].stringid,goinfo);
			//���ֶ�����
			for(int j=0;j<goinfo.stones[x0][y0].lzcount;j++)
			{
				if(goinfo.stones[x0][y0].lzxs[j]==x && goinfo.stones[x0][y0].lzys[j]==y)
				{
					for(k=j;k<goinfo.stones[x0][y0].lzcount-1;k++)
					{
						goinfo.stones[x0][y0].lzxs[k]=goinfo.stones[x0][y0].lzxs[k+1];
						goinfo.stones[x0][y0].lzys[k]=goinfo.stones[x0][y0].lzys[k+1];
					}
					goinfo.stones[x0][y0].lzcount--;
					for(k=0;k<goinfo.stones[x0][y0].lzcount;k++)
					{
						if(goinfo.stones[goinfo.stones[x0][y0].lzxs[k]][goinfo.stones[x0][y0].lzys[k]].stringid==goinfo.stones[x][y].stringid) break;
					}
					if(k==goinfo.stones[x0][y0].lzcount) AddStoneDispartToString(x,y,goinfo.stones[x0][y0].stringid,goinfo);
					break;
				}
			}
			/*//��Ⱥ�仯
			if(mQk[goinfo.stones[x][y].stringid].qqid==mQk[goinfo.stones[x0][y0].stringid].qqid && !QkIndirectLinkToQk(goinfo.stones[x][y].stringid,goinfo.stones[x0][y0].stringid))//��Ⱥ���ֶ�
			{
			DispartQq(goinfo.stones[x][y].stringid);
			}
			*/
			break;
		}
	}
}

//������Χ�Է����ӱ��ֶ����
void Sfc::CalStoneAroundDispart(int x,int y, Data_GoInfo &goinfo)
{
	int stringcount=0;
	int stringids[8];
	for(int i=-1;i<2;i++)
	{
		for(int j=-1;j<2;j++)
		{
			if(i==0 && j==0) continue;
			if(x+i<0 || x+i>goinfo.boardsize-1 || y+j<0 || y+j>goinfo.boardsize-1) continue;
			if(goinfo.stones[x+i][y+j].color==OTHER_COLOR(goinfo.stones[x][y].color))
			{
				CalStoneDispart(x+i,y+j,goinfo);
				int k;
				for(k=0;k<stringcount;k++)
				{
					if(goinfo.stones[x+i][y+j].stringid==stringids[k]) break;
				}
				if(k==stringcount)
				{
					stringids[k]=goinfo.stones[x+i][y+j].stringid;
					stringcount++;
				}
			}
		}
	}
	//��Ⱥ�仯
	for(int i=0;i<stringcount;i++)
	{
		if(!StringLinkToDragon(stringids[i],goinfo.strings[stringids[i]].dragonid,goinfo))
		{
			DispartDragon(stringids[i],goinfo);
		}
	}
}

//����������Χ�Է���������仯
void Sfc::CalStoneAroundAir(int x, int y, Data_GoInfo &goinfo)
{
	int qkcount=0;
	int stringids[4]={0,0,0,0};
	for(int i=-1;i<2;i++)
	{
		for(int j=-1;j<2;j++)
		{
			if(i==j || i-j==2 || j-i==2) continue;
			if(x+i<0 || x+i>goinfo.boardsize-1 || y+j<0 || y+j>goinfo.boardsize-1) continue;
			if(goinfo.stones[x+i][y+j].color==OTHER_COLOR(goinfo.stones[x][y].color))
			{
				int k;
				for(k=0;k<qkcount;k++)
				{
					if(goinfo.stones[x+i][y+j].stringid==stringids[k]) break;
				}
				if(k==qkcount)
				{
					for(int l=0;l<goinfo.strings[goinfo.stones[x+i][y+j].stringid].air;l++)
					{
						if(goinfo.strings[goinfo.stones[x+i][y+j].stringid].airxs[l]==x && goinfo.strings[goinfo.stones[x+i][y+j].stringid].airys[l]==y)
						{
							for(int m=l;m<goinfo.strings[goinfo.stones[x+i][y+j].stringid].air-1;m++)
							{
								goinfo.strings[goinfo.stones[x+i][y+j].stringid].airxs[m]=goinfo.strings[goinfo.stones[x+i][y+j].stringid].airxs[m+1];
								goinfo.strings[goinfo.stones[x+i][y+j].stringid].airys[m]=goinfo.strings[goinfo.stones[x+i][y+j].stringid].airys[m+1];
							}
							break;
						}
					}
					goinfo.strings[goinfo.stones[x+i][y+j].stringid].air--;
					stringids[k]=goinfo.stones[x+i][y+j].stringid;
					qkcount++;
				}
			}
		}
	}
	//������Ⱥ
	for(int i=0;i<qkcount;i++)
	{
		CalStringToDragon(stringids[i],goinfo);
	}
}

//�ݹ��ж�����������
bool Sfc::StringILToString(int stringid1,int stringid2, int &ilcount, int ils[180], Data_GoInfo &goinfo)
{
	for(int i=0;i<goinfo.strings[stringid1].lkcount;i++)
	{
		if(goinfo.strings[stringid1].lkid[i]==stringid2) return true;
	}
	ils[ilcount]=stringid1;
	ilcount++;
	for(int i=0;i<goinfo.strings[stringid1].lkcount;i++)
	{
		int j;
		for(j=0;j<ilcount;j++)
		{
			if(goinfo.strings[stringid1].lkid[i]==ils[j]) break;
		}
		if(j==ilcount) return StringILToString(goinfo.strings[stringid1].lkid[i],stringid2,ilcount,ils,goinfo);
	}
	return false;
}

//�ж�����������
bool Sfc::StringIndirectLinkToString(int stringid1,int stringid2, Data_GoInfo &goinfo)
{
	int ilcount=0,ils[180];
	return StringILToString(stringid1,stringid2,ilcount,ils,goinfo);
	/*for(int i=0;i<goinfo.strings[stringid1].lkcount;i++)
	{
		if(goinfo.strings[stringid1].lkid[i]==stringid2) return true;
	}
	for(int i=0;i<goinfo.strings[stringid1].lkcount;i++)
	{
		if(StringIndirectLinkToString(stringid1, goinfo.strings[stringid1].lkid[i], stringid2,goinfo))
			return true;
	}
	return false;*/
}

//���������ӷֶ�����������
void Sfc::AddStoneDispartToString(int x/*���ֶ�����x����*/,int y/*���ֶ�����y����*/,int stringid, Data_GoInfo &goinfo)
{
	for(int i=0;i<goinfo.strings[stringid].zcount;i++)
	{
		for(int j=0;j<goinfo.stones[goinfo.strings[stringid].xs[i]][goinfo.strings[stringid].ys[i]].lzcount;j++)
		{
			int x0=goinfo.stones[goinfo.strings[stringid].xs[i]][goinfo.strings[stringid].ys[i]].lzxs[j];
			int y0=goinfo.stones[goinfo.strings[stringid].xs[i]][goinfo.strings[stringid].ys[i]].lzys[j];
			if(goinfo.stones[x][y].stringid==goinfo.stones[x0][y0].stringid) return;
		}
	}
	for(int i=0;i<goinfo.strings[stringid].lkcount;i++)
	{
		if(goinfo.strings[stringid].lkid[i]==goinfo.stones[x][y].stringid)
		{
			for(int j=i;j<goinfo.strings[stringid].lkcount-1;j++)
			{
				goinfo.strings[stringid].lkid[j]=goinfo.strings[stringid].lkid[j+1];
			}
			goinfo.strings[stringid].lkcount--;
			break;
		}
	}
}

//Ϊ�������ӵ���Χ���Ӽ�������
void Sfc::AddStoneRoundLink(int x,int y, Data_GoInfo &goinfo)
{
	int x1,y1;
	for(int i=0;i<goinfo.stones[x][y].lzcount;i++)
	{
		//���ӵ�����
		x1=goinfo.stones[x][y].lzxs[i];y1=goinfo.stones[x][y].lzys[i];
		goinfo.stones[x1][y1].lzxs[goinfo.stones[x1][y1].lzcount]=x;
		goinfo.stones[x1][y1].lzys[goinfo.stones[x1][y1].lzcount]=y;
		goinfo.stones[x1][y1].lzcount++;
		//��������
		AddStoneLinkToString(x1,y1,goinfo.stones[x1][y1].stringid,goinfo);
	}
}

//�������������Ӽ������
void Sfc::AddStoneLinkToString(int x,int y,int stringid, Data_GoInfo &goinfo)
{
	int i,j,k;
	i=stringid;
	for(j=0;j<goinfo.stones[x][y].lzcount;j++)
	{
		//���������ӵ�����������
		if(goinfo.stones[goinfo.stones[x][y].lzxs[j]][goinfo.stones[x][y].lzys[j]].stringid==stringid)
			continue;
		for(k=0;k<goinfo.strings[i].lkcount;k++)
		{
			if(goinfo.strings[i].lkid[k]==goinfo.stones[goinfo.stones[x][y].lzxs[j]][goinfo.stones[x][y].lzys[j]].stringid) break;
		}
		if(k>=goinfo.strings[i].lkcount)
		{
			goinfo.strings[i].lkid[k]=goinfo.stones[goinfo.stones[x][y].lzxs[j]][goinfo.stones[x][y].lzys[j]].stringid;
			goinfo.strings[i].lkcount++;
		}
	}
}

//�ϲ��������
void Sfc::CombStringLink(int stringid1,int stringid2, Data_GoInfo &goinfo)
{
	int i,j;
	//�ų���ǰ��string2������
	for(i=0;i<goinfo.strings[stringid1].lkcount;i++)
	{
		if(goinfo.strings[stringid1].lkid[i]==stringid2)
		{
			for(j=i;j<goinfo.strings[stringid1].lkcount-1;j++)
			{
				goinfo.strings[stringid1].lkid[j]=goinfo.strings[stringid1].lkid[j+1];
			}
			goinfo.strings[stringid1].lkcount--;
		}
	}
	int k=goinfo.strings[stringid1].lkcount;
	for(i=0;i<goinfo.strings[stringid2].lkcount;i++)
	{
		if(goinfo.strings[stringid2].lkid[i]==stringid1) continue;
		//������ӵ�stringid1
		for(j=0;j<k;j++)
		{
			if(goinfo.strings[stringid2].lkid[i]==goinfo.strings[stringid1].lkid[j]) break;
		}
		if(j==k)
		{
			goinfo.strings[stringid1].lkid[goinfo.strings[stringid1].lkcount]=goinfo.strings[stringid2].lkid[i];
			goinfo.strings[stringid1].lkcount++;
		}
		//�Ƴ���������к�stringid2������
		int stringid=goinfo.strings[stringid2].lkid[i];
		for(j=0;j<goinfo.strings[stringid].lkcount;j++)
		{
			if(goinfo.strings[stringid].lkid[j]==stringid2)
			{
				for(int l=j;l<goinfo.strings[stringid].lkcount-1;l++)
				{
					goinfo.strings[stringid].lkid[l]=goinfo.strings[stringid].lkid[l+1];
				}
				goinfo.strings[stringid].lkcount--;
				break;
			}
		}
	}
	//�Ƴ���������������������ӵ�����
	for(i=0;i<goinfo.strings[stringid1].zcount;i++)
	{
		int x=goinfo.strings[stringid1].xs[i];
		int y=goinfo.strings[stringid1].ys[i];
		for(j=0;j<goinfo.stones[x][y].lzcount;j++)
		{
			if(goinfo.stones[goinfo.stones[x][y].lzxs[j]][goinfo.stones[x][y].lzys[j]].stringid==stringid1)
			{
				for(k=j;k<goinfo.stones[x][y].lzcount-1;k++)
				{
					goinfo.stones[x][y].lzxs[k]=goinfo.stones[x][y].lzxs[k+1];
					goinfo.stones[x][y].lzys[k]=goinfo.stones[x][y].lzys[k+1];
				}
				goinfo.stones[x][y].lzcount--;
				j--;
			}
		}
	}
}

//������鴴����Ⱥ
void Sfc::CreateDragon(int stringid, Data_GoInfo &goinfo)
{
	int i;
	for(i=0;i<100;i++)
	{
		if(goinfo.dragons[i].color==0) break;
	}
	goinfo.strings[stringid].dragonid=i;
	goinfo.dragons[i].color=goinfo.strings[stringid].color;
	goinfo.dragons[i].kcount=1;
	goinfo.dragons[i].stringids[0]=stringid;
	goinfo.dragons[i].air=goinfo.strings[stringid].air;
	goinfo.dragons[i].alive=true;
	goinfo.dragoncount++;
}

//�ϲ���Ⱥ,ԭ�����Ǵ�ĺϲ�С�ģ����غϲ������Ⱥid
int Sfc::CombDragon(int dragonid1, int dragonid2, Data_GoInfo &goinfo)
{
	//id��ͬ��Ϊ��ͬ��ɫʱ���ϲ�ʧ��
	if(dragonid1==dragonid2 || goinfo.dragons[dragonid1].color!=goinfo.dragons[dragonid2].color) return -1;
	//Ѱ�Ҵ����Ⱥ
	if(goinfo.dragons[dragonid1].kcount<goinfo.dragons[dragonid2].kcount)
	{
		int dragonid=dragonid1;
		dragonid1=dragonid2;
		dragonid2=dragonid;
	}
	//���������������id
	memcpy_s(goinfo.dragons[dragonid1].stringids+goinfo.dragons[dragonid1].kcount,goinfo.dragons[dragonid2].kcount*sizeof(int),goinfo.dragons[dragonid2].stringids,goinfo.dragons[dragonid2].kcount*sizeof(int));
	//Array.Copy(goinfo.dragons[dragonid2].stringids,0,goinfo.dragons[dragonid1].stringids,goinfo.dragons[dragonid1].kcount,goinfo.dragons[dragonid2].kcount);
	goinfo.dragons[dragonid1].kcount+=goinfo.dragons[dragonid2].kcount;
	//����������鼰���ӵ���Ⱥid
	for(int i=0;i<goinfo.dragons[dragonid2].kcount;i++)
	{
		int stringid=goinfo.dragons[dragonid2].stringids[i];
		goinfo.strings[stringid].dragonid=dragonid1;
		for(int j=0;j<goinfo.strings[stringid].zcount;j++)
		{
			goinfo.stones[goinfo.strings[stringid].xs[j]][goinfo.strings[stringid].ys[j]].dragonid=dragonid1;
		}
	}
	//�ϲ���������
	goinfo.dragons[dragonid1].air+=goinfo.dragons[dragonid2].air;
	goinfo.dragons[dragonid1].eye+=goinfo.dragons[dragonid2].eye;
	memcpy_s(goinfo.dragons[dragonid1].yxids+goinfo.dragons[dragonid1].yxcount,goinfo.dragons[dragonid2].yxcount*sizeof(int),goinfo.dragons[dragonid2].yxids,goinfo.dragons[dragonid2].yxcount*sizeof(int));
	//Array.Copy(goinfo.dragons[dragonid2].yxids,0,goinfo.dragons[dragonid1].yxids,goinfo.dragons[dragonid1].yxcount,goinfo.dragons[dragonid2].yxcount);
	goinfo.dragons[dragonid1].yxcount+=goinfo.dragons[dragonid2].yxcount;
	goinfo.dragons[dragonid1].alive|=goinfo.dragons[dragonid2].alive;
	goinfo.dragons[dragonid2].color=0;
	goinfo.dragoncount--;
	return dragonid1;
}

//�ֶ�ȺΪ�������Ͳ���������Ⱥ
void Sfc::DispartDragon(int stringid, Data_GoInfo &goinfo)
{
	int dragonid0=goinfo.strings[stringid].dragonid;
	if(goinfo.dragons[dragonid0].kcount==1) return;
	CreateDragon(stringid,goinfo);
	int dragonid=goinfo.strings[stringid].dragonid;
	for(int i=0;i<goinfo.dragons[dragonid0].kcount;i++)
	{
		if(goinfo.dragons[dragonid0].stringids[i]==stringid)
		{
			goinfo.dragons[dragonid0].stringids[i]=-1;
			continue;
		}
		if(StringIndirectLinkToString(stringid,goinfo.dragons[dragonid0].stringids[i],goinfo))
		{
			goinfo.dragons[dragonid].stringids[goinfo.dragons[dragonid].kcount]=goinfo.dragons[dragonid0].stringids[i];
			goinfo.dragons[dragonid].kcount++;
			goinfo.strings[goinfo.dragons[dragonid0].stringids[i]].dragonid=dragonid;
			goinfo.dragons[dragonid0].stringids[i]=-1;
		}
	}
	int k=0;
	for(int i=0;i<goinfo.dragons[dragonid0].kcount;i++)
	{
		if(goinfo.dragons[dragonid0].stringids[i]==-1) continue;
		if(i>k) goinfo.dragons[dragonid0].stringids[k]=goinfo.dragons[dragonid0].stringids[i];
		k++;
	}
	goinfo.dragons[dragonid0].kcount=k;
}

//�����¿�
void Sfc::CreateString(int x,int y,int color, Data_GoInfo &goinfo)
{
	int i;
	for(i=0;i<180;i++)
	{
		if(goinfo.strings[i].color==0) break;
	}
	goinfo.stones[x][y].stringid=i;
	goinfo.strings[i].color=color;
	goinfo.strings[i].zcount=1;
	goinfo.strings[i].xs[0]=x;
	goinfo.strings[i].ys[0]=y;
	goinfo.strings[i].lkcount=0;
	CalStoneLink(x,y,goinfo);
	AddStoneLinkToString(x,y,i,goinfo);
	AddStoneRoundLink(x,y,goinfo);
	GetStringAir(i,goinfo);
	goinfo.strings[i].dragonid=-1;
	if(goinfo.strings[i].lkcount>0)
	{
		AddStringToDragon(i,goinfo.strings[goinfo.strings[i].lkid[0]].dragonid,goinfo);
		for(int j=1;j<goinfo.strings[i].lkcount;j++) CombDragon(goinfo.strings[i].dragonid,goinfo.strings[goinfo.strings[i].lkid[j]].dragonid,goinfo);
	}
	else CreateDragon(i,goinfo);
}

//�ϲ����
void Sfc::CombString(int stringid1,int stringid2, Data_GoInfo &goinfo)
{
	if(stringid1==stringid2 || goinfo.strings[stringid1].color!=goinfo.strings[stringid2].color) return;
	//ѡ�������
	if(goinfo.strings[stringid1].zcount<goinfo.strings[stringid2].zcount)
	{
		int stringid=stringid1;
		stringid1=stringid2;
		stringid2=stringid;
	}
	//�ı�����������
	for(int i=0;i<goinfo.strings[stringid2].zcount;i++) goinfo.stones[goinfo.strings[stringid2].xs[i]][goinfo.strings[stringid2].ys[i]].stringid=stringid1;
	//������������
	memcpy_s(goinfo.strings[stringid1].xs+goinfo.strings[stringid1].zcount,goinfo.strings[stringid2].zcount*sizeof(int),goinfo.strings[stringid2].xs,goinfo.strings[stringid2].zcount*sizeof(int));
	memcpy_s(goinfo.strings[stringid1].ys+goinfo.strings[stringid1].zcount,goinfo.strings[stringid2].zcount*sizeof(int),goinfo.strings[stringid2].ys,goinfo.strings[stringid2].zcount*sizeof(int));
	//������������
	goinfo.strings[stringid1].zcount+=goinfo.strings[stringid2].zcount;
	//�ϲ��������
	CombStringLink(stringid1,stringid2,goinfo);
	//ɾ�����2������ɫ��Ϊ0��
	goinfo.strings[stringid2].color=0;
	//goinfo.stringsCount--;
	//�����������
	GetStringAir(stringid1,goinfo);
	//����Ⱥ�仯
	int dragonid=goinfo.strings[stringid2].dragonid;
	for(int i=0;i<goinfo.dragons[dragonid].kcount;i++)
	{
		if(goinfo.dragons[dragonid].stringids[i]==stringid2)
		{
			for(int j=i;j<goinfo.dragons[dragonid].kcount-1;j++)
			{
				goinfo.dragons[dragonid].stringids[j]=goinfo.dragons[dragonid].stringids[j+1];
			}
			goinfo.dragons[dragonid].kcount--;
			break;
		}
	}
	if(goinfo.strings[stringid1].dragonid!=dragonid)
	{
		if(goinfo.dragons[dragonid].kcount>0) CombDragon(goinfo.strings[stringid1].dragonid,dragonid,goinfo);
		else
		{
			goinfo.dragons[goinfo.strings[stringid1].dragonid].air+=goinfo.dragons[dragonid].air;
			goinfo.dragons[dragonid].color=0;
			goinfo.dragoncount--;
		}
	}
}

//����������
int Sfc::GetStringAir(int stringid, Data_GoInfo &goinfo)
{
	int air=0;
	for(int i=0;i<goinfo.strings[stringid].zcount;i++)
	{
		if(goinfo.strings[stringid].xs[i]>0)
		{
			if(goinfo.stones[goinfo.strings[stringid].xs[i]-1][goinfo.strings[stringid].ys[i]].color==0)
			{
				int j=0;
				for(j=0;j<air;j++)
				{
					if(goinfo.strings[stringid].airxs[j]==goinfo.strings[stringid].xs[i]-1 && goinfo.strings[stringid].airys[j]==goinfo.strings[stringid].ys[i]) break;
				}
				if(j==air)
				{
					air++;
					goinfo.strings[stringid].airxs[j]=goinfo.strings[stringid].xs[i]-1;
					goinfo.strings[stringid].airys[j]=goinfo.strings[stringid].ys[i];
				}
			}
		}
		if(goinfo.strings[stringid].xs[i]<goinfo.boardsize-1)
		{
			if(goinfo.stones[goinfo.strings[stringid].xs[i]+1][goinfo.strings[stringid].ys[i]].color==0)
			{
				int j=0;
				for(j=0;j<air;j++)
				{
					if(goinfo.strings[stringid].airxs[j]==goinfo.strings[stringid].xs[i]+1 && goinfo.strings[stringid].airys[j]==goinfo.strings[stringid].ys[i]) break;
				}
				if(j==air)
				{
					air++;
					goinfo.strings[stringid].airxs[j]=goinfo.strings[stringid].xs[i]+1;
					goinfo.strings[stringid].airys[j]=goinfo.strings[stringid].ys[i];
				}
			}
		}
		if(goinfo.strings[stringid].ys[i]>0)
		{
			if(goinfo.stones[goinfo.strings[stringid].xs[i]][goinfo.strings[stringid].ys[i]-1].color==0)
			{
				int j=0;
				for(j=0;j<air;j++)
				{
					if(goinfo.strings[stringid].airxs[j]==goinfo.strings[stringid].xs[i] && goinfo.strings[stringid].airys[j]==goinfo.strings[stringid].ys[i]-1) break;
				}
				if(j==air)
				{
					air++;
					goinfo.strings[stringid].airxs[j]=goinfo.strings[stringid].xs[i];
					goinfo.strings[stringid].airys[j]=goinfo.strings[stringid].ys[i]-1;
				}
			}
		}
		if(goinfo.strings[stringid].ys[i]<goinfo.boardsize-1)
		{
			if(goinfo.stones[goinfo.strings[stringid].xs[i]][goinfo.strings[stringid].ys[i]+1].color==0)
			{
				int j=0;
				for(j=0;j<air;j++)
				{
					if(goinfo.strings[stringid].airxs[j]==goinfo.strings[stringid].xs[i] && goinfo.strings[stringid].airys[j]==goinfo.strings[stringid].ys[i]+1) break;
				}
				if(j==air)
				{
					air++;
					goinfo.strings[stringid].airxs[j]=goinfo.strings[stringid].xs[i];
					goinfo.strings[stringid].airys[j]=goinfo.strings[stringid].ys[i]+1;
				}
			}
		}
	}
	goinfo.strings[stringid].air=air;
	return air;
}

//��������ӵ����
void Sfc::AddStoneToString(int x,int y,int stringid, Data_GoInfo &goinfo)
{
	goinfo.stones[x][y].stringid=stringid;
	goinfo.strings[stringid].xs[goinfo.strings[stringid].zcount]=x;
	goinfo.strings[stringid].ys[goinfo.strings[stringid].zcount]=y;
	goinfo.strings[stringid].zcount++;
	//������ɢ�������
	CalStoneLink(x,y,goinfo);
	AddStoneRoundLink(x,y,goinfo);
	int lkcount=goinfo.strings[stringid].lkcount;
	AddStoneLinkToString(x,y,stringid,goinfo);
	//���������仯
	for(int i=0;i<goinfo.strings[stringid].air;i++)
	{
		if(goinfo.strings[stringid].airxs[i]==x && goinfo.strings[stringid].airys[i]==y)
		{
			for(int j=i;j<goinfo.strings[stringid].air-1;j++)
			{
				goinfo.strings[stringid].airxs[j]=goinfo.strings[stringid].airxs[j+1];
				goinfo.strings[stringid].airys[j]=goinfo.strings[stringid].airys[j+1];
			}
			goinfo.strings[stringid].air--;
			break;
		}
	}
	if(x>0 && goinfo.stones[x-1][y].color==0)
	{
		int i;
		for(i=0;i<goinfo.strings[stringid].air;i++)
		{
			if(goinfo.strings[stringid].airxs[i]==x-1 && goinfo.strings[stringid].airys[i]==y) break;
		}
		if(i==goinfo.strings[stringid].air)
		{
			goinfo.strings[stringid].airxs[i]=x-1;
			goinfo.strings[stringid].airys[i]=y;
			goinfo.strings[stringid].air++;
		}
	}
	if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==0)
	{
		int i;
		for(i=0;i<goinfo.strings[stringid].air;i++)
		{
			if(goinfo.strings[stringid].airxs[i]==x+1 && goinfo.strings[stringid].airys[i]==y) break;
		}
		if(i==goinfo.strings[stringid].air)
		{
			goinfo.strings[stringid].airxs[i]=x+1;
			goinfo.strings[stringid].airys[i]=y;
			goinfo.strings[stringid].air++;
		}
	}
	if(y>0 && goinfo.stones[x][y-1].color==0)
	{
		int i;
		for(i=0;i<goinfo.strings[stringid].air;i++)
		{
			if(goinfo.strings[stringid].airxs[i]==x && goinfo.strings[stringid].airys[i]==y-1) break;
		}
		if(i==goinfo.strings[stringid].air)
		{
			goinfo.strings[stringid].airxs[i]=x;
			goinfo.strings[stringid].airys[i]=y-1;
			goinfo.strings[stringid].air++;
		}
	}
	if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==0)
	{
		int i;
		for(i=0;i<goinfo.strings[stringid].air;i++)
		{
			if(goinfo.strings[stringid].airxs[i]==x && goinfo.strings[stringid].airys[i]==y+1) break;
		}
		if(i==goinfo.strings[stringid].air)
		{
			goinfo.strings[stringid].airxs[i]=x;
			goinfo.strings[stringid].airys[i]=y+1;
			goinfo.strings[stringid].air++;
		}
	}
	//������Ⱥ�仯
	for(int i=lkcount;i<goinfo.strings[stringid].lkcount;i++)
	{
		if(goinfo.strings[goinfo.strings[stringid].lkid[i]].dragonid!=goinfo.strings[stringid].dragonid)
		{
			CombDragon(goinfo.strings[stringid].dragonid,goinfo.strings[goinfo.strings[stringid].lkid[i]].dragonid,goinfo);
		}
	}
}

//�������ӵ���Ⱥ
void Sfc::AddStringToDragon(int stringid,int dragonid, Data_GoInfo &goinfo)
{
	goinfo.strings[stringid].dragonid=dragonid;
	goinfo.dragons[dragonid].stringids[goinfo.dragons[dragonid].kcount]=stringid;
	goinfo.dragons[dragonid].kcount++;
	//mQq[qqid].air+=mQk[qkid].air;
}

//�������Ƴ����
void Sfc::RemoveStoneFromString(int x,int y,int stringid, Data_GoInfo &goinfo)
{
	RemoveStringFromDragon(stringid,goinfo.strings[stringid].dragonid,goinfo);
	for(int i=0;i<goinfo.strings[stringid].zcount;i++)
	{
		goinfo.stones[goinfo.strings[stringid].xs[i]][goinfo.strings[stringid].ys[i]].stringid=-1;
	}
	//stringcount--;
	int color=goinfo.stones[x][y].color;
	goinfo.stones[x][y].color=0;
	goinfo.stones[x][y].lzcount=0;
	goinfo.strings[stringid].color=0;
	if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==color && goinfo.stones[x+1][y].stringid==-1)
	{
		int j;
		for(j=0;j<180;j++)
		{
			if(goinfo.strings[j].color==0) break;
		}
		goinfo.stones[x+1][y].stringid=j;
		goinfo.strings[j].color=color;
		goinfo.strings[j].zcount=1;
		goinfo.strings[j].xs[0]=x+1;
		goinfo.strings[j].ys[0]=y;
		//goinfo.stringsCount++;
		CalStoneToString(x+1,y,goinfo);
	}
	if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==color && goinfo.stones[x][y+1].stringid==-1)
	{
		int j;
		for(j=0;j<180;j++)
		{
			if(goinfo.strings[j].color==0) break;
		}
		goinfo.stones[x][y+1].stringid=j;
		goinfo.strings[j].color=color;
		goinfo.strings[j].zcount=1;
		goinfo.strings[j].xs[0]=x;
		goinfo.strings[j].ys[0]=y+1;
		//goinfo.stringsCount++;
		CalStoneToString(x,y+1,goinfo);
	}
	if(x>0 && goinfo.stones[x-1][y].color==color && goinfo.stones[x-1][y].stringid==-1)
	{
		int j;
		for(j=0;j<180;j++)
		{
			if(goinfo.strings[j].color==0) break;
		}
		goinfo.stones[x-1][y].stringid=j;
		goinfo.strings[j].color=color;
		goinfo.strings[j].zcount=1;
		goinfo.strings[j].xs[0]=x-1;
		goinfo.strings[j].ys[0]=y;
		//goinfo.stringsCount++;
		CalStoneToString(x-1,y,goinfo);
	}
	if(y>0 && goinfo.stones[x][y-1].color==color && goinfo.stones[x][y-1].stringid==-1)
	{
		int j;
		for(j=0;j<180;j++)
		{
			if(goinfo.strings[j].color==0) break;
		}
		goinfo.stones[x][y-1].stringid=j;
		goinfo.strings[j].color=color;
		goinfo.strings[j].zcount=1;
		goinfo.strings[j].xs[0]=x;
		goinfo.strings[j].ys[0]=y-1;
		//goinfo.stringsCount++;
		CalStoneToString(x,y-1,goinfo);
	}
}

//���ݸ��������ӵݹ�������
int Sfc::CalStoneToString(int x,int y, Data_GoInfo &goinfo)
{
	int stringid=goinfo.stones[x][y].stringid;
	int color=goinfo.stones[x][y].color;
	if(stringid==-1)
	{
		CreateString(x,y,color,goinfo);
		stringid=goinfo.stones[x][y].stringid;
	}
	if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==color && goinfo.stones[x+1][y].stringid==-1)
	{
		goinfo.stones[x+1][y].stringid=stringid;
		goinfo.strings[stringid].xs[goinfo.strings[stringid].zcount]=x+1;
		goinfo.strings[stringid].ys[goinfo.strings[stringid].zcount]=y;
		goinfo.strings[stringid].zcount++;
		CalStoneToString(x+1,y,goinfo);
	}
	if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==color && goinfo.stones[x][y+1].stringid==-1)
	{
		goinfo.stones[x][y+1].stringid=stringid;
		goinfo.strings[stringid].xs[goinfo.strings[stringid].zcount]=x;
		goinfo.strings[stringid].ys[goinfo.strings[stringid].zcount]=y+1;
		goinfo.strings[stringid].zcount++;
		CalStoneToString(x,y+1,goinfo);
	}
	if(x>0 && goinfo.stones[x-1][y].color==color && goinfo.stones[x-1][y].stringid==-1)
	{
		goinfo.stones[x-1][y].stringid=stringid;
		goinfo.strings[stringid].xs[goinfo.strings[stringid].zcount]=x-1;
		goinfo.strings[stringid].ys[goinfo.strings[stringid].zcount]=y;
		goinfo.strings[stringid].zcount++;
		CalStoneToString(x-1,y,goinfo);
	}
	if(y>0 && goinfo.stones[x][y-1].color==color && goinfo.stones[x][y-1].stringid==-1)
	{
		goinfo.stones[x][y-1].stringid=stringid;
		goinfo.strings[stringid].xs[goinfo.strings[stringid].zcount]=x;
		goinfo.strings[stringid].ys[goinfo.strings[stringid].zcount]=y-1;
		goinfo.strings[stringid].zcount++;
		CalStoneToString(x,y-1,goinfo);
	}
	//CalQkAir(stringid);
	return stringid;
}

//���ݸ�������������Ⱥ
int Sfc::CalStringToDragon(int stringid, Data_GoInfo &goinfo)
{
	int dragonid=goinfo.strings[stringid].dragonid;
	for(int i=0;i<goinfo.strings[stringid].lkcount;i++)
	{
		if(goinfo.strings[goinfo.strings[stringid].lkid[i]].dragonid!=dragonid)
		{
			if(dragonid==-1)//���ϵ���Ⱥ
			{
				dragonid=goinfo.strings[goinfo.strings[stringid].lkid[i]].dragonid;
				AddStringToDragon(stringid,dragonid,goinfo);
			}
			else
			{
				if(goinfo.strings[goinfo.strings[stringid].lkid[i]].dragonid==-1) AddStringToDragon(goinfo.strings[stringid].lkid[i],dragonid,goinfo);
				else
				{
					CombDragon(dragonid,goinfo.strings[goinfo.strings[stringid].lkid[i]].dragonid,goinfo);
					dragonid=goinfo.strings[stringid].dragonid;
				}
			}
		}
	}
	if(dragonid==-1)
	{
		CreateDragon(stringid,goinfo);
		dragonid=goinfo.strings[stringid].dragonid;
	}
	if(goinfo.strings[stringid].lkcount==0)
	{
		goinfo.dragons[dragonid].air=goinfo.strings[stringid].air;
		goinfo.dragons[dragonid].color=goinfo.strings[stringid].color;
		goinfo.dragons[dragonid].kcount=1;
		goinfo.dragons[dragonid].stringids[0]=stringid;
	}
	return dragonid;
}

//������Ƴ���Ⱥ
void Sfc::RemoveStringFromDragon(int stringid, int dragonid, Data_GoInfo &goinfo)
{
	for(int i=0;i<goinfo.dragons[dragonid].kcount;i++)
	{
		if(goinfo.dragons[dragonid].stringids[i]==stringid)
		{
			//����Ⱥ�����Ŀ����Ƴ�
			for(int j=i;j<goinfo.dragons[dragonid].kcount-1;j++)
			{
				goinfo.dragons[dragonid].stringids[j]=goinfo.dragons[dragonid].stringids[j+1];
			}
			goinfo.dragons[dragonid].kcount--;
			//ԭ��Ⱥ����������飬����Ⱥɾ��
			if(goinfo.dragons[dragonid].kcount==0)
			{
				goinfo.dragons[dragonid].color=0;
				goinfo.dragoncount--;
			}
			else//�������ӱ仯
			{
				for(int j=0;j<goinfo.dragons[dragonid].kcount;j++)
				{
					for(int k=0;k<goinfo.strings[goinfo.dragons[dragonid].stringids[j]].lkcount;k++)
					{
						if(goinfo.strings[goinfo.dragons[dragonid].stringids[j]].lkid[k]==stringid)
						{
							for(int l=k;l<goinfo.strings[goinfo.dragons[dragonid].stringids[j]].lkcount-1;l++)
							{
								goinfo.strings[goinfo.dragons[dragonid].stringids[j]].lkid[l]=goinfo.strings[goinfo.dragons[dragonid].stringids[j]].lkid[l+1];
							}
							goinfo.strings[goinfo.dragons[dragonid].stringids[j]].lkcount--;
							for(int l=0;l<goinfo.strings[goinfo.dragons[dragonid].stringids[j]].zcount;l++)
							{
								int x=goinfo.strings[goinfo.dragons[dragonid].stringids[j]].xs[l];
								int y=goinfo.strings[goinfo.dragons[dragonid].stringids[j]].ys[l];
								for(int m=0;m<goinfo.stones[x][y].lzcount;m++)
								{
									if(goinfo.stones[goinfo.stones[x][y].lzxs[m]][goinfo.stones[x][y].lzys[m]].stringid==stringid)
									{
										for(int n=m;n<goinfo.stones[x][y].lzcount-1;n++)
										{
											goinfo.stones[x][y].lzxs[n]=goinfo.stones[x][y].lzxs[n+1];
											goinfo.stones[x][y].lzys[n]=goinfo.stones[x][y].lzys[n+1];
										}
										goinfo.stones[x][y].lzcount--;
									}
								}
							}
							break;
						}
					}
				}
			}
			break;
		}
	}
	//CalQqAir(dragonid);
	//CalQqEye(dragonid);
}

//������Ⱥ����
int Sfc::GetDragonAir(int dragonid, Data_GoInfo &goinfo)
{
	goinfo.dragons[dragonid].air=0;
	for(int i=0;i<goinfo.dragons[dragonid].kcount;i++)
	{
		for(int j=0;j<goinfo.strings[goinfo.dragons[dragonid].stringids[i]].air;j++)
		{
			int k;
			for(k=0;k<goinfo.dragons[dragonid].air;k++)
			{
				if(goinfo.dragons[dragonid].airxs[k]==goinfo.strings[goinfo.dragons[dragonid].stringids[i]].airxs[j] && goinfo.dragons[dragonid].airys[k]==goinfo.strings[goinfo.dragons[dragonid].stringids[i]].airys[j]) break;
			}
			if(k==goinfo.dragons[dragonid].air)
			{
				goinfo.dragons[dragonid].airxs[k]=goinfo.strings[goinfo.dragons[dragonid].stringids[i]].airxs[j];
				goinfo.dragons[dragonid].airys[k]=goinfo.strings[goinfo.dragons[dragonid].stringids[i]].airys[j];
				goinfo.dragons[dragonid].air++;
			}
		}
	}
	return goinfo.dragons[dragonid].air;
}

//����Χ��Ծ���Ϣ
void Sfc::CopyGoInfo(Data_GoInfo* psource_goinfo, Data_GoInfo* pdest_goinfo)
{
	/*dest_goinfo.boardsize = source_goinfo.boardsize;//���̴�С
	for (int i = 0; i < dest_goinfo.boardsize; i++)
		for (int j = 0; j < dest_goinfo.boardsize; j++)
			dest_goinfo.board[i][j] = source_goinfo.board[i][j];
	for (int i = 0; i < dest_goinfo.boardsize; i++)
		for (int j = 0; j < dest_goinfo.boardsize; j++)
			dest_goinfo.stones[i][j] = source_goinfo.stones[i][j];
	/*
	Data_Stone stones[19][19];//��������
	Data_Stone laststone;//�������
	Data_Stone lastcapturestone;//������
	Data_String strings[180];//�������
	int dragoncount;//��Ⱥ��
	Data_Dragon dragons[100];//��Ⱥ����
	Data_Yx yxs[100];//��������
	int gocolor;//���ַ���ɫ
	int gocount;//���Ӽ�¼��
	int recallstartid;//������ʼID
	Data_GoRecord gorecord[500];//���Ӽ�¼
	int anacount;//������¼��
	Data_GoRecord anarecord[500];//������¼
	int blackcount;//������
	int whitecount;//������
	int blackcaptured;//���ӱ�����
	int whitecaptured;//���ӱ�����
	*/
}

//���壬num-���岽��
void Sfc::Undo(int num, Data_GoInfo& goinfo)
{
	if (num > goinfo.gocount)
		return;
	int gocount = goinfo.gocount - num;
	int fixedstone = min(goinfo.fixedstone, gocount);
	Data_GoRecord recs[500];
	memcpy(recs, goinfo.gorecord, sizeof(Data_GoRecord) * gocount);
	goinfo.Init(goinfo.boardsize);
	for (int i = 0; i < gocount; i++)
		PlayStone(recs[i].x, recs[i].y, recs[i].color, goinfo);
	goinfo.fixedstone = fixedstone;
}

//��ȡ��Ⱥ��Χ
CRect Sfc::GetDragonArea(int dragonid, Data_GoInfo& goinfo)
{
	int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
	int color = goinfo.dragons[dragonid].color;
	for (int i = 0; i < goinfo.boardsize; i++)
	{
		for (int j = 0; j < goinfo.boardsize; j++)
		{
			if (goinfo.stones[i][j].color == color && goinfo.stones[i][j].dragonid == dragonid)
			{
				x1 = i;
				break;
			}
		}
		if (x1 >= 0)
			break;
	}
	for (int i = goinfo.boardsize - 1; i >= 0; i--)
	{
		for (int j = 0; j < goinfo.boardsize; j++)
		{
			if (goinfo.stones[i][j].color == color && goinfo.stones[i][j].dragonid == dragonid)
			{
				x2 = i;
				break;
			}
		}
		if (x2 >= 0)
			break;
	}
	for (int j = 0; j < goinfo.boardsize; j++)
	{
		for (int i = 0; i < goinfo.boardsize; i++)
		{
			if (goinfo.stones[i][j].color == color && goinfo.stones[i][j].dragonid == dragonid)
			{
				y1 = j;
				break;
			}
		}
		if (y1 >= 0)
			break;
	}
	for (int j = goinfo.boardsize - 1; j >= 0; j--)
	{
		for (int i = 0; i < goinfo.boardsize; i++)
		{
			if (goinfo.stones[i][j].color == color && goinfo.stones[i][j].dragonid == dragonid)
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

//�ж���Ⱥ�Ƿ񱻰�Χ
bool Sfc::DragonSurrounded(int dragonid, Data_GoInfo& goinfo)
{
	CRect rect = GetDragonArea(dragonid, goinfo);
	int boardsize = goinfo.boardsize;
	int color = goinfo.dragons[dragonid].color;
	int othercolor = OTHER_COLOR(color);
	bool surrounded = false;
	//left
	if (rect.left > 3)
	{
		for (int y = max(rect.top,1); y <= min(rect.bottom,boardsize-2); y++)
		{
			for (int x = rect.left - 3; x < rect.right; x++)
			{
				if (goinfo.stones[x][y].color == color && goinfo.stones[x][y].dragonid == dragonid)
					break;
				for (int y1 = y - 1; y1 <= y + 1; y1++)
				{
					if (goinfo.board[x][y1] == othercolor)
					{
						surrounded = true;
						break;
					}
				}
				if (surrounded)
					break;
			}
			if (!surrounded)
			{
				goinfo.dragons[dragonid].surrounded = false;
				return false;
			}
		}
	}
	surrounded = false;
	//right
	if (rect.right < boardsize - 4)
	{
		for (int y = max(rect.top, 1); y <= min(rect.bottom,boardsize-2); y++)
		{
			for (int x = rect.right + 3; x > rect.left; x--)
			{
				if (goinfo.stones[x][y].color == color && goinfo.stones[x][y].dragonid == dragonid)
					break;
				for (int y1 = y - 1; y1 <= y + 1; y1++)
				{
					if (goinfo.board[x][y1] == othercolor)
					{
						surrounded = true;
						break;
					}
				}
				if (surrounded)
					break;
			}
			if (!surrounded)
			{
				goinfo.dragons[dragonid].surrounded = false;
				return false;
			}
		}
	}
	surrounded = false;
	//top
	if (rect.top > 3)
	{
		for (int x = max(rect.left, 1); x <= min(rect.right, boardsize - 2); x++)
		{
			for (int y = rect.top - 3; y < rect.bottom; y++)
			{
				if (goinfo.stones[x][y].color == color && goinfo.stones[x][y].dragonid==dragonid)
					break;
				for (int x1 = x - 1; x1 <= x + 1; x1++)
				{
					if (goinfo.board[x1][y] == othercolor)
					{
						surrounded = true;
						break;
					}
				}
				if (surrounded)
					break;
			}
			if (!surrounded)
			{
				goinfo.dragons[dragonid].surrounded = false;
				return false;
			}
		}
	}
	surrounded = false;
	//bottom
	if (rect.bottom < boardsize - 4)
	{
		for (int x = max(rect.left, 1); x <= min(rect.right, boardsize - 2); x++)
		{
			for (int y = rect.bottom + 3; y > rect.top; y--)
			{
				if (goinfo.stones[x][y].color == color && goinfo.stones[x][y].dragonid == dragonid)
					break;
				for (int x1 = x - 1; x1 <= x + 1; x1++)
				{
					if (goinfo.board[x1][y] == othercolor)
					{
						surrounded = true;
						break;
					}
				}
				if (surrounded)
					break;
			}
			if (!surrounded)
			{
				goinfo.dragons[dragonid].surrounded = false;
				return false;
			}
		}
	}
	goinfo.dragons[dragonid].surrounded = true;
	return true;
}
