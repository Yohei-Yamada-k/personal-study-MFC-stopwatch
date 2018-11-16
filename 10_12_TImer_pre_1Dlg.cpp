
// 10_12_TImer_pre_1Dlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "10_12_TImer_pre_1.h"
#include "10_12_TImer_pre_1Dlg.h"
#include "afxdialogex.h"
#include "windows.h"
#include "mmsystem.h"	// timeGetTime()
#pragma comment( lib, "winmm.lib")
#include "StopWatch_Assert.h"
#include "StopWatch_Const.h"
#include <sstream>
#include <string>
#include <direct.h> // mkdir
#include <sys/stat.h> // ファイルの状態を取得

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//***********************************************************
// @@@@ 追加実装：構造体のオブジェクト定義
//***********************************************************
filesave FileSave[__LAP_COUNT_MAX] = {
	0
};

// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy10_12_TImer_pre_1Dlg ダイアログ



CMy10_12_TImer_pre_1Dlg::CMy10_12_TImer_pre_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy10_12_TImer_pre_1Dlg::IDD, pParent)
	, m_counter(_T("00:00.000"))
	, m_start_time(0)
	, m_lap_1(_T("00:00.000"))
	, m_lap_idc_f(_T("00:00.000"))
	, m_lap_idc_h(_T("00:00.000"))
	, m_lap_idc_j(_T("00:00.000"))
	// ラップラベル描画変数
	, m_label_lap_1(_T(""))
	, m_label_lap_2(_T(""))
	, m_label_lap_3(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_end_time = 0;
	m_elapsed_time = 0;
	m_elapsed_laptime = 0;
	m_str_idc_h_value = _T("00:00.000");
	m_str_idc_j_value = _T("00:00.000");
	// ラップラベルのカウント変数
	m_label_count_lap_1 = 1;
	m_label_count_lap_2 = 1;
	m_label_count_lap_3 = 1;
}

void CMy10_12_TImer_pre_1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_STATIC_A, m_text);
	//  DDX_Control(pDX, IDC_STATIC_A, m_counter);
	DDX_Text(pDX, IDC_STATIC_A, m_counter);
	DDX_Control(pDX, IDC_STATIC_A, m_static_a_color);
	DDX_Control(pDX, IDC_STATIC_B, m_static_b_color);
	DDX_Text(pDX, IDC_STATIC_B, m_lap_1);
	DDX_Text(pDX, IDC_STATIC_F, m_lap_idc_f);
	DDX_Text(pDX, IDC_STATIC_H, m_lap_idc_h);
	DDX_Control(pDX, IDC_STATIC_F, m_static_f_color);
	DDX_Control(pDX, IDC_STATIC_H, m_static_h_color);
	DDX_Text(pDX, IDC_STATIC_J, m_lap_idc_j);
	DDX_Control(pDX, IDC_STATIC_J, m_static_j_color);
	DDX_Text(pDX, IDC_STATIC_E, m_label_lap_1);
	DDX_Text(pDX, IDC_STATIC_G, m_label_lap_2);
	DDX_Text(pDX, IDC_STATIC_I, m_label_lap_3);
}

BEGIN_MESSAGE_MAP(CMy10_12_TImer_pre_1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy10_12_TImer_pre_1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy10_12_TImer_pre_1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy10_12_TImer_pre_1Dlg::OnBnClickedButton3)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &CMy10_12_TImer_pre_1Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMy10_12_TImer_pre_1Dlg メッセージ ハンドラー

BOOL CMy10_12_TImer_pre_1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	Stop_Enable = false;
	Laptime_On = false;
	Laptime_count_over = false;
	Time_count_over = false;

	// 赤色のブラシを作成する．
	//m_brDlg.CreateSolidBrush(RGB(55,55,40));

	// ボタン表示の初期化
	CButton *button2=(CButton*)GetDlgItem(IDC_BUTTON2);
	button2->EnableWindow(FALSE);
	CButton *button3=(CButton*)GetDlgItem(IDC_BUTTON3);
	button3->EnableWindow(FALSE);

	// フォントを作成
    LOGFONT lf;
    this->GetFont()->GetLogFont(&lf);

    lf.lfHeight = 200;        // 16.0ポイント（1/10ポイント単位で指定）
	lf.lfWeight = FW_BOLD;
	lf.lfItalic =  true;

    CFont font;
    font.CreatePointFontIndirect(&lf);

    // コントロールのフォントを変更
    this->GetDlgItem(IDC_STATIC_A)->SetFont(&font);
	this->GetDlgItem(IDC_STATIC_B)->SetFont(&font);
	this->GetDlgItem(IDC_STATIC_F)->SetFont(&font);
	this->GetDlgItem(IDC_STATIC_H)->SetFont(&font);
	this->GetDlgItem(IDC_STATIC_J)->SetFont(&font);

    // フォントハンドルがクローズされないようにする
    font.Detach();

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CMy10_12_TImer_pre_1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMy10_12_TImer_pre_1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMy10_12_TImer_pre_1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////
//
// ■■ ボタン1:スタートボタンを押下処理 ■■
//
//////////////////////////////////////////////////
void CMy10_12_TImer_pre_1Dlg::OnBnClickedButton1()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	// タイマー停止中
	if(!Stop_Enable){

		// システム時刻を開始時間として取得
		CMy10_12_TImer_pre_1Dlg::GetSysStartTime();

		    // タイマー起動
	        SetTimer(1, 100, NULL);
		    Stop_Enable = true;

		if(Laptime_count_over == true){
			// ラップボタンを非表示
			CButton *button2=(CButton*)GetDlgItem(IDC_BUTTON2);
			button2->EnableWindow(FALSE);

			// クリアボタンを非表示
			CButton *button3=(CButton*)GetDlgItem(IDC_BUTTON3);
			button3->EnableWindow(FALSE);
		}
		else
			{
			// ラップボタンを活性化
			CButton *button2=(CButton*)GetDlgItem(IDC_BUTTON2);
			button2->EnableWindow(TRUE);

			// クリアボタンを非表示
			CButton *button3=(CButton*)GetDlgItem(IDC_BUTTON3);
			button3->EnableWindow(FALSE);
		}
	}
	else
	    {
			// タイマー停止
			StopTimer();
	}
	UpdateData(FALSE);
}

//////////////////////////////////////////////////
//
// ■■ボタン2:ラップボタンを押下処理 ■■
//
//////////////////////////////////////////////////
void CMy10_12_TImer_pre_1Dlg::OnBnClickedButton2()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	CString str = 0;
	CString str_f = 0;
	CString str_h = 0;
	CString str_j = 0;
	CString iCount = 0;

	Laptime_On = true; 

	// ラップのカウント上限は100カウントとする
	if(GetLabelLapCount(__LABEL_COUNT_LAP_1) > __LAP_COUNT_MAX){
		// エラーコード表示
		StopWatch_Assert Assert;
		Assert.ExecAssert(__ERR_CODE001);

	}
	else{

		// ラップカウンターを描画
		str = ExecTimeCastProcess();
		// 描画処理
		DrawStaticText(&str,__IDC_STATIC_B);

		// ラップ
		str_f = ExecLapTimeCastProcess();
		iCount.Format(L"Lap %d",GetLabelLapCount(__LABEL_COUNT_LAP_1));
		m_label_lap_1 = iCount;

		if(m_lap_idc_f == "00:00.000"){
			// 描画処理
		    DrawStaticText(&str_f,__IDC_STATIC_F);
		}
		else if(m_lap_idc_h == "00:00.000"){
			str_h = GetSrtIdcHValue();
			SetStrIdcJValue(GetSrtIdcHValue());

			SetLabelLapCount(__LABEL_COUNT_LAP_2,(GetLabelLapCount(__LABEL_COUNT_LAP_1) - 1));

			iCount.Format(L"Lap %d",GetLabelLapCount(__LABEL_COUNT_LAP_2));
			m_label_lap_2 = iCount;

			SetLabelLapCount(__LABEL_COUNT_LAP_3,GetLabelLapCount(__LABEL_COUNT_LAP_2));

			// 描画処理
		    DrawStaticText(&str_f,__IDC_STATIC_F);
			DrawStaticText(&str_h,__IDC_STATIC_H);
		}
		else
	        {
				str_h = GetSrtIdcHValue();
				str_j = GetStrIdcJValue();

				// ラップ3を表示
				//★ m_label_count_lap_2 = GetLabelLapCount(1) -1 ;
			    SetLabelLapCount(__LABEL_COUNT_LAP_2,(GetLabelLapCount(__LABEL_COUNT_LAP_1) - 1));

				iCount.Format(L"Lap %d",GetLabelLapCount(__LABEL_COUNT_LAP_2));
				m_label_lap_2 = iCount;

				iCount.Format(L"Lap %d",GetLabelLapCount(__LABEL_COUNT_LAP_3));
				m_label_lap_3 = iCount;

				// 描画処理
			    DrawStaticText(&str_f,__IDC_STATIC_F);
				DrawStaticText(&str_h,__IDC_STATIC_H);
				DrawStaticText(&str_j,__IDC_STATIC_J);

				//★m_str_idc_j_value = GetSrtIdcHValue();
				SetStrIdcJValue(GetSrtIdcHValue());
				//★　m_label_count_lap_3 = GetLabelLapCount(2);
			    SetLabelLapCount(__LABEL_COUNT_LAP_3,GetLabelLapCount(__LABEL_COUNT_LAP_2));
		}
		//★ m_str_idc_h_value = str_f;
		SetStrIdcHValue(str_f);
		// ★　m_label_count_lap_1 ++;
		SetLabelLapCount(__LABEL_COUNT_LAP_1,(GetLabelLapCount(__LABEL_COUNT_LAP_1) + 1));
	}

	Laptime_On = false; 
	UpdateData(FALSE);
}

//////////////////////////////////////////////////
//
// ■■ ボタン3:クリアボタン押下処理 ■■
//
//////////////////////////////////////////////////
void CMy10_12_TImer_pre_1Dlg::OnBnClickedButton3()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	
	CString str;

	m_start_time = 0;
	m_elapsed_time = 0;
	m_elapsed_laptime = 0;
	SetStrIdcHValue(L"00:0.000");
	SetStrIdcJValue(L"00:0.000");

	// カウンター表示を初期化
	str.Format(L"%02d:%0.03f",00 ,00 ,000);
	for (int i = 0; i <= __IDC_STATIC_MAX ; ++i){
		DrawStaticText(&str,i);
	}

    // スタティックテキストの描画変数を初期化
	m_lap_idc_f.SetString(L"00:00.000");
	m_lap_idc_h.SetString(L"00:00.000");
	m_lap_idc_j.SetString(L"00:00.000");

	//ラベル描画変数を初期化
	m_label_count_lap_1 = 1;
	m_label_count_lap_2 = 1;
	m_label_count_lap_3 = 1;

	//ラベル描画をブランク
	m_label_lap_1.SetString(L" ");
	m_label_lap_2.SetString(L" ");
	m_label_lap_3.SetString(L" ");

	CButton *button1=(CButton*)GetDlgItem(IDC_BUTTON1);
	button1->EnableWindow(TRUE);
	CButton *button3=(CButton*)GetDlgItem(IDC_BUTTON3);
	button3->EnableWindow(FALSE);

	Laptime_count_over = false;
	Time_count_over = false;

	UpdateData(FALSE);
}


/////////////////////////////////////////////////////////
//
// タイムカウンターの計算処理
//
/////////////////////////////////////////////////////////
CString CMy10_12_TImer_pre_1Dlg::ExecTimeCastProcess(void)
{
	DWORD s_tm = 0;
    DWORD e_tm = 0;
	float tm_sec = 0;
    int tm_min = 0;
	CString str;

	// 開始/終了時間を取得
	GetSysEndTime();
	e_tm = GetEndTime();
	s_tm = GetStartTime();

	// ss:mmm表記に変換
	tm_sec = TimeSecConvert(e_tm, s_tm);

	// mm表記に変換
	tm_min = TimeMinConvert(e_tm, s_tm);

	// 表示フォーマットにキャスト
	str.Format(L"%02d:%02.3f",tm_min ,tm_sec);

	//***********************************************************
	// @@@@ 追加実装：ファイル出力構造体にスプリットデータを保存
	//***********************************************************

	FileSave[(GetLabelLapCount(__LABEL_COUNT_LAP_1))-1].svesplittime = (float)tm_min + tm_sec;

	return str;

}

////////////////////////////////////////////////////////////
//
// ラップタイムカウンターの計算処理
//
////////////////////////////////////////////////////////////
CString CMy10_12_TImer_pre_1Dlg::ExecLapTimeCastProcess(void)
{
	DWORD s_tm = 0;
    DWORD e_tm = 0;
    DWORD elap_tm = 0;
	DWORD lap_tm = 0;
	float tm_sec = 0;
    int tm_min = 0;
	CString str;

	// 開始/終了時間を取得
	GetSysEndTime();
	e_tm = GetEndTime();
	s_tm = GetStartTime();

	elap_tm = GetElapsedTime();

	// 初回処理
	if(m_elapsed_laptime == 0){
	    m_elapsed_laptime = (e_tm - s_tm);
	// ss:mmm表記に変換
	tm_sec = LapTimeSecConvert(GetElapsedLapTime());

	// mm表記に変換
	tm_min = LapTimeMinConvert(GetElapsedLapTime());

	// 表示フォーマットにキャスト
	str.Format(L"%02d:%02.3f",tm_min ,tm_sec);

	}
	else{
		// 現在 - 過去
	    lap_tm = (e_tm - s_tm) - GetElapsedLapTime();

		m_elapsed_laptime = e_tm - s_tm ;
	    // ss:mmm表記に変換
	    tm_sec = LapTimeSecConvert(lap_tm);

	    // mm表記に変換
	    tm_min = LapTimeMinConvert(lap_tm);

	    // 表示フォーマットにキャスト
	    str.Format(L"%02d:%02.3f",tm_min ,tm_sec);

	}

	//***********************************************************
	// @@@@@ 追加実装:ラップタイムをファイル構造体に保存
    //***********************************************************

	// ラップラベルカウントの初期値=1のため、-1する
	FileSave[(GetLabelLapCount(__LABEL_COUNT_LAP_1))-1].savelaptime = (float)tm_min + tm_sec;

	time_t rtime = 0;
	time_t atime = 0;

	// 現在時刻を取得
	rtime = time(&atime);
		if(rtime == -1){
		return str;
	}

	errno_t error;

	// グローバルタイムをローカルタイムに変換
	struct tm strtim;
	error = localtime_s(&strtim,&rtime);

	char ascstr[40];
	asctime_s(ascstr,sizeof(ascstr),&strtim);

	// 出力ファイル構造体に保存
	asctime_s(FileSave[(GetLabelLapCount(__LABEL_COUNT_LAP_1))-1].localtime,sizeof(FileSave[(GetLabelLapCount(__LABEL_COUNT_LAP_1))-1].localtime),&strtim);

	return str;
}

///////////////////////////////////////////////////////////////////
//
// スタティックテキストの描画処理
//
///////////////////////////////////////////////////////////////////
void CMy10_12_TImer_pre_1Dlg::DrawStaticText(CString *str, int enm)
{

	switch (enm)
	{
	case __IDC_STATIC_A:
		//IDC_STATIC_Aの描画
		m_counter = *str;
		break;
	case __IDC_STATIC_B:
		//IDC_STATIC_Bの描画
		m_lap_1 = *str;
		break;
	case __IDC_STATIC_F:
		//IDC_STATIC_Fの描画
		m_lap_idc_f = *str;
		break;
	case __IDC_STATIC_H:
		//IDC_STATIC_Hの描画
		m_lap_idc_h = *str;
		break;
	case __IDC_STATIC_J:
		//IDC_STATIC_Jの描画
	    m_lap_idc_j = *str;
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////////////////////////
//
// ss:SSS表記に変換
//
/////////////////////////////////////////////////////////////////////////
float CMy10_12_TImer_pre_1Dlg::TimeSecConvert(DWORD e_conv, DWORD s_conv)
{

	float tm_sec = 0;
	int tm_sec_conv;
	DWORD elap_tm;

	elap_tm = GetElapsedTime();
	tm_sec = (float)((e_conv - s_conv) + elap_tm) / 1000;
	tm_sec_conv = (int)tm_sec;
	tm_sec = tm_sec - (float)tm_sec_conv;
	tm_sec_conv %= 60;
	tm_sec = tm_sec + (float)tm_sec_conv;

	return tm_sec;
}


/////////////////////////////////////////////////////////////////////////
//
// ss:SSS表記に変換
//
/////////////////////////////////////////////////////////////////////////
float CMy10_12_TImer_pre_1Dlg::LapTimeSecConvert(DWORD conv)
{
	float tm_sec = 0;
	int tm_sec_conv;
	DWORD elap_tm;

	elap_tm = GetElapsedTime();

	tm_sec = (float)(conv) / 1000;
	tm_sec_conv = (int)tm_sec;
	tm_sec = tm_sec - (float)tm_sec_conv;
	tm_sec_conv %= 60;
	tm_sec = tm_sec + (float)tm_sec_conv;

	return tm_sec;
}


/////////////////////////////////////////////////////////////////////////
//
// mm表記に変換
//
/////////////////////////////////////////////////////////////////////////
int CMy10_12_TImer_pre_1Dlg::TimeMinConvert(DWORD e_conv, DWORD s_conv)
{
	int tm_min = 0;
	DWORD elap_tm;

	elap_tm = GetElapsedTime();

	tm_min = ((int)((e_conv - s_conv) + elap_tm) / 1000) / 60;
	tm_min %= 60;

	return tm_min;
}

/////////////////////////////////////////////////////////////////////////
//
// mm表記に変換
//
/////////////////////////////////////////////////////////////////////////
int CMy10_12_TImer_pre_1Dlg::LapTimeMinConvert(DWORD conv)
{
	int tm_min = 0;
	DWORD elap_tm;

	elap_tm = GetElapsedTime();

	tm_min = ((int)(conv) / 1000) / 60;
	tm_min %= 60;

	return tm_min;
}


void CMy10_12_TImer_pre_1Dlg::OnStnClickedStaticB()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


HBRUSH CMy10_12_TImer_pre_1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

   // ｽﾀﾃｨｯｸﾃｷｽﾄの色変更	
    if (nCtlColor == CTLCOLOR_STATIC )	
		if (*pWnd == m_static_a_color ||*pWnd == m_static_b_color ||*pWnd ==  m_static_f_color ||*pWnd == m_static_j_color)	
        {	
            // 文字色	
            pDC->SetTextColor(RGB(0, 255, 65));	
            // 背景色	
            hbr = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));	
            pDC->SetBkColor(RGB(0, 0, 0));	
        }	
		if (*pWnd ==  m_static_h_color || *pWnd == m_static_j_color)
		{
            // 文字色	
            pDC->SetTextColor(RGB(0, 150, 65));	
            // 背景色	
            hbr = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));	
            pDC->SetBkColor(RGB(0, 0, 0));			
		}
			return hbr;
}


///////////////////////////////////////////////////////
//
// ラップラベルのカウント数を取得
//
///////////////////////////////////////////////////////
int CMy10_12_TImer_pre_1Dlg::GetLabelLapCount(int def)
{
	int result = 0;

	switch (def)
	{
	case 1:
		result = m_label_count_lap_1;
		break;
	case 2:
		result = m_label_count_lap_2;
		break;
	case 3:
		result = m_label_count_lap_3;
		break;
	default:
		break;
	}
	
	return result;
}


///////////////////////////////////////////////////////
//
// ラップラベルのカウント数を返す
//
///////////////////////////////////////////////////////
void CMy10_12_TImer_pre_1Dlg::SetLabelLapCount(int def,int count)
{
	switch (def)
	{
	case 1:
		m_label_count_lap_1 = count;
		break;
	case 2:
		m_label_count_lap_2 = count;
		break;
	case 3:
		m_label_count_lap_3 = count;
		break;
	default:
		break;
	}
}


void CMy10_12_TImer_pre_1Dlg::SetStrIdcHValue(CString str)
{
	m_str_idc_h_value = str;
}


void CMy10_12_TImer_pre_1Dlg::SetStrIdcJValue(CString str)
{
	m_str_idc_j_value = str;
}



void CMy10_12_TImer_pre_1Dlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	//***********************************************************
	// @@@@ 追加実装：ファイル出力処理
	//***********************************************************

	if(FileSave[0].savelaptime == 0){
		// ラップボタンを押さない場合はファイルオープンしない
	}
	else {

		// フォルダを作成
		char *dir = __FOLDER_PATH_1;

		if (_mkdir(dir) == 0){
		}
		else {
		}

		// ファイルオープン
		FILE *fp = 0;
		char file[50];
		int i = 0;

		struct stat buf;

		time_t rtime = 0;
		time_t atime = 0;

		// 現在時刻を取得
		rtime = time(&atime);
			if(rtime == -1){
			
		}
		tm tim;
		errno_t error;
		error = localtime_s(&tim,&rtime);

		// ファイルの存在を確認する
		do
		{
			i++;
			sprintf_s(file,"C:\\MFC_Debug_Stopwatch\\Stopwatch-%d%d-%d.txt",tim.tm_mon,tim.tm_mday,i) ;
		} while (stat(file, &buf) == 0);
		 
		fopen_s(&fp, file, "w");


		// 構造体のポインタ
		filesave *pFileSave;
		pFileSave = FileSave;

		// 計測データの日時/ラップタイム/スプリットタイムをファイルに出力
		for (int i =0; i < (GetLabelLapCount(__LABEL_COUNT_LAP_1))-1; ++i){
			fprintf(fp,"%s Laptime%d：%g SplitTime%d : %g\n", (pFileSave+i)->localtime, i+1,(pFileSave+i)->savelaptime, i +1,(pFileSave+i)->svesplittime);
		}

		// ファイルクローズ
		fclose(fp);

	}

	CDialogEx::OnOK();
}
