#include "SDL_events.h"
#include "SDL_video.h"
#include <iostream>
#include <SDL.h>
#include "window.h"
#include "sakoengine.h"

int main() {

  // turn on everything

  // done in sakoengine.cpp
  // if (!SDL_INIT_EVERYTHING) {
  //   std::cout << "[CRITICAL] SDL3 FAILED TO LOAD!" << std::endl;
  //   return 1;
  // };

  // SakoEngine::init();

  SakoEngine::init();

  // predefined height

  int width = 800;
  int height = 800;

  // create window

  Window window("SakoEngine");
  // Window window2("SakoEngine 2");

  // renderer to display window on *NIX
  // on Windows systems the window will show without one

  // SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED);

  // if (!renderer) {
  //   SDL_Log("[CRITICAL SDL failed to create renderer!");
  //   return 1;
  // };

  // game loop

  {

  Window window("SakoEngine");

  bool running = true;

  while (running) {
    // set the event variable

    SDL_Event event;

    // SDL_PollEvent uses the event variable's pointer reference (?)

    //SDL_PollEvent(&event);

    while (SDL_PollEvent(&event)) {
      // Event Handling Here
      if (event.type == SDL_EventType::SDL_EVENT_QUIT) {
	running = false;
      };
    };
    
  };
  
  }

  // destroy renderer
  //SDL_DestroyRenderer(renderer);
  // SDL_QuitSubSystem(SDL_InitFlags::SDL_INIT_VIDEO);

  SakoEngine::quit();
  return 0;
}
