#include "stdafx.h"
#include "StopWatch_Assert.h"
#include "10_12_TImer_pre_1.h"
#include "10_12_TImer_pre_1Dlg.h"
#include "StopWatch_Const.h"


StopWatch_Assert::StopWatch_Assert(void)
{
	//do nathing
}


StopWatch_Assert::~StopWatch_Assert(void)
{
	//do nathing
}


void StopWatch_Assert::ExecAssert(int id)
{
    CString errorDisplay;
	CString str;
	CMy10_12_TImer_pre_1Dlg Dlg;

	switch (id)
	{
	case 1:
		// エラーコード001
		str = L"error code : ER%003d\nLap上限に達しました";
		Dlg.Laptime_count_over = true;
		break;
	case 2:
		// エラーコード002
		str = L"error code : ER%03d\nタイムカウントの上限に達しました";
		Dlg.Time_count_over = true;
	default:
		break;
	}
	errorDisplay.Format((str),id);
	AfxMessageBox(errorDisplay);
}
