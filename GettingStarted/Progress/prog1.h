#pragma once
#include "../global.h"
#include "../Shader.h"
class prog1
{
public:
	prog1();
	prog1(int width, int height, const char* title);

public:
	void helloTriangle();
	void helloWindow();
	void helloSquare();
	
	void changingColor();
	void mixColor();

	void tryShaderClass();
public: // exercises
	void twoTriangle();
	void twoTriangle2();
	void twoTriangle3();

	void triangleUpSideDown();
	void moveTriangleUsingUniform();
	void setColorUsingVertexPosition();

private:
	void initGLFW();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

private:
	void processInput(GLFWwindow* window);

private:
	GLFWwindow* m_window;
	int m_width;
	int m_height;

};
