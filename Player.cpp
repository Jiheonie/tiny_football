#include "Player.h"
#include "media.h"
#include "string"

Player::Player(TeamEnum t, float x, float y, SDL_Renderer *renderer, SDL_Surface *screenSurface) : PhysicsObject(x, y, 50)
{
  team = t;
  std::string path = (t == Blue) ? "assets/blueHead.png" : "assets/redHead.png";
  image = loadTexture(path, renderer, screenSurface);
  rad = 50;
  turnLeft = (t == Blue) ? false : true;
  isMoving = false;
  isJumping = false;
};

void Player::draw(SDL_Renderer *renderer)
{
  SDL_Rect playerRect;
  playerRect.w = playerRect.h = rad * 2;
  playerRect.x = position.getX() + rad;
  playerRect.y = position.getY() - rad;

  SDL_RendererFlip flip = (turnLeft == true) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
  SDL_RenderCopyEx(renderer, image, NULL, &playerRect, 0, NULL, flip);
}

void Player::move(char m)
{
  switch (m)
  {
  case 'l':
    if (!isMoving)
    {
      forces.push_back(Vector2D(-10, 0));
      turnLeft = true;
      isMoving = true;
    }
    break;
  case 'r':
    if (!isMoving)
    {
      forces.push_back(Vector2D(10, 0));
      turnLeft = false;
      isMoving = true;
    }
    break;
  case 'j':
    if (!isJumping)
    {
      forces.push_back(Vector2D(0, 20));
      isJumping = true;
    }
    break;
  case 's':
    if (isMoving)
    {
      // stop
      isMoving = false;
    }
    break;

  default:
    break;
  }
  std::cout << m;
}

Team::Team(TeamEnum c)
{
  color = c;
  selectedNumber = 0;
}

Player *Team::selectPlayer()
{
  return players[selectedNumber];
}

void Team::addPlayer(Player *p)
{
  players.push_back(p);
}

void Team::switchPlayer()
{
  selectedNumber += 1;
  if (selectedNumber == players.size())
    selectedNumber = 0;
  std::cout << selectedNumber << std::endl;
}

void Team::draw(SDL_Renderer *renderer)
{
  for (int i = 0; i < players.size(); i++)
  {
    players[i]->draw(renderer);
  }
}