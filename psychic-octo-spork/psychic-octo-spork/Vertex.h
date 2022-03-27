#pragma once
class Vertex
{
	// Fields
	int xPos;
	int yPos;

	// Estimated cost from current square to destination
	int heuristic;

	// How many tiles away from starting position it is
	int lowestCost = MAXINT;

	// If the tile has been visited
	bool visited;
	Vertex* parent;

public:
	// Constructor
	Vertex(int x, int y);

	// Methods
	void UpdateParent(Vertex& newParent);

	void UpdateVisited();

	int LowestCost();

	// Stores tile's new lowestCost by taking from parent tile and adding 1
	void UpdateLowestCost();
};