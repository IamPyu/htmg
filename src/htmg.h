#pragma once
#include <stdlib.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} htmg_Color;

// Initializes the window, along with SDL2. Returns 1 on failure.
int InitWindow(int width, int height, const char *title);

// Closes the window and quits SDL2.
void CloseWindow();

// Returns a boolean describing whether the window should close or not.
int WindowShouldClose();

// Sets the draw color.
void SetDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
// Sets the draw color but with a struct.
void SetDrawColorStruct(htmg_Color color);

// Draw a rectangle onto the screen
void DrawRect(int x, int y, int width, int height);
// Draw a filled rectangle onto the screen
void FillRect(int x, int y, int width, int height);


void BeginDrawing(htmg_Color bgColor);
void EndDrawing();