const char* SimpleVertexShader = STRINGIFY(

attribute vec4 XYZW;
attribute vec4 RGBA;
varying vec4 Color;
uniform mat4 Projection;
uniform mat4 Modelview;

void main(void)
{
    Color = RGBA;
    gl_Position = Projection * Modelview * XYZW;
}
);
