//  Show reference image

uniform sampler2D img1;

void main()
{
   gl_FragColor = texture2D(img1,gl_TexCoord[0].st);
}
