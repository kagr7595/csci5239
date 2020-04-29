#version 400 core
layout(triangles) in;  // 3 vertices input (triangle input)
layout(triangle_strip, max_vertices=100) out; //(outputting a triangle)

in vec3 FrontColor[];
in vec3 FrontColorSpecial[];
in vec3 TextureCoord2d[];
in vec3 vNormal[];

//  Output to next shader
out vec3 FrontColorFrag;
out vec3 TextureCoord2dFrag;
out vec2 Special;

uniform float time;
uniform int special;

void main()
{

    Special = vec2(0,0);
    for(int i=0; i<3; i++)
    {
      FrontColorFrag = FrontColor[i];
      TextureCoord2dFrag = TextureCoord2d[i];
      gl_Position = gl_in[i].gl_Position;
      EmitVertex();
    }
    EndPrimitive();


    if(special == 1) {
        Special = vec2(1,0);
        FrontColorFrag = FrontColorSpecial[0];
        vec4 v3 = gl_in[0].gl_Position+sin(time)/100.0; // always same vector

        float u = 0.0;      //u  --- this will change by 1/30.0 each loop
        for(int i = 0; i<= 30; i++)
        {
            float u2 = u*u;     //u^2
            float u3 = u2*u;    //u^3
            float u1 = 1.0-u;   //1-u
            float u12 = u1*u1;  //(1-u)^2
            float u13 = u12*u1; //(1-u)^3
            gl_Position = u13*gl_in[0].gl_Position + vec4(vNormal[0]/2.0,0.0);
            gl_Position += 3*u*u12*(gl_in[1].gl_Position + vec4(vNormal[1]/2.0,0.0));
            gl_Position += 3*u2*u1*gl_in[2].gl_Position + vec4(vNormal[2]/2.0,0.0);
            gl_Position += u3*v3;
            EmitVertex();
            u += 1/30.0;
        }
    }

    EndPrimitive();

}
