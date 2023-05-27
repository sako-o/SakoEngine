#include "SDL_error.h"
#include "SDL_init.h"
#include "SDL_log.h"
#include "SDL_video.h"
#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char *argv[]) {
  // init everything
  SDL_Init(SDL_INIT_EVERYTHING);
  // check if SDL_Init worked properly
  if (!SDL_INIT_EVERYTHING) {
    SDL_Log("%s", "SDL2 failed??? ", SDL_GetError());
    return 1;
  }

  // Window to place renderer in
  //
  // https://wiki.libsdl.org/SDL3/SDL_CreateWindow
  //
  //
  SDL_Window *window =
      SDL_CreateWindow("SakoEngine", 800, 800, SDL_WINDOW_OPENGL);

  if (window == NULL) {
    SDL_Log("%s", "how did you fail to make the window??", SDL_GetError());
    return 1;
  }

  return 0;
}
