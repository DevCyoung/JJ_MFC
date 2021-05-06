#pragma once


// CFigureObject


class Figure : public CWnd
{
	DECLARE_DYNAMIC(Figure);

	// �����Ǻ���
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
			pdc->SetDCBrushColor(RGB(255, 0, 0));		//����
			break;
		case 2:
			pdc->SetDCBrushColor(RGB(0, 0, 255));		//�Ķ�
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




// ����

public:
	Figure();
	virtual ~Figure();

protected:
	DECLARE_MESSAGE_MAP();
};


