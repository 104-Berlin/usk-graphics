#include "graphics_opengl.h"

using namespace GL;


void GLContext::Init(void* initData) 
{
    if (!initData) { printf("Please provide the GLADloadproc to the OpenGL context init"); return; }
    int gladStatus = gladLoadGLLoader((GLADloadproc)initData);
    printf("Glad Init Status: %d\n", gladStatus);
    printf("%s\n", glGetString(GL_VERSION));
    EnableDepthTest(true);
}

void GLContext::Clear(float r, float g, float b, unsigned char GCLEAROPTIONS) 
{
    G_RENDERCMD4(r, g, b, GCLEAROPTIONS, {
        GLuint clearOption = 0;
        clearOption |= GCLEAROPTIONS & GCLEAROPTION_COLOR_BUFFER ? GL_COLOR_BUFFER_BIT : 0;
        clearOption |= GCLEAROPTIONS & GCLEAROPTION_DEPTH_BUFFER ? GL_DEPTH_BUFFER_BIT : 0;
        clearOption |= GCLEAROPTIONS & GCLEAROPTION_STENCIL_BUFFER ? GL_STENCIL_BUFFER_BIT : 0;
        clearOption |= GCLEAROPTIONS & GCLEAROPTION_ACCUM_BUFFER ? GL_ACCUM_BUFFER_BIT : 0;
        glCall(glClearColor(r, g, b, 1));
        
        glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    })
}

void GLContext::EnableDepthTest(bool enable)
{
    fDepthTestEnabled = enable;
    G_RENDERCMD1(enable, {
        glCall(glDisable(GL_SCISSOR_TEST));
        if (enable)
        {
            glCall(glEnable(GL_DEPTH_TEST));
        }
        else
        {
            glCall(glDisable(GL_DEPTH_TEST));
        }
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