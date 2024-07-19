#include "stdafx.h"
#include "Sfc.h"

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

//对数组进行升序排序，参数bcs为真时，同时返回数组下标的排序
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

//按行读取文本文件，并按指定字符分割成字符串数组
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
	if (len == 0)//分割符为空时不进行分割
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

//重写，按行读取文本文件，按空字符分割成count个字符串数组。主意：count大于一行实有的字符串数时会读出错误结果
bool Sfc::ReadLine(FILE *fp,int count,CString strings[])
{
	for(int i=0;i<count;i++) fscanf_s(fp,"%s",strings[i]);
	//换行
	char c='a';
	do
	{
		c=fgetc(fp);
	}while(c!='\n' && c!=-1);
	if(c==-1) return false;
	return true;
}

//读取系统配置文件
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

//写入系统配置文件
bool Sfc::WriteSysIni()
{
	errno_t err;
	FILE *fp;
	if((err=fopen_s(&fp,strSysDirectry+"\\Sys.ini","w"))!=0)
	{
		CString msg = "无法写入系统配置文件！";
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

//将yyyy-mm-ddThh:mm:ss字符串格式转化为时间
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

//着子
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
	//己方
	goinfo.board[x][y]=color;
	goinfo.stones[x][y].x=x;
	goinfo.stones[x][y].y=y;
	goinfo.stones[x][y].color=color;
	goinfo.stones[x][y].stringid=-1;
	//产生棋块和棋群
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
	//判断是否吃子
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
	if(aircount>0)//有吃子情况
	{
		//确定受影响的棋块
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
		//重新计算棋块
		for(int i=0;i<qkcount;i++)
		{
			CalString(stringids[i],goinfo);
			if(goinfo.strings[stringids[i]].dragonid>-1)
			{
				RemoveStringFromDragon(stringids[i],goinfo.strings[stringids[i]].dragonid,goinfo);
				goinfo.strings[stringids[i]].dragonid=-1;
			}
		}
		//计算棋群
		for(int i=0;i<qkcount;i++)
		{
			CalStringToDragon(stringids[i],goinfo);
		}
	}
	//对方
	CalStoneAroundDispart(x,y,goinfo);
	CalStoneAroundAir(x,y,goinfo);
	//重新标识所有棋子的dragonid
	for (int i = 0; i < goinfo.boardsize; i++)
	{
		for (int j = 0; j < goinfo.boardsize; j++)
			if(goinfo.stones[i][j].color>0)
				goinfo.stones[i][j].dragonid = goinfo.strings[goinfo.stones[i][j].stringid].dragonid;
	}
	return aircount > 0;
}

//在棋盘上摆放棋子
void Sfc::AddStone(int x,int y,int color, Data_GoInfo &goinfo)
{
	if (x < 0 || x >= goinfo.boardsize || y<0 || y>goinfo.boardsize)
		return;
	if (color != BLACK && color != WHITE)
		return;
	if(color==WHITE) goinfo.whitecount++;
	else goinfo.blackcount++;
	//己方
	goinfo.board[x][y]=color;
	goinfo.stones[x][y].x=x;
	goinfo.stones[x][y].y=y;
	goinfo.stones[x][y].color=color;
	goinfo.stones[x][y].stringid=-1;
	//产生棋块和棋群
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
	//对方
	CalStoneAroundDispart(x,y,goinfo);
	CalStoneAroundAir(x,y,goinfo);
}

//移除棋子
void Sfc::RemoveStone(int x,int y, Data_GoInfo &goinfo)
{
	RemoveStoneFromString(x,y,goinfo.stones[x][y].stringid,goinfo);
	//计算周边的棋块变化
	//确定受影响的棋块
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
	//重新计算棋块
	for(int i=0;i<qkcount;i++)
	{
		CalString(stringids[i],goinfo);
		if(goinfo.strings[stringids[i]].dragonid>-1)
		{
			RemoveStringFromDragon(stringids[i],goinfo.strings[stringids[i]].dragonid,goinfo);
			goinfo.strings[stringids[i]].dragonid=-1;
		}
	}
	//计算棋群
	for(int i=0;i<qkcount;i++)
	{
		CalStringToDragon(stringids[i],goinfo);
	}
}

//棋子和棋块相连
bool Sfc::StoneLinkToString(int x,int y,int color,int stringid,Data_GoInfo &goinfo)
{
	if(goinfo.strings[stringid].color!=color) return false;
	int othercolor=OTHER_COLOR(color);
	//小尖相连
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
	//单关相连
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
	//小飞相连
	return false;
}


//判断棋子间的松散连接，x，y为棋子或空点，x0，y0必须为棋子
bool Sfc::StoneLinkToStone(int x,int y,int color,int x0,int y0, Data_GoInfo &goinfo)
{
	if(color!=goinfo.stones[x0][y0].color)
		return false;
	int othercolor=OTHER_COLOR(color);
	//直接相连
	//if((x-1==x0 || x+1==x0) && y==y0 || x==x0 && (y-1==y0 || y+1==y0))
	//	return true;
	//小尖相连
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
	//单关相连
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
	//小飞相连
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

//判断是否吃子点
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

//判断禁着点
bool Sfc::IsFobidenPoint(int x,int y,int color,Data_GoInfo &goinfo)
{
	int othercolor=OTHER_COLOR(color);
	//有多余空的情况
	if(x-1>=0 && goinfo.stones[x-1][y].color==0 || x+1<=goinfo.boardsize-1 && goinfo.stones[x+1][y].color==0 || y-1>=0 && goinfo.stones[x][y-1].color==0 || y+1<=goinfo.boardsize-1 && goinfo.stones[x][y+1].color==0) return false;
	//单个棋子的情况
	if((x==0 || goinfo.stones[x-1][y].color==othercolor) && (x==goinfo.boardsize-1 || goinfo.stones[x+1][y].color==othercolor) && (y==0 || goinfo.stones[x][y-1].color==othercolor) && (y==goinfo.boardsize-1 || goinfo.stones[x][y+1].color==othercolor))
	{
		if(x>0 && goinfo.stones[x-1][y].color==othercolor)
		{
			int stringid=goinfo.stones[x-1][y].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1 && goinfo.laststone.x==x-1 && goinfo.laststone.y==y)//劫争
					return true;
				else return false;
			}
		}
		if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==othercolor)
		{
			int stringid=goinfo.stones[x+1][y].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1 && goinfo.laststone.x==x+1 && goinfo.laststone.y==y)//劫争
					return true;
				else return false;
			}
		}
		if(y>0 && goinfo.stones[x][y-1].color==othercolor)
		{
			int stringid=goinfo.stones[x][y-1].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1 && goinfo.laststone.x==x && goinfo.laststone.y==y-1)//劫争
					return true;
				else return false;
			}
		}
		if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==othercolor)
		{
			int stringid=goinfo.stones[x][y+1].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1 && goinfo.laststone.x==x && goinfo.laststone.y==y+1)//劫争
					return true;
				else return false;
			}
		}
		return true;
	}
	//棋块的情况
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

//判断非劫争禁着点
bool Sfc::IsNoKoFobidenPoint(int x,int y,int color, Data_GoInfo &goinfo)
{
	//已经有子的点不被判断为非劫争禁着点
	if(goinfo.stones[x][y].color!=0)
		return false;
	int othercolor=OTHER_COLOR(color);
	//有多余空的情况
	if(x-1>=0 && goinfo.stones[x-1][y].color==0
		|| x+1<=goinfo.boardsize-1 && goinfo.stones[x+1][y].color==0
		|| y-1>=0 && goinfo.stones[x][y-1].color==0
		|| y+1<=goinfo.boardsize-1 && goinfo.stones[x][y+1].color==0) return false;
	//单个棋子的情况
	if((x==0 || goinfo.stones[x-1][y].color==othercolor)
		&& (x==goinfo.boardsize-1 || goinfo.stones[x+1][y].color==othercolor)
		&& (y==0 || goinfo.stones[x][y-1].color==othercolor)
		&& (y==goinfo.boardsize-1 || goinfo.stones[x][y+1].color==othercolor))
	{
		if(x>0 && goinfo.stones[x-1][y].color==othercolor && goinfo.strings[goinfo.stones[x-1][y].stringid].air==1
			|| x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==othercolor && goinfo.strings[goinfo.stones[x+1][y].stringid].air==1
			|| y>0 && goinfo.stones[x][y-1].color==othercolor && goinfo.strings[goinfo.stones[x][y-1].stringid].air==1
			|| y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==othercolor && goinfo.strings[goinfo.stones[x][y+1].stringid].air==1)
			return false;//涉及劫争或提子
		return true;
	}
	//棋块的情况
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

//判断劫争点
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
				if(goinfo.strings[stringid].zcount==1)//劫争
					return true;
				return false;
			}
		}
		if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==othercolor)
		{
			int stringid=goinfo.stones[x+1][y].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1)//劫争
					return true;
				return false;
			}
		}
		if(y>0 && goinfo.stones[x][y-1].color==othercolor)
		{
			int stringid=goinfo.stones[x][y-1].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1)//劫争
					return true;
				return false;
			}
		}
		if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==othercolor)
		{
			int stringid=goinfo.stones[x][y+1].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==11)//劫争
					return true;
				return false;
			}
		}
		return false;
	}
	return false;
}

//判断劫争禁着点
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
				if(goinfo.strings[stringid].zcount==1 && goinfo.laststone.x==x-1 && goinfo.laststone.y==y)//劫争
					return true;
				return false;
			}
		}
		if(x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==othercolor)
		{
			int stringid=goinfo.stones[x+1][y].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1 && goinfo.laststone.x==x+1 && goinfo.laststone.y==y)//劫争
					return true;
				return false;
			}
		}
		if(y>0 && goinfo.stones[x][y-1].color==othercolor)
		{
			int stringid=goinfo.stones[x][y-1].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1 && goinfo.laststone.x==x && goinfo.laststone.y==y-1)//劫争
					return true;
				return false;
			}
		}
		if(y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==othercolor)
		{
			int stringid=goinfo.stones[x][y+1].stringid;
			if(goinfo.strings[stringid].air==1)
			{
				if(goinfo.strings[stringid].zcount==1 && goinfo.laststone.x==x && goinfo.laststone.y==y+1)//劫争
					return true;
				return false;
			}
		}
		return false;
	}
	return false;
}

//判断虎口
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
	//只有一面未被包围时才是虎口
	if(air!=1)
		return false;
	//有接应时，不算虎口
	if(x>0 && goinfo.stones[x-1][y].color==othercolor && goinfo.strings[goinfo.stones[x-1][y].stringid].air>=2
		|| x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==othercolor && goinfo.strings[goinfo.stones[x+1][y].stringid].air>=2
		|| y>0 && goinfo.stones[x][y-1].color==othercolor && goinfo.strings[goinfo.stones[x][y-1].stringid].air>=2
		|| y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==othercolor && goinfo.strings[goinfo.stones[x][y+1].stringid].air>=2)
		return false;
	return true;
}

//判断单虎口
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

//判断扑劫点（即单虎口相对）
bool Sfc::IsPutKoPoint(int x, int y, int color, Data_GoInfo &goinfo)
{
	//判断单虎口
	if(!IsTermInside(x,y,color,goinfo))
		return false;
	int othercolor=OTHER_COLOR(color);
	//判断相对的单虎口
	if(x>0 && goinfo.stones[x-1][y].color==0 && IsTermInside(x-1,y,othercolor,goinfo)
		|| x<goinfo.boardsize-1 && goinfo.stones[x+1][y].color==0 && IsTermInside(x+1,y,othercolor,goinfo)
		|| y>0 && goinfo.stones[x][y-1].color==0 && IsTermInside(x,y-1,othercolor,goinfo)
		|| y<goinfo.boardsize-1 && goinfo.stones[x][y+1].color==0 && IsTermInside(x,y+1,othercolor,goinfo))
		return true;
	return false;

}

//判断真眼（单目眼）
bool Sfc::IsTrueEye1(int x, int y, int color, Data_GoInfo &goinfo)
{
	//判断是否单目眼
	if((x==0 || goinfo.stones[x-1][y].color==color)
		&& (x==goinfo.boardsize-1 || goinfo.stones[x+1][y].color==color)
		&& (y==0 || goinfo.stones[x][y-1].color==color)
		&& (y==goinfo.boardsize-1 || goinfo.stones[x][y+1].color==color))
	{
		int othercolor=OTHER_COLOR(color);
		//角上的眼，只有一个肩必须已占据或处于保护状态（禁着点或虎口且非扑劫点）
		if(x==0 && y==0)
			return goinfo.stones[x+1][y+1].color==color || IsNoKoFobidenPoint(x+1,y+1,othercolor,goinfo) || IsTermsInside(x+1,y+1,color,goinfo) && !IsPutKoPoint(x+1,y+1,color,goinfo);
		if(x==goinfo.boardsize-1 && y==0)
			return goinfo.stones[x-1][y+1].color==color || IsNoKoFobidenPoint(x-1,y+1,othercolor,goinfo) || IsTermsInside(x-1,y+1,color,goinfo) && !IsPutKoPoint(x-1,y+1,color,goinfo);
		if(x==0 && y==goinfo.boardsize-1)
			return goinfo.stones[x+1][y-1].color==color || IsNoKoFobidenPoint(x+1,y-1,othercolor,goinfo) || IsTermsInside(x+1,y-1,color,goinfo) && !IsPutKoPoint(x+1,y-1,color,goinfo);
		if(x==goinfo.boardsize-1 && y==goinfo.boardsize-1)
			return goinfo.stones[x-1][y-1].color==color || IsNoKoFobidenPoint(x-1,y-1,othercolor,goinfo) || IsTermsInside(x-1,y-1,color,goinfo) && !IsPutKoPoint(x-1,y-1,color,goinfo);
		//边上的眼，两个肩
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
		//中腹的眼，四个肩中只要占据三个就行
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

//判断棋块之间的松散连接
bool Sfc::StringLinkToString(int stringid1,int stringid2, Data_GoInfo &goinfo)
{
	for(int i=0;i<goinfo.strings[stringid1].lkcount;i++)
	{
		if(goinfo.strings[stringid1].lkid[i]==stringid2) return true;
	}
	return false;
}

//判断棋块和棋群是否相连
bool Sfc::StringLinkToDragon(int stringid, int dragonid, Data_GoInfo &goinfo)
{
	if(goinfo.dragons[dragonid].kcount==1 && goinfo.dragons[dragonid].stringids[0]==stringid) return true;
	for(int i=0;i<goinfo.strings[stringid].lkcount;i++)
	{
		if(goinfo.strings[goinfo.strings[stringid].lkid[i]].dragonid==dragonid) return true;
	}
	return false;
}

//计算棋子
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
					if(!linked)//连上一个群
					{
						goinfo.strings[goinfo.stones[x][y].stringid].dragonid=goinfo.strings[goinfo.stones[x-1+i][y-1+j].stringid].dragonid;
						goinfo.dragons[goinfo.strings[goinfo.stones[x][y].stringid].dragonid].kcount++;
						goinfo.dragons[goinfo.strings[goinfo.stones[x][y].stringid].dragonid].stringids[goinfo.dragons[goinfo.strings[goinfo.stones[x][y].stringid].dragonid].kcount-1]=goinfo.stones[x][y].stringid;
					}
					else//连上多个群
					{
						//迁移群
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

//计算棋块
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

//计算棋块周围点（不一定是气），并存入air里
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

//计算棋子和周边己方棋子的关系，决定加入块或创建快
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

//计算棋子松散相连情况，并存入lzcount和lzxs，lzys
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

//计算移除棋子产生的分断
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

//计算棋子分断情况
void Sfc::CalStoneDispart(int x,int y, Data_GoInfo &goinfo)
{
	for(int i=0;i<goinfo.stones[x][y].lzcount;i++)
	{
		if(!StoneLinkToStone(x,y,goinfo.stones[x][y].color,goinfo.stones[x][y].lzxs[i],goinfo.stones[x][y].lzys[i],goinfo))
		{
			//原棋子
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
			//被分断棋子
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
			/*//棋群变化
			if(mQk[goinfo.stones[x][y].stringid].qqid==mQk[goinfo.stones[x0][y0].stringid].qqid && !QkIndirectLinkToQk(goinfo.stones[x][y].stringid,goinfo.stones[x0][y0].stringid))//棋群被分断
			{
			DispartQq(goinfo.stones[x][y].stringid);
			}
			*/
			break;
		}
	}
}

//计算周围对方棋子被分断情况
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
	//棋群变化
	for(int i=0;i<stringcount;i++)
	{
		if(!StringLinkToDragon(stringids[i],goinfo.strings[stringids[i]].dragonid,goinfo))
		{
			DispartDragon(stringids[i],goinfo);
		}
	}
}

//计算落子周围对方棋块气数变化
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
	//计算棋群
	for(int i=0;i<qkcount;i++)
	{
		CalStringToDragon(stringids[i],goinfo);
	}
}

//递归判断棋块间间接连接
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

//判断棋块间间接相连
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

//将单个棋子分断情况加入棋块
void Sfc::AddStoneDispartToString(int x/*被分断棋子x坐标*/,int y/*被分断棋子y坐标*/,int stringid, Data_GoInfo &goinfo)
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

//为新下棋子的周围棋子加上连接
void Sfc::AddStoneRoundLink(int x,int y, Data_GoInfo &goinfo)
{
	int x1,y1;
	for(int i=0;i<goinfo.stones[x][y].lzcount;i++)
	{
		//棋子的连接
		x1=goinfo.stones[x][y].lzxs[i];y1=goinfo.stones[x][y].lzys[i];
		goinfo.stones[x1][y1].lzxs[goinfo.stones[x1][y1].lzcount]=x;
		goinfo.stones[x1][y1].lzys[goinfo.stones[x1][y1].lzcount]=y;
		goinfo.stones[x1][y1].lzcount++;
		//棋块的连接
		AddStoneLinkToString(x1,y1,goinfo.stones[x1][y1].stringid,goinfo);
	}
}

//将单个棋子连接加入棋块
void Sfc::AddStoneLinkToString(int x,int y,int stringid, Data_GoInfo &goinfo)
{
	int i,j,k;
	i=stringid;
	for(j=0;j<goinfo.stones[x][y].lzcount;j++)
	{
		//不计算连接到本棋块的连接
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

//合并棋块连接
void Sfc::CombStringLink(int stringid1,int stringid2, Data_GoInfo &goinfo)
{
	int i,j;
	//排除以前对string2的连接
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
		//添加连接到stringid1
		for(j=0;j<k;j++)
		{
			if(goinfo.strings[stringid2].lkid[i]==goinfo.strings[stringid1].lkid[j]) break;
		}
		if(j==k)
		{
			goinfo.strings[stringid1].lkid[goinfo.strings[stringid1].lkcount]=goinfo.strings[stringid2].lkid[i];
			goinfo.strings[stringid1].lkcount++;
		}
		//移除其他棋块中和stringid2的连接
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
	//移除棋块中棋子连到本块棋子的连接
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

//根据棋块创建新群
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

//合并棋群,原则上是大的合并小的，返回合并后的棋群id
int Sfc::CombDragon(int dragonid1, int dragonid2, Data_GoInfo &goinfo)
{
	//id相同或为不同颜色时，合并失败
	if(dragonid1==dragonid2 || goinfo.dragons[dragonid1].color!=goinfo.dragons[dragonid2].color) return -1;
	//寻找大的棋群
	if(goinfo.dragons[dragonid1].kcount<goinfo.dragons[dragonid2].kcount)
	{
		int dragonid=dragonid1;
		dragonid1=dragonid2;
		dragonid2=dragonid;
	}
	//更新下属棋块数和id
	memcpy_s(goinfo.dragons[dragonid1].stringids+goinfo.dragons[dragonid1].kcount,goinfo.dragons[dragonid2].kcount*sizeof(int),goinfo.dragons[dragonid2].stringids,goinfo.dragons[dragonid2].kcount*sizeof(int));
	//Array.Copy(goinfo.dragons[dragonid2].stringids,0,goinfo.dragons[dragonid1].stringids,goinfo.dragons[dragonid1].kcount,goinfo.dragons[dragonid2].kcount);
	goinfo.dragons[dragonid1].kcount+=goinfo.dragons[dragonid2].kcount;
	//更新下属棋块及棋子的棋群id
	for(int i=0;i<goinfo.dragons[dragonid2].kcount;i++)
	{
		int stringid=goinfo.dragons[dragonid2].stringids[i];
		goinfo.strings[stringid].dragonid=dragonid1;
		for(int j=0;j<goinfo.strings[stringid].zcount;j++)
		{
			goinfo.stones[goinfo.strings[stringid].xs[j]][goinfo.strings[stringid].ys[j]].dragonid=dragonid1;
		}
	}
	//合并气和眼型
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

//分断群为含本棋块和不含的两个群
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

//创建新块
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

//合并棋块
void Sfc::CombString(int stringid1,int stringid2, Data_GoInfo &goinfo)
{
	if(stringid1==stringid2 || goinfo.strings[stringid1].color!=goinfo.strings[stringid2].color) return;
	//选择大的棋块
	if(goinfo.strings[stringid1].zcount<goinfo.strings[stringid2].zcount)
	{
		int stringid=stringid1;
		stringid1=stringid2;
		stringid2=stringid;
	}
	//改变棋子所属块
	for(int i=0;i<goinfo.strings[stringid2].zcount;i++) goinfo.stones[goinfo.strings[stringid2].xs[i]][goinfo.strings[stringid2].ys[i]].stringid=stringid1;
	//复制棋子坐标
	memcpy_s(goinfo.strings[stringid1].xs+goinfo.strings[stringid1].zcount,goinfo.strings[stringid2].zcount*sizeof(int),goinfo.strings[stringid2].xs,goinfo.strings[stringid2].zcount*sizeof(int));
	memcpy_s(goinfo.strings[stringid1].ys+goinfo.strings[stringid1].zcount,goinfo.strings[stringid2].zcount*sizeof(int),goinfo.strings[stringid2].ys,goinfo.strings[stringid2].zcount*sizeof(int));
	//下属棋子数量
	goinfo.strings[stringid1].zcount+=goinfo.strings[stringid2].zcount;
	//合并棋块连接
	CombStringLink(stringid1,stringid2,goinfo);
	//删除棋块2（将颜色置为0）
	goinfo.strings[stringid2].color=0;
	//goinfo.stringsCount--;
	//计算棋块气数
	GetStringAir(stringid1,goinfo);
	//处理群变化
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

//计算棋块的气
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

//将棋子添加到棋块
void Sfc::AddStoneToString(int x,int y,int stringid, Data_GoInfo &goinfo)
{
	goinfo.stones[x][y].stringid=stringid;
	goinfo.strings[stringid].xs[goinfo.strings[stringid].zcount]=x;
	goinfo.strings[stringid].ys[goinfo.strings[stringid].zcount]=y;
	goinfo.strings[stringid].zcount++;
	//计算松散连接情况
	CalStoneLink(x,y,goinfo);
	AddStoneRoundLink(x,y,goinfo);
	int lkcount=goinfo.strings[stringid].lkcount;
	AddStoneLinkToString(x,y,stringid,goinfo);
	//计算气数变化
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
	//计算棋群变化
	for(int i=lkcount;i<goinfo.strings[stringid].lkcount;i++)
	{
		if(goinfo.strings[goinfo.strings[stringid].lkid[i]].dragonid!=goinfo.strings[stringid].dragonid)
		{
			CombDragon(goinfo.strings[stringid].dragonid,goinfo.strings[goinfo.strings[stringid].lkid[i]].dragonid,goinfo);
		}
	}
}

//将棋块添加到棋群
void Sfc::AddStringToDragon(int stringid,int dragonid, Data_GoInfo &goinfo)
{
	goinfo.strings[stringid].dragonid=dragonid;
	goinfo.dragons[dragonid].stringids[goinfo.dragons[dragonid].kcount]=stringid;
	goinfo.dragons[dragonid].kcount++;
	//mQq[qqid].air+=mQk[qkid].air;
}

//将棋子移出棋块
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

//根据给定的棋子递归计算棋块
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

//根据给定的棋块计算棋群
int Sfc::CalStringToDragon(int stringid, Data_GoInfo &goinfo)
{
	int dragonid=goinfo.strings[stringid].dragonid;
	for(int i=0;i<goinfo.strings[stringid].lkcount;i++)
	{
		if(goinfo.strings[goinfo.strings[stringid].lkid[i]].dragonid!=dragonid)
		{
			if(dragonid==-1)//连上单个群
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

//将棋块移出棋群
void Sfc::RemoveStringFromDragon(int stringid, int dragonid, Data_GoInfo &goinfo)
{
	for(int i=0;i<goinfo.dragons[dragonid].kcount;i++)
	{
		if(goinfo.dragons[dragonid].stringids[i]==stringid)
		{
			//从棋群所属的块里移除
			for(int j=i;j<goinfo.dragons[dragonid].kcount-1;j++)
			{
				goinfo.dragons[dragonid].stringids[j]=goinfo.dragons[dragonid].stringids[j+1];
			}
			goinfo.dragons[dragonid].kcount--;
			//原棋群里若已无棋块，将该群删除
			if(goinfo.dragons[dragonid].kcount==0)
			{
				goinfo.dragons[dragonid].color=0;
				goinfo.dragoncount--;
			}
			else//计算连接变化
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

//计算棋群气数
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

//复制围棋对局信息
void Sfc::CopyGoInfo(Data_GoInfo* psource_goinfo, Data_GoInfo* pdest_goinfo)
{
	/*dest_goinfo.boardsize = source_goinfo.boardsize;//棋盘大小
	for (int i = 0; i < dest_goinfo.boardsize; i++)
		for (int j = 0; j < dest_goinfo.boardsize; j++)
			dest_goinfo.board[i][j] = source_goinfo.board[i][j];
	for (int i = 0; i < dest_goinfo.boardsize; i++)
		for (int j = 0; j < dest_goinfo.boardsize; j++)
			dest_goinfo.stones[i][j] = source_goinfo.stones[i][j];
	/*
	Data_Stone stones[19][19];//棋子数组
	Data_Stone laststone;//最后落子
	Data_Stone lastcapturestone;//最后吃子
	Data_String strings[180];//棋块数组
	int dragoncount;//棋群数
	Data_Dragon dragons[100];//棋群数组
	Data_Yx yxs[100];//眼型数组
	int gocolor;//着手方颜色
	int gocount;//着子记录数
	int recallstartid;//回溯起始ID
	Data_GoRecord gorecord[500];//着子记录
	int anacount;//分析记录数
	Data_GoRecord anarecord[500];//分析记录
	int blackcount;//黑子数
	int whitecount;//白字数
	int blackcaptured;//黑子被吃数
	int whitecaptured;//白子被吃数
	*/
}

//悔棋，num-悔棋步数
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

//获取棋群范围
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

//判断棋群是否被包围
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
