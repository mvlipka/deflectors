//
//  grid.h
//  deflections
//
//  Created by Michael Lipka on 6/2/17.
//  Copyright © 2017 Michael Lipka. All rights reserved.
//

#ifndef grid_h
#define grid_h

class Tile {
public:
    bool hasDeflector;
};

class Grid {
public:
    Tile** Contents;
    Grid(int rows, int columns);
};

#endif /* grid_h */
