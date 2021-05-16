#version 420
layout(location = 0) in vec3 aPos;

layout(std140, binding=0) uniform Matricies
{
    mat4 viewProjection;
    vec3 viewPos;
};

void main()
{
    gl_Position = viewProjection * vec4(aPos, 1.0);
}