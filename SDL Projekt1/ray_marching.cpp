#include<SDL.h>

#include"Vector3.h"
#include"hex_to_vector3.h"
#include"ray_marching_namespace.h"
#include"scene_objects.h"
#include"scene.h"
#include"hit_info.h"
#include<iostream>
#include<thread>
using namespace ray_marcher;


Vector3 pixel_to_world_coords(double x, double y);

const double spread = 0.001;
const int max_marching_iters = 100;
const int max_reflections = 10;
const double min_marching_dist = 0.001;
const double max_marching_dist = 100;

Vector3 sun_light_dir = Vector3(-1, -0.3, 5).get_normalized();
Vector3 sun_light_color(hex_to_vector3("FFF9C3").get_normalized());
double sun_light_str = 1; //between 0 and 1 

Vector3 base_light_color(hex_to_vector3("000000").get_normalized());
double base_light_str = 0.3; //between 0 and 1


//march the ray and return its color
Vector3 ray_march(Ray& ray, Scene& scene, int n_bounces) {
	int i = 0;
	while (i < max_marching_iters) {
		HitInfo hit = scene.signed_distance(ray.pos);

		if (hit.dist > max_marching_dist) {
			break;
		}

		if (hit.dist <= min_marching_dist) {
			//First calculate color disregarding if ray will reflect
			double sun_illumination =
				std::fmax(-(sun_light_dir.dot(hit.normal)), 0);

			Vector3 sun_plus_base_color =
				sun_light_color * sun_illumination * sun_light_str
				+ base_light_color * base_light_str * (1 - sun_illumination);
			Vector3 color = hit.mat.col * sun_plus_base_color;

			//Do reflection if ray can still reflect and calc new color
			if (n_bounces < max_reflections) {
				Ray new_ray = Ray(Vector3(ray.pos), Vector3(hit.normal * 2 + ray.dir).get_normalized());
				new_ray.march(min_marching_dist);
				color = color * (1 - hit.mat.reflection_index)
					+ ray_march(new_ray, scene, n_bounces + 1) * hit.mat.col * hit.mat.reflection_index;
			}

			return color ;
		}

		ray.march(hit.dist);

		i++;
	}
	return Vector3(1, 1, 1);
}

void draw_threaded(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_Rect rect{ 0, 0, 50, 50 };
	SDL_RenderDrawRect(renderer, &rect);
}

void render(SDL_Renderer* renderer, Scene& scene, int mouse_X, int mouse_Y) {
	sun_light_dir = pixel_to_world_coords(WINDOW_WIDTH - mouse_X, WINDOW_HEIGHT - mouse_Y).get_normalized();

	std::thread t = std::thread();

	for (double x = 0; x < WINDOW_WIDTH; x++) {
		for (double y = 0; y < WINDOW_HEIGHT; y++) {
			Ray ray(Vector3(0, 0, 0), pixel_to_world_coords(x, y).get_normalized());
			Vector3 col = ray_march(ray, scene, 0);

			SDL_SetRenderDrawColor(renderer, col.x * 255, col.y * 255, col.z * 255, 255);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
	SDL_RenderPresent(renderer);
}

Vector3 pixel_to_world_coords(double x, double y) {
	x = (2 * x - WINDOW_WIDTH) * spread;
	y = -(2 * y - WINDOW_HEIGHT) * spread;
	return(Vector3(x, y, 1));
}