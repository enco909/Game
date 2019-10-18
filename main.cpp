#include "Game.hpp"

Game *game = nullptr;

int main(int argc, const char *argv[])
{
  // Set framerate
  const int FPS = 60;
  const int frameDelay = 1000. / FPS;

  // Storing running time
  Uint32 frameStart;
  int frameTime;

  // Initialize game instance
  game = new Game();

  // Init SDL
  game->init("GameEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
             800, 600, false);

  // Game loop
  while (game->running()) {
    frameStart = SDL_GetTicks();

    game->handleEvents();
    game->update();
    game->render();

    frameTime = SDL_GetTicks() - frameStart; // Time a fram needed

    if(frameDelay > frameTime)
      SDL_Delay(frameDelay - frameTime);
  }

  game->clean();

  return 0;
}
