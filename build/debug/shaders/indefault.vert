#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in mat4 instanceMatrix;

out vec4 vertexColor;

uniform mat4 presp_mat;
uniform mat4 model_mat;
uniform bool wave_particle;
uniform int selected;
uniform float size;
uniform vec3 color1;
uniform vec3 color2;

void main()
{
    gl_Position =  presp_mat * instanceMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    if(wave_particle)
    {
        vertexColor = 10*abs(determinant(instanceMatrix)*125000/(size*size*size))*vec4(color2 ,1.0) + vec4(color1 ,1.0)*(10*(0.1 - determinant(instanceMatrix)*125000/(size*size*size)));
    }
    else
    {
        vertexColor = vec4(aColor ,1.0);
        if((selected-1) == gl_InstanceID)
        {
            vertexColor = vec4(1.0, 0.0, 0.0 ,1.0);
        }
    }
}