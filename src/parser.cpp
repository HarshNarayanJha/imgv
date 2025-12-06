#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "parser.hpp"
#include "ppm.hpp"

PPM *Parser::parse() {
  std::ifstream file(this->file, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Unable to open file " << this->file << std::endl;
    return nullptr;
  }

  std::string line;

  // read in the format header
  std::getline(file, line);

  while (!file.eof() && !line.empty() && line.starts_with("#")) {
    std::getline(file, line);
  }

  if (line != "P6") {
    std::cerr << "Unsupported format: " << line << std::endl;
    return nullptr;
  }

  unsigned int width = 0, height = 0, maxColor = 0;

  do {
    std::getline(file, line);
  } while (!file.eof() && !line.empty() && line.starts_with("#"));

  {
    std::stringstream ss(line);
    ss >> width;
    ss >> height;
    if (ss.fail()) {
      std::cerr << "Invalid image dimensions: " << line << std::endl;
      return nullptr;
    }
  }

  do {
    std::getline(file, line);
  } while (!file.eof() && !line.empty() && line.starts_with("#"));

  {
    std::stringstream ss(line);
    ss >> maxColor;
    if (ss.fail()) {
      std::cerr << "Invalid max color value: " << line << std::endl;
      return nullptr;
    }
  }

  if (width == 0 || height == 0) {
    std::cerr << "Invalid image dimensions" << std::endl;
    return nullptr;
  }

  if (maxColor == 0 || maxColor > 65535) {
    std::cerr << "Invalid max color value" << std::endl;
    return nullptr;
  }

  std::cout << "Parsing Image Header: " << width << "x" << height << std::endl;

  size_t nPixels = static_cast<size_t>(width) * height;
  std::vector<Color> pixels;
  pixels.reserve(nPixels);

  if (maxColor > 255) {
    std::cerr << "16-bit per channel is not supported yet." << std::endl;
    return nullptr;
  }

  std::vector<uint8_t> raw;
  raw.resize(nPixels * 3);
  file.read(reinterpret_cast<char *>(raw.data()), raw.size());
  if (!file) {
    std::cerr << "Failed to read image data" << std::endl;
    return nullptr;
  }

  for (size_t i = 0; i < nPixels; i++) {
    Color pixel;

    pixel.r = (raw[3 * i + 0] * 255) / maxColor;
    pixel.g = (raw[3 * i + 1] * 255) / maxColor;
    pixel.b = (raw[3 * i + 2] * 255) / maxColor;
    pixels.push_back(pixel);

    // std::cout << "Pixel: " << pixel.r << " " << pixel.g << " " << pixel.b
    //           << std::endl;
  }

  this->ppm.width = width;
  this->ppm.height = height;
  this->ppm.maxColor = maxColor;
  this->ppm.pixels = pixels;

  file.close();
  return &this->ppm;
}
