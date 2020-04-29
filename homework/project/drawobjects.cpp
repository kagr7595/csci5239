#include "objectparts.cpp"

void Fprojopengl::drawflower(int pshader, QMatrix4x4 proj, QMatrix4x4 view, QMatrix4x4 mv,
                             float x_t, float y_t, float z_t,
                             float x_r, float y_r, float z_r,
                             float x_s, float y_s, float z_s,
                             float height, int color, int special)
{
    //  Select cube buffer
    flat_leaf_buffer.bind();
    //   Attribute 0: vertex coordinate (vec4) at offset 0
    shader[pshader][mode]->enableAttributeArray(0);
    shader[pshader][mode]->setAttributeBuffer(0,GL_FLOAT,0,4,12*sizeof(float));
    //   Attribute 1:  vertex color (vec3) offset 7 floats
    shader[pshader][mode]->enableAttributeArray(1);
    shader[pshader][mode]->setAttributeBuffer(1,GL_FLOAT,7*sizeof(float),3,12*sizeof(float));
    //   Attribute 2:  vertex normal (vec3) offset 4 floats
    shader[pshader][mode]->enableAttributeArray(2);
    shader[pshader][mode]->setAttributeBuffer(2,GL_FLOAT,4*sizeof(float),3,12*sizeof(float));
    //   Attribute 3:  texture coor 2d (vec2) offset 10 floats
    shader[pshader][mode]->enableAttributeArray(3);
    shader[pshader][mode]->setAttributeBuffer(3,GL_FLOAT,10*sizeof(float),2,12*sizeof(float));


    mv.translate(x_t,y_t,z_t);
    mv.scale(x_s,y_s,z_s);

    //Set the stem
    shader[pshader][mode]->setUniformValue("currently_leaf",0);
    shader[pshader][mode]->setUniformValue("currently_petal",0);
    mv.rotate(90.0,0.0,0.0,1.0);
    mv.scale(.4+height,.05,.5);
    //  Set Modelview and Projection Matrix
    shader[pshader][mode]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
    shader[pshader][mode]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
    //KG Set View and Normal
    shader[pshader][mode]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
    shader[pshader][mode]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3
    glDrawArrays(GL_TRIANGLES,0,flat_leaf_size);
    mv.scale(1/(.4+height), 1/.05, 1/.5);
    mv.rotate(-90.0,0.0,0.0,1.0);

    //set the leaves
    shader[pshader][mode]->setUniformValue("currently_leaf",1);
    shader[pshader][mode]->setUniformValue("special",special);
    shader[pshader][mode]->setUniformValue("time",zh);
    for(int i = 0; i < 6; i++) {
        mv.translate(0,((.4+height)/2.0+i*((.4+height)/12.0))*11.5,0);
        mv.scale(.05,.05,.05);
        mv.rotate(90.0,1.0,0.0,0.0);
        mv.rotate(120.0*i,0.0,0.0,1.0);

        //  Set Modelview and Projection Matrix
        shader[pshader][mode]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
        shader[pshader][mode]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
        //KG Set View and Normal
        shader[pshader][mode]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
        shader[pshader][mode]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3
        glDrawArrays(GL_TRIANGLES,0,flat_leaf_size);

        mv.rotate(-120.0*i,0.0,0.0,1.0);
        mv.rotate(-90.0,1.0,0.0,0.0);
        mv.scale(1/.05,1/.05,1/.05);

        mv.translate(0,-((.4+height)/2.0+i*((.4+height)/12.0))*11.5,0);
    }

    //Set the petal
    shader[pshader][mode]->setUniformValue("currently_leaf",0);
    shader[pshader][mode]->setUniformValue("currently_petal",1);
    QVector3D color_vec = colorvec(color);
    shader[pshader][mode]->setUniformValue("petal.color",color_vec);
    mv.translate(0,(.4+height)*11.5,0);
    if(x_r != 0){
        mv.rotate(x_r,1.0,0.0,0.0);
    }
    if(y_r != 0){
        mv.rotate(y_r,0.0,1.0,0.0);
    }
    if(z_r != 0){
        mv.rotate(z_r,0.0,0.0,1.0);
    }
    if(color == 1)
    {}
    mv.scale(.1,.1,.1);
    mv.rotate(90.0,1.0,0.0,0.0);
    for(int i = 0; i< 5; i++) {
      for(int j = 0; j< 8; j++) {
          mv.scale(1.00-i*.05,1.00-i*.05,1.00-i*.05);
          mv.rotate(45*j+i*22.5,0.0,0.0,1.0);
          mv.rotate(15.0*i,0.0,1.0,0.0);

          //  Set Modelview and Projection Matrix
          shader[pshader][mode]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
          shader[pshader][mode]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
          //KG Set View and Normal
          shader[pshader][mode]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
          shader[pshader][mode]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3
          glDrawArrays(GL_TRIANGLES,0,flat_leaf_size);
          mv.rotate(-15.0*i,0.0,1.0,0.0);
          mv.rotate(-(45*j+i*22.5),0.0,0.0,1.0);
          mv.scale(1.00+i*.05,1.00+i*.05,1.00+i*.05);
      }
    }

    shader[pshader][mode]->setUniformValue("currently_petal",0);
    shader[pshader][mode]->setUniformValue("special",0);


    //  Disable vertex arrays
    shader[pshader][mode]->disableAttributeArray(0);
    shader[pshader][mode]->disableAttributeArray(1);
    shader[pshader][mode]->disableAttributeArray(2);
    shader[pshader][mode]->disableAttributeArray(3);

    //  Unbind this buffer
    flat_leaf_buffer.release();
};

void Fprojopengl::drawspikyflower(int pshader, QMatrix4x4 proj, QMatrix4x4 view, QMatrix4x4 mv,
                             float x_t, float y_t, float z_t,
                             float x_r, float y_r, float z_r,
                             float x_s, float y_s, float z_s,
                             int color)
{
    //  Select cube buffer
    cylinder_buffer.bind();
    //   Attribute 0: vertex coordinate (vec4) at offset 0
    shader[pshader][mode]->enableAttributeArray(0);
    shader[pshader][mode]->setAttributeBuffer(0,GL_FLOAT,0,4,12*sizeof(float));
    //   Attribute 1:  vertex color (vec3) offset 7 floats
    shader[pshader][mode]->enableAttributeArray(1);
    shader[pshader][mode]->setAttributeBuffer(1,GL_FLOAT,7*sizeof(float),3,12*sizeof(float));
    //   Attribute 2:  vertex normal (vec3) offset 4 floats
    shader[pshader][mode]->enableAttributeArray(2);
    shader[pshader][mode]->setAttributeBuffer(2,GL_FLOAT,4*sizeof(float),3,12*sizeof(float));
    //   Attribute 3:  texture coor 2d (vec2) offset 10 floats
    shader[pshader][mode]->enableAttributeArray(3);
    shader[pshader][mode]->setAttributeBuffer(3,GL_FLOAT,10*sizeof(float),2,12*sizeof(float));


    mv.translate(x_t,y_t,z_t);
    mv.scale(x_s,y_s,z_s);

    //Set the stem
    shader[pshader][mode]->setUniformValue("currently_leaf",0);
    shader[pshader][mode]->setUniformValue("currently_petal",0);
    QVector3D color_vec = colorvec(BROWN);
    shader[pshader][mode]->setUniformValue("petal.color",color_vec);
    mv.scale(.05,2.2,.05);
    //  Set Modelview and Projection Matrix
    shader[pshader][mode]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
    shader[pshader][mode]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
    //KG Set View and Normal
    shader[pshader][mode]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
    shader[pshader][mode]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3
    glDrawArrays(GL_TRIANGLES,0,flat_leaf_size);
    mv.scale(1/.05,1/(2.2),1/.05);

    //  Disable vertex arrays
    shader[pshader][mode]->disableAttributeArray(0);
    shader[pshader][mode]->disableAttributeArray(1);
    shader[pshader][mode]->disableAttributeArray(2);
    shader[pshader][mode]->disableAttributeArray(3);
    cylinder_buffer.release();


    //set the leaves
    flat_leaf_buffer.bind();
    //   Attribute 0: vertex coordinate (vec4) at offset 0
    shader[pshader][mode]->enableAttributeArray(0);
    shader[pshader][mode]->setAttributeBuffer(0,GL_FLOAT,0,4,12*sizeof(float));
    //   Attribute 1:  vertex color (vec3) offset 7 floats
    shader[pshader][mode]->enableAttributeArray(1);
    shader[pshader][mode]->setAttributeBuffer(1,GL_FLOAT,7*sizeof(float),3,12*sizeof(float));
    //   Attribute 2:  vertex normal (vec3) offset 4 floats
    shader[pshader][mode]->enableAttributeArray(2);
    shader[pshader][mode]->setAttributeBuffer(2,GL_FLOAT,4*sizeof(float),3,12*sizeof(float));
    //   Attribute 3:  texture coor 2d (vec2) offset 10 floats
    shader[pshader][mode]->enableAttributeArray(3);
    shader[pshader][mode]->setAttributeBuffer(3,GL_FLOAT,10*sizeof(float),2,12*sizeof(float));


    shader[pshader][mode]->setUniformValue("currently_leaf",1);
    color_vec = colorvec(color);
    shader[pshader][mode]->setUniformValue("petal.color",color_vec);
    for(int i = 0; i < 2; i++) {
        mv.translate(0,((.4)/2.0+i*((.4)/12.0))*5.5,0);
        mv.scale(.05,.1,.15);
        mv.rotate(90.0,1.0,0.0,0.0);
        mv.rotate(180.0*i,0.0,0.0,1.0);

        //  Set Modelview and Projection Matrix
        shader[pshader][mode]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
        shader[pshader][mode]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
        //KG Set View and Normal
        shader[pshader][mode]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
        shader[pshader][mode]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3
        glDrawArrays(GL_TRIANGLES,0,flat_leaf_size);

        mv.rotate(-180.0*i,0.0,0.0,1.0);
        mv.rotate(-90.0,1.0,0.0,0.0);
        mv.scale(1/.05,1/.1,1/.15);

        mv.translate(0,-((.4)/2.0+i*((.4)/12.0))*5.5,0);
    }

    //  Disable vertex arrays
    shader[pshader][mode]->disableAttributeArray(0);
    shader[pshader][mode]->disableAttributeArray(1);
    shader[pshader][mode]->disableAttributeArray(2);
    shader[pshader][mode]->disableAttributeArray(3);
    flat_leaf_buffer.release();

    //Set the petal
    sharp_circle_flower_buffer.bind();
    //   Attribute 0: vertex coordinate (vec4) at offset 0
    shader[pshader][1]->enableAttributeArray(0);
    shader[pshader][1]->setAttributeBuffer(0,GL_FLOAT,0,4,12*sizeof(float));
    //   Attribute 1:  vertex color (vec3) offset 7 floats
    shader[pshader][1]->enableAttributeArray(1);
    shader[pshader][1]->setAttributeBuffer(1,GL_FLOAT,7*sizeof(float),3,12*sizeof(float));
    //   Attribute 2:  vertex normal (vec3) offset 4 floats
    shader[pshader][1]->enableAttributeArray(2);
    shader[pshader][1]->setAttributeBuffer(2,GL_FLOAT,4*sizeof(float),3,12*sizeof(float));
    //   Attribute 3:  texture coor 2d (vec2) offset 10 floats
    shader[pshader][1]->enableAttributeArray(3);
    shader[pshader][1]->setAttributeBuffer(3,GL_FLOAT,10*sizeof(float),2,12*sizeof(float));


    shader[pshader][mode]->setUniformValue("currently_leaf",0);
    shader[pshader][mode]->setUniformValue("currently_petal",1);
    color_vec = colorvec(color);
    shader[pshader][mode]->setUniformValue("petal.color",color_vec);
    mv.translate(0,(.4)*5.5,0);
    if(x_r != 0){
        mv.rotate(x_r,1.0,0.0,0.0);
    }
    if(y_r != 0){
        mv.rotate(y_r,0.0,1.0,0.0);
    }
    if(z_r != 0){
        mv.rotate(z_r,0.0,0.0,1.0);
    }
    if(color == 1)
    {}
    mv.scale(.2,.2,.2);

    //  Set Modelview and Projection Matrix
    shader[pshader][mode]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
    shader[pshader][mode]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
    //KG Set View and Normal
    shader[pshader][mode]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
    shader[pshader][mode]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3
    glDrawArrays(GL_TRIANGLES,0,flat_leaf_size);

    shader[pshader][mode]->setUniformValue("currently_petal",0);


    //  Disable vertex arrays
    shader[pshader][mode]->disableAttributeArray(0);
    shader[pshader][mode]->disableAttributeArray(1);
    shader[pshader][mode]->disableAttributeArray(2);
    shader[pshader][mode]->disableAttributeArray(3);

    //  Unbind this buffer
    sharp_circle_flower_buffer.release();
};

void Fprojopengl::drawburrflower(int pshader, QMatrix4x4 proj, QMatrix4x4 view, QMatrix4x4 mv,
                             float x_t, float y_t, float z_t,
                             float x_r, float y_r, float z_r,
                             float x_s, float y_s, float z_s,
                             float height, int color)
{
    //  Select cube buffer
    flat_leaf_buffer.bind();
    //   Attribute 0: vertex coordinate (vec4) at offset 0
    shader[pshader][mode]->enableAttributeArray(0);
    shader[pshader][mode]->setAttributeBuffer(0,GL_FLOAT,0,4,12*sizeof(float));
    //   Attribute 1:  vertex color (vec3) offset 7 floats
    shader[pshader][mode]->enableAttributeArray(1);
    shader[pshader][mode]->setAttributeBuffer(1,GL_FLOAT,7*sizeof(float),3,12*sizeof(float));
    //   Attribute 2:  vertex normal (vec3) offset 4 floats
    shader[pshader][mode]->enableAttributeArray(2);
    shader[pshader][mode]->setAttributeBuffer(2,GL_FLOAT,4*sizeof(float),3,12*sizeof(float));
    //   Attribute 3:  texture coor 2d (vec2) offset 10 floats
    shader[pshader][mode]->enableAttributeArray(3);
    shader[pshader][mode]->setAttributeBuffer(3,GL_FLOAT,10*sizeof(float),2,12*sizeof(float));


    mv.translate(x_t,y_t,z_t);
    mv.scale(x_s,y_s,z_s);

    //Set the stem
    shader[pshader][mode]->setUniformValue("currently_leaf",0);
    shader[pshader][mode]->setUniformValue("currently_petal",0);
    QVector3D color_vec = colorvec(BROWN);
    shader[pshader][mode]->setUniformValue("petal.color",color_vec);
    mv.rotate(90.0,0.0,0.0,1.0);
    mv.scale(.45+height,.05,.4);
    //  Set Modelview and Projection Matrix
    shader[pshader][mode]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
    shader[pshader][mode]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
    //KG Set View and Normal
    shader[pshader][mode]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
    shader[pshader][mode]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3
    glDrawArrays(GL_TRIANGLES,0,flat_leaf_size);
    mv.scale(1/(.45+height), 1/.05, 1/.4);
    mv.rotate(-90.0,0.0,0.0,1.0);

    //set the leaves
    shader[pshader][mode]->setUniformValue("currently_leaf",1);
    color_vec = colorvec(GREEN);
    shader[pshader][mode]->setUniformValue("petal.color",color_vec);
    for(int i = 0; i < 4; i++) {
        mv.translate(0,((.43+height)/2.0+i*((.4+height)/12.0))*11.5,0);
        mv.scale(.05,.05,.05);
        mv.rotate(90.0,1.0,0.0,0.0);
        mv.rotate(180.0*i,0.0,0.0,1.0);

        //  Set Modelview and Projection Matrix
        shader[pshader][mode]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
        shader[pshader][mode]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
        //KG Set View and Normal
        shader[pshader][mode]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
        shader[pshader][mode]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3
        glDrawArrays(GL_TRIANGLES,0,flat_leaf_size);

        mv.rotate(-180.0*i,0.0,0.0,1.0);
        mv.rotate(-90.0,1.0,0.0,0.0);
        mv.scale(1/.05,1/.05,1/.05);

        mv.translate(0,-((.43+height)/2.0+i*((.4+height)/12.0))*11.5,0);
    }

    //  Disable vertex arrays
    shader[pshader][mode]->disableAttributeArray(0);
    shader[pshader][mode]->disableAttributeArray(1);
    shader[pshader][mode]->disableAttributeArray(2);
    shader[pshader][mode]->disableAttributeArray(3);
    flat_leaf_buffer.release();

    sharp_circle_flower_buffer.bind();

    //   Attribute 0: vertex coordinate (vec4) at offset 0
    shader[pshader][1]->enableAttributeArray(0);
    shader[pshader][1]->setAttributeBuffer(0,GL_FLOAT,0,4,12*sizeof(float));
    //   Attribute 1:  vertex color (vec3) offset 7 floats
    shader[pshader][1]->enableAttributeArray(1);
    shader[pshader][1]->setAttributeBuffer(1,GL_FLOAT,7*sizeof(float),3,12*sizeof(float));
    //   Attribute 2:  vertex normal (vec3) offset 4 floats
    shader[pshader][1]->enableAttributeArray(2);
    shader[pshader][1]->setAttributeBuffer(2,GL_FLOAT,4*sizeof(float),3,12*sizeof(float));
    //   Attribute 3:  texture coor 2d (vec2) offset 10 floats
    shader[pshader][1]->enableAttributeArray(3);
    shader[pshader][1]->setAttributeBuffer(3,GL_FLOAT,10*sizeof(float),2,12*sizeof(float));
    //Set the petal
    shader[pshader][mode]->setUniformValue("currently_leaf",0);
    shader[pshader][mode]->setUniformValue("currently_petal",1);
    color_vec = colorvec(color);
    shader[pshader][mode]->setUniformValue("petal.color",color_vec);
    mv.translate(0,(.4+height)*11.5,0);
    if(x_r != 0){
        mv.rotate(x_r,1.0,0.0,0.0);
    }
    if(y_r != 0){
        mv.rotate(y_r,0.0,1.0,0.0);
    }
    if(z_r != 0){
        mv.rotate(z_r,0.0,0.0,1.0);
    }
    if(color == 1)
    {}
    mv.scale(.1,.1,.1);
    mv.rotate(90.0,1.0,0.0,0.0);
    for(int i = 0; i< 3; i++) {
      for(int j = 0; j< 4; j++) {
          mv.scale(1.00-i*.05,1.00-i*.05,1.00-i*.05);
          mv.rotate(45*j+i*22.5,0.0,0.0,1.0);
          mv.rotate(15.0*i,0.0,1.0,0.0);

          //  Set Modelview and Projection Matrix
          shader[pshader][mode]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
          shader[pshader][mode]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
          //KG Set View and Normal
          shader[pshader][mode]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
          shader[pshader][mode]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3
          glDrawArrays(GL_TRIANGLES,0,sharp_circle_flower_size);
          mv.rotate(-15.0*i,0.0,1.0,0.0);
          mv.rotate(-(45*j+i*22.5),0.0,0.0,1.0);
          mv.scale(1.00+i*.05,1.00+i*.05,1.00+i*.05);
      }
    }

    mv.rotate(-90.0,1.0,0.0,0.0);
    mv.scale(1/.1,1/.1,1/.1);
    if(z_r != 0){
        mv.rotate(-z_r,0.0,0.0,1.0);
    }
    if(y_r != 0){
        mv.rotate(-y_r,0.0,1.0,0.0);
    }
    if(x_r != 0){
        mv.rotate(-x_r,1.0,0.0,0.0);
    }
    mv.translate(0,-(.4+height)*11.5,0);

    mv.translate(0,(.42+height)*11.5,0);
    if(x_r != 0){
        mv.rotate(x_r,1.0,0.0,0.0);
    }
    if(y_r != 0){
        mv.rotate(y_r,0.0,1.0,0.0);
    }
    if(z_r != 0){
        mv.rotate(z_r,0.0,0.0,1.0);
    }
    if(color == 1)
    {}
    mv.scale(.1,.1,.1);
    mv.rotate(90.0,1.0,0.0,0.0);
    for(int i = 0; i< 3; i++) {
      for(int j = 0; j< 4; j++) {
          mv.scale(1.00-i*.05,1.00-i*.05,1.00-i*.05);
          mv.rotate(45*j+i*22.5,0.0,0.0,1.0);
          mv.rotate(15.0*i,0.0,1.0,0.0);

          //  Set Modelview and Projection Matrix
          shader[pshader][mode]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
          shader[pshader][mode]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
          //KG Set View and Normal
          shader[pshader][mode]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
          shader[pshader][mode]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3
          glDrawArrays(GL_TRIANGLES,0,sharp_circle_flower_size);
          mv.rotate(-15.0*i,0.0,1.0,0.0);
          mv.rotate(-(45*j+i*22.5),0.0,0.0,1.0);
          mv.scale(1.00+i*.05,1.00+i*.05,1.00+i*.05);
      }
    }

    mv.rotate(-90.0,1.0,0.0,0.0);
    mv.scale(1/.1,1/.1,1/.1);
    if(z_r != 0){
        mv.rotate(-z_r,0.0,0.0,1.0);
    }
    if(y_r != 0){
        mv.rotate(-y_r,0.0,1.0,0.0);
    }
    if(x_r != 0){
        mv.rotate(-x_r,1.0,0.0,0.0);
    }
    mv.translate(0,-(.42+height)*11.5,0);

    mv.translate(0,(.44+height)*11.5,0);
    if(x_r != 0){
        mv.rotate(x_r,1.0,0.0,0.0);
    }
    if(y_r != 0){
        mv.rotate(y_r,0.0,1.0,0.0);
    }
    if(z_r != 0){
        mv.rotate(z_r,0.0,0.0,1.0);
    }
    if(color == 1)
    {}
    mv.scale(.1,.1,.1);
    mv.rotate(90.0,1.0,0.0,0.0);
    for(int i = 0; i< 3; i++) {
      for(int j = 0; j< 4; j++) {
          mv.scale(1.00-i*.05,1.00-i*.05,1.00-i*.05);
          mv.rotate(45*j+i*22.5,0.0,0.0,1.0);
          mv.rotate(15.0*i,0.0,1.0,0.0);

          //  Set Modelview and Projection Matrix
          shader[pshader][mode]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
          shader[pshader][mode]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
          //KG Set View and Normal
          shader[pshader][mode]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
          shader[pshader][mode]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3
          glDrawArrays(GL_TRIANGLES,0,sharp_circle_flower_size);
          mv.rotate(-15.0*i,0.0,1.0,0.0);
          mv.rotate(-(45*j+i*22.5),0.0,0.0,1.0);
          mv.scale(1.00+i*.05,1.00+i*.05,1.00+i*.05);
      }
    }


    shader[pshader][mode]->setUniformValue("currently_petal",0);


    //  Disable vertex arrays
    shader[pshader][mode]->disableAttributeArray(0);
    shader[pshader][mode]->disableAttributeArray(1);
    shader[pshader][mode]->disableAttributeArray(2);
    shader[pshader][mode]->disableAttributeArray(3);

    //  Unbind this buffer
    sharp_circle_flower_buffer.release();
};


void Fprojopengl::drawgrass(int pshader, QMatrix4x4 proj, QMatrix4x4 view, QMatrix4x4 mv,
                             float x_t, float y_t, float z_t,
                             float x_r, float y_r, float z_r,
                             float x_s, float y_s, float z_s,
                             int color)
{
    //  Select cube buffer
    flat_leaf_buffer.bind();
    //   Attribute 0: vertex coordinate (vec4) at offset 0
    shader[pshader][1]->enableAttributeArray(0);
    shader[pshader][1]->setAttributeBuffer(0,GL_FLOAT,0,4,12*sizeof(float));
    //   Attribute 1:  vertex color (vec3) offset 7 floats
    shader[pshader][1]->enableAttributeArray(1);
    shader[pshader][1]->setAttributeBuffer(1,GL_FLOAT,7*sizeof(float),3,12*sizeof(float));
    //   Attribute 2:  vertex normal (vec3) offset 4 floats
    shader[pshader][1]->enableAttributeArray(2);
    shader[pshader][1]->setAttributeBuffer(2,GL_FLOAT,4*sizeof(float),3,12*sizeof(float));
    //   Attribute 3:  texture coor 2d (vec2) offset 10 floats
    shader[pshader][1]->enableAttributeArray(3);
    shader[pshader][1]->setAttributeBuffer(3,GL_FLOAT,10*sizeof(float),2,12*sizeof(float));


    mv.translate(x_t,y_t,z_t);
    mv.scale(x_s,y_s,z_s);


    //grass shader
    shader[pshader][1]->setUniformValue("currently_leaf",1);
    for(int i = 0; i < 6; i++) {
        mv.scale(.05,.05,.05);
        mv.rotate(90.0,1.0,0.0,0.0);
        mv.rotate(120.0*i,0.0,0.0,1.0);

        //  Set Modelview and Projection Matrix
        shader[pshader][1]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
        shader[pshader][1]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
        //KG Set View and Normal
        shader[pshader][1]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
        shader[pshader][1]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3
        glDrawArrays(GL_TRIANGLES,0,flat_leaf_size);

        mv.rotate(-120.0*i,0.0,0.0,1.0);
        mv.rotate(-90.0,1.0,0.0,0.0);
        mv.scale(1/.05,1/.05,1/.05);

    }

    //Set the petal
    shader[pshader][1]->setUniformValue("currently_leaf",0);
    shader[pshader][1]->setUniformValue("currently_petal",1);
    QVector3D color_vec = colorvec(color);
    shader[pshader][1]->setUniformValue("petal.color",color_vec);
    if(x_r != 0){
        mv.rotate(x_r,1.0,0.0,0.0);
    }
    if(y_r != 0){
        mv.rotate(y_r,0.0,1.0,0.0);
    }
    if(z_r != 0){
        mv.rotate(z_r,0.0,0.0,1.0);
    }
    if(color == 1)
    {}
    mv.scale(.1,.1,.1);
    mv.rotate(90.0,1.0,0.0,0.0);
    for(int i = 0; i< 5; i++) {
      for(int j = 0; j< 8; j++) {
          mv.scale(1.00-i*.05,1.00-i*.05,1.00-i*.05);
          mv.rotate(45*j+i*22.5,0.0,0.0,1.0);
          mv.rotate(15.0*i,0.0,1.0,0.0);

          //  Set Modelview and Projection Matrix
          shader[pshader][1]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
          shader[pshader][1]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
          //KG Set View and Normal
          shader[pshader][1]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
          shader[pshader][1]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3
          glDrawArrays(GL_TRIANGLES,0,flat_leaf_size);
          mv.rotate(-15.0*i,0.0,1.0,0.0);
          mv.rotate(-(45*j+i*22.5),0.0,0.0,1.0);
          mv.scale(1.00+i*.05,1.00+i*.05,1.00+i*.05);
      }
    }

    shader[pshader][1]->setUniformValue("currently_petal",0);


    //  Disable vertex arrays
    shader[pshader][1]->disableAttributeArray(0);
    shader[pshader][1]->disableAttributeArray(1);
    shader[pshader][1]->disableAttributeArray(2);
    shader[pshader][1]->disableAttributeArray(3);

    //  Unbind this buffer
    flat_leaf_buffer.release();
};



void Fprojopengl::drawtree(int pshader, QMatrix4x4 proj, QMatrix4x4 view, QMatrix4x4 mv,
                             float x_t, float y_t, float z_t,
                             float x_r, float z_r,
                             float x_s, float y_s, float z_s,
                             float height, int color_trunk, int color_branch)
{
    //  Select cube buffer
    cylinder_buffer.bind();
    //   Attribute 0: vertex coordinate (vec4) at offset 0
    shader[pshader][4]->enableAttributeArray(0);
    shader[pshader][4]->setAttributeBuffer(0,GL_FLOAT,0,4,12*sizeof(float));
    //   Attribute 1:  vertex color (vec3) offset 7 floats
    shader[pshader][4]->enableAttributeArray(1);
    shader[pshader][4]->setAttributeBuffer(1,GL_FLOAT,7*sizeof(float),3,12*sizeof(float));
    //   Attribute 2:  vertex normal (vec3) offset 4 floats
    shader[pshader][4]->enableAttributeArray(2);
    shader[pshader][4]->setAttributeBuffer(2,GL_FLOAT,4*sizeof(float),3,12*sizeof(float));
    //   Attribute 3:  texture coor 2d (vec2) offset 10 floats
    shader[pshader][4]->enableAttributeArray(3);
    shader[pshader][4]->setAttributeBuffer(3,GL_FLOAT,10*sizeof(float),2,12*sizeof(float));


    mv.translate(x_t,y_t,z_t);
    mv.scale(x_s,y_s,z_s);

    //Set the trunk
    shader[pshader][4]->setUniformValue("currently_trunk",1);
    QVector3D color_vec = colorvec(color_trunk);
    shader[pshader][4]->setUniformValue("ocolor",color_vec);
    mv.scale(.3,7.5+height,.3);
    //  Set 4lview and Projection Matrix
    shader[pshader][4]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
    shader[pshader][4]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
    //KG Set View and Normal
    shader[pshader][4]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
    shader[pshader][4]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3
    glDrawArrays(GL_TRIANGLES,0,cylinder_size);
    mv.scale(1/.3, 1/(7.5+height), 1/.3);

    //  Disable vertex arrays
    shader[pshader][4]->disableAttributeArray(0);
    shader[pshader][4]->disableAttributeArray(1);
    shader[pshader][4]->disableAttributeArray(2);
    shader[pshader][4]->disableAttributeArray(3);
    cylinder_buffer.release();

    //  Select cube buffer
    cone_buffer.bind();
    //   Attribute 0: vertex coordinate (vec4) at offset 0
    shader[pshader][4]->enableAttributeArray(0);
    shader[pshader][4]->setAttributeBuffer(0,GL_FLOAT,0,4,12*sizeof(float));
    //   Attribute 1:  vertex color (vec3) offset 7 floats
    shader[pshader][4]->enableAttributeArray(1);
    shader[pshader][4]->setAttributeBuffer(1,GL_FLOAT,7*sizeof(float),3,12*sizeof(float));
    //   Attribute 2:  vertex normal (vec3) offset 4 floats
    shader[pshader][4]->enableAttributeArray(2);
    shader[pshader][4]->setAttributeBuffer(2,GL_FLOAT,4*sizeof(float),3,12*sizeof(float));
    //   Attribute 3:  texture coor 2d (vec2) offset 10 floats
    shader[pshader][4]->enableAttributeArray(3);
    shader[pshader][4]->setAttributeBuffer(3,GL_FLOAT,10*sizeof(float),2,12*sizeof(float));

    //set the tree branch/cones (three staggered)
    shader[pshader][4]->setUniformValue("currently_trunk",0);
    shader[pshader][4]->setUniformValue("num_branch",2);
    shader[pshader][4]->setUniformValue("mirror_branch",1);
    color_vec = colorvec(color_branch);
    shader[pshader][4]->setUniformValue("ocolor",color_vec);
    for(int i = 0; i < 3; i++) {
        mv.translate(0,((.4+height)/2.0+i*((1.5+height)/12.0))*11.5,0);
        mv.scale(2-.2*i,4-.2*i,2-.2*i);
        mv.rotate(i%2 ? x_r:-1*x_r,1.0,0.0,0.0);
        mv.rotate(i%2 ? z_r:-1*z_r,0.0,0.0,1.0);

        //  Set 4lview and Projection Matrix
        shader[pshader][4]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
        shader[pshader][4]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
        //KG Set View and Normal
        shader[pshader][4]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
        shader[pshader][4]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3
        glDrawArrays(GL_TRIANGLES,0,cone_size);

        mv.rotate(i%2 ? -1*z_r:z_r,0.0,0.0,1.0);
        mv.rotate(i%2 ? -1*x_r:x_r,1.0,0.0,0.0);
        mv.scale(1/(2-.2*i),1/(4-.2*i),1/(2-.2*i));
        mv.translate(0,-((.4+height)/2.0+i*((1.5+height)/12.0))*11.5,0);
    }

    shader[pshader][4]->setUniformValue("num_branch",0);
    shader[pshader][4]->setUniformValue("mirror_branch",0);
    //  Disable vertex arrays
    shader[pshader][4]->disableAttributeArray(0);
    shader[pshader][4]->disableAttributeArray(1);
    shader[pshader][4]->disableAttributeArray(2);
    shader[pshader][4]->disableAttributeArray(3);
    cone_buffer.release();

};


void Fprojopengl::drawstone(int pshader, QMatrix4x4 proj, QMatrix4x4 view, QMatrix4x4 mv,
                             float x_t, float y_t, float z_t,
                             float x_r, float y_r, float z_r,
                             float x_s, float y_s, float z_s)
{
    //  Select cube buffer
    cylinder_buffer.bind();
    //   Attribute 0: vertex coordinate (vec4) at offset 0
    shader[pshader][mode]->enableAttributeArray(0);
    shader[pshader][mode]->setAttributeBuffer(0,GL_FLOAT,0,4,12*sizeof(float));
    //   Attribute 1:  vertex color (vec3) offset 7 floats
    shader[pshader][mode]->enableAttributeArray(1);
    shader[pshader][mode]->setAttributeBuffer(1,GL_FLOAT,7*sizeof(float),3,12*sizeof(float));
    //   Attribute 2:  vertex normal (vec3) offset 4 floats
    shader[pshader][mode]->enableAttributeArray(2);
    shader[pshader][mode]->setAttributeBuffer(2,GL_FLOAT,4*sizeof(float),3,12*sizeof(float));
    //   Attribute 3:  texture coor 2d (vec2) offset 10 floats
    shader[pshader][mode]->enableAttributeArray(3);
    shader[pshader][mode]->setAttributeBuffer(3,GL_FLOAT,10*sizeof(float),2,12*sizeof(float));


    mv.translate(x_t,y_t,z_t);
    mv.scale(x_s,y_s,z_s);

    if(x_r != 0){
        mv.rotate(x_r,1.0,0.0,0.0);
    }
    if(y_r != 0){
        mv.rotate(y_r,0.0,1.0,0.0);
    }
    if(z_r != 0){
        mv.rotate(z_r,0.0,0.0,1.0);
    }
    shader[pshader][mode]->setUniformValue("currently_leaf",0);
    shader[pshader][mode]->setUniformValue("currently_petal",0);
    QVector3D color_vec = colorvec(BLACK);
    shader[pshader][mode]->setUniformValue("petal.color",color_vec);
    mv.scale(.3,.4,.5);
    //  Set Modelview and Projection Matrix
    shader[pshader][mode]->setUniformValue("ProjectionMatrix",proj); //QMatrix 4x4
    shader[pshader][mode]->setUniformValue("ModelViewMatrix",mv);  //QMatrix 4x4
    //KG Set View and Normal
    shader[pshader][mode]->setUniformValue("ViewMatrix",view); //QMatrix 4x4
    shader[pshader][mode]->setUniformValue("NormalMatrix",mv.normalMatrix()); //QMatrix  3x3
    glDrawArrays(GL_TRIANGLES,0,flat_leaf_size);
    mv.scale(1/.3,1/(.4),1/.5);

    //  Disable vertex arrays
    shader[pshader][mode]->disableAttributeArray(0);
    shader[pshader][mode]->disableAttributeArray(1);
    shader[pshader][mode]->disableAttributeArray(2);
    shader[pshader][mode]->disableAttributeArray(3);
    cylinder_buffer.release();

};
