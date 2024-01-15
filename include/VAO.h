#ifndef VAO_H_
#define VAO_H_

#include <glad/glad.h>

#include "VBO.h"

class VAO
{
	GLuint ID;
	public:

		VAO();

		void LinkVBO(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();
};

#endif

