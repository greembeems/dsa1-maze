#include "pch.h"
#include "Graph.h"
using namespace std;

	// Constructor
	Graph::Graph(const int** mData, int h, int w)
	{
		//Sets all the required variables
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
			vector<Vertex*> row;

			for (int i = 0; i < width; i++)
			{
				// If not a wall, add to matrix
				if (data[i][j] == 0) {
					generatedVertex = new Vertex(i, j, false);
					// Push to the back of the list of vertices
					row.push_back(generatedVertex);
				}
				else {
					generatedVertex = new Vertex(i, j, true);
					// Push to the back of the list of vertices
					row.push_back(generatedVertex);
				}
			}

			// Push into the 2d vector of vertices
			vertices.push_back(row);
		}

		// Set up adjacency matrix
		for (int i = 0; i < height; i++) {
			vector<int> row;

			for (int j = 0; j < width; j++) {
				row.push_back(0);
			}
			adjacency.push_back(row);
		}

		// Set up adjacency matrix
		for (int j = 0; j < width; j++) {

			for (int i = 0; i < height; i++)
			{
				//Non-Edge case
				if (i != 0 && j != 0 && i != height - 1 && j != width - 1)
				{
					//if right is null
					if (data[j + 1][i] == 0)
					{
						//Add an edge connection
						adjacency[j + 1][i] = 1;
						adjacency[i][j + 1] = 1;
					}

					//if up is null
					if (data[j][i + 1] == 0) {
						//Add an edge connection
						adjacency[j][i + 1] = 1;
						adjacency[i + 1][j] = 1;
					}

					//If down is null
					if (data[j][i - 1] == 0) {
						//Add an edge connection
						adjacency[j][i - 1] = 1;
						adjacency[i - 1][j] = 1;
					}

					//If left is null
					if (data[j - 1][i] == 0) {
						//Add an edge connection
						adjacency[j - 1][i] = 1;
						adjacency[i][j - 1] = 1;
					}
				}

				//"Top wall" case
				if (i == 0) {

					if (j != 0) {
						//if up is null
						if (data[j][i + 1] == 0) {
							//Add an edge connection
							adjacency[j][i + 1] = 1;
							adjacency[i + 1][j] = 1;
						}
					}

					if (j != width - 1) {
						//if right is null
						if (data[j + 1][i] == 0)
						{
							//Add an edge connection
							adjacency[j + 1][i] = 1;
							adjacency[i][j + 1] = 1;
						}
					}

					//If down is null
					if (data[j][i + 1] == 0) {
						//Add an edge connection
						adjacency[j][i + 1] = 1;
						adjacency[i + 1][j] = 1;
					}
				}

				//"Left wall" case
				if (j == 0) {
					//if right is null
					if (data[j + 1][i] == 0)
					{
						//Add an edge connection
						adjacency[j + 1][i] = 1;
						adjacency[i][j + 1] = 1;
					}

					if (i != 0) {
						//If down is null
						if (data[j][i - 1] == 0) {
							//Add an edge connection
							adjacency[j][i - 1] = 1;
							adjacency[i - 1][j] = 1;
						}
					}

					if (i != height - 1) {
						
						//if up is null
						if (data[j][i + 1] == 0) {
							//Do nothing
						}
						else {
							//Add an edge connection
							adjacency[j][i + 1] = 1;
							adjacency[i + 1][j] = 1;
						}
					}
				}

				//"Bottom wall" case
				if (i == height - 1) {

					//if up is null
					if (adjacency[j][i - 1] == NULL) {
						//Do nothing
					}
					else {
						//Add an edge connection
						adjacency[j][i - 1] = 1;
						adjacency[i - 1][j] = 1;
					}

					if (j != width - 1) {
						//If right is null
						if (adjacency[j + 1][i] == NULL) {
							//Do nothing
						}
						else {
							//Add an edge connection
							adjacency[j + 1][i] = 1;
							adjacency[i][j + 1] = 1;
						}
					}
					
					if (j != 0) {
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
				}

				//"Right wall" case
				if (j == width - 1) {
					
					if (i != 0) {
						//If down is null
						if (data[j][i - 1] == 0) {
							//Add an edge connection
							adjacency[j][i - 1] = 1;
							adjacency[i - 1][j] = 1;
						}
					}

					if (i != height - 1) {
						//if up is null
						if (adjacency[j][i + 1] == 0) {
							//Add an edge connection
							adjacency[j][i + 1] = 1;
							adjacency[i + 1][j] = 1;
						}
					}

					//If left is null
					if (adjacency[j - 1][i] == 0) {
						//Add an edge connection
						adjacency[j - 1][i] = 1;
						adjacency[i][j - 1] = 1;
					}
				}
			}
			
		}
	}

	// Methods

	/// <summary>
	/// A* pathfinding method. Only call once
	/// </summary>
	bool Graph::aStar(int startX, int startY, int endX, int endY)
	{
		// Add starting vertex to closed list
		closed.emplace(closed.begin(), vertices[startY][startX]);
		
		vertices[startY][startX]->g = 0;

		// Add all adjacent tiles to open list

		//Non-Edge case
		if (startX != 0 && startY != 0 && startY != height - 1 && startX != width - 1)
		{
			//Right
			if (adjacency[startY][startX + 1] == 1 && adjacency[startY][startX + 1] != NULL && !Check_if(open, vertices[startY][startX + 1]) && !vertices[startY][startX + 1]->isWall) {
				open.emplace(open.begin(), vertices[startY][startX + 1]);
				vertices[startY][startX + 1]->UpdateParent(vertices[startY][startX]);
				vertices[startY][startX + 1]->UpdateG();
			}
			
			//Left
			if (adjacency[startY][startX - 1] != NULL && adjacency[startY][startX - 1] == 1 && !Check_if(open, vertices[startY][startX - 1]) && !vertices[startY][startX - 1]->isWall) {
				open.emplace(open.begin(), vertices[startY][startX - 1]);
				vertices[startY][startX - 1]->UpdateParent(vertices[startY][startX]);
				vertices[startY][startX - 1]->UpdateG();
			}
			
			//Down
			if (adjacency[startY + 1][startX] == 1 && adjacency[startY + 1][startX] != NULL && !Check_if(open, vertices[startY + 1][startX]) && !vertices[startY + 1][startX]->isWall) {
				open.emplace(open.begin(), vertices[startY + 1][startX]);
				vertices[startY + 1][startX]->UpdateParent(vertices[startY][startX]);
				vertices[startY + 1][startX]->UpdateG();
			}
			
			//Up
			if (adjacency[startY - 1][startX] == 1 && adjacency[startY - 1][startX] != NULL && !Check_if(open, vertices[startY - 1][startX]) && !vertices[startY - 1][startX]->isWall) {
				open.emplace(open.begin(), vertices[startY - 1][startX]);
				vertices[startY - 1][startX]->UpdateParent(vertices[startY][startX]);
				vertices[startY - 1][startX]->UpdateG();
			}
		}

		//"Top wall" case
		if (startY == 0) {

			//Up
			if (startX != 0) {
				if (adjacency[startY - 1][startX] == 1 && adjacency[startY - 1][startX] != NULL && !Check_if(open, vertices[startY - 1][startX]) && !vertices[startY - 1][startX]->isWall) {
					open.emplace(open.begin(), vertices[startY - 1][startX]);
					vertices[startY - 1][startX]->UpdateParent(vertices[startY][startX]);
					vertices[startY - 1][startX]->UpdateG();
				}
			}

			//Right
			if (startX != width - 1) {
				//if right is null
				if (adjacency[startY][startX + 1] == 1 && adjacency[startY][startX + 1] != NULL && !Check_if(open, vertices[startY][startX + 1]) && !vertices[startY][startX + 1]->isWall) {
					open.emplace(open.begin(), vertices[startY][startX + 1]);
					vertices[startY][startX + 1]->UpdateParent(vertices[startY][startX]);
					vertices[startY][startX + 1]->UpdateG();
				}
			}

			//Down
			if (adjacency[startY + 1][startX] == 1 && adjacency[startY + 1][startX] != NULL && !Check_if(open, vertices[startY + 1][startX]) && !vertices[startY + 1][startX]->isWall) {
				open.emplace(open.begin(), vertices[startY + 1][startX]);
				vertices[startY + 1][startX]->UpdateParent(vertices[startY][startX]);
				vertices[startY + 1][startX]->UpdateG();
			}
		}

		//"Left wall" case
		if (startX == 0) {
			//Right
			if (adjacency[startY][startX + 1] == 1 && adjacency[startY][startX + 1] != NULL && !Check_if(open, vertices[startY][startX + 1]) && !vertices[startY][startX + 1]->isWall) {
				open.emplace(open.begin(), vertices[startY][startX + 1]);
				vertices[startY][startX + 1]->UpdateParent(vertices[startY][startX]);
				vertices[startY][startX + 1]->UpdateG();
			}

			if (startY != 0) {
				//Up
				if (adjacency[startY - 1][startX] == 1 && adjacency[startY - 1][startX] != NULL && !Check_if(open, vertices[startY - 1][startX]) && !vertices[startY - 1][startX]->isWall) {
					open.emplace(open.begin(), vertices[startY - 1][startX]);
					vertices[startY - 1][startX]->UpdateParent(vertices[startY][startX]);
					vertices[startY - 1][startX]->UpdateG();
				}
			}

			if (startY != height - 1) {
				//Down
				if (adjacency[startY + 1][startX] == 1 && adjacency[startY + 1][startX] != NULL && !Check_if(open, vertices[startY + 1][startX]) && !vertices[startY + 1][startX]->isWall) {
					open.emplace(open.begin(), vertices[startY + 1][startX]);
					vertices[startY + 1][startX]->UpdateParent(vertices[startY][startX]);
					vertices[startY + 1][startX]->UpdateG();
				}
			}
		}

		//"Bottom wall" case
		if (startY == height - 1) {

			//Up
			if (adjacency[startY - 1][startX] == 1 && adjacency[startY - 1][startX] != NULL && !Check_if(open, vertices[startY - 1][startX]) && !vertices[startY + 1][startX]->isWall) {
				open.emplace(open.begin(), vertices[startY - 1][startX]);
				vertices[startY - 1][startX]->UpdateParent(vertices[startY][startX]);
				vertices[startY - 1][startX]->UpdateG();
			}

			//Right
			if (startX != width - 1 && !Check_if(open, vertices[startY][startX + 1]) && !vertices[startY][startX + 1]->isWall) {
				open.emplace(open.begin(), vertices[startY][startX + 1]);
				vertices[startY][startX + 1]->UpdateParent(vertices[startY][startX]);
				vertices[startY][startX + 1]->UpdateG();
			}

			//Left
			if (startX != 0 && !Check_if(open, vertices[startY][startX - 1]) && !vertices[startY][startX - 1]->isWall) {
				open.emplace(open.begin(), vertices[startY][startX - 1]);
				vertices[startY][startX - 1]->UpdateParent(vertices[startY][startX]);
				vertices[startY][startX - 1]->UpdateG();
			}
		}

		//"Right wall" case
		if (startX == width - 1) {

			//Up
			if (startY != 0 && !Check_if(open, vertices[startY - 1][startX]) && !vertices[startY - 1][startX]->isWall) {
				open.emplace(open.begin(), vertices[startY - 1][startX]);
				vertices[startY - 1][startX]->UpdateParent(vertices[startY][startX]);
				vertices[startY - 1][startX]->UpdateG();
			}

			//Down
			if (startY != height - 1 && !Check_if(open, vertices[startY + 1][startX]) && !vertices[startY + 1][startX]->isWall) {
				open.emplace(open.begin(), vertices[startY + 1][startX]);
				vertices[startY + 1][startX]->UpdateParent(vertices[startY][startX]);
				vertices[startY + 1][startX]->UpdateG();
			}

			//Left
			if (adjacency[startY][startX - 1] != NULL && adjacency[startY][startX - 1] == 1 && !Check_if(open, vertices[startY][startX - 1]) && !vertices[startY][startX - 1]->isWall) {
				open.emplace(open.begin(), vertices[startY][startX - 1]);
				vertices[startY][startX - 1]->UpdateParent(vertices[startY][startX]);
				vertices[startY][startX - 1]->UpdateG();
			}
		}

		int xDistance;
		int yDistance;

		//Create heuristics for all tiles
		for (int i = 0; i < height; i++) {

			for (int j = 0; j < vertices[i].size(); j++) {
				xDistance = abs(vertices[i][j]->xPos - endX);
				yDistance = abs(vertices[i][j]->yPos - endY);

				vertices[i][j]->GenerateHeuristic(xDistance + yDistance);
			}
		}

		// Find shortest path
		bool checking = true;

		while (checking) {
		// Get the square on the open list with lowest score, s
			Vertex *s = open.front();
			
			// if tie in lowest score, continue going with most recent tile
			for(auto v: open)
			{
				if (s->ReturnG() + s->heuristic > v->ReturnG() + v->heuristic)
				{
					s = v;
				}
			}

			// Remove s from open list & add to closed
			Remove_if(open, s);
			closed.emplace(closed.begin(), s);
			
			// For each square, t, in s's valid adjacent tiles

			//Non-Edge case
			if (s->xPos != 0 && s->yPos != 0 && s->yPos != height - 1 && s->xPos != width - 1)
			{
				//Right
				if (adjacency[s->yPos][s->xPos + 1] != NULL) {
					if (Check_if(closed, vertices[s->yPos][s->xPos + 1]) || vertices[s->yPos][s->xPos + 1]->isWall)
					{
						//In closed list
						// if t is in closed list, ignore it
					}
					else {
						if (!Check_if(open, vertices[s->yPos][s->xPos + 1])) { //Not in open
							open.emplace(open.begin(), vertices[s->yPos][s->xPos + 1]);
							vertices[s->yPos][s->xPos + 1]->UpdateParent(vertices[s->yPos][s->xPos]);
							vertices[s->yPos][s->xPos + 1]->UpdateG();
						}
						else { // In open
							//Check if F score is lower on current path
							if (vertices[s->yPos][s->xPos + 1]->f <= (vertices[s->yPos][s->xPos + 1]->ReturnG() + vertices[s->yPos][s->xPos + 1]->heuristic)) {
								//Update score and parent
								vertices[s->yPos][s->xPos + 1]->UpdateF();
								vertices[s->yPos][s->xPos + 1]->UpdateParent(s);
							}
						}
					}
					
					// if end square is on open list, add to close list
					if(s->xPos + 1 == endX && s->yPos == endY) {
						closed.emplace(closed.begin(), vertices[s->yPos][s->xPos + 1]);
						vertices[s->yPos][s->xPos + 1]->UpdateParent(s);
						checking = false;
						break;
					}
				}

				//Left
				if (adjacency[s->yPos][s->xPos - 1] != NULL) {

					if (Check_if(closed, vertices[s->yPos][s->xPos - 1]) || vertices[s->yPos][s->xPos - 1]->isWall)
					{
						//In closed list
						// if t is in closed list, ignore it
					}
					else { //Not in closed list
						// if t is not in open list, add and compute score
						if (!Check_if(open, vertices[s->yPos][s->xPos - 1])) { //Not in open
							open.emplace(open.begin(), vertices[s->yPos][s->xPos - 1]);
							vertices[s->yPos][s->xPos - 1]->UpdateParent(vertices[s->yPos][s->xPos]);
							vertices[s->yPos][s->xPos - 1]->UpdateG();
						}
						else { // In open
							//Check if F score is lower on current path
							if (vertices[s->yPos][s->xPos - 1]->f <= (vertices[s->yPos][s->xPos - 1]->ReturnG() + vertices[s->yPos][s->xPos - 1]->heuristic)) {
								//Update score and parent
								vertices[s->yPos][s->xPos - 1]->UpdateF();
								vertices[s->yPos][s->xPos - 1]->UpdateParent(s);
							}
						}
					}
					
					// if end square is on open list, add to close list
					if(s->xPos - 1 == endX && s->yPos == endY) {

						closed.emplace(closed.begin(), vertices[s->yPos][s->xPos - 1]);
						vertices[s->yPos][s->xPos - 1]->UpdateParent(s);
						checking = false;
						break;
					}
				}

				//Down
				if (adjacency[s->yPos + 1][s->xPos] != NULL) {

					if (Check_if(closed, vertices[s->yPos + 1][s->xPos]) || vertices[s->yPos + 1][s->xPos]->isWall)
					{
						//In closed list
						// if t is in closed list, ignore it
					}
					else { //Not in closed list
						// if t is not in open list, add and compute score
						if (!Check_if(open, vertices[s->yPos + 1][s->xPos])) { //Not in open
							open.emplace(open.begin(), vertices[s->yPos + 1][s->xPos]);
							vertices[s->yPos + 1][s->xPos]->UpdateParent(vertices[s->yPos][s->xPos]);
							vertices[s->yPos + 1][s->xPos]->UpdateG();
						}
						else { // In open
							//Check if F score is lower on current path
							if (vertices[s->yPos + 1][s->xPos]->f <= (vertices[s->yPos + 1][s->xPos]->ReturnG() + vertices[s->yPos + 1][s->xPos]->heuristic)) {
								//Update score and parent
								vertices[s->yPos + 1][s->xPos]->UpdateF();
								vertices[s->yPos + 1][s->xPos]->UpdateParent(s);
							}
						}
					}
					
					// if end square is on open list, add to close list
					if(s->xPos == endX && s->yPos + 1 == endY) {

						closed.emplace(closed.begin(), vertices[s->yPos + 1][s->xPos]);
						vertices[s->yPos + 1][s->xPos]->UpdateParent(s);
						checking = false;
						break;
					}
				}

				//Up
				if (adjacency[s->yPos - 1][s->xPos] != NULL) {

					if (Check_if(closed, vertices[s->yPos - 1][s->xPos]) || vertices[s->yPos - 1][s->xPos]->isWall)
					{
						//In closed list
						// if t is in closed list, ignore it
					}
					else { //Not in closed list
						// if t is not in open list, add and compute score

						if (!Check_if(open, vertices[s->yPos - 1][s->xPos])) { //Not in open
							open.emplace(open.begin(), vertices[s->yPos - 1][s->xPos]);
							vertices[s->yPos - 1][s->xPos]->UpdateParent(vertices[s->yPos][s->xPos]);
							vertices[s->yPos - 1][s->xPos]->UpdateG();
						}
						else { // In open
							//Check if F score is lower on current path
							if (vertices[s->yPos - 1][s->xPos]->f <= (vertices[s->yPos - 1][s->xPos]->ReturnG() + vertices[s->yPos - 1][s->xPos]->heuristic)) {
								//Update score and parent
								vertices[s->yPos - 1][s->xPos]->UpdateF();
								vertices[s->yPos - 1][s->xPos]->UpdateParent(s);
							}
						}
					}

					// if end square is on open list, add to close list
					if(s->xPos == endX && s->yPos - 1 == endY) {

						closed.emplace(closed.begin(), vertices[s->yPos - 1][s->xPos]);
						vertices[s->yPos - 1][s->xPos]->UpdateParent(s);
						checking = false;
						break;
					}
				}
			}

			//"Top wall" case
			if (s->yPos == 0) {

				//Right
				if (s->xPos != width - 1) {
					if (adjacency[s->yPos][s->xPos + 1] != NULL) {

						if (Check_if(closed, vertices[s->yPos][s->xPos + 1]) || vertices[s->yPos][s->xPos + 1]->isWall)
						{
							//In closed list
							// if t is in closed list, ignore it
						}
						else { //Not in closed list
							// if t is not in open list, add and compute score

							if (!Check_if(open, vertices[s->yPos][s->xPos + 1])) { //Not in open
								open.emplace(open.begin(), vertices[s->yPos][s->xPos + 1]);
								vertices[s->yPos][s->xPos + 1]->UpdateParent(vertices[s->yPos][s->xPos]);
								vertices[s->yPos][s->xPos + 1]->UpdateG();
							}
							else { // In open
								//Check if F score is lower on current path
								if (vertices[s->yPos][s->xPos + 1]->f <= (vertices[s->yPos][s->xPos + 1]->ReturnG() + vertices[s->yPos][s->xPos + 1]->heuristic)) {
									//Update score and parent
									vertices[s->yPos][s->xPos + 1]->UpdateF();
									vertices[s->yPos][s->xPos + 1]->UpdateParent(s);
								}
							}
						}
						// if end square is on open list, add to close list
						if(s->xPos + 1 == endX && s->yPos == endY) {

							closed.emplace(closed.begin(), vertices[s->yPos][s->xPos + 1]);
							vertices[s->yPos][s->xPos + 1]->UpdateParent(s);
							checking = false;
							break;
						}
					}
				}

				//Left
				if (s->xPos != 0) {
					if (adjacency[s->yPos][s->xPos - 1] != NULL) {

						if (Check_if(closed, vertices[s->yPos][s->xPos - 1]) || vertices[s->yPos][s->xPos - 1]->isWall)
						{
							//In closed list
							// if t is in closed list, ignore it
						}
						else { //Not in closed list
							// if t is not in open list, add and compute score
							if (!Check_if(open, vertices[s->yPos][s->xPos - 1])) { //Not in open
								open.emplace(open.begin(), vertices[s->yPos][s->xPos - 1]);
								vertices[s->yPos][s->xPos - 1]->UpdateParent(vertices[s->yPos][s->xPos]);
								vertices[s->yPos][s->xPos - 1]->UpdateG();
							}
							else { // In open
								//Check if F score is lower on current path
								if (vertices[s->yPos][s->xPos - 1]->f <= (vertices[s->yPos][s->xPos - 1]->ReturnG() + vertices[s->yPos][s->xPos - 1]->heuristic)) {
									//Update score and parent
									vertices[s->yPos][s->xPos - 1]->UpdateF();
									vertices[s->yPos][s->xPos - 1]->UpdateParent(s);
								}
							}
						}

						// if end square is on open list, add to close list
						if(s->xPos - 1 == endX && s->yPos == endY) {

							closed.emplace(closed.begin(), vertices[s->yPos][s->xPos - 1]);
							vertices[s->yPos][s->xPos - 1]->UpdateParent(s);
							checking = false;
							break;
						}
					}
				}
				
				//Down
				if (adjacency[s->yPos + 1][s->xPos] != NULL) {

					if (Check_if(closed, vertices[s->yPos + 1][s->xPos]) || vertices[s->yPos + 1][s->xPos]->isWall)
					{
						//In closed list
						// if t is in closed list, ignore it
					}
					else { //Not in closed list
						// if t is not in open list, add and compute score

						if (!Check_if(open, vertices[s->yPos + 1][s->xPos])) { //Not in open
							open.emplace(open.begin(), vertices[s->yPos + 1][s->xPos]);
							vertices[s->yPos + 1][s->xPos]->UpdateParent(vertices[s->yPos][s->xPos]);
							vertices[s->yPos + 1][s->xPos]->UpdateG();
						}
						else { // In open
							//Check if F score is lower on current path
							if (vertices[s->yPos + 1][s->xPos]->f <= (vertices[s->yPos + 1][s->xPos]->ReturnG() + vertices[s->yPos + 1][s->xPos]->heuristic)) {
								//Update score and parent
								vertices[s->yPos + 1][s->xPos]->UpdateF();
								vertices[s->yPos + 1][s->xPos]->UpdateParent(s);
							}
						}
					}

					// if end square is on open list, add to close list
					if(s->xPos == endX && s->yPos + 1 == endY) {

						closed.emplace(closed.begin(), vertices[s->yPos + 1][s->xPos]);
						vertices[s->yPos + 1][s->xPos]->UpdateParent(s);
						checking = false;
						break;
					}
				}
			}

			//"Left wall" case
			if (s->xPos == 0) {
				//Right
				if (adjacency[s->yPos][s->xPos + 1] != NULL) {

					

					if (Check_if(closed, vertices[s->yPos][s->xPos + 1]) || vertices[s->yPos][s->xPos + 1]->isWall)
					{
						//In closed list
						// if t is in closed list, ignore it
					}
					else { //Not in closed list
						// if t is not in open list, add and compute score

						if (!Check_if(open, vertices[s->yPos][s->xPos + 1])) { //Not in open
							open.emplace(open.begin(), vertices[s->yPos][s->xPos + 1]);
							vertices[s->yPos][s->xPos + 1]->UpdateParent(vertices[s->yPos][s->xPos]);
							vertices[s->yPos][s->xPos + 1]->UpdateG();
						}
						else { // In open
							//Check if F score is lower on current path
							if (vertices[s->yPos][s->xPos + 1]->f <= (vertices[s->yPos][s->xPos + 1]->ReturnG() + vertices[s->yPos][s->xPos + 1]->heuristic)) {
								//Update score and parent
								vertices[s->yPos][s->xPos + 1]->UpdateF();
								vertices[s->yPos][s->xPos + 1]->UpdateParent(s);
							}
						}
					}

					// if end square is on open list, add to close list
					if(s->xPos + 1 == endX && s->yPos == endY) {

						closed.emplace(closed.begin(), vertices[s->yPos][s->xPos + 1]);
						vertices[s->yPos][s->xPos + 1]->UpdateParent(s);
						checking = false;
						break;
					}
				}

				if (s->yPos != 0) {
					//Up
					if (adjacency[s->yPos - 1][s->xPos] != NULL) {



						if (Check_if(closed, vertices[s->yPos - 1][s->xPos]) || vertices[s->yPos - 1][s->xPos]->isWall)
						{
							//In closed list
							// if t is in closed list, ignore it
						}
						else { //Not in closed list
							// if t is not in open list, add and compute score

							if (!Check_if(open, vertices[s->yPos - 1][s->xPos])) { //Not in open
								open.emplace(open.begin(), vertices[s->yPos - 1][s->xPos]);
								vertices[s->yPos - 1][s->xPos]->UpdateParent(vertices[s->yPos][s->xPos]);
								vertices[s->yPos - 1][s->xPos]->UpdateG();
							}
							else { // In open
								//Check if F score is lower on current path
								if (vertices[s->yPos - 1][s->xPos]->f <= (vertices[s->yPos - 1][s->xPos]->ReturnG() + vertices[s->yPos - 1][s->xPos]->heuristic)) {
									//Update score and parent
									vertices[s->yPos - 1][s->xPos]->UpdateF();
									vertices[s->yPos - 1][s->xPos]->UpdateParent(s);
								}
							}
						}

						// if end square is on open list, add to close list
						if(s->xPos == endX && s->yPos - 1 == endY) {

							closed.emplace(closed.begin(), vertices[s->yPos - 1][s->xPos]);
							vertices[s->yPos - 1][s->xPos]->UpdateParent(s);
							checking = false;
							break;
						}
					}
				}

				if (s->yPos != height - 1) {
					//Down
					if (adjacency[s->yPos + 1][s->xPos] != NULL) {

						if (Check_if(closed, vertices[s->yPos + 1][s->xPos]) || vertices[s->yPos + 1][s->xPos]->isWall)
						{
							//In closed list
							// if t is in closed list, ignore it
						}
						else { //Not in closed list
							// if t is not in open list, add and compute score

							if (!Check_if(open, vertices[s->yPos + 1][s->xPos])) { //Not in open
								open.emplace(open.begin(), vertices[s->yPos + 1][s->xPos]);
								vertices[s->yPos + 1][s->xPos]->UpdateParent(vertices[s->yPos][s->xPos]);
								vertices[s->yPos + 1][s->xPos]->UpdateG();
							}
							else { // In open
								//Check if F score is lower on current path
								if (vertices[s->yPos + 1][s->xPos]->f <= (vertices[s->yPos + 1][s->xPos]->ReturnG() + vertices[s->yPos + 1][s->xPos]->heuristic)) {
									//Update score and parent
									vertices[s->yPos + 1][s->xPos]->UpdateF();
									vertices[s->yPos + 1][s->xPos]->UpdateParent(s);
								}
							}
						}

						// if end square is on open list, add to close list
						if(s->xPos == endX && s->yPos + 1 == endY) {

							closed.emplace(closed.begin(), vertices[s->yPos + 1][s->xPos]);
							vertices[s->yPos + 1][s->xPos]->UpdateParent(s);
							checking = false;
							break;
						}
					}
				}
			}

			//"Bottom wall" case
			if (s->yPos == height - 1) {

				//Up
				if (adjacency[s->yPos - 1][s->xPos] != NULL) {



					if (Check_if(closed, vertices[s->yPos - 1][s->xPos]) || vertices[s->yPos - 1][s->xPos]->isWall)
					{
						//In closed list
						// if t is in closed list, ignore it
					}
					else { //Not in closed list
						// if t is not in open list, add and compute score

						if (!Check_if(open, vertices[s->yPos - 1][s->xPos])) { //Not in open
							open.emplace(open.begin(), vertices[s->yPos - 1][s->xPos]);
							vertices[s->yPos - 1][s->xPos]->UpdateParent(vertices[s->yPos][s->xPos]);
							vertices[s->yPos - 1][s->xPos]->UpdateG();
						}
						else { // In open
							//Check if F score is lower on current path
							if (vertices[s->yPos - 1][s->xPos]->f <= (vertices[s->yPos - 1][s->xPos]->ReturnG() + vertices[s->yPos - 1][s->xPos]->heuristic)) {
								//Update score and parent
								vertices[s->yPos - 1][s->xPos]->UpdateF();
								vertices[s->yPos - 1][s->xPos]->UpdateParent(s);
							}
						}
					}

					// if end square is on open list, add to close list
					if(s->xPos == endX && s->yPos - 1 == endY) {

						closed.emplace(closed.begin(), vertices[s->yPos - 1][s->xPos]);
						vertices[s->yPos - 1][s->xPos]->UpdateParent(s);
						checking = false;
						break;
					}
				}

				//Right
				if (s->xPos != width - 1) {
					if (adjacency[s->yPos][s->xPos + 1] != NULL) {



						if (Check_if(closed, vertices[s->yPos][s->xPos + 1]) || vertices[s->yPos][s->xPos + 1]->isWall)
						{
							//In closed list
							// if t is in closed list, ignore it
						}
						else { //Not in closed list
							// if t is not in open list, add and compute score

							if (!Check_if(open, vertices[s->yPos][s->xPos + 1])) { //Not in open
								open.emplace(open.begin(), vertices[s->yPos][s->xPos + 1]);
								vertices[s->yPos][s->xPos + 1]->UpdateParent(vertices[s->yPos][s->xPos]);
								vertices[s->yPos][s->xPos + 1]->UpdateG();
							}
							else { // In open
								//Check if F score is lower on current path
								if (vertices[s->yPos][s->xPos + 1]->f <= (vertices[s->yPos][s->xPos + 1]->ReturnG() + vertices[s->yPos][s->xPos + 1]->heuristic)) {
									//Update score and parent
									vertices[s->yPos][s->xPos + 1]->UpdateF();
									vertices[s->yPos][s->xPos + 1]->UpdateParent(s);
								}
							}
						}

						// if end square is on open list, add to close list
						if(s->xPos + 1 == endX && s->yPos == endY) {

							closed.emplace(closed.begin(), vertices[s->yPos][s->xPos + 1]);
							vertices[s->yPos][s->xPos + 1]->UpdateParent(s);
							checking = false;
							break;
						}
					}
				}

				//Left
				if (s->xPos != 0) {
					if (adjacency[s->yPos][s->xPos - 1] != NULL) {


						if (Check_if(closed, vertices[s->yPos][s->xPos - 1]) || vertices[s->yPos][s->xPos - 1]->isWall)
						{
							//In closed list
							// if t is in closed list, ignore it
						}
						else { //Not in closed list
							// if t is not in open list, add and compute score

							if (!Check_if(open, vertices[s->yPos][s->xPos - 1])) { //Not in open
								open.emplace(open.begin(), vertices[s->yPos][s->xPos - 1]);
								vertices[s->yPos][s->xPos - 1]->UpdateParent(vertices[s->yPos][s->xPos]);
								vertices[s->yPos][s->xPos - 1]->UpdateG();
							}
							else { // In open
								//Check if F score is lower on current path
								if (vertices[s->yPos][s->xPos - 1]->f <= (vertices[s->yPos][s->xPos - 1]->ReturnG() + vertices[s->yPos][s->xPos - 1]->heuristic)) {
									//Update score and parent
									vertices[s->yPos][s->xPos - 1]->UpdateF();
									vertices[s->yPos][s->xPos - 1]->UpdateParent(s);
								}
							}
						}
						// if end square is on open list, add to close list
						if(s->xPos - 1 == endX && s->yPos == endY) {

							closed.emplace(closed.begin(), vertices[s->yPos][s->xPos - 1]);
							vertices[s->yPos][s->xPos - 1]->UpdateParent(s);
							checking = false;
							break;
						}
					}
				}
			}

			//"Right wall" case
			if (s->xPos == width - 1) {

				//Up
				if (s->yPos != 0) {
					if (adjacency[s->yPos - 1][s->xPos] != NULL) {


						if (Check_if(closed, vertices[s->yPos - 1][s->xPos]) || vertices[s->yPos - 1][s->xPos]->isWall)
						{
							//In closed list
							// if t is in closed list, ignore it
						}
						else { //Not in closed list
							// if t is not in open list, add and compute score

							if (!Check_if(open, vertices[s->yPos - 1][s->xPos])) { //Not in open
								open.emplace(open.begin(), vertices[s->yPos - 1][s->xPos]);
								vertices[s->yPos - 1][s->xPos]->UpdateParent(vertices[s->yPos][s->xPos]);
								vertices[s->yPos - 1][s->xPos]->UpdateG();
							}
							else { // In open
								//Check if F score is lower on current path
								if (vertices[s->yPos - 1][s->xPos]->f <= (vertices[s->yPos - 1][s->xPos]->ReturnG() + vertices[s->yPos - 1][s->xPos]->heuristic)) {
									//Update score and parent
									vertices[s->yPos - 1][s->xPos]->UpdateF();
									vertices[s->yPos - 1][s->xPos]->UpdateParent(s);
								}
							}
						}
						// if end square is on open list, add to close list
						if(s->xPos == endX && s->yPos - 1 == endY) {

							closed.emplace(closed.begin(), vertices[s->yPos - 1][s->xPos]);
							vertices[s->yPos - 1][s->xPos]->UpdateParent(s);
							checking = false;
							break;
						}
					}
				}

				// Down
				if (s->yPos != height - 1) {
					if (adjacency[s->yPos + 1][s->xPos] != NULL) {


						if (Check_if(closed, vertices[s->yPos + 1][s->xPos]) || vertices[s->yPos + 1][s->xPos]->isWall)
						{
							// In closed list
							// if t is in closed list, ignore it
						}
						else { // Not in closed list
							// if t is not in open list, add and compute score

							if (!Check_if(open, vertices[s->yPos + 1][s->xPos])) { //Not in open
								open.emplace(open.begin(), vertices[s->yPos + 1][s->xPos]);
								vertices[s->yPos + 1][s->xPos]->UpdateParent(vertices[s->yPos][s->xPos]);
								vertices[s->yPos + 1][s->xPos]->UpdateG();
							}
							else { // In open
								//Check if F score is lower on current path
								if (vertices[s->yPos + 1][s->xPos]->f <= (vertices[s->yPos + 1][s->xPos]->ReturnG() + vertices[s->yPos + 1][s->xPos]->heuristic)) {
									//Update score and parent
									vertices[s->yPos + 1][s->xPos]->UpdateF();
									vertices[s->yPos + 1][s->xPos]->UpdateParent(s);
								}
							}
						}
						// if end square is on open list, add to close list
						if(s->xPos == endX && s->yPos + 1 == endY) {

							closed.emplace(closed.begin(), vertices[s->yPos + 1][s->xPos]);
							vertices[s->yPos + 1][s->xPos]->UpdateParent(s);
							checking = false;
							break;
						}
					}
				}

				// Left
				if (adjacency[s->yPos][s->xPos - 1] != NULL) {


					if (Check_if(closed, vertices[s->yPos][s->xPos - 1]) || vertices[s->yPos][s->xPos - 1]->isWall)
					{
						// In closed list
						// if t is in closed list, ignore it
					}
					else { // Not in closed list
						// if t is not in open list, add and compute score

						if (!Check_if(open, vertices[s->yPos][s->xPos - 1])) { //Not in open
							open.emplace(open.begin(), vertices[s->yPos][s->xPos - 1]);
							vertices[s->yPos][s->xPos - 1]->UpdateParent(vertices[s->yPos][s->xPos]);
							vertices[s->yPos][s->xPos - 1]->UpdateG();
						}
						else { // In open
							//Check if F score is lower on current path
							if (vertices[s->yPos][s->xPos - 1]->f <= (vertices[s->yPos][s->xPos - 1]->ReturnG() + vertices[s->yPos][s->xPos - 1]->heuristic)) {
								//Update score and parent
								vertices[s->yPos][s->xPos - 1]->UpdateF();
								vertices[s->yPos][s->xPos - 1]->UpdateParent(s);
							}
						}
					}
					// if end square is on open list, add to close list
					if(s->xPos - 1 == endX && s->yPos == endY) {

						closed.emplace(closed.begin(), vertices[s->yPos][s->xPos - 1]);
						vertices[s->yPos][s->xPos - 1]->UpdateParent(s);
						checking = false;
						break;
					}
				}
			}
		}

		// go backwards from end tile parent by parent to learn exact shortest path
		Vertex* currentVert = vertices[endY][endX];
		while (currentVert->ReturnParent() != nullptr)
		{
			shortestPath.emplace(shortestPath.begin(), currentVert);
			currentVert = currentVert->ReturnParent();
		}

		// done!
		return true;
	}

	// THIS IS A DRAFT FOR A HELPER METHOD! DO NOT USE YET!!
	void Graph::Check(Vertex* v, Vertex* s, int xShift, int yShift, int endX, int endY, bool checking)
	{
		if (adjacency[s->xPos + xShift][s->yPos + yShift] != NULL) {

			// if end square is on open list, add to close list
			if (s->xPos + xShift == endX && s->yPos + yShift == endY) {

				closed.emplace(closed.begin(), vertices[s->xPos + xShift][s->yPos + yShift]);
				vertices[s->xPos + xShift][s->yPos + yShift]->UpdateParent(s);
				checking = false;
				//break;  We're going to have to find a way to fix this but that's a later issue 
				// To fix this I just made the other part of the method in an Else{}
			}

			// Added this Else here to fix?
			else
			{
				if (Check_if(closed, vertices[s->xPos + xShift][s->yPos + yShift]))
				{
					// In closed list
					// if t is in closed list, ignore it
				}
				else { // Not in closed list
					// if t is not in open list, add and compute score
					if (!Check_if(open, vertices[s->xPos + xShift][s->yPos + yShift])) { // Not in open
						open.emplace(open.begin(), vertices[s->xPos + xShift][s->yPos + yShift]);
						vertices[s->xPos + xShift][s->yPos + yShift]->UpdateParent(vertices[s->yPos][s->xPos]);
						vertices[s->xPos + xShift][s->yPos + yShift]->UpdateG();
					}
					else { // In open
						//Check if F score is lower on current path
						if (vertices[s->xPos + xShift][s->yPos + yShift]->f <= (vertices[s->xPos + xShift][s->yPos + yShift]->ReturnG() + vertices[s->yPos][s->xPos - 1]->heuristic)) {
							//Update score and parent
							vertices[s->xPos + xShift][s->yPos + yShift]->UpdateF();
							vertices[s->xPos + xShift][s->yPos + yShift]->UpdateParent(s);
						}
					}
				}
			}
		}
	}

	// Method to reverse the contents of the list
	void Graph::Reverse()
	{
		
		vector<Vertex*> reversedList;

		reversedList.resize(shortestPath.size());

		// Go though each element in the vector and reverse the elements 
		// by making a new vector and adding the elements in reversed order
		for (size_t i = 0; i < shortestPath.size(); i++)
		{
			reversedList[i] =  shortestPath[shortestPath.size() - (i + 1)];
		}

		// Make the list the reversedList we just made
		shortestPath = reversedList;
	}

	// Method used to get the shortest path
	// Used this in the mazeFunction.cpp in the GetNextPositions method 
	vector<Vertex*> Graph::GetShortestPath()
	{
		return shortestPath;
	}
	
	// Returns true if the vertex is in the vector and can be removed 
	// Does not do anything if the vertex isnt in the vector
	bool Graph::Remove_if(vector<Vertex*> list, Vertex* s)
	{
		// Check to see if the vertex is in the vector
		for (size_t i = 0; i < list.size(); i++)
		{
			// If it is then remove it and return true
			if (list[i] == s)
			{
				// Remove the vertex 
				for (size_t x = i; x < list.size()-1; x++) 
				{
					list[x] = list[x + 1];
				}
				list[list.size() - 1] = nullptr;
				list.resize(list.size() - 1);
				return true;
			}
		}

		return false;
	}

	// Returns true if the vertex is in the vector
	// Does not do anything if the vertex isnt in the vector
	bool Graph::Check_if(vector<Vertex*> list, Vertex* s)
	{
		// Check to see if the vertex is in the vector
		for (size_t i = 0; i < list.size(); i++)
		{
			// If it is then remove it and return true
			if (list[i] == s)
			{
				return true;
			}
		}

		return false;
	}