#version 330 core

out vec4 o_colour;

uniform float u_time_s;

void main()
{
    o_colour = vec4(0.0, 1.0, 0.0, 1.0);
    o_colour.g = (sin(u_time_s) / 2.0f) + 0.5f;
};
