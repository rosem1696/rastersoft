/**
 * @file demo.c
 * @author Mitchell Rose
 * @date 9 Feb 2018
 * @brief Base source file for the Rastersoft demo applications
 * @copyright Copyright (c) 2018 Mitchell Rose
 * @license MIT License
 */

/*** Standard Library ***/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

/*** External Libraries ***/
#include <SDL.h>
#include <rastersoft.h>
#include <rast_matrix.h>

/*** Local Headers ***/
#include "demo.h"
#include "cmd_handler.h"
#include "system_vars.h"

/*** Local Defines ***/
/*** Local Enums ***/
/*** Local Structs ***/

/*** Local Functions ***/
bool init_sdl_vars();
void cleanup_sdl();

/*** Local Variables ***/

/*** Function Implementations ***/

/**
 * @brief Entry point for SDL2
 * 
 * @param argc Not used
 * @param argv Not used
 * @return int Exit status code
 */
int main(int argc, char *argv[]) {
	//Initial SDL component setup
	init_sdl_vars();

	//Start command listening thread
	SDL_Thread * command_thread;
	command_thread = SDL_CreateThread(cmd_watch, CMD_THREAD_NAME, (void *)NULL);
	SDL_DetachThread(command_thread);
	SDL_Event ev;

	//Main Loop
	while (!quit) {
		//Poll and distribute events until all have been handled 
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
			case SDL_QUIT:
				quit = true;
			default:
				break;
			}
		}
		//SDL_Delay(10);

	}

	//free memory from comand array
	free_cmds();
	return 0;
}

/**
 * @brief Initializes necessary SDL2 constructs
 * 
 * @return true on init success
 * @return false on init error
 */
bool init_sdl_vars() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		fprintf(stderr, "SDL couldn't initialize! SDL_Error: %s\n", SDL_GetError());
		return true;
	}
	demo_window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!demo_window) {
		fprintf(stderr, "SDL couldn't create a window! SDL_Error: %s\n", SDL_GetError());
		return true;
	}
	demo_renderer = SDL_CreateRenderer(demo_window, -1, SDL_RENDERER_ACCELERATED);
	if (!demo_renderer) {
		fprintf(stderr, "SDL couldn't create a renderer! SDL_Error: %s\n", SDL_GetError());
		return true;
	}
	SDL_SetRenderDrawColor(demo_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(demo_renderer);
	SDL_RenderPresent(demo_renderer);
	return false;
}

/**
 * @brief Calls destroy and quit on SDL2 and constructs
 * 
 */
void cleanup_sdl() {
	SDL_DestroyRenderer(demo_renderer);
	SDL_DestroyWindow(demo_window);
	SDL_Quit();
}

/*SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
SDL_RenderClear(renderer);
SDL_RenderPresent(renderer);
SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);*/
/*SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
SDL_RenderClear(renderer);
SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
SDL_RenderPresent(renderer);*/
