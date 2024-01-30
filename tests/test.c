#include <stdio.h>
#include "../src/htmg.h"

int main(void) {
  InitWindow(1000, 800, "How to make games?!?!!?!?");

  while (!WindowShouldClose()) {
    BeginDrawing((htmg_Color){255, 255, 0, 255});

    SetDrawColor(0, 90, 255, 255);
    FillRect(300, 300, 230, 230);

    SetDrawColor(255, 0, 0, 255);
    FillRect(0, 0, 200, 200);

    //DrawTexture(50, 50, 200, 120, "./tests/water.png");

    EndDrawing();
  }
  
  CloseWindow();
  
  return 0;
}
