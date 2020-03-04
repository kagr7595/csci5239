HEADERS = ex19viewer.h ex19opengl.h CUgl.h Noise.h Type.h Object.h
SOURCES = ex19.cpp ex19viewer.cpp ex19opengl.cpp CUgl.cpp Noise.cpp Object.cpp
QT += opengl
RESOURCES = ex19.qrc
win32:{LIBS += -lopengl32}
