
// ConnectPlayerMFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CConnectPlayerMFCApp: 
// �йش����ʵ�֣������ ConnectPlayerMFC.cpp
//

class CConnectPlayerMFCApp : public CWinApp
{
public:
	CConnectPlayerMFCApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CConnectPlayerMFCApp theApp;