#include "include/Game.hpp"
#include <stdio.h>

Game::Game()
  : mWindow(sf::VideoMode(800, 600), "Platforms"),
    TimePerFrame(sf::seconds(1.f/60.f)),
    playerSprite(),
    playerPosition(400.f, ground),
    mIsMovingLeft(false),
    mIsMovingRight(false),
    mIsJumping(false),
    hasJumped(false),
    hasDoubleJumped(false),
    canDoubleJump(false),
    playerSpeed(0.f, 0.f),
    gravity(0.f, 4.f),
    drag(0.5f, 0.f)
{
  if (!playerTexture.loadFromFile("textures/player_sprite.png")) {
    //??
  }
  playerSprite.setTexture(playerTexture);
  playerSprite.setPosition(playerPosition);
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
      update(TimePerFrame, playerPosition, playerSpeed);
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

void Game::update(sf::Time deltaTime, sf::Vector2f &playerPos, sf::Vector2f &playerSpeed) {
  sf::Vector2f speed(0.f, 0.f);

  if (mIsMovingLeft) {
    speed.x -= moveSpeed;
  }
  if (mIsMovingRight) {
    speed.x += moveSpeed;
  }
  if (mIsJumping) {
    // Handle jumpstates
    if (!hasJumped) {
      hasJumped = true;
      speed.y -= jumpSpeed*5;
      speed.x *= 1.5;
    } else if (canDoubleJump && !hasDoubleJumped) {
      hasDoubleJumped = true;
      canDoubleJump = false;
      speed.y -= jumpSpeed*5;
      speed.x *= 1.5;
    }
  } else if (playerPos.y < ground) {
    speed += gravity;
  } else if (playerPos.y > ground) {
    hasJumped = false;
    hasDoubleJumped = false;
    canDoubleJump = false;
    playerSpeed.y = 0.f;
    speed.y = 0.f;
    playerPos.y = ground;
  }
  /*float mod = 1.f;
  if (playerSpeed.x > 0) {
    mod = -1.f;
    }*/
  playerSpeed += speed;
  playerSpeed.x = speed.x;
  /*  if (abs(playerSpeed.x) > maxSpeed) {
    playerSpeed.x = maxSpeed;
    if (playerSpeed.x < 0) {
      playerSpeed.x *= -1;
    }
    }*/
  playerPos += playerSpeed* deltaTime.asSeconds()*10.f;
  playerSprite.setPosition(playerPos);
}

void Game::render() {
  mWindow.clear();
  //mWindow.draw(things);
  mWindow.draw(playerSprite);
  mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
  if (key == sf::Keyboard::Escape) {
    mWindow.close();
  } else if (key == sf::Keyboard::Space) {
    mIsJumping = isPressed;
    if (!mIsJumping && hasJumped && !hasDoubleJumped && !canDoubleJump) {
      canDoubleJump = true;
    }
  } else if (key == sf::Keyboard::A || key == sf::Keyboard::Left) {
    mIsMovingLeft = isPressed;
  } else if (key == sf::Keyboard::D || key == sf::Keyboard::Right) {
    mIsMovingRight = isPressed;
  }
 }
