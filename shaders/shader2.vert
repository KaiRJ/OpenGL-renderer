#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_colour;

out vec3 v_position;
out vec3 v_colour;

uniform float u_time_s;
uniform float u_x_offset;

void main()
{
    gl_Position = vec4(a_pos.x + u_x_offset, -a_pos.y, a_pos.z, 1.0);
    gl_Position.y += sin(u_time_s);
    v_position = gl_Position.xyz;

    v_colour = a_colour;
};
