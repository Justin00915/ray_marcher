#include<SDL.h>

#include"rendering.h"
#include"globals.h"
#include"scene.h"

void handle_SDL_events(bool&);
void manage_window();

SDL_Event e;
SDL_Renderer* renderer;
SDL_Window* window;

Scene scene;

int mouse_X;
int mouse_Y;

Vector3 sun_light_dir = Vector3(-1, -0.3, 5);
Material mat1 = Material(Vector3(255, 255, 255), 0.5);
Material mat2 = Material(Vector3(255, 0, 0), 0);

int main(int argc, char* argv[]) {
	//initing system
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "raymarcher.kms");


	//scene.objects.push_back(std::make_unique<Sphere>(Sphere(Vector3(3, 0, 20), mat1, 5)));
	scene.objects.push_back(std::make_unique<Sphere>(Sphere(Vector3(10, 0, 20), &mat1, 10)));
	scene.objects.push_back(std::make_unique<Sphere>(Sphere(Vector3(-6, 0, 20), &mat1, 6)));
	scene.objects.push_back(std::make_unique<Box>(Box(Vector3(0, -5, 25), &mat2, Vector3(10, 1, 30))));

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
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{

			case SDLK_UP:
				mat1.col = mat1.col + Vector3(50, 0, 50)/255;
				std::cout << mat1.col.x << std::endl;
				break;
			case SDLK_DOWN:
				mat1.col = mat1.col - Vector3(50, 0, 50)/255;
				std::cout << mat1.col.x << std::endl;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}