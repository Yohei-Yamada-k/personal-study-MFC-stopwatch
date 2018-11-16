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
// SetTimer�ɌĂ΂��^�C�}�[�C�x���g����
//
//////////////////////////////////////////////////////////////////////////
void CMy10_12_TImer_pre_1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	UpdateData(FALSE);
	
	CString str;
	DWORD s_tm = 0;
    DWORD e_tm = 0;
	
	str = ExecTimeCastProcess();
	DrawStaticText(&str,__IDC_STATIC_A);

	e_tm = GetEndTime();
	s_tm = GetStartTime();
	
	// �^�C�}�[�J�E���g�̏��
	if(((e_tm - s_tm) +m_elapsed_time) > 3600000){

		StopTimer();

		// �G���[�R�[�h�\��
		StopWatch_Assert Assert;
		Assert.ExecAssert(__ERR_CODE002);

		//���b�v�{�^����������
		CButton *button1=(CButton*)GetDlgItem(IDC_BUTTON1);
		button1->EnableWindow(FALSE);

	}

	CDialogEx::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////////////
//
// �^�C�}�[��~����
//
//////////////////////////////////////////////////////////////////////////
int CMy10_12_TImer_pre_1Dlg::StopTimer(void)
{
	// �^�C�}�[���~
	KillTimer(1);

	// �o�ߎ��Ԃ�ۑ�
	SetElapsedTime();

	if(Laptime_count_over == true){
		// �N���A�{�^�����\��
		CButton *button3=(CButton*)GetDlgItem(IDC_BUTTON3);
	    button3->EnableWindow(TRUE);

	}
	else {
		// ���b�v�{�^�����\��
		// �N���A�{�^����������
		CButton *button2=(CButton*)GetDlgItem(IDC_BUTTON2);
		button2->EnableWindow(FALSE);
		CButton *button3=(CButton*)GetDlgItem(IDC_BUTTON3);
		button3->EnableWindow(TRUE);
	}

	// �X�^�[�g�{�^���̏�Ԃ�ύX
	Stop_Enable = false;

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
// �V�X�e���������J�n���ԂƂ��Ď擾
//
//////////////////////////////////////////////////////////////////////////
void CMy10_12_TImer_pre_1Dlg::GetSysStartTime(void)
{
	m_start_time = timeGetTime();
}

//////////////////////////////////////////////////////////////////////////
//
// �V�X�e���������I�����ԂƂ��Ď擾
//
//////////////////////////////////////////////////////////////////////////
void CMy10_12_TImer_pre_1Dlg::GetSysEndTime(void)
{
	m_end_time = timeGetTime();
}

//////////////////////////////////////////////////////////////////////////
//
// �o�ߎ��Ԃ��擾
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