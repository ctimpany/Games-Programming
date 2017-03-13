#include "Node.h"

Node::Node() {
}

Node::Node(int xCoord, int yCoord, int g, int h, int xParent, int yParent) {
	this->xCoord = xCoord;
	this->yCoord = yCoord;
	this->g = g;
	this->h = h;
	f = g + h;
	this->xParent = xParent;
	this->yParent = yParent;
}

bool Node::operator==(const Node & other) const
{
	if (this->xCoord == other.xCoord &&
		this->yCoord == other.yCoord &&
		this->xParent == other.xParent &&
		this->yParent == other.yParent &&
		this->f == other.f &&
		this->g == other.g &&
		this->h == other.h)
		return true;
	else
		return false;
}