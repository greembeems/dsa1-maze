#ifdef MAZELIB_EXPORTS
#define MAZE_API __declspec(dllexport)
#else
#define MAZE_API __declspec(dllimport)
#endif

char* GetTeam();

void SetMaze(const int** data, int width, int height);

int** GetMaze(int& width, int& height);

void GetNextPosition(int& xpos, int& ypos);

void SetStart(int xpos, int ypos);

void GetStart(int& xpos, int& ypos);

void SetEnd(int xpos, int ypos);

void GetEnd(int& xpos, int& ypos);