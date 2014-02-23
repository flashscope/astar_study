#pragma once
#include <vector>
#include "Tile.h"
#include "Macro.h"

class CWorldMap
{
	SINGLETON(CWorldMap);
public:
	CWorldMap(void);
	~CWorldMap(void);

	void		InitializeMap( int weight, int height );
	void		InsertMap();
	void		CreateRoad( int x, int y );
	void		CreateRoads(int startX, int startY, int endX, int endY);
	TileType	GetTileType( int x, int y );
		
	bool		ValidPoint( int x, int y );
	

	void	PrintMap();
	void	SaveFile();
	
private:
	std::vector<std::vector<CTile>> m_Map;
};

