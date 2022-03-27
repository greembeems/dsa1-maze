#pragma once
#include <vector>
#include <list>
#include "Vertex.h"
using namespace std;

class Graph
{
	// Dimensions of the graph
	int height;
	int width;

	// Total number of vertices
	int totalV;

	// 2d vector of vertices
	vector<vector<Vertex>> vertices; //https://stackoverflow.com/questions/1946830/multidimensional-variable-size-array-in-c Just in case we want a reference later

	// ??
	Vertex* generatedVertex;

	// Adjacency of vertices
	const int** adjacency;

	// Open and closed list of vertices for pathfinding
	list<Vertex*> open;
	list<Vertex*> closed;

	// Methods
public:
	void aStar(int startX, int startY, int endX, int endY);

	Graph(const int** mData, int h, int w);

	void Setup();
};
