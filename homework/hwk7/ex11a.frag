// Embossing
// used http://cs.uns.edu.ar/cg/clasespdf/GraphicShaders.pdf

uniform float dX;
uniform float dY;
uniform float R;
uniform float G;
uniform float B;
uniform int GRAYSCALE;
uniform sampler2D img;

vec4 sample(float dx,float dy)
{
   return texture2D(img,gl_TexCoord[0].st+vec2(dx,dy));
}

void main()
{
    float contrast = 1.5;
    if(gl_TexCoord[0].t < 0.5)
        gl_FragColor = texture2D(img,gl_TexCoord[0].st);
    else {
        if(GRAYSCALE) {
            ivec2 ires = textureSize(img, 0);
            float ResS = float(ires.s);
            float ResT = float(ires.t);
            vec3 c00 = sample(dX,dY).rgb;
            vec3 cp1p1 = sample(dX+1./ResS,dY+1./ResT).rgb;

            vec3 diffs = c00 - cp1p1; //vector difference
            float max = diffs.r;
            if( abs(diffs.g) > abs(max))
                max = diffs.g;
            if( abs(diffs.b) > abs(max))
                max = diffs.b;

            float gray = clamp(max + .5, 0,1);
            vec3 color = vec3(gray, gray, gray);
            gl_FragColor = vec4( color, 1.);
        } else
            gl_FragColor = (sample(dX,dY) - sample(-dX,-dY))*contrast;

    }
}
