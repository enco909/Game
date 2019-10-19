#include "Map.hpp"
#include "TextureManager.hpp"

int lvl1[15][20] = {
    {1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 2, 1, 1, 1, 2, 2, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 2, 2, 1, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

Map::Map()
{
  water = TextureManager::LoadTexture("assets/water.png"); // Index 0
  grass = TextureManager::LoadTexture("assets/grass.png"); // Index 1
  dirt = TextureManager::LoadTexture("assets/dirt.png"); // Index 2

  LoadMap(lvl1);

  src.x = dest.x = 0;
  src.y = dest.y = 0;
  src.w = dest.w = 40;
  src.h = dest.h = 40;
}

Map::~Map()
{
}

void Map::LoadMap(int arr[15][20])
{
  for(int row = 14; row >= 0; row--)
    for (int column = 19; column >= 0; column--)
      map[row][column] = arr[row][column];
}

void Map::DrawMap()
{
  unsigned int type = 0;

  for(int row = 14; row >= 0; row--) {
    for (int column = 19; column >= 0; column--) {
      type = map[row][column];

      dest.x = 40 * column;
      dest.y = 40 * row;

      switch (type) {
      case 0:
        TextureManager::Draw(water, src, dest);
        break;
      case 1:
        TextureManager::Draw(grass, src, dest);
        break;
      case 2:
        TextureManager::Draw(dirt, src, dest);
        break;
      default:
        break;
      }
    }
  }
}
