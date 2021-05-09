
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "FigureMove.h"
#include "ChildView.h"

#define RED 1
#define BLUE 2

#define CIRCLE 10
#define RECT   11	


// CChildView

CChildView::CChildView()
{
	// 전체적인 초기화

	show = false;
	curIndex = 0;

	const int XPOS = 600;
	int radius = 30;
	int x = XPOS;
	int y = 100;

	// 5 ~ 10
	count = ( rand() %  6 ) + 5;

	for (int i = 0; i < count; i++)
	{
		if (i % 2 == 0)
		{
			y += 80;
			x = XPOS;
		}

		figures[i].Initialize(x, y, radius);
		rgns[i].CreateEllipticRgn(x - radius, y - radius, x + radius, y + radius);
		figures[i].startX = x;
		figures[i].startY = y;

		x += 80;

	}

	redBox.SetRectangle(50, 150, 350, 700);
	redRgn.CreateEllipticRgn(50, 150, 350, 700);
	redBox.SetColor(RED);

	blueBox.SetRectangle(1050, 150, 1350, 700);
	blueRgn.CreateEllipticRgn(1050, 150, 1350, 700);
	blueBox.SetColor(BLUE);



}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	//	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_COMMAND(ID_LOAD_CALCULATOR, &CChildView::OnLoadCalculator)
	ON_COMMAND(ID_LOAD_GAME, &CChildView::OnLoadGame)
	ON_COMMAND(ID_LOAD_WEP, &CChildView::OnLoadWep)
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
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (show == false)
		return;

	SetTimer(0, 60, NULL);

	// 도형들을 그립니다.
	redBox.Draw(&dc,   RECT);
	blueBox.Draw(&dc,  RECT);

	for (int i = 0; i < count; i++)
	{
		figures[i].Draw(&dc, 10);
	}


	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPoint pt;
	::GetCursorPos(&pt);
	ScreenToClient(&pt);

	for (int i = 0; i < count; i++)
	{
		// 클릭한객체를 알기위해 checked로 구분해둡니다. 그후 MOVE나 UP에서 사용합니다.
		if (rgns[i].PtInRegion(pt) && figures[i].good != true)
		{
			figures[i].checked = true;
			curIndex = i;
			
			break;
		}
	}

	CWnd::OnLButtonDown(nFlags, point);

}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (figures[curIndex].checked == false)
	{
		return;
	}

	CPoint pt;
	::GetCursorPos(&pt);
	ScreenToClient(&pt);

	int x = figures[curIndex].x;
	int y = figures[curIndex].y;
	int radius = figures[curIndex].radius;;


	// 버튼이 UP 될시 마우스가 바구니 안에 들어있고 
	// 박스와 원의 색이 다르다면 에러를 호출한다.
	if (redRgn.PtInRegion(pt) && figures[curIndex].color != 1)
	{
		MessageBox(_T("에러지롱~~~메렁메렁"), _T("떙!!!!!!!"));
		// 초기화
		x = figures[curIndex].startX;
		y = figures[curIndex].startY;
	}
	else if (blueRgn.PtInRegion(pt) && figures[curIndex].color != 2)
	{
		MessageBox(_T("에러지롱~~~메렁메렁"), _T("떙!!!!!!!"));
		x = figures[curIndex].startX;
		y = figures[curIndex].startY;
	}
	
	// 움직임이 끝난후 위치와 Rgns를 초기화하 하며 chekced를 해제한다.
	figures[curIndex].SetPos(x, y);
	rgns[curIndex].SetRectRgn(x - radius, y - radius, x + radius, y + radius);
	figures[curIndex].checked = false;

	// 움직임이 끝난후 맞는 상자에 들어갔다면 더이상 선택할수 없게된다.
	if (redRgn.PtInRegion(pt) && figures[curIndex].color == 1)
	{
		figures[curIndex].good = true;
	}
	else if (blueRgn.PtInRegion(pt) && figures[curIndex].color == 2)
	{
		figures[curIndex].good = true;
	}

	
	if (GameFinish())
	{
		MessageBox(_T("게임에서 승리하였다!!!"), _T("Victory"));
	}
	

	CWnd::OnLButtonUp(nFlags, point);
}

// 마우스가 Move 중일때 checked 상태라면 원을 지속적으로 움직인다.
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{

	CPoint pt;
	::GetCursorPos(&pt);
	ScreenToClient(&pt);

	if (figures[curIndex].checked)
	{
		figures[curIndex].SetPos(pt.x, pt.y);
	}


	CWnd::OnMouseMove(nFlags, point);
}


// 계산기 실행
void CChildView::OnLoadCalculator()
{
	
	::ShellExecute(NULL, _T("open"), _T("C:\Windows\\System32\\calc.exe"), NULL, NULL, SW_SHOW);
}
// 게임 실행
void CChildView::OnLoadGame()
{
	show = true;
	Invalidate();
	
}
// 웹페이지 실행
void CChildView::OnLoadWep()
{
	::ShellExecute(NULL, _T("open"), _T("http://cyber.jj.ac.kr/"), NULL, NULL, SW_SHOW);

}

void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	Invalidate();

	CWnd::OnTimer(nIDEvent);
}