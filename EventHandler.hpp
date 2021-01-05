//
// Created by iagoc on 04/12/2020.
//

#ifndef P1RV_EVENTHANDLER_HPP
#define P1RV_EVENTHANDLER_HPP


#include <unordered_map>
#include <list>
#include <functional>
#include <string>
#include <SFML/Graphics.hpp>

class EventHandler {
public:
    // TODO : Create a Action class to simplify the structure and contain features
    static std::list<std::pair<std::string, std::function<void(sf::Event::EventType)>>> actions;
    // TODO : Do the same for Binding
    static std::unordered_map<sf::Keyboard::Key, std::function<void(sf::Event::EventType)>> bindings;

    static void addAction(const std::string& name, const std::function<void(sf::Event::EventType)>& f);
    static bool setBinding(sf::Keyboard::Key key, const std::string& actionName);
    static void clearBindings();
    static void processEvent(sf::Keyboard::Key key, sf::Event::EventType event);
};

#endif //P1RV_EVENTHANDLER_HPP
