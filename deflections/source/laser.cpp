#include "laser.h"
#include <iostream>

Laser::Laser(SDL_Renderer* renderer, int x, int y, Direction direction) {
    this->renderer = renderer;
    this->x = x;
    this->y = y;
    this->startX = x;
    this->startY = y;
    this->direction = direction;
    this->speed = 5;
    this->stepping = true;
}
void Laser::render() {
    SDL_RenderDrawLine(this->renderer, startX, startY, x, y);
    std::cout << startX << "," << startY << ":" << x << "," << y << "\n";
}

void Laser::step() {
    if(!stepping) {
        return;
    }
    
    if(this->direction == Direction::E || this->direction == Direction::W) {
        this->x += this->direction * speed;
    } else {
        this->y += this->direction * speed;
    }

}

Laser::~Laser() { delete this; }
