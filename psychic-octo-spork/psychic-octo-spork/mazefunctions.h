
__declspec(dllexport) char* GetTeam();

__declspec(dllexport) void SetMaze(const int** data, int width, int height);

__declspec(dllexport) int** GetMaze(int& width, int& height);

__declspec(dllexport) void GetNextPosition(int& xpos, int& ypos);

__declspec(dllexport) void SetStart(int xpos, int ypos);

__declspec(dllexport) void GetStart(int& xpos, int& ypos);

__declspec(dllexport) void SetEnd(int xpos, int ypos);

__declspec(dllexport) void GetEnd(int& xpos, int& ypos);