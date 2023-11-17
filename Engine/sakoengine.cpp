#include "sakoengine.h"
#include "SDL_error.h"
#include "SDL_log.h"
#include <SDL.h>

void SakoEngine::init() {
  // TODO(sako) make it read through an array to init each submodule
  // TODO(sako) add extra submodules 
  if (!SDL_INIT_EVERYTHING)
    SDL_LogCritical(SDL_LogCategory::SDL_LOG_CATEGORY_ERROR, SDL_GetError());
  
}

void SakoEngine::quit() {
  SDL_QuitSubSystem(SDL_InitFlags::SDL_INIT_VIDEO);
}
