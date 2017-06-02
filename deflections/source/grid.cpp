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
        Tile tile = Tile();
        for (int y = 0; y < columns; y++) {
            tile = Tile();
        }
    }
}
