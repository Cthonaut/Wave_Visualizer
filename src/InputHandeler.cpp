#include "InputHandeler.h"

InputHandeler::InputHandeler(GLFWwindow* win)
{
	window = win;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void InputHandeler::InputHaldeling(double dt, float width, float height)
{
    deltatime = dt;

	res[0] = width;
	res[1] = height;

	glfwSetWindowUserPointer(window, this);

    glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int mods) {
        InputHandeler* inputHandlerInstance = static_cast<InputHandeler*>(glfwGetWindowUserPointer(win));
        if (inputHandlerInstance != nullptr) {
            inputHandlerInstance->mouse_button_callback(win, button, action, mods);
        }
    });

    glfwSetScrollCallback(window, [](GLFWwindow* win, double xoffset, double yoffset) {
        InputHandeler* inputHandlerInstance = static_cast<InputHandeler*>(glfwGetWindowUserPointer(win));
        if (inputHandlerInstance != nullptr) {
            inputHandlerInstance->scroll_callback(win, xoffset, yoffset);
        }
    });

	glfwSetCursorPosCallback(window, [](GLFWwindow* win, double xpos, double ypos) {
        InputHandeler* inputHandlerInstance = static_cast<InputHandeler*>(glfwGetWindowUserPointer(win));
        if (inputHandlerInstance != nullptr) {
            inputHandlerInstance->cursor_position_callback(win, xpos, ypos);
        }
    });

    glfwSetCursorEnterCallback(window, [](GLFWwindow* win, int entered) {
        InputHandeler* inputHandlerInstance = static_cast<InputHandeler*>(glfwGetWindowUserPointer(win));
        if (inputHandlerInstance != nullptr) {
            inputHandlerInstance->cursor_enter_callback(win, entered);
        }
    });

	processInput_general(window);
}

void InputHandeler::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	mouse_pos[0] = xpos/res[0];
	mouse_pos[1] = ypos/res[1];
}


void InputHandeler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

    ImGui_ImplGlfw_MouseButtonCallback(window,button,action,mods);

    if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        mouse_pr = true;
        pre_mouse_pos[0] = mouse_pos[0];
        pre_mouse_pos[1] = mouse_pos[1];
    }

    if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        mouse_pr = false;
    }
}

void InputHandeler::cursor_enter_callback(GLFWwindow* window, int entered){}

void InputHandeler::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){}

void InputHandeler::processInput_general(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {   
        glm::vec4 looking_vec = {0,0,-speed,0};
        looking_vec = glm::rotate(glm::mat4(1.0f), glm::radians(-theta), glm::vec3(0, 1, 0)) * looking_vec;
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	    {
            pos[0] += looking_vec.x*deltatime;
            pos[1] += looking_vec.y*deltatime;
            pos[2] += looking_vec.z*deltatime;
    	}
        else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	    {
            pos[0] -= looking_vec.x*deltatime;
            pos[1] -= looking_vec.y*deltatime;
            pos[2] -= looking_vec.z*deltatime;
	    }

        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	    {
	    	pos[0] += looking_vec.z*deltatime;
            pos[1] -= looking_vec.y*deltatime;
            pos[2] -= looking_vec.x*deltatime;
	    }
        else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	    {
		    pos[0] -= looking_vec.z*deltatime;
            pos[1] += looking_vec.y*deltatime;
            pos[2] += looking_vec.x*deltatime;
	    }
    }

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        pos[1] += speed*deltatime;
    }
    else if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        pos[1] -= speed*deltatime;
    }

    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        theta = 0;
        thita = 0;
    }

    if(mouse_pr)
    {
        theta += 1000*sens*(mouse_pos[0] - pre_mouse_pos[0])*deltatime;

        if(abs(thita) < 60 || thita/(mouse_pos[1] - pre_mouse_pos[1]) < 0)
        {
            thita += 1000*sens*(mouse_pos[1] - pre_mouse_pos[1])*deltatime;
        }

        pre_mouse_pos[0] = mouse_pos[0];
        pre_mouse_pos[1] = mouse_pos[1];
    }
}
