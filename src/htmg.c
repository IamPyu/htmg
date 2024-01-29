#include <SDL2/SDL.h>
#include <stdlib.h>
#include "htmg.h"

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Event event;
// static htmg_Color drawColor;

void PrintSDLError() {
  printf("An SDL2 error occured: %s\n", SDL_GetError());
}

SDL_Rect *CreateRect(int x, int y, int width, int height) {
  SDL_Rect *rect = malloc(sizeof(SDL_Rect));
  rect->x = x;
  rect->y = y;
  rect->w = width;
  rect->h = height;
  return rect;
}

int InitWindow(int width, int height, const char *title) {
  SDL_Init(SDL_INIT_EVERYTHING);
  if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL, &window, &renderer)) {
    PrintSDLError();
    SDL_Quit();
    return 1;
  }

  SDL_SetWindowTitle(window, title);
  return 0;
}

void CloseWindow() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

int WindowShouldClose() {
  if (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      return 1;
      break;
      
    default:
      break;
    }
  }

  return 0;
}

void BeginDrawing(htmg_Color bgColor) {
  SetDrawColorStruct(bgColor);
  SDL_RenderClear(renderer);
}

void EndDrawing() {
  SDL_RenderPresent(renderer);
}

void SetDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
void SetDrawColorStruct(htmg_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void DrawRect(int x, int y, int width, int height) {
  SDL_Rect *rect = CreateRect(x, y, width, height);
  SDL_RenderDrawRect(renderer, rect);
  free(rect);
}

void FillRect(int x, int y, int width, int height) {
  SDL_Rect *rect = CreateRect(x, y, width, height);
  SDL_RenderFillRect(renderer, rect);
  free(rect);
}