#include "pch.h"
#include "Graph.h"
#include "Vertex.h"
#include <vector>
#include <list>
using namespace std;

class Graph {
	// Fields
	vector<Vertex> vertices;

	int height;
	int width;

	// Adjacency List/Matrix depending on what we decide to use
	const int** adjacency;

	// Open list - all considered vertices
	list<Vertex> open;
	// Closed list - unconsidered vertices
	list<Vertex> closed;

	// Constructors
public:
	Graph(const int** mData, int h, int w)
	{
		height = h;
		width = w;
		adjacency = mData;
	}

	void Setup(int startX, int startY, int endX, int endY)
	{
		
	}

	// Methods

	/// <summary>
	/// A* pathfinding method. Only call once
	/// </summary>
	void aStar()
	{
		// Add starting vertex to closed list
		closed.push_front(vertices[0]);

		// Add all adjacent tiles to open list
		for (int i = 1; i < 4; i++)
		{
			//adjacency map
		}

		// Find shortest path

		// Get square on open list with lowest score, s

		// Remove s from open list & add to closed

		// For each square, t, in s's valid adjacent tiles

		// if t is in closed list, ignore

		// if t is not in open list, add and compute score

		// if t is in open list, check if g + h is lower if use current generated path to get there
			// if f is lower, update that tile's score & update parents

		// if tie in lowest score, continue going with most recent tile

		// if end square is on open list, add to close list

		// go backwards from end tile parent by parent to learn exact shortest path

		// done!
	}
};