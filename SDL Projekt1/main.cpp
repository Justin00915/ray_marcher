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

Scene scene = Scene();

int mouse_X;
int mouse_Y;

int main(int argc, char* argv[]) {
	//initing system
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "raymarcher.kms");

	scene.objects.push_back(std::make_unique<SceneObject>(Sphere(Vector3(0, 0, 20), Vector3(255, 255, 255), 5)));
	scene.objects.push_back(std::make_unique<SceneObject>(Box(Vector3(0, 0, 20), Vector3(255, 255, 255), Vector3(1, 3, 2))));
	//scene.object = Sphere(Vector3(0, 0, 20), Vector3(255, 255, 255), 5);


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