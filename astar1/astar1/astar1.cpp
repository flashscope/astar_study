// astar1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <array>
#include <queue>
#include "RoadMap.h"
#include <windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	UINT timeStart;
	UINT timeEnd;

	CRoadMap g;
	g.InitializeMap(60, 22);
	g.MakeWall(1, 4, 8, 4);
	g.MakeWall(1, 4, 1, 8);
	g.MakeWall(1, 8, 7, 8);
	g.SetStartAndEndNode(3, 2, 21, 40);

	timeStart = GetTickCount();
	g.FindPath();
	timeEnd = GetTickCount();

	g.PrintMap();

	printf_s("소요시간:%dms \n",timeEnd-timeStart);

	getchar();
	return 0;
}

