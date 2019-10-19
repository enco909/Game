#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include <iostream>

class Game {
public:
  /*
   * Constructor
   */
  Game();

  /*
   * Decstructor
   */
  ~Game();

  /* Create the game window
   *
   * @param Title of the game
   * @param x-position of window on screen
   * @param y-position of window on screen
   * @param width of window
   * @param height of window
   * @param toggle fullscreen
   */
  void init(const char *title, int xpos, int ypos, int width, int height,
            bool fullscreen);

  /*
   * Handling game events
   */
  void handleEvents();

  /*
   * Updating game objects
   */
  void update();

  /*
   * Render graphics
   */
  void render();

  /*
   * Clear memory not used anymore
   */
  void clean();

  /*
   * Tells if the game is running or not
   */
  bool running();

  static SDL_Renderer *renderer;

private:
  // Graphic library specific variables
  SDL_Window *window;

  bool isRunning; // True if game is running, false when not
};

#endif // Game_hpp
