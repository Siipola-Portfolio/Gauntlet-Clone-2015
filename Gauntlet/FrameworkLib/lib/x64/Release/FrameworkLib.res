        ��  ��                  �   ,   S H A D E R   ��i       0 	        #version 330

// very simple pixel shader that just samples a texture

in vec2 vUV;
in vec4 vColor;
out vec4 outColour;

uniform sampler2D diffuseTexture;

void main()
{
    outColour = texture2D(diffuseTexture, vUV) * vColor;
}
   ,   S H A D E R   ��j       0 	        #version 330

// very simple vertex shader that just transforms an object-space
// position into clip space and passes along a texture coordinate

in vec4 Position;
in vec4 Color;
in vec2 UV;

out vec2 vUV;
out vec4 vColor;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform vec4 tintColor;
uniform vec2 uvScale;
uniform vec2 uvOffset;

void main()
{
	vUV = UV * uvScale + uvOffset;
	vColor = Color * tintColor;
	gl_Position = Projection * View * Model * Position;
}
  5  ,   S H A D E R   ��       0 	        #version 330

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
}   s  ,   S H A D E R   ��n       0 	        #version 330

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
} 