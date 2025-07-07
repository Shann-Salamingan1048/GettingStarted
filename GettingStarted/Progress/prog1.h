#pragma once
#include "../global.h"
#include "../Shader.h"
#include "../Texture.h"
// camera
static glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
static glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
static glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// timing
static float deltaTimeCam = 0.0f;	// time between current frame and last frame
static float lastFrame = 0.0f;

static bool firstMouse = true;
static float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
static float pitch = 0.0f;
static float lastX = 800.0f / 2.0;
static float lastY = 600.0 / 2.0;
static float fov = 45.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypo);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
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

	void tryTextureContainer();
	void doubleTexture();

	void tryGLM();

	void try3D();
	void more3D();
	void moreCubes();

	void tryCam();
	void camWithController();
	void camWithControllerProcessInput(GLFWwindow* window);
	void camUsingMouse();
	void camUsingMouseProcessInput(GLFWwindow* window);

public: // exercises
	void twoTriangle();
	void twoTriangle2();
	void twoTriangle3();

	void triangleUpSideDown();
	void moveTriangleUsingUniform();
	void setColorUsingVertexPosition();

	void onlyAwesomeFaceOtherDirection();
	void experimentWithWrappingMethods();
	void displayOnlyCenterPixels();
	void controlMixUsingUpDownKeys();
	void controlMixUsingUpDownKeysInputs(GLFWwindow* window, float& mix, float scale);

	void GLM_Rotate_Translate();
	void GLM_tryDrawingSecondContainerPlaceItDifferentPositionUsingTransformation();

	void rotateEvery3rdCube();
	void rotationalRingBox();

private:
	void initGLFW();
	void printMat4(const glm::mat4& mat, const std::string& name) const;
private:
	void processInput(GLFWwindow* window);

private:
	GLFWwindow* m_window;
	int m_width;
	int m_height;
private:
	constexpr static double targetFPS = 60.0;
	constexpr static double frameTime = 1.0 / targetFPS;
	std::chrono::steady_clock::time_point lastTime;
};