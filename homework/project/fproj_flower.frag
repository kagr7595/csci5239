#version 400 core

uniform sampler2D tex;

//  Input from previous shader
in vec3 FrontColorFrag;
in vec2 Special;
in vec3 TextureCoord2dFrag;

//  Fragment color
layout (location=0) out vec4 Fragcolor;

void main()
{
    Fragcolor = vec4(FrontColorFrag,1.0);
    if(Special.x != 1)
        Fragcolor *= texture2D(tex,vec2(TextureCoord2dFrag));
}
