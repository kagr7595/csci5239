// Grayscale RGB
// used http://cs.uns.edu.ar/cg/clasespdf/GraphicShaders.pdf

uniform float dX;
uniform float dY;
uniform float R;
uniform float G;
uniform float B;
uniform sampler2D img;

vec4 sample(float dx,float dy)
{
   return texture2D(img,gl_TexCoord[0].st+vec2(dx,dy));
}

void main()
{
   vec3 w = vec3( R, G, B );

   vec3 irgb = texture2D(img,gl_TexCoord[0].st).rgb;
   float luminance = dot( irgb, w);

   gl_FragColor = vec4( luminance, luminance, luminance, 1.);
}
