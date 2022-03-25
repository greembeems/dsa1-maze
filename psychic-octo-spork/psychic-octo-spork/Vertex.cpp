#include "pch.h"
#include "Vertex.h"

class Vertex
{
	// Fields
	int xPos;
	int yPos;

	// Estimated cost from current square to destination
	int heuristic;

	// How many tiles away from starting position it is
	int lowestCost = 0;

	// If the tile has been visited
	bool visited;

	Vertex* parent;

	// Constructor
public:
	Vertex(int x, int y, Vertex& parentVertex, int h)
	{
		xPos = x;
		yPos = y;
		parent = &parentVertex;

		heuristic = h;
	}

	// Methods

	void UpdateParent(Vertex& newParent)
	{
		parent = &newParent;
	}

	void UpdateVisited()
	{
		visited = true;
	}

	int LowestCost()
	{
		return lowestCost;
	}

	// Stores tile's new lowestCost by taking from parent tile and adding 1
	void UpdateLowestCost()
	{
		lowestCost = parent->LowestCost() + 1;
	}
};