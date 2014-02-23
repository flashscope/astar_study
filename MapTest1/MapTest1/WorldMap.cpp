#include "stdafx.h"
#include "WorldMap.h"
#include <fstream>
#include <string>
#include <array>

CWorldMap::CWorldMap(void)
{
}


CWorldMap::~CWorldMap(void)
{
}

void CWorldMap::InitializeMap( int weight, int height )
{
	// º¤ÅÍÀÇ °¹¼ö¸¦ ÁöÁ¤ÇÏ¿© ³¶ºñ¸¦ ¾ø¾Ú
	m_Map.resize(height);
	for (int i = 0; i < static_cast<int>(m_Map.size()); ++i) {
		m_Map[i].resize(weight);
	}

	for (int i = 0; i < static_cast<int>(m_Map.size()); ++i) {
		for (int j = 0; j < static_cast<int>(m_Map[i].size()); ++j) {
			m_Map[i][j].SetPointX(j);
			m_Map[i][j].SetPointY(i);
			m_Map[i][j].SetTileType(TILE_GROUND);
			m_Map[i][j].SetRoadStatus(0);
		}
	}
}

void CWorldMap::InsertMap()
{

}

void CWorldMap::PrintMap()
{
	for (int i = 0; i < static_cast<int>(m_Map.size()); ++i) {
		for (int j = 0; j < static_cast<int>(m_Map[i].size()); ++j) {
			printf_s("%3d",m_Map[i][j].GetRoadStatus());
		}
		printf_s("\n");
	}
}

void CWorldMap::CreateRoad( int x, int y )
{
	if ( !ValidPoint( x, y ) )
	{
		return;
	}

	if (m_Map[y][x].GetTileType() != TILE_GROUND)
	{
		return;
	}

	m_Map[y][x].SetTileType(TILE_ROAD);
	m_Map[y][x].RefreshRoad();

	if ( ValidPoint( x-1, y ) )
	{
		m_Map[y][x-1].RefreshRoad();
	}
	if ( ValidPoint( x+1, y ) )
	{
		m_Map[y][x+1].RefreshRoad();
	}
	if ( ValidPoint( x, y-1 ) )
	{
		m_Map[y-1][x].RefreshRoad();
	}
	if ( ValidPoint( x, y+1 ) )
	{
		m_Map[y+1][x].RefreshRoad();
	}
}

void CWorldMap::CreateRoads( int startX, int startY, int endX, int endY )
{
	for (int i = startX; i <= endX; ++i) {
		for (int j = startY; j <= endY; ++j) {
			CreateRoad( i, j );
		}
	}
}

bool CWorldMap::ValidPoint( int x, int y )
{
	if (x < 0 ||
		y < 0 ||
		y >= static_cast<int>(m_Map.size()) ||
		x >= static_cast<int>(m_Map[y].size())
		)
	{
		return false;
	}

	return true;
}

TileType CWorldMap::GetTileType( int x, int y )
{
	if ( ValidPoint( x, y ) )
	{
		return m_Map[y][x].GetTileType();
	}

	return TILE_NONE;
}

std::string	GetImgTag(std::string fileName) {
	std::string	result = "<img src='";
	result += fileName;
	result += ".png'>";

	return result;
}

void CWorldMap::SaveFile()
{
	std::string	mapData = "<html><body>";
	for (int i = 0; i < static_cast<int>(m_Map.size()); ++i) {
		for (int j = 0; j < static_cast<int>(m_Map[i].size()); ++j) {
			mapData+= GetImgTag( std::to_string( m_Map[i][j].GetRoadStatus() ) );
		}
		mapData+="\n<br>";
	}
	mapData+="</body></html>";
	std::ofstream SaveFile("mapView.html");
	SaveFile << mapData;
	SaveFile.close();
}


