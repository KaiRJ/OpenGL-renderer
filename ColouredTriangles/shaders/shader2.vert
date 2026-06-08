#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_colour;

out vec3 v_colour;

uniform float u_time_s;

void main()
{
    gl_Position = vec4(a_pos, 1.0);
    gl_Position.y += sin(u_time_s);

    v_colour = a_colour;
};
