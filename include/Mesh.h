#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include"VAO.h"
#include"EBO.h"
#include"ShaderClass.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Object_Info
{
	glm::vec3 pos {glm::vec3(0,0,0)};
	glm::vec3 color {glm::vec3(0,0,0)};
	float size {0.25f};
	glm::vec3 rotation {0};
};

class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	VAO MVAO;
	bool wave{false};
	std::vector<Object_Info> info;

	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices,unsigned int instances = 1);

	void Draw(Shader& shader);
};
#endif