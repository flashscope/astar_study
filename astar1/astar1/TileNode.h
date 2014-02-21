#pragma once

// ����� ���¸� ǥ��
enum NodeStatus {
	NodeStatusFree,
	NodeStatusWall,
	NodeStatusPath,
	NodeStatusStart,
	NodeStatusEnd
};

// xy��ǥ�� ������ �������̵带 ���� �񱳸� ���� ��
struct NodePoint {
	int x, y;
	bool operator == (NodePoint p) {
		return x == p.x && y == p.y;
	}
	bool operator != (NodePoint p) {
		return !(*this == p);
	}
};

// ����� ���� ���°�, ��� ��꿡 �ʿ���f,g,h���� ��� ��ġ ��ǥ�� �θ��� ��ġ��ǥ�� ������. 
struct Node {
	NodeStatus type;
	int f, g, h;
	NodePoint point;
	NodePoint parent;
};
