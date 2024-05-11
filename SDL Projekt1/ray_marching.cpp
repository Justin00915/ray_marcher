#include<SDL.h>

#include"vector3.h"
#include"hex_to_vector3.h"
#include"globals.h"
#include"scene_objects.h"
#include"scene.h"
#include"hit_info.h"
#include<iostream>
#include<thread>

Vector3 ray_march(Ray& ray, Scene& scene, int n_bounces);

Vector3 sun_light_color(hex_to_vector3("FFF9C3").get_normalized());
double sun_light_str = 1; //between 0 and 1 
Vector3 base_light_color(hex_to_vector3("92BCEA").get_normalized());
double base_light_str = 0.3; //between 0 and 1

void draw_threaded(Scene& scene, int index, int n_threads, std::vector<Pixel>& rendered_pixel) {
	for (int x = 0; x < WINDOW_WIDTH; x++) {
		for (int y = 0; y < WINDOW_HEIGHT; y++) {
			if ((x + y * WINDOW_HEIGHT) % n_threads == index) {
				Vector3 pixel_to_world = pixel_to_world_coords(x, y);
				double angle = scene.cam.angles.y * RADIANS_TO_DEGREE;
				Vector3 base_ray_dir = Vector3(
					pixel_to_world.x * spread, pixel_to_world.y * spread + scene.cam.angles.x * 0.1, 1
				);

				Vector3 ray_dir = rotate_by_angle(base_ray_dir, angle);
				Ray ray(scene.cam.pos, ray_dir.get_normalized());
				Pixel pix{ x, y, ray_march(ray, scene, 0) * 255 };
				rendered_pixel[x + y * WINDOW_WIDTH] = pix;
			}
		}
	}
}

//march the ray and return its color
//if n_bounces == -1 then this function
//is looking if theres any collision with the scene at all(this also saves computing power)
Vector3 ray_march(Ray& ray, Scene& scene, int n_bounces) {
	int i = 0;
	while (i < max_marching_iters) {
		HitInfo hit = scene.signed_distance(ray.pos);

		if (hit.dist > max_cam_dist) {
			return base_light_color;
		}

		if (hit.dist < min_marching_dist) {
			//-1 is to check if ray reaches sun
			//if this condition activates, ray didnt reach it
			if (n_bounces == -1) {
				return HIT_AN_OBJECT_COLOR;
			}
			//First calculate color disregarding if ray will reflect
			double sun_illumination = 0;

			Ray sun_ray(ray.pos, sun_light_dir * -1);
			sun_ray.march(min_marching_dist * 20);
			if (!(ray_march(sun_ray, scene, -1) == HIT_AN_OBJECT_COLOR)) {
				sun_illumination = std::fmax(-(sun_light_dir.dot(hit.normal)), 0);
			}

			Vector3 sun_plus_base_color =
				sun_light_color * sun_illumination * sun_light_str
				+ base_light_color * base_light_str * (1 - sun_illumination);
			Vector3 color = hit.mat.col * sun_plus_base_color;

			//Do reflection if ray can still reflect and calc new color
			if (n_bounces < max_reflections) {
				//Ray has hit an object, so reflect vector along object normal
				Ray new_ray = Ray(Vector3(ray.pos), Vector3(hit.normal * 2 + ray.dir).get_normalized());
				new_ray.march(min_marching_dist);

				//Update color
				color = color * (1 - hit.mat.reflection_index);
				if (hit.mat.reflection_index != 0)
				{
					color = color +
						ray_march(new_ray, scene, n_bounces + 1) * hit.mat.col * hit.mat.reflection_index;
				}
			}
			return color;
		}
		ray.march(hit.dist);

		i++;
	}
	return base_light_color;
}