#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

class Game {

public:
  Game();
  void run();

private:
  void processEvents();
  void update(sf::Time deltaTime, sf::Vector2f &playerPos, sf::Vector2f &playerSpeed);
  void render();
  void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
  void loadResources();
  sf::Vector2f applyForces(sf::Vector2f playerSpeed, sf::Vector2f forces);

private:
  sf::RenderWindow mWindow;
  sf::Time TimePerFrame;
  sf::Texture playerTexture;
  sf::Texture wallsTexture;
  sf::Sprite playerSprite;

  // This is really ugly, move me out to the player controller maybe?
  sf::Vector2f playerPosition;
  sf::Vector2f playerSpeed;
  bool mIsMovingLeft;
  bool mIsMovingRight;
  bool mIsJumping;
  bool hasJumped;
  bool hasDoubleJumped;
  bool canDoubleJump;
  static const float moveSpeed = 15.f;
  static const float jumpSpeed = 10.f;
  static const float maxSpeed = 12.f;
  static const float ground = 400.f;
  sf::Vector2f gravity;
  sf::Vector2f drag;

};

#endif
