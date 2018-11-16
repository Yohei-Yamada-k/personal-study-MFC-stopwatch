
// 10_12_TImer_pre_1Dlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"

// CMy10_12_TImer_pre_1Dlg ダイアログ
class CMy10_12_TImer_pre_1Dlg : public CDialogEx
{
// コンストラクション
public:
	CBrush m_brDlg;		// ダイアログの背景色ブラシ(ここを追加する)
	CMy10_12_TImer_pre_1Dlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
	enum { IDD = IDD_MY10_12_TIMER_PRE_1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	//タイムカウンター計算処理
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:

	// システム時間を取得
	void GetSysStartTime(void);
	void GetSysEndTime(void);

	//タイマー開始時間を取得
	DWORD GetStartTime(void){
		return m_start_time;	
	};

	//タイマー停止時間を取得
	DWORD GetEndTime(void){
		return m_end_time;
	};

	//タイマー経過時間を保存
	DWORD SetElapsedTime(void);

	//タイマー経過時間を取得
	DWORD GetElapsedTime(void){
		return m_elapsed_time;
	};

	// 文字列を描画する
	void DrawStaticText(CString* str, int enm);

	// ラップ2の文字列を返す
	CString GetSrtIdcHValue(void){
		return m_str_idc_h_value;
	}
	void SetStrIdcHValue(CString str);

	// ラップ3の文字列を返す
	CString GetStrIdcJValue(void){
		return m_str_idc_j_value;
	}
	void SetStrIdcJValue(CString str);

	// mm:ss:SS表記に変換
	float TimeSecConvert(DWORD e_conv, DWORD s_conv);
	int TimeMinConvert(DWORD e_conv, DWORD s_conv);

	// LapTimeをmm:ss:SS表記に変換
	float LapTimeSecConvert(DWORD conv);
	int LapTimeMinConvert(DWORD conv);

	// タイマー停止関数
	int StopTimer(void);

	// 時間表示のキャスト処理
	CString ExecTimeCastProcess(void);

	// ラップ時間表示のキャスト処理
	CString ExecLapTimeCastProcess(void);

	int GetLabelLapCount(int def);
	void SetLabelLapCount(int def, int count);

	// 描画処理のメッセージハンドラ
	afx_msg void OnStnClickedStaticB();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	// ラップのフラグ
	bool Laptime_On;
	// タイーマー状態のフラグ
	bool Stop_Enable;
	// ER001
	bool Laptime_count_over;
	// ER002
	bool Time_count_over;

private:
	DWORD m_start_time;
	DWORD m_end_time;
	DWORD m_elapsed_time;
	DWORD m_elapsed_laptime;
private:

	// 背景・フォントの描画処理変数
	CStatic m_static_a_color;
	CStatic m_static_b_color;
	CStatic m_static_f_color;
	CStatic m_static_h_color;
	CStatic m_static_j_color;

	// スタティックテキストの描画変数
	CString m_counter;// ラップカウンター
	CString m_lap_1; // ラップタイム
	CString m_lap_idc_f;
	CString m_lap_idc_h;
	CString m_lap_idc_j;

	// ラップラベルの描画変数
	CString m_label_lap_1;
	CString m_label_lap_2;
	CString m_label_lap_3;

	// ラップ2のString
	CString m_str_idc_h_value;
	// ラップ3のString
	CString m_str_idc_j_value;

	// ラップラベルのカウント変数
	int m_label_count_lap_1;
	int m_label_count_lap_2;
	int m_label_count_lap_3;

public:
	DWORD GetElapsedLapTime(void){
		return m_elapsed_laptime;
	}
};
