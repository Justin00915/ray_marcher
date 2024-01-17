#define SDL_MAIN_HANDLED
#include<SDL.h>

#include"ray_marching.h"
#include"ray_marching_namespace.h"
using namespace ray_marcher;

void handle_SDL_events(bool&);
void manage_window();

SDL_Event e;
SDL_Renderer* renderer;
SDL_Window* window;

int mouse_X;
int mouse_Y;

int main() {
	//initing system
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "raymarcher.kms");

	bool running = true;
	while (running)
	{
		handle_SDL_events(running);
		manage_window();
	}
}

void manage_window() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	render(window, renderer, mouse_X, mouse_Y);

	SDL_RenderPresent(renderer);
}

void handle_SDL_events(bool& running) {
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			running = false;
			break;

		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&mouse_X, &mouse_Y);
			break;

		default:
			break;
		}
	}
}


//Code graveyard
