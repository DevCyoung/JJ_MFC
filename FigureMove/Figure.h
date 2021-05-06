#pragma once


// CFigureObject


class Figure : public CWnd
{
	DECLARE_DYNAMIC(Figure);

	// 도형의변수
public:
	int x;
	int y;
	int radius;
	int color;
	CRgn rgn;

public:
	void Initialize(int _x, int _y, int color , int _radius)
	{
		SetPos(_x, _y);
		SetCRgn();
		SetColor(color);
		radius = _radius;
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
	void SetCRgn()
	{
		rgn.CreateEllipticRgn(x - radius, y - radius, x + radius, y + radius);
	}
	void Draw(CPaintDC* pdc)
	{
		switch (color)
		{
		case 1:
			pdc->SetDCBrushColor(RGB(255, 0, 0));		//빨강
			break;
		case 2:
			pdc->SetDCBrushColor(RGB(0, 0, 255));		//파랑
		default:
			break;
		}

		pdc->Ellipse(x - radius, y - radius, x + radius, y + radius);
	}
	bool GetChecked()
	{
		CPoint point;
		::GetCursorPos(&point);
		ScreenToClient(&point);
		return rgn.PtInRegion(point);
	}




// 종료

public:
	Figure();
	virtual ~Figure();

protected:
	DECLARE_MESSAGE_MAP();
};


