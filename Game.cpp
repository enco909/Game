#include "Game.hpp"
#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject *player1;
GameObject *player2;

SDL_Renderer *Game::renderer = nullptr;

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
    Game::renderer = SDL_CreateRenderer(window, -1, 0);

    // Check if Game::renderer creation was successfull
    if (Game::renderer) {
      SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);

      std::cout << "Game::Renderer created!\n";
    } else
      std::cerr << "ERROR: Failed to initialize Game::renderer!\n";

    isRunning = true; // Game is now running
  } else
    isRunning = false; // Failed to start game

  player1 = new GameObject("assets/Henriette.png", 0, 0);
  player2 = new GameObject("assets/Henriette.png", 720, 520);
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
  player1->Update();
  player2->Update();
}

void Game::render()
{
  SDL_RenderClear(Game::renderer);
  player1->Render();
  player2->Render();
  SDL_RenderPresent(Game::renderer); // Update screen
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
