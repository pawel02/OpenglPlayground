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
} vs_out;

uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = view * model * vec4(aPos, 1.0);

    //need to transform the normal into view space
    mat3 normalMatrix = mat3(transpose(inverse(view * model)));
    vs_out.Normal = normalize(vec3(vec4(normalMatrix * aNormal, 0.0)));
}