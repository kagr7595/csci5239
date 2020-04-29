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

struct Petal {
    vec3 color;
};

uniform LightS light;

uniform Petal petal;
uniform int currently_petal;
uniform int currently_leaf;
uniform int special;

//  Transformation matrices
uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat3 NormalMatrix;

//  Vertex attributes (input)
layout(location = 0) in vec4 Vertex;
layout(location = 1) in vec3 Color;
layout(location = 2) in vec3 Normal;
layout(location = 3) in vec2 Texture2d;

//  Output to next shader
out vec3 FrontColor;
out vec3 FrontColorSpecial;
out vec3 TextureCoord2d;
out vec3 vNormal;

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
   color = special == 1 ? color + .2: color;

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

   FrontColor = (currently_petal == 1) ? petal.color*phong() : (currently_leaf == 1) ? (petal.color-vec3(.1,.1,.1))*phong() : petal.color*phong();
   FrontColorSpecial = vec3(1,1,1)*phong();
   //  Set transformed vertex location
   gl_Position =  ProjectionMatrix * ModelViewMatrix * Vertex;
   // Pass Texture2d
   TextureCoord2d = vec3(Texture2d,1);
   vNormal = Normal;
}
