#include <SDL_events.h>
#include <SDL_log.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <exception>
#include <iostream>
#include <SDL.h>
#include "SDL_oldnames.h"
#include "window.h"
#include "sakoengine.h"

int main()
{

  // init
  SakoEngine::init();

  // todo:: make user customiztable somehow
  // predefined height
  int width = 800;
  int height = 800;

  // create window

  Window window("SakoEngine", 800, 800, SDL_WINDOW_OPENGL, SDL_RENDERER_ACCELERATED);

  // game loop begins here

  {

    SakoEngine::handleEvents();

    // cleanup
    SakoEngine::quit();
    return 0;
  };
}
