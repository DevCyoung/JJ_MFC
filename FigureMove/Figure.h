#pragma once


// CFigureObject

#include "FigureMove.h"
#include "time.h"

class Figure : public CWnd
{
	DECLARE_DYNAMIC(Figure);

	// 도형의변수
public:
	int x = 0;
	int y =0;
	int radius = 0;
	int color = 1;
	bool checked = false;
	CRgn rgn;

public:
	void Initialize(int _x, int _y, int color , int _radius)
	{
		SetPos(_x, _y);
		radius = _radius;
		SetColor(color);
		checked = false;
	}
	void Initialize(int _x, int _y , int _radius)
	{
		SetPos(_x, _y);
		radius = _radius;
		checked = false;

		

		if (RED == rand() % 2) 
		{
			SetColor(RED);
		}
		else
			SetColor(BLUE);

	}
	

private:
	void SetColor(int _color)
	{
		color = _color;
	}

public:

	void SetPos(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	void SetCRgn(CPaintDC dc)
	{
		
		

	}
	void Draw(CPaintDC* pdc)
	{

		CBrush brush;
		
		switch (color)
		{
		case RED:
			brush.CreateSolidBrush(RGB(255, 0, 0));		//빨강
			break;
		case BLUE:
			brush.CreateSolidBrush(RGB(0, 0, 255));		//파랑
			break;
		default:
			brush.CreateSolidBrush(RGB(255, 0, 0));
			break;
		}

		
		pdc->SelectObject(brush);

		pdc->Ellipse(x - radius, y - radius, x + radius, y + radius);

	}
	bool GetChecked()
	{
		CPoint point;
		::GetCursorPos(&point);
		ScreenToClient(&point);
		
		/*checked = rgn.PtInRegion(point);*/
		return checked;
	}

	void Move()
	{
		CPoint point;
		::GetCursorPos(&point);
		ScreenToClient(&point);

		SetPos(point.x, point.y);
		
	}




// 종료

public:
	Figure();
	virtual ~Figure();

protected:
	DECLARE_MESSAGE_MAP();
};


