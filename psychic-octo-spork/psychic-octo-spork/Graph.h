#pragma once
class Graph
{
	// Dimensions of the graph
	int height;
	int width;

	// Total number of vertices
	int totalV = height * width;

	// Vector of vertices
	vector<Vertex> vertices;

	// ??
	Vertex* generatedVertex = nullptr;

	// Adjacency of vertices
	const int** adjacency;

	// Open and closed list of vertices for pathfinding
	list<Vertex> open;
	list<Vertex> closed;

	// Methods
public:
	void aStar(int startX, int startY, int endX, int endY);

	Graph(const int** mData, int h, int w);

	void Setup();
};
