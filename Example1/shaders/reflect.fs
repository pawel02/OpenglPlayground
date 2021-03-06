#version 420
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;
in vec3 viewPos;

uniform samplerCube skybox;

void main()
{
    vec3 I = normalize(FragPos - viewPos);
    vec3 R = reflect(I, normalize(Normal));

    FragColor = vec4(texture(skybox, R).rgb, 1.0);
}