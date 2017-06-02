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
