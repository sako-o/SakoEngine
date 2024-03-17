#include <SDL_events.h>
#include <SDL_log.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <exception>
#include <iostream>
#include <SDL.h>
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

    bool running = true;

    while (running)
    {
      // set the event variable
      SDL_Event event;

      // event handling
      // maybe move this into a function?
      while (SDL_PollEvent(&event))
      {
        switch (event.type)
        {
        case SDL_EventType::SDL_EVENT_QUIT:
          running = false;
        };
      };
    }

    // cleanup
    SakoEngine::quit();
    return 0;
  };
}
