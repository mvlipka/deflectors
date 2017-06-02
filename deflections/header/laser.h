//
//  laser.h
//  deflections
//
//  Created by Michael Lipka on 6/2/17.
//  Copyright © 2017 Michael Lipka. All rights reserved.
//

#ifndef laser_h
#define laser_h

#include <SDL2/SDL.h>

enum Direction {
    N = 1,
    E = 1,
    S = -1,
    W = -1
};

class Laser {
public:
    Laser(SDL_Renderer* renderer, int x, int y, Direction direction);
    ~Laser();
    void render();
    void step();
    Direction direction;
    
    int startX, startY;
    int x, y;
    
    bool stepping;
    
    int speed;
    
private:
    SDL_Renderer *renderer;
};

#endif /* laser_h */
