#pragma once

#include "SDL_video.h"
#include <SDL.h>
#include <memory>
#include <string>

class Window {

  // m_window is member_window
  // dealocate SDL_Window pointer 
  // decltype takes the type of function pointer decltype added in C++11
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window; 

 public:
  // TODO(sako):: Once make default dropin, set to windowed fullscreen as default.
  Window(const std::string &title, int width = 800, int height = 600, SDL_WindowFlags flags = (SDL_WindowFlags) 0); 

};
