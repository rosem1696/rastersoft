//Standard Library
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

//External Libraries
#include <SDL.h>
#include <rastersoft.h>
#include <rast_matrix.h>

//Local Headers
#include "demo.h"
#include "system_vars.h"

//Local Function Definitions

bool init_sdl_vars();
void cleanup_sdl();

//Global Functions



//Local Functions

int main(int argc, char *argv[]) {
	init_sdl_vars();
	SDL_Event ev;
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
	return 0;
}

bool init_sdl_vars() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
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