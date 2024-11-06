#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <iostream>
#include <string>

// vars
bool running = true;
int w_height = 600;
int w_width = 800;

bool init();

bool init() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL Failed with %s", SDL_GetError());
    return false;
  } else {
    return true;
  };
};

int main() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL Failed with %s", SDL_GetError());
    return 1;
  };

  SDL_Window *sdl_window =
      SDL_CreateWindow("SakoEngine", w_width, w_height, SDL_WINDOW_VULKAN);

  if (!sdl_window) {
    SDL_Log("Failed to create window, %s", SDL_GetError());
    return 1;
  };

  SDL_Renderer *sdl_renderer = SDL_CreateRenderer(sdl_window, nullptr);

  if (!sdl_renderer) {
    SDL_Log("Failed to create renderer, %s", SDL_GetError());
    return 1;
  };

  SDL_Surface *sdl_windowSurface = SDL_GetWindowSurface(sdl_window);

  std::string imagePath{"wires.bmp"};

  SDL_Surface *wires = SDL_LoadBMP(imagePath.c_str());

  if (!wires) {
    SDL_Log("I can't find wires this is why, %s", SDL_GetError());
    return 1;
  };

  while (running) {
    SDL_Event sdl_event;
    while (SDL_PollEvent(&sdl_event)) {
      switch (sdl_event.type) {
      case SDL_EVENT_QUIT:
        running = false;
      case SDL_EVENT_KEY_DOWN:
        SDL_Log("Key");
        switch (sdl_event.key.key) {
        case SDLK_ESCAPE:
          running = false;
        };
      };
    };
    SDL_BlitSurface(wires, nullptr, sdl_windowSurface, nullptr);
    SDL_UpdateWindowSurface(sdl_window);
    SDL_Delay(10);
  };

  SDL_DestroyWindow(sdl_window);

  SDL_DestroyRenderer(sdl_renderer);

  SDL_DestroySurface(wires);

  SDL_Log("See you next time...");

  SDL_Quit();

  return 0;
}
