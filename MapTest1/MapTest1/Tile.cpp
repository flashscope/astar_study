#include "stdafx.h"
#include "Tile.h"
#include "WorldMap.h"


CTile::CTile(void)
{
}


CTile::~CTile(void)
{
}

void CTile::RefreshRoad()
{
	
	if (m_TileType != TILE_ROAD)
	{
		return;
	}
	
	m_RoadStatus = 1;


	CWorldMap* worldMap = CWorldMap::GetInstance();
	

	if ( worldMap->ValidPoint( m_PointX, m_PointY+1 ) )
	{
		if ( worldMap->GetTileType(m_PointX, m_PointY+1) == TILE_ROAD )
		{
			m_RoadStatus = m_RoadStatus + 8;
		}
	}

	if ( worldMap->ValidPoint( m_PointX+1, m_PointY ) )
	{
		if ( worldMap->GetTileType(m_PointX+1, m_PointY) == TILE_ROAD )
		{
			m_RoadStatus = m_RoadStatus + 4;
		}
	}

	if ( worldMap->ValidPoint( m_PointX, m_PointY-1 ) )
	{
		if ( worldMap->GetTileType(m_PointX, m_PointY-1) == TILE_ROAD )
		{
			m_RoadStatus = m_RoadStatus + 2;
		}
	}

	if ( worldMap->ValidPoint( m_PointX-1, m_PointY ) )
	{
		if ( worldMap->GetTileType(m_PointX-1, m_PointY) == TILE_ROAD )
		{
			m_RoadStatus = m_RoadStatus + 16;
		}
	}
}
