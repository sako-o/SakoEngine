#pragma once

#include <string>
#include <SDL.h>

class Window {

private:
  int width;
  int height;
  SDL_WindowFlags flags;
  SDL_RendererFlags renderer_flags;

public:
  
  int CreateWindow(const std::string &title, int width, int height, SDL_WindowFlags flags, SDL_RendererFlags renderer_flags);

};
