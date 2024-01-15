#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices,unsigned int instances)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Object_Info obj;
	for(int i{0}; i < instances; i++)
	{
		Mesh::info.push_back(obj);
	}

	MVAO.Bind();
	VBO VBO(vertices);
	EBO EBO(indices);
	
	MVAO.LinkVBO(VBO, 0, 3 , GL_FLOAT, 6 * sizeof(float), (void*)0);
	MVAO.LinkVBO(VBO, 1, 3 , GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	
	MVAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}


void Mesh::Draw(Shader& shader)
{
	shader.Activate();
	MVAO.Bind();

	if (info.size() == 1)
	{
		GLuint modUniform = glGetUniformLocation(shader.ID, "model_mat");
		glm::mat4 model_mat = glm::mat4(1.0f);
		model_mat = glm::translate(model_mat,info[0].pos);
		model_mat = glm::scale(model_mat, info[0].size*glm::vec3(1));
		model_mat = glm::rotate(model_mat, glm::radians(info[0].rotation.x), glm::vec3(0, 1, 0));
		model_mat = glm::rotate(model_mat, glm::radians(info[0].rotation.y), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(modUniform, 1, GL_FALSE, glm::value_ptr(model_mat));

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	else
	{
		std::vector <glm::mat4> instanceMatrix;
		for(int i{0}; i < info.size(); i++)
		{
			glm::mat4 model_mat = glm::mat4(1.0f);
			model_mat = glm::translate(model_mat,info[i].pos);
			model_mat = glm::scale(model_mat, info[i].size*glm::vec3(1));
			model_mat = glm::rotate(model_mat, glm::radians(info[i].rotation.y), glm::vec3(0, 1, 0));
			model_mat = glm::rotate(model_mat, glm::radians(info[i].rotation.x), glm::vec3(1, 0, 0));
			model_mat = glm::rotate(model_mat, glm::radians(info[i].rotation.z), glm::vec3(0, 0, 1));
			instanceMatrix.push_back(model_mat);
		}

		VBO instanceVBO(instanceMatrix);

		instanceVBO.Bind();
		// Can't link to a mat4 so you need to link four vec4s
		MVAO.LinkVBO(instanceVBO, 2, 4, GL_FLOAT, sizeof(glm::mat4), (void*)0);
		MVAO.LinkVBO(instanceVBO, 3, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
		MVAO.LinkVBO(instanceVBO, 4, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		MVAO.LinkVBO(instanceVBO, 5, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
		// Makes it so the transform is only switched when drawing the next instance
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1); 
		glVertexAttribDivisor(5, 1);

		instanceVBO.Unbind();

		GLuint waveUniform = glGetUniformLocation(shader.ID, "wave_particle");
		glUniform1i(waveUniform,wave);


		glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, info.size());
	}
}