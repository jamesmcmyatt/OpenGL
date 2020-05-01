#pragma once
#include <iostream>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>


enum direction {FORWARDS = 0, BACKWARDS, LEFT, RIGHT, UP, DOWN};

class Camera
{

private:

	GLfloat movementSpeed;
	GLfloat sensitivity;

	glm::mat4 ViewMatrix;

	glm::vec3 cameraUp;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	//aditional openGL research
	//learn opengl.comn

	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;
	
	void updateCamVectors()
	{
		this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		this->front.y = sin(glm::radians(this->pitch));
		this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

		this->front = glm::normalize(this->front);
		this->right = glm::normalize(glm::cross(this->front, this->cameraUp));
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}
public:

	Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 cameraUp)
	{
		this->ViewMatrix = glm::mat4(1.f);

		this->movementSpeed = 10.f;
		this->sensitivity = 5.f;

		this->cameraUp = cameraUp;
		this->position = position;
		this->right = glm::vec3(0.f);
		this->up = cameraUp;

		this->pitch = 0.f;
		this->yaw = -90.f;
		this->roll = 0.f;

		this->updateCamVectors();
	}

	~Camera()
	{
	
	}

	//accessors
	const glm::mat4 getViewMatrix()
	{
		this->updateCamVectors();

		this->ViewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);

		return this->ViewMatrix;
	}

	const glm::vec3 getPosition() const
	{
		return this->position;
	}

	void move(const float& deltaTime, const int direction)
	{
		switch (direction)
		{
		case FORWARDS:
			this->position += this->front * this->movementSpeed * deltaTime;
			break;
		case BACKWARDS:
			this->position -= this->front * this->movementSpeed * deltaTime;
			break;
		case LEFT:
			this->position -= this->right * this->movementSpeed * deltaTime;
			break;
		case RIGHT:
			this->position += this->right * this->movementSpeed * deltaTime;
			break;
		case UP:
			this->position += this->up * this->movementSpeed * deltaTime;
			break;
		case DOWN:
			this->position -= this->up * this->movementSpeed * deltaTime;
			break;
		default:
			break;
			
		}
	}

	void updateMouseInput(const float& deltaTime, const double& offsetX, const double& offsetY)
	{
		//update additional movement
		this->yaw += static_cast<GLfloat>(offsetX) * this->sensitivity* deltaTime;
		this->pitch += static_cast<GLfloat>(offsetY) * this->sensitivity* deltaTime;

		if (this->pitch > 80.f)
		{
			this->pitch = 80.f;
		}
		else if (this->pitch < -80.f)
		{
			this->pitch = -80.f;
		}

		if (this->yaw > 360.f || this->yaw < -360.f)
		{
			this->yaw = 0.f;
		}
	}

	void updateInput(const float& deltaTime, const int direction, const double& offsetX, const double& offsetY)
	{
		this->updateMouseInput(deltaTime, offsetX, offsetY);
	}
};
