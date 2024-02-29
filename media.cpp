#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "media.h"

bool loadMedia(SDL_Renderer *renderer, SDL_Surface *screenSurface)
{
  // Loading success flag
  bool success = true;

  // Loadsplash image
  // helloWorld = loadTexture("assets/hello_world.bmp", renderer, screenSurface);
  background = loadTexture("assets/bg.png", renderer, screenSurface);
  if (background == NULL)
  {
    std::cout << "Unable to load image "
              << "std/map.png"
              << "SDL Error: " << SDL_GetError() << std::endl;
    success = false;
  }

  return success;
}

void destroyMedia()
{
  // Deallocate texture
  SDL_DestroyTexture(background);
  background = NULL;
}

SDL_Surface *loadSurface(std::string path, SDL_Surface *screenSurface)
{
  // The final optimized image
  SDL_Surface *optimizedSurface = NULL;

  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  // SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
  if (loadedSurface == NULL)
  {
    std::cout << "Unable to load image "
              << path.c_str() << "! "
              << "SDL Error: " << SDL_GetError() << std::endl;
  }
  else
  {
    // Convert Surface to screen format
    optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
    if (optimizedSurface == NULL)
    {
      printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
      Uint32 color_key = SDL_MapRGB(optimizedSurface->format, 111, 49, 152);
      SDL_SetColorKey(optimizedSurface, SDL_TRUE, color_key);
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  return optimizedSurface;
}

SDL_Texture *loadTexture(std::string path, SDL_Renderer *renderer, SDL_Surface *screenSurface)
{
  // The final texture
  SDL_Texture *newTexture = NULL;

  // Load image at specified path
  SDL_Surface *loadedSurface = loadSurface(path.c_str(), screenSurface);

  // Create texture from surface pixels
  newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
  if (newTexture == NULL)
  {
    printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
  }

  // Get rid of old loaded surface
  SDL_FreeSurface(loadedSurface);

  return newTexture;
}