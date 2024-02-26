#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "media.h"
#include "init.h"
#include "Ball.h"
#include "Player.h"
#include "Vector2D.h"

SDL_Texture *background = NULL;

SDL_Window *window = NULL;

SDL_Surface *screenSurface = NULL;

SDL_Renderer *renderer = NULL;

std::vector<Vector2D> externalForces{
    Vector2D(0, 10),
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

  Team *blueTeam = new Team(Blue);
  blueTeam->addPlayer(new Player(Blue, 100, 300, renderer, screenSurface));
  blueTeam->addPlayer(new Player(Blue, 200, 300, renderer, screenSurface));
  Player *blueSelectedPlayer = blueTeam->selectPlayer();

  Team *redTeam = new Team(Red);
  redTeam->addPlayer(new Player(Red, 500, 300, renderer, screenSurface));
  redTeam->addPlayer(new Player(Red, 400, 300, renderer, screenSurface));
  Player *redSelectedPlayer = redTeam->selectPlayer();

  Ball *soccerBall = new Ball(renderer, screenSurface);

  // Main Loop Flag
  bool quit = false;

  // Event Handler
  SDL_Event event;

  // while application is running
  while (!quit)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        quit = true;
      }

      if (event.type == SDL_KEYDOWN)
      {
        const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_A])
        {
          blueSelectedPlayer->move('l');
        }
        if (currentKeyStates[SDL_SCANCODE_D])
        {
          blueSelectedPlayer->move('r');
        }

        if (currentKeyStates[SDL_SCANCODE_J])
        {
          redSelectedPlayer->move('l');
        }
        if (currentKeyStates[SDL_SCANCODE_L])
        {
          redSelectedPlayer->move('r');
        }

        if (event.key.repeat == 0)
        {
          if (currentKeyStates[SDL_SCANCODE_S])
          {
            blueTeam->switchPlayer();
            blueSelectedPlayer = blueTeam->selectPlayer();
          }
          if (currentKeyStates[SDL_SCANCODE_W])
          {
            blueSelectedPlayer->move('j');
          }

          if (currentKeyStates[SDL_SCANCODE_K])
          {
            redTeam->switchPlayer();
            redSelectedPlayer = redTeam->selectPlayer();
          }
          if (currentKeyStates[SDL_SCANCODE_I])
          {
            redSelectedPlayer->move('j');
          }
        }
      }

      if (event.type == SDL_KEYUP)
      {
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderCopy(renderer, background, NULL, NULL);

    blueTeam->draw(renderer);
    redTeam->draw(renderer);

    soccerBall->draw(renderer);

    // Update screen
    SDL_RenderPresent(renderer);
  }

  // Free resourcs and close SDL
  destroyMedia();
  close();

  return EXIT_SUCCESS;
}