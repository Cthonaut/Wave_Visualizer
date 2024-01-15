#ifndef VBO_H_
#define VBO_H_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
};

class VBO
{
	GLuint ID;
	public:

		VBO(std::vector<Vertex>& vertices);
		VBO(std::vector<glm::mat4>& mat4s);

		void Bind();
		void Unbind();
		void Delete();
};

#endif

