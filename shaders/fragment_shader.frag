#version 450

in vec3 vertex_color;

out vec4 FragColor;

void main()
{
    FragColor = vec4(vertex_color, 1);
}