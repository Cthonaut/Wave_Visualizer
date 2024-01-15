#include <iostream>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stb/stb_image.h>

#include <math.h>
#include <vector>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "ShaderClass.h"
#include "InputHandeler.h"
#include "ImguiHandeler.h"
#include "Mesh.h"

int resolution[2]{1920,1080};
uint frame_rate{120};
float fov{60};
float near_plane{0.25f};
float far_plane{500.0f};
float axis_width{0.1f};

Vertex axis_x_v[] =
{
	// Front face
	Vertex{glm::vec3( 20.0f, axis_width,-axis_width), glm::vec3(1.0f, 0, 0)},
	Vertex{glm::vec3(-20.0f, axis_width,-axis_width), glm::vec3(0.5f, 0, 0)},
	Vertex{glm::vec3(-20.0f,-axis_width,-axis_width), glm::vec3(0.5f, 0, 0)},
	Vertex{glm::vec3( 20.0f,-axis_width,-axis_width), glm::vec3(1.0f, 0, 0)},

    // Front face
    Vertex{glm::vec3( 20.0f, axis_width, axis_width), glm::vec3(1.0f, 0, 0)},
	Vertex{glm::vec3(-20.0f, axis_width, axis_width), glm::vec3(0.5f, 0, 0)},
	Vertex{glm::vec3(-20.0f,-axis_width, axis_width), glm::vec3(0.5f, 0, 0)},
	Vertex{glm::vec3( 20.0f,-axis_width, axis_width), glm::vec3(1.0f, 0, 0)},
};

Vertex axis_y_v[] =
{
	// Front face
	Vertex{glm::vec3( axis_width, 20.0f,-axis_width), glm::vec3(0, 0, 1.0f)},
	Vertex{glm::vec3(-axis_width, 20.0f,-axis_width), glm::vec3(0, 0, 1.0f)},
	Vertex{glm::vec3(-axis_width,-20.0f,-axis_width), glm::vec3(0, 0, 0.5f)},
	Vertex{glm::vec3( axis_width,-20.0f,-axis_width), glm::vec3(0, 0, 0.5f)},

    // Front face
    Vertex{glm::vec3( axis_width, 20.0f, axis_width), glm::vec3(0, 0, 1.0f)},
	Vertex{glm::vec3(-axis_width, 20.0f, axis_width), glm::vec3(0, 0, 1.0f)},
	Vertex{glm::vec3(-axis_width,-20.0f, axis_width), glm::vec3(0, 0, 0.5f)},
	Vertex{glm::vec3( axis_width,-20.0f, axis_width), glm::vec3(0, 0, 0.5f)},
};

Vertex axis_z_v[] =
{
	// Front face
	Vertex{glm::vec3( axis_width, axis_width,-20.0f), glm::vec3(0, 0.5f, 0)},
	Vertex{glm::vec3(-axis_width, axis_width,-20.0f), glm::vec3(0, 0.5f, 0)},
	Vertex{glm::vec3(-axis_width,-axis_width,-20.0f), glm::vec3(0, 0.5f, 0)},
	Vertex{glm::vec3( axis_width,-axis_width,-20.0f), glm::vec3(0, 0.5f, 0)},

    // Front face
    Vertex{glm::vec3( axis_width, axis_width, 20.0f), glm::vec3(0, 1.0f, 0)},
	Vertex{glm::vec3(-axis_width, axis_width, 20.0f), glm::vec3(0, 1.0f, 0)},
	Vertex{glm::vec3(-axis_width,-axis_width, 20.0f), glm::vec3(0, 1.0f, 0)},
	Vertex{glm::vec3( axis_width,-axis_width, 20.0f), glm::vec3(0, 1.0f, 0)},
};

GLuint axis_i[] =
{
	// Front face
    0, 1, 2,
    0, 2, 3,

    // Back face
    4, 5, 6,
    4, 6, 7,

    // Top face
    0, 1, 5,
    0, 5, 4,

    // Bottom face
    2, 3, 7,
    2, 7, 6,

    // Left face
    0, 3, 7,
    0, 7, 4,

    // Right face
    1, 2, 6,
    1, 6, 5,
};

Vertex vertices[] =
{
	// Front face
	Vertex{glm::vec3( 1.0f, 1.0f,-1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f, 1.0f,-1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f,-1.0f,-1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},

    // Front face
    Vertex{glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f,-1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f,-1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
};

GLuint indices[] =
{
	// Front face
    0, 1, 2,
    0, 2, 3,

    // Back face
    4, 5, 6,
    4, 6, 7,

    // Top face
    0, 1, 5,
    0, 5, 4,

    // Bottom face
    2, 3, 7,
    2, 7, 6,

    // Left face
    0, 3, 7,
    0, 7, 4,

    // Right face
    1, 2, 6,
    1, 6, 5,
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	glfwInit();// Initialize GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(resolution[0], resolution[1], "Sonar_Sim", NULL, NULL);
	if (window == NULL)// Error check
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);// Introduce the window into the current context

	//Load GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	glViewport(0, 0, resolution[0], resolution[1]);// Specify the viewport
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//shader
	Shader shaderProgram("default.vert", "default.frag");
	Shader inshaderProgram("indefault.vert", "default.frag");

	std::vector<Vertex> axis_x_verts(axis_x_v, axis_x_v + sizeof(axis_x_v) / sizeof(Vertex));
	std::vector<Vertex> axis_y_verts(axis_y_v, axis_y_v + sizeof(axis_y_v) / sizeof(Vertex));
	std::vector<Vertex> axis_z_verts(axis_z_v, axis_z_v + sizeof(axis_z_v) / sizeof(Vertex));
	std::vector <GLuint> axis_ind(axis_i, axis_i + sizeof(axis_i) / sizeof(GLuint));
	Mesh axis_x(axis_x_verts, axis_ind);
	Mesh axis_y(axis_y_verts, axis_ind);
	Mesh axis_z(axis_z_verts, axis_ind);

	std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	Mesh cubes(verts, ind, 1000);
	cubes.wave = true;
	Mesh sources(verts, ind, 3);
	sources.info[0].pos.x = -2;
	sources.info[2].pos.x = 2;
	std::vector<float> dp;
	dp.push_back(0.1);
	dp.push_back(0.1);
	dp.push_back(0.1);
	std::vector<float> hz;
	hz.push_back(1);
	hz.push_back(1);
	hz.push_back(1);

	//uniforms
	GLuint matUniform = glGetUniformLocation(shaderProgram.ID, "presp_mat");
	GLuint inmatUniform = glGetUniformLocation(inshaderProgram.ID, "presp_mat");
	GLuint szUniform = glGetUniformLocation(inshaderProgram.ID, "size");
	GLuint cl1Uniform = glGetUniformLocation(inshaderProgram.ID, "color1");
	GLuint cl2Uniform = glGetUniformLocation(inshaderProgram.ID, "color2");
	GLuint slUniform = glGetUniformLocation(inshaderProgram.ID, "selected");

	InputHandeler Input(window);

	glEnable(GL_DEPTH_TEST);

	//main loop variables
	double delta_time;
	bool vs{false};
	float size {5};
	float color1[3] = {0,0,0};
	float color2[3] = {1,1,1};
	int sources_number = {3};
	int selected_source = {0};
	int particle_number = {1000};
	float density {10};
	bool ingore_axis[3] {1,1,1};
	bool old_ingore_axis[3] {1,1,1};
	void* ui_pointers[] {&vs,&size,&color1,&color2,&sources_number,&selected_source,&density,&particle_number,&sources.info[0].pos.x,&sources.info[0].size,&dp[0],&hz[0],&ingore_axis[0],&ingore_axis[1],&ingore_axis[2]};
	float old_density = {0};

	//imgui setup
	Imgui_manager ui(window);

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		double time = glfwGetTime();

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Prespective Math
		glm::mat4 presp_mat = glm::mat4(1.0f);
		presp_mat = glm::translate(presp_mat,glm::vec3(-Input.pos[0],-Input.pos[1],-Input.pos[2]));
		presp_mat = glm::scale(presp_mat, glm::vec3(1,1,1));
		presp_mat = glm::rotate(glm::mat4(1.0f), glm::radians(Input.theta), glm::vec3(0, 1, 0)) * presp_mat;
		presp_mat = glm::rotate(glm::mat4(1.0f), glm::radians(Input.thita), glm::vec3(1, 0, 0)) * presp_mat;
		presp_mat = glm::perspective(glm::radians(fov), (float)((resolution[0] / (float)resolution[1])), near_plane, far_plane) * presp_mat;
		
		shaderProgram.Activate();
		glUniformMatrix4fv(matUniform, 1, GL_FALSE, glm::value_ptr(presp_mat));
		axis_x.Draw(shaderProgram);
		axis_y.Draw(shaderProgram);
		axis_z.Draw(shaderProgram);

		if(sources_number > sources.info.size())
		{
			Object_Info temp;
			temp.size = 0.25f;
			sources.info.push_back(temp);
			dp.push_back(0);
			hz.push_back(0);
		}
		if(sources_number < sources.info.size())
		{
			if(selected_source > sources_number)
			{
				selected_source = sources_number;
			}
			sources.info.pop_back();
			dp.pop_back();
			hz.pop_back();
		}

		while(particle_number > cubes.info.size())
		{
			Object_Info temp;
			cubes.info.push_back(temp);
			old_density = 0;
		}
		while(particle_number < cubes.info.size())
		{
			cubes.info.pop_back();
			old_density = 0;
		}

		inshaderProgram.Activate();
		glUniformMatrix4fv(inmatUniform, 1, GL_FALSE, glm::value_ptr(presp_mat));
		glUniform3f(cl1Uniform, color1[0], color1[1], color1[2]);
		glUniform3f(cl2Uniform, color2[0], color2[1], color2[2]);
		glUniform1f(szUniform,size);
		glUniform1i(slUniform,selected_source);
		sources.Draw(inshaderProgram);
		for(int i{0}; i < particle_number; i++)
		{
			for(int j{0}; j < sources.info.size(); j++)
			{
				float dinstance = glm::length(cubes.info[i].pos - sources.info[j].pos);
				float wave = dp[j]*(sin(hz[j]*glfwGetTime() - dinstance) + 1);
				cubes.info[i].size += wave;
			}
			cubes.info[i].size = size*(cubes.info[i].size)/50;
		}
		if(density != old_density || ingore_axis[0] != old_ingore_axis[0] || ingore_axis[1] != old_ingore_axis[1] || ingore_axis[2] != old_ingore_axis[2])
		{
			for(int i{0}; i < particle_number; i++)
			{
				cubes.info[i].pos.x = ingore_axis[0]*((rand() % particle_number)-particle_number/2.0f)*density/1000;
				cubes.info[i].pos.y = ingore_axis[1]*((rand() % particle_number)-particle_number/2.0f)*density/1000;
				cubes.info[i].pos.z = ingore_axis[2]*((rand() % particle_number)-particle_number/2.0f)*density/1000;
			}
		}
		cubes.Draw(inshaderProgram);

		glfwGetFramebufferSize(window, &resolution[0], &resolution[1]);

		//imgui main
		old_density = density;
		for(int i{0}; i < 3; i++)
		{
			old_ingore_axis[i] = ingore_axis[i];
		}
		ui_pointers[8] = &sources.info[selected_source - 1].pos.x;
		ui_pointers[9] = &sources.info[selected_source - 1].size;
		ui_pointers[10] = &dp[selected_source - 1];
		ui_pointers[11] = &hz[selected_source - 1];
		ui.main(1/delta_time,ui_pointers);

		delta_time = glfwGetTime() - time;
		if(!vs){while(1/delta_time > frame_rate){delta_time = glfwGetTime() - time;}}

		//Input Handeling
		Input.InputHaldeling(delta_time, resolution[0], resolution[1]);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// closing statements
	ui.exit();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
