#version 420
out vec4 FragColor;

layout(std140, binding=2) uniform Colours
{
    vec4 m_color;
};


void main()
{
    FragColor = m_color;
}