//  Show test image

uniform sampler2D img0;

void main()
{
   gl_FragColor = texture2D(img0,gl_TexCoord[0].st);
}
