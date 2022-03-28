#pragma once

class Vertex
{
	// Fields

	// If the tile has been visited
	bool visited;
	Vertex* parent;

public:
	
	int f;
	int g = MAXINT;
	int xPos;
	int yPos;
	int heuristic; // Estimated cost from current square to destination
	// Constructor
	Vertex(int x, int y);

	// Methods
	void UpdateParent(Vertex& newParent);

	void UpdateVisited();

	void GenerateHeuristic(int totalDistance);

	int ReturnG();

	Vertex* ReturnParent();

	void UpdateF();

	// Stores tile's new lowestCost by taking from parent tile and adding 1
	void UpdateG();
};