#version 420

layout(std140, binding = 0) uniform Matricies
{
    mat4 viewProjection;
    vec3 viewPos;
};

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 lightPos;
uniform sampler2D tex;

void main()
{
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    float spec = pow(max(dot(-normal, halfwayDir), 0.0), 32.0);

    // combine results
    vec3 ambient = vec3(0.1) * texture(tex, TexCoords).rgb;
    vec3 diffuse = vec3(0.3) * diff * texture(tex, TexCoords).rgb;
    vec3 specular = vec3(0.5) * spec;
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}