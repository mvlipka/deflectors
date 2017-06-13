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

void Laser::step() {
  if (!stepping) {
    return;
  }

  if (this->direction == Direction::E || this->direction == Direction::W) {
    this->x += this->direction * speed;
  } else {
    this->y += this->direction * speed;
  }
}

void createChildLaser(Laser *parent, Tile *tile) {
  switch (tile->direction) {
  case Forward:
    break;
  case Back:
    if (parent->direction == Direction::E) {
      Laser *childLaser = new Laser(parent->getRenderer(), tile->CenterX(),
                                    tile->Bottom(), Direction::S);
      lasers->push_back(childLaser);
    }
    break;
  }
}

bool Laser::CheckCollisions(std::vector<Tile *> tiles) {
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
