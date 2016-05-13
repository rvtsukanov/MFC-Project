
// ChildView.cpp : реализация класса CChildView
//

#include "stdafx.h"
#include "App1.h"
#include "ChildView.h"
//#include "Header.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CChildView::~CChildView(){
	for (int i(0); m_Objects.size(); i++) {
		delete m_Objects[i];
	}
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_NEWOBJ, OnNewObj)
	ON_WM_MBUTTONDBLCLK()
END_MESSAGE_MAP()



// обработчики сообщений CChildView
BOOL CChildView::OnEraseBkgnd(CDC* pDC) {
	return true;
}
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

CChildView::CChildView(){ 
	m_nCatched = -1;
};

void CChildView::OnNewObj() {
	CRect rect;
	GetClientRect(&rect);
	CMy2DPoint C(400, 400);
	m_Objects.push_back(new CMy2DObject(C, 0, 300, 100, 100, 100));
	Invalidate();
}

void CChildView::OnPaint() {
	CPaintDC dc(this); // device context for drawing 
	CDC dcMem; 
	dcMem.CreateCompatibleDC(&dc); 
	CRect rect; GetClientRect(&rect); 
	CBitmap bmp; 
	bmp.CreateCompatibleBitmap(&dcMem, rect.Width(), rect.Height()); 
	CBitmap *pOldBmp = dcMem.SelectObject(&bmp); 
	dcMem.FillSolidRect(0,0,rect.Width(), rect.Height(), 0xFFFFFF); 
	
	for(int i=0; i<m_Objects.size(); i++){ 
		m_Objects[i]->Draw(dcMem); 
	} 
	dc.BitBlt(0,0, rect.Width(), rect.Height(), &dcMem, 0,0,SRCCOPY); 
	dcMem.SelectObject(pOldBmp); 
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point){
	m_nCatched = FindObject(point);
	if (m_nCatched >= 0) {
		m_MousePos = point;
		SetCapture();
	}
	
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point){
	m_nCatched = -1;
	ReleaseCapture();

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point){
	if (m_nCatched >= 0) {
		CRect rect; GetClientRect(&rect); 
		point.x = min(rect.right, max(rect.left, point.x)); 
		point.y = min(rect.bottom, max(rect.top, point.y));
		CPoint Delta;
		Delta = point - m_MousePos;
		m_Objects[m_nCatched] -> Move(Delta.x, Delta.y);
		m_MousePos = point;
		Invalidate();
	}
	

	CWnd::OnMouseMove(nFlags, point);
}


BOOL CChildView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	if (m_nCatched >= 0) {
		m_Objects[m_nCatched]->Rotate(zDelta/10);
		Invalidate();
		return CWnd::OnMouseWheel(nFlags, zDelta, pt);
	}
}


void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point){
	CMy2DPoint C;
	C.m_x = point.x;
	C.m_y = point.y;
	m_Objects.push_back(new CMy2DObject(C, 0, 300, 100, 100, 100));
	Invalidate();
	CWnd::OnMButtonDblClk(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point){
	for (int i(0); i < m_Objects.size(); i++) {
		CMy2DPoint C;
		C.m_x = point.x;
		C.m_y = point.y;
		if (m_Objects[i]->IsInside(C)) {
			delete m_Objects[i];
			Invalidate();
			break;
		}
	}
	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	for (int i(0); i < m_Objects.size(); i++) {
		if (m_Objects[i]->IsInside(point.x, point.y)) {
			CDlgProps Dlg(m_Objects[i]->GetA());
			if(Dlg.DoModal()){
				m_Objects[i]->SetFig(m_Objects[i]->GetCenter(), Dlg.m_Angle,  Dlg.m_A, 
					Dlg.m_A1, Dlg.m_A2, Dlg.m_A3);
				Invalidate();
			};
		}
	}
	CWnd::OnMButtonDblClk(nFlags, point);
}
