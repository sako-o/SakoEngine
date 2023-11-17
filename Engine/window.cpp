#include "window.h"
#include "SDL_assert.h"
#include "SDL_error.h"
#include "SDL_video.h"
#include <stdexcept>

Window::Window(const std::string &title, int width, int height,
	       SDL_WindowFlags flags) : m_window(SDL_CreateWindow(title.c_str(), width, height, flags), &SDL_DestroyWindow) {

  if(!m_window) 
    throw std::runtime_error(SDL_GetError());


};