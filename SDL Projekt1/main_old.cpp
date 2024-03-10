//#include <SDL.h>
//#include <iostream>
//#include <vector>
//
//const int WINDOW_WIDTH = 1440;
//const int WINDOW_HEIGHT = 720;
//
//SDL_Window* window;
//SDL_Renderer* renderer;
//SDL_Event event;
//
//double fps = 60;
//double timestep = 1000 / fps;
//
//int mouse_X;
//int mouse_Y;
//
//void start();
//
//int main(int argc, char* argv[])
//{
//	start();
//	return 0;
//}
//
//void handle_events(bool&);
//void render();
//
//void start() {
//	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
//
//	bool running = true;
//	while (running)
//	{
//		handle_events(running);
//		render();
//		SDL_Delay(timestep);
//	}
//}
//
//void handle_events(bool& running) {
//	while (SDL_PollEvent(&event)) {
//		switch (event.type)
//		{
//		case SDL_QUIT:
//			running = false;
//			return;
//			break;
//
//		case SDL_KEYDOWN:
//			switch (event.key.keysym.sym) {
//			case SDLK_ESCAPE:
//				running = false;
//				return;
//
//			default:
//				break;
//			}
//			break;
//
//		case SDL_MOUSEMOTION:
//			SDL_GetMouseState(&mouse_X, &mouse_Y);
//			break;
//
//		default:
//			break;
//		}
//	}
//}
//
//void render() {
//	SDL_RenderClear(renderer);
//
//	SDL_Rect rect = { mouse_X, mouse_Y, 100, 100};
//	SDL_RenderDrawRect(renderer, &rect);
//
//	SDL_RenderPresent(renderer);
//}