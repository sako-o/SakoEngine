#include <iostream>
#include <stdio.h>
#include "../lib/SDL/include/SDL3/SDL.h"

int main(){
  if (!SDL_INIT_EVERYTHING){
    std::cout << "SDL_INIT_EVERYTHING failed" << std::endl;
    return 1;
  }
  
  std::cout << SDL_INIT_EVERYTHING << std::endl;

  return 0;
}
