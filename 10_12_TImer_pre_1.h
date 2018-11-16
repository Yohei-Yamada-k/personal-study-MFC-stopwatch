
// 10_12_TImer_pre_1.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMy10_12_TImer_pre_1App:
// このクラスの実装については、10_12_TImer_pre_1.cpp を参照してください。
//

class CMy10_12_TImer_pre_1App : public CWinApp
{
public:
	CMy10_12_TImer_pre_1App();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMy10_12_TImer_pre_1App theApp;