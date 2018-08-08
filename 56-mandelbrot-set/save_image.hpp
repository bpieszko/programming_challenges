#include <vector>

#ifndef SAVE_IMAGE_HPP
#define SAVE_IMAGE_HPP

#include "window.hpp"

void plot(window<int> &scr, std::vector<int> &colors, int iter_max, const char *fname, bool smooth_color);

#endif // SAVE_IMAGE_HPP