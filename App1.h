
// App1.h : главный файл заголовка для приложения App1
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CApp1App:
// О реализации данного класса см. App1.cpp
//

class CApp1App : public CWinApp
{
public:
	CApp1App();


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CApp1App theApp;
