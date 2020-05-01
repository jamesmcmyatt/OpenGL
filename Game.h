#pragma once
#include "Libraries.h"
#include "Camera.h"
//enums

enum shader_Enum { SHADER_CORE_PROGRAM = 0 };
enum texture_enum { TEXTURE1= 0, TEXTURE2, TEXTURE3, TEXTURE4};
enum material_Enum { MATERIAL_1 = 0 };
enum mesh_Enum { Mesh_QUAD = 0 };

class Game
{
private:
	//variables
	GLFWwindow* window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int frameBufferWidth;
	int frameBufferHeight;

	//camera
	Camera camera;

	glm::mat4 ViewMatrix;
	glm::vec3 cameraPosition;
	glm::vec3 cameraUp;
	glm::vec3 cameraFront;

	glm::mat4 projectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;

	//OpenGL content
	const int GL_VERSION_MAJ;
	const int GL_VERSION_MIN;

	//mouse input
	double previousMouseX;
	double previousMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool mouseMove;

	//deltaTime
	float deltaTime;
	float currentTime;
	float previousTime;

	//Shader
	std::vector<Shader*> shaders;

	//Texture
	std::vector<Texture*> textures;

	//material
	std::vector<Material*> materials;

	//Models
	std::vector<Model*> models;

	//lights
	std::vector<glm::vec3*> lights;


	//functions
	void initializeGLFW();
	void initializeWindow(const char* title, bool resizable);
	void initializeGLEW();
	void initializeOpenGL();
	void initializeMatrices();// might not need
	void initializeShaders();
	void initializeTextures();
	void initializeMaterials();
	void initializeOBJfiles();
	void initializeModels();
	void initializeLights();
	void initializeUniforms();

	void updateUniforms();

public:

	Game(const char* title, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const int GL_VERSION_MAJ, const int GL_VERSION_MIN, bool resizable);

	virtual ~Game();

	//accessor
	int getWindowShouldClose();

	//modifier
	void setWindowShouldClose();

	//functions
	void updateDeltaTime();
	void updateMouseInput();
	void updateKeyboard();
	void updateInput();
	void update();
	void render();


	//static calls
	static void framebuffer_resize_callbacks(GLFWwindow* window, int fbw, int fbh);


};

