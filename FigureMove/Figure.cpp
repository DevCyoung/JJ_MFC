// Figure.cpp: 구현 파일
//

#include "pch.h"
#include "FigureMove.h"
#include "Figure.h"
#include "time.h"

// Figure

IMPLEMENT_DYNAMIC(Figure, CWnd)

Figure::Figure()
{

	srand((unsigned int)time(NULL));


}

Figure::~Figure()
{
}


BEGIN_MESSAGE_MAP(Figure, CWnd)
END_MESSAGE_MAP()



// Figure 메시지 처리기


