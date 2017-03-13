#include "Node.h"
#include <vector>
#include <random>
#include <iostream>
#include <ctime>
#include <list>
using namespace std;

const int h = 20;
const int w = 20;

string map[w][h];
vector<Node> closed = {};
vector<Node> open = {};

int xStart, yStart, xEnd, yEnd;

int dir = 8;
enum directions{N, NE, E, SE, S, SW, W, NW};

void InitMap(int numImpassable);
void PrintMap();
void AStarSearch(int xStart, int yStart, int xEnd, int yEnd);
void addToOpen(int x, int y, int g, int px, int py);
int diff(int a, int b);

int main() {
	InitMap(80);
	PrintMap();

	cout << "Enter the X coord of the start position:" << endl;
	cin >> xStart;

	cout << "Enter the Y coord of the start position:" << endl;
	cin >> yStart;

	cout << "Enter the X coord of the end position:" << endl;
	cin >> xEnd;

	cout << "Enter the Y coord of the end position:" << endl;
	cin >> yEnd;

	AStarSearch(xStart, yStart, xEnd, yEnd);
	PrintMap();
	cout << "\nPress any key to continue...\n";
	cin.ignore(); cin.get();

	return 0;
}

void InitMap(int numImpassable) {
	int impassable = numImpassable;
	srand(time(NULL));
	for (int i = 0; i < h; i++) {
		int temp = (rand() % (impassable+1)) % (w/2);
		if (h-i == 1 && temp < impassable) {
			temp = impassable;
		}
		impassable -= temp;

		for (int j = 0; j < w; j++) {
			if (h - j != temp) {
				if (temp != 0) {
					int r = rand() % 5;
					switch (r) {
					case 1:
						map[i][j] = "[X]";
						temp--;
						break;
					default:
						map[i][j] = "[ ]";
						break;
					}
				}
				else {
					map[i][j] = "[ ]";
				}
			}
			else
			{
				map[i][j] = "[X]";
				temp--;
			}
		}
	}
}

void PrintMap() {
	cout << "   ";
	for (int j = 0; j < w; j++) {
		if(j<10)
			cout << " "<< j << " ";
		else
			cout << j << " ";
	}
	cout << endl;
	for (int i = 0; i < h; i++) {
		if(i<10)
			cout << i << "  ";
		else
			cout << i << " ";

		for (int j = 0; j < w; j++) {
			string tmp = map[i][j];
			cout << tmp.c_str();
		}
		cout << "\n";
	}
}

void AStarSearch(int xStart, int yStart, int xEnd, int yEnd){
	if (open.size() == 0) {
		int h = diff(xStart, xEnd) + diff(yStart, yEnd);
		Node n = Node(xStart, yStart, 0, h, -1, -1);
		open.push_back(n);
	}

	bool finished = false;
	while (!finished) {
		int f = NULL;
		Node chosen = Node();
		int xtmp = 0;
		int ytmp = 0;

		for each (Node n in open) {
			if (n.xCoord == xEnd && n.yCoord == yEnd) {
				chosen = n;
				finished = true;
				break;
			}else if (n.f < f || f == NULL) {
				f = n.f;
				chosen = n;
			}
		}

		if (!finished) {
			for (int i = 0; i < dir; i++) {
				switch (i) {
				case N:
					addToOpen(chosen.xCoord, chosen.yCoord + 1, chosen.g + 10, chosen.xCoord, chosen.yCoord);
					break;
				case NE:
					addToOpen(chosen.xCoord + 1, chosen.yCoord + 1, chosen.g + 14, chosen.xCoord, chosen.yCoord);
					break;
				case E:
					addToOpen(chosen.xCoord + 1, chosen.yCoord, chosen.g + 10, chosen.xCoord, chosen.yCoord);
					break;
				case SE:
					addToOpen(chosen.xCoord + 1, chosen.yCoord - 1, chosen.g + 14, chosen.xCoord, chosen.yCoord);
					break;
				case S:
					addToOpen(chosen.xCoord, chosen.yCoord - 1, chosen.g + 10, chosen.xCoord, chosen.yCoord);
					break;
				case SW:
					addToOpen(chosen.xCoord - 1, chosen.yCoord - 1, chosen.g + 14, chosen.xCoord, chosen.yCoord);
					break;
				case W:
					addToOpen(chosen.xCoord - 1, chosen.yCoord, chosen.g + 10, chosen.xCoord, chosen.yCoord);
					break;
				case NW:
					addToOpen(chosen.xCoord - 1, chosen.yCoord + 1, chosen.g + 14, chosen.xCoord, chosen.yCoord);
					break;
				}
			}
			cout << "Explored: " << chosen.xCoord << ", " << chosen.yCoord << endl;
			closed.push_back(chosen);

			for (unsigned int i = 0; i < open.size(); i++) {
				if (open[i] == chosen) {
					open.erase(open.begin()+i);
					break;
				}
			}
		}
		else
		{
			while (chosen.xParent != -1 && chosen.yParent != -1) {
				if(chosen.xCoord == xEnd && chosen.yCoord == yEnd)
					map[chosen.yCoord][chosen.xCoord] = "[F]";
				else
					map[chosen.yCoord][chosen.xCoord] = "[O]";

				for each(Node n in closed) {
					if (chosen.xParent == n.xCoord && chosen.yParent == n.yCoord)
						chosen = n;
				}
			}
			cout << chosen.xParent << "   " << chosen.yParent << endl;
			map[chosen.yCoord][chosen.xCoord] = "[S]";

		}
	}
	
}

void addToOpen(int x, int y, int g, int px, int py) {
	if (!(x<0 || x>=w || y < 0 || y>=h)) {
		if (!(map[y][x] == "[X]")) {
			int h = diff(x, xEnd) + diff(y, yEnd);
			Node tmp = Node(x, y, g, h, px, py);

			bool inClosed = false;

			for (unsigned int i = 0; i < closed.size(); i++) {
				if (closed[i].xCoord == tmp.xCoord && closed[i].yCoord == tmp.yCoord) {
					inClosed = true;
					break;
				}
					
			}

			if (!inClosed) {
					vector<Node> tmpOpen;
					bool added = false;
					if (open.empty()) {
						open.push_back(tmp);
						added = true;
					}
					else {
						for (unsigned int i = 0; i < open.size(); i++) {
							if (open[i].xCoord == tmp.xCoord && open[i].yCoord == tmp.yCoord) {
								if (tmp.g < open[i].g) {
									tmpOpen.push_back(tmp);
									added = true;
								}
								else {
									tmpOpen.push_back(open[i]);
									added = true;
								}

							}
							else {
								tmpOpen.push_back(open[i]);
							}

						}
						if (!added)
							tmpOpen.push_back(tmp);
						open = tmpOpen;
					}
			}
		}
	}
}

int diff(int a, int b) {
	if (a > b)
		return a - b;
	else
		return b - a;
}