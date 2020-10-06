#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works with OpenGL!");

    glClearColor(0, 0, 0, 0);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        glViewport(0, 0, window.getSize().x, window.getSize().y);

        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_QUADS);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-.5f, -.5f);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(.5f, -.5f);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(.5f, .5f);

        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-.5f, .5f);

        glEnd();

        window.display();
    }

    return 0;
}