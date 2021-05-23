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

void main()
{
    Normal = gs_in[0].Normal;
    FragPos = gs_in[0].FragPos;
    TexCoords = gs_in[0].TexCoords;

    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    Normal = gs_in[1].Normal;
    FragPos = gs_in[1].FragPos;
    TexCoords = gs_in[1].TexCoords;
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    Normal = gs_in[2].Normal;
    FragPos = gs_in[2].FragPos;
    TexCoords = gs_in[2].TexCoords;
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();
}