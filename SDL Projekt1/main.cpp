#include<SDL.h>

#include"rendering.h"
#include"globals.h"
#include"scene.h"
#include"camera.h"

void handle_SDL_events(bool&);
void manage_window();

SDL_Event e;
SDL_Renderer* renderer;
SDL_Window* window;

Camera cam(Vector3(3, 0, 0), Vector3(0, 0, 0), spread);
Scene scene;

int mouse_X;
int mouse_Y;

double camspeed = 2;

Vector3 sun_light_dir(-1, -0.3, 5);
Material mat1(Vector3(255, 255, 255), 0.5);
Material mat2(Vector3(255, 0, 0), 0);

int main(int argc, char* argv[]) {
	//initing system
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "raymarcher.kms");


	//Adding everything to the scene
	scene.set_camera(cam);
	scene.objects.push_back(std::make_unique<Sphere>(Sphere(Vector3(10, 0, 20), &mat1, 10)));
	scene.objects.push_back(std::make_unique<Sphere>(Sphere(Vector3(-6, 0, 20), &mat2, 6)));
	//scene.objects.push_back(std::make_unique<Box>(Box(Vector3(0, -5, 25), &mat2, Vector3(10, 1, 30))));


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
			case SDLK_w:
				scene.cam.pos = scene.cam.pos + rotate_by_angle(Vector3(0, 0, camspeed), scene.cam.angles.y * RADIANS_TO_DEGREE);
				break;
			case SDLK_a:
				scene.cam.pos = scene.cam.pos + rotate_by_angle(Vector3(-camspeed, 0, 0), scene.cam.angles.y * RADIANS_TO_DEGREE);
				break;
			case SDLK_s:
				scene.cam.pos = scene.cam.pos + rotate_by_angle(Vector3(0, 0, -camspeed), scene.cam.angles.y * RADIANS_TO_DEGREE);
				break;
			case SDLK_d:
				scene.cam.pos = scene.cam.pos + rotate_by_angle(Vector3(camspeed, 0, 0), scene.cam.angles.y * RADIANS_TO_DEGREE);
				break;
			case SDLK_LSHIFT:
				scene.cam.pos = scene.cam.pos + Vector3(0, -camspeed, 0);
				break;
			case SDLK_SPACE:
				scene.cam.pos = scene.cam.pos + Vector3(0, camspeed, 0);
				break;

			case SDLK_LEFT:
				scene.cam.set_angles(scene.cam.angles + Vector3(0, 5, 0));
				break;
			case SDLK_RIGHT:
				scene.cam.set_angles(scene.cam.angles - Vector3(0, 5, 0));
				break;
			case SDLK_UP:
				scene.cam.set_angles(scene.cam.angles + Vector3(5, 0, 0));
				break;
			case SDLK_DOWN:
				scene.cam.set_angles(scene.cam.angles - Vector3(5, 0, 0));
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