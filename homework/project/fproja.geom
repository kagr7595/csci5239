#version 400 core
layout(triangles) in;  // 3 vertices input (triangle input)
layout(line_strip, max_vertices=6) out; //(outputting lines)

in vec3 FrontColor[];
in vec3 vNormal[];

//  Output to next shader
out vec3 FrontColorFrag;
void main()
{
  FrontColorFrag = FrontColor[0];
  for(int i=0; i<3; i++)
  {
    gl_Position = gl_in[i].gl_Position - vec4(vNormal[0]/2.0,0.0);
    EmitVertex();
    gl_Position = gl_in[i].gl_Position + vec4(vNormal[0]/2.0,0.0);
    EmitVertex();
    EndPrimitive();
  }
}
