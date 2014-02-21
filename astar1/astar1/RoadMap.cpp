// �ҽ��ڵ� ��ó
//https://github.com/iwitaly/AStar
// ���� ����
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

// ������ �ʱ�ȭ �Ѵ�.
// ���ڷ� �ѱ� ����ŭ ���� ����
void CRoadMap::InitializeMap( int weight, int height )
{
	m_IsFindPath = false;

	// ������ ������ �����Ͽ� ���� ����
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
	// ���� ��ġ�κ��� ���� �ִ� ����
	std::multimap<int, Node> open;
	// �̹� Ȯ���ϰ� ���̻� �˻��� �ʿ䰡 ���� ����
	std::multimap<int, Node> close;

	// ���� ��ġ�� ���Ѵ�.
	// �������̹Ƿ� ���������� �Ÿ��� g���� 0���� �ִ´�.
	m_Map[m_StartNode.x][m_StartNode.y].g = 0;
	// ���������� �Ÿ����� ã�´�.
	CalculateH(m_StartNode);
	// �������� �������� ��밪�� ���Ѵ�. (��� �������̹Ƿ� h���� �����ϴ�.)
	CalculateF(m_StartNode);
	
	// ����� ���� ǥ���ϱ� ���� �θ� �ڽ����� �д�.
	m_Map[m_StartNode.x][m_StartNode.y].parent = m_StartNode;

	// �˻��� �ϵ��� open�� ���۰��� �ִ´�.
	open.insert(std::make_pair(m_Map[m_StartNode.x][m_StartNode.y].f, m_Map[m_StartNode.x][m_StartNode.y]));

	// �����ִ°��̳� �������� ã�������� ��� �˻� ( open�� �� ����� �������� ã�� ���ϸ� ���� ����. ��������1)
	while (!open.empty())
	{
		// �˻��� �ֺ� ��ġ�� ������.
		Node nowNode = open.begin()->second;
		open.erase(open.begin());

		// �������� ã�� - ��������2
		if (nowNode.point.x == m_EndNode.x && nowNode.point.y == m_EndNode.y)
		{
			m_IsFindPath = true;
			printf_s("��θ� ã�Ҵ�!\n");
			break;
		}

		// �̹� �˻��� ��ġ�� �˻����� �ʵ��� close�� �ִ´�.
		close.insert(std::make_pair(m_Map[nowNode.point.x][nowNode.point.y].f, m_Map[nowNode.point.x][nowNode.point.y]));

		// ���� ��ġ���� �ֺ��� Ž���Ѵ�.
		for (int i = -1; i <= 1; ++i)
		{
			for (int j = -1; j <= 1; ++j)
			{
				int cost;

				// �밢�������̸� 14�� ���������̸� 10 (��Ʈ2 ��1.4�� ������ ����� ���� 14,10�� ��)
				if (i && j)
				{
					cost = 14;
				}
				else
				{
					cost = 10;
				}

				// �밢���� ���ؼ��� �׳� �Ѱܹ����� �밢�� �̵��� ���� ����
				// ������ ���� 4���� �����̸� ������� ������ ������� ���ִ°��� �ΰ���� �ϴ� �ļ���� �� (�ٵ� �̰� �ʹ� �ܼ�)
				if (i && j)
				{
					continue;
				}

				NodePoint nearNodeP;
				nearNodeP.x = nowNode.point.x + i;
				nearNodeP.y = nowNode.point.y + j;

				// �ֺ��� ��尡 ���̰ų� ���� ����°��� �Ѱܹ���
				if ( !ValidPoint(nearNodeP) )
				{
					continue;
				}
				
				// �̹� close�� ���� ��尡 �ִ�!
				if (close.find(m_Map[nearNodeP.x][nearNodeP.y].f) != close.end())
				{
					continue;
				}

				// open�Ǿ��ִ� ��Ͽ� �� ��尡����!
				if (open.find(m_Map[nearNodeP.x][nearNodeP.y].f) == open.end())
				{
					std::multimap<int, Node>::iterator iterTime = open.end();
					CalculateG(nowNode.point,nearNodeP, cost);
					CalculateH(nearNodeP);
					CalculateF(nearNodeP);

					// ���� ���� �������� ��尡 ������ ǥ�� - �̰� ���󰡸� ��ΰ� ���´�.
					m_Map[nearNodeP.x][nearNodeP.y].parent = nowNode.point;

					// ���� ��带 �˻� ������� �÷����´�.
					open.insert(std::make_pair(m_Map[nearNodeP.x][nearNodeP.y].f, m_Map[nearNodeP.x][nearNodeP.y]));
				}
				else
				//���� �̰��� �̹� ������Ͽ� �ִٸ�, G����� �̿����� ������� �� ������ �˾ƺ���
				//�װ��� G����� �� ������ �װ��� �� ���� ���̶�� ���� �ǹ��ϹǷ�
				//������ �ִ� ��带 �� ����� nearNode�� ��ü
				//�� �� ���� ���µ� �� ���� ��� ã��
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

	// ��θ� ã�� ����
	if ( !m_IsFindPath )
	{
		printf_s("��θ� ��ã�Ҵ�...\n");
	}

	WritePathOnTheMap();

}

// ���� ã�� ��忡 ������ �ڽ�Ʈ�� ���� �߰��� �ڽ�Ʈ�� ���Ѵ�.
// ��������� ���� ��ġ������ ����� ��Ÿ��
void CRoadMap::CalculateG( NodePoint nowNodeP, NodePoint nearNodeP, int cost )
{
	m_Map[nearNodeP.x][nearNodeP.y].g = m_Map[nowNodeP.x][nowNodeP.y].g + cost;
}

// ���� ��ġ�κ��� ��ǥ���������� ����� ��Ÿ��
// ��ֹ�, �밢�� �����ʰ� �׳� ������ �������� �������� �Ÿ��� ���� - ������ ����Ѵٰ� ����ź ����̶�� �� 
void CRoadMap::CalculateH( NodePoint nodeP )
{
	m_Map[nodeP.x][nodeP.y].h = abs(m_Map[nodeP.x][nodeP.y].point.x - m_EndNode.x) + abs(m_Map[nodeP.x][nodeP.y].point.y - m_EndNode.y);
}

// ���������� ��ǥ�������� ����� ����� ��
void CRoadMap::CalculateF( NodePoint nodeP )
{
	m_Map[nodeP.x][nodeP.y].f = m_Map[nodeP.x][nodeP.y].h + m_Map[nodeP.x][nodeP.y].g;
}

// ���������� ����Ʈ�� �˻�
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

//���������� ���� ����������� �θ��� ��带 ���� �̵�
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

// ���� ��Ȳ�� ����Ʈ
void CRoadMap::PrintMap()
{
	for (int i = 0; i < static_cast<int>(m_Map.size()); ++i) {
		for (int j = 0; j < static_cast<int>(m_Map[i].size()); ++j) {
			printf_s("%d",m_Map[i][j].type);
		}
		printf_s("\n");
	}
}

