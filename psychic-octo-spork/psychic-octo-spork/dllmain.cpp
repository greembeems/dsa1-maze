// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

const char* team = "Holly A & Josh T";

// Maze Data
int mWidth;
int mHeight;
//const int** mData;
// Start
int sXPos;
int sYPos;
//End
int eXPos;
int eYPos;

// Test x and y for GetNextPosition
int positions[10][2] = { {1,1}, {2,2}, {3,3}, {4,4}, {5,5}, {6,6}, {7,7}, {8,8}, {9,9}, {10,10} };
int currentIndex = 0;

// Returns string with team members' names
char* GetTeam()
{
    return (char*)team;
}

// Sets maze data from main program
void SetMaze(const int** data, int width, int height)
{
    //mData = data;
    mWidth = width;
    mHeight = height;
}

// Return maze data that was passed in from SetMaze
int** GetMaze(int& width, int& height)
{
    //return ;
}

// Returns next x and y position
void GetNextPosition(int& xpos, int& ypos)
{

}

// Sets starting location for player
// Save x and y value
void SetStart(int xpos, int ypos)
{
    sXPos = xpos;
    sYPos = ypos;
}

// Get starting location for player
// Return x and y, -1 if not stored
void GetStart(int& xpos, int& ypos)
{

}

// Sets ending location for player
void SetEnd(int xpos, int ypos)
{
    eXPos = xpos;
    eYPos = ypos;
}

// Get ending location for player
// Return x and y, -1 if not stored 
void GetEnd(int& xpos, int& ypos)
{

}

