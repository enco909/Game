#include "Game.hpp"
#include <iostream>

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
}

void Game::handleEvents()
{
  SDL_Event event;
  SDL_PollEvent(&event);

  // Check for running events
  switch (event.type) {
  case SDL_QUIT: // Stops game
    isRunning = false;
    break;

  default:
    break;
  }
}

void Game::update()
{
}

void Game::render()
{
  SDL_RenderClear(renderer); // Clear rendering target

  /* Rendering stuff here */

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
