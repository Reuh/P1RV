#include <iostream>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include "GameObject.h"
#include "Scene.h"
#include "TestScene.h"
#include <SFML/System.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Collider.h"
#include <algorithm>
#include "Shader.hpp"
#include "MatrixStack.hpp"

// Player position
const glm::vec3 up(0,1,0); // up axis, fixed
glm::vec3 position(-2,0,0); // player position
glm::vec3 front(1,0,0); // player front axis (parrallel to the horizontal) = rotate((1,0,0), angleX, up)
glm::vec3 right(0,0,1); // player right axis (parrallel to the horizontal) = cross(front, up)
glm::vec3 eye(1,0,0); // player eye direction = rotate(front, angleX, right)
float speed = 1; // movement speed per second
float angleX = 0; // eye rotation
float angleY = 0;
float rotateSpeed = 0.1; // rotation speed per second

int main()
{
    // Setup window
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    sf::Window window(sf::VideoMode(800, 600), "Making the basic structure", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    window.setActive(true);

    // Setup OpenGL
    glewInit();
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    // Load shader
    Shader shader = Shader("shaders/vertex.glsl", "shaders/frag.glsl");

    // Setup default matrices
    // Mise en place de la perspective
    setProjection(glm::perspective(glm::radians(60.0f), (float)800 / (float)600, 0.1f, 100.0f));
    // Placement de la caméra
    setView(glm::lookAt(position, position+eye, up));

    // Init scene
    Scene* actualScene = new TestScene();
    actualScene->initialize();

    // Time
    sf::Clock clock;

    // Movement
    sf::Mouse::setPosition(sf::Vector2i(400, 300), window);
    sf::Vector2i mousePosition = sf::Mouse::getPosition();

    // Game Loop
    while (window.isOpen())
    {
        // Process Input
        sf::Event event{};
        while (window.pollEvent(event))
        {
            // TODO Send events to the scene
            // It may be a good idea to create a middleware that uses signals
            // A scene can expose some signal inputs that a manager will attach to the keyboard
            switch (event.type) {
                case sf::Event::KeyPressed:
                    std::cout << "KeyPressed" << std::endl;
                    break;
                case sf::Event::KeyReleased:
                    std::cout << "KeyReleased" << std::endl;
                    break;
                case sf::Event::MouseButtonPressed:
                    //std::cout << "MouseButtonPressed" << std::endl;
                    // Fire
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        auto objList = actualScene->getObjectList();
                        for(auto iter = objList->begin() ; iter != objList->end(); ++iter) {
                            Collider* coll = (*iter)->getComponent<Collider>();
                            if (coll != nullptr && coll->collideRay(position, eye)) {
                               std::cout << "Touché!" << std::endl;
                            }
                        }
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    std::cout << "MouseButtonReleased" << std::endl;
                    break;
                case sf::Event::MouseMoved:
                    //std::cout << "MouseMoved" << std::endl;
                    break;
                case sf::Event::JoystickButtonPressed:
                    std::cout << "JoystickButtonPressed" << std::endl;
                    break;
                case sf::Event::JoystickButtonReleased:
                    std::cout << "JoystickButtonReleased" << std::endl;
                    break;
                case sf::Event::JoystickMoved:
                    std::cout << "JoystickMoved" << std::endl;
                    break;
                case sf::Event::JoystickConnected:
                    std::cout << "JoystickConnected" << std::endl;
                    break;
                case sf::Event::JoystickDisconnected:
                    std::cout << "JoystickDisconnected" << std::endl;
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    glViewport(0, 0, event.size.width, event.size.height);
                    break;
                default:
                    break;
            }
        }

        // Get delta time
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        // Player movement
        // TODO: separate into a PlayerMovement component
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            position += right * speed*dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            position -= right * speed*dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            position += front * speed*dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            position -= front * speed*dt;

        sf::Vector2i newMousePosition = sf::Mouse::getPosition();
        sf::Vector2i diff = newMousePosition - mousePosition;
        sf::Mouse::setPosition(sf::Vector2i(400, 300), window); // re-center mouse
        mousePosition = sf::Mouse::getPosition();
        angleY += -diff.x * rotateSpeed * dt;
        angleX += -diff.y * rotateSpeed * dt;
        angleX = std::min(std::max(angleX, -3.14f/2), 3.14f/2); // prevent infinite rotation on x axis

        // Update position vectors
        front = glm::rotate(glm::vec3(1,0,0), angleY, up);
        right = glm::cross(front, up);
        eye = glm::rotate(front, angleX, right);

        // Update camera
        setView(glm::lookAt(position, position+eye, up));

        // Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        actualScene->draw(&shader);

        // Swap buffers
        window.display();
    }

    // Cleaning Up

    return EXIT_SUCCESS;
}
