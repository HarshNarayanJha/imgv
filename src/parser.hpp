#pragma once

#include "ppm.hpp"
#include <string>

class Parser {
public:
  Parser(std::string file) { this->file = file; };
  ~Parser() {};

  PPM *parse();

private:
  std::string file;
  PPM ppm;
};
