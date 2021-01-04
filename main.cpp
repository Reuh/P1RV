#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <algorithm>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <component/EventHandler.hpp>

#include "GameObject.hpp"
#include "scene/Scene.hpp"
#include "scene/TestScene.hpp"
#include "Shader.hpp"
#include "MatrixStack.hpp"
#include "component/Game.hpp"

const float fov = glm::radians(60.0f);
const float nearPlane = 0.1f;
const float farPlane = 100.0f;

int main()
{
    // Get game instance
    Game *game = Game::getInstance();

    // Setup window
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    sf::Window *window = game->newWindow(sf::VideoMode(800, 600), "P1RV - FPS", sf::Style::Default, settings);
    window->setVerticalSyncEnabled(true);
    window->setMouseCursorVisible(false);
    window->setMouseCursorGrabbed(true);
    window->setActive(true);

    // Center mouse
    sf::Mouse::setPosition(sf::Vector2i(400, 300), *window);

    // Setup OpenGL
    glewInit();
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    // Load shader
    Shader shader = Shader("shaders/vertex.glsl", "shaders/frag.glsl");

    // Mise en place de la perspective
    setPerspective(fov, (float)800 / (float)600, nearPlane, farPlane);

    // Init scene
    Scene* actualScene = new TestScene();
    actualScene->initialize();

    // Time
    sf::Clock clock;

    // Game Loop
    while (window->isOpen()) {
        // Process Input
        sf::Event event{};
        while (window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        window->close();
                    else
                        EventHandler::processEvent(event.key.code, event.type);
                    break;
                case sf::Event::KeyReleased:
                    EventHandler::processEvent(event.key.code, event.type);
                    break;
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::Resized:
                    glViewport(0, 0, event.size.width, event.size.height);
                    setPerspective(fov, (float)event.size.width / (float)event.size.height, nearPlane, farPlane);
                    break;
                default:
                    break;
            }
            // Send event to the scene
            actualScene->onWindowEvent(event);
        }

        // Get delta time
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        actualScene->update(dt);

        // Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        actualScene->draw(&shader);

        // Swap buffers
        window->display();
    }

    // Cleaning Up

    return EXIT_SUCCESS;
}
