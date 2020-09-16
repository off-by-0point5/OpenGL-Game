/*
 * shader.h
 *
 *  Created on: 08.08.2020
 *      Author: offbyone
 */

#ifndef SHADER_H_
#define SHADER_H_
#include <GL/glew.h>
#include <string>

class Shader {
public:
	Shader(const char* vertexShaderFilename, const char* fragmentShaderFilename);
	virtual ~Shader();

	void bind();
	void unbind();
private:
	GLuint compile(std::string shaderSource, GLenum type);
	std::string parse(const char* filename);
	GLuint createShader(const char* vertexShaderFilename, const char* fragmentShaderFilename);
	GLuint shaderId;
};

#endif /* SHADER_H_ */
