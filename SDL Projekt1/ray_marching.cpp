#include<SDL.h>

#include"Vector3.h"
#include"hex_to_vector3.h"
#include"ray_marching_namespace.h"
#include"scene_objects.h"
#include"hit_info.h"

using namespace ray_marcher;


Vector3 pixel_to_world_coords(double x, double y);

const double spread = 0.001;
const int marching_iters = 1000;

Vector3 sun_light_dir = Vector3(0.6, -1, -1).get_normalized();
Vector3 sun_light_color(hex_to_vector3("F7D08A"));
float sun_light_str = 1; //between 0 and 1 

Vector3 base_light_color(hex_to_vector3("340068"));
float base_light_str = 0.3; //between 0 and 1


Box box(Vector3(0, 0, 20), Vector3(255, 255, 255), Vector3(1, 3, 2));
Sphere sph(Vector3(0, 0, 20), Vector3(255, 255, 255), 5);

//march the ray and return its color
Vector3 ray_march(Ray ray) {
	int i = 0;
	for (; i < marching_iters; i++) {
		HitInfo h = box.signed_distance(ray.pos);

		if (h.dist > 1000) {
			break;
		}

		if (h.dist <= 0.00001) {
			double sun_illumination =
				std::fmax(-(sun_light_dir.dot(h.normal)), 0);

			Vector3 color = sun_light_color * sun_illumination * sun_light_str + base_light_color * base_light_str;
			return color;
		}
		ray.march(h.dist);
	}
	return Vector3(255, 255, 255) / i;
}

void render(SDL_Window* window, SDL_Renderer* renderer, int mouse_X, int mouse_Y) {
	box.pos = pixel_to_world_coords(mouse_X, mouse_Y) * box.pos.z;

	//for every pixel
	for (double x = 0; x < WINDOW_WIDTH; x++) {
		for (double y = 0; y < WINDOW_HEIGHT; y++) {
			Ray ray(Vector3(0, 0, 0), pixel_to_world_coords(x, y).get_normalized());
			Vector3 col = ray_march(ray);

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
//						std::fmax(-(sun_light_dir.dot((box1.pos - ray.pos).get_normalized())), 0);
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