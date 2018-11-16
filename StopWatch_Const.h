#pragma once
#include "afxwin.h"

// エラーコード
#define __ERR_CODE001 1
#define __ERR_CODE002 2

// スタティック
#define __IDC_STATIC_A 0
#define __IDC_STATIC_B 1
#define __IDC_STATIC_F 2
#define __IDC_STATIC_H 3
#define __IDC_STATIC_J 4
#define __IDC_STATIC_MAX 5

// ラベル
#define __LABEL_COUNT_LAP_1 1
#define __LABEL_COUNT_LAP_2 2
#define __LABEL_COUNT_LAP_3 3

// ラップカウント
#define __LAP_COUNT_MAX 99

// 出力フォルダパス
#define __FOLDER_PATH_1 "C:\\MFC_Debug_Stopwatch"

//出力ファイル構造体
typedef struct
{
	char localtime[32];
	float savelaptime;
	float svesplittime;
} filesave;