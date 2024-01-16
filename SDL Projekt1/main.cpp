#include<iostream>
#define SDL_MAIN_HANDLED
#include<SDL.h>
#include<vector>

#include"./Vector3.h"
#include"hex_to_vector3.h"
#include"ray_marching.h"

void handle_SDL_events(bool&);
void ray_march(SDL_Window*, SDL_Renderer*);
double SDF(Vector3);

const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;
const double spread = 0.0032;
const int marching_iterations = 20;

Sphere sph1{ Vector3(0, 0, 10), 2 };

Vector3 sun_light_dir = Vector3(0.6, -1, -1).get_normalized();
Vector3 sun_light_color(hex_to_vector3("F7D08A"));
float sun_light_str = 1; //between 0 and 1 

Vector3 base_light_color(hex_to_vector3("340068"));
float base_light_str = 0.3; //between 0 and 1

int main() {
	SDL_Window* window = SDL_CreateWindow("marcher.kms", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);

	bool running = 1;
	while (running)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		for (double x = 0; x < WINDOW_WIDTH; x++) {
			for (double y = 0; y < WINDOW_HEIGHT; y++) {
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}
		ray_march(window, renderer);
		SDL_RenderPresent(renderer);
		handle_SDL_events(running);

		int x, y;
		SDL_GetMouseState(&x, &y);
		sph1.pos = Vector3((2 * x - WINDOW_WIDTH) * spread * 10, (2 * y - WINDOW_HEIGHT) * spread * 10, 10);
	}
}

void ray_march(SDL_Window* window, SDL_Renderer* renderer) {
	//std::vector<Ray> rays = std::vector<Ray>();

	for (double x = 0; x < WINDOW_WIDTH; x++) {
		for (double y = 0; y < WINDOW_HEIGHT; y++) {
			double _x = (2 * x - WINDOW_WIDTH) * spread;
			double _y = (2 * y - WINDOW_WIDTH) * spread;

			Ray ray(Vector3(0, 0, 0), Vector3(_x, _y, 1).get_normalized());

			//marching
			for (int i = 0; i < marching_iterations; i++) {
				double d = SDF(ray.pos);
				if (d <= 0.001) {
					double sun_illumination =
						std::fmax(-(sun_light_dir.dot((sph1.pos - ray.pos).get_normalized())), 0);

					Vector3 color(
						(sun_illumination * sun_light_color.x * sun_light_str + base_light_str * base_light_color.x),
						(sun_illumination * sun_light_color.y * sun_light_str + base_light_str * base_light_color.y),
						(sun_illumination * sun_light_color.z * sun_light_str + base_light_str * base_light_color.z)
					);
					SDL_SetRenderDrawColor(renderer, color.x, color.y, color.z, SDL_ALPHA_OPAQUE);
					SDL_RenderDrawPoint(renderer, x, y);
					break;
				}
				ray.march(d);
			}
		}
	}
}

double SDF(Vector3 pos) {
	return pos.get_dist(sph1.pos) - sph1.r;
}

void handle_SDL_events(bool& running) {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) running = false;
	}
}


//Code graveyard
