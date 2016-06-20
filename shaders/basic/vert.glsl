#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 tex_coord;

uniform mat4 world_view;
uniform mat4 inverse_transpose_world_view;
uniform mat4 world_view_projection;

out VS_OUT
{
    smooth vec3 position;
    smooth vec3 normal;
    smooth vec2 tex_coord;
} vs_out;

void main()
{
    gl_Position = world_view_projection * vec4(position, 1);
    vs_out.position = (world_view * vec4(position, 1)).xyz;
    vs_out.normal = (inverse_transpose_world_view * vec4(normal, 0)).xyz;
    vs_out.tex_coord = tex_coord;
}
