#include <SDL.h>
#include <SDL_events.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_opengl.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>

int main(int argc, char *argv[]) {
  // init everything
  // SDL_Init(SDL_INIT_EVERYTHING);
  // check if SDL_Init worked properly
  // if (!SDL_INIT_EVERYTHING) {
  // printf("SDL failed to initalize: %s\n", SDL_GetError());
  //  return 1;
  //}
  //
  // vulkan tutorial
  // https://github.com/AndreVallestero/sdl-vulkan-tutorial/blob/master/hello-triangle/main.cpp

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Vulkan_LoadLibrary(nullptr);

  // Window to place renderer in
  SDL_Window *window = SDL_CreateWindow("SakoEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_VULKAN);

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
      // TODO(sako) fix this
      default:
        break;
      case SDL_KEYDOWN:
        isRunning = false;
      case SDL_KEYUP:
        isRunning = false;
      case SDL_QUIT:
        isRunning = false;
        break;
      }
  }

  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
