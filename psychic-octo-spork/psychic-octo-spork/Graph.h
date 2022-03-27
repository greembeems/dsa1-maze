#pragma once
class Graph
{
	int height;
	int width;
	int totalV = height * width;
	vector<Vertex> vertices;
	Vertex* generatedVertex = nullptr;
	const int** adjacency;
	list<Vertex> open;
	list<Vertex> closed;
	void aStar(int startX, int startY, int endX, int endY);
	Graph(const int** mData, int h, int w);
	void Setup();
};
