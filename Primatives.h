#pragma once

#include <glew.h>
#include <glfw3.h>

#include <vector>
#include "Vertex.h"


class Primitive
{

private:

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;


public:

	Primitive()
	{

	}

	virtual ~Primitive()
	{

	}

	//functions

	void set(const Vertex* vertices, const unsigned numberOfVertices, const GLuint* indices, const unsigned numberOfIndices)
	{
		for (size_t i = 0; i < numberOfVertices; i++)
		{
			this->vertices.push_back(vertices[i]);
		}

		for (size_t i = 0; i < numberOfIndices; i++)
		{
			this->indices.push_back(indices[i]);
		}


	}

	inline Vertex* getVerticces() { return this->vertices.data(); }
	inline GLuint* getIndices() { return this->indices.data(); }

	inline const unsigned getNumberOfVertices() { return this->vertices.size(); }
	inline const unsigned getNumberOfIndices() { return this->indices.size(); }
};

