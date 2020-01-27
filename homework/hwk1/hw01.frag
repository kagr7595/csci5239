//  Basic fragment shader

uniform vec3 window_dim; //use window_dim from "outside" the shader

void main()
{
   // KG change color to be based on the normalized device coordinates set in hw01.vert (which is unchanged)
   // KG gl_FragCoord contains the current normalized device coordinates 
   // KG window_dim is gotten from hw01opengl.cpp
   vec3 col= gl_FragCoord.xyz/window_dim;
   //  Set color
   gl_FragColor = vec4(col,1);
}
