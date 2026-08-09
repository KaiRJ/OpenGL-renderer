#version 330 core

out vec4 o_colour;

in vec2 o_tex_coord;

uniform float u_time_s;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

void main()
{
    vec4 mix_colour = vec4(0.0, 1.0, 0.0, 1.0);
    mix_colour.g = (sin(u_time_s) / 2.0f) + 0.5f;

    o_colour = mix(texture(u_texture1, o_tex_coord),
                   texture(u_texture2, vec2(1.0 - o_tex_coord.x, o_tex_coord.y)), 0.2) * mix_colour;
};
