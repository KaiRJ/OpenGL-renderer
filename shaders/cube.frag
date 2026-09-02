#version 330 core

out vec4 o_colour;

in vec2 o_texture_coord;

uniform sampler2D u_texture0;
uniform sampler2D u_texture1;

void main()
{
    o_colour =
        mix(texture(u_texture0, o_texture_coord),
            texture(u_texture1, vec2(1.0 - o_texture_coord.x, o_texture_coord.y)), 0.2);
};
