#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_video.h>
#include <iostream>

// vars
bool running = false;
int w_height = 800;
int w_width = 600;

SDL_Window *sdl_window;

bool init();

bool init() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL Failed with %s", SDL_GetError());
    return false;
  } else {
    return true;
  };
};

bool cleanup() {
  running = false;

  SDL_DestroyWindow(sdl_window);

  SDL_Log("See you next time...");

  return 0;
};

int main() { return 0; }
