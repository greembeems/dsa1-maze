#include "pch.h"
#include "Graph.h"
using namespace std;

	// Constructor
	Graph::Graph(const int** mData, int h, int w)
	{
		//Sets all the required variables
		height = h;
		width = w;
		adjacency = mData;

		totalV = height * width;

		generatedVertex = nullptr;
	}

	//Generates the Vertices list
	void Graph::Setup()
	{
		int j = 0;
		//Generates the list of vertices, but we might change it to a 2d array of vertices
		// We are changing this to a 2D array for our own brains
		for (int i = 0; i < height * width; i++) {

			// A wall
			if (adjacency[i][j] == 1) {
				generatedVertex = new Vertex(i, j, true);
				// Push to the back of the list of vertices
				vertices.push_back(*generatedVertex);
			}
			// Very much not a wall
			else {
				generatedVertex = new Vertex(i, j, false);
				// Push to the back of the list of vertices
				vertices.push_back(*generatedVertex);
			}

			j++;
		}
	}

	// Methods

	/// <summary>
	/// A* pathfinding method. Only call once
	/// </summary>
	void Graph::aStar(int startX, int startY, int endX, int endY)
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
