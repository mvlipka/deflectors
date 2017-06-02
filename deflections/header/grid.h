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

// Spaces between tile centers
const int GRID_SPACING = 50;

enum DeflectorDirection {
    Back,
    Forward
};

class Tile {
public:
    bool hasDeflector;
    DeflectorDirection direction;
    bool isTarget;
    
};

class Grid {
public:
    std::vector<std::vector<Tile>> Contents;
    Grid(int rows, int columns);
    void SetTarget(int x, int y);
    void PlaceDeflector(int x, int y, DeflectorDirection direction);
    
    int rowLength, columnLength;
};

#endif /* grid_h */
