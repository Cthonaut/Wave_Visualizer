#include "ImguiHandeler.h"

Imgui_manager::Imgui_manager(GLFWwindow* win)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(win, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	ImGui::StyleColorsDark();

	ImVec4 color = ImVec4(0.2f,0.f,0.35f,1.f);
	float pr_up = 0.5f;
	float pr_down = 0.2f;
	ImVec4 down_color = ImVec4(color.x - pr_down * color.x ,color.y - pr_down * color.y,color.z - pr_down * color.z,1.f);
	ImVec4 up_color = ImVec4(color.x + pr_up * color.x ,color.y + pr_up * color.y,color.z + pr_up * color.z,1.f);
	ImVec4 up_up_color = ImVec4(up_color.x + pr_up * up_color.x ,up_color.y + pr_up * up_color.y,up_color.z + pr_up * up_color.z,1.f);

	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, color);
	ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, down_color);
	ImGui::PushStyleColor(ImGuiCol_TitleBg, down_color);
	ImGui::PushStyleColor(ImGuiCol_FrameBg, color);
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, up_color);
	ImGui::PushStyleColor(ImGuiCol_CheckMark, up_up_color);
	ImGui::PushStyleColor(ImGuiCol_ResizeGrip, color);
	ImGui::PushStyleColor(ImGuiCol_ResizeGripHovered, up_color);
	ImGui::PushStyleColor(ImGuiCol_ResizeGripActive, up_color);
}

void Imgui_manager::main(int framerate, void* pointer_array[])
{
	bool* vs_ptr = static_cast<bool*>(pointer_array[0]);
	float* sz_ptr = static_cast<float*>(pointer_array[1]);
	float* cl1_ptr = static_cast<float*>(pointer_array[2]);
	float* cl2_ptr = static_cast<float*>(pointer_array[3]);
	int* sn_ptr = static_cast<int*>(pointer_array[4]);
	int* ss_ptr = static_cast<int*>(pointer_array[5]);
	float* ds_ptr = static_cast<float*>(pointer_array[6]);
	int* pan_ptr = static_cast<int*>(pointer_array[7]);
	float* pos_selected = static_cast<float*>(pointer_array[8]);
	float* size_selected = static_cast<float*>(pointer_array[9]);
	float* dp_ptr = static_cast<float*>(pointer_array[10]);
	float* hz_ptr = static_cast<float*>(pointer_array[11]);
	bool* ig1 = static_cast<bool*>(pointer_array[12]);
	bool* ig2 = static_cast<bool*>(pointer_array[13]);
	bool* ig3 = static_cast<bool*>(pointer_array[14]);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

    ImGui::Begin("Settings");
	ImGui::Text("Frame rate: %d", framerate);
	ImGui::Checkbox("VSync", vs_ptr);
	if(!(*vs_ptr))
	{
			glfwSwapInterval(0);
	}
	else
	{
		glfwSwapInterval(1);
	}
	ImGui::Text("Sources: %d", *sn_ptr);
	ImGui::SameLine();
    if (ImGui::ArrowButton("Increase", ImGuiDir_Up))
	{
		(*sn_ptr)++;
	}
    ImGui::SameLine();
	if (ImGui::ArrowButton("Decrease", ImGuiDir_Down) && *sn_ptr > 0)
	{
		(*sn_ptr)--;
	}
	
	ImGui::Text("Selected Source: %d", *ss_ptr);
	ImGui::SameLine();
    if (ImGui::ArrowButton("Increas", ImGuiDir_Up) && *ss_ptr < *sn_ptr)
	{
		(*ss_ptr)++;
	}
    ImGui::SameLine();
	if (ImGui::ArrowButton("Decreas", ImGuiDir_Down) && *ss_ptr > 0)
	{
		(*ss_ptr)--;
	}
	if(*ss_ptr != 0)
	{
		ImGui::InputFloat3("Pos", pos_selected);
		ImGui::SliderFloat("Size", size_selected, 0.0f, 2.0f);
		ImGui::SliderFloat("Change in pressure", dp_ptr, 0.0f, 1.0f);
		ImGui::SliderFloat("Frequency", hz_ptr, 0.5f, 2.0f);
	}
	ImGui::End();
	

	ImGui::Begin("Particle settings");
	ImGui::Text("Particles: %d", *pan_ptr);
	ImGui::SameLine();
    if (ImGui::ArrowButton("Increa", ImGuiDir_Up))
	{
		(*pan_ptr) += 100;
	}
    ImGui::SameLine();
	if (ImGui::ArrowButton("Decrea", ImGuiDir_Down) && *pan_ptr > 0)
	{
		(*pan_ptr) -= 100;
	}
	ImGui::SliderFloat("Particle Size", sz_ptr, 0.0f, 10.0f);
	ImGui::SliderFloat("Density", ds_ptr, 0.0f, 10.0f);
	ImGui::Checkbox("X", ig1);
	ImGui::SameLine();
	ImGui::Checkbox("Y", ig2);
	ImGui::SameLine();
	ImGui::Checkbox("Z", ig3);
	ImGui::ColorPicker3("Low Color", cl1_ptr);
	ImGui::ColorPicker3("High Color", cl2_ptr);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void Imgui_manager::exit()
{
    ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
