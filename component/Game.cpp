//
// Created by iagoc on 08/12/2020.
//

#include "Game.hpp"

Game *Game::instance = nullptr;

Game *Game::getInstance() {
    if (!instance) instance = new Game();
    return instance;
}

sf::Window* Game::getWindow() {
    return this->window;
}

sf::Window* Game::newWindow(sf::VideoMode mode, const std::string &title, int style, const sf::ContextSettings &settings) {
    this->window = new sf::Window(mode, title, style, settings);
    return this->window;
}
