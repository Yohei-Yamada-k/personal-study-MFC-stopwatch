
// 10_12_TImer_pre_1Dlg.cpp : �����t�@�C��
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
#include <sys/stat.h> // �t�@�C���̏�Ԃ��擾

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//***********************************************************
// @@@@ �ǉ������F�\���̂̃I�u�W�F�N�g��`
//***********************************************************
filesave FileSave[__LAP_COUNT_MAX] = {
	0
};

// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
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


// CMy10_12_TImer_pre_1Dlg �_�C�A���O



CMy10_12_TImer_pre_1Dlg::CMy10_12_TImer_pre_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy10_12_TImer_pre_1Dlg::IDD, pParent)
	, m_counter(_T("00:00.000"))
	, m_start_time(0)
	, m_lap_1(_T("00:00.000"))
	, m_lap_idc_f(_T("00:00.000"))
	, m_lap_idc_h(_T("00:00.000"))
	, m_lap_idc_j(_T("00:00.000"))
	// ���b�v���x���`��ϐ�
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
	// ���b�v���x���̃J�E���g�ϐ�
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


// CMy10_12_TImer_pre_1Dlg ���b�Z�[�W �n���h���[

BOOL CMy10_12_TImer_pre_1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
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

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B
	Stop_Enable = false;
	Laptime_On = false;
	Laptime_count_over = false;
	Time_count_over = false;

	// �ԐF�̃u���V���쐬����D
	//m_brDlg.CreateSolidBrush(RGB(55,55,40));

	// �{�^���\���̏�����
	CButton *button2=(CButton*)GetDlgItem(IDC_BUTTON2);
	button2->EnableWindow(FALSE);
	CButton *button3=(CButton*)GetDlgItem(IDC_BUTTON3);
	button3->EnableWindow(FALSE);

	// �t�H���g���쐬
    LOGFONT lf;
    this->GetFont()->GetLogFont(&lf);

    lf.lfHeight = 200;        // 16.0�|�C���g�i1/10�|�C���g�P�ʂŎw��j
	lf.lfWeight = FW_BOLD;
	lf.lfItalic =  true;

    CFont font;
    font.CreatePointFontIndirect(&lf);

    // �R���g���[���̃t�H���g��ύX
    this->GetDlgItem(IDC_STATIC_A)->SetFont(&font);
	this->GetDlgItem(IDC_STATIC_B)->SetFont(&font);
	this->GetDlgItem(IDC_STATIC_F)->SetFont(&font);
	this->GetDlgItem(IDC_STATIC_H)->SetFont(&font);
	this->GetDlgItem(IDC_STATIC_J)->SetFont(&font);

    // �t�H���g�n���h�����N���[�Y����Ȃ��悤�ɂ���
    font.Detach();

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
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

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CMy10_12_TImer_pre_1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CMy10_12_TImer_pre_1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////
//
// ���� �{�^��1:�X�^�[�g�{�^������������ ����
//
//////////////////////////////////////////////////
void CMy10_12_TImer_pre_1Dlg::OnBnClickedButton1()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	// �^�C�}�[��~��
	if(!Stop_Enable){

		// �V�X�e���������J�n���ԂƂ��Ď擾
		CMy10_12_TImer_pre_1Dlg::GetSysStartTime();

		    // �^�C�}�[�N��
	        SetTimer(1, 100, NULL);
		    Stop_Enable = true;

		if(Laptime_count_over == true){
			// ���b�v�{�^�����\��
			CButton *button2=(CButton*)GetDlgItem(IDC_BUTTON2);
			button2->EnableWindow(FALSE);

			// �N���A�{�^�����\��
			CButton *button3=(CButton*)GetDlgItem(IDC_BUTTON3);
			button3->EnableWindow(FALSE);
		}
		else
			{
			// ���b�v�{�^����������
			CButton *button2=(CButton*)GetDlgItem(IDC_BUTTON2);
			button2->EnableWindow(TRUE);

			// �N���A�{�^�����\��
			CButton *button3=(CButton*)GetDlgItem(IDC_BUTTON3);
			button3->EnableWindow(FALSE);
		}
	}
	else
	    {
			// �^�C�}�[��~
			StopTimer();
	}
	UpdateData(FALSE);
}

//////////////////////////////////////////////////
//
// �����{�^��2:���b�v�{�^������������ ����
//
//////////////////////////////////////////////////
void CMy10_12_TImer_pre_1Dlg::OnBnClickedButton2()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	CString str = 0;
	CString str_f = 0;
	CString str_h = 0;
	CString str_j = 0;
	CString iCount = 0;

	Laptime_On = true; 

	// ���b�v�̃J�E���g�����100�J�E���g�Ƃ���
	if(GetLabelLapCount(__LABEL_COUNT_LAP_1) > __LAP_COUNT_MAX){
		// �G���[�R�[�h�\��
		StopWatch_Assert Assert;
		Assert.ExecAssert(__ERR_CODE001);

	}
	else{

		// ���b�v�J�E���^�[��`��
		str = ExecTimeCastProcess();
		// �`�揈��
		DrawStaticText(&str,__IDC_STATIC_B);

		// ���b�v
		str_f = ExecLapTimeCastProcess();
		iCount.Format(L"Lap %d",GetLabelLapCount(__LABEL_COUNT_LAP_1));
		m_label_lap_1 = iCount;

		if(m_lap_idc_f == "00:00.000"){
			// �`�揈��
		    DrawStaticText(&str_f,__IDC_STATIC_F);
		}
		else if(m_lap_idc_h == "00:00.000"){
			str_h = GetSrtIdcHValue();
			SetStrIdcJValue(GetSrtIdcHValue());

			SetLabelLapCount(__LABEL_COUNT_LAP_2,(GetLabelLapCount(__LABEL_COUNT_LAP_1) - 1));

			iCount.Format(L"Lap %d",GetLabelLapCount(__LABEL_COUNT_LAP_2));
			m_label_lap_2 = iCount;

			SetLabelLapCount(__LABEL_COUNT_LAP_3,GetLabelLapCount(__LABEL_COUNT_LAP_2));

			// �`�揈��
		    DrawStaticText(&str_f,__IDC_STATIC_F);
			DrawStaticText(&str_h,__IDC_STATIC_H);
		}
		else
	        {
				str_h = GetSrtIdcHValue();
				str_j = GetStrIdcJValue();

				// ���b�v3��\��
				//�� m_label_count_lap_2 = GetLabelLapCount(1) -1 ;
			    SetLabelLapCount(__LABEL_COUNT_LAP_2,(GetLabelLapCount(__LABEL_COUNT_LAP_1) - 1));

				iCount.Format(L"Lap %d",GetLabelLapCount(__LABEL_COUNT_LAP_2));
				m_label_lap_2 = iCount;

				iCount.Format(L"Lap %d",GetLabelLapCount(__LABEL_COUNT_LAP_3));
				m_label_lap_3 = iCount;

				// �`�揈��
			    DrawStaticText(&str_f,__IDC_STATIC_F);
				DrawStaticText(&str_h,__IDC_STATIC_H);
				DrawStaticText(&str_j,__IDC_STATIC_J);

				//��m_str_idc_j_value = GetSrtIdcHValue();
				SetStrIdcJValue(GetSrtIdcHValue());
				//���@m_label_count_lap_3 = GetLabelLapCount(2);
			    SetLabelLapCount(__LABEL_COUNT_LAP_3,GetLabelLapCount(__LABEL_COUNT_LAP_2));
		}
		//�� m_str_idc_h_value = str_f;
		SetStrIdcHValue(str_f);
		// ���@m_label_count_lap_1 ++;
		SetLabelLapCount(__LABEL_COUNT_LAP_1,(GetLabelLapCount(__LABEL_COUNT_LAP_1) + 1));
	}

	Laptime_On = false; 
	UpdateData(FALSE);
}

//////////////////////////////////////////////////
//
// ���� �{�^��3:�N���A�{�^���������� ����
//
//////////////////////////////////////////////////
void CMy10_12_TImer_pre_1Dlg::OnBnClickedButton3()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	
	CString str;

	m_start_time = 0;
	m_elapsed_time = 0;
	m_elapsed_laptime = 0;
	SetStrIdcHValue(L"00:0.000");
	SetStrIdcJValue(L"00:0.000");

	// �J�E���^�[�\����������
	str.Format(L"%02d:%0.03f",00 ,00 ,000);
	for (int i = 0; i <= __IDC_STATIC_MAX ; ++i){
		DrawStaticText(&str,i);
	}

    // �X�^�e�B�b�N�e�L�X�g�̕`��ϐ���������
	m_lap_idc_f.SetString(L"00:00.000");
	m_lap_idc_h.SetString(L"00:00.000");
	m_lap_idc_j.SetString(L"00:00.000");

	//���x���`��ϐ���������
	m_label_count_lap_1 = 1;
	m_label_count_lap_2 = 1;
	m_label_count_lap_3 = 1;

	//���x���`����u�����N
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
// �^�C���J�E���^�[�̌v�Z����
//
/////////////////////////////////////////////////////////
CString CMy10_12_TImer_pre_1Dlg::ExecTimeCastProcess(void)
{
	DWORD s_tm = 0;
    DWORD e_tm = 0;
	float tm_sec = 0;
    int tm_min = 0;
	CString str;

	// �J�n/�I�����Ԃ��擾
	GetSysEndTime();
	e_tm = GetEndTime();
	s_tm = GetStartTime();

	// ss:mmm�\�L�ɕϊ�
	tm_sec = TimeSecConvert(e_tm, s_tm);

	// mm�\�L�ɕϊ�
	tm_min = TimeMinConvert(e_tm, s_tm);

	// �\���t�H�[�}�b�g�ɃL���X�g
	str.Format(L"%02d:%02.3f",tm_min ,tm_sec);

	//***********************************************************
	// @@@@ �ǉ������F�t�@�C���o�͍\���̂ɃX�v���b�g�f�[�^��ۑ�
	//***********************************************************

	FileSave[(GetLabelLapCount(__LABEL_COUNT_LAP_1))-1].svesplittime = (float)tm_min + tm_sec;

	return str;

}

////////////////////////////////////////////////////////////
//
// ���b�v�^�C���J�E���^�[�̌v�Z����
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

	// �J�n/�I�����Ԃ��擾
	GetSysEndTime();
	e_tm = GetEndTime();
	s_tm = GetStartTime();

	elap_tm = GetElapsedTime();

	// ���񏈗�
	if(m_elapsed_laptime == 0){
	    m_elapsed_laptime = (e_tm - s_tm);
	// ss:mmm�\�L�ɕϊ�
	tm_sec = LapTimeSecConvert(GetElapsedLapTime());

	// mm�\�L�ɕϊ�
	tm_min = LapTimeMinConvert(GetElapsedLapTime());

	// �\���t�H�[�}�b�g�ɃL���X�g
	str.Format(L"%02d:%02.3f",tm_min ,tm_sec);

	}
	else{
		// ���� - �ߋ�
	    lap_tm = (e_tm - s_tm) - GetElapsedLapTime();

		m_elapsed_laptime = e_tm - s_tm ;
	    // ss:mmm�\�L�ɕϊ�
	    tm_sec = LapTimeSecConvert(lap_tm);

	    // mm�\�L�ɕϊ�
	    tm_min = LapTimeMinConvert(lap_tm);

	    // �\���t�H�[�}�b�g�ɃL���X�g
	    str.Format(L"%02d:%02.3f",tm_min ,tm_sec);

	}

	//***********************************************************
	// @@@@@ �ǉ�����:���b�v�^�C�����t�@�C���\���̂ɕۑ�
    //***********************************************************

	// ���b�v���x���J�E���g�̏����l=1�̂��߁A-1����
	FileSave[(GetLabelLapCount(__LABEL_COUNT_LAP_1))-1].savelaptime = (float)tm_min + tm_sec;

	time_t rtime = 0;
	time_t atime = 0;

	// ���ݎ������擾
	rtime = time(&atime);
		if(rtime == -1){
		return str;
	}

	errno_t error;

	// �O���[�o���^�C�������[�J���^�C���ɕϊ�
	struct tm strtim;
	error = localtime_s(&strtim,&rtime);

	char ascstr[40];
	asctime_s(ascstr,sizeof(ascstr),&strtim);

	// �o�̓t�@�C���\���̂ɕۑ�
	asctime_s(FileSave[(GetLabelLapCount(__LABEL_COUNT_LAP_1))-1].localtime,sizeof(FileSave[(GetLabelLapCount(__LABEL_COUNT_LAP_1))-1].localtime),&strtim);

	return str;
}

///////////////////////////////////////////////////////////////////
//
// �X�^�e�B�b�N�e�L�X�g�̕`�揈��
//
///////////////////////////////////////////////////////////////////
void CMy10_12_TImer_pre_1Dlg::DrawStaticText(CString *str, int enm)
{

	switch (enm)
	{
	case __IDC_STATIC_A:
		//IDC_STATIC_A�̕`��
		m_counter = *str;
		break;
	case __IDC_STATIC_B:
		//IDC_STATIC_B�̕`��
		m_lap_1 = *str;
		break;
	case __IDC_STATIC_F:
		//IDC_STATIC_F�̕`��
		m_lap_idc_f = *str;
		break;
	case __IDC_STATIC_H:
		//IDC_STATIC_H�̕`��
		m_lap_idc_h = *str;
		break;
	case __IDC_STATIC_J:
		//IDC_STATIC_J�̕`��
	    m_lap_idc_j = *str;
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////////////////////////
//
// ss:SSS�\�L�ɕϊ�
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
// ss:SSS�\�L�ɕϊ�
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
// mm�\�L�ɕϊ�
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
// mm�\�L�ɕϊ�
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
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
}


HBRUSH CMy10_12_TImer_pre_1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

   // ��è��÷�Ă̐F�ύX	
    if (nCtlColor == CTLCOLOR_STATIC )	
		if (*pWnd == m_static_a_color ||*pWnd == m_static_b_color ||*pWnd ==  m_static_f_color ||*pWnd == m_static_j_color)	
        {	
            // �����F	
            pDC->SetTextColor(RGB(0, 255, 65));	
            // �w�i�F	
            hbr = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));	
            pDC->SetBkColor(RGB(0, 0, 0));	
        }	
		if (*pWnd ==  m_static_h_color || *pWnd == m_static_j_color)
		{
            // �����F	
            pDC->SetTextColor(RGB(0, 150, 65));	
            // �w�i�F	
            hbr = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));	
            pDC->SetBkColor(RGB(0, 0, 0));			
		}
			return hbr;
}


///////////////////////////////////////////////////////
//
// ���b�v���x���̃J�E���g�����擾
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
// ���b�v���x���̃J�E���g����Ԃ�
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
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	//***********************************************************
	// @@@@ �ǉ������F�t�@�C���o�͏���
	//***********************************************************

	if(FileSave[0].savelaptime == 0){
		// ���b�v�{�^���������Ȃ��ꍇ�̓t�@�C���I�[�v�����Ȃ�
	}
	else {

		// �t�H���_���쐬
		char *dir = __FOLDER_PATH_1;

		if (_mkdir(dir) == 0){
		}
		else {
		}

		// �t�@�C���I�[�v��
		FILE *fp = 0;
		char file[50];
		int i = 0;

		struct stat buf;

		time_t rtime = 0;
		time_t atime = 0;

		// ���ݎ������擾
		rtime = time(&atime);
			if(rtime == -1){
			
		}
		tm tim;
		errno_t error;
		error = localtime_s(&tim,&rtime);

		// �t�@�C���̑��݂��m�F����
		do
		{
			i++;
			sprintf_s(file,"C:\\MFC_Debug_Stopwatch\\Stopwatch-%d%d-%d.txt",tim.tm_mon,tim.tm_mday,i) ;
		} while (stat(file, &buf) == 0);
		 
		fopen_s(&fp, file, "w");


		// �\���̂̃|�C���^
		filesave *pFileSave;
		pFileSave = FileSave;

		// �v���f�[�^�̓���/���b�v�^�C��/�X�v���b�g�^�C�����t�@�C���ɏo��
		for (int i =0; i < (GetLabelLapCount(__LABEL_COUNT_LAP_1))-1; ++i){
			fprintf(fp,"%s Laptime%d�F%g SplitTime%d : %g\n", (pFileSave+i)->localtime, i+1,(pFileSave+i)->savelaptime, i +1,(pFileSave+i)->svesplittime);
		}

		// �t�@�C���N���[�Y
		fclose(fp);

	}

	CDialogEx::OnOK();
}
