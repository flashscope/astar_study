#pragma once
#include <vector>
#include <map>
#include "TileNode.h"


class CRoadMap {

public:
	CRoadMap(void);
	~CRoadMap(void);

	void InitializeMap(int weight, int height);
	void MakeWall(int startX, int startY, int endX, int endY);
	void SetStartAndEndNode(int startX, int startY, int endX, int endY);
	void FindPath();
	void PrintMap();

private:
	void CalculateG(NodePoint nowNodeP, NodePoint nearNodeP, int cost);
	void CalculateF(NodePoint nodeP);
	void CalculateH(NodePoint nodeP);
	bool ValidPoint(NodePoint nodeP);
	void WritePathOnTheMap();
	

private:
	std::vector<std::vector<Node>> m_Map;
	NodePoint m_StartNode, m_EndNode;
	bool m_IsFindPath;

};
