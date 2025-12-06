#pragma once

#include <vector>

struct Color {
  int r;
  int g;
  int b;
};

struct PPM {
  unsigned int width;
  unsigned int height;
  unsigned int maxColor;
  std::vector<Color> pixels;
};
