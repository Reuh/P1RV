#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

int main()
{
    // setup window
    sf::Window window(sf::VideoMode(1280, 720), "OpenGL test");
    window.setVerticalSyncEnabled(true);
    window.setActive(true);

    // load ressources
    // ...

    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // clear buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw
        // ...

        // swap buffers
        window.display();
    }

    // release ressources
    // ...

    return 0;
}