#ifndef Map_hpp
#define Map_hpp

#include "Game.hpp"

class Map {
public:
  /*
   * Constructor
   */
  Map();

  /*
   * Destructor
   */
  ~Map();

  /*
   * Loading textures of map
   */
  void LoadMap(int arr[15][20]);

  /*
   * Drawing map to the screen
   */
  void DrawMap();

private:
  SDL_Rect src, dest;

  SDL_Texture *dirt;
  SDL_Texture *grass;
  SDL_Texture *water;

  int map[15][20]; // Map consisting of 20x15 tiles
};

#endif // Map_hpp
