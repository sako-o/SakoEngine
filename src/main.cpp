#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_stdinc.h>
#include <iostream>

// guid(e)
// https://sibras.github.io/OpenGL4-Tutorials/docs/Tutorials/01-Tutorial1/#part-3-opengl-rendering
int main() {

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "Failed to initalize SDL!: %s\n", SDL_GetError());
    return 1;
  } else {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SDL2 Ready!");
  }

  // Use OpenGL 4.3 core profile
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // Turn on double buffering with a 24bit Z buffer
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  // Declare window variables
  int windowWidth = 800;
  int windowHeight = 600;
  bool windowIsFullscreen = false;

  // its window time
  SDL_Window *window =
      SDL_CreateWindow("SakoEngine", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight,
                       SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL |
                           (windowIsFullscreen * SDL_WINDOW_FULLSCREEN));
  if (window == NULL) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "OpenGL Window failed! %s\n",
                    SDL_GetError());
    SDL_Quit();
    return 1;
  } else {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "OpenGL Window ready!");
  }

  // GL context
  SDL_GLContext gl_context = SDL_GL_CreateContext(window);
  if (gl_context == NULL) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "OpenGL Context failed! %s\n",
                    SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  } else {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "OpenGL Context ready!");
  }

  // vsync
  // 1 Enables
  // 0 Disbles
  // -1 makes late swaps occur immedately instead of waiting for next refresh
  SDL_GL_SetSwapInterval(-1);

  // Event Handling
  SDL_Event Event;
  bool running = true;
  while (running) {
    // Poll SDL for buffered events
    while (SDL_PollEvent(&Event)) {
      if (Event.type == SDL_QUIT)
        running = false;
      else if (Event.type == SDL_KEYDOWN) {
        if (Event.key.keysym.sym == SDLK_ESCAPE)
          running = false;
      }
    }

    // Render the scene
    // GL_Render();

    // Swap the back-buffer and present it
    SDL_GL_SwapWindow(window);
  }

  // cleanup
  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
