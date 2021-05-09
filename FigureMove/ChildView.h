
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once

#include "Figure.h"

// CChildView 창

class CChildView : public CWnd
{

// 생성입니다.
public:

	CChildView();

	bool show;

	int count;
	
	Figure figures[10];
	CRgn	rgns[10];


	Figure redBox;
	CRgn	redRgn;
	Figure blueBox;
	CRgn	blueRgn;
	
	int curIndex;
	

public:
	// 모든공이 알맞은 상자에 들어갔는지 체크합니다.
	bool GameFinish()
	{

		for (int i = 0; i < count; i++)
		{
			if (figures[i].good == false)
				return false;
		}
		return true;

	}


	


	

	

// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnLoadCalculator();
	afx_msg void OnLoadGame();
	afx_msg void OnLoadWep();
};

