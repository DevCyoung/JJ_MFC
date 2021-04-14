// ChildView.cpp: CChildView 클래스의 구현
#include "pch.h"
#include "framework.h"
#include "Bitmaps.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CBitmap bitmap;
BITMAP bmpinfo;

// CChildView
CChildView::CChildView()
{
	bitmap.LoadBitmap(IDB_BITMAP1);
	bitmap.GetBitmap(&bmpinfo);

	//Position Init
	ch_pos.x = INTER * 10  - bmpinfo.bmWidth  / 2;   // 중앙 정렬  - bmpinfo.bmWidth  / 2
	ch_pos.y = INTER * 6   - bmpinfo.bmHeight / 2;   // 중앙 정렬  - bmpinfo.bmHeight / 2
}

CChildView::~CChildView()
{
}

// 이곳은 메세지 맵이라고한다.
BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()  
	ON_WM_KEYDOWN()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
END_MESSAGE_MAP()

// CChildView 메시지 처리기
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW),
		reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this);

	SetTimer(1, FRAME_SPEED, NULL);

	//GRID
	if (SCREEN_STATE & GRID)				
	{
		for (int i = 0; i < 30; i++) {

			dc.MoveTo(i	* INTER, 0);
			dc.LineTo(i	* INTER, 2000);

			dc.MoveTo(0	  , i * INTER);
			dc.LineTo(2000, i * INTER);
		}
	}

	//DRAW RHOMBUS
	if (SCREEN_STATE & RHOMBUS)
	{
		dc.MoveTo(INTER * 14, INTER * 3);
		dc.LineTo(INTER * 10, INTER * 6);
		dc.MoveTo(INTER * 14, INTER * 3);
		dc.LineTo(INTER * 18, INTER * 6);

		dc.MoveTo(INTER * 14, INTER * 9);
		dc.LineTo(INTER * 10, INTER * 6);
		dc.MoveTo(INTER * 14, INTER * 9);
		dc.LineTo(INTER * 18, INTER * 6);
	}

	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc);
	dcmem.SelectObject(&bitmap);

	dc.BitBlt(ch_pos.x, ch_pos.y, bmpinfo.bmWidth, bmpinfo.bmHeight,
		&dcmem, 0, 0, SRCCOPY);

	//PAUSE
	if ( (SCREEN_STATE & PLAY) == 0) {
		const TCHAR* msg = _T("PAUSE");
		dc.TextOut(INTER * 14 - INTER / 2, INTER * 6 - INTER / 2, msg, lstrlen(msg));
	}

	//DRAW TEXT
	const TCHAR* msg = _T("스페이스바 : 그리드");
	dc.TextOut(INTER * 25 , INTER * 1, msg, lstrlen(msg));
	msg = _T("마우스 : L정지 / R시작");
	dc.TextOut(INTER * 25 , INTER * 2, msg, lstrlen(msg));
	msg = _T("마우스휠 : RHOMBUS");
	dc.TextOut(INTER * 25,  INTER * 3, msg, lstrlen(msg));
}

// <summary>
// 1000 =>	  1초에 한번 호출
// 50   =>	  0.05초에 한번 호출
// </summary>
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	Invalidate();

	//CHECK PLAY
	if ( SCREEN_STATE & PLAY  )
	{

		//MOVE 
		ch_pos.x += DIRECTION[dirIndex][0];
		ch_pos.y += DIRECTION[dirIndex][1];

		//MOVE SCALE
		moveScale += 4;

		//SWITCH DIR
		if (moveScale % 200 == 0) {
			++dirIndex;
		}


		if (dirIndex > 3) {
			dirIndex = 0;
			moveScale = 0;
		}
		
	}

	CWnd::OnTimer(nIDEvent);
}

//STOP
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (SCREEN_STATE & PLAY)
		SCREEN_STATE ^= PLAY;
	

	CWnd::OnLButtonDown(nFlags, point);
}

//PLAY
void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	SCREEN_STATE |= PLAY;
	CWnd::OnRButtonDown(nFlags, point);
}




	// ON GRID , OFF RGID
void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_SPACE:
		SCREEN_STATE ^= GRID;
		break;
	default:
		break;
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CChildView::OnDestroy()
{
	KillTimer(1);
	CWnd::OnDestroy();
}

//RHOMBUS
void CChildView::OnMButtonDown(UINT nFlags, CPoint point)
{
	SCREEN_STATE ^= RHOMBUS;
	CWnd::OnMButtonDown(nFlags, point);
}
