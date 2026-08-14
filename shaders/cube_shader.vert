#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texture_coord;

out vec2 o_texture_coord;;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
    o_texture_coord = a_texture_coord;
};
