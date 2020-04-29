#version 400 core
layout(triangles) in;  // 3 vertices input (triangle input)
layout(triangle_strip, max_vertices=500) out; //(outputting a triangle)

in vec3 FrontColor[];
in vec3 vNormal[];
in vec3 TextureCoord2d[];

//  Output to next shader
out vec3 FrontColorFrag;
out vec3 TextureCoord2dFrag;
void main()
{
  FrontColorFrag = FrontColor[0];
  for(int i=0; i<3; i++)
  {
    FrontColorFrag = FrontColor[i];
    TextureCoord2dFrag = TextureCoord2d[i];
    gl_Position = gl_in[i].gl_Position;
    EmitVertex();
    //gl_Position = gl_in[i].gl_Position - vec4(vNormal[0]/2.0,0.0);
    //EmitVertex();
    //gl_Position = gl_in[i].gl_Position + vec4(vNormal[0]/2.0,0.0);
    //EmitVertex();
    //EndPrimitive();
  }
  EndPrimitive();

  FrontColorFrag = FrontColor[0];
  for(int i=0; i<4; i++)
  {
    TextureCoord2dFrag = TextureCoord2d[i];

    vec4 dpos = vec4((gl_in[i%3].gl_Position.xyz + gl_in[(i+1)%3].gl_Position.xyz)/16,gl_in[i%3].gl_Position.w);
    vec4 dpos3 = vec4((gl_in[i%3].gl_Position.xyz + gl_in[(i+1)%3].gl_Position.xyz + gl_in[(i+2)%3].gl_Position.xyz)/16,gl_in[i%3].gl_Position.w);
    for(int j = 0; j< 7; j++)
    {
      vec4 pos0 = vec4(gl_in[i%3].gl_Position.xyz + 2*j*dpos.xyz,     gl_in[i%3].gl_Position.w);
      vec4 pos1 = vec4(gl_in[i%3].gl_Position.xyz + 2*(j+1)*dpos.xyz, gl_in[i%3].gl_Position.w);
      vec4 pos0h = vec4(gl_in[i%3].gl_Position.xyz + 2*j*dpos.xyz,     gl_in[i%3].gl_Position.w)+ vec4(vNormal[0]*((2*j+i)%3+1.0),0.0);
      vec4 pos1h = vec4(gl_in[i%3].gl_Position.xyz + 2*(j+1)*dpos.xyz, gl_in[i%3].gl_Position.w)+ vec4(vNormal[0]*((j+i)%3+1.0),0.0);
      FrontColorFrag = FrontColor[i]*vec3(.4,.5+(j%3)/8.0,.2);
      gl_Position = pos0;
      EmitVertex();
      gl_Position = pos0h;
      EmitVertex();
      gl_Position = pos1;
      EmitVertex();
      //gl_Position = pos1h;
      //EmitVertex();
      EndPrimitive();

      /*vec4 pos30 = vec4(gl_in[(i+1)%3].gl_Position.xyz + 3*j*dpos3.xyz,     gl_in[i%3].gl_Position.w);
      vec4 pos31 = vec4(gl_in[(i+1)%3].gl_Position.xyz + 3*(j+1)*dpos3.xyz, gl_in[i%3].gl_Position.w);
      vec4 pos30h = vec4(gl_in[(i+1)%3].gl_Position.xyz + 3*j*dpos3.xyz,     gl_in[i%3].gl_Position.w)+ vec4(vNormal[0]*((2*j+i)%3+1.0),0.0);
      vec4 pos31h = vec4(gl_in[(i+1)%3].gl_Position.xyz + 3*(j+1)*dpos3.xyz, gl_in[i%3].gl_Position.w)+ vec4(vNormal[0]*((j+i)%3+1.0),0.0);
      FrontColorFrag = FrontColor[i]*vec3(.4,.5+((j+2)%3)/8.0,.2);
      gl_Position = pos30;
      EmitVertex();
      gl_Position = pos30h;
      EmitVertex();
      gl_Position = pos31;
      EmitVertex();
      gl_Position = pos31h;
      EmitVertex();
      EndPrimitive();
*/

    }
    //gl_Position = gl_in[i%3].gl_Position;
    //EmitVertex();
    //gl_Position = gl_in[i%3].gl_Position+ vec4(vNormal[0]/2.0,0.0);
    //EmitVertex();
    //gl_Position = gl_in[i%3].gl_Position;
    //EmitVertex();
    //EndPrimitive();
    //gl_Position = gl_in[i%3].gl_Position + vec4(vNormal[0]/2.0,0.0);
    //EmitVertex();
    //gl_Position = gl_in[(i+1)%3].gl_Position;
    //EmitVertex();
    //EndPrimitive();
  }

}
