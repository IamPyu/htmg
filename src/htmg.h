// Initializes the window, along with SDL2. Returns 1 on failure.
int InitWindow(int width, int height, const char *title);

// Closes the window and quits SDL2.
void CloseWindow();

// Returns a boolean describing whether the window should close or not.
int WindowShouldClose();
