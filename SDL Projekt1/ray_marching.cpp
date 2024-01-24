#include<SDL.h>

#include"Vector3.h"
#include"hex_to_vector3.h"
#include"ray_marching_namespace.h"
#include"scene_objects.h"
#include"scene.h"
#include"hit_info.h"
#include<iostream>
using namespace ray_marcher;


Vector3 pixel_to_world_coords(double x, double y);

const double spread = 0.001;
const int marching_iters = 1000;
const double min_marching_dist = 0.1;

Vector3 sun_light_dir = Vector3(0.6, -1, -1).get_normalized();
Vector3 sun_light_color(hex_to_vector3("F7D08A"));
float sun_light_str = 1; //between 0 and 1 

Vector3 base_light_color(hex_to_vector3("340068"));
float base_light_str = 0.3; //between 0 and 1


//march the ray and return its color
Vector3 ray_march(Ray ray, Scene& scene) {
	int i = 0;


	while (i < marching_iters) {
		HitInfo hit = scene.signed_distance(ray.pos);

		if (hit.dist > 1000) {
			break;
		}

		if (hit.dist <= min_marching_dist) {
			double sun_illumination =
				std::fmax(-(sun_light_dir.dot(hit.normal)), 0);

			Vector3 color = sun_light_color * sun_illumination * sun_light_str + base_light_color * base_light_str;
			return color;
		}

		ray.march(hit.dist);

		i++;
	}
	return Vector3(255, 255, 255) / i;
}

void render(SDL_Window* window, SDL_Renderer* renderer, Scene& scene, int mouse_X, int mouse_Y) {
	//for every pixel
	for (double x = 0; x < WINDOW_WIDTH; x++) {
		for (double y = 0; y < WINDOW_HEIGHT; y++) {
			Ray ray(Vector3(0, 0, 0), pixel_to_world_coords(x, y).get_normalized());
			Vector3 col = ray_march(ray, scene);

			SDL_SetRenderDrawColor(renderer, col.x, col.y, col.z, 255);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
	SDL_RenderPresent(renderer);
}

Vector3 pixel_to_world_coords(double x, double y) {
	x = (2 * x - WINDOW_WIDTH) * spread;
	y = (2 * y - WINDOW_HEIGHT) * spread;
	return(Vector3(x, y, 1));
}