/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// OpenGL ES 2.0 code

#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <vector>

#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

auto gVertexShader =
    "struct LightS {\n"
    "   vec3 ambient;\n"
    "   vec3 diffuse;\n"
    "   vec3 emission;\n"
    "   vec3 position;\n"
    "    vec3 specular;\n"
    "    float shininess;\n"
    "};\n"
    "uniform LightS light;\n"
    "uniform mat4 ProjectionMatrix;\n"
    "uniform mat4 ModelViewMatrix;\n"
    "uniform mat4 ViewMatrix;\n"
    "uniform mat3 NormalMatrix;\n"
    "attribute vec3 XYZ;\n"
    "attribute vec3 RGB;\n"
    "attribute vec3 NORMAL;\n"
    "varying vec3 col;\n"
    "vec3 phong()\n"
    "{\n"
        //  P is the vertex coordinate on body
    "   vec3 P = vec3(ModelViewMatrix * vec4(XYZ,1));\n"
        //  N is the object normal at P
    "   vec3 N = normalize(NormalMatrix * NORMAL);\n"
        //  Light Position for light 0
    "   vec3 LightPos = vec3(ViewMatrix*vec4(light.position,1.0));\n"
        //  L is the light vector
    "   vec3 L = normalize(LightPos - P);\n"

        //  Emission and ambient color
    "   vec3 color = light.emission + light.ambient;\n"

        //  Diffuse light intensity is cosine of light and normal vectors
    "   float Id = dot(L,N);\n"
    "    if (Id>0.0)\n"
    "    {\n"
            //  Add diffuse
    "       color += Id*light.diffuse;\n"
           //  R is the reflected light vector R = 2(L.N)N - L
    "       vec3 R = reflect(-L, N);\n"
           //  V is the view vector (eye at the origin)
    "       vec3 V = normalize(-P);\n"
           //  Specular is cosine of reflected and view vectors
    "       float Is = dot(R,V);\n"
    "       if (Is>0.0) color += pow(Is,light.shininess)*light.specular;\n"
    "    }\n"

        //  Return sum of color components
    "    return color;\n"
    "}\n"


    "void main() {\n"
    "  col = RGB*phong();\n"
    "  gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(XYZ,1);\n"
    "}\n";

auto gFragmentShader =
    "precision mediump float;\n"
    "varying vec3 col;\n"
    "void main() {\n"
    "  gl_FragColor = vec4(col,1);\n"
    "}\n";

GLuint loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                            shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint gProgram;
GLuint XYZHandle;
GLuint RGBHandle;
GLuint NormalHandle;


//  Vertex array count
const GLint n = 108;
//  "K" vertex coordinates
const GLfloat xyz[] =
        {

/*Side faces*/
                -1.0f, +1, -1,       -1, -1, -1,       -1, -1, +1,       -1, -1, +1,       -1, +1, +1,        -1, +1, -1, //1
                +.43f, +1, -1,    -.43f, +.25f, -1, -.43f, +.25f, +1, -.43f, +.25f, +1, +.43f, +1, +1,     +.43f, +1, -1, //10
                -.14f, 0, -1,     +.43f, -1, -1,    +.43f, -1, +1,    +.43f, -1, +1,    -.14f, 0, +1,      -.14f, 0, -1, //5
                -.14f, 0, +1,     -.43f, -.25f, +1, -.43f, -.25f, -1, -.43f, -.25f, -1, -.14f, 0, -1,      -.14f, 0, +1, //4
                -.43f, -.25f, +1, -.43f, -1, +1,    -.43f, -1, -1,    -.43f, -1, -1,    -.43f, -.25f, -1,  -.43f, -.25f, +1, //3
                +1.0f, +1, +1,    +.14f, +.25f, +1, +.14f, +.25f, -1, +.14f, +.25f, -1,    +1, +1, -1,        +1,  +1, +1, //8
                +.14f, +.25f, +1,    +1, -1, +1,       +1, -1, -1,      +1, -1, -1,     +.14f, +.25f, -1,  +.14f, +.25f, +1, //7
                -.43f, +1, +1,    -.43f, +.25f, +1, -.43f, +.25f, -1, -.43f, +.25f, -1, -.43f, +1, -1,     -.43f, +1, +1, //11
                -1.0f, -1, +1,       -1, -1, -1,    -.43f, -1, -1,    -.43f, -1, -1,    -.43f, -1, +1,        -1, -1, +1, //2
                +.43f, -1, +1,    +.43f, -1, -1,       +1, -1, -1,     +1, -1, -1,         +1, -1, +1,     +.43f, -1, +1, //6
                -1.0f, +1, -1,       -1, +1, +1,    -.43f, +1, +1,    -.43f, +1, +1,    -.43f, +1, -1,        -1, +1, -1, //12
                +.43f, +1, -1,    +.43f, +1, +1,       +1, +1, +1,     +1, +1, +1,         +1, +1, -1,     +.43f, +1, -1, //9

/*Front Face*/
                -1.0f, +1, +1,       -1, -1, +1,    -.43f, -1, +1,    -.43f, -1, +1,    -.43f, +1, +1,        -1, +1, +1,
                -.43f, +.25f, +1, -.43f, -.25f, +1, +.43f, +1, +1,    +.43f, +1, +1,    -.43f, -.25f, +1,     +1, +1, +1,
                -.14f, 0, +1,     +.43f, -1, +1,    +.14f, +.25f, +1, +.14f, +.25f, +1, +.43f, -1, +1,        +1, -1, +1,


/*Back side */
                -1.0f, +1, -1,    -.43f, -1, -1,       -1, -1, -1,    -.43f, -1, -1,       -1, +1, -1,     -.43f, +1, -1,
                -.43f, +.25f, -1, +.43f, +1, -1,    -.43f, -.25f, -1, +.43f, +1, -1,       +1, +1, -1,     -.43f, -.25f,-1,
                -.14f, 0, -1,     +.14f, +.25f, -1, +.43f, -1, -1,    +.14f, +.25f, -1,    +1, -1, -1,     +.43f, -1, -1,
        };

//  "K" colors
const GLfloat rgb[] =
        {
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,
                0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
                1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0,

                0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,
                0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1,
                1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1,
        };

GLfloat normals[n*3] = {};
void set_normal(float x0,float y0,float z0,float x1,float y1,float z1,float x2,float y2,float z2,int i)
{
    float vx0 = x1-x0;
    float vy0 = y1-y0;
    float vz0 = z1-z0;
    float vx1 = x2-x0;
    float vy1 = y2-y0;
    float vz1 = z2-z0;
    float Nx = (vy0*vz1)-(vz0*vy1);
    float Ny = (vz0*vx1)-(vx0*vz1);
    float Nz = (vx0*vy1)-(vy0*vx1);
    normals[9*i+0] = Nx;
    normals[9*i+1] = Ny;
    normals[9*i+2] = Nz;
    normals[9*i+3] = Nx;
    normals[9*i+4] = Ny;
    normals[9*i+5] = Nz;
    normals[9*i+6] = Nx;
    normals[9*i+7] = Ny;
    normals[9*i+8] = Nz;
}

//  Rotation angles
float ph = 165;
//  Light Position
float zh = 0;
float lrad = 1.5;
float lpos_x = lrad*cos(zh*3.14/180);
float lpos_y = 2;
float lpos_z = lrad*sin(zh*3.14/180);
float t0;
float modelview[16];
float view[16];
float normalview[9];
int desiredAngle = 0;
int currentAngle = 0;

//  Taken from https://stackoverflow.com/questions/10961746/opengl-normal-matrix
float determinant(float m[9]){
    return
            (+m[0] * (m[4] * m[8] - m[7] * m[5])
             -m[3] * (m[1] * m[8] - m[7] * m[2])
             +m[6] * (m[1] * m[5] - m[4] * m[2]));
}
//  Taken from https://stackoverflow.com/questions/10961746/opengl-normal-matrix
void mat3(float m4[16], float m[9]){
    m[0]=m4[0];
    m[1]=m4[1];
    m[2]=m4[2];
    m[3]=m4[4];
    m[4]=m4[5];
    m[5]=m4[6];
    m[6]=m4[8];
    m[7]=m4[9];
    m[8]=m4[10];
}
//  Taken from https://stackoverflow.com/questions/10961746/opengl-normal-matrix
void inverse(float m[9], float inversem[9], int offset){
    float Determinant = determinant(m);
    inversem[offset+0] = + (m[4] * m[8] - m[7] * m[5])/ Determinant;
    inversem[offset+3] = - (m[3] * m[8] - m[6] * m[5])/ Determinant;
    inversem[offset+6] = + (m[3] * m[7] - m[6] * m[4])/ Determinant;
    inversem[offset+1] = - (m[1] * m[8] - m[7] * m[2])/ Determinant;
    inversem[offset+4] = + (m[0] * m[8] - m[6] * m[2])/ Determinant;
    inversem[offset+7] = - (m[0] * m[7] - m[6] * m[1])/ Determinant;
    inversem[offset+2] = + (m[1] * m[5] - m[4] * m[2])/ Determinant;
    inversem[offset+5] = - (m[0] * m[5] - m[3] * m[2])/ Determinant;
    inversem[offset+8] = + (m[0] * m[4] - m[3] * m[1])/ Determinant;
}
//  Taken from https://stackoverflow.com/questions/10961746/opengl-normal-matrix
void transpose(float m[9], int offset, float result[9]){
    result[0] = m[offset+0];
    result[1] = m[offset+3];
    result[2] = m[offset+6];

    result[3] = m[offset+1];
    result[4] = m[offset+4];
    result[5] = m[offset+7];

    result[6] = m[offset+2];
    result[7] = m[offset+5];
    result[8] = m[offset+8];
}

//  Taken from RenderingEngine.cpp 5239 example 10
void renderRotate(int angle) {
    //update global angle
    desiredAngle = angle;
}
//  Taken from RenderingEngine.cpp 5239 example 10
//  Determine rotation direction
//    0 - match
//    +1 clockwise
//    -i counter-clockwise
float renderRotationDirection()
{
    float delta = desiredAngle - currentAngle;
    if (delta==0)
        return 0;
    else if ((delta > 0 && delta <= 180) || (delta < -180))
        return +1;
    else
        return -1;
}

//   Taken from RenderingEngine.cpp 5239 example 10
//  Update current angle during animation
//
void renderUpdateAnimation(float t)
{
    //  Time increments
    float dt = t-t0;
    t0 = t;
    //  Direction to rotate during animation
    float direction = renderRotationDirection();
    //  Animation done
    if (dt<0 || direction == 0) return;

    //  Change current angle at 90 deg/sec
    currentAngle +=  direction * 90 * dt;

    // Normalize the angle to [0, 360)
    while (currentAngle >= 360)
        currentAngle -= 360;
    while (currentAngle < 0)
        currentAngle += 360;

    // If the rotation direction changed, then we reached the desired angle.
    if (renderRotationDirection() != direction) currentAngle = desiredAngle;
}


//  Taken from RenderingEngine2.cpp 5239 example 10
//  Set model view (rotation) matrix
//
void renderApplyModelview()
{
    //  Set the modelview matrix in shader
    GLint id = glGetUniformLocation(gProgram,"ModelViewMatrix");
    if (id>=0) glUniformMatrix4fv(id,1,0,modelview);
}
//  Taken from RenderingEngine2.cpp 5239 example 10
//  Set modelview matrix to I
void modelviewLoadIdentity()
{
    float I[16] =
            {
                    1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1
            };
    memcpy(modelview,I,sizeof(modelview));
}
void renderViewandNormalMatrix() {
    float temp [18] = {};
    memcpy(view,modelview,sizeof(modelview));
    //  Set the view matrix in shader
    GLint id = glGetUniformLocation(gProgram,"ViewMatrix");
    if (id>=0) glUniformMatrix4fv(id,1,0,view);

    mat3(modelview,temp);
    inverse(temp,temp,9);
    transpose(temp,9,normalview);
    //  Set the normal matrix in shader
    id = glGetUniformLocation(gProgram,"NormalMatrix");
    if (id>=0) glUniformMatrix3fv(id,1,0,normalview);
}
void renderLight(){
    // set the light information
    GLint lightposition = glGetUniformLocation(gProgram, "light.position");
    glUniform3f(lightposition, lpos_x, lpos_y, lpos_z);
    GLint lightambient = glGetUniformLocation(gProgram, "light.ambient");
    glUniform3f(lightambient, 0.3, 0.3, 0.3);
    GLint lightdiffuse = glGetUniformLocation(gProgram, "light.diffuse");
    glUniform3f(lightdiffuse, 1, 1, 1);
    GLint lightemission = glGetUniformLocation(gProgram, "light.emission");
    glUniform3f(lightemission, 0.1, 0.1, 0.1);
    GLint lightshininess = glGetUniformLocation(gProgram, "light.shininess");
    glUniform1f(lightshininess, 16.0);
    GLint lightspecular = glGetUniformLocation(gProgram, "light.specular");
    glUniform3f(lightspecular, 1, 1, 1);
}

//   Taken from RenderingEngine2.cpp 5239 example 10
//  Apply rotation to modelview matrix
//
void modelviewRotate(float deg,float X,float Y,float Z)
{
    //  Normalize axis
    float l = sqrt(X*X+Y*Y+Z*Z);
    if (l==0) return;
    float x = X/l;
    float y = Y/l;
    float z = Z/l;
    //  Calculate sin and cos
    float s = sin(deg*3.1415927/180);
    float c = cos(deg*3.1415927/180);
    float C = 1-c;
    //  Rotation matrix
    float rot[16] =
            {
                    C*x*x+c   , C*x*y+z*s , C*z*x-y*s , 0 ,
                    C*x*y-z*s , C*y*y+c   , C*y*z+x*s , 0 ,
                    C*z*x+y*s , C*y*z-x*s , C*z*z+c   , 0 ,
                    0    ,      0    ,      0    , 1 ,
            };
    //  Copy old matrix
    float mv0[16];
    memcpy(mv0,modelview,sizeof(modelview));
    //  Multiply matrixes
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            modelview[4*i+j] = mv0[j]*rot[4*i]+ mv0[4+j]*rot[4*i+1]+ mv0[8+j]*rot[4*i+2]+ mv0[12+j]*rot[4*i+3];
}


//  Taken from RenderingEngine2.cpp 5239 example 10
//  Set projection matrix
//
void renderApplyOrtho(int width,int height)
{
    //  Create orthogonal projection matrix
    float asp = width/(float)height;
    float dim = 2.5;
    float a = 1/(dim*asp);
    float b = 1/dim;
    float mat[16] =
            {
                    a, 0,  0, 0,
                    0, b,  0, 0,
                    0, 0, -b, 0,
                    0, 0,  0, 1
            };
    //  Set projection matrix in shader
    GLint id = glGetUniformLocation(gProgram,"ProjectionMatrix");
    if (id>=0) glUniformMatrix4fv(id,1,0,mat);
}

bool setupGraphics(int w, int h) {
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("setupGraphics(%d, %d)", w, h);
    gProgram = createProgram(gVertexShader, gFragmentShader);
    if (!gProgram) {
        LOGE("Could not create program.");
        return false;
    }
    XYZHandle = glGetAttribLocation(gProgram, "XYZ");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"XYZ\") = %d\n",
         XYZHandle);
    RGBHandle = glGetAttribLocation(gProgram, "RGB");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"RGB\") = %d\n",
         RGBHandle);
    NormalHandle = glGetAttribLocation(gProgram, "NORMAL");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"NORMAL\") = %d\n",
         NormalHandle);

    glViewport(0, 0, w, h);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    glUseProgram(gProgram);
    checkGlError("glUseProgram");

    //  Set projection
    renderApplyOrtho(w,h);
    renderRotate(0);
    currentAngle = desiredAngle;
    renderUpdateAnimation(0);

    //Calculate normals
    for(GLint i = 0; i < n/3; i++) {
        set_normal(xyz[9*i+0],xyz[9*i+1],xyz[9*i+2],
                   xyz[9*i+3],xyz[9*i+4],xyz[9*i+5],
                   xyz[9*i+6],xyz[9*i+7],xyz[9*i+8],
                   i);
    }

    checkGlError("glViewport");
    return true;
}

void renderFrame(double t) {
    //GLuint verts;
    //glGenBuffers(1,&verts);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, verts);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(xyz),xyz,GL_STATIC_DRAW);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //GLuint color;
    //glGenBuffers(1,&color);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, color);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(rgb),rgb,GL_STATIC_DRAW);
    //GLuint normalb;
    //glGenBuffers(1,&normalb);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, normalb);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(normals),normals,GL_STATIC_DRAW);

    glClearColor(0.6, 0.6, 0.6, 1.0f);
    checkGlError("glClearColor");
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");

    modelviewLoadIdentity();
    modelviewRotate(currentAngle, 0, 0, 1);
    modelviewRotate(ph, 1, 0, 0);
    modelviewRotate(30*t, 0, 1, 0);
    renderApplyModelview();
    renderViewandNormalMatrix();
    renderLight();

    zh = zh + 1;
    if (zh>360) zh -= 360;
    lpos_x = lrad*cos(zh*3.14/180);
    lpos_z = lrad*sin(zh*3.14/180);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, verts);
    //GLuint XYZ = glGetAttribLocation(gProgram, "XYZ");
    //checkGlError("glGetAttribLocation");
    glVertexAttribPointer(XYZHandle, 3, GL_FLOAT, GL_FALSE,0, &xyz);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(XYZHandle);
    checkGlError("glEnableVertexAttribArray");

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, color);
    //GLuint RGB = glGetAttribLocation(gProgram, "RGB");
    //checkGlError("glGetAttribLocation");
    glVertexAttribPointer(RGBHandle, 3, GL_FLOAT, GL_FALSE, 0, &rgb);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(RGBHandle);
    checkGlError("glEnableVertexAttribArray");

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, normalb);
    //GLuint Normal = glGetAttribLocation(gProgram, "Normal");
    //checkGlError("glGetAttribLocation");
    glVertexAttribPointer(NormalHandle, 3, GL_FLOAT, GL_FALSE, 0, normals);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(NormalHandle);
    checkGlError("glEnableVertexAttribArray");

    //glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, n);
    checkGlError("glDrawArrays");
    //  Disable vertex arrays
    //glDisableVertexAttribArray(verts);
    //glDisableVertexAttribArray(color);

}

extern "C" {
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj, jfloat t);
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_rotate(JNIEnv * env, jobject obj, jint angle);
};

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj, jfloat t)
{
    renderUpdateAnimation(t);
    renderFrame(t);
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_rotate(JNIEnv * env, jobject obj, jint angle)
{
    renderRotate(angle);
}
