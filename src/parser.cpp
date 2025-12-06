#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "parser.hpp"
#include "ppm.hpp"

PPM *Parser::parse() {
  std::ifstream file(this->file);
  if (!file.is_open()) {
    std::cerr << "Unable to open file " << this->file << std::endl;
    return nullptr;
  }

  std::string line;

  // read in the format header
  std::getline(file, line);

  while (line.starts_with("#")) {
    std::getline(file, line);
  }

  if (line != "P3") {
    std::cerr << "Unsupported format: " << line << std::endl;
    return nullptr;
  }

  unsigned int width, height, maxColor;

  // read in the width and height
  std::getline(file, line);

  while (line.starts_with("#")) {
    std::getline(file, line);
  }

  std::stringstream ss(line);
  ss >> width;
  ss >> height;

  // read in the max color value
  std::getline(file, line);

  while (line.starts_with("#")) {
    std::getline(file, line);
  }

  maxColor = std::stoi(line);

  std::vector<Color> pixels;

  std::cout << "Parsing Image Header Done: " << width << "x" << height
            << std::endl;

  while (std::getline(file, line)) {
    if (line.starts_with("#")) {
      continue;
    }

    std::stringstream ss(line);
    Color pixel;
    int r, g, b;
    ss >> r;
    ss >> g;
    ss >> b;

    // std::cout << "Parsing Pixel: " << r << " " << g << " " << b << std::endl;

    pixel.r = (r * 255) / maxColor;
    pixel.g = (g * 255) / maxColor;
    pixel.b = (b * 255) / maxColor;

    pixels.push_back(pixel);
  }

  this->ppm.width = width;
  this->ppm.height = height;
  this->ppm.maxColor = maxColor;
  this->ppm.pixels = pixels;

  file.close();
  return &this->ppm;
}
