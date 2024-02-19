#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "media.h"
#include "init.h"
#include "Ball.h"
// #include "texture.h"

SDL_Texture *background = NULL;

SDL_Window *window = NULL;

SDL_Surface *screenSurface = NULL;

SDL_Renderer *renderer = NULL;

int main(int argc, char *argv[])
{
  // Start up SDL and create window
  if (!init())
  {
    return EXIT_FAILURE;
  }

  // Load media
  if (!loadMedia(renderer, screenSurface))
  {
    return EXIT_FAILURE;
  }

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
  {
    std::cout << "Failed to initialize SDL_image for PNG file: " << SDL_GetError() << std::endl;
  }

  SDL_Texture *surface1 = loadTexture("assets/zomb.png", renderer, screenSurface);
  SDL_Texture *surface2 = loadTexture("assets/zomb.png", renderer, screenSurface);

  // Apply the image
  SDL_Rect zombRect;
  zombRect.x = zombRect.y = 100;
  zombRect.w = 140;
  zombRect.h = 140;

  SDL_Rect zombRect2;
  zombRect2.x = zombRect2.y = 120;
  zombRect2.w = 128;
  zombRect2.h = 128;

  Ball soccerBall{};

  // SDL_RenderPresent(renderer);

  // Main Loop Flag
  bool quit = false;

  // Event Handler
  SDL_Event event;

  // while application is running
  while (!quit)
  {
    while (SDL_PollEvent(&event))
    {
      if (SDL_QUIT == event.type)
      {
        quit = true;
      }
      if (SDL_KEYDOWN == event.type)
      {
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
          std::cout << "a is down - move left" << std::endl;
          break;
        }
      }
      else if (SDL_KEYUP == event.type)
      {
        if (SDLK_a == event.key.keysym.sym)
        {
          std::cout << "a is up - stop moving left" << std::endl;
        }
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    // SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderDrawLine(renderer, 5, 5, 400, 400);
    SDL_RenderCopy(renderer, surface1, NULL, &zombRect);
    SDL_RenderCopy(renderer, surface2, NULL, &zombRect2);

    soccerBall.draw(renderer);

    // Update screen
    SDL_RenderPresent(renderer);
  }

  // Free resourcs and close SDL
  destroyMedia();
  close();

  return EXIT_SUCCESS;
}