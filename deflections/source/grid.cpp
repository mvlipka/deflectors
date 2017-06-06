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
            this->Contents[x].push_back(Tile());
        }
    }
}

void Grid::SetTarget(int x, int y) {
    this->Contents[x][y].isTarget = true;
}

void Grid::PlaceDeflector(int x, int y, DeflectorDirection direction) {
    x--;
    y--;
    this->Contents[x][y].hasDeflector = true;
    this->Contents[x][y].direction = direction;
}

void Grid::createPoints() {
    std::vector<SDL_Point> points;
    
    
    this->points = points;
}

void Grid::render(SDL_Renderer *renderer) {
    for(int x = 0; x < this->rowLength; x++) {
        for(int y = 0; y < this->columnLength; y++) {
            this->Contents[x][y].render(renderer, x, y);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
    }
}

void Tile::render(SDL_Renderer *renderer, int x, int y) {
    SDL_Rect rect{x * GRID_SPACING, y * GRID_SPACING, GRID_SPACING, GRID_SPACING};
	if (this->isTarget) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rect);
	}
	else {
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderDrawRect(renderer, &rect);
	}

	if (this->hasDeflector) {
		if (this->direction == DeflectorDirection::Back) {
			SDL_RenderDrawLine(renderer, x*GRID_SPACING, y*GRID_SPACING, (x * GRID_SPACING) + GRID_SPACING, (y * GRID_SPACING) + GRID_SPACING);
		}
		else {
			SDL_RenderDrawLine(renderer, x*GRID_SPACING + GRID_SPACING, y * GRID_SPACING, x * GRID_SPACING, y * GRID_SPACING + GRID_SPACING);
		}
	}
}
