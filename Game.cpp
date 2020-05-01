#include "Game.h"

//functions


void Game::initializeGLFW()
{
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "ERROR::GAME::GLFW FAILED INITIALIZE LINE 9\n";
		glfwTerminate();
	}
}

void Game::initializeWindow(const char* title, bool resizable)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJ);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MIN);;
	glfwWindowHint(GLFW_RESIZABLE, resizable);


	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);

	if (this->window == nullptr)
	{
		std::cout << "ERROR::GAME::GLFW WINDOW FAILED TO CREATE LINE 26\n";
	}

	glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callbacks);

	glfwMakeContextCurrent(this->window);

}

void Game::initializeGLEW()
{
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::GAME::GLEW FAILED INITIALIZE LINE 38\n";
		glfwTerminate();
	}
}

void Game::initializeOpenGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//input system
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::initializeMatrices()
{
	this->ViewMatrix = glm::mat4(1.f);
	this->ViewMatrix = glm::lookAt(this->cameraPosition, this->cameraPosition + this->cameraFront, this->cameraUp);

	this->projectionMatrix = glm::mat4(1.f);
	this->projectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight, this->nearPlane, this->farPlane);
}

void Game::initializeTextures()
{
	this->textures.push_back(new Texture(".png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture(".png", GL_TEXTURE_2D));
	
	this->textures.push_back(new Texture(".png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture(".png", GL_TEXTURE_2D));

}

void Game::initializeShaders()
{
	this->shaders.push_back(new Shader ( this->GL_VERSION_MAJ, this->GL_VERSION_MIN,"vertex_core.glsl", "fragment_core.glsl" ));
}

void Game::initializeMaterials()
{
	this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), 0, 1));
}

void Game::initializeOBJfiles()
{

}

void Game::initializeModels()
{
	std::vector<Mesh*>meshes;

	this->models.push_back(new Model(glm::vec3(4.f, -10.f, 4.f), this->materials[0],
		this->textures[TEXTURE3], this->textures[TEXTURE4], "Map7/map7.obj")); 


	for (auto*& i : meshes)
	{
		delete i;
	}
}


void Game::initializeLights()
{
	this->lights.push_back(new glm::vec3(10.f, 10.f, 0.f));
}

void Game::initializeUniforms()
{
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(projectionMatrix, "ProjectionMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
}

void Game::updateUniforms()
{
	this->ViewMatrix = this->camera.getViewMatrix();

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "cameraPos");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");

	//update frame buffer and viewmatrix
	glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);


	this->projectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight, this->nearPlane, this->farPlane);

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->projectionMatrix, "ProjectionMatrix");
}


//costructor
Game::Game(const char* title, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const int GL_VERSION_MAJ, const int GL_VERSION_MIN, bool resizable) : WINDOW_WIDTH(WINDOW_WIDTH), WINDOW_HEIGHT(WINDOW_HEIGHT), GL_VERSION_MAJ(GL_VERSION_MAJ), GL_VERSION_MIN(GL_VERSION_MIN), camera(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))
{

	//initialize variables
	this->window = nullptr;
	this->frameBufferWidth = this->WINDOW_WIDTH;
	this->frameBufferHeight = this->WINDOW_HEIGHT;

	this->cameraPosition = glm::vec3(0.f, 0.f, 1.f);
	this->cameraUp = glm::vec3(0.f, 1.f, 0.f);
	this->cameraFront = glm::vec3(0.f, 0.f, -1.f);

	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.f;

	this->deltaTime = 0.f;
	this->currentTime = 0.f;
	this->previousTime = 0.f;

	this->mouseX = 0.0;
	this->mouseY = 0.0;
	this->previousMouseX = 0.0;
	this->previousMouseY = 0.0;
	this->mouseOffsetX = 0.0;
	this->mouseOffsetY = 0.0;
	this->mouseMove = true;

	this->initializeGLFW();
	this->initializeWindow(title, resizable);
	this->initializeGLEW();
	this->initializeOpenGL();

	this->initializeMatrices();
	this->initializeShaders();
	this->initializeTextures();
	this->initializeMaterials();
	this->initializeOBJfiles();
	this->initializeModels();
	this->initializeLights();
	this->initializeUniforms();
}

Game::~Game()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();

	for (int i = 0; i < this->shaders.size(); i++)
	{
		delete this->shaders[i];
	}

	for (int i = 0; i < textures.size(); i++)
	{
		delete this->textures[i];
	}

	for (int i = 0; i < this->materials.size(); i++)
	{
		delete this->materials[i];
	}

	//delete models and lights  using new loops;

	for (auto*& i : this->models)
	{
		delete i;
	}

	for (int i = 0; i < lights.size(); i++)
	{
		delete this->lights[i];
	}

}

int Game::getWindowShouldClose()
{
	return glfwWindowShouldClose(this->window);
}

void Game::setWindowShouldClose()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}


void Game::updateDeltaTime()
{
	this->currentTime = static_cast<float>(glfwGetTime());
	this->deltaTime = this->currentTime - this->previousTime;
	this->previousTime = this->currentTime;
}

void Game::updateMouseInput()
{
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if (this->mouseMove)
	{
		this->previousMouseX = this->mouseX;
		this->previousMouseY = this->mouseY;
		this->mouseMove = false;
	}
	//calculate offset
	this->mouseOffsetX = this->mouseX - this->previousMouseX;
	this->mouseOffsetY = this->previousMouseY - this->mouseY;

	//set the x to x and set y to y
	this->previousMouseX = this->mouseX;
	this->previousMouseY = this->mouseY;
}

void Game::updateKeyboard()
{
	//close window
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);
	}

	//camera values
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->camera.move(this->deltaTime, FORWARDS);
	}

	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->camera.move(this->deltaTime, BACKWARDS);
	}

	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->camera.move(this->deltaTime, LEFT);
	}

	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->camera.move(this->deltaTime, RIGHT);
	}

	//UP AND DOWN
	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		this->camera.move(this->deltaTime, UP);
	}

	if (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		this->camera.move(this->deltaTime, DOWN);
	}
}


void Game::updateInput()
{
	glfwPollEvents();
	this->updateKeyboard();
	this->updateMouseInput();
	this->camera.updateInput(deltaTime, -1, this->mouseOffsetX, this->mouseOffsetY);
}

void Game::update()
{
	this->updateDeltaTime();
	this->updateInput();
	*this->lights[0] = this->camera.getPosition();
}

void Game::render()
{
	//clear display
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//update uniforms
	this->updateUniforms();

	//render
	for (auto& i : this->models)
	{
		i->render(this->shaders[SHADER_CORE_PROGRAM]);
	}

	//end draws
	glfwSwapBuffers(window);
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::framebuffer_resize_callbacks(GLFWwindow* window, int fbw, int fbh)
{
	glViewport(0, 0, fbw, fbh);
}






