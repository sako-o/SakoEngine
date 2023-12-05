#include "renderer.h"
#include "SDL_error.h"
#include <stdexcept>
#include <SDL.h>

Renderer::Renderer(const SDL_Window window, const std::string &title,
                   SDL_RendererFlags flags)
    : m_renderer(SDL_CreateRenderer(window, title.c_str(), flags),
                 &SDL_DestroyWindow) {
  
  if(!m_renderer)
    throw std::runtime_error(SDL_GetError());

} 
