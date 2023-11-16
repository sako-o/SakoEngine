#include "SDL_init.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include <iostream>
#include <SDL.h>

int main() {

  if (!SDL_INIT_EVERYTHING) {
    std::cout << "[CRITICAL] SDL3 FAILED TO LOAD!" << std::endl;
    return 1;
  };

  SDL_Window* window = SDL_CreateWindow("SakoEngine DEV", 800, 800, SDL_WINDOW_OPENGL);

  if (!window) {
    SDL_Log("[CRITICAL] SDL failed to create window!");
    return 1;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED);

  if (!renderer) {
    SDL_Log("[CRITICAL SDL failed to create renderer!");
    return 1;
  };
  

  return 0;
}
