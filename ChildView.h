
// ChildView.h : интерфейс класса CChildView
//


#pragma once
#include "Header.h"
#include <vector>
#include "DlgProps.h"


// окно CChildView

class CChildView : public CWnd
{
// Создание
public:
	CChildView();

// Атрибуты
protected:
	std::vector<CMy2DObject*> m_Objects;
	int m_nCatched;
	CPoint m_MousePos;
	int FindObject(CPoint point) {
		int nObj = -1;
		for (int i = m_Objects.size() - 1; i >= 0; i--) {
			if (m_Objects[i]->IsInside(point.x, point.y)) {
				nObj = i;
			}
		}
	return nObj;
	}
	

// Операции
public:

// Переопределение
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	

// Реализация
public:
	virtual ~CChildView();

	// Созданные функции схемы сообщений
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNewObj();
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
};

