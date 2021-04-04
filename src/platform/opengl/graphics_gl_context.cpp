#include "graphics_opengl.h"

using namespace GL;


void GLContext::Init(void* initData) 
{
    if (!initData) { printf("Please provide the GLADloadproc to the OpenGL context init"); return; }
    int gladStatus = gladLoadGLLoader((GLADloadproc)initData);
    printf("Glad Init Status: %d\n", gladStatus);
    printf("%s\n", glGetString(GL_VERSION));
}

void GLContext::Clear(float r, float g, float b, unsigned char GCLEAROPTIONS) 
{
    G_RENDERCMD4(r, g, b, GCLEAROPTIONS, {
        glCall(glClearColor(r, g, b, 1));
        glCall(glClear(GL_COLOR_BUFFER_BIT));
    })
}