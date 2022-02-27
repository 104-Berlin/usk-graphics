#include "graphics_opengl.h"

using namespace GL;


void GLContext::Init(void* initData) 
{
    if (!initData) { printf("Please provide the GLADloadproc to the OpenGL context init"); return; }
    int gladStatus = gladLoadGLLoader((GLADloadproc)initData);
    printf("Glad Init Status: %d\n", gladStatus);
    printf("%s\n", glGetString(GL_VERSION));
    EnableDepthTest(true);
    int bits;
    glGetIntegerv(GL_DEPTH_BITS, &bits);
    printf("Depth Bits: %d", bits);

}

void GLContext::Clear(float r, float g, float b, unsigned char GCLEAROPTIONS) 
{
    GLuint clearOption = 0;
    clearOption |= GCLEAROPTIONS & GCLEAROPTION_COLOR_BUFFER ? GL_COLOR_BUFFER_BIT : 0;
    clearOption |= GCLEAROPTIONS & GCLEAROPTION_DEPTH_BUFFER ? GL_DEPTH_BUFFER_BIT : 0;
    clearOption |= GCLEAROPTIONS & GCLEAROPTION_STENCIL_BUFFER ? GL_STENCIL_BUFFER_BIT : 0;
    clearOption |= GCLEAROPTIONS & GCLEAROPTION_ACCUM_BUFFER ? GL_ACCUM_BUFFER_BIT : 0;
    glCall(glClearColor(r, g, b, 1));
    //glCall(glClearDepth(1.0));
    glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void GLContext::EnableDepthTest(bool enable)
{
    glCall(glDisable(GL_SCISSOR_TEST));
    if (fDepthTestEnabled)
    {
        glCall(glDepthFunc(GL_LESS));
        glCall(glDepthMask(GL_TRUE));
        glCall(glEnable(GL_DEPTH_TEST));
        glCall(glDisable(GL_BLEND));
        //glCall(glDisable(GL_STENCIL_TEST));
    }
    else
    {
        glCall(glDisable(GL_DEPTH_TEST));
    }
}

void GLContext::SetFaceCullingMode(Graphics::GCullMode mode)
{
    switch (mode)
    {
        case Graphics::GCullMode::NONE:
            glCall(glDisable(GL_CULL_FACE));
            break;
        case Graphics::GCullMode::FRONT:
            glCall(glEnable(GL_CULL_FACE));
            glCall(glCullFace(GL_FRONT));
            break;
        case Graphics::GCullMode::BACK:
            glCall(glEnable(GL_CULL_FACE));
            glCall(glCullFace(GL_BACK));
            break;
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