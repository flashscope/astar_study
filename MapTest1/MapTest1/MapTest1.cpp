// MapTest1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <vector>
#include "Tile.h"
#include "WorldMap.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CWorldMap* worldMap = CWorldMap::GetInstance();
	worldMap->InitializeMap(20, 10);

	//worldMap->CreateRoad(1,2);worldMap->CreateRoad(1,3);

	worldMap->CreateRoads(1,2, 3,2);
	//worldMap->CreateRoad(1,2);worldMap->CreateRoad(2,2);worldMap->CreateRoad(3,2);
	worldMap->CreateRoad(1,3);worldMap->CreateRoad(2,3);worldMap->CreateRoad(3,3);
	worldMap->CreateRoad(1,4);worldMap->CreateRoad(2,4);worldMap->CreateRoad(3,4);

	worldMap->CreateRoad(5,1);worldMap->CreateRoad(6,1);worldMap->CreateRoad(7,1);worldMap->CreateRoad(8,1);worldMap->CreateRoad(9,1);
	worldMap->CreateRoad(6,2);worldMap->CreateRoad(8,2);
	worldMap->CreateRoad(6,3);worldMap->CreateRoad(7,3);worldMap->CreateRoad(8,3);
	worldMap->CreateRoad(6,4);worldMap->CreateRoad(8,4);

	worldMap->CreateRoad(6,6);worldMap->CreateRoad(8,6);
	worldMap->CreateRoad(6,7);worldMap->CreateRoad(7,7);worldMap->CreateRoad(8,7);
	worldMap->CreateRoad(6,8);worldMap->CreateRoad(8,8);
	worldMap->CreateRoad(5,9);worldMap->CreateRoad(6,9);worldMap->CreateRoad(7,9);worldMap->CreateRoad(8,9);worldMap->CreateRoad(9,9);

	worldMap->CreateRoad(11,4);
	worldMap->CreateRoad(10,5);worldMap->CreateRoad(11,5);worldMap->CreateRoad(12,5);
	worldMap->CreateRoad(11,6);

	worldMap->PrintMap();
	worldMap->SaveFile();

	getchar();
	return 0;
}

