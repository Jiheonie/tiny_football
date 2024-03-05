#include "Player.h"
#include "media.h"
#include "utils.h"
#include "string"

std::vector<Player *> Player::_allPlayers = {};

Player::Player(TeamEnum t, float x, float y, SDL_Renderer *renderer, SDL_Surface *screenSurface)
    : PhysicsObject(x, y, 50)
{
  team = t;
  std::string path = (t == Blue) ? "assets/blueHead.png" : "assets/redHead.png";
  image = loadTexture(path, renderer, screenSurface);
  rad = 50;
  turnLeft = (t == Blue) ? false : true;
  isMoving = false;
  isJumping = false;

  _allPlayers.push_back(this);
};

float Player::getRadius()
{
  return rad;
}

bool Player::getIsJumpint()
{
  return isJumping;
}

bool Player::getTurnLeft()
{
  return turnLeft;
}

void Player::draw(SDL_Renderer *renderer)
{
  SDL_Rect playerRect;
  playerRect.w = playerRect.h = rad * 2;
  playerRect.x = position.getX() - rad;
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
      forces.push_back(Vector2D(-100, 0));
      turnLeft = true;
      isMoving = true;
      std::cout << "l." << position.getX() << "." << position.getY() << std::endl;
    }
    break;
  case 'r':
    if (!isMoving)
    {
      forces.push_back(Vector2D(100, 0));
      turnLeft = false;
      isMoving = true;
      std::cout << "r." << position.getX() << "." << position.getY() << std::endl;
    }
    break;
  case 'j':
    if (!isJumping && position.getY() == groundY)
    {
      forces.insert(forces.begin(), Vector2D(0, -300000));
      isJumping = true;
      printf("Vel: %f,%f\n", velocity.getX(), velocity.getY());
      printf("%f\n", velocity.getY());
      printf("%f\n", acceleration.getY());
      printf("%d\n", forces.size());
    }
    break;
  case 'd':
    if (isJumping)
    {
      forces.erase(forces.begin());
      isJumping = false;
      printf("%f\n", velocity.getY());
      printf("d\n");
    }

  default:
    break;
  }
}

void Player::stop()
{
  if (isMoving)
  {
    int nForces = isJumping ? 2 : 1;
    while (forces.size() > nForces)
    {
      forces.pop_back();
    }
    velocity.setX(0);
    isMoving = false;
  }
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

Player *Team::getPlayerByIdx(int i)
{
  return players[i];
}

void Team::drop()
{
  for (int i = 0; i < players.size(); i++)
  {
    players[i]->move('d');
  }
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

void Team::update(float dt)
{
  for (int i = 0; i < players.size(); i++)
  {
    collidePlayerAndWall(players[i]);
    players[i]->update(dt);
  }
}