//
//  OpenGL Renderer
//
//  Base class for both OpenGL ES 1.1 and OpenGL ES 2.0
//
#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

//
//  Base OpenGL ES renderer class
//  Virtual method must be reimplemented for ES 1.1 and ES 2.0
//
class RenderingEngine
{
private:
   double t0; //  Keep track of time
public:
   virtual void Initialize(int width,int height) = 0;    //  Initialize to this size
   virtual void Display(double t) = 0;                   //  Display the scene
   virtual ~RenderingEngine() {}                         //  Destructor is virtual
   void UpdateAnimation(double t);                       //  Set current angle in animation
   void OnRotate(int angle);                             //  Set destination angle for animation
private:
   float RotationDirection() const;                      //  Helper to decide rotation direction
protected:
   float desiredAngle;                                   //  Desired up angle
   float currentAngle;                                   //  Current up angle (changed in animation)
   unsigned int renderbuffer;                            //  Render buffer name
};

// Create an instance of the renderer and set up various OpenGL state.
RenderingEngine* CreateRenderer1();  // OpenGL ES 1.1
RenderingEngine* CreateRenderer2();  // OpenGL ES 2.0

#endif
