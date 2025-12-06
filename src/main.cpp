#include "parser.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <string>
#include <vector>

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

  window.setPosition(sf::Vector2i(
      sf::VideoMode::getDesktopMode().size.x * 0.5 - window.getSize().x * 0.5,
      sf::VideoMode::getDesktopMode().size.y * 0.5 - window.getSize().y * 0.5));
  window.setVerticalSyncEnabled(true);

  std::vector<sf::CircleShape> pixelShapes(image->pixels.size());

  for (int i = 0; i < image->width; i++) {
    for (int j = 0; j < image->height; j++) {
      const auto &p = image->pixels[i * image->height + j];

      sf::CircleShape px(1.0f);
      // std::cout << p.r << ' ' << p.g << ' ' << p.b << std::endl;
      px.setFillColor(sf::Color(p.r, p.g, p.b, 255));
      px.setPosition(sf::Vector2f(i, j));
      pixelShapes[i * image->height + j] = px;
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
