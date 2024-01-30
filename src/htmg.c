#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
#include "htmg.h"

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Event event;
// static htmg_Color drawColor;

// Private utility functions

void PrintSDLError() {
  printf("An SDL2 error occured: %s\n", SDL_GetError());
}

SDL_Rect CreateRect(int x, int y, int width, int height) {
  SDL_Rect rect = {0};
  rect.x = x;
  rect.y = y;
  rect.w = width;
  rect.h = height;
  return rect;
}

// Window functions

int InitWindow(int width, int height, const char *title) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    PrintSDLError();
    SDL_Quit();
    return 1;
  }

  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP | IMG_INIT_TIF);
  Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3 | MIX_INIT_WAVPACK);

  if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL, &window, &renderer) != 0) {
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

// Event-related functions

int IsKeyPressed(SDL_KeyCode key) {
  if (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN: {
        if (event.key.keysym.sym == key) {
          return 1;
        }
        break;
      }
      default: break;
    }
  }

  return 0;
}

int IsKeyReleased(SDL_KeyCode key) {
  if (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYUP: {
        if (event.key.keysym.sym == key) {
          return 1;
        }
        break;
      }
      default: break;
    }
  }

  return 0;
}

// Drawing functions

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
  SDL_Rect rect = CreateRect(x, y, width, height);
  SDL_RenderDrawRect(renderer, &rect);
}

void FillRect(int x, int y, int width, int height) {
  SDL_Rect rect = CreateRect(x, y, width, height);
  SDL_RenderFillRect(renderer, &rect);
}

int DrawTexture(int x, int y, int width, int height, const char *filePath) {
  SDL_Texture *tex = IMG_LoadTexture(renderer, filePath);
  SDL_Rect rect = CreateRect(x, y, width, height);

  if (tex == NULL) {
    PrintSDLError();
    return 1;
  }

  SDL_RenderCopy(renderer, tex, NULL, &rect);

  SDL_DestroyTexture(tex); // I dont care if I am allocating images every single damn frame because it works!
  return 0;
}

int PlaySound(const char *filePath) {
  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) != 0) {
    PrintSDLError();
    return 1;
  }

  Mix_Chunk *sound = Mix_LoadWAV(filePath);
  if (sound == NULL) {
    PrintSDLError();
    return 1;
  }

  Mix_PlayChannel(-1, sound, 0);

  return 0;
}