#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

class Scoreboard
{
private:
  TTF_Font *ourFont;
  SDL_Texture *textureText;
  int blueScore;
  int redScore;
  bool isGoal;

public:
  Scoreboard();
  void draw(SDL_Renderer *renderer);
  void upScore(char g);
  void destroy();
  bool getIsGoal();
  void setIsGoal(bool g);
};

#endif
