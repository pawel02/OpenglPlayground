#version 420
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

layout(std140) uniform Matricies
{
    mat4 viewProjection;
    vec3 aviewPos;
};

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;
out vec3 viewPos;

uniform mat4 model;

void main()
{
    gl_Position = viewProjection * model * vec4(aPos, 1.0);

    Normal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
    TexCoord = aTexCoords;
    viewPos = aviewPos;
}
