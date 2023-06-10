#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_init.h"
#include "SDL_log.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  // init everything
  SDL_Init(SDL_INIT_EVERYTHING);
  // check if SDL_Init worked properly
  if (!SDL_INIT_EVERYTHING) {
    SDL_Log("%s", "SDL2 failed??? ", SDL_GetError());
    return 1;
  }

  bool isRunning = true;

  // Window to place renderer in
  SDL_Window *window =
      SDL_CreateWindow("SakoEngine", 800, 800, SDL_WINDOW_OPENGL);

  if (window == NULL) {
    SDL_Log("%s", "how did you fail to make the window??", SDL_GetError());
    return 1;
  }

  // pauses execution in miliseconds
  //  SDL_Delay(3000);

  void PrintKeyInfo(SDL_KeyboardEvent * key);

  // tells SDL2 that the game
  while (isRunning) {
    // TODO(sako) think of a better name for this
    SDL_Event event;
    while (SDL_PollEvent(&event))
      switch (event.type) {
      default:
        break;
      case SDL_EVENT_KEY_DOWN:
      case SDL_EVENT_KEY_UP:
        PrintKeyInfo(&event.key);
      case SDL_EVENT_QUIT:
        isRunning = false;
        break;
      }
  }

  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
