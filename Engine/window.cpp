#include "window.h"
#include "SDL_error.h"
#include "SDL_log.h"
#include <SDL.h>
#include <exception>
#include <stdexcept>

// TODO Make this work

int CreateWindow(const std::string &title, int width, int height,
                 SDL_WindowFlags flags, SDL_RendererFlags renderer_flags) {

  SDL_Window* m_window = SDL_CreateWindow(title.c_str(), width, height, flags);

  if (!m_window)
    throw std::runtime_error(SDL_GetError());


  SDL_LogDebug(SDL_LOG_PRIORITY_DEBUG, "[DEBUG] Window has loaded");

  SDL_Renderer* m_renderer = SDL_CreateRenderer(m_window, NULL, renderer_flags); 

  if (!m_window)
    throw std::runtime_error(SDL_GetError());

  SDL_LogDebug(SDL_LOG_PRIORITY_DEBUG, "[DEBUG] Renderer has loaded");

  return 0;
  
};
