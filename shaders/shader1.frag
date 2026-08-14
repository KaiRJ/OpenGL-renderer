#version 330 core

out vec4 o_colour;

in vec2 o_texture_coord;

uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

void main()
{
    o_colour = mix(texture(u_texture1, o_texture_coord),
                   texture(u_texture2, vec2(1.0 - o_texture_coord.x, o_texture_coord.y)), 0.2);
};
