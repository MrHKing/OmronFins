
// OmronFins.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// COmronFinsApp:
// �йش����ʵ�֣������ OmronFins.cpp
//

class COmronFinsApp : public CWinApp
{
public:
	COmronFinsApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern COmronFinsApp theApp;