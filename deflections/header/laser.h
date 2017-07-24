//
//  laser.h
//  deflections
//
//  Created by Michael Lipka on 6/2/17.
//  Copyright © 2017 Michael Lipka. All rights reserved.
//

#ifndef laser_h
#define laser_h

#ifdef _WIN64
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <vector>

class Tile;

class Grid;

enum Direction { N = 1, E = 2, S = 3, W = 4 };

class Laser {
public:
  Laser(SDL_Renderer *renderer, int x, int y, Direction direction);
  ~Laser();
  void render();
  void step(Grid *grid);
  bool CheckCollisions(std::vector<Tile *> tiles);
  SDL_Renderer *getRenderer();

  Direction direction;

  int startX, startY;
  int x, y;

  bool stepping;

  int speed;

private:
  SDL_Renderer *renderer;
};

extern std::vector<Laser *> lasers;

#endif /* laser_h */
