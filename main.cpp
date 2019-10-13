#include "Game.hpp"

Game *game = nullptr;

int main(int argc, const char *argv[])
{
  // Initialize game instance
  game = new Game();

  // Init SDL
  game->init("GameEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

  // Game loop
  while (game->running()) {
    game->handleEvents();
    game->update();
    game->render();
  }

  game->clean();

  return 0;
}