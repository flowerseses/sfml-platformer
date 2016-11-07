#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

class Game {

public:
  Game();
  void run();

private:
  void processEvents();
  void update(sf::Time deltaTime);
  void render();
  void handlePlayerInput(sf::Keyboard::Key, bool);
  void loadResources();

private:
  sf::RenderWindow mWindow;
  sf::Time TimePerFrame;
  //sf::Sprite playerSprite;
  //sf::Sprite wallsSprite;

};

#endif
