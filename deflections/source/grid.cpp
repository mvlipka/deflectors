//
//  grid.cpp
//  deflections
//
//  Created by Michael Lipka on 6/2/17.
//  Copyright © 2017 Michael Lipka. All rights reserved.
//

#include "grid.h"

Grid::Grid(int rows, int columns) {
    this->rowLength = rows;
    this->columnLength = columns;
    
    for(int x = 0; x < rows; x++) {
        std::vector<Tile> col;
        this->Contents.push_back(col);
        for (int y = 0; y < columns; y++) {
            Tile tile = Tile();
            this->Contents[x].push_back(tile);
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
    for(int x = 0; x < this->columnLength; x++) {
        for(int y =0; y < this->rowLength; y++) {
//            SDL_RenderDrawLine(renderer, x * GRID_SPACING, 0, x * GRID_SPACING, y * GRID_SPACING + 200);
//            SDL_RenderDrawLine(renderer, 0, y * GRID_SPACING, x * GRID_SPACING + 200, y * GRID_SPACING);
            this->Contents[x][y].render(renderer, x, y);
        }
    }
}

void Tile::render(SDL_Renderer *renderer, int x, int y) {
    SDL_Rect rect{x * GRID_SPACING, y * GRID_SPACING, GRID_SPACING, GRID_SPACING};
    SDL_RenderDrawRect(renderer, &rect);
}
