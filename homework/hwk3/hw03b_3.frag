
//  Model coordinates and light from vertex shader
varying float LightIntensity;
varying vec2  ModelPos;
uniform float time;

void main()
{
    //making strobe lighting that can get brighter/darker depending on x/y positions
    float s = cos(time*30.0)*ModelPos.x;
    float t = cos(time*30.0)*ModelPos.y;
   vec3 color  = vec3(s,t,.5);
   //  Modulate for lighting
   color *= LightIntensity;
   //  Pad color with alpha
   gl_FragColor = vec4(color,1.0);
}
