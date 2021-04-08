// ChildView.h: CChildView 클래스의 인터페이스
//
#pragma once
// CChildView 창
class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:

	//CHARACTOR POSITION
	struct Vector {
	public:
		int x = 0;
		int y = 0;
	};

	const int inter = 50;
	const int frame_speed = 25;
	const int PLAY		 = 0X00000001;
	const int GRID		 = 0X00000002;

	const int direction[4][2] =
	{
		{  4 ,-3 },
		{  4,  3 },
		{ -4,  3 },
		{ -4, -3 }
	};

	int SCREEN_STATE = 0X00000003;	//On Play , On GRID

	int dir_index = 0;
	int moveScale = 0;

	Vector ch_pos;


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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

