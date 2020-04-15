#version 400 core

// Modifying phong to OpenGL4 code - starting from ex04c vert

struct LightS {
    vec3 ambient;
    vec3 diffuse;
    vec3 emission;
    vec3 position;
    vec3 specular;
    float shininess;
};

uniform LightS light;

//  Transformation matrices
uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat3 NormalMatrix;

//  Vertex attributes (input)
layout(location = 0) in vec4 Vertex;
layout(location = 1) in vec3 Color;
layout(location = 2) in vec3 Normal;

//  Output to next shader
out vec3 FrontColor;

vec3 phong()
{
   //  P is the vertex coordinate on body
   vec3 P = vec3(ModelViewMatrix * Vertex);
   //  N is the object normal at P
   vec3 N = normalize(NormalMatrix * Normal);
   //  Light Position for light 0
   vec3 LightPos = vec3(ViewMatrix*vec4(light.position,1.0));
   //  L is the light vector
   vec3 L = normalize(LightPos - P);

   //  Emission and ambient color
   vec3 color = light.emission + light.ambient;

   //  Diffuse light intensity is cosine of light and normal vectors
   float Id = dot(L,N);
   if (Id>0.0)
   {
      //  Add diffuse
      color += Id*light.diffuse;
      //  R is the reflected light vector R = 2(L.N)N - L
      vec3 R = reflect(-L, N);
      //  V is the view vector (eye at the origin)
      vec3 V = normalize(-P);
      //  Specular is cosine of reflected and view vectors
      float Is = dot(R,V);
      if (Is>0.0) color += pow(Is,light.shininess)*light.specular;
   }

   //  Return sum of color components
   return color;
}


void main()
{
   //  Pass colors to fragment shader (will be interpolated)
   FrontColor = Color*phong();
   //  Set transformed vertex location
   gl_Position =  ProjectionMatrix * ModelViewMatrix * Vertex;
}
