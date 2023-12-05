#pragma once

#include "SDL_render.h"
#include <SDL.h>
#include <memory>
#include <string>

/*
  TODO(sako):: Idea??
  import window.h and use Window instead of SDL_Window when declaring Renderer?
  Maybe Rename Window and Renderer classes as well
  
 */

class Renderer {
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;


 public:
  explicit Renderer(const SDL_Window window, const std::string &title, SDL_RendererFlags flags = (SDL_RendererFlags) 0); 

};
