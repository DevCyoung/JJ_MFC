// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Bitmaps.h"
#include "ChildView.h"
#include <iostream>
#include <math.h>
#include <string>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 기준선 14번째
// 한칸당 50


struct Vector {

public:
	int x = 0;
	int y = 0;
};


int location = 0;
int index = 0;

Vector ch_pos;

int val = 50;

int frame_speed = 50;

int STOP = 0;
int PLAY = 1;
int GRID = 1;

int STATE_CHECK = 0X00000001;		
int GRIGD_CHECK = 0X00000001;

CBitmap bitmap;
BITMAP bmpinfo;

// CChildView

int line = 10;

CChildView::CChildView()
{
	val = 50;

	bitmap.LoadBitmap(IDB_BITMAP1);
	bitmap.GetBitmap(&bmpinfo);

	ch_pos.x = val * 10 - bmpinfo.bmWidth / 2;
	ch_pos.y = val * 6 - bmpinfo.bmHeight / 2;
}

CChildView::~CChildView()
{
}

// 이곳은 메세지 맵이라고한다.
BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()  // 타이머 를 사용하기위해 등록하였다.
	ON_WM_DESTROY()

	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()

	ON_WM_KEYDOWN()
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

	// 1000 =>	  1초에 한번
	//   50 => 0.05초에 한번

	SetTimer(1, frame_speed, NULL);

	//Test
	if (GRIGD_CHECK & GRID)				//GRID 를 켜야함
	{
		for (int i = 0; i < 100; i++) {

			dc.MoveTo(i * val, 0);
			dc.LineTo(i * val, 2000);


			dc.MoveTo(0, i * val);
			dc.LineTo(2000, i * val);
		}
	}

	dc.MoveTo(val * 14, val * 3);
	dc.LineTo(val * 10, val * 6);
	dc.MoveTo(val * 14, val * 3);
	dc.LineTo(val * 18, val * 6);

	dc.MoveTo(val * 14, val * 9);
	dc.LineTo(val * 10, val * 6);
	dc.MoveTo(val * 14, val * 9);
	dc.LineTo(val * 18, val * 6);

	// 메모리 DC를 만든 후 비트맵을 선택해 넣는다.
	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc);
	dcmem.SelectObject(&bitmap);

	dc.BitBlt(ch_pos.x, ch_pos.y, bmpinfo.bmWidth, bmpinfo.bmHeight,
		&dcmem, 0, 0, SRCCOPY);

	// STOP 상태일때만 PAUSE 텍스트를 출력합니다.
	if (STATE_CHECK == STOP) {
		const TCHAR* msg = _T("PAUSE");
		dc.TextOut(val * 14 - val / 2, val * 6 - val / 2, msg, lstrlen(msg));
	}

	const TCHAR* msg = _T("스페이스바 : 그리드");
	dc.TextOut(val * 25 , val * 1 , msg, lstrlen(msg));
	msg = _T("마우스 : L정지 / R시작");
	dc.TextOut(val * 25 , val * 2, msg, lstrlen(msg));
	msg = _T("방향키 프레임조절");
	dc.TextOut(val * 25, val * 3, msg, lstrlen(msg));


}

// 타이머 함수
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	if (STATE_CHECK == STOP)
	{
		Invalidate();
		return;
	}
	else
	{

	}

	// 이동방법
	int select[4][2] =
	{
		{  4 ,-3 },
		{  4, 3 },
		{ -4, 3 },
		{ -4, -3 }
	};

	Invalidate();

	//  캐릭터의 이동방향
	ch_pos.x += select[index][0];
	ch_pos.y += select[index][1];

	// location 을 이동 거리로 생각하였습니다.
	location += 4;
	// 일정거리를 이동할때마다 이동방법을 바꿉니다.
	if (location % 200 == 0) {
		++index;
	}

	if (index > 3) {
		index	 = 0;
		location = 0;
	}

	CWnd::OnTimer(nIDEvent);
}

// 왼쪽 버튼을 누르면 STOP
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	STATE_CHECK = STOP;

	CWnd::OnLButtonDown(nFlags, point);
}

// 오른쪽 버튼을 누르면 PLAY
void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{

	STATE_CHECK = PLAY;

	CWnd::OnRButtonDown(nFlags, point);

}

// 테스트중
void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int tempt = frame_speed;
	switch (nChar)
	{
	case VK_UP:
		frame_speed -= 10;
		break;
	case VK_DOWN:
		frame_speed += 10;
		break;
	// 그리드 켜기 or 지우기
	case VK_SPACE:
		GRIGD_CHECK ^= GRID;
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