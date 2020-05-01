#pragma once
#pragma once
#include <iostream>
#include <string>

#include <glew.h>
#include <glfw3.h>

#include <SOIL2.h>



class Texture
{
private:
	GLuint ID;
	int width;
	int height;
	unsigned int type;


public:

	Texture(const char* fileName, GLenum type)
	{


		this->type = type;

		//LOAD IMAGE
		unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

		//GENERATE TEXTURE INTO ID
		glGenTextures(1, &this->ID);
		glBindTexture(type, this->ID);

		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//IF DATA IS IN IMAGE CREATE GL IMAGE & GENERATE MIPMAP
		if (image)
		{
			glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(type);
		}
		else
		{
			std::cout << "ERROR::TEXTURE:: TEXTURE LOADING FAILED" << fileName << "\n";
		}
		glActiveTexture(0);
		glBindTexture(type, 0);
		SOIL_free_image_data(image);
	}

	~Texture()
	{
		glDeleteTextures(1, &this->ID);
	}

	inline GLuint getID() const { return this->ID; }

	//on the fly choosing which texture image to use
	void bind(const GLint texture_unit)
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit);
		glBindTexture(this->type, this->ID);
	}

	void unbind(GLenum type)
	{
		glActiveTexture(0);
		glBindTexture(this->type, 0);
	}


	void loadFromFile(const char* fileName)
	{
		if (this->ID)
		{
			glDeleteTextures(1, &this->ID);
		}
		//LOAD IMAGE
		unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

		//GENERATE TEXTURE INTO ID
		glGenTextures(1, &this->ID);
		glBindTexture(this->type, this->ID);

		glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//IF DATA IS IN IMAGE CREATE GL IMAGE & GENERATE MIPMAP
		if (image)
		{
			glTexImage2D(this->type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(this->type);
		}
		else
		{
			std::cout << "ERROR::TEXTURE::LOAD FROM FILE:: TEXTURE LOADING FAILED" << fileName << "\n";
		}
		glActiveTexture(0);
		glBindTexture(this->type, 0);
		SOIL_free_image_data(image);
	}

};

