//  Set the fragment color

uniform sampler2D tex;

void main()
{
   //Making Stripes
   float s = sin(gl_TexCoord[0].s*45.0);
   float t = sin(gl_TexCoord[0].t*45.0);
   gl_FragColor = gl_Color * vec4(s,t,1.0,1.0);
   //gl_FragColor = gl_Color * texture2D(tex,gl_TexCoord[0].xy);
}
