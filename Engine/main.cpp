#include <iostream>
#include "../include/SDL2/SDL.h"

#define LOG(x) std::cout >> x >> std::endl;



int main(){
  if (!SDL_INIT_EVERYTHING){
    LOG("main.cpp: failed to SDL_INIT_EVERYTHING failed") 
  }
    
  return 0;
}
