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

	//Mirror like material
	Material mat1 = Material(Vector3(255, 255, 255).get_normalized(), 0.99);
	
	//Almost non-reflective material
	Material mat2 = Material(Vector3(255, 0, 0).get_normalized(), 0.3);

	scene.objects.push_back(std::make_unique<Sphere>(Sphere(Vector3(3, 0, 20), mat1, 5)));
	scene.objects.push_back(std::make_unique<Box>(Box(Vector3(-9, 0, 20), mat2, Vector3(6, 6, 6))));

	bool running = true;
	while (running)
	{
		handle_SDL_events(running);
		manage_window();
	}
	return 0;
}

void manage_window() {
	render(renderer, scene, mouse_X, mouse_Y);
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