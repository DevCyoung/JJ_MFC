
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "ChangeCursor.h"
#include "ChildView.h"
#include  <atlstr.h>
#include "time.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	//	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	CString str;


	//3개의 비트맵을 그립니다.
	for (int i = 0; i < 3; i++) {

		CBitmap bitmap;
		BITMAP bmpinfo;
		bitmap.LoadBitmap(FRUITS_NUM + i);
		bitmap.GetBitmap(&bmpinfo);
		CDC dcmem;
		dcmem.CreateCompatibleDC(&dc);
		dcmem.SelectObject(&bitmap);

		int X1 = rect.right / 4;
		int Y1 = rect.bottom / 4;

		dc.BitBlt( 100+i * X1, Y1 , bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
	}

	for (int i = 0; i < 3; i++) {
		str.Format(_T("%d"), fruits_counts[i]);
		dc.TextOut(180 + i * rect.right / 4, rect.bottom / 4 -30, str);
		dc.TextOut(100 + i * rect.right / 4, rect.bottom / 4 -30, fruits_names[i]);
	}

}

BOOL CChildView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{

	if (nHitTest == HTCLIENT) {
		
		CPoint point;
		::GetCursorPos(&point); 
		ScreenToClient(&point); 

		CRect rect;
		GetClientRect(&rect);
		
		CBitmap bitmap;
		BITMAP bmpinfo;
		bitmap.LoadBitmap(FRUITS_NUM);
		bitmap.GetBitmap(&bmpinfo);
		
		//영역을 3개 생성합니다.
		CRgn apple;
		CRgn banana;
		CRgn strawberry;

		int X1 = rect.right / 4;
		int Y1 = rect.bottom / 4;

		apple.CreateRectRgn	(	 100 + 0 * X1, Y1, (100 + 0 * X1) + bmpinfo.bmWidth, Y1 + bmpinfo.bmHeight);
		banana.CreateRectRgn(	 100 + 1 * X1, Y1, (100 + 1 * X1) + bmpinfo.bmWidth, Y1 + bmpinfo.bmHeight);
		strawberry.CreateRectRgn(100 + 2 * X1, Y1, (100 + 2 * X1) + bmpinfo.bmWidth, Y1 + bmpinfo.bmHeight);

		// 마우스가 각 과일에 닿았는지 체크합니다.
		fruits_chekcs[0] = apple.PtInRegion(point);
		fruits_chekcs[1] = banana.PtInRegion(point);
		fruits_chekcs[2] = strawberry.PtInRegion(point);

		// 3개중 하나라도 닿으면 커서가 변합니다.
		if (fruits_chekcs[0] || fruits_chekcs[1] || fruits_chekcs[2])
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR1));
		else
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
		return TRUE;
	}


	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{

	// 체크중인 과일이있다면 그 과일을 카운팅합니다.
	for (int i = 0; i < 3; i++) {
		if (fruits_chekcs[i])
			++fruits_counts[i];
	}

	Invalidate(FALSE);
	CWnd::OnLButtonDown(nFlags, point);
}
