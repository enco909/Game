#include "Game.hpp"
#include "TextureManager.hpp"

// For storing player texture
SDL_Texture *playerTex;
SDL_Rect srcR, destR;

Game::~Game()
{
}

Game::Game()
{
}

void Game::init(const char *title, int xpos, int ypos, int width, int height,
                bool fullscreen)
{
  // Flag for SDL fullscreen toggle
  int flags = 0;

  // Check for fullscreen variable and set SDL flag
  if (fullscreen)
    flags = SDL_WINDOW_FULLSCREEN;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    std::cout << "Subsystems initialized!...\n";

    // Init window
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

    // Check if window creation was successfull
    if (window)
      std::cout << "Window created!\n";
    else
      std::cerr << "ERROR: Failed to create a new window!\n";

    // Init renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    // Check if renderer creation was successfull
    if (renderer) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

      std::cout << "Renderer created!\n";
    } else
      std::cerr << "ERROR: Failed to initialize renderer!\n";

    isRunning = true; // Game is now running
  } else
    isRunning = false; // Failed to start game

  playerTex = TextureManager::LoadTexture("assets/Henriette.png", renderer);
}

void Game::handleEvents()
{
  SDL_Event event;
  SDL_PollEvent(&event);

  // Check for running events
  switch (event.type) {
  case SDL_QUIT:
    isRunning = false;
    break;

  default:
    break;
  }
}

void Game::update()
{
  // Update counter
  cnt++;

  // Position of rectangle holding texture
  destR.h = 80;
  destR.w = 80;

  // Saving current size of window
  int currWidth, currHeight;

  SDL_GetWindowSize(window, &currWidth, &currHeight);

  // Let the texture run in a square over the screen
  if (destR.x < currWidth - 80 && destR.y == 0)
    destR.x += 2;
  else if (destR.y < currHeight - 80 && destR.x == currWidth - 80)
    destR.y += 2;
  else if (destR.x > 0 && destR.y == currHeight - 80)
    destR.x -= 2;
  else if (destR.x == 0 && destR.y >= 0)
    destR.y -= 2;
}

void Game::render()
{
  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, playerTex, NULL, &destR);

  SDL_RenderPresent(renderer); // Update screen
}

void Game::clean()
{
  // Terminate any parts of SDL
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  std::cout << "Game cleared!\n";
}

bool Game::running()
{
  return isRunning;
}
