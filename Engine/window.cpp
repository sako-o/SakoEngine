#include "window.h"
#include "SDL_error.h"
#include "SDL_log.h"
#include "SDL_video.h"
#include <SDL.h>
#include <exception>
#include <stdexcept>

// make a new window via the Window variable
// this has everything needed (hopefully)
Window::Window(const std::string &title, int width, int height,
                   SDL_WindowFlags flags, SDL_RendererFlags renderer_flags) {

  // TODO Add more handling to this to make sure we don't accidentally change the resolution?
  // bool fullscreen = false;
  // if (fullscreen)
  //   flags = SDL_WINDOW_FULLSCREEN;

  // make the window with the needed things
    SDL_Window *m_window =
        SDL_CreateWindow(title.c_str(), width, height, flags);

    // error handling
    if (!m_window)
      throw std::runtime_error(SDL_GetError());

    // log it
    SDL_Log("Window has loaded");

    // make the renderer
    // required on some platforms
    SDL_Renderer *m_renderer =
        SDL_CreateRenderer(m_window, NULL, renderer_flags);

    // error handling
    if (!m_renderer)
      throw std::runtime_error(SDL_GetError());

    // log it
    SDL_Log("Renderer has loaded");
  };
