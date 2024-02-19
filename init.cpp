#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "init.h"

bool init()
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
    return false;
  }

  // Create window
  window = SDL_CreateWindow("Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
  if (window == NULL)
  {
    std::cout << "window could not created! SDL Error: " << SDL_GetError() << std::endl;
    return false;
  }

  // create render for window
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL)
  {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return false;
  }
  // Initialize renderer color
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  // Get window surface
  screenSurface = SDL_GetWindowSurface(window);
  return true;
}

void close()
{
  // Destroy window
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  window = NULL;
  renderer = NULL;

  // Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}