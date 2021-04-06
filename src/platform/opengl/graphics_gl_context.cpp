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

void GLContext::DrawElements(size_t count, Graphics::GIndexType indexType, Graphics::GDrawMode drawMode) 
{
    G_RENDERCMD3(count, indexType, drawMode, {
        glCall(glDrawElements(DrawModeToOpenGLMode(drawMode), count, IndexTypeToOpenGLType(indexType), NULL));
    })
}

void GLContext::DrawArrays(size_t start, size_t count, Graphics::GDrawMode drawMode) 
{
    G_RENDERCMD3(start, count, drawMode, {
        glCall(glDrawArrays(DrawModeToOpenGLMode(drawMode), start, count));
    })
}