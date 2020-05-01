#pragma once

#include "Libraries.h"

class Light
{
protected:

	float intensity;
	glm::vec3 color;

public:
	Light(float intensity, glm::vec3 color)
	{
		this->intensity = intensity;
		this->color = color;
	}

	~Light(){}

	//functions
	virtual void sendToShader(Shader& shader) = 0;
};

class pointLight : public Light
{
protected:
	glm::vec3 position;

public:
	pointLight(glm::vec3 position, float intensity, glm::vec3 color) : Light(intensity, color)
	{
		this->position = position;
	}

	~pointLight(){}

	void sendToShader(Shader& shader)
	{
		shader.setVec3f(this->position, "pointlight.position");
		shader.set1f(this->intensity, "pointlight.intensity");
		shader.setVec3f(this->color, "pointlight.color");
	}
};