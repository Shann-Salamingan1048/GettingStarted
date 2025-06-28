#include "Shader.h"

Shader::Shader(const char* vertPath, const char* fragPath)
{
	try
	{
		std::string vShaderCode = readShaderFile(vertPath);
		std::string fShaderCode = readShaderFile(fragPath);

		GLuint vertShader = compileShader(vShaderCode.c_str(), GL_VERTEX_SHADER, "VERTEX");
		GLuint fragShader = compileShader(fShaderCode.c_str(), GL_FRAGMENT_SHADER, "FRAGMENT");

		m_ID = createShaderProgram(vertShader, fragShader);

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}
	catch (const std::exception& e) 
	{
		// Clean up on failure
		if (m_ID != 0) {
			glDeleteProgram(m_ID);
			m_ID = 0;
		}
		std::println("ERROR::SHADER::CONSTRUCTION_FAILED: {}", e.what());
		throw; // Re-throw to let caller handle
	}

}
GLuint Shader::compileShader(const char* source, GLenum type, const char* typeName)
{
	GLuint shader = glCreateShader(type);
	if (shader == 0) {
		throw std::runtime_error(std::format("Failed to create {} shader", typeName));
	}

	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		GLint logLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

		std::string log(logLength, '\0');
		glGetShaderInfoLog(shader, logLength, nullptr, log.data());

		glDeleteShader(shader);
		throw std::runtime_error(std::format("{} shader compilation failed: {}",
			typeName, log));
	}

	return shader;
}
GLuint Shader::createShaderProgram(GLuint vertShader, GLuint fragShader)
{
	GLuint program = glCreateProgram();
	if (program == 0) {
		throw std::runtime_error("Failed to create shader program");
	}
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) 
	{
		GLint logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

		std::string log(logLength, '\0');
		glGetProgramInfoLog(program, logLength, nullptr, log.data());

		glDeleteProgram(program);
		throw std::runtime_error(std::format("Shader program linking failed: {}", log));
	}

	return program;
	
}
std::string Shader::readShaderFile(const char* filePath)
{
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file.open(filePath);
		std::stringstream stream;
		stream << file.rdbuf();
		return stream.str();
	}
	catch (const std::ifstream::failure& e)
	{
		throw std::runtime_error(std::format("Failed to read shader file '{}': {}",
			filePath, e.what()));
	}
}
void Shader::deleteShader()
{
	glDeleteProgram(m_ID);
}
void Shader::use()
{
	glUseProgram(m_ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}
unsigned int Shader::getID()
{
	return m_ID;
}
