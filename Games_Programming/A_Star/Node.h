#pragma once

class Node {
public:
	Node();
	Node(int xCoord, int yCoord, int g, int h, int xParent, int yParent);
	bool operator==(const Node& other) const;

	int xCoord, yCoord, g, h, f, xParent, yParent;
};