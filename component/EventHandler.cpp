//
// Created by iagoc on 04/12/2020.
//

#include "EventHandler.hpp"


std::list<std::pair<std::string, std::function<void(sf::Event::EventType)>>> EventHandler::actions;
std::unordered_map<sf::Keyboard::Key, std::function<void(sf::Event::EventType)>> EventHandler::bindings;

void EventHandler::addAction(const std::string& name, const std::function<void(sf::Event::EventType)>& f) {
    actions.emplace_back(name, f);
}

bool EventHandler::setBinding(sf::Keyboard::Key key, const std::string& actionName) {
    for (const std::pair<std::string, std::function<void(sf::Event::EventType)>>& action : actions ) {
        if (action.first == actionName) {
            bindings.insert({key, action.second});
            return true;
        }
    }
    return false;
}

void EventHandler::processEvent(sf::Keyboard::Key key, sf::Event::EventType event) {
    bindings[key](event);
}

void EventHandler::clearBindings() {
    bindings.clear();
}
