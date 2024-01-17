#include<SDL.h>

#include"Vector3.h"
#include"hex_to_vector3.h"
#include"ray_marching_namespace.h"
using namespace ray_marcher;

Sphere sph1{ Vector3(0, 0, 20), 3 };

const double spread = 0.001;
const int marching_iters = 50;

Vector3 sun_light_dir = Vector3(0.6, -1, -1).get_normalized();
Vector3 sun_light_color(hex_to_vector3("F7D08A"));
float sun_light_str = 1; //between 0 and 1 

Vector3 base_light_color(hex_to_vector3("340068"));
float base_light_str = 0.3; //between 0 and 1

double SDF(Vector3 pos) {
	return pos.get_dist(sph1.pos) - sph1.r;
}



//march the ray and return its color
Vector3 march_ray(Ray ray) {
	for (int i = 0; i < marching_iters; i++) {
		double d = SDF(ray.pos);

		if (d > 1000) {
			break;
		}

		if (d <= 0.0001) {
			double sun_illumination =
				std::fmax(-(sun_light_dir.dot((sph1.pos - ray.pos).get_normalized())), 0);

			Vector3 color = sun_light_color * sun_illumination * sun_light_str + base_light_color * base_light_str;
			return color;
		}
		ray.march(d);
	}
	return Vector3(0, 0, 0);
}

void render(SDL_Window* window, SDL_Renderer* renderer, int mouse_X, int mouse_Y) {
	sph1.pos = Vector3((2 * mouse_X - WINDOW_WIDTH) * spread * sph1.pos.z, (2 * mouse_Y - WINDOW_HEIGHT) * spread * sph1.pos.z, sph1.pos.z);
	//for every pixel

	for (double x = 0; x < WINDOW_WIDTH; x++) {
		for (double y = 0; y < WINDOW_HEIGHT; y++) {
			double _x = (2 * x - WINDOW_WIDTH) * spread;
			double _y = (2 * y - WINDOW_HEIGHT) * spread;
			Ray ray(Vector3(0, 0, 0), Vector3(_x, _y, 1).get_normalized());
			Vector3 color = march_ray(ray);

			SDL_SetRenderDrawColor(renderer, color.x, color.y, color.z, 255);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}

	SDL_RenderPresent(renderer);
}


//Code graveyard

//void ray_march(SDL_Window* window, SDL_Renderer* renderer) {
//	for (double x = 0; x < WINDOW_WIDTH; x++) {
//		for (double y = 0; y < WINDOW_HEIGHT; y++) {
//			double _x = (2 * x - WINDOW_WIDTH) * spread;
//			double _y = (2 * y - WINDOW_HEIGHT) * spread;
//
//			Ray ray(Vector3(0, 0, 0), Vector3(_x, _y, 1).get_normalized());
//
//			//marching
//			for (int i = 0; i < marching_iters; i++) {
//				double d = SDF(ray.pos);
//				if (d <= 0.1) {
//					double sun_illumination =
//						std::fmax(-(sun_light_dir.dot((sph1.pos - ray.pos).get_normalized())), 0);
//
//					Vector3 color = sun_light_color * sun_illumination * sun_light_str + base_light_color * base_light_str;
//					SDL_SetRenderDrawColor(renderer, color.x, color.y, color.z, SDL_ALPHA_OPAQUE);
//					SDL_RenderDrawPoint(renderer, x, y);
//					break;
//				}
//				ray.march(1.001 * d);
//			}
//		}
//	}
//}