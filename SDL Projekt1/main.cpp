#include<SDL.h>

#include"ray_marching.h"
#include"ray_marching_namespace.h"
#include"scene.h"

using namespace ray_marcher;

void handle_SDL_events(bool&);
void manage_window();

SDL_Event e;
SDL_Renderer* renderer;
SDL_Window* window;

Scene scene;

int mouse_X;
int mouse_Y;

int main(int argc, char* argv[]) {
	//initing system
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "raymarcher.kms");

	Material mat1 = Material(Vector3(255, 255, 255), 0.5);
	scene.objects.push_back(std::make_unique<Sphere>(Sphere(Vector3(0, 5, 20), mat1, 5)));
	scene.objects.push_back(std::make_unique<Box>(Box(Vector3(-12, 5, 20), mat1, Vector3(1, 3, 2))));

	bool running = true;
	while (running)
	{
		handle_SDL_events(running);
		manage_window();
	}
	return 0;
}

void manage_window() {
	render(window, renderer, scene, mouse_X, mouse_Y);
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