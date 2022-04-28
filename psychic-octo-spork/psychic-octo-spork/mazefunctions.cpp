// MazeFunctions.cpp : Exported functions for the DLL

#include "pch.h"
#include "mazefunctions.h"
#include "Vertex.h"
#include "Graph.h"

const char* team = "Holly A & Josh T & Nash F";

// Maze Data
int mWidth;
int mHeight;

// Start
int sXPos;
int sYPos;
// End
int eXPos;
int eYPos;

int currentIndex = 0;

int length = 0;

Graph* aGraph;

// Returns string with team members' names
extern "C" __declspec(dllexport) char* GetTeam()
{
    return (char*)team;
}

// Sets maze data from main program
extern "C" __declspec(dllexport) bool SetMaze(const int** data, int width, int height)
{
    if (width >= 1 || height >= 1) {
        mData = data;
        mWidth = width;
        mHeight = height;
        return true;
    }
    
    return false;
}

// Return maze data that was passed in from SetMaze
extern "C" __declspec(dllexport) int** GetMaze(int& width, int& height)
{
    width = mWidth;
    height = mHeight;

    if (mData == nullptr) {
        return nullptr;
    }
    
    return (int**)mData;
}

// Returns next x and y position
extern "C" __declspec(dllexport) bool GetNextPosition(int& xpos, int& ypos)
{
    // Calls A Star for first instance only
    if (currentIndex == 0)
    {
        aGraph = new Graph(mData, mHeight, mWidth);
        aGraph->aStar(sXPos, sYPos, eXPos, eYPos);
        aGraph->Reverse(aGraph->GetShortestPath());
    }

    Vertex *vert = aGraph->shortestPath.back();


    if ((aGraph->shortestPath)[currentIndex] != NULL) {
        xpos = vert->xPos;
        ypos = vert->yPos;

        aGraph->shortestPath.pop_back();

        currentIndex++;
        return true;
    }
    
    return false;
}

// Sets starting location for player
// Save x and y value
extern "C" __declspec(dllexport) bool SetStart(int xpos, int ypos)
{
    sXPos = xpos;
    sYPos = ypos;

    if (sXPos >= 0 && sXPos <= mWidth && sYPos >= 0 && sYPos <= mHeight) {
        return true;
    }

    return false;
}

// Get starting location for player
// Return x and y, -1 if not stored
extern "C" __declspec(dllexport) bool GetStart(int& xpos, int& ypos)
{
    if (sXPos >= 0 && sXPos <= mWidth && sYPos >= 0 && sYPos <= mHeight)
    {
        xpos = sXPos;
        ypos = sYPos;
        return true;
    }
    
    return false;
}

// Sets ending location for player
extern "C" __declspec(dllexport) bool SetEnd(int xpos, int ypos)
{
    if (xpos >= 0 && xpos <= mWidth && ypos >= 0 && ypos <= mHeight) {
        eXPos = xpos;
        eYPos = ypos;
        return true;
    }

    return false;
}

// Get ending location for player
// Return x and y, -1 if not stored 
extern "C" __declspec(dllexport) bool GetEnd(int& xpos, int& ypos)
{
    if (eXPos >= 0 && eXPos <= mWidth && eYPos >= 0 && eYPos <= mHeight)
    {
        xpos = eXPos;
        ypos = eYPos;
        return true;
    }
    
    return false;
}

extern "C" __declspec(dllexport) bool Restart() {
    currentIndex = 0;
    return true;
}

