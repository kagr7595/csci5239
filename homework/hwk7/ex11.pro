HEADERS = ex11viewer.h ex11opengl.h Type.h Object.h Cube.h Sphere.h Teapot.h WaveOBJ.h CUgl.h
SOURCES = ex11.cpp ex11viewer.cpp ex11opengl.cpp Object.cpp Cube.cpp Sphere.cpp Teapot.cpp WaveOBJ.cpp CUgl.cpp
QT += opengl
RESOURCES = ex11.qrc
win32:{LIBS += -lopengl32}
