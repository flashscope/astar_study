#pragma once

// 노드의 상태를 표시
enum NodeStatus {
	NodeStatusFree,
	NodeStatusWall,
	NodeStatusPath,
	NodeStatusStart,
	NodeStatusEnd
};

// xy좌표와 연산자 오버라이드를 통해 비교를 쉽게 함
struct NodePoint {
	int x, y;
	bool operator == (NodePoint p) {
		return x == p.x && y == p.y;
	}
	bool operator != (NodePoint p) {
		return !(*this == p);
	}
};

// 노드의 정보 상태값, 비용 계산에 필요한f,g,h값과 노드 위치 좌표와 부모의 위치좌표를 가진다. 
struct Node {
	NodeStatus type;
	int f, g, h;
	NodePoint point;
	NodePoint parent;
};
