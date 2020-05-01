#pragma once
#pragma once
#include <iostream>
#include <vector>

#include "Vertex.h"
#include "Primatives.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"

class Mesh
{

private:

	unsigned numberOfVertices;
	unsigned numberOfIndices;
	Vertex * vertexArray;
	GLuint * indexArray;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 point;
	glm::vec3 rotation;
	glm::vec3 scale;
	
	glm::mat4 ModelMatrix;

	void initVAO()
	{
		//create VAO
		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//Generate VBO and bind
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->numberOfVertices * sizeof(Vertex), this->vertexArray, GL_STATIC_DRAW);

		//Generate EBO and bind
		if (this->numberOfIndices > 0)
		{
			glGenBuffers(1, &this->EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->numberOfIndices * sizeof(GLuint), this->indexArray, GL_STATIC_DRAW);
		}

		//Set vertex attribute buffers and enable (input assembly)
		//position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);

		//color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);

		//texcoord
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));
		glEnableVertexAttribArray(2);

		//normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);

		//bind VAO 0
		glBindVertexArray(0);
	}

	void updateUniForms(Shader* shader)
	{
		shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
	}

	void updateModelMatrix()
	{
		this->ModelMatrix = glm::mat4(1.f);
		//put at origin
		this->ModelMatrix = glm::translate(this->ModelMatrix, this->point);
		//rotate
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
		this->ModelMatrix = glm::translate(this->ModelMatrix, this->position - this->point);
		this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
	}

public:

	Mesh(Primitive* primitive, glm::vec3 position = glm::vec3(0.f), glm::vec3 point = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f))
	{
		this->position = position;
		this->point = point;
		this->rotation = rotation;
		this->scale = scale;

		this->numberOfVertices = primitive->getNumberOfVertices();
		this->numberOfIndices = primitive->getNumberOfIndices();

		this->vertexArray = new Vertex[this->numberOfVertices];
		for (int i = 0; i < this->numberOfVertices; i++)
		{
			this->vertexArray[i] = primitive->getVerticces()[i];
		}

		this->indexArray = new GLuint[this->numberOfIndices];
		for (int i = 0; i < numberOfIndices; i++)
		{
			this->indexArray[i] = primitive->getIndices()[i];
		}


		this->initVAO();
		this->updateModelMatrix();
	}

	Mesh(Vertex* vertexArray, const unsigned& numberOfVertices, GLuint* indexArray, const unsigned& numberOfIndices, glm::vec3 position = glm::vec3(0.f), glm::vec3 point = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f))
	{
		this->position = position;
		this->point = point;
		this->rotation = rotation;
		this->scale = scale;

		this->numberOfVertices = numberOfVertices;
		this->numberOfIndices = numberOfIndices;

		this->vertexArray = new Vertex[this->numberOfVertices];
		for (int i = 0; i < numberOfVertices; i++)
		{
			this->vertexArray[i] = vertexArray[i];
		}

		this->indexArray = new GLuint[this->numberOfIndices];
		for (int i = 0; i < numberOfIndices; i++)
		{
			this->indexArray[i] = indexArray[i];
		}

		this->initVAO();
		this->updateModelMatrix();
	}

	Mesh(const Mesh& object)
	{
		this->position = object.position;
		this->point = object.point;
		this->rotation = object.rotation;
		this->scale = object.scale;

		this->numberOfVertices = object.numberOfVertices;
		this->numberOfIndices = object.numberOfIndices;

		this->vertexArray = new Vertex[this->numberOfVertices];
		for (int i = 0; i < this->numberOfVertices; i++)
		{
			this->vertexArray[i] = object.vertexArray[i];
		}

		this->indexArray = new GLuint[this->numberOfIndices];
		for (int i = 0; i < numberOfIndices; i++)
		{
			this->indexArray[i] = object.indexArray[i];
		}


		this->initVAO();
		this->updateModelMatrix();
	}

	~Mesh()
	{
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);

		if (this->numberOfIndices > 0)
		{
			glDeleteBuffers(1, &this->EBO);
		}

		delete[] this->vertexArray;
		delete[] this->indexArray;
	}

	//accessors

	//modifieers
	void setPosition(const glm::vec3 position)
	{
		this->position = position;
	}

	void setPoint(const glm::vec3 point)
	{
		this->point = point;
	}

	void setRotation(const glm::vec3 rotation)
	{
		this->rotation = rotation;
	}

	void setScale(const glm::vec3 scale)
	{
		this->scale = scale;///////////////////////////////////////////////////
	}
	//functions
	void Move(const glm::vec3 position)
	{
		this->position += position;
	}

	void Rotate(const glm::vec3 rotation)
	{
		this->rotation += rotation;
	}

	void Scale(const glm::vec3 scale)
	{
		this->scale += scale;
	}

	void update()
	{

	}

	void render(Shader* shader)
	{
		//update uniforms
		this->updateModelMatrix();
		this->updateUniForms(shader);

		shader->use();

		//bindVAO
		glBindVertexArray(this->VAO);

		//render
		if (this->numberOfIndices == 0)
		{
			glDrawArrays(GL_TRIANGLES, 0, this->numberOfVertices);
		}
		else
		{
			glDrawElements(GL_TRIANGLES, this->numberOfIndices, GL_UNSIGNED_INT, 0);
		}

		//empty
		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);


	}
};

