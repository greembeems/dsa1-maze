#include "pch.h"
#include "Graph.h"
using namespace std;

	// Constructor
	Graph::Graph(const int** mData, int h, int w)
	{
		//Sets all the required variablesw
		height = h;
		width = w;
		data = mData;

		totalV = height * width;

		generatedVertex = nullptr;

		Setup();
	}

	//Generates the Vertices list
	void Graph::Setup()
	{
		//Generates the 2d vector of vertices
		// Have to go row by row and then push to start next row
		for (int j = 0; j < height; j++) {
			// 1 row of vertices
			vector<Vertex> row;

			for (int i = 0; i < width; i++)
			{
				// If not a wall, add to matrix
				if (data[i][j] == 0) {
					generatedVertex = new Vertex(i, j);
					// Push to the back of the list of vertices
					row.push_back(*generatedVertex);
				}
			}

			// Push into the 2d vector of vertices
			vertices.push_back(row);
		}

		// Set up adjacency matrix
		for (int j = 0; j < totalV; j++) {
			vector<int> row;

			for (int i = 0; i < totalV; i++)
			{ 

				//if right is null
				if (adjacency[j+1][i] == NULL)
				{
					//Do nothing
				}
				else{
					//Add an edge connection
					adjacency[j + 1][i] = 1;
					adjacency[i][j + 1] = 1;
				}

				//if up is null
				if (adjacency[j][i + 1] == NULL) {
					//Do nothing
				}
				else {
					//Add an edge connection
					adjacency[j][i + 1] = 1;
					adjacency[i + 1][j] = 1;
				}

				//If down is null
				if (adjacency[j][i - 1] == NULL) {
					//Do nothing
				}
				else {
					//Add an edge connection
					adjacency[j][i - 1] = 1;
					adjacency[i - 1][j] = 1;
				}

				//If left is null
				if (adjacency[j - 1][i] == NULL) {
					//Do nothing
				}
				else {
					//Add an edge connection
					adjacency[j - 1][i] = 1;
					adjacency[i][j - 1] = 1;
				}

			}
			adjacency.push_back(row);
		}

	}
			


	// Methods

	/// <summary>
	/// A* pathfinding method. Only call once
	/// </summary>
	void Graph::aStar(int startX, int startY, int endX, int endY)
	{

		// Add starting vertex to closed list
		closed.push_front(&vertices[startX][startY]);

		// Add all adjacent tiles to open list
		if (adjacency[startX + 1][startY] == 1) {
			open.push_front(&vertices[startX + 1][startY]);
			vertices[startX + 1][startY].UpdateParent(vertices[startX][startY]);
		}
		if (adjacency[startX - 1][startY] == 1) {
			open.push_front(&vertices[startX - 1][startY]);
			vertices[startX - 1][startY].UpdateParent(vertices[startX][startY]);
		}
		if (adjacency[startX][startY + 1] == 1) {
			open.push_front(&vertices[startX][startY + 1]);
			vertices[startX][startY + 1].UpdateParent(vertices[startX][startY]);
		}
		if (adjacency[startX][startY - 1] == 1) {
			open.push_front(&vertices[startX][startY - 1]);
			vertices[startX][startY - 1].UpdateParent(vertices[startX][startY]);
		}

		int xDistance;
		int yDistance;

		//Create heuristics for all tiles
		for (int i = 0; i < height; i++) {

			for (int j = 0; j < width; j++) {
				xDistance = abs(vertices[i][j].xPos - endX);
				yDistance = abs(vertices[i][j].yPos - endY);

				vertices[i][j].GenerateHeuristic(xDistance + yDistance);
			}
		}

		// Find shortest path
		
		while (true) {
		// Get square on open list with lowest score, s
			Vertex s = *open.front();

			for(auto v: open)
			{
				if (s.ReturnG() + s.heuristic > v->ReturnG() + v->heuristic)
				{
					s = *v;
				}
			}

		// Remove s from open list & add to closed

			open.remove(&s);
			closed.push_front(&s);

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

		
	}
