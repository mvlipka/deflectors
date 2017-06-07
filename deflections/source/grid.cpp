//
//  grid.cpp
//  deflections
//
//  Created by Michael Lipka on 6/2/17.
//  Copyright © 2017 Michael Lipka. All rights reserved.
//

#include "grid.h"
#include <iostream>

Grid::Grid(int rows, int columns) {
    this->rowLength = rows;
    this->columnLength = columns;
    
    for(int x = 0; x < rows; x++) {
        this->Contents.push_back(std::vector<Tile>());
        for (int y = 0; y < columns; y++) {
            this->Contents[x].push_back(Tile(x, y));
        }
    }
}

void Grid::SetTarget(int x, int y) {
    this->target = &this->Contents[x][y];
    this->Contents[x][y].isTarget = true;
    this->targetY = y;
    this->targetX = x;
}

Tile* Grid::GetTarget() {
    return this->target;
}

void Grid::PlaceDeflector(int x, int y, DeflectorDirection direction) {
    x--;
    y--;
    this->Contents[x][y].hasDeflector = true;
    this->Contents[x][y].direction = direction;
    this->DeflectorTiles.push_back(&this->Contents[x][y]);
}

void Grid::createPoints() {
    std::vector<SDL_Point> points;
    
    
    this->points = points;
}

void Grid::render(SDL_Renderer *renderer) {
    for(int x = 0; x < this->rowLength; x++) {
        for(int y = 0; y < this->columnLength; y++) {
            this->Contents[x][y].render(renderer, x, y);
        }
    }
}

Tile::Tile(int x, int y) {
    this->x = x;
    this->y = y;
    this->hasDeflector = false;
    this->isTarget = false;
}

void Tile::render(SDL_Renderer *renderer, int x, int y) {
    SDL_Rect rect{x * GRID_SPACING, y * GRID_SPACING, GRID_SPACING, GRID_SPACING};
	if (this->isTarget) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
	else {
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderDrawRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}

	if (this->hasDeflector) {
		if (this->direction == DeflectorDirection::Back) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			SDL_RenderDrawLine(renderer, x*GRID_SPACING, y*GRID_SPACING, (x * GRID_SPACING) + GRID_SPACING, (y * GRID_SPACING) + GRID_SPACING);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
		else {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			SDL_RenderDrawLine(renderer, x*GRID_SPACING + GRID_SPACING, y * GRID_SPACING, x * GRID_SPACING, y * GRID_SPACING + GRID_SPACING);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
	}
}

float Tile::CenterX() {
    return this->x + (1 / 2);
}

float Tile::CenterY() {
    return this->y + (1 / 2);
}

int Tile::Left() {
    return this->x;
}

int Tile::Right() {
    return this->x + 1;
}

int Tile::Top() {
    return this->y;
}

int Tile::Bottom() {
    return this->y + 1;
}
