#include <iostream>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include "GameObject.h"
#include "Scene.h"
#include "TestScene.h"
#include <GL/glu.h>
#include <SFML/System.hpp>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Collider.h"
#include <algorithm>

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

// Check for shader compilation error
// TODO: put into Shader class
void checkCompileErrors(GLuint shader, const std::string &type){
    GLint success;
    GLchar message[1024];
    if(type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(shader, 1024, NULL, message);
            std::cerr << "[ERROR] Shader compilation error for " << type << ": " << message << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shader, 1024, NULL, message);
            std::cerr << "[ERROR] Shader linking error: " << message << std::endl;
        }
    }
}


int main()
{
    // Setup
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    sf::Window window(sf::VideoMode(800, 600), "Making the basic structure", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    window.setActive(true);

    glewInit();

    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
   
    // Resetting matrix
    glLoadIdentity();

    // Viewport
    glViewport(0, 0, 800, 600);

    // Mise en place de la perspective
    gluPerspective(60, 800/600, 0.1f, 10.f);

    // Placement de la caméra
    gluLookAt(0, 0, 2, 0, 0, 1, 0, 1, 0);

    // Retourne a la pile modelview
    glMatrixMode(GL_MODELVIEW);

    glScalef(0.05f, 0.05f, 0.05f);

    // Load fragment shader
    std::string fragmentCode;
    std::ifstream fShaderFile;
    fShaderFile.open("shaders/frag.glsl");
    std::stringstream fShaderStream;
    fShaderStream << fShaderFile.rdbuf();
    fShaderFile.close();
    fragmentCode = fShaderStream.str();

    const char* fCode = fragmentCode.c_str();
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // Load vertex shader
    std::string vertexCode;
    std::ifstream vShaderFile;
    vShaderFile.open("shaders/vertex.glsl");
    std::stringstream vShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    vShaderFile.close();
    vertexCode = vShaderStream.str();

    const char* vCode = vertexCode.c_str();
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    unsigned int ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            position += right * speed*dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            position -= right * speed*dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            position += front * speed*dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            position -= front * speed*dt;
        }

        sf::Vector2i newMousePosition = sf::Mouse::getPosition();
        sf::Vector2i diff = newMousePosition - mousePosition;
        sf::Mouse::setPosition(sf::Vector2i(400, 300), window); // re-center mouse
        mousePosition = sf::Mouse::getPosition();
        angleY += -diff.x * rotateSpeed * dt;
        angleX += -diff.y * rotateSpeed * dt;
        //angleX = std::min(std::max(angleX, -3.14f/2), 3.14f/2);

        // Update position vectors
        front = glm::rotate(glm::vec3(1,0,0), angleY, up);
        right = glm::cross(front, up);
        eye = glm::rotate(front, angleX, right);

        // Update camera
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glViewport(0, 0, 800, 600);
        gluPerspective(60, 800/600, 0.1f, 10.f);
        gluLookAt(position.x, position.y, position.z, position.x+eye.x, position.y+eye.y, position.z+eye.z, up.x, up.y, up.z);

        // Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // TODO: switch to modern OpenGL pipeline fully
        GLfloat model[16]; 
        glGetFloatv(GL_MODELVIEW_MATRIX, model);
        GLfloat projection[16]; 
        glGetFloatv(GL_PROJECTION_MATRIX, projection);

        glUniformMatrix4fv(glGetUniformLocation(ID, "modelview"), 1, GL_FALSE, &model[0]);
        glUniformMatrix4fv(glGetUniformLocation(ID, "projection"), 1, GL_FALSE, &projection[0]);

        glUseProgram(ID);
        actualScene->draw();

        // Swap buffers
        window.display();
    }

    // Cleaning Up

    return EXIT_SUCCESS;
}
