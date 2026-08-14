#version 330 core

out vec4 o_colour;

in vec3 v_position;
in vec3 v_colour;

void main()
{
    o_colour = vec4(v_colour + v_position, 1.0f);
}
