#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "media.h"
#include "init.h"
#include "Ball.h"
#include "Player.h"
#include "Vector2D.h"
#include "PhysicsObject.h"
#include "Goal.h"
#include "utils.h"

#define FPS 60.0

int groundY = 665;

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

  Team *blueTeam = new Team(Blue);
  blueTeam->addPlayer(new Player(Blue, 100, groundY, renderer, screenSurface));
  blueTeam->addPlayer(new Player(Blue, 300, groundY, renderer, screenSurface));
  Player *blueSelectedPlayer = blueTeam->selectPlayer();

  Team *redTeam = new Team(Red);
  redTeam->addPlayer(new Player(Red, 1180, groundY, renderer, screenSurface));
  redTeam->addPlayer(new Player(Red, 980, groundY, renderer, screenSurface));
  Player *redSelectedPlayer = redTeam->selectPlayer();

  Ball *soccerBall = new Ball(renderer, screenSurface);

  Goal *blueGoal = new Goal(Blue, 0, 720 - 256, renderer, screenSurface);
  Goal *redGoal = new Goal(Red, 1280 - 128, 720 - 256, renderer, screenSurface);

  // Main Loop Flag
  bool quit = false;

  // Event Handler
  SDL_Event event;

  float lastTime = ((float)SDL_GetTicks()) / ((float)FPS);

  // while application is running
  while (!quit)
  {
    float newTime = ((float)SDL_GetTicks()) / ((float)FPS);

    float dt = newTime - lastTime;

    if (dt > 1.0 / 60.0)
      dt = 1.0 / 60.0;

    // printf("FPS: %f\n", 1 / dt);
    lastTime = newTime;

    SDL_Delay(1 / FPS);

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        quit = true;
      }

      const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
      if (event.type == SDL_KEYDOWN)
      {
        if (currentKeyStates[SDL_SCANCODE_A] && currentKeyStates[SDL_SCANCODE_D])
        {
          blueSelectedPlayer->stop();
        }
        else if (currentKeyStates[SDL_SCANCODE_A])
        {
          blueSelectedPlayer->move('l');
        }
        else if (currentKeyStates[SDL_SCANCODE_D])
        {
          blueSelectedPlayer->move('r');
        }

        if (currentKeyStates[SDL_SCANCODE_J] && currentKeyStates[SDL_SCANCODE_L])
        {
          redSelectedPlayer->stop();
        }
        else if (currentKeyStates[SDL_SCANCODE_J])
        {
          redSelectedPlayer->move('l');
        }
        else if (currentKeyStates[SDL_SCANCODE_L])
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
        if (!currentKeyStates[SDL_SCANCODE_A] && !currentKeyStates[SDL_SCANCODE_D])
        {
          blueSelectedPlayer->stop();
        }
        if (!currentKeyStates[SDL_SCANCODE_J] && !currentKeyStates[SDL_SCANCODE_L])
        {
          redSelectedPlayer->stop();
        }
      }
    }

    if (blueSelectedPlayer->getIsJumpint())
    {
      printf("Dt: %f\n", dt);
    }

    blueTeam->update(dt);
    redTeam->update(dt);
    soccerBall->update(dt);

    blueTeam->drop();
    redTeam->drop();

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderCopy(renderer, background, NULL, NULL);

    blueTeam->draw(renderer);
    redTeam->draw(renderer);

    soccerBall->draw(renderer);

    blueGoal->draw(renderer);
    redGoal->draw(renderer);

    // Update screen
    SDL_RenderPresent(renderer);

    for (int i = 0; i < 4; i++)
    {
      Player *p = Player::_allPlayers[i];
      Vector2D cPoint = collidePlayerAndBall(p, soccerBall);
      if (!isRootVector(cPoint))
      {
        if (cPoint.getX() > p->getPosition().getX() && !p->getTurnLeft())
        {
          p->setVelocity(0, p->getVelocity().getY());
          p->setPosition(p->getPosition().getX() - 1, p->getPosition().getY());
        }
        else if (cPoint.getX() < p->getPosition().getX() && p->getTurnLeft())
        {
          p->setVelocity(0, p->getVelocity().getY());
          p->setPosition(p->getPosition().getX() + 1, p->getPosition().getY());
        }
      }
    }

    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        Player *p1 = Player::_allPlayers[i];
        Player *p2 = Player::_allPlayers[j];
        if (p1 != p2)
        {
          Vector2D cPoint = collidePlayerAndPlayer(p1, p2);
          if (!isRootVector(cPoint))
          {
            if (p1->getPosition().getX() < cPoint.getX() && cPoint.getX() < p2->getPosition().getX())
            {
              printf("hihi1\n");
              printf("%f--%f--%f\n", p1->getPosition().getX(), cPoint.getX(), p2->getPosition().getX());
              p1->setPosition(p1->getPosition().getX() - 5, p1->getPosition().getY());
              p2->setPosition(p2->getPosition().getX() + 5, p2->getPosition().getY());
            }
            else if (p1->getPosition().getX() >= cPoint.getX() && cPoint.getX() >= p2->getPosition().getX())
            {
              printf("hihi2\n");
              p1->setPosition(p1->getPosition().getX() + 5, p1->getPosition().getY());
              p2->setPosition(p2->getPosition().getX() - 5, p2->getPosition().getY());
            }
          }
        }
      }
    }
  }

  // Free resourcs and close SDL
  destroyMedia();
  close();

  return EXIT_SUCCESS;
}