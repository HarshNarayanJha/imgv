#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowEnums.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode({800u, 600u}), "imgv", sf::Style::None);

  window.setPosition({10, 50});
  window.setVerticalSyncEnabled(true);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    sf::CircleShape circle(50.0f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition({100, 100});

    window.clear(sf::Color::Black);

    window.draw(circle);

    window.display();
  }

  return 0;
}
