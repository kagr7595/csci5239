//  Basic vertex shader

uniform float time;
varying vec4 color;
varying vec2 tex;

void main()
{
   //  Use color unchanged
   color = gl_Color;
   //  Scroll texture coordinates
   tex  = gl_MultiTexCoord0.xy;
   //  Set vertex coordinates
   vec4 pos = gl_Vertex;
   //  Scale in XY plane
   pos.xy *= 1.0+0.3*cos(4.0*time);
   //  Transform
   gl_Position = gl_ModelViewProjectionMatrix * pos;
}
