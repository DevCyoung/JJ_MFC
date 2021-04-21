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

	const int FRUITS_NUM = 312;
	const CString fruits_names[3] = { CString("사과 :") , CString("바나나 :") , CString("딸기 :") };
	int fruits_counts[3] = {0,0,0};
	bool fruits_chekcs[3] = { false , false , false };
	



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
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

