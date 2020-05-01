#pragma once
#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "OBJloader.h"

class Model
{
private:
	Material* material;
	Texture* overrideTextureDiffuse;
	Texture* overrideTextureSpecular;
	std::vector<Mesh*> meshes;
	glm::vec3 position;


public:
	Model(glm::vec3 position, Material* material,Texture* overrideTexDif, Texture* overrideTexSpec, std::vector<Mesh*>& meshes)
	{
		this->position = position;
		this->material = material;
		this->overrideTextureDiffuse = overrideTexDif;
		this->overrideTextureSpecular = overrideTexSpec;

		//new c++ for loops...SUPER FAST!!!!!!
		//points to each mesh in the array

		for (auto* i : meshes)
		{
			this->meshes.push_back(new Mesh(*i));
		}

		for (auto& i : this->meshes)
		{
			i->Move(this->position);
			i->setPoint(this->position);
		}
	}

	//obj loader
	Model(glm::vec3 position, Material* material, Texture* overrideTexDif, Texture* overrideTexSpec, const char* obj)
	{
		this->position = position;
		this->material = material;
		this->overrideTextureDiffuse = overrideTexDif;
		this->overrideTextureSpecular = overrideTexSpec;
		std::vector<Vertex> mesh = loadOBJ(obj);

		this->meshes.push_back(new Mesh(mesh.data(), mesh.size(), NULL, 0, glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));

		for (auto& i : this->meshes)
		{
			i->Move(this->position);
			i->setPoint(this->position);
		}

	}

	~Model()
	{
		//pointer reference as we are deleting
		//it gets the pointes address to delete it
		for (auto*& i : this->meshes)
		{
			delete i;
		}
	}

	//functions

	void render(Shader* shader)
	{

		this->material->sendToShader(*shader);

		//use a program
		shader->use();

		// Render
		for (auto& i : this->meshes)
		{

			//activate texture
			this->overrideTextureDiffuse->bind(0);
			this->overrideTextureSpecular->bind(1);
			i->render(shader);
		}
	}

	void rotate(const glm::vec3 rotation)
	{
		for (auto& i : this->meshes)
		{
			i->Rotate(rotation);
		}
	}
};

