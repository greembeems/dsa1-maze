extern const int** mData = nullptr;

extern "C" __declspec(dllexport) char* GetTeam();

extern "C" __declspec(dllexport) bool SetMaze(const int** data, int width, int height);

extern "C" __declspec(dllexport) int** GetMaze(int& width, int& height);

extern "C" __declspec(dllexport) bool GetNextPosition(int& xpos, int& ypos);

extern "C" __declspec(dllexport) bool SetStart(int xpos, int ypos);

extern "C" __declspec(dllexport) bool GetStart(int& xpos, int& ypos);

extern "C" __declspec(dllexport) bool SetEnd(int xpos, int ypos);

extern "C" __declspec(dllexport) bool GetEnd(int& xpos, int& ypos);

extern "C" __declspec(dllexport) bool Restart();