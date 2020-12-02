#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Shader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

bool Shader::checkErrors(GLuint shader, const std::string &type) {
    GLint success;
    GLchar message[1024];
    if(type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(shader, 1024, NULL, message);
            std::cerr << "[ERROR] Shader compilation error for " << type << ": " << message << std::endl;
            return false;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shader, 1024, NULL, message);
            std::cerr << "[ERROR] Shader linking error: " << message << std::endl;
            return false;
        }
    }
    return true;
}

Shader::Shader(const char* vertPath, const char* fragPath) {
    // Load fragment shader
    std::string fragmentCode;
    std::ifstream fShaderFile;
    fShaderFile.open(fragPath);
    std::stringstream fShaderStream;
    fShaderStream << fShaderFile.rdbuf();
    fShaderFile.close();
    fragmentCode = fShaderStream.str();

    const char* fCode = fragmentCode.c_str();
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fCode, NULL);
    glCompileShader(fragment);
    checkErrors(fragment, "FRAGMENT");

    // Load vertex shader
    std::string vertexCode;
    std::ifstream vShaderFile;
    vShaderFile.open(vertPath);
    std::stringstream vShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    vShaderFile.close();
    vertexCode = vShaderStream.str();

    const char* vCode = vertexCode.c_str();
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vCode, NULL);
    glCompileShader(vertex);
    checkErrors(vertex, "VERTEX");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkErrors(ID, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() const {
    glUseProgram(ID);
}

void Shader::sendUniform(const char* name, const glm::mat4 matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::sendUniform(const char* name, const GLfloat matrix[14]) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &matrix[0]);
}
