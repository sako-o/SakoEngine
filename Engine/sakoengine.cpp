#include "sakoengine.h"
#include "SDL_error.h"
#include "SDL_log.h"
#include <SDL.h>

void SakoEngine::init() {
  // TODO(sako) make it read through an array to init each submodule
  // TODO(sako) add extra submodules 
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Init(SDL_INIT_AUDIO);

  Uint32 video_init;
  video_init = SDL_WasInit(SDL_INIT_VIDEO);

  Uint32 audio_init;
  audio_init = SDL_WasInit(SDL_INIT_AUDIO);



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
  SDL_QuitSubSystem(SDL_InitFlags::SDL_INIT_VIDEO);
}
