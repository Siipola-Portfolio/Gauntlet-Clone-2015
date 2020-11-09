#version 330

layout(location=0) in vec2 in_Position;
layout(location=1) in vec2 in_Size;
layout(location=2) in vec2 in_Origin;
layout(location=3) in vec4 in_Color;
layout(location=4) in vec2 in_MinUV;
layout(location=5) in vec2 in_MaxUV;
layout(location=6) in float in_Rotation;
layout(location=7) in uint in_Alive;

// Output values to the geometry shader.
out Vertex
{
    vec2 position;
    vec2 size;
    vec2 origin;
    vec4 color;
    vec2 minUV;
    vec2 maxUV;
    float rotation;
    uint alive;
} out_Vertex;

void main()
{
    // Pass-Through vertex shader.
    out_Vertex.position = in_Position;
    out_Vertex.size = in_Size;
    out_Vertex.origin = in_Origin;
    out_Vertex.color = in_Color;
    out_Vertex.minUV = in_MinUV;
    out_Vertex.maxUV = in_MaxUV;
    out_Vertex.rotation = in_Rotation;
    out_Vertex.alive = in_Alive;
}