#include "Player.h"
#include "media.h"
#include "string"

Player::Player(Team team, float x, float y, SDL_Renderer *renderer, SDL_Surface *screenSurface)
{
  std::string path = (team == Blue) ? "assets/blueHead.png" : "assets/redHead.png";
  image = loadTexture(path, renderer, screenSurface);
  cenX = x;
  cenY = y;
  rad = 50;
};

void Player::draw(SDL_Renderer *renderer)
{
  SDL_Rect playerRect;
  playerRect.w = playerRect.h = rad * 2;
  playerRect.x = cenX;
  playerRect.y = cenY;

  SDL_RendererFlip flip = (team == Blue) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
  SDL_RenderCopyEx(renderer, image, NULL, &playerRect, 0, NULL, flip);
}