/**
 * @file system_vars.c
 * @author Mitchell Rose
 * @date 10 Feb 2018
 * @brief Global application variables
 * @copyright Copyright (c) 2018 Mitchell Rose
 * @license MIT License
 */

/*** Standard Library ***/
#include <stdbool.h>

/*** External Libraries ***/
#include <SDL.h>

/*** Local Headers ***/
/*** Local Defines ***/
/*** Local Enums ***/
/*** Local Structs ***/
/*** Local Functions ***/
/*** Local Variables ***/
struct SDL_Window* demo_window;
struct SDL_Renderer* demo_renderer;
bool quit = false;

/*** Function Implementations ***/
