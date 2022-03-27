#pragma once
class Vertex
{
	// Fields
	int xPos;
	int yPos;
	bool isWall;
	// Estimated cost from current square to destination
	int heuristic;
	// How many tiles away from starting position it is
	int lowestCost = 0;
	// If the tile has been visited
	bool visited;
	Vertex* parent;

	// Constructor
public:
	Vertex(int x, int y, bool isOne);
	// Methods
	void UpdateParent(Vertex& newParent);
	void UpdateVisited();
	int LowestCost();
	// Stores tile's new lowestCost by taking from parent tile and adding 1
	void UpdateLowestCost();
};