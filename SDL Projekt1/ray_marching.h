#pragma once
#include"vector"
#include"scene.h"

void draw_threaded(Scene& scene, int index, int n_threads, std::vector<Pixel>& rendered_pixel);