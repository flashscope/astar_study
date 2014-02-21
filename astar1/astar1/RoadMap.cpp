// 소스코드 출처
//https://github.com/iwitaly/AStar
// 설명 참고
//http://cozycoz.egloos.com/9748811

#include "stdafx.h"
#include "RoadMap.h"
#include <iostream>

CRoadMap::CRoadMap(void)
{
}

CRoadMap::~CRoadMap(void)
{
}

// 지도를 초기화 한다.
// 인자로 넘긴 수만큼 맵을 만듬
void CRoadMap::InitializeMap( int weight, int height )
{
	m_IsFindPath = false;

	// 벡터의 갯수를 지정하여 낭비를 없앰
	m_Map.resize(height);
	for (int i = 0; i < static_cast<int>(m_Map.size()); ++i) {
		m_Map[i].resize(weight);
	}

	for (int i = 0; i < static_cast<int>(m_Map.size()); ++i) {
		for (int j = 0; j < static_cast<int>(m_Map[i].size()); ++j) {
			m_Map[i][j].point.x = i;
			m_Map[i][j].point.y = j;
			m_Map[i][j].type = NodeStatusFree;
		}
	}
}

void CRoadMap::MakeWall(int startX, int startY, int endX, int endY)
{
	for (int i = startX; i <= endX; ++i) {
		for (int j = startY; j <= endY; ++j) {
			m_Map[i][j].type = NodeStatusWall;
		}
	}
}

void CRoadMap::SetStartAndEndNode(int startX, int startY, int endX, int endY)
{
	m_StartNode.x = startX; m_StartNode.y = startY;
	m_EndNode.x = endX; m_EndNode.y = endY;

	m_Map[m_StartNode.x][m_StartNode.y].type = NodeStatusPath;
	m_Map[m_EndNode.x][m_EndNode.y].type = NodeStatusPath;
}



void CRoadMap::FindPath()
{
	// 현재 위치로부터 갈수 있는 노드들
	std::multimap<int, Node> open;
	// 이미 확인하고 더이상 검색할 필요가 없는 노드들
	std::multimap<int, Node> close;

	// 시작 위치를 정한다.
	// 시작점이므로 시작점과의 거리인 g값을 0으로 넣는다.
	m_Map[m_StartNode.x][m_StartNode.y].g = 0;
	// 목적지와의 거리값을 찾는다.
	CalculateH(m_StartNode);
	// 목적지와 선택지의 비용값을 더한다. (사실 시작점이므로 h값과 동일하다.)
	CalculateF(m_StartNode);
	
	// 경로의 끝을 표시하기 위해 부모를 자신으로 둔다.
	m_Map[m_StartNode.x][m_StartNode.y].parent = m_StartNode;

	// 검색을 하도록 open에 시작값을 넣는다.
	open.insert(std::make_pair(m_Map[m_StartNode.x][m_StartNode.y].f, m_Map[m_StartNode.x][m_StartNode.y]));

	// 갈수있는곳이나 목적지를 찾을때까지 계속 검색 ( open이 다 비워도 목적지를 찾지 못하면 길이 없다. 종료조건1)
	while (!open.empty())
	{
		// 검색된 주변 위치를 꺼낸다.
		Node nowNode = open.begin()->second;
		open.erase(open.begin());

		// 목적지를 찾음 - 종료조건2
		if (nowNode.point.x == m_EndNode.x && nowNode.point.y == m_EndNode.y)
		{
			m_IsFindPath = true;
			printf_s("경로를 찾았다!\n");
			break;
		}

		// 이미 검색한 위치는 검색하지 않도록 close에 넣는다.
		close.insert(std::make_pair(m_Map[nowNode.point.x][nowNode.point.y].f, m_Map[nowNode.point.x][nowNode.point.y]));

		// 현재 위치에서 주변을 탐색한다.
		for (int i = -1; i <= 1; ++i)
		{
			for (int j = -1; j <= 1; ++j)
			{
				int cost;

				// 대각선방향이면 14로 직선방향이면 10 (루트2 약1.4를 정수로 만들기 위해 14,10을 씀)
				if (i && j)
				{
					cost = 14;
				}
				else
				{
					cost = 10;
				}

				// 대각선에 대해서는 그냥 넘겨버리면 대각선 이동을 하지 않음
				// 어차피 길이 4방향 게임이면 상관없긴 하지만 직선운동도 해주는것이 인간답게 하는 꼼수라고 함 (근데 이건 너무 단순)
				if (i && j)
				{
					continue;
				}

				NodePoint nearNodeP;
				nearNodeP.x = nowNode.point.x + i;
				nearNodeP.y = nowNode.point.y + j;

				// 주변의 노드가 벽이거나 맵을 벗어나는것은 넘겨버림
				if ( !ValidPoint(nearNodeP) )
				{
					continue;
				}
				
				// 이미 close된 곳에 노드가 있다!
				if (close.find(m_Map[nearNodeP.x][nearNodeP.y].f) != close.end())
				{
					continue;
				}

				// open되어있는 목록에 이 노드가없다!
				if (open.find(m_Map[nearNodeP.x][nearNodeP.y].f) == open.end())
				{
					std::multimap<int, Node>::iterator iterTime = open.end();
					CalculateG(nowNode.point,nearNodeP, cost);
					CalculateH(nearNodeP);
					CalculateF(nearNodeP);

					// 지금 노드로 가기전의 노드가 누군지 표시 - 이걸 따라가면 경로가 나온다.
					m_Map[nearNodeP.x][nearNodeP.y].parent = nowNode.point;

					// 지금 노드를 검색 대상으로 올려놓는다.
					open.insert(std::make_pair(m_Map[nearNodeP.x][nearNodeP.y].f, m_Map[nearNodeP.x][nearNodeP.y]));
				}
				else
				//만약 이것이 이미 열린목록에 있다면, G비용을 이용하해 어느쪽이 더 나은가 알아보고
				//그것의 G비용이 더 작으면 그것이 더 나은 길이라는 것을 의미하므로
				//기존에 있던 노드를 비교 대상인 nearNode로 교체
				//즉 그 노드로 가는데 더 좋은 방법 찾음
				{
					Node nearNode = open.find(m_Map[nearNodeP.x][nearNodeP.y].f)->second;
					if (nearNode.g < m_Map[nearNodeP.x][nearNodeP.y].g)
					{
						open.erase(m_Map[nearNode.point.x][nearNode.point.y].f);
						open.insert(std::make_pair(m_Map[nearNodeP.x][nearNodeP.y].f, m_Map[nearNodeP.x][nearNodeP.y]));
					}
				}
			}
		}
	}

	// 경로를 찾지 못함
	if ( !m_IsFindPath )
	{
		printf_s("경로를 못찾았다...\n");
	}

	WritePathOnTheMap();

}

// 새로 찾은 노드에 기존의 코스트와 새로 추가된 코스트를 더한다.
// 출발점에서 지금 위치까지의 비용을 나타냄
void CRoadMap::CalculateG( NodePoint nowNodeP, NodePoint nearNodeP, int cost )
{
	m_Map[nearNodeP.x][nearNodeP.y].g = m_Map[nowNodeP.x][nowNodeP.y].g + cost;
}

// 지금 위치로부터 목표지점까지의 비용을 나타냄
// 장애물, 대각선 생각않고 그냥 간단히 직각으로 갔을때의 거리를 측정 - 블럭으로 계산한다고 맨하탄 방식이라고 함 
void CRoadMap::CalculateH( NodePoint nodeP )
{
	m_Map[nodeP.x][nodeP.y].h = abs(m_Map[nodeP.x][nodeP.y].point.x - m_EndNode.x) + abs(m_Map[nodeP.x][nodeP.y].point.y - m_EndNode.y);
}

// 시작지점과 목표지점과의 비용을 계산한 값
void CRoadMap::CalculateF( NodePoint nodeP )
{
	m_Map[nodeP.x][nodeP.y].f = m_Map[nodeP.x][nodeP.y].h + m_Map[nodeP.x][nodeP.y].g;
}

// 비정상적인 포인트를 검사
bool CRoadMap::ValidPoint( NodePoint nodeP )
{
	if (nodeP.x < 0 ||
		nodeP.y < 0 ||
		nodeP.x >= static_cast<int>(m_Map.size()) ||
		nodeP.y >= static_cast<int>(m_Map[nodeP.x].size()) ||
		m_Map[nodeP.x][nodeP.y].type == NodeStatusWall
		)
	{
		return false;
	}

	return true;
}

//목적지에서 부터 출발지점으로 부모의 노드를 따라서 이동
void CRoadMap::WritePathOnTheMap()
{
	NodePoint p = m_EndNode;
	while (p != m_Map[m_StartNode.x][m_StartNode.y].parent) {
		m_Map[p.x][p.y].type = NodeStatusPath;
		p = m_Map[p.x][p.y].parent;
	}
	m_Map[m_StartNode.x][m_StartNode.y].type = NodeStatusStart;
	m_Map[m_EndNode.x][m_EndNode.y].type = NodeStatusEnd;
}

// 지도 상황을 프린트
void CRoadMap::PrintMap()
{
	for (int i = 0; i < static_cast<int>(m_Map.size()); ++i) {
		for (int j = 0; j < static_cast<int>(m_Map[i].size()); ++j) {
			printf_s("%d",m_Map[i][j].type);
		}
		printf_s("\n");
	}
}

