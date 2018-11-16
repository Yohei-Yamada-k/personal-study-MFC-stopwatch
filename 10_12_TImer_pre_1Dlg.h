
// 10_12_TImer_pre_1Dlg.h : �w�b�_�[ �t�@�C��
//

#pragma once
#include "afxwin.h"

// CMy10_12_TImer_pre_1Dlg �_�C�A���O
class CMy10_12_TImer_pre_1Dlg : public CDialogEx
{
// �R���X�g���N�V����
public:
	CBrush m_brDlg;		// �_�C�A���O�̔w�i�F�u���V(������ǉ�����)
	CMy10_12_TImer_pre_1Dlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^�[

// �_�C�A���O �f�[�^
	enum { IDD = IDD_MY10_12_TIMER_PRE_1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	//�^�C���J�E���^�[�v�Z����
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:

	// �V�X�e�����Ԃ��擾
	void GetSysStartTime(void);
	void GetSysEndTime(void);

	//�^�C�}�[�J�n���Ԃ��擾
	DWORD GetStartTime(void){
		return m_start_time;	
	};

	//�^�C�}�[��~���Ԃ��擾
	DWORD GetEndTime(void){
		return m_end_time;
	};

	//�^�C�}�[�o�ߎ��Ԃ�ۑ�
	DWORD SetElapsedTime(void);

	//�^�C�}�[�o�ߎ��Ԃ��擾
	DWORD GetElapsedTime(void){
		return m_elapsed_time;
	};

	// �������`�悷��
	void DrawStaticText(CString* str, int enm);

	// ���b�v2�̕������Ԃ�
	CString GetSrtIdcHValue(void){
		return m_str_idc_h_value;
	}
	void SetStrIdcHValue(CString str);

	// ���b�v3�̕������Ԃ�
	CString GetStrIdcJValue(void){
		return m_str_idc_j_value;
	}
	void SetStrIdcJValue(CString str);

	// mm:ss:SS�\�L�ɕϊ�
	float TimeSecConvert(DWORD e_conv, DWORD s_conv);
	int TimeMinConvert(DWORD e_conv, DWORD s_conv);

	// LapTime��mm:ss:SS�\�L�ɕϊ�
	float LapTimeSecConvert(DWORD conv);
	int LapTimeMinConvert(DWORD conv);

	// �^�C�}�[��~�֐�
	int StopTimer(void);

	// ���ԕ\���̃L���X�g����
	CString ExecTimeCastProcess(void);

	// ���b�v���ԕ\���̃L���X�g����
	CString ExecLapTimeCastProcess(void);

	int GetLabelLapCount(int def);
	void SetLabelLapCount(int def, int count);

	// �`�揈���̃��b�Z�[�W�n���h��
	afx_msg void OnStnClickedStaticB();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	// ���b�v�̃t���O
	bool Laptime_On;
	// �^�C�[�}�[��Ԃ̃t���O
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

	// �w�i�E�t�H���g�̕`�揈���ϐ�
	CStatic m_static_a_color;
	CStatic m_static_b_color;
	CStatic m_static_f_color;
	CStatic m_static_h_color;
	CStatic m_static_j_color;

	// �X�^�e�B�b�N�e�L�X�g�̕`��ϐ�
	CString m_counter;// ���b�v�J�E���^�[
	CString m_lap_1; // ���b�v�^�C��
	CString m_lap_idc_f;
	CString m_lap_idc_h;
	CString m_lap_idc_j;

	// ���b�v���x���̕`��ϐ�
	CString m_label_lap_1;
	CString m_label_lap_2;
	CString m_label_lap_3;

	// ���b�v2��String
	CString m_str_idc_h_value;
	// ���b�v3��String
	CString m_str_idc_j_value;

	// ���b�v���x���̃J�E���g�ϐ�
	int m_label_count_lap_1;
	int m_label_count_lap_2;
	int m_label_count_lap_3;

public:
	DWORD GetElapsedLapTime(void){
		return m_elapsed_laptime;
	}
};
