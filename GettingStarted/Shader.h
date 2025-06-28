#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <print>

class Shader
{
public:

	Shader(const char* vertPath, const char* fragPath);
	void use();
	unsigned int getID();
	void deleteShader();

public:
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
private:
	unsigned int m_ID;

private:
	std::string readShaderFile(const char* filePath);
	GLuint createShaderProgram(GLuint vertShader, GLuint fragShader);
	GLuint compileShader(const char* source, GLenum type, const char* typeName);
};