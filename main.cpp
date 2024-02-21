#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "media.h"
#include "init.h"
#include "Ball.h"
#include "Vector2D.h"
// #include "texture.h"

SDL_Texture *background = NULL;

SDL_Window *window = NULL;

SDL_Surface *screenSurface = NULL;

SDL_Renderer *renderer = NULL;

std::vector<Vector2D> externalForces{
    Vector2D(0, 1),
};

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

  SDL_Texture *surface1 = loadTexture("assets/playerHead.png", renderer, screenSurface);
  SDL_Texture *surface2 = loadTexture("assets/playerHead.png", renderer, screenSurface);

  // Apply the image
  SDL_Rect playerRect;
  playerRect.x = 100;
  playerRect.y = 100;
  playerRect.w = playerRect.h = 100;

  SDL_Rect playerRect2;
  playerRect2.x = 500;
  playerRect2.y = 100;
  playerRect2.w = playerRect2.h = 100;

  Ball soccerBall{renderer, screenSurface};

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
    SDL_RenderCopy(renderer, background, NULL, NULL);
    // SDL_RenderDrawLine(renderer, 5, 5, 400, 400);
    SDL_RenderCopyEx(renderer, surface1, NULL, &playerRect, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(renderer, surface2, NULL, &playerRect2, 0, NULL, SDL_FLIP_HORIZONTAL);

    soccerBall.draw(renderer);

    // Update screen
    SDL_RenderPresent(renderer);
  }

  // Free resourcs and close SDL
  destroyMedia();
  close();

  return EXIT_SUCCESS;
}