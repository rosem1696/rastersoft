#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include <SDL.h>
#include <rast_matrix.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const float NEAR_PLANE = 1;
const float FAR_PLANE = 50;

const uint8_t* WINDOW_TITLE = "Tiny Renderer";


SDL_Window* draw_new_window(uint8_t* windowTitle, const int screenWidth, const int screenHeight) {
	SDL_Window* window = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL couldn't initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else {
		window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	}
	return window;
}

SDL_Renderer* draw_new_renderer(SDL_Window* window) {
	return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void draw_kill_window(SDL_Window* window) {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void getNextColor(uint8_t* r, uint8_t* g, uint8_t* b) {
	if (*r == 255) {
		if (*b > 0) {
			*b -= 1;
		}
		else if (*g > 0) {
			if (*g == 255) {
				*r -= 1;
			}
			else {
				*g += 1;
			}
		}
		else {
			*g += 1;
		}
	}
	else if (*g == 255) {
		if (*r > 0) {
			*r -= 1;
		}
		else if (*b > 0) {
			if (*b == 255) {
				*g -= 1;
			}
			else {
				*b += 1;
			}
		}
		else {
			*b += 1;
		}
	}
	else if (*b == 255) {
		if (*g > 0) {
			*g -= 1;
		}
		else {
			*r += 1;
		}
	}
	else {
		*r = 255;
	}
}

void drawLineNDC(SDL_Renderer* renderer, float x0, float y0, float x1, float y1) {
	int hwidth = SCREEN_WIDTH >> 1;
	int hheight = SCREEN_HEIGHT >> 1;
	//printf("%f x , %f y - %f x , %f y\n", x0, y0, x1, y1);
	int px0 = hwidth + hheight * x0;
	int px1 = hwidth + hheight * x1;
	int py0 = hheight + -(hheight * y0);
	int py1 = hheight + -(hheight * y1);
	//printf("%d x , %d y - %d x , %d y\n", px0, py0, px1, py1);
	SDL_RenderDrawLine(renderer, px0, py0, px1, py1);
}

struct object* setupCube() {
	struct object* cube = malloc(sizeof(struct object));
	cube->points = malloc(8 * sizeof(struct point));
	cube->faces = malloc(12 * sizeof(struct face));

	int i, j, k;
	int x, y, z;
	int count = 0;
	for (i = 0; i < 2; i++) {
		x = i == 0 ? 1 : -1;
		for (j = 0; j < 2; j++) {
			y = j == 0 ? 1 : -1;
			for (k = 0; k < 2; k++) {
				z = k == 0 ? 1 : -1;
				cube->points[count].matrix[0] = x;
				cube->points[count].matrix[1] = y;
				cube->points[count].matrix[2] = z;
				cube->points[count].matrix[3] = 1;
				count++;
			}
		}
	}

	cube->faces[0].p1 = 0;
	cube->faces[0].p2 = 1;
	cube->faces[0].p3 = 3;

	cube->faces[1].p1 = 0;
	cube->faces[1].p2 = 2;
	cube->faces[1].p3 = 3;

	cube->faces[2].p1 = 4;
	cube->faces[2].p2 = 5;
	cube->faces[2].p3 = 7;

	cube->faces[3].p1 = 4;
	cube->faces[3].p2 = 6;
	cube->faces[3].p3 = 7;

	cube->faces[4].p1 = 0;
	cube->faces[4].p2 = 1;
	cube->faces[4].p3 = 5;

	cube->faces[5].p1 = 0;
	cube->faces[5].p2 = 4;
	cube->faces[5].p3 = 5;

	cube->faces[6].p1 = 2;
	cube->faces[6].p2 = 3;
	cube->faces[6].p3 = 7;

	cube->faces[7].p1 = 2;
	cube->faces[7].p2 = 6;
	cube->faces[7].p3 = 7;

	cube->faces[8].p1 = 0;
	cube->faces[8].p2 = 2;
	cube->faces[8].p3 = 6;

	cube->faces[9].p1 = 0;
	cube->faces[9].p2 = 4;
	cube->faces[9].p3 = 6;

	cube->faces[10].p1 = 1;
	cube->faces[10].p2 = 3;
	cube->faces[10].p3 = 7;

	cube->faces[11].p1 = 1;
	cube->faces[11].p2 = 5;
	cube->faces[11].p3 = 7;

	return cube;
}

void freeCube(struct object* cube) {
	free(cube->points);
	free(cube->faces);
	free(cube);
}

bool clipDrawPolygon(SDL_Renderer* renderer, struct point* p1, struct point* p2, struct point* p3) {

}

bool clipDrawLine(SDL_Renderer* renderer, struct point* p1, struct point* p2) {
	float x1, y1, x2, y2;
	if (p1->matrix[3] >= NEAR_PLANE || p2->matrix[3] >= NEAR_PLANE) {
		if (p1->matrix[3] < NEAR_PLANE) {
			x2 = p2->matrix[0] / p2->matrix[3];
			y2 = p2->matrix[1] / p2->matrix[3];
			float n = (p2->matrix[3] - NEAR_PLANE) / (p2->matrix[3] - p1->matrix[3]);
			x1 = (n * p2->matrix[0]) + ((1 - n) * p1->matrix[0]);
			y1 = (n * p2->matrix[1]) + ((1 - n) * p1->matrix[1]);
			drawLineNDC(renderer, x1, y1, x2, y2);
		}
		else if (p1->matrix[3] < NEAR_PLANE) {
			x1 = p1->matrix[0] / p1->matrix[3];
			y1 = p1->matrix[1] / p1->matrix[3];
			float n = (p1->matrix[3] - NEAR_PLANE) / (p1->matrix[3] - p2->matrix[3]);
			x2 = (n * p1->matrix[0]) + ((1 - n) * p2->matrix[0]);
			y2 = (n * p1->matrix[1]) + ((1 - n) * p2->matrix[1]);
			drawLineNDC(renderer, x1, y1, x2, y2);
		}
		else {
			x1 = p1->matrix[0] / p1->matrix[3];
			y1 = p1->matrix[1] / p1->matrix[3];
			x2 = p2->matrix[0] / p2->matrix[3];
			y2 = p2->matrix[1] / p2->matrix[3];
			drawLineNDC(renderer, x1, y1, x2, y2);
		}
	}
	else {

	}

}

int main(int argc, char *argv[]) {
	struct SDL_Window* window = draw_new_window(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
	struct SDL_Renderer* renderer = draw_new_renderer(window);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	struct transform* projection = malloc(sizeof(struct transform));
	struct transform* model = malloc(sizeof(struct transform));
	struct transform* view = malloc(sizeof(struct transform));
	struct object* cube = setupCube();

	float z = 3;
	float x = .5;
	float y = .5;
	float c = .01;
	while (true) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

		getProjectionMat(projection, NEAR_PLANE, FAR_PLANE);
		getTranslateMat(model, x, y, z);
		getTranslateMat(view, 0, 0, 0);

		struct transform* stack = malloc(sizeof(struct transform));

		multTransforms(stack, projection, model);
		multTransforms(stack, stack, view);

		struct point* transPoints = malloc(12 * sizeof(struct point));

		/*printPoints(cube->points, 8);
		Sleep(1000000);*/

		int i;
		for (i = 0; i < 8; i++) {
			transformPoint(transPoints + i, stack, cube->points + i);
		}

		for (i = 0; i < 12; i++) {
			struct point* p1 = transPoints + cube->faces[i].p1;
			struct point* p2 = transPoints + cube->faces[i].p2;
			struct point* p3 = transPoints + cube->faces[i].p3;
			clipDrawLine(renderer, p1, p2);
			clipDrawLine(renderer, p1, p3);
			clipDrawLine(renderer, p2, p3);
		}

		SDL_RenderPresent(renderer);
		z += c;
		//x += c;
		//y += c;
		if (z < -5 || z > 5) {
			c = -c;
		}
		Sleep(10);
	}

	Sleep(100000);

	freeCube(cube);
	draw_kill_window(window);
}