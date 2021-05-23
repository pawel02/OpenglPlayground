#version 420
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform sampler2D tex;

void main()
{
    FragColor = texture(tex, TexCoords);
}