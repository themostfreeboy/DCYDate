
// DCY_Date.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDCY_DateApp:
// �йش����ʵ�֣������ DCY_Date.cpp
//

class CDCY_DateApp : public CWinApp
{
public:
	CDCY_DateApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDCY_DateApp theApp;