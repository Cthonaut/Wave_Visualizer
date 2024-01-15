#ifndef IMGUIHANDELER_H_
#define IMGUIHANDELER_H_

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

class Imgui_manager
{
	public:
		Imgui_manager(GLFWwindow* win);
		void main(int framerate, void* pointer_array[]);
		void exit();
};

#endif
