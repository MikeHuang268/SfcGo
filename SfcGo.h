
// SfcGo.h : SfcGo Ӧ�ó������ͷ�ļ�
//
#pragma once

#include "resource.h"       // ������

#include "Sfc.h"
/*struct Data_GoRecord
{
	int x;
	int y;
	int color;
};*/
// CSfcGoApp:
// �йش����ʵ�֣������ SfcGo.cpp
//
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

const char* color_to_string(int color);

#define DEBUG_LOADSGF               0x0080
#define OTHER_COLOR(color)      (WHITE+BLACK-(color))
#define IS_STONE(arg)           ((arg) == WHITE || (arg) == BLACK)
#define POS(i, j)     ((iBoardSize + 2) + (i) * (iBoardSize + 1) + (j))
#define PASS_MOVE     0
#define NO_MOVE       PASS_MOVE


class CSfcGoApp : public CWinApp
{
public:
	CSfcGoApp();

	// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	static void LoadImg();
	static void DestroyImg();

};

extern CSfcGoApp theApp;
