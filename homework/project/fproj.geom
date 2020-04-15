#version 400 core
layout(triangles) in;  // 3 vertices input (triangle input)
layout(triangle_strip, max_vertices=3) out; //(outputting a triangle)

in vec3 FrontColor[];
in vec3 TextureCoord2d[];

//  Output to next shader
out vec3 FrontColorFrag;
out vec3 TextureCoord2dFrag;
void main()
{
  for(int i=0; i<3; i++)
  {
    FrontColorFrag = FrontColor[i];
    TextureCoord2dFrag = TextureCoord2d[i];
    gl_Position = gl_in[i].gl_Position;
    EmitVertex();
  }
  EndPrimitive();
}
