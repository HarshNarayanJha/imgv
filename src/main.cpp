#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "parser.hpp"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: imgv <image_file.ppm>" << std::endl;
    return 1;
  }

  std::string filename = argv[1];

  Parser p(filename);
  PPM *image = p.parse();

  if (image == nullptr) {
    std::cerr << "Failed to parse image file" << std::endl;
    return 1;
  }

  std::cout << "Reading Image: " << image->width << 'x' << image->height << ' '
            << image->maxColor << " - " << image->pixels.size() << std::endl;

  sf::RenderWindow window(sf::VideoMode({image->width, image->height}), "imgv",
                          sf::Style::None);

  // center the window
  window.setPosition(sf::Vector2i(
      sf::VideoMode::getDesktopMode().size.x * 0.5 - window.getSize().x * 0.5,
      sf::VideoMode::getDesktopMode().size.y * 0.5 - window.getSize().y * 0.5));
  window.setVerticalSyncEnabled(true);

  std::vector<sf::RectangleShape> pixelShapes(image->width * image->height);

  for (int i = 0; i < image->width; i++) {
    for (int j = 0; j < image->height; j++) {
      const auto &p = image->pixels[j * image->width + i];

      sf::RectangleShape px({1.0f, 1.0f});
      // std::cout << p.r << ' ' << p.g << ' ' << p.b << std::endl;

      px.setFillColor(sf::Color(p.r, p.g, p.b, 255));
      px.setPosition(sf::Vector2f(i, j));
      pixelShapes[j * image->width + i] = px;
    }
  }

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    window.clear(sf::Color::Black);

    for (const auto &px : pixelShapes) {
      window.draw(px);
    }

    window.display();
  }

  return 0;
}
