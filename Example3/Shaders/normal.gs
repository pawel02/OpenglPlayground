#version 420
layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 Normal;
} gs_in[];

uniform mat4 projection;
const float MAGNITUDE = 0.2;

void GenerateLine(int index)
{
    gl_Position = projection * gl_in[index].gl_Position;
    EmitVertex();

    gl_Position = projection * (gl_in[index].gl_Position + vec4(gs_in[index].Normal, 0.0) * MAGNITUDE);
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GenerateLine(0);
    GenerateLine(1);
    GenerateLine(2);
}