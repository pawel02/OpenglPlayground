#version 420
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec3 Normal;
    vec3 FragPos;
    vec2 TexCoords;
} gs_in[];

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform float time;

vec3 GetNormal()
{
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   return normalize(cross(a, b));
}

vec4 explode(vec4 position, vec3 normal)
{
    float magnitude = 2.0;
    vec3 direction = normal * ((sin(time) + 1) / 2) * magnitude;
    return position + vec4(direction, 1.0);
}

void main()
{
    //this normal includes all the tranlations and everything different to the one calculated in the vertex shader
    vec3 normal = GetNormal();

    Normal = gs_in[0].Normal;
    FragPos = gs_in[0].FragPos;
    TexCoords = gs_in[0].TexCoords;

    gl_Position = explode(gl_in[0].gl_Position, normal);
    EmitVertex();

    FragPos = gs_in[1].FragPos;
    TexCoords = gs_in[1].TexCoords;
    gl_Position = explode(gl_in[1].gl_Position, normal);
    EmitVertex();

    FragPos = gs_in[2].FragPos;
    TexCoords = gs_in[2].TexCoords;
    gl_Position = explode(gl_in[2].gl_Position, normal);
    EmitVertex();

    EndPrimitive();
}