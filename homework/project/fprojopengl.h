//
//  OpenGL Fprojopengl Widget
//

#ifndef FProjOPENGL_H
#define FProjOPENGL_H

#include "CUgl.h"
#include <QMatrix4x4>
//#include <QGlobal.h>
#include <QTime>
#define C_FRONT 0
#define C_BACK 1
#define C_RIGHT 2
#define C_LEFT 3
#define C_TOP 4
#define C_BOTTOM 5

#define COLOR 0
#define DISP 1
#define NORM 2
#define OCC 3
#define ROUGH 4

#define NUM_FLOWERS 200
#define NUM_BFLOWERS 200
#define NUM_SFLOWERS 250
#define NUM_STONES 50

struct FlowerS {
    float loc_x;
    float loc_y;
    float loc_z;
    int rot_x;
    int rot_y;
    int rot_z;
    int scl;
    int height;
    int color;
    int draw;
    //0 = don't draw,
    //1 = draw the one flower,
    //2-4 = draw flower with other plants,
    //5 = draw two flowers
    //6 = draw special flower
    int secondary_flower_number;
    //only 100 possible -- if more 5s are rolled than 100 then the ones after 100 will have their draw number rerandomized
};


#define NUM_TREES 100

struct TreeS {
    float loc_x;
    float loc_y;
    float loc_z;
    int rot_x;
    int rot_y;
    int rot_z;
    float scl_x;
    float scl_y;
    float scl_z;
    float height;
    int color;
    int draw;
    //0 = don't draw,
    //1 = draw the one tree
};


class Fprojopengl : public CUgl
{
Q_OBJECT
private:
   QOpenGLTexture* tex;          //  Textures
   QOpenGLTexture* skyboxtex[6];          //  Textures
   QOpenGLTexture* grass[5];          //  Textures
   QOpenGLBuffer   triangular_prism_buffer;  //  Vertex buffer
   QOpenGLBuffer   cube_buffer;  //  Vertex buffer
   QOpenGLBuffer   skybox_buffer;  //  Vertex buffer
   QOpenGLBuffer   skybox1_buffer;  //  Vertex buffer
   QOpenGLBuffer   flat_leaf_buffer;  //  Vertex buffer
   QOpenGLBuffer   cone_buffer;  //  Vertex buffer
   QOpenGLBuffer   cylinder_buffer;  //  Vertex buffer
   QOpenGLBuffer   sharp_circle_flower_buffer;  //  Vertex buffer
   FlowerS         flower_data[NUM_FLOWERS];
   FlowerS         spikyflower_data[NUM_SFLOWERS];
   FlowerS         burrflower_data[NUM_BFLOWERS];
   FlowerS         stone_data[NUM_STONES];
   TreeS           tree_data[NUM_TREES];
public:
   Fprojopengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
protected:
   void initializeGL();  //  Initialize widget
   QVector3D colorvec(int color_name); //return color vector
   void paintGL();       //  Draw widget
   void setupflowerdata();
   void setupspikyflowerdata();
   void setupburrflowerdata();
   void setupstonesdata();
   void setuptreedata();
   int randInt(int low, int high);
   void drawflower(int pshader, QMatrix4x4 proj, QMatrix4x4 view, QMatrix4x4 mv,
                   float x_t, float y_t, float z_t,
                   float x_r, float y_r, float z_r,
                   float x_s, float y_s, float z_s,
                   float height, int color, int special);       //  Draw flower
   void drawspikyflower(int pshader, QMatrix4x4 proj, QMatrix4x4 view, QMatrix4x4 mv,
                   float x_t, float y_t, float z_t,
                   float x_r, float y_r, float z_r,
                   float x_s, float y_s, float z_s,
                   int color);       //  Draw spiky flowers
   void drawburrflower(int pshader, QMatrix4x4 proj, QMatrix4x4 view, QMatrix4x4 mv,
                   float x_t, float y_t, float z_t,
                   float x_r, float y_r, float z_r,
                   float x_s, float y_s, float z_s,
                   float height, int color);       //  Draw burr flowers
   void drawgrass(int pshader, QMatrix4x4 proj, QMatrix4x4 view, QMatrix4x4 mv,
                   float x_t, float y_t, float z_t,
                   float x_r, float y_r, float z_r,
                   float x_s, float y_s, float z_s,
                   int color);       //  Draw grass
   void drawstone(int pshader, QMatrix4x4 proj, QMatrix4x4 view, QMatrix4x4 mv,
                   float x_t, float y_t, float z_t,
                   float x_r, float y_r, float z_r,
                   float x_s, float y_s, float z_s);       //  Draw stone
   void drawtree(int pshader, QMatrix4x4 proj, QMatrix4x4 view, QMatrix4x4 mv,
                   float x_t, float y_t, float z_t,
                   float x_r, float z_r,
                   float x_s, float y_s, float z_s,
                   float height, int color_trunk, int color_branch);       //  Draw grass
   void outputallflowerdata();
   void outputflowerdata(int i);
   void outputalltreedata();
   void outputtreedata(int i);
   void triangular_prism();
   void cube_prism();
   QVector3D circle();
   int cylinder();
   int cone();
   int circle_up();
   int circle_down();
   QVector3D normals(float x0, float y0, float z0,
                     float x1, float y1, float z1,
                     float x2, float y2, float z2);
};

#endif
