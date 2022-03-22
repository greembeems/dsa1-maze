
__declspec(dllexport) char* GetTeam();

__declspec(dllexport) bool SetMaze(const int** data, int width, int height);

__declspec(dllexport) int** GetMaze(int& width, int& height);

__declspec(dllexport) bool GetNextPosition(int& xpos, int& ypos);

__declspec(dllexport) bool SetStart(int xpos, int ypos);

__declspec(dllexport) bool GetStart(int& xpos, int& ypos);

__declspec(dllexport) bool SetEnd(int xpos, int ypos);

__declspec(dllexport) bool GetEnd(int& xpos, int& ypos);