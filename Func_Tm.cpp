#include "stdafx.h"
#include "10_12_TImer_pre_1.h"
#include "10_12_TImer_pre_1Dlg.h"
#include "afxdialogex.h"
#include "windows.h"
#include "mmsystem.h"	// timeGetTime()
#include "StopWatch_Const.h"
#include "StopWatch_Assert.h"
#pragma comment( lib, "winmm.lib")

//////////////////////////////////////////////////////////////////////////
//
// SetTimerに呼ばれるタイマーイベント処理
//
//////////////////////////////////////////////////////////////////////////
void CMy10_12_TImer_pre_1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	UpdateData(FALSE);
	
	CString str;
	DWORD s_tm = 0;
    DWORD e_tm = 0;
	
	str = ExecTimeCastProcess();
	DrawStaticText(&str,__IDC_STATIC_A);

	e_tm = GetEndTime();
	s_tm = GetStartTime();
	
	// タイマーカウントの上限
	if(((e_tm - s_tm) +m_elapsed_time) > 3600000){

		StopTimer();

		// エラーコード表示
		StopWatch_Assert Assert;
		Assert.ExecAssert(__ERR_CODE002);

		//ラップボタンを活性化
		CButton *button1=(CButton*)GetDlgItem(IDC_BUTTON1);
		button1->EnableWindow(FALSE);

	}

	CDialogEx::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////////////
//
// タイマー停止処理
//
//////////////////////////////////////////////////////////////////////////
int CMy10_12_TImer_pre_1Dlg::StopTimer(void)
{
	// タイマーを停止
	KillTimer(1);

	// 経過時間を保存
	SetElapsedTime();

	if(Laptime_count_over == true){
		// クリアボタンを非表示
		CButton *button3=(CButton*)GetDlgItem(IDC_BUTTON3);
	    button3->EnableWindow(TRUE);

	}
	else {
		// ラップボタンを非表示
		// クリアボタンを活性化
		CButton *button2=(CButton*)GetDlgItem(IDC_BUTTON2);
		button2->EnableWindow(FALSE);
		CButton *button3=(CButton*)GetDlgItem(IDC_BUTTON3);
		button3->EnableWindow(TRUE);
	}

	// スタートボタンの状態を変更
	Stop_Enable = false;

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
// システム時刻を開始時間として取得
//
//////////////////////////////////////////////////////////////////////////
void CMy10_12_TImer_pre_1Dlg::GetSysStartTime(void)
{
	m_start_time = timeGetTime();
}

//////////////////////////////////////////////////////////////////////////
//
// システム時刻を終了時間として取得
//
//////////////////////////////////////////////////////////////////////////
void CMy10_12_TImer_pre_1Dlg::GetSysEndTime(void)
{
	m_end_time = timeGetTime();
}

//////////////////////////////////////////////////////////////////////////
//
// 経過時間を取得
//
//////////////////////////////////////////////////////////////////////////
DWORD CMy10_12_TImer_pre_1Dlg::SetElapsedTime(void)
{
	DWORD e_tm;
	DWORD s_tm;

	e_tm = GetEndTime();
	s_tm = GetStartTime();

	m_elapsed_time = m_elapsed_time + (e_tm - s_tm);
	//79178050

	return 0;
}