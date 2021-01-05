//
// Created by iagoc on 08/12/2020.
//

#ifndef P1RV_GAME_HPP
#define P1RV_GAME_HPP


#include <SFML/Window.hpp>

class Game {
private:
    static Game* instance;
    sf::Window* window;
public:
    static Game* getInstance();
    sf::Window* getWindow();
    sf::Window* newWindow(sf::VideoMode mode, const std::string &title, int style=sf::Style::Default, const sf::ContextSettings &settings=sf::ContextSettings());
};

#endif //P1RV_GAME_HPP
