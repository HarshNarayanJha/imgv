#pragma once

#include <vector>

struct Color {
  int r;
  int g;
  int b;
};

struct PPM {
  int width;
  int height;
  int maxColor;
  std::vector<Color> pixels;
};
