
// HuffmanMsg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHuffmanMsgApp: 
// �йش����ʵ�֣������ HuffmanMsg.cpp
//

class CHuffmanMsgApp : public CWinApp
{
public:
	CHuffmanMsgApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHuffmanMsgApp theApp;
