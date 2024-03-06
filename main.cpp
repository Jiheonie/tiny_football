#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <cmath>

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

  Goal *blueGoal = new Goal(Blue, 0, 720 - 256, 128, 465, 0, 500, renderer, screenSurface);
  Goal *redGoal = new Goal(Red, 1280 - 128, 720 - 256, 128, 465, 0, 500, renderer, screenSurface);

  // Main Loop Flag
  bool quit = false;

  // Event Handler
  SDL_Event event;

  float lastTime = ((float)SDL_GetTicks()) * 1000 / ((float)FPS) / 1000;

  // while application is running
  while (!quit)
  {
    float newTime = ((float)SDL_GetTicks()) * 1000 / ((float)FPS) / 1000;
    // printf("%f--%f\n", newTime, lastTime);
    float dt = newTime - lastTime;

    if (dt > 1.0 / FPS)
      dt = 1.0 / FPS;

    lastTime = newTime;

    SDL_Delay(1.0 / FPS);

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
          blueSelectedPlayer->stop();
        else if (currentKeyStates[SDL_SCANCODE_A])
          blueSelectedPlayer->move('l');
        else if (currentKeyStates[SDL_SCANCODE_D])
          blueSelectedPlayer->move('r');

        if (currentKeyStates[SDL_SCANCODE_J] && currentKeyStates[SDL_SCANCODE_L])
          redSelectedPlayer->stop();
        else if (currentKeyStates[SDL_SCANCODE_J])
          redSelectedPlayer->move('l');
        else if (currentKeyStates[SDL_SCANCODE_L])
          redSelectedPlayer->move('r');

        if (event.key.repeat == 0)
        {
          if (currentKeyStates[SDL_SCANCODE_E])
            blueSelectedPlayer->shoot('r', soccerBall);
          if (currentKeyStates[SDL_SCANCODE_Q])
            blueSelectedPlayer->shoot('l', soccerBall);
          if (currentKeyStates[SDL_SCANCODE_S])
          {
            blueTeam->switchPlayer();
            blueSelectedPlayer = blueTeam->selectPlayer();
          }
          if (currentKeyStates[SDL_SCANCODE_W])
            blueSelectedPlayer->move('j');

          if (currentKeyStates[SDL_SCANCODE_U])
            redSelectedPlayer->shoot('l', soccerBall);
          if (currentKeyStates[SDL_SCANCODE_O])
            redSelectedPlayer->shoot('r', soccerBall);
          if (currentKeyStates[SDL_SCANCODE_K])
          {
            redTeam->switchPlayer();
            redSelectedPlayer = redTeam->selectPlayer();
          }
          if (currentKeyStates[SDL_SCANCODE_I])
            redSelectedPlayer->move('j');
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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawLine(renderer, 1152, 465, 1280, 500);
    SDL_RenderDrawLine(renderer, 128, 465, 0, 500);

    // Update screen
    SDL_RenderPresent(renderer);

    int numOfTouching = 0;
    for (int i = 0; i < 4; i++)
    {
      Player *p = Player::_allPlayers[i];
      Vector2D cPoint = collidePlayerAndBall(p, soccerBall);
      if (!isRootVector(cPoint))
      {
        numOfTouching += 1;
        Vector2D sumF = p->getSumOfForces();
        float fX = sumF.getX();
        float fY = sumF.getY();
        float cX = cPoint.getX() - p->getPosition().getX();
        float cY = cPoint.getY() - p->getPosition().getY();
        float scalar2 = pow(fX * cX + fY * cY, 2);
        float lProd2 = (pow(fX, 2) + pow(fY, 2)) * (pow(cX, 2) + pow(cY, 2));
        float cos2 = scalar2 / lProd2;
        float lPF2 = cos2 * (pow(fX, 2) + pow(fY, 2));
        float lC2 = pow(cX, 2) + pow(cY, 2);
        float pFX = std::sqrt(lPF2 / lC2 * pow(cX, 2));
        float pFY = std::sqrt(lPF2 / lC2 * pow(cY, 2));

        if (p->getIsShooting())
        {
          if (p->getTurnLeft())
            soccerBall->touch(-300000, -100000);
          else
            soccerBall->touch(300000, -100000);
          p->setIsShooting(false);
        }
        else
        {
          soccerBall->touch(pFX, pFY);
        }

        p->setVelocity(0, 0);

        float dSepX = 0;
        float dSepY = 0;
        if (cX > 0 && cY > 0)
        {
          dSepX = -10;
          dSepY = -10;
        }
        if (cX > 0 && cY < 0)
        {
          dSepX = -10;
          dSepY = 10;
        }
        if (cX > 0 && cY == 0)
        {
          dSepX = -10;
          // dSepY = -10;
        }
        if (cX < 0 && cY < 0)
        {
          dSepX = 10;
          dSepY = 10;
        }
        if (cX < 0 && cY > 0)
        {
          dSepX = 10;
          dSepY = -10;
        }
        if (cX < 0 && cY == 0)
        {
          dSepX = 10;
          // dSepY = -10;
        }
        if (cX == 0 && cY > 0)
        {
          dSepX = -10;
        }
        if (cX == 0 && cY < 0)
        {
          dSepX = 10;
        }

        p->setPosition(
            p->getPosition().getX() + dSepX,
            p->getPosition().getY() + dSepY);

        soccerBall->setPosition(
            soccerBall->getPosition().getX() - dSepX,
            soccerBall->getPosition().getY() - dSepY);
      }
    }
    if (numOfTouching == 0)
    {
      soccerBall->resetForces();
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
              p1->setPosition(p1->getPosition().getX() - 5, p1->getPosition().getY());
              p2->setPosition(p2->getPosition().getX() + 5, p2->getPosition().getY());
            }
            else if (p1->getPosition().getX() >= cPoint.getX() && cPoint.getX() >= p2->getPosition().getX())
            {
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