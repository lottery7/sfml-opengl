#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 in_color;

layout (location = 2) uniform float rotate_x;
layout (location = 3) uniform float rotate_y;
layout (location = 4) uniform float rotate_z;

out vec3 vertex_color;


mat3 rotation_matrix_x(float angle)
{
    return mat3(
    1, 0, 0,
    0, cos(angle), -sin(angle),
    0, sin(angle), cos(angle));
}

mat3 rotation_matrix_y(float angle)
{

    return mat3(
    cos(angle), 0, sin(angle),
    0, 1, 0,
    -sin(angle), 0, cos(angle));
}


mat3 rotation_matrix_z(float angle)
{
    return mat3(
    cos(angle), sin(angle), 0,
    -sin(angle), cos(angle), 0,
    0, 0, 1);
}


void main()
{
    vec3 pos = position;
    pos = rotation_matrix_x(rotate_x) * pos;
    pos = rotation_matrix_y(rotate_y) * pos;
    pos = rotation_matrix_y(rotate_z) * pos;

    gl_Position = vec4(pos, 1.0);
    vertex_color = in_color;
}