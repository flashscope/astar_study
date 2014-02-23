#pragma once
enum TileType {
	TILE_NONE,

	TILE_GROUND,
	TILE_ROAD,
	TILE_BUILDING,

	TILE_MAX
};

class CTile
{
public:
	CTile(void);
	~CTile(void);

	void	RefreshRoad();

	void	SetPointX( int pointX ) { m_PointX = pointX; };
	void	SetPointY( int pointY ) { m_PointY = pointY; };
	void	SetTileType( TileType tileType ) { m_TileType = tileType; };
	void	SetRoadStatus( int roadStatus ) { m_RoadStatus = roadStatus; };

	int	GetPointX() { return m_PointX; };
	int	GetPointY() { return m_PointY; };
	TileType	GetTileType() { return m_TileType; };
	int	GetRoadStatus() { return m_RoadStatus; };

private:

	int m_PointX;
	int m_PointY;
	TileType m_TileType;
	int m_RoadStatus;
};

