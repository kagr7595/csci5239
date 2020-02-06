
//  Model coordinates and light from vertex shader
varying float LightIntensity;
varying vec2  ModelPos;
uniform float time;

vec2 func1(vec2 st);
vec2 func2(vec2 st);
vec2 func3(vec2 st);

void main()
{
   //making strobe lighting that can get brighter/darker depending on x/y positions
   float s = cos(time*30.0)*ModelPos.x;
   float t = cos(time*30.0)*ModelPos.y;
   vec2 ret_st;
   if(s > 0.5) { 
      ret_st = func1(vec2(s,t)); 
   } else {
      if(s >0.0) {
         ret_st = func2(vec2(s,t));  
      } else {
         ret_st = func3(vec2(s,t)); 
      }

   }
   s = ret_st.x;
   t = ret_st.y;
   vec3 color  = vec3(s,t,.5);
   //  Modulate for lighting
   color *= LightIntensity;
   //  Pad color with alpha
   gl_FragColor = vec4(color,1.0);
}


vec2 func1(vec2 st) {
    return vec2(-st.x,-st.y);
}
vec2 func2(vec2 st) {
    return vec2(st.x,-st.y);
}
vec2 func3(vec2 st) {
    return vec2(-st.x,st.y);
}
