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
    
    // This is a hack; needs actual light rendering
    vec3 light_pos =  vec3(0., 0., 0.);

    vec3 normal = normalize(fs_in.normal);

    vec3 to_eye = vec3(0., 0., 1.);
    vec3 to_light = normalize(light_pos - fs_in.position);

    float ambient_factor = 1;

    // Added some tooniness
    float diffuse_factor = 0.4 + (0.6 * clamp(dot(normal, to_light), 0, 1));

    vec3 to_reflect = -to_light + 2 * diffuse_factor * normal;

    float specular_factor = pow(clamp(dot(to_reflect, to_eye), 0, 1), material.shininess);

    vec3 ambient = material.ambient_color;
    if (material.has_ambient_map)
        ambient = texture(material.ambient_map, fs_in.tex_coord).xyz;
    vec3 diffuse = material.diffuse_color;
    if (material.has_diffuse_map)
        diffuse = texture(material.diffuse_map, fs_in.tex_coord).xyz;
    vec3 specular = material.specular_color;
    if (material.has_specular_map)
        ambient = texture(material.specular_map, fs_in.tex_coord).xyz;

    frag_out = vec4(
        ambient * ambient_factor + 
        diffuse * diffuse_factor + 
        specular * specular_factor,
        1.);
}
