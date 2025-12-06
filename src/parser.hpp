#pragma once

#include <string>

#include "ppm.hpp"

class Parser {
public:
  Parser(std::string file) { this->file = file; };
  ~Parser() {};

  PPM *parse();

private:
  std::string file;
  PPM ppm;
};
