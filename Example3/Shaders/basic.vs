#version 420
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

layout(std140, binding = 0) uniform Matricies
{
    mat4 viewProjection;
    vec3 viewPos;
};

out VS_OUT {
    vec3 Normal;
    vec3 FragPos;
    vec2 TexCoords;
} vs_out;

uniform mat4 model;

void main()
{
    gl_Position = viewProjection * model * vec4(aPos, 1.0);

    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
    vs_out.TexCoords = aTexCoords;
}