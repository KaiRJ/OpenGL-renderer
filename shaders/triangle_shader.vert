#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_colour;

out vec3 v_position;
out vec3 v_colour;

uniform mat4 u_transform;

void main()
{
    gl_Position = u_transform * vec4(a_position, 1.0f);
    v_position = gl_Position.xyz;
    v_colour = a_colour;
};
