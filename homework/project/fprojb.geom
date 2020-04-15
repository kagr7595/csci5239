//idea from http://web.engr.oregonstate.edu/~mjb/cs519/Handouts/geometry_shaders.1pp.pdf

#version 400 core
layout(triangles) in;  // 3 vertices input (triangle input)
layout(triangle_strip, max_vertices=200) out; //(outputting triangles)

in vec3 FrontColor[];

//  Output to next shader
out vec3 FrontColorFrag;

const float smaller = .75;
void main()
{
    vec3 center = (gl_in[0].gl_Position.xyz + gl_in[1].gl_Position.xyz + gl_in[2].gl_Position.xyz)/3.0;

    for(int i=0; i<3; i++)
    {
        FrontColorFrag = FrontColor[i];
        gl_Position = vec4(center + smaller*(gl_in[i].gl_Position.xyz - center),gl_in[i].gl_Position.w);
        EmitVertex();
    }
    EndPrimitive();

}
