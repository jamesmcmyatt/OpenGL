#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include"Vertex.h"


static std::vector<Vertex> loadOBJ(const char*file_name)
{
	//vertex portions
	std::vector<glm::fvec3> vertex_position;
	std::vector<glm::fvec3> vertex_normal;
	std::vector<glm::fvec2> vertex_texcoord;

	//face vectors
	std::vector<GLint> vertex_position_indices;
	std::vector<GLint> vertex_normal_indices;
	std::vector<GLint> vertex_texcoord_indices;

	//vertex array
	std::vector<Vertex> vertices;

	std::stringstream ss;
	std::ifstream in_file(file_name);
	std::string line = "";
	std::string prefix = "";
	glm::vec3 temp_vec3;
	glm::vec2 temp_vec2;
	GLint temp_glint = 0;

	//file error
	if(!in_file.is_open())
	{
		throw "ERROR:: OBJ LOADER::COULDNT OPEN FILE";
	}

	//read one line per loop
	while(std::getline(in_file,line))
	{
		//get prefix of line e.g. v, f
		ss.clear();
		ss.str(line);
		ss >> prefix;

		//ignore is it is a hashtag
		if(prefix == "#")
		{
			
		}
		else if(prefix == "o")
		{
			
		}
		else if (prefix == "s")
		{
		
		}
		else if (prefix == "use_mtl")
		{
			//LATER IMPLEMENTATION
		}
		//vertex position
		else if (prefix == "v") 
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_position.push_back(temp_vec3);
		}
		else if(prefix == "vt")
		{
			ss >> temp_vec2.x >> temp_vec2.y;
			vertex_texcoord.push_back(temp_vec2);
		}
		else if (prefix == "vn")
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_normal.push_back(temp_vec3);
		}
		else if( prefix  == "f")
		{
			int counter = 0;
			
			while(ss>>temp_glint)
			{
				//pushing indices int array
				if (counter == 0)
				{
					vertex_position_indices.push_back(temp_glint);
				}
				else if (counter == 1)
				{
					vertex_texcoord_indices.push_back(temp_glint);
				}
				else if (counter == 2)
				{
					vertex_normal_indices.push_back(temp_glint);
				}
				//handling characters
				if(ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					counter++;
					ss.ignore(1, ' ');
				}
				//reset counter
				if (counter> 2)
				{
					counter = 0;
				}
				
			}
		}
		else
		{
			
		}
		
	}
	//build final vertex array(mesh)
	vertices.resize(vertex_position_indices.size(), Vertex());

	//load in all indices
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		vertices[i].position = vertex_position[vertex_position_indices[i] - 1];
		vertices[i].texCoord = vertex_texcoord[vertex_texcoord_indices[i] - 1];
		vertices[i].normal = vertex_normal[vertex_normal_indices[i] - 1];
		vertices[i].color = glm::vec3(1.f, 1.f, 1.f);
	}
	//loaded
	std::cout << "obj loaded\n";
	return vertices;
}

