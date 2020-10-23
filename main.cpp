#include <iostream>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include "GameObject.h"
#include "Scene.h"
#include "TestScene.h"
#include <GL/glu.h>


int main()
{
    // Setup
    sf::RenderWindow window(sf::VideoMode(800, 600), "Making the basic structure");
    window.setVerticalSyncEnabled(true);
    window.setActive(true);

    glewInit();

    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
   
    // Resetting matrix
    glLoadIdentity();

    // Viewport
    glViewport(0, 0, 800, 600);

    // Mise en place de la perspective
    gluPerspective(60, 800/600, 0.1f, 10.f);

    // Placement de la caméra
    gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);

    // Retourne a la pile modelview
    glMatrixMode(GL_MODELVIEW);

    glScalef(0.05f, 0.05f, 0.05f);

    Scene* actualScene = new TestScene();
    actualScene->initialize();

    // Game Loop
    while (window.isOpen())
    {
        // Process Input
        sf::Event event;
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
                    std::cout << "MouseButtonPressed" << std::endl;
                    break;
                case sf::Event::MouseButtonReleased:
                    std::cout << "MouseButtonReleased" << std::endl;
                    break;
                case sf::Event::MouseMoved:
                    std::cout << "MouseMoved" << std::endl;
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

        // Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        actualScene->draw();

        // Swap buffers
        window.display();
    }

    // Cleaning Up

    return EXIT_SUCCESS;
}
