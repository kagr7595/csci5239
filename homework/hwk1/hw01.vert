//  Basic vertex shader

//This shader doesn't really do anything a basic .vert shader wouldn't already do
void main()
{ 
   //  Set vertex coordinates
   vec4 pos = gl_Vertex;
   //  Scale in XY plane
   //pos.xy *= 1.0+0.3*cos(4.0*time); //KG Do not need this as I just want the color to be mapped with no size changes
   //  Transform to normalized device coordinates
   gl_Position = gl_ModelViewProjectionMatrix * pos;
}
