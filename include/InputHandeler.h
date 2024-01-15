#ifndef __InputHandeler_H_
#define __InputHandeler_H_

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui_impl_glfw.h>

class InputHandeler
{
	public:
		GLFWwindow* window;
		float res[2];
		float pos[3]{0,0,0};
		double mouse_pos[2];
		float theta{0};
		float thita{0};
		float sens{2};
		float speed{1.5};
		float deltatime;
		InputHandeler(GLFWwindow* win);
		void InputHaldeling(double dt, float width, float height);

	private:
		double pre_mouse_pos[2];
		bool mouse_pr{false};

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		void processInput_general(GLFWwindow* window);
		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		void cursor_enter_callback(GLFWwindow* window, int entered);
		
};

#endif