#include "include/Game.hpp"

Game::Game()
  : mWindow(sf::VideoMode(800, 600), "Platforms"),
    TimePerFrame(sf::seconds(1.f/60.f))
{
  // Do nothing for now.
}

void Game::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while (mWindow.isOpen()) {
    timeSinceLastUpdate += clock.restart();
    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;
      processEvents();
      update(TimePerFrame);
    }
    render();
  }
}


void Game::processEvents() {
  sf::Event event;
  while (mWindow.pollEvent(event)) {
    switch (event.type) {
    case sf::Event::Closed:
      mWindow.close();
      break;
    case sf::Event::KeyPressed:
      handlePlayerInput(event.key.code, true);
      break;
    case sf::Event::KeyReleased:
      handlePlayerInput(event.key.code, false);
      break;
    }
  }
}

void Game::update(sf::Time deltatime) {
  sf::Vector2f speed(0.f, 0.f);

  // Handle movement here!
}

void Game::render() {
  mWindow.clear();
  //mWindow.draw(things);
  mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
  if (key == sf::Keyboard::Escape) {
    mWindow.close();
  }
 }
