#version 330 core

in VS_OUT
{
    smooth vec3 position;
    smooth vec3 normal;
    smooth vec2 tex_coord;
} fs_in;

uniform struct Material
{
    bool has_ambient_map;
    bool has_diffuse_map;
    bool has_specular_map;
    vec3 ambient_color;
    vec3 diffuse_color;
    vec3 specular_color;
    float shininess;
    sampler2D ambient_map;
    sampler2D diffuse_map;
    sampler2D specular_map;
} material;

out vec4 frag_out;

void main()
{
    frag_out = vec4(material.diffuse_color, 1);
    if (material.has_diffuse_map) {
        frag_out = texture(material.diffuse_map, fs_in.tex_coord);
    }
    frag_out = vec4(0.5 * fs_in.normal + 0.5, 1);
}
