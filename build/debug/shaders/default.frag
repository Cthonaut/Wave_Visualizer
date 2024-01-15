#version 460 core
#extension GL_ARB_shading_language_420pack : enable

out vec4 FragColor;
in vec4 vertexColor;

void main()
{
    FragColor = vertexColor;
}