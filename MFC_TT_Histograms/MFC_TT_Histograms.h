
// MFC_TT_Histograms.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CMFC_TT_HistogramsApp:
// �аѾ\��@�����O�� MFC_TT_Histograms.cpp
//

class CMFC_TT_HistogramsApp : public CWinApp
{
public:
	CMFC_TT_HistogramsApp();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CMFC_TT_HistogramsApp theApp;