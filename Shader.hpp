#ifndef P1RV_SHADER_H
#define P1RV_SHADER_H

#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <string>

class Shader {
private:
	// Check for shader compilation error
	bool checkErrors(GLuint shader, const std::string &type);
public:
	unsigned int ID; // OpenGL programm ID

	Shader(const char* vertPath, const char* fragPath);

	// Enable shader.
	void use() const;

	// Send uniforms to the shader.
	void sendUniform(const char* name, const glm::mat4 matrix) const;
	void sendUniform(const char* name, const GLfloat matrix[14]) const;
};

#endif