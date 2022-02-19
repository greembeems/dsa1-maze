// MazeFunctions.cpp : Exported functions for the DLL

#include "pch.h"
#include "mazefunctions.h"

const char* team = "Holly A & Josh T";

// Maze Data
int mWidth;
int mHeight;
const int** mData;
// Start
int sXPos;
int sYPos;
// End
int eXPos;
int eYPos;

// Test x and y for GetNextPosition
int positions[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int currentIndex = 0; // So that the starting indeces are 0,0

// Returns string with team members' names
__declspec(dllexport) char* GetTeam()
{
    return (char*)team;
}

// Sets maze data from main program
__declspec(dllexport) void SetMaze(const int** data, int width, int height)
{
    mData = data;
    mWidth = width;
    mHeight = height;
}

// Return maze data that was passed in from SetMaze
__declspec(dllexport) int** GetMaze(int& width, int& height)
{
    
    width = mWidth;
    height = mHeight;
    
    return (int**)mData;
}

// Returns next x and y position
__declspec(dllexport) void GetNextPosition(int& xpos, int& ypos)
{
    xpos = (int)positions[currentIndex];
    ypos = (int)positions[currentIndex];

    currentIndex++;
}

// Sets starting location for player
// Save x and y value
__declspec(dllexport) void SetStart(int xpos, int ypos)
{
    sXPos = xpos;
    sYPos = ypos;
}

// Get starting location for player
// Return x and y, -1 if not stored
__declspec(dllexport) void GetStart(int& xpos, int& ypos)
{
    if (sXPos != NULL && sYPos != NULL)
    {
        xpos = sXPos;
        ypos = sYPos;
    }
    else
    {
        xpos = -1;
        ypos = -1;
    }
}

// Sets ending location for player
__declspec(dllexport) void SetEnd(int xpos, int ypos)
{
    eXPos = xpos;
    eYPos = ypos;
}

// Get ending location for player
// Return x and y, -1 if not stored 
__declspec(dllexport) void GetEnd(int& xpos, int& ypos)
{
    if (eXPos != NULL && eYPos != NULL)
    {
        xpos = eXPos;
        ypos = eYPos;
    }
    else
    {
        xpos = -1;
        ypos = -1;
    }
}
