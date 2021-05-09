#pragma once
// CFigureObject

#include "FigureMove.h"
#include "time.h"

#define RED 1
#define BLUE 2

#define CIRCLE 10
#define RECT   11	



class Figure : public CWnd
{
	DECLARE_DYNAMIC(Figure);

	// �����Ǻ���
public:
	int x = 0;
	int y = 0;
	int x2 = 0;
	int y2 = 0;

	int startX;
	int startY;

	int radius = 0;
	int color = 1;

	// ���� ���� ������ üũ�ϴ� ����
	bool checked = false;
	// �ڽ��ȿ� �ߵ��ٸ� good!!
	bool good;

public:

	// ���� ���� �����Ѵ�.
	void Initialize(int _x, int _y, int color , int _radius)
	{
		SetPos(_x, _y);
		radius = _radius;
		SetColor(color);
		checked = false;
		good = false;
	}

	// ���� �������� �ʱ�ȭ
	void Initialize(int _x, int _y , int _radius)
	{
		SetPos(_x, _y);
		radius = _radius;
		checked = false;
		good = false;

		if (RED == rand() % 2) 
		{
			SetColor(RED);
		}
		else
			SetColor(BLUE);

	}

	void SetRectangle(int _x, int _y, int _x2 , int _y2 )
	{
		x = _x;
		y = _y;
		x2 = _x2;
		y2 = _y2;
		
		checked = false;

	}

public:
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

	// �������� �׸��ϴ�.
	void Draw(CPaintDC* pdc , int type)
	{

		CBrush brush;
		
		switch (color)
		{
		case 1:
			brush.CreateSolidBrush(RGB(255, 0, 0));		//����
			break;
		case 2:
			brush.CreateSolidBrush(RGB(0, 0, 255));		//�Ķ�
			break;
		default:
			brush.CreateSolidBrush(RGB(255, 0, 0));
			break;
		}

		pdc->SelectObject(brush);

		switch (type)
		{
		case CIRCLE:
			pdc->Ellipse(x - radius, y - radius, x + radius, y + radius);
			break;
		case RECT:
			pdc->Rectangle(x, y, x2, y2);
			break;
		default:
			pdc->Ellipse(x - radius, y - radius, x + radius, y + radius);
			break;
		}
	}

public:
	Figure();
	virtual ~Figure();

protected:
	DECLARE_MESSAGE_MAP();
};


