
// DFM.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDFMApp:
// �йش����ʵ�֣������ DFM.cpp
//

class CDFMApp : public CWinApp
{
public:
	CDFMApp();
	CString pwd;
	CString name;
	_ConnectionPtr m_pConnect;//����access������

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDFMApp theApp;