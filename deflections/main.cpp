//
//  main.cpp
//  deflections
//
//  Created by Michael Lipka on 6/1/17.
//  Copyright © 2017 Michael Lipka. All rights reserved.
//

#include "header/laser.h"

#ifdef _WIN64
#include <SDL.h>
#undef main
#else
#include <SDL2/SDL.h>
#endif
#include "header/grid.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Globals, sorry
SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Renderer *renderer = NULL;
bool running = false;

std::vector<Laser *> *lasers = new std::vector<Laser *>();

Grid *grid;

void render();
void events();
void loadFile();
void logic();

int main(int argc, const char *argv[]) {

  loadFile();

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL Could Not Be Initialized");
    return 1;
  } else {
    // Create window
    window = SDL_CreateWindow("Deflections", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      printf("Window could not be created");
      return 2;
    } else {
      // Create Renderer
      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

      if (renderer == NULL) {
        printf("Renderer could not be created");
        return 3;
      } else {
        // Create surface
        screenSurface = SDL_GetWindowSurface(window);
        SDL_FreeSurface(screenSurface);
      }
    }
  }

  running = true;

  // Create starting lasers
  lasers->push_back(new Laser(renderer, grid->GetTarget()->Right(),
                              grid->GetTarget()->CenterY(), Direction::E));
  while (running) {
    events();
    logic();
    render();
  }

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return 0;
}

void render() {
  SDL_UpdateWindowSurface(window);
  SDL_RenderClear(renderer);

  grid->render(renderer);

  for (std::vector<Laser *>::iterator it = lasers->begin(); it != lasers->end();
       ++it) {
    (*it)->render();
  }

  SDL_RenderPresent(renderer);
  SDL_Delay(200);
}

void events() {
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      running = false;
    }
  }
}

void logic() {
  for (std::vector<Laser *>::iterator it = lasers->begin(); it != lasers->end();
       ++it) {
    (*it)->step();
    (*it)->CheckCollisions(grid->DeflectorTiles);
  }
}

std::vector<std::string> split(std::string str, char delim) {
  std::string out;
  std::stringstream strStream;
  strStream << str;
  std::vector<std::string> outVec;
  while (std::getline(strStream, out, delim)) {
    outVec.push_back(out);
  }

  return outVec;
}

void replace(std::string &str, const std::string &from, const std::string &to) {
  size_t pos = 0;
  while ((pos = str.find(from, pos)) != std::string::npos) {
    str.replace(pos, from.length(), to);
    pos += to.length();
  }
}

void loadFile() {
  std::ifstream file("deflections/samples/01.txt");
  std::string line;
  int lineNum = 0;
  if (file.is_open()) {
    // Iterate through lines, skipping first 2
    while (std::getline(file, line)) {
      lineNum++;

      if (lineNum <= 2) {
        continue;
      }

      // Remove double spaces
      replace(line, "  ", " ");

      // Split line into tokens
      std::vector<std::string> tokens = split(line, ' ');

      int x = std::stoi(tokens[0]);
      int y = std::stoi(tokens[1]);

      if (lineNum == 3) {
        // Grid
        grid = new Grid(x, y);
        continue;

      } else if (lineNum == 4) {
        // Target Position
        grid->SetTarget(x - 1, y - 1);
        continue;
      }

      DeflectorDirection direction;
      if (tokens[2] == "/") {
        direction = DeflectorDirection::Forward;
      } else {
        direction = DeflectorDirection::Back;
      }

      grid->PlaceDeflector(x, y, direction);
    }
  } else {
    printf("Could not open file");
  }
}
