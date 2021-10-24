#include "graphics_opengl.h"

using namespace GL;


void GLContext::Init(void* initData) 
{
    int gladStatus = 0;
    if (initData)
    {
        gladStatus = gladLoadGLLoader((GLADloadproc)initData);
    }
    else
    {
        gladStatus = gladLoadGL();
    }
    printf("Glad Init Status: %d\n", gladStatus);
    printf("%s\n", glGetString(GL_VERSION));
    EnableDepthTest(true);
}

void GLContext::Clear(float r, float g, float b, unsigned char GCLEAROPTIONS) 
{
    GLuint clearOption = 0;
    clearOption |= GCLEAROPTIONS & GCLEAROPTION_COLOR_BUFFER ? GL_COLOR_BUFFER_BIT : 0;
    clearOption |= GCLEAROPTIONS & GCLEAROPTION_DEPTH_BUFFER ? GL_DEPTH_BUFFER_BIT : 0;
    clearOption |= GCLEAROPTIONS & GCLEAROPTION_STENCIL_BUFFER ? GL_STENCIL_BUFFER_BIT : 0;
    clearOption |= GCLEAROPTIONS & GCLEAROPTION_ACCUM_BUFFER ? GL_ACCUM_BUFFER_BIT : 0;
    glCall(glClearColor(r, g, b, 1));
        
    glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void GLContext::EnableDepthTest(bool enable)
{
    glCall(glDisable(GL_SCISSOR_TEST));
    if (fDepthTestEnabled)
    {
        glCall(glEnable(GL_DEPTH_TEST));
    }
    else
    {
        glCall(glDisable(GL_DEPTH_TEST));
    }
}

void GLContext::DrawElements(size_t count, Graphics::GIndexType indexType, Graphics::GDrawMode drawMode) 
{
    glCall(glDrawElements(DrawModeToOpenGLMode(drawMode), count, IndexTypeToOpenGLType(indexType), NULL));
}

void GLContext::DrawArrays(size_t start, size_t count, Graphics::GDrawMode drawMode) 
{
    glCall(glDrawArrays(DrawModeToOpenGLMode(drawMode), start, count));
}