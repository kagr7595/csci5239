//  Set the fragment color

uniform sampler2D tex;

vec2 func1(vec2 st);

void main()
{
   float s = sin(gl_TexCoord[0].s*45.0);
   float t = sin(gl_TexCoord[0].t*45.0);
   //Making Stripes/Checkers with if statement
   if(s > 0.5) { 
      vec2 st = func1(vec2(s,t));
      s = st.x;
      t = st.y;  
   }
   gl_FragColor = gl_Color * vec4(s,t,1.0,1.0);
}

vec2 func1(vec2 st) {
    return vec2(-st);
}