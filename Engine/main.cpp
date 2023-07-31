#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_init.h"
#include "SDL_log.h"
#include "SDL_video.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <stdio.h>
#include <SDL_opengl.h>
#include <SDL_vulkan.h>

int main(int argc, char *argv[]) {
  // init everything
  SDL_Init(SDL_INIT_EVERYTHING);
  // check if SDL_Init worked properly
  if (!SDL_INIT_EVERYTHING) {
    printf("SDL failed to initalize: %s\n", SDL_GetError());
    return 1;
  }

  // Window to place renderer in
  SDL_Window *window = SDL_CreateWindow("SakoEngine", 800, 600, SDL_WINDOW_OPENGL);

  if (window == NULL) {
    // SDL_Log("%s", "how did you fail to make the window??", SDL_GetError());
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  bool isRunning = true;

  // pauses execution in miliseconds
  SDL_Delay(2000);

  // tells SDL2 that the game
  while (isRunning) {
    // TODO(sako) think of a better name for this
    SDL_Event event;
    while (SDL_PollEvent(&event))
      switch (event.type) {
      default:
        break;
      case SDL_EVENT_KEY_DOWN:
        isRunning = false;
      case SDL_EVENT_KEY_UP:
        isRunning = false;
      case SDL_EVENT_QUIT:
        isRunning = false;
        break;
      }
  }

  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
