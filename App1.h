
// App1.h : ������� ���� ��������� ��� ���������� App1
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"       // �������� �������


// CApp1App:
// � ���������� ������� ������ ��. App1.cpp
//

class CApp1App : public CWinApp
{
public:
	CApp1App();


// ���������������
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����������

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CApp1App theApp;
