#version 400 core
layout(triangles) in;  // 3 vertices input (triangle input)
layout(line_strip, max_vertices=200) out; //(outputting lines)

in vec3 FrontColor[];

//  Output to next shader
out vec3 FrontColorFrag;

//Algorithm -- (1-u)^3*V0 + 3u*(1-u)^2*V1 + 3u^2*(1-u)*V2 + u^3*V3
void main()
{

    FrontColorFrag = FrontColor[0];
    vec4 v3 = vec4(0.0,0.0,0.0,gl_in[0].gl_Position.w); // always same vector

    float u = 0.0;      //u  --- this will change by 1/30.0 each loop
    for(int i = 0; i<= 30; i++)
    {
        float u2 = u*u;     //u^2
        float u3 = u2*u;    //u^3
        float u1 = 1.0-u;   //1-u
        float u12 = u1*u1;  //(1-u)^2
        float u13 = u12*u1; //(1-u)^3
        gl_Position = u13*gl_in[0].gl_Position;
        gl_Position += 3*u*u12*gl_in[1].gl_Position;
        gl_Position += 3*u2*u1*gl_in[2].gl_Position;
        gl_Position += u3*v3;
        EmitVertex();
        u += 1/30.0;
    }

    EndPrimitive();

}
