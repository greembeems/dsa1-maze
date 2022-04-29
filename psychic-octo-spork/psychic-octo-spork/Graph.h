#pragma once
#include <vector>
#include <list>
#include <cmath>
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
	vector<vector<Vertex*>> vertices; //https://stackoverflow.com/questions/1946830/multidimensional-variable-size-array-in-c Just in case we want a reference later (Khaled Alshaya)

	// Vertex generated from data
	Vertex* generatedVertex;

	// Adjacency matrix
	vector<vector<int>> adjacency;

	// Data
	const int** data;

	// Open and closed list of vertices for pathfinding
	vector<Vertex*> open;
	vector<Vertex*> closed;

	// Methods
	
public:
	
	vector<Vertex*> shortestPath;

	bool aStar(int startX, int startY, int endX, int endY);

	Graph(const int** mData, int h, int w);

	void Setup();

	void Check(Vertex* v, Vertex* s, int xShift, int yShift, int endX, int endY, bool checking);

	void Reverse();

	vector<Vertex*> GetShortestPath();

	bool Remove_if(Vertex* s);

	bool Check_if(vector<Vertex*> list, Vertex* s);

	

	
};
