#include "Scoreboard.h"
#include <SDL2/SDL_ttf.h>

Scoreboard::Scoreboard() : blueScore(0), redScore(0), isGoal(false)
{
  ourFont = TTF_OpenFont("./fonts/Roboto-Black.ttf", 64);
  if (ourFont == nullptr)
  {
    std::cout << "Could not load font" << std::endl;
    exit(1);
  }
}

void Scoreboard::draw(SDL_Renderer *renderer)
{
  std::string text = std::to_string(blueScore) + " : " + std::to_string(redScore);
  SDL_Surface *surfaceText = TTF_RenderText_Solid(ourFont, text.c_str(), {0, 0, 0});

  textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);

  SDL_FreeSurface(surfaceText);

  SDL_Rect boardRect;
  boardRect.x = 580;
  boardRect.y = 100;
  boardRect.w = 160;
  boardRect.h = 80;

  SDL_RenderCopy(renderer, textureText, NULL, &boardRect);
}

void Scoreboard::upScore(char g)
{
  if (g == 'r')
    redScore += 1;
  else
    blueScore += 1;
}

void Scoreboard::destroy()
{
  SDL_DestroyTexture(textureText);
  TTF_CloseFont(ourFont);
}

bool Scoreboard::getIsGoal()
{
  return isGoal;
}

void Scoreboard::setIsGoal(bool g)
{
  isGoal = g;
}