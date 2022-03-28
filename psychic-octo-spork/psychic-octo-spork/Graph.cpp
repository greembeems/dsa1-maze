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
	list<Vertex*>* Graph::aStar(int startX, int startY, int endX, int endY)
	{

		// Add starting vertex to closed list
		closed.push_front(&vertices[startX][startY]);

		vertices[startX][startY].g = 0;

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
		bool checking = true;

		while (checking) {
		// Get the square on the open list with lowest score, s
			Vertex s = *open.front();
			
			// if tie in lowest score, continue going with most recent tile
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
			if (adjacency[s.xPos + 1][s.yPos] != NULL) {

				// if end square is on open list, add to close list
				if (s.xPos + 1 == endX && s.yPos == endY) {

					closed.push_front(&vertices[s.xPos + 1][s.yPos]);
					vertices[s.xPos + 1][s.yPos].UpdateParent(s);
					checking = false;
					break;
				}

				bool inClosed = false;
				for (auto v : closed)
				{
					if (v->xPos == (s.xPos + 1) && v->yPos == s.yPos)
					{
						inClosed = true;
						break;
					}
				}

				if (inClosed)
				{
					//In closed list
					// if t is in closed list, ignore it
				}
				else { //Not in closed list
					// if t is not in open list, add and compute score

					bool inOpen = false;
					for (auto v : open)
					{
						if (v->xPos == (s.xPos + 1) && v->yPos == s.yPos)
						{
							inOpen = true;
							break;
						}
					}

					//Iterator returns last if the vertex is not found
					if (!inOpen) { //Not in open
						open.push_front(&vertices[s.xPos + 1][s.yPos]);
						vertices[s.xPos + 1][s.yPos].UpdateParent(vertices[s.xPos][s.yPos]);
						vertices[s.xPos + 1][s.yPos].UpdateG();
					}
					else { // In open
						//Check if F score is lower on current path
						if (vertices[s.xPos + 1][s.yPos].f >= (vertices[s.xPos + 1][s.yPos].ReturnG() + vertices[s.xPos + 1][s.yPos].heuristic)) {
							//Update score and parent
							vertices[s.xPos + 1][s.yPos].UpdateF();
							vertices[s.xPos + 1][s.yPos].UpdateParent(s);
						}
					}
				}

			}

			if (adjacency[s.xPos - 1][s.yPos] != NULL) {

				// if end square is on open list, add to close list
				if (s.xPos - 1 == endX && s.yPos == endY) {

					closed.push_front(&vertices[s.xPos - 1][s.yPos]);
					vertices[s.xPos - 1][s.yPos].UpdateParent(s);
					checking = false;
					break;
				}

				bool inClosed = false;
				for (auto v : closed)
				{
					if (v->xPos == (s.xPos + 1) && v->yPos == s.yPos)
					{
						inClosed = true;
						break;
					}
				}

				if (inClosed)
				{
					//In closed list
					// if t is in closed list, ignore it
				}
				else { //Not in closed list
					// if t is not in open list, add and compute score

					bool inOpen = false;
					for (auto v : open)
					{
						if (v->xPos == (s.xPos - 1) && v->yPos == s.yPos)
						{
							inOpen = true;
							break;
						}
					}

					//Iterator returns last if the vertex is not found
					if (!inOpen) { //Not in open
						open.push_front(&vertices[s.xPos - 1][s.yPos]);
						vertices[s.xPos - 1][s.yPos].UpdateParent(vertices[s.xPos][s.yPos]);
						vertices[s.xPos - 1][s.yPos].UpdateG();
					}
					else { // In open
						//Check if F score is lower on current path
						if (vertices[s.xPos - 1][s.yPos].f >= (vertices[s.xPos - 1][s.yPos].ReturnG() + vertices[s.xPos - 1][s.yPos].heuristic)) {
							//Update score and parent
							vertices[s.xPos - 1][s.yPos].UpdateF();
							vertices[s.xPos - 1][s.yPos].UpdateParent(s);
						}
					}
				
				}

			}
			
			if (adjacency[s.xPos][s.yPos + 1] != NULL) {

				// if end square is on open list, add to close list
				if (s.xPos == endX && s.yPos + 1 == endY) {

					closed.push_front(&vertices[s.xPos][s.yPos + 1]);
					vertices[s.xPos][s.yPos + 1].UpdateParent(s);
					checking = false;
					break;
				}

				bool inClosed = false;
				for (auto v : closed)
				{
					if (v->xPos == s.xPos && v->yPos == (s.yPos + 1))
					{
						inClosed = true;
						break;
					}
				}

				if (inClosed)
				{
					//In closed list
					// if t is in closed list, ignore it
				}
				else { //Not in closed list
					// if t is not in open list, add and compute score

					bool inOpen = false;
					for (auto v : open)
					{
						if (v->xPos == s.xPos && v->yPos == (s.yPos + 1))
						{
							inOpen = true;
							break;
						}
					}

					//Iterator returns last if the vertex is not found
					if (!inOpen) { //Not in open
						open.push_front(&vertices[s.xPos][s.yPos + 1]);
						vertices[s.xPos][s.yPos + 1].UpdateParent(vertices[s.xPos][s.yPos]);
						vertices[s.xPos][s.yPos + 1].UpdateG();
					}
					else { // In open
						//Check if F score is lower on current path
						if (vertices[s.xPos][s.yPos + 1].f >= (vertices[s.xPos][s.yPos + 1].ReturnG() + vertices[s.xPos][s.yPos + 1].heuristic)) {
							//Update score and parent
							vertices[s.xPos][s.yPos + 1].UpdateF();
							vertices[s.xPos][s.yPos + 1].UpdateParent(s);
						}
					}
				}

			}
			
			if (adjacency[s.xPos][s.yPos - 1] != NULL) {

				// if end square is on open list, add to close list
				if (s.xPos == endX && s.yPos - 1 == endY) {

					closed.push_front(&vertices[s.xPos][s.yPos - 1]);
					vertices[s.xPos][s.yPos - 1].UpdateParent(s);
					checking = false;
					break;
				}

				bool inClosed = false;
				for (auto v : closed)
				{
					if (v->xPos == s.xPos && v->yPos == (s.yPos - 1))
					{
						inClosed = true;
						break;
					}
				}

				if (inClosed)
				{
					//In closed list
					// if t is in closed list, ignore it
				}
				else { //Not in closed list
					// if t is not in open list, add and compute score

					bool inOpen = false;
					for (auto v : open)
					{
						if (v->xPos == s.xPos && v->yPos == (s.yPos - 1))
						{
							inOpen = true;
							break;
						}
					}

					//Iterator returns last if the vertex is not found
					if (!inOpen) { //Not in open
						open.push_front(&vertices[s.xPos][s.yPos - 1]);
						vertices[s.xPos][s.yPos - 1].UpdateParent(vertices[s.xPos][s.yPos]);
						vertices[s.xPos][s.yPos - 1].UpdateG();
					}
					else { // In open
						//Check if F score is lower on current path
						if (vertices[s.xPos][s.yPos - 1].f >= (vertices[s.xPos][s.yPos - 1].ReturnG() + vertices[s.xPos][s.yPos - 1].heuristic)) {
							//Update score and parent
							vertices[s.xPos][s.yPos - 1].UpdateF();
							vertices[s.xPos][s.yPos - 1].UpdateParent(s);
						}
					}
				}

			}

		}

		// go backwards from end tile parent by parent to learn exact shortest path
		Vertex* currentVert = &vertices[endX][endY];
		while (currentVert->ReturnParent() != nullptr)
		{
			shortestPath.push_front(currentVert);
			currentVert = currentVert->ReturnParent();
		}

		// done!
		return &shortestPath;
	}
