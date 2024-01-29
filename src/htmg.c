#include "htmg.h"
#include <SDL2/SDL.h>

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Event event;

void printSDLError() {
  printf("An SDL2 error occured: %s\n", SDL_GetError());
}

int InitWindow(int width, int height, const char *title) {
  SDL_Init(SDL_INIT_EVERYTHING);
  if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL, &window, &renderer)) {
    printSDLError();
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
