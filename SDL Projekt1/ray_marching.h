#pragma once
#include<SDL.h>
#include"scene.h"

void render(SDL_Window* window, SDL_Renderer* renderer, Scene& scene, int mouse_X, int mouse_Y);