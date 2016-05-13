// DlgProps.cpp: файл реализации
//

#include "stdafx.h"
#include "App1.h"
#include "DlgProps.h"
#include "afxdialogex.h"


// диалоговое окно CDlgProps

IMPLEMENT_DYNAMIC(CDlgProps, CDialogEx)

CDlgProps::CDlgProps(double angle, double A, double A1, double A2, double A3, CWnd* pParent)
:  m_Angle(angle), m_A(A), m_A1(A1), m_A2(A2), m_A3(A3), CDialogEx(IDD_PROPS, pParent) {
}

CDlgProps::~CDlgProps()
{
}

void CDlgProps::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_A);
	DDV_MinMaxDouble(pDX, m_A, 50, 1000);
	DDX_Text(pDX, IDC_EDIT2, m_A1);
	DDX_Text(pDX, IDC_EDIT4, m_A3);
	DDX_Text(pDX, IDC_EDIT3, m_Angle);
	DDX_Text(pDX, IDC_EDIT5, m_A2);
}


BEGIN_MESSAGE_MAP(CDlgProps, CDialogEx)
END_MESSAGE_MAP()


// обработчики сообщений CDlgProps
