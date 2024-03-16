#include<SDL.h>
#include<thread>

#include"scene.h"
#include"globals.h"
#include"ray_marching.h"


void render(SDL_Renderer* renderer, Scene& scene, int mouse_X, int mouse_Y) {
	sun_light_dir = pixel_to_world_coords(WINDOW_WIDTH - mouse_X, WINDOW_HEIGHT - mouse_Y).get_normalized();

	std::vector<Pixel> rendered_pixels(WINDOW_WIDTH * WINDOW_HEIGHT);
	std::vector<std::thread> threads;
	for (int i = 0; i < max_n_threads; i++) {
		threads.push_back(
			std::thread(draw_threaded, std::ref(scene), i, max_n_threads, std::ref(rendered_pixels)));
	}

	for (std::thread& t : threads) {
		if (t.joinable()) {
			t.join();
		}
	}

	for (const auto& p : rendered_pixels) {
		SDL_SetRenderDrawColor(renderer, p.col.x, p.col.y, p.col.z, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawPoint(renderer, p.x, p.y);
	}

	SDL_RenderPresent(renderer);
}