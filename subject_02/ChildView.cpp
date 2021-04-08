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

	ch_pos.x = inter * 10  - bmpinfo.bmWidth  / 2;   // 중앙 정렬  - bmpinfo.bmWidth  / 2
	ch_pos.y = inter * 6   - bmpinfo.bmHeight / 2;   // 중앙 정렬  - bmpinfo.bmHeight / 2
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
	SetTimer(1, frame_speed, NULL);
	//VIEW GRID
	if (SCREEN_STATE & GRID)				
	{
		for (int i = 0; i < 30; i++) {

			dc.MoveTo(i * inter, 0);
			dc.LineTo(i * inter, 2000);

			dc.MoveTo(0,	i * inter);
			dc.LineTo(2000, i * inter);
		}
	}

	//DRAW RHOMBUS
	dc.MoveTo(inter * 14, inter * 3);
	dc.LineTo(inter * 10, inter * 6);
	dc.MoveTo(inter * 14, inter * 3);
	dc.LineTo(inter * 18, inter * 6);

	dc.MoveTo(inter * 14, inter * 9);
	dc.LineTo(inter * 10, inter * 6);
	dc.MoveTo(inter * 14, inter * 9);
	dc.LineTo(inter * 18, inter * 6);

	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc);
	dcmem.SelectObject(&bitmap);

	dc.BitBlt(ch_pos.x, ch_pos.y, bmpinfo.bmWidth, bmpinfo.bmHeight,
		&dcmem, 0, 0, SRCCOPY);

	//PAUSE
	if ( (SCREEN_STATE & PLAY) == 0) {
		const TCHAR* msg = _T("PAUSE");
		dc.TextOut(inter * 14 - inter / 2, inter * 6 - inter / 2, msg, lstrlen(msg));
	}

	//DRAW TEXT
	const TCHAR* msg = _T("스페이스바 : 그리드");
	dc.TextOut(inter * 25 , inter * 1 , msg, lstrlen(msg));
	msg = _T("마우스 : L정지 / R시작");
	dc.TextOut(inter * 25 , inter * 2, msg, lstrlen(msg));
}

// <summary>
// 1000 =>	  1초에 한번 호출
// 50   =>	  0.05초에 한번 호출
// </summary>
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	Invalidate();

	//CHECK PLAY
	if ( (SCREEN_STATE & PLAY) == 0 )
	{
		return;
	}

	//MOVE CHARACTOR
	ch_pos.x += direction[dir_index][0];
	ch_pos.y += direction[dir_index][1];

	//MOVE_SIZE
	moveScale += 4;

	//SWITCH MOVEDIR
	if (moveScale % 200 == 0) {
		++dir_index;
	}

	if (dir_index > 3) {
		dir_index	 = 0;
		moveScale = 0;
	}

	CWnd::OnTimer(nIDEvent);
}

// 왼쪽 버튼을 누르면 STOP
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (SCREEN_STATE & PLAY)
	{
		SCREEN_STATE ^= PLAY;
	}

	CWnd::OnLButtonDown(nFlags, point);
}

// 오른쪽 버튼을 누르면 PLAY
void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	SCREEN_STATE |= PLAY;
	CWnd::OnRButtonDown(nFlags, point);
}

// 테스트중
void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	// ON GRID , OFF RGID
	case VK_SPACE:
		SCREEN_STATE ^= GRID;
		break;
	// START
	case VK_CONTROL:
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