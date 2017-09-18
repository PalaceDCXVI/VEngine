#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable



layout (location = 0) in vec3 inNormal;
layout (location = 1) in vec2 inUV;

layout (location = 0) out vec4 outColor;

layout (set = 1, binding = 0) uniform sampler2D albedo; 
layout (set = 1, binding = 1) uniform Matrix_ModelView 
{
    mat4 data;
} mv_matrix;

void main() 
{
    vec3 normal = vec4(inNormal, 0.0).xyz;
    //outColor = vec4(normal, 1.0);
    outColor = texture(albedo, inUV);
}