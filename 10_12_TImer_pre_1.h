
// 10_12_TImer_pre_1.h : PROJECT_NAME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��


// CMy10_12_TImer_pre_1App:
// ���̃N���X�̎����ɂ��ẮA10_12_TImer_pre_1.cpp ���Q�Ƃ��Ă��������B
//

class CMy10_12_TImer_pre_1App : public CWinApp
{
public:
	CMy10_12_TImer_pre_1App();

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CMy10_12_TImer_pre_1App theApp;