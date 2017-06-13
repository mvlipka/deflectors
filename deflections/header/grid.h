//
//  grid.h
//  deflections
//
//  Created by Michael Lipka on 6/2/17.
//  Copyright © 2017 Michael Lipka. All rights reserved.
//

#ifndef grid_h
#define grid_h

#include <vector>

#ifdef _WIN64
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif

// Spaces between tile centers
const int GRID_SPACING = 25;

enum DeflectorDirection { Back, Forward };

class Tile {
public:
  Tile(int x, int y);
  bool hasDeflector;
  DeflectorDirection direction;
  bool isTarget;

  void render(SDL_Renderer *renderer, int x, int y);
  float CenterX();
  float CenterY();
  int Left();
  int Right();
  int Top();
  int Bottom();

private:
  int x, y;
};

class Grid {
public:
  std::vector<std::vector<Tile>> Contents;
  std::vector<Tile *> DeflectorTiles;
  Grid(int rows, int columns);
  void SetTarget(int x, int y);
  void PlaceDeflector(int x, int y, DeflectorDirection direction);
  Tile *GetTarget();

  void render(SDL_Renderer *renderer);

  int rowLength, columnLength;

private:
  std::vector<SDL_Point> points;
  void createPoints();
  int targetX, targetY;
  Tile *target;
};

#endif /* grid_h */
