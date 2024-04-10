#include "sakoengine.h"
#include "SDL_error.h"
#include "SDL_log.h"
#include <SDL.h>

void SakoEngine::init() {
  // TODO(sako) make it read through an array to init each submodule
  // TODO(sako) add extra submodules 

  // init modules
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Init(SDL_INIT_AUDIO);

  // make specific variable for checking status 
  Uint32 video_init;
  video_init = SDL_WasInit(SDL_INIT_VIDEO);

  Uint32 audio_init;
  audio_init = SDL_WasInit(SDL_INIT_AUDIO);

  // error handling
  if(video_init&SDL_INIT_VIDEO)
    SDL_Log("VIDEO READY");
  else
    SDL_LogCritical(SDL_LogCategory::SDL_LOG_CATEGORY_ERROR, "VIDEO FAILED \n %s", SDL_GetError());
  
  if(audio_init&SDL_INIT_AUDIO)
    SDL_Log("AUDIO READY");
  else
    SDL_LogCritical(SDL_LogCategory::SDL_LOG_CATEGORY_ERROR, "AUDIO FAILED \n %s", SDL_GetError());
  
  
}

void SakoEngine::quit() {
  // cleanup
  SDL_QuitSubSystem(SDL_InitFlags::SDL_INIT_VIDEO);
  SDL_QuitSubSystem(SDL_InitFlags::SDL_INIT_AUDIO);
}

void SakoEngine::handleEvents() {

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
	case SDL_EventType::SDL_EVENT_KEY_DOWN:
	  // keypress event 
	  // this should differenciate between them
	  if (event.key.keysym.sym == SDL_KeyCode::SDLK_q)
	    running = false;
	default:
	  break;
        };
      };
    }
}
