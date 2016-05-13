#pragma once


// диалоговое окно CDlgProps

class CDlgProps : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgProps)

public:
	CDlgProps(double angle = 0, double A = 300, double A1 = 100, double A2= 100, double A3=100, CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CDlgProps();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	double m_A;
	double m_A1;
	double m_A2;
	double m_A3;
	double m_Angle;
	
};
