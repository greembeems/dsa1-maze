#include "pch.h"
#include "Vertex.h"

	// Constructor

	Vertex::Vertex(int x, int y, bool isOne)
	{
		visited = false;
		xPos = x;
		yPos = y;
		parent = nullptr;
		isWall = isOne;
		heuristic = 0;
	}

	// Methods

	void Vertex::UpdateParent(Vertex& newParent)
	{
		parent = &newParent;
	}

	void Vertex::UpdateVisited()
	{
		visited = true;
	}

	int Vertex::LowestCost()
	{
		return lowestCost;
	}

	// Stores tile's new lowestCost by taking from parent tile and adding 1
	void Vertex::UpdateLowestCost()
	{
		lowestCost = parent->LowestCost() + 1;
	}