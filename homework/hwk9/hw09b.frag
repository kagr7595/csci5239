// CMYK Grayscale Filter
// used http://cs.uns.edu.ar/cg/clasespdf/GraphicShaders.pdf

uniform float dX;
uniform float dY;
uniform int C;
uniform int M;
uniform int Y;
uniform int K;
uniform sampler2D img;

vec4 sample(float dx,float dy)
{
   return texture2D(img,gl_TexCoord[0].st+vec2(dx,dy));
}

void main()
{
    vec3 cmy = vec3(1,1,1) - texture2D(img,gl_TexCoord[0].st).rgb;
    float k = min( cmy.x, min(cmy.y, cmy.z));
    vec3 temp = (cmy - vec3(k,k,k))/(1.0-k);
    vec4 cmyk = vec4(temp,k);
    if(C)
        gl_FragColor = vec4(cmyk.xxx, 1);
    else if(M)
        gl_FragColor = vec4(cmyk.yyy, 1);
    else if(Y)
        gl_FragColor = vec4(cmyk.zzz, 1);
    else
        gl_FragColor = vec4(cmyk.www, 1);
}
