#include "graphics_opengl.h"

using namespace GL;

GLTexture2D::GLTexture2D() 
    : fRenderId(0)
{
    glCall(glGenTextures(1, &fRenderId));
}

GLTexture2D::~GLTexture2D() 
{
    glCall(glDeleteTextures(1, &fRenderId));
}

void GLTexture2D::Bind(unsigned int slot) const 
{
    glCall(glActiveTexture(GL_TEXTURE0 + slot));
    glCall(glBindTexture(GL_TEXTURE_2D, fRenderId));
}

void GLTexture2D::Unbind() const 
{
    glCall(glBindTexture(GL_TEXTURE_2D, 0));
}

unsigned int GLTexture2D::GetID() const 
{
    return fRenderId;
}

void GLTexture2D::SetData(unsigned char* data, size_t width, size_t height) 
{
    Bind();
    glCall(glTexImage2D(GL_TEXTURE_2D, 0, TextureFormatToOpenGLFormat(fFormat), width, height, 0, TextureFormatToOpenGLFormat(fFormat), GL_UNSIGNED_BYTE, data));
    glCall(glGenerateMipmap(GL_TEXTURE_2D));
    Unbind();
}
