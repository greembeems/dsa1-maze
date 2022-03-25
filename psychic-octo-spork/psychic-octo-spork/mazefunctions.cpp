// MazeFunctions.cpp : Exported functions for the DLL

#include "pch.h"
#include "mazefunctions.h"

const char* team = "Holly A & Josh T";

// Maze Data
int mWidth;
int mHeight;

// Start
int sXPos;
int sYPos;
// End
int eXPos;
int eYPos;

int currentIndex = 0; // So that the starting indeces are 0,0

// Returns string with team members' names
__declspec(dllexport) char* GetTeam()
{
    return (char*)team;
}

// Sets maze data from main program
__declspec(dllexport) bool SetMaze(const int** data, int width, int height)
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
__declspec(dllexport) int** GetMaze(int& width, int& height)
{
    width = mWidth;
    height = mHeight;

    if (mData == nullptr) {
        return nullptr;
    }
    
    return (int**)mData;
}

// Returns next x and y position
__declspec(dllexport) bool GetNextPosition(int& xpos, int& ypos)
{
    xpos = (int)mData[currentIndex];
    ypos = (int)mData[currentIndex];
    currentIndex++;

    if (mData[currentIndex] != NULL) {
        return true;
    }
    
    return false;
}

// Sets starting location for player
// Save x and y value
__declspec(dllexport) bool SetStart(int xpos, int ypos)
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
__declspec(dllexport) bool GetStart(int& xpos, int& ypos)
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
__declspec(dllexport) bool SetEnd(int xpos, int ypos)
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
__declspec(dllexport) bool GetEnd(int& xpos, int& ypos)
{
    if (eXPos >= 0 && eXPos <= mWidth && eYPos >= 0 && eYPos <= mHeight)
    {
        xpos = eXPos;
        ypos = eYPos;
        return true;
    }
    
    return false;
}

__declspec(dllexport) bool Restart() {
    currentIndex = 0;
    return true;
}