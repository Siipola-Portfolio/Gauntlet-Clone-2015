#version 330

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

// Input values from the vertex shader.
in Vertex
{
    vec2 position;
    vec2 size;
    vec2 origin;
    vec4 color;
    vec2 minUV;
    vec2 maxUV;
    float rotation;
    uint alive;
} in_Vertex[];

out vec2 vUV;
out vec4 vColor;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main()
{
    if ( in_Vertex[0].alive != 0u )
    {
        mat4 MVP = Projection * View * Model;

        mat2 rotation = mat2( cos( in_Vertex[0].rotation ), sin( in_Vertex[0].rotation ), // First column
                              -sin( in_Vertex[0].rotation ), cos( in_Vertex[0].rotation ) ); // Second column

        // Compute offsets to corners of sprite.
        vec2 left = rotation * vec2( in_Vertex[0].size.x * in_Vertex[0].origin.x, 0 );
        vec2 right = rotation * vec2( in_Vertex[0].size.x * ( 1 - in_Vertex[0].origin.x ), 0 );
        vec2 top = rotation * vec2( 0, in_Vertex[0].size.y * ( 1 - in_Vertex[0].origin.y ) );
        vec2 bottom = rotation * vec2( 0, in_Vertex[0].size.y * in_Vertex[0].origin.y );

        // Bottom-left vertex
        gl_Position = MVP * vec4( in_Vertex[0].position - bottom - left, 0, 1 );
        vUV = in_Vertex[0].minUV;
        vColor = in_Vertex[0].color;
        EmitVertex();

        // Bottom-right vertex
        gl_Position = MVP * vec4( in_Vertex[0].position - bottom + right, 0, 1 );
        vUV = vec2( in_Vertex[0].maxUV.x, in_Vertex[0].minUV.y );
        vColor = in_Vertex[0].color;
        EmitVertex();
        
        // Top-left vertex
        gl_Position = MVP * vec4( in_Vertex[0].position + top - left, 0, 1 );
        vUV = vec2( in_Vertex[0].minUV.x, in_Vertex[0].maxUV.y );
        vColor = in_Vertex[0].color;
        EmitVertex();
        
        // Top-right vertex
        gl_Position = MVP * vec4( in_Vertex[0].position + top + right, 0, 1 );
        vUV = in_Vertex[0].maxUV;
        vColor = in_Vertex[0].color;
        EmitVertex();
    }
    EndPrimitive();
}