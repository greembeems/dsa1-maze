# Maze Wars

# Goals
Create a DLL that can work with other applications that implements A* pathfinding and other game logic. This will be done in groups of two students. 

# Parts
The overall project is to get A* pathfinding implemented inside of a DLL that is created by the students. The main program will be given to the students and their DLL will be to be loaded and run from the executable.  The interface for the DLL could change from one part to the next.  This is a normal thing for software where requirements change.
For grading a different version of the main application will be used. This version will have possible errors when calling the various functions. Your code should be able to handle the bad data and not crash and to give back appropriate handling of the error to the calling program and/ or the output console.

# Part 1 – Building DLL
This is the start of the project and will be where the original DLL project is created by the teams.  There will be an interface (API) that the project needs to implement for the DLL to be loaded properly by the main program.    
# Details
## Part 1
For the first part, the DLL will be created and will need to implement the following functions and export them from the DLL.  A sample application project will be provided to be used to test the DLLs.  Create the project to make a DLL that is x86 (Win32).

## DLL Interface
char* GetTeam() – Returns a string that has both team members name.  Have the C string value return both team member names.  There is no defined format for this.

void SetMaze(const int** data, int width, int height) – sets the maze data from the main program into the DLL.  Save the data into a variable in the DLL.  Use this data for the GetMaze function.

int** GetMaze(int& width, int& height) – gets the maze data from the DLL. Return the maze data that was passed in using the SetMaze function, and the width/ height using the references to the arguments
void GetNextPosition(int& xpos, int& ypos) – returns the next x/y postion to move to.  For this first part, save a list of x and y values (at least 10) and then keep track of which is your current location.  Return those variables for the current position. 

void SetStart(int xpos, int ypos) – sets the starting location for the player.  Save the x and y values for the starting location.

void GetStart(int& xpos, int& ypos) – gets the starting location for the player.  Return the saved x and y starting locations.  If the x and y locations for the start have not been saved yet, then return -1 for both.

void SetEnd(int xpos, int ypos) – sets the ending location for the player.  Save the x and y values for the ending location.

void GetEnd(int& xpos, int& ypos) – gets the ending location for the player.  Return the saved x and y end locations.  If the x and y locations for the end have not been saved yet, then return -1 for both.

## Milestone 1 – Part 2 – Unit Tests
In class we went over how to make unit tests for DLLs. The second part of the milestone is to make a set of Unit Tests for your DLL. Look at each function that is being exported to the main program and come up with a minimum of 1 test per method. Make sure that all your tests pass. 
Add a Native Unit Test project to your solution and then add a reference to your DLL. This will allow you to add the methods to be tested. From here, create separate tests for each method that is being exported.
