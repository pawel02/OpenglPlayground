#version 420
layout(location = 0) in vec3 aPos;
layout(location = 2) in vec2 aTexCoords;
//this will use location 3,4,5,6 because max size is vec4 and mat4 is 4 vec4s
layout(location = 3) in mat4 instanceMatrix;

layout(std140, binding = 0) uniform Matricies
{
    mat4 viewProjection;
    vec3 viewPos;
};

out vec2 TexCoords;

void main()
{
    gl_Position = viewProjection * instanceMatrix * vec4(aPos, 1.0);
    TexCoords = aTexCoords;
}