#ifndef EBO_H_
#define EBO_H_

#include <glad/glad.h>
#include <vector>

class EBO
{
	GLuint ID;
	
public:

	EBO(std::vector<GLuint>& indices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif

