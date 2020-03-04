HEADERS = ex07viewer.h ex07opengl.h CUgl.h Object.h Type.h
SOURCES = ex07.cpp ex07viewer.cpp ex07opengl.cpp CUgl.cpp Object.cpp
QT += opengl
RESOURCES = ex07.qrc
win32:{LIBS += -lopengl32}
