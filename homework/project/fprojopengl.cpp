//
//  OpenGL widget
//
#include "fprojopengl.h"
#include "drawobjects.cpp"
//
//  Constructor
//
Fprojopengl::Fprojopengl(QWidget* parent)
    : CUgl(parent)
{
}


//
//  Initialize
//
void Fprojopengl::initializeGL()
{
   glEnable(GL_CULL_FACE);
   setupflowerdata();
   setupspikyflowerdata();
   setupburrflowerdata();
   setuptreedata();
   // Texture
   skyboxtex[C_FRONT] = new QOpenGLTexture(QImage(":/hills_ft.bmp").mirrored());
   skyboxtex[C_BACK] = new QOpenGLTexture(QImage(":/hills_bk.bmp").mirrored());
   skyboxtex[C_LEFT] = new QOpenGLTexture(QImage(":/hills_lf.bmp").mirrored());
   skyboxtex[C_RIGHT] = new QOpenGLTexture(QImage(":/hills_rt.bmp").mirrored());
   skyboxtex[C_TOP] = new QOpenGLTexture(QImage(":/hills_up.bmp").mirrored());
   skyboxtex[C_BOTTOM] = new QOpenGLTexture(QImage(":/hills_dn.bmp").mirrored());

   for(int i = 0; i< 6; i++) {
      skyboxtex[i]->setWrapMode(QOpenGLTexture::ClampToEdge);
   }

   grass[COLOR] = new QOpenGLTexture(QImage(":/Grass4/Grass_004_COLOR.jpg").mirrored());
   grass[ROUGH] = new QOpenGLTexture(QImage(":/grass_bottom.bmp").mirrored());
   grass[DISP] = new QOpenGLTexture(QImage(":/Grass4/Grass_004_DISP.png").mirrored());
   grass[NORM] = new QOpenGLTexture(QImage(":/Grass4/Grass_004_NORM.jpg").mirrored());
   grass[OCC] = new QOpenGLTexture(QImage(":/Grass4/Grass_004_OCC.jpg").mirrored());
   //grass[ROUGH] = new QOpenGLTexture(QImage(":/Grass4/Grass_004_ROUGH.jpg").mirrored());

   for(int i = 0; i< 5; i++) {
      grass[i]->setWrapMode(QOpenGLTexture::ClampToEdge);
   }


   tex = new QOpenGLTexture(QImage(":/crate.png").mirrored()); // for flowers -- works surprisingly well

   addShader(0,":/fproj_skybox.vert",":/fproj_skybox.frag"); //SKYBOX
   addShader3(0,":/fproj_grass.vert",":/fproj_grass.geom",":/fproj_grass.frag"); //GRASS
   //  Load shaders
   addShader3(1,":/fproj_flower.vert",":/fproj_flower.geom",":/fproj_flower.frag");
   addShader3(1,":/fproja.vert",":/fproja.geom",":/fproja.frag");
   addShader3(1,":/fprojb.vert",":/fprojb.geom",":/fprojb.frag");
   addShader3(1,":/fprojb.vert",":/fprojc.geom",":/fprojb.frag");
   addShader3(1,":/fproj_tree.vert",":/fproj_tree.geom",":/fproj_tree.frag");

   triangular_prism();
   //  triangular prism vertex buffer object
   //  Copy data to vertex buffer object
   triangular_prism_buffer.create();
   triangular_prism_buffer.bind();
   triangular_prism_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
   triangular_prism_buffer.allocate(sizeof(triangular_prism_data));
   triangular_prism_buffer.write(0,triangular_prism_data,sizeof(triangular_prism_data));
   //  Unbind this buffer
   triangular_prism_buffer.release();

   cube_prism();
   //  Cube vertex buffer object
   //  Copy data to vertex buffer object
   cube_buffer.create();
   cube_buffer.bind();
   cube_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
   cube_buffer.allocate(sizeof(cube_data));
   cube_buffer.write(0,cube_data,sizeof(cube_data));
   //  Unbind this buffer
   cube_buffer.release();


   //  Skybox vertex buffer object
   //  Copy data to vertex buffer object
   skybox_buffer.create();
   skybox_buffer.bind();
   skybox_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
   skybox_buffer.allocate(sizeof(skybox_data));
   skybox_buffer.write(0,skybox_data,sizeof(skybox_data));
   //  Unbind this buffer
   skybox_buffer.release();

   //  Flat_leaf vertex buffer object
   //  Copy data to vertex buffer object
   flat_leaf_buffer.create();
   flat_leaf_buffer.bind();
   flat_leaf_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
   flat_leaf_buffer.allocate(sizeof(flat_leaf_data));
   flat_leaf_buffer.write(0,flat_leaf_data,sizeof(flat_leaf_data));
   //  Unbind this buffer
   flat_leaf_buffer.release();
   //circle_up();
   //circle_down();
   //cone();
   //cylinder();
   //  Cone vertex buffer object
   //  Copy data to vertex buffer object
   cone_buffer.create();
   cone_buffer.bind();
   cone_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
   cone_buffer.allocate(sizeof(cone_data));
   cone_buffer.write(0,cone_data,sizeof(cone_data));
   //  Unbind this buffer
   cone_buffer.release();

   //  Cylinder vertex buffer object
   //  Copy data to vertex buffer object
   cylinder_buffer.create();
   cylinder_buffer.bind();
   cylinder_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
   cylinder_buffer.allocate(sizeof(cylinder_data));
   cylinder_buffer.write(0,cylinder_data,sizeof(cylinder_data));
   //  Unbind this buffer
   cylinder_buffer.release();

   //  sharp_circle_flower vertex buffer object
   //  Copy data to vertex buffer object
   sharp_circle_flower_buffer.create();
   sharp_circle_flower_buffer.bind();
   sharp_circle_flower_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
   sharp_circle_flower_buffer.allocate(sizeof(sharp_circle_flower_data));
   sharp_circle_flower_buffer.write(0,sharp_circle_flower_data,sizeof(sharp_circle_flower_data));
   //  Unbind this buffer
   sharp_circle_flower_buffer.release();
}

int Fprojopengl::randInt(int low, int high) {
    return qrand() %((high+1)-low)+low;
}

void Fprojopengl::outputallflowerdata() {
    for(int i = 0; i< NUM_FLOWERS-NUM_FLOWERS*.1; i++) {
        qInfo() << "flower[" << i << "]";
        qInfo() << "   loc_xyz: (" << flower_data[i].loc_x << "," << flower_data[i].loc_y << "," << flower_data[i].loc_z << ")";
        qInfo() << "   rot_xyz: (" << flower_data[i].rot_x << "," << flower_data[i].rot_y << "," << flower_data[i].rot_z << ")";
        qInfo() << "   scl: " << flower_data[i].scl << ", height: " << flower_data[i].height << ", color: " << flower_data[i].color << ", draw:" << flower_data[i].draw;
        if(flower_data[i].draw == 5)
            outputflowerdata(flower_data[i].secondary_flower_number);
    }
}
void Fprojopengl::outputflowerdata(int i) {
    qInfo() << "flower[" << i << "]";
    qInfo() << "   loc_xyz: (" << flower_data[i].loc_x << "," << flower_data[i].loc_y << "," << flower_data[i].loc_z << ")";
    qInfo() << "   rot_xyz: (" << flower_data[i].rot_x << "," << flower_data[i].rot_y << "," << flower_data[i].rot_z << ")";
    qInfo() << "   scl: " << flower_data[i].scl << ", height: " << flower_data[i].height << ", color: " << flower_data[i].color << ", draw:" << flower_data[i].draw;
}

void Fprojopengl::setupflowerdata(){
    int current_secondary_flower = NUM_FLOWERS-NUM_FLOWERS*.1;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    for(int i = 0; i< NUM_FLOWERS; i++) {
        if(i < NUM_FLOWERS-NUM_FLOWERS*.1) {
            if(current_secondary_flower == NUM_FLOWERS)
                flower_data[i].draw = randInt(0,4);
            else
                flower_data[i].draw = randInt(0,6);
        } else if (i < current_secondary_flower)
            flower_data[i].draw = 1;
        else
            flower_data[i].draw = 0;

        flower_data[i].loc_x = randInt(-1000,1000)/1000.0;
        flower_data[i].loc_y = 0.0;
        flower_data[i].loc_z = randInt(-1000,1000)/1000.0;
        flower_data[i].rot_x = randInt(-60,60);
        flower_data[i].rot_y = 0;
        flower_data[i].rot_z = randInt(-60,60);
        flower_data[i].scl = randInt(1,3);
        flower_data[i].height = randInt(1,3);
        flower_data[i].color = randInt(2,NUM_COLORS); // don't include white or black
        if(flower_data[i].draw == 5) {
            //get next available flower number after NUM_FLOWERS-NUM_FLOWERS*.1
            flower_data[i].secondary_flower_number = current_secondary_flower;
            current_secondary_flower++;
        }
    }

    //outputallflowerdata();

}

void Fprojopengl::setupspikyflowerdata(){
    int current_secondary_flower = NUM_SFLOWERS-NUM_SFLOWERS*.1;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    for(int i = 0; i< NUM_SFLOWERS; i++) {
        if(i < NUM_SFLOWERS-NUM_SFLOWERS*.1) {
            if(current_secondary_flower == NUM_SFLOWERS)
                spikyflower_data[i].draw = randInt(0,2);
            else
                spikyflower_data[i].draw = randInt(0,3);
        } else if (i < current_secondary_flower)
            spikyflower_data[i].draw = 1;
        else
            spikyflower_data[i].draw = 0;

        spikyflower_data[i].loc_x = randInt(-1000,600)/1000.0;
        spikyflower_data[i].loc_y = 0.0;
        spikyflower_data[i].loc_z = randInt(-600,1000)/1000.0;
        spikyflower_data[i].rot_x = randInt(-60,60);
        spikyflower_data[i].rot_y = 0;
        spikyflower_data[i].rot_z = randInt(-60,60);
        spikyflower_data[i].scl = randInt(1,3);
        spikyflower_data[i].height = randInt(0,1);
        spikyflower_data[i].color = randInt(2,NUM_COLORS-2); // don't include white or yellow or black
        if(spikyflower_data[i].draw == 3) {
            //get next available flower number after NUM_FLOWERS-NUM_FLOWERS*.1
            spikyflower_data[i].secondary_flower_number = current_secondary_flower;
            current_secondary_flower++;
        }
    }

    //outputallflowerdata();

}
void Fprojopengl::setupburrflowerdata(){
    int current_secondary_flower = NUM_BFLOWERS-NUM_BFLOWERS*.1;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    for(int i = 0; i< NUM_BFLOWERS; i++) {
        if(i < NUM_BFLOWERS-NUM_BFLOWERS*.1) {
            if(current_secondary_flower == NUM_BFLOWERS)
                burrflower_data[i].draw = randInt(0,1);
            else
                burrflower_data[i].draw = randInt(0,2);
        } else if (i < current_secondary_flower)
            burrflower_data[i].draw = 1;
        else
            burrflower_data[i].draw = 0;

        burrflower_data[i].loc_x = randInt(-500,1000)/1000.0;
        burrflower_data[i].loc_y = 0.0;
        burrflower_data[i].loc_z = randInt(-1000,500)/1000.0;
        burrflower_data[i].rot_x = randInt(-60,60);
        burrflower_data[i].rot_y = 0;
        burrflower_data[i].rot_z = randInt(-60,60);
        burrflower_data[i].scl = randInt(1,3);
        burrflower_data[i].height = randInt(0,1);
        burrflower_data[i].color = randInt(1,NUM_COLORS-2); // don't include white or yellow
        if(burrflower_data[i].draw == 2) {
            //get next available flower number after NUM_FLOWERS-NUM_FLOWERS*.1
            burrflower_data[i].secondary_flower_number = current_secondary_flower;
            current_secondary_flower++;
        }
    }

    //outputallflowerdata();

}

void Fprojopengl::setupstonesdata(){
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    for(int i = 0; i< NUM_FLOWERS; i++) {
        tree_data[i].draw   = randInt(0,1);
        stone_data[i].loc_x = randInt(-200,200)/1000.0;
        stone_data[i].loc_y = 0.0;
        stone_data[i].loc_z = randInt(-500,500)/1000.0;
        stone_data[i].rot_x = randInt(-10,10);
        stone_data[i].rot_y = 0;
        stone_data[i].rot_z = randInt(-10,10);
        stone_data[i].scl = randInt(1,3);
        stone_data[i].height = randInt(1,3);
        stone_data[i].color = 1;
    }

}

void Fprojopengl::outputalltreedata() {
    for(int i = 0; i< NUM_TREES; i++) {
        qInfo() << "tree[" << i << "]";
        qInfo() << "   loc_xyz: (" << tree_data[i].loc_x << "," << tree_data[i].loc_y << "," << tree_data[i].loc_z << ")";
        qInfo() << "   rot_xyz: (" << tree_data[i].rot_x << "," << tree_data[i].rot_y << "," << tree_data[i].rot_z << ")";
        qInfo() << "   scl_xyz: (" << tree_data[i].scl_x << "," << tree_data[i].scl_y << "," << tree_data[i].scl_z << ")";
        qInfo() << ", height: " << tree_data[i].height << ", color: " << tree_data[i].color << ", draw:" << tree_data[i].draw;

    }
}
void Fprojopengl::outputtreedata(int i) {

    qInfo() << "tree[" << i << "]";
    qInfo() << "   loc_xyz: (" << tree_data[i].loc_x << "," << tree_data[i].loc_y << "," << tree_data[i].loc_z << ")";
    qInfo() << "   rot_xyz: (" << tree_data[i].rot_x << "," << tree_data[i].rot_y << "," << tree_data[i].rot_z << ")";
    qInfo() << "   scl_xyz: (" << tree_data[i].scl_x << "," << tree_data[i].scl_y << "," << tree_data[i].scl_z << ")";
    qInfo() << ", height: " << tree_data[i].height << ", color: " << tree_data[i].color << ", draw:" << tree_data[i].draw;

}

void Fprojopengl::setuptreedata(){
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    for(int i = 0; i< NUM_TREES; i++) {
        tree_data[i].draw = randInt(0,1);
        int val = randInt(-1000,1000);
        tree_data[i].loc_x = val < 0 ? (val-100)/1000.0 < -1 ? val/1000.0 : (val-100)/1000.0 : (val+100)/1000.0 > 1 ? val/1000.0 : (val+100)/1000.0;
        tree_data[i].loc_y = -0.02;
        val = randInt(-1000,1000);
        tree_data[i].loc_z = val < 0 ? (val-100)/1000.0 < -1 ? val/1000.0 : (val-100)/1000.0 : (val+100)/1000.0 > 1 ? val/1000.0 : (val+100)/1000.0;
        tree_data[i].rot_x = randInt(-2,2);
        tree_data[i].rot_y = 0;
        tree_data[i].rot_z = randInt(-2,2);
        val = randInt(3,6);
        tree_data[i].scl_y = val/2.0;
        tree_data[i].scl_x = randInt(val-2,val-1);
        tree_data[i].scl_z = randInt(val-2,val-1);
        tree_data[i].height = randInt(0,2)/10.0;
        tree_data[i].color = randInt(4,5); // only green or blue
    }

    //outputalltreedata();

}

//
//
//
QVector3D Fprojopengl::colorvec(int color_name) {
    QVector3D color;
    switch(color_name) {
    case BROWN:
        color = (season == FALL) ? QVector3D(96,60,20) :
                                 (season == SPRING) ? QVector3D(123,63,0) :
                                                    (season == WINTER) ? QVector3D(159,129,112) :
                                                                       (season == SUMMER) ? QVector3D(138,51,136) :
                                                                                          QVector3D(150,75,0);
        break;
    case RED:
        color = (season == FALL) ? QVector3D(156,39,6) :
                                 (season == SPRING) ? QVector3D(243,168,188) :
                                                    (season == WINTER) ? QVector3D(66,104,124) :
                                                                       (season == SUMMER) ? QVector3D(255,89,143) :
                                                                                          QVector3D(255,0,0);
        break;
    case ORANGE:
        color = (season == FALL) ? QVector3D(212,91,18) :
                                 (season == SPRING) ? QVector3D(245,176,148) :
                                                    (season == WINTER) ? QVector3D(132,165,184) :
                                                                       (season == SUMMER) ? QVector3D(243,135,47) :
                                                                                          QVector3D(255,127,0);
        break;
    case YELLOW:
        color = (season == FALL) ? QVector3D(243,188,46) :
                                 (season == SPRING) ? QVector3D(255,241,166) :
                                                    (season == WINTER) ? QVector3D(203,203,203) :
                                                                       (season == SUMMER) ? QVector3D(255,215,0) :
                                                                                          QVector3D(255,255,0);
        break;
    case GREEN:
        color = (season == FALL) ? QVector3D(95,84,38) :
                                 (season == SPRING) ? QVector3D(180,249,165) :
                                                    (season == WINTER) ? QVector3D(112,117,113) :
                                                                       (season == SUMMER) ? QVector3D(180,249,165) :
                                                                                          QVector3D(0,255,0);
        break;
    case BLUE:
        color = (season == FALL) ? QVector3D(96,60,20) :
                                 (season == SPRING) ? QVector3D(158,231,245) :
                                                    (season == WINTER) ? QVector3D(179,218,241) :
                                                                       (season == SUMMER) ? QVector3D(21,178,211) :
                                                                                          QVector3D(0,0,255);
        break;
    case BLACK:
        color = QVector3D(0,0,0);
        break;
    case WHITE:
        color = QVector3D(255,255,255);
        break;

    }

    return color/255.0;
}

//
//  Draw the window
//
void Fprojopengl::paintGL()
{
    float floor_cube = 60.0;
    int current_shader = 0;
    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.8,0.8,0.8,1.0);

    //  Set projection for fixed pipeline
    doModelViewProjection();

    //  Set light
    QVector3D lpos = doLight(); //KG set uniform value LPosition as input to vert shader
    //Q_UNUSED(lpos);  // Suppress warning since lpos is not used yet

    //  Create Projection matrix
    QMatrix4x4 proj;
    proj.setToIdentity();
    float asp = width() / (float)height();
    if (fov)
     proj.perspective(fov,asp,dim/40,40*dim);
    else
     proj.ortho(-dim*asp, +dim*asp, -dim, +dim, -dim, +dim);
    //  Create View matrix
    QMatrix4x4 view;
    if (fov) view.translate(0,0,-2*dim);
    view.rotate(ph,1,0,0);
    view.rotate(th,0,1,0);
    //  Create ModelView matrix
    QMatrix4x4 mv = view;
    mv.translate(0,0,0);
    mv.scale(floor_cube,floor_cube,floor_cube);

    //SKYBOX
    // Enable shader
    shader[SKYBOX][SKYBOX]->bind();
    //KG Set Light Position
    shader[SKYBOX][SKYBOX]->setUniformValue("light.ambient",QVector3D(0.3,0.3,0.3)); //Associate with light.ambient in vert (based on CUgl settings)
    shader[SKYBOX][SKYBOX]->setUniformValue("light.diffuse",QVector3D(1.0,1.0,1.0)); //Associate with light.diffuse in vert (based on CUgl settings)
    shader[SKYBOX][SKYBOX]->setUniformValue("light.emission",QVector3D(0.1,0.1,0.1)); //Associate with light.emission in vert
    shader[SKYBOX][SKYBOX]->setUniformValue("light.position",QVector3D(lpos.x(),lpos.y(),lpos.z())); //Associate with light.position in vert
    shader[SKYBOX][SKYBOX]->setUniformValue("light.shininess",16.0f); //Associate with light.shininess in vert
    shader[SKYBOX][SKYBOX]->setUniformValue("light.specular",QVector3D(1.0,1.0,1.0)); //Associate with light.specular in vert (based on CUgl settings)

    skybox_buffer.bind();
    //  Set Modelview and Projection Matrix
    shader[SKYBOX][SKYBOX]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
    shader[SKYBOX][SKYBOX]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
    //KG Set View and Normal
    shader[SKYBOX][SKYBOX]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
    shader[SKYBOX][SKYBOX]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3
    for (int i = 0; i< 6; i++)  {
        skyboxtex[i]->bind();

        //   Attribute 0: vertex coordinate (vec4) at offset 0
        shader[SKYBOX][SKYBOX]->enableAttributeArray(0);
        shader[SKYBOX][SKYBOX]->setAttributeBuffer(0,GL_FLOAT,(0)*sizeof(float),4,9*sizeof(float));
        //   Attribute 2:  vertex normal (vec3) offset 4 floats
        shader[SKYBOX][SKYBOX]->enableAttributeArray(1);
        shader[SKYBOX][SKYBOX]->setAttributeBuffer(1,GL_FLOAT,(4)*sizeof(float),3,9*sizeof(float));
        //   Attribute 3:  texture coor 2d (vec2) offset 7 floats
        shader[SKYBOX][SKYBOX]->enableAttributeArray(2);
        shader[SKYBOX][SKYBOX]->setAttributeBuffer(2,GL_FLOAT,(7)*sizeof(float),2,9*sizeof(float));

        glDrawArrays(GL_TRIANGLES,i*6,skybox_size/6);
    }

    skybox_buffer.release();


    shader[SKYBOX][SKYBOX]->release();
    mv.translate(0,-.1,0);
    mv.scale(1/floor_cube,1/floor_cube,1/floor_cube);

    shader[SKYBOX][FLOOR]->bind();
    //KG Set Light Position
    shader[SKYBOX][FLOOR]->setUniformValue("light.ambient",QVector3D(0.3,0.3,0.3)); //Associate with light.ambient in vert (based on CUgl settings)
    shader[SKYBOX][FLOOR]->setUniformValue("light.diffuse",QVector3D(1.0,1.0,1.0)); //Associate with light.diffuse in vert (based on CUgl settings)
    shader[SKYBOX][FLOOR]->setUniformValue("light.emission",QVector3D(0.1,0.1,0.1)); //Associate with light.emission in vert
    shader[SKYBOX][FLOOR]->setUniformValue("light.position",QVector3D(lpos.x(),lpos.y(),lpos.z())); //Associate with light.position in vert
    shader[SKYBOX][FLOOR]->setUniformValue("light.shininess",16.0f); //Associate with light.shininess in vert
    shader[SKYBOX][FLOOR]->setUniformValue("light.specular",QVector3D(1.0,1.0,1.0)); //Associate with light.specular in vert (based on CUgl settings)

    mv.scale(1.0,.1,1.0);
    cube_buffer.bind();

    grass[COLOR]->bind();
    for(int i = 0; i< floor_cube; i++) {
        mv.translate(-(floor_cube-1.0)+2*i,0,-(floor_cube-1.0));
        for(int j = 0; j< floor_cube; j++) {
            mv.translate(0,0,+2*j);
            //  Set Modelview and Projection Matrix
            shader[SKYBOX][FLOOR]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
            shader[SKYBOX][FLOOR]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
            //KG Set View and Normal
            shader[SKYBOX][FLOOR]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
            shader[SKYBOX][FLOOR]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3

            //   Attribute 0: vertex coordinate (vec4) at offset 0
            shader[SKYBOX][SKYBOX]->enableAttributeArray(0);
            shader[SKYBOX][SKYBOX]->setAttributeBuffer(0,GL_FLOAT,(0)*sizeof(float),4,12*sizeof(float));
            //   Attribute 2:  vertex normal (vec3) offset 4 floats
            shader[SKYBOX][SKYBOX]->enableAttributeArray(1);
            shader[SKYBOX][SKYBOX]->setAttributeBuffer(1,GL_FLOAT,(4)*sizeof(float),3,12*sizeof(float));
            //   Attribute 3:  texture coor 2d (vec2) offset 7 floats
            shader[SKYBOX][SKYBOX]->enableAttributeArray(2);
            shader[SKYBOX][SKYBOX]->setAttributeBuffer(2,GL_FLOAT,(10)*sizeof(float),2,12*sizeof(float));

            glDrawArrays(GL_TRIANGLES,C_TOP*6,cube_size/6);
            mv.translate(0,0,-2*j);
        }
        mv.translate(-(-(floor_cube-1.0)+2*i),0,-(-(floor_cube-1.0)));
    }

    /*
    grass[ROUGH]->bind();
    mv.scale(floor_cube,1,floor_cube);
    //  Set Modelview and Projection Matrix
    shader[SKYBOX][FLOOR]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
    shader[SKYBOX][FLOOR]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
    //KG Set View and Normal
    shader[SKYBOX][FLOOR]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
    shader[SKYBOX][FLOOR]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3

    //   Attribute 0: vertex coordinate (vec4) at offset 0
    shader[SKYBOX][SKYBOX]->enableAttributeArray(0);
    shader[SKYBOX][SKYBOX]->setAttributeBuffer(0,GL_FLOAT,(0)*sizeof(float),4,12*sizeof(float));
    //   Attribute 2:  vertex normal (vec3) offset 4 floats
    shader[SKYBOX][SKYBOX]->enableAttributeArray(1);
    shader[SKYBOX][SKYBOX]->setAttributeBuffer(1,GL_FLOAT,(4)*sizeof(float),3,12*sizeof(float));
    //   Attribute 3:  texture coor 2d (vec2) offset 7 floats
    shader[SKYBOX][SKYBOX]->enableAttributeArray(2);
    shader[SKYBOX][SKYBOX]->setAttributeBuffer(2,GL_FLOAT,(10)*sizeof(float),2,12*sizeof(float));

    glDrawArrays(GL_TRIANGLES,C_TOP*6,cube_size/6);

    mv.scale(1/floor_cube,1,1/floor_cube);
    */
    cube_buffer.release();
    mv.scale(1,1/.1,1);
    shader[SKYBOX][FLOOR]->release();

    //Flowers
    current_shader = 1;
    // Enable shader
    shader[current_shader][mode]->bind();
    //KG Set Light Position
    shader[current_shader][mode]->setUniformValue("light.ambient",QVector3D(0.3,0.3,0.3)); //Associate with light.ambient in vert (based on CUgl settings)
    shader[current_shader][mode]->setUniformValue("light.diffuse",QVector3D(1.0,1.0,1.0)); //Associate with light.diffuse in vert (based on CUgl settings)
    shader[current_shader][mode]->setUniformValue("light.emission",QVector3D(0.1,0.1,0.1)); //Associate with light.emission in vert
    shader[current_shader][mode]->setUniformValue("light.position",QVector3D(lpos.x(),lpos.y(),lpos.z())); //Associate with light.position in vert
    shader[current_shader][mode]->setUniformValue("light.shininess",16.0f); //Associate with light.shininess in vert
    shader[current_shader][mode]->setUniformValue("light.specular",QVector3D(1.0,1.0,1.0)); //Associate with light.specular in vert (based on CUgl settings)

    tex->bind();
    //qInfo() << season;
    for(int i = 0; i < NUM_FLOWERS-NUM_FLOWERS*.1; i++) {
        if(flower_data[i].draw > 0) {
            drawflower(current_shader, proj, view, mv,
                       flower_data[i].loc_x*floor_cube,flower_data[i].loc_y*floor_cube,flower_data[i].loc_z*floor_cube,
                       flower_data[i].rot_x,flower_data[i].rot_y,flower_data[i].rot_z,
                       flower_data[i].scl/3.0,flower_data[i].scl/3.0,flower_data[i].scl/3.0,
                       0,flower_data[i].color, flower_data[i].draw == 6 ? 1:0);
            if(flower_data[i].draw == 5) {
                int secf = flower_data[i].secondary_flower_number;
                //second flower drawn in the same area -- maybe even on top of the last one
                drawflower(current_shader, proj, view, mv,
                           flower_data[i].loc_x*floor_cube+flower_data[secf].loc_x,flower_data[i].loc_y*floor_cube+flower_data[secf].loc_y,flower_data[i].loc_z*floor_cube+flower_data[secf].loc_z,
                           flower_data[secf].rot_x,flower_data[secf].rot_y,flower_data[secf].rot_z,
                           flower_data[secf].scl/3.0,flower_data[secf].scl/3.0,flower_data[secf].scl/3.0,
                           0,flower_data[secf].color,0);
            }
        }
    }

    for(int i = 0; i < NUM_BFLOWERS-NUM_BFLOWERS*.1; i++) {
        if(burrflower_data[i].draw > 0) {
            drawburrflower(current_shader, proj, view, mv,
                       burrflower_data[i].loc_x*floor_cube-3.0,burrflower_data[i].loc_y*floor_cube,burrflower_data[i].loc_z*floor_cube-3.0,
                       burrflower_data[i].rot_x,burrflower_data[i].rot_y,burrflower_data[i].rot_z,
                       burrflower_data[i].scl/3.0,burrflower_data[i].scl/3.0,burrflower_data[i].scl/3.0,
                       0,burrflower_data[i].color);
            if(burrflower_data[i].draw == 2) {
                int secf = burrflower_data[i].secondary_flower_number;
                //second flower drawn in the same area -- maybe even on top of the last one
                drawburrflower(current_shader, proj, view, mv,
                           burrflower_data[i].loc_x*floor_cube-3.0+burrflower_data[secf].loc_x,burrflower_data[i].loc_y*floor_cube+burrflower_data[secf].loc_y,burrflower_data[i].loc_z*floor_cube-3.0+burrflower_data[secf].loc_z,
                           burrflower_data[secf].rot_x,burrflower_data[secf].rot_y,burrflower_data[secf].rot_z,
                           burrflower_data[secf].scl/3.0,burrflower_data[secf].scl/3.0,burrflower_data[secf].scl/3.0,
                           0,burrflower_data[secf].color);
            }
        }
    }

    for(int i = 0; i < NUM_SFLOWERS-NUM_SFLOWERS*.1; i++) {
        if(spikyflower_data[i].draw > 0) {
            drawspikyflower(current_shader, proj, view, mv,
                       spikyflower_data[i].loc_x*floor_cube-1.0,spikyflower_data[i].loc_y*floor_cube,spikyflower_data[i].loc_z*floor_cube-1.0,
                       spikyflower_data[i].rot_x,spikyflower_data[i].rot_y,spikyflower_data[i].rot_z,
                       spikyflower_data[i].scl/3.0,spikyflower_data[i].scl/3.0,spikyflower_data[i].scl/3.0,
                       spikyflower_data[i].color);
            if(spikyflower_data[i].draw == 3) {
                int secf = spikyflower_data[i].secondary_flower_number;
                //second flower drawn in the same area -- maybe even on top of the last one
                drawspikyflower(current_shader, proj, view, mv,
                           spikyflower_data[i].loc_x*floor_cube-1.0+spikyflower_data[secf].loc_x,spikyflower_data[i].loc_y*floor_cube+spikyflower_data[secf].loc_y,spikyflower_data[i].loc_z*floor_cube-1.0+spikyflower_data[secf].loc_z,
                           spikyflower_data[secf].rot_x,spikyflower_data[secf].rot_y,spikyflower_data[secf].rot_z,
                           spikyflower_data[secf].scl/3.0,spikyflower_data[secf].scl/3.0,spikyflower_data[secf].scl/3.0,
                           spikyflower_data[secf].color);
            }
        }
    }

    for(int i = 0; i < NUM_STONES; i++) {
        drawstone(current_shader, proj, view, mv,
                       stone_data[i].loc_x*floor_cube+2.0,stone_data[i].loc_y*floor_cube,stone_data[i].loc_z*floor_cube+2.0,
                       stone_data[i].rot_x,stone_data[i].rot_y,stone_data[i].rot_z,
                       stone_data[i].scl,stone_data[i].scl*3,stone_data[i].scl);
    }
    drawflower(current_shader, proj, view, mv,
             0,0,0, //xyz translate
             0,0,0, //xyz rotate
             1,1,1, //xyz scale
             0,BLUE,1);  //height and color
    shader[current_shader][mode]->release();
    //draw grass
    current_shader = 1;
    // Enable shader
    shader[current_shader][1]->bind();
    //KG Set Light Position
    shader[current_shader][1]->setUniformValue("light.ambient",QVector3D(0.3,0.3,0.3)); //Associate with light.ambient in vert (based on CUgl settings)
    shader[current_shader][1]->setUniformValue("light.diffuse",QVector3D(1.0,1.0,1.0)); //Associate with light.diffuse in vert (based on CUgl settings)
    shader[current_shader][1]->setUniformValue("light.emission",QVector3D(0.1,0.1,0.1)); //Associate with light.emission in vert
    shader[current_shader][1]->setUniformValue("light.position",QVector3D(lpos.x(),lpos.y(),lpos.z())); //Associate with light.position in vert
    shader[current_shader][1]->setUniformValue("light.shininess",16.0f); //Associate with light.shininess in vert
    shader[current_shader][1]->setUniformValue("light.specular",QVector3D(1.0,1.0,1.0)); //Associate with light.specular in vert (based on CUgl settings)

    for(int i = 0; i < NUM_FLOWERS-NUM_FLOWERS*.1; i++) {
        if((flower_data[i].draw >= 2 && flower_data[i].draw <= 4) || flower_data[i].draw == 0) {
            drawgrass(current_shader, proj, view, mv,
                       flower_data[i].loc_x*floor_cube,flower_data[i].loc_y*floor_cube,flower_data[i].loc_z*floor_cube,
                       flower_data[i].rot_x,flower_data[i].rot_y,flower_data[i].rot_z,
                       flower_data[i].scl/3.0,flower_data[i].scl/3.0,flower_data[i].scl/3.0,
                       flower_data[i].color);
        }
    }

    for(int i = 0; i < NUM_BFLOWERS-NUM_BFLOWERS*.1; i++) {
        if(burrflower_data[i].draw == 2) {
            drawgrass(current_shader, proj, view, mv,
                       burrflower_data[i].loc_x*floor_cube-3.0,burrflower_data[i].loc_y*floor_cube,burrflower_data[i].loc_z*floor_cube-3.0,
                       burrflower_data[i].rot_x,burrflower_data[i].rot_y,burrflower_data[i].rot_z,
                       burrflower_data[i].scl/3.0,burrflower_data[i].scl/3.0,burrflower_data[i].scl/3.0,
                       burrflower_data[i].color);
        }
    }

    for(int i = 0; i < NUM_SFLOWERS-NUM_SFLOWERS*.1; i++) {
        if(spikyflower_data[i].draw == 2) {
            drawgrass(current_shader, proj, view, mv,
                       spikyflower_data[i].loc_x*floor_cube-1.0,spikyflower_data[i].loc_y*floor_cube,spikyflower_data[i].loc_z*floor_cube-1.0,
                       spikyflower_data[i].rot_x,spikyflower_data[i].rot_y,spikyflower_data[i].rot_z,
                       spikyflower_data[i].scl,spikyflower_data[i].scl,spikyflower_data[i].scl,
                       spikyflower_data[i].color);
        }
    }
    for(int i = 0; i < NUM_TREES; i++) {
        drawgrass(current_shader, proj, view, mv,
                  tree_data[i].loc_x*floor_cube,tree_data[i].loc_y*floor_cube,tree_data[i].loc_z*floor_cube,
                  tree_data[i].rot_x,tree_data[i].rot_y,tree_data[i].rot_z,
                  tree_data[i].scl_x*6,tree_data[i].scl_y,tree_data[i].scl_z*6,
                  tree_data[i].color);

    }
    shader[current_shader][1]->release();

    current_shader = 1;
    shader[current_shader][4]->bind();

    shader[current_shader][4]->setUniformValue("light.ambient",QVector3D(0.3,0.3,0.3)); //Associate with light.ambient in vert (based on CUgl settings)
    shader[current_shader][4]->setUniformValue("light.diffuse",QVector3D(1.0,1.0,1.0)); //Associate with light.diffuse in vert (based on CUgl settings)
    shader[current_shader][4]->setUniformValue("light.emission",QVector3D(0.1,0.1,0.1)); //Associate with light.emission in vert
    shader[current_shader][4]->setUniformValue("light.position",QVector3D(lpos.x(),lpos.y(),lpos.z())); //Associate with light.position in vert
    shader[current_shader][4]->setUniformValue("light.shininess",16.0f); //Associate with light.shininess in vert
    shader[current_shader][4]->setUniformValue("light.specular",QVector3D(1.0,1.0,1.0)); //Associate with light.specular in vert (based on CUgl settings)

    for(int i = 0; i < NUM_TREES; i++) {
        if(tree_data[i].draw > 0) {
            drawtree(current_shader, proj, view, mv,
                       tree_data[i].loc_x*floor_cube,tree_data[i].loc_y*floor_cube,tree_data[i].loc_z*floor_cube,
                       tree_data[i].rot_x,tree_data[i].rot_z,
                       tree_data[i].scl_x,tree_data[i].scl_y,tree_data[i].scl_z,
                       tree_data[i].height, BROWN, tree_data[i].color);
        }
    }
    shader[current_shader][4]->release();

    /*//  Axes for reference
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(2,0,0);
    glVertex3f(0,0,0);
    glVertex3f(0,2,0);
    glVertex3f(0,0,0);
    glVertex3f(0,0,2);
    glEnd();*/
}
