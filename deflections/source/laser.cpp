#include "laser.h"
#include "grid.h"
#include <iostream>

Laser::Laser(SDL_Renderer *renderer, int x, int y, Direction direction) {
  this->renderer = renderer;
  this->x = x;
  this->y = y;
  this->startX = x;
  this->startY = y;
  this->direction = direction;
  this->speed = 1;
  this->stepping = true;
}
void Laser::render() {
  SDL_SetRenderDrawColor(this->renderer, 0, 255, 0, 255);
  SDL_RenderDrawLine(this->renderer, startX * GRID_SPACING,
                     startY * GRID_SPACING, x * GRID_SPACING, y * GRID_SPACING);
  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
}

void Laser::step(Grid *grid) {
  if (!stepping) {
    return;
  }

  if (this->direction == Direction::E || this->direction == Direction::W) {
    if (this->direction == Direction::E) {
      this->x += 1 * speed;
    } else {
      this->x -= 1 * speed;
    }
  } else if (this->direction == Direction::N ||
             this->direction == Direction::S) {
    if (this->direction == Direction::N) {
      this->y -= 1 * speed;
    } else {
      this->y += 1 * speed;
    }
  }

  if (this->x >= grid->rowLength + 1 || this->x <= 0) {
    this->stepping = false;
  }
  if (this->y >= grid->columnLength + 1 || this->y <= 0) {
    this->stepping = false;
  }
}

void createChildLaser(Laser *parent, Tile *tile) {
  Laser *childLaser;
  switch (tile->direction) {
  case Forward:
    switch (parent->direction) {
    case Direction::E:
      childLaser = new Laser(parent->getRenderer(), tile->Left(), tile->Top(),
                             Direction::N);
      lasers.push_back(childLaser);
      break;
    case Direction::W:
      childLaser = new Laser(parent->getRenderer(), tile->Right(),
                             tile->Bottom(), Direction::S);
      lasers.push_back(childLaser);
      break;

    case Direction::N:
      childLaser = new Laser(parent->getRenderer(), tile->Right(),
                             tile->Bottom(), Direction::E);
      lasers.push_back(childLaser);
      break;
    case Direction::S:
      childLaser = new Laser(parent->getRenderer(), tile->Left(),
                             tile->Bottom(), Direction::W);
      lasers.push_back(childLaser);
      break;
    }
    break;
  case Back:
    switch (parent->direction) {
    case Direction::E:
      childLaser = new Laser(parent->getRenderer(), tile->CenterX(),
                             tile->Bottom(), Direction::S);
      lasers.push_back(childLaser);
      break;
    case Direction::W:
      childLaser = new Laser(parent->getRenderer(), tile->Right(), tile->Top(),
                             Direction::N);
      lasers.push_back(childLaser);
      break;

    case Direction::N:
      childLaser = new Laser(parent->getRenderer(), tile->CenterX(),
                             tile->Bottom(), Direction::W);
      lasers.push_back(childLaser);
      break;
    case Direction::S:
      childLaser = new Laser(parent->getRenderer(), tile->CenterX(),
                             tile->Top(), Direction::E);
      lasers.push_back(childLaser);
      break;
    }
    break;
  }
}

bool Laser::CheckCollisions(std::vector<Tile *> tiles) {
  if (!this->stepping) {
    return false;
  }

  for (std::vector<Tile *>::iterator it = tiles.begin(); it != tiles.end();
       ++it) {
    Tile tile = *(*it);
    if (this->x <= tile.Right() && this->x >= tile.Left()) {
      if (this->y <= tile.Bottom() && this->y >= tile.Top()) {
        this->stepping = false;
        createChildLaser(this, &tile);
        return true;
      }
    }
  }
  return false;
}

SDL_Renderer *Laser::getRenderer() { return this->renderer; }

Laser::~Laser() { delete this; }
