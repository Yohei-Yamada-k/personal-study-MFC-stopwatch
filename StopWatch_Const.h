#pragma once
#include "afxwin.h"

// �G���[�R�[�h
#define __ERR_CODE001 1
#define __ERR_CODE002 2

// �X�^�e�B�b�N
#define __IDC_STATIC_A 0
#define __IDC_STATIC_B 1
#define __IDC_STATIC_F 2
#define __IDC_STATIC_H 3
#define __IDC_STATIC_J 4
#define __IDC_STATIC_MAX 5

// ���x��
#define __LABEL_COUNT_LAP_1 1
#define __LABEL_COUNT_LAP_2 2
#define __LABEL_COUNT_LAP_3 3

// ���b�v�J�E���g
#define __LAP_COUNT_MAX 99

// �o�̓t�H���_�p�X
#define __FOLDER_PATH_1 "C:\\MFC_Debug_Stopwatch"

//�o�̓t�@�C���\����
typedef struct
{
	char localtime[32];
	float savelaptime;
	float svesplittime;
} filesave;