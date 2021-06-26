#include "graphics_opengl.h"

using namespace GL;

GLVertexBuffer::GLVertexBuffer() 
    : fRenderId(0)
{
    glCall(glGenBuffers(1, &fRenderId));
}

GLVertexBuffer::~GLVertexBuffer() 
{
    glCall(glDeleteBuffers(1, &fRenderId));
}

void GLVertexBuffer::Bind() const
{
    glCall(glBindBuffer(GL_ARRAY_BUFFER, fRenderId));
}

void GLVertexBuffer::Unbind() const
{
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void GLVertexBuffer::SetData(unsigned char* data, size_t data_size) 
{
    Bind();
    glCall(glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW));
}

GLIndexBuffer::GLIndexBuffer() 
    : fRenderId(0), fIndexCount(0)
{
    glCall(glGenBuffers(1, &fRenderId));
}

GLIndexBuffer::~GLIndexBuffer() 
{
    glCall(glDeleteBuffers(1, &fRenderId));
}

void GLIndexBuffer::Bind() const 
{
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fRenderId));
}

void GLIndexBuffer::Unbind() const 
{
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

size_t GLIndexBuffer::GetIndexCount() const 
{
    return fIndexCount;
}

Graphics::GIndexType GLIndexBuffer::GetIndexType() const 
{
    return fType;
}

void GLIndexBuffer::SetData(unsigned char* data, size_t size_in_bytes, size_t element_size)
{
    if (element_size == 1)
    {
        fType = Graphics::GIndexType::UNSIGNED_BYTE;
    }
    else if (element_size == 2)
    {
        fType = Graphics::GIndexType::UNSIGNED_SHORT;
    }
    else if (element_size == 4)
    {
        fType = Graphics::GIndexType::UNSIGNED_INT;
    }
    else
    {
        printf("Wrong element size for the indexBuffer. Accepted sizes are: 1, 2 and 4 bytes!\n");
        return;
    }

    if (size_in_bytes % element_size != 0)
    {
        printf("Cant set Data of IndexBuffer. Size in bytes is not devidable by element size!\n");
        return;
    }

    fIndexCount = size_in_bytes / element_size;


    Bind();
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_in_bytes, data, GL_STATIC_DRAW));
}

GLVertexArray::GLVertexArray() 
    : fRenderId(0), fIndexBuffer(nullptr), fVertexBufferIndex(0)
{
    glCall(glGenVertexArrays(1, &fRenderId));
}

GLVertexArray::~GLVertexArray() 
{
    if (fIndexBuffer)
    {
        delete fIndexBuffer;
    }
    for (Graphics::GVertexBuffer* vb : fVertexBuffers)
    {
        delete vb;
    }
    fVertexBuffers.clear();
    GLuint ID = fRenderId;
    glCall(glDeleteVertexArrays(1, &fRenderId));
}

void GLVertexArray::Bind() const 
{
    glCall(glBindVertexArray(fRenderId));
    for (Graphics::GVertexBuffer* vb : fVertexBuffers)
    {
        vb->Bind();
    }
    if (fIndexBuffer)
    {
        fIndexBuffer->Bind();
    }
}

void GLVertexArray::Unbind() const 
{
    glCall(glBindVertexArray(0));
}

void GLVertexArray::AddVertexBuffer(Graphics::GVertexBuffer* vertexBuffer) 
{
    if (vertexBuffer->GetLayout().GetElements().size() == 0)
	{	
        printf("No Vertex Layout set for the buffer\n");
		return;
	}

	fVertexBuffers.push_back(vertexBuffer);
	Bind();
	vertexBuffer->Bind();

	const auto layout = vertexBuffer->GetLayout();
	int stride = layout.GetStride();
	for (const auto& element : layout)
	{
        glCall(glEnableVertexAttribArray(fVertexBufferIndex));
        glCall(glVertexAttribPointer(fVertexBufferIndex,
                    element.GetComponentCount(),
                    ShaderDataTypeToOpenGLType(element.Type),
                    element.Normalized ? GL_TRUE : GL_FALSE,
                    stride, (const void*)element.Offset));
        fVertexBufferIndex++;
	}
}

Graphics::GIndexBuffer* GLVertexArray::GetIndexBuffer() const 
{
    return fIndexBuffer;
}

void GLVertexArray::SetIndexBuffer(Graphics::GIndexBuffer* indexBuffer) 
{
    if (fIndexBuffer)
    {
        delete fIndexBuffer;
    }
    fIndexBuffer = indexBuffer;
}

GLFrameBuffer::GLFrameBuffer(unsigned int width, unsigned int height, Graphics::GFrameBufferFormat format) 
    : fWidth(0), fHeight(0), fFormat(Graphics::GFrameBufferFormat::None), fRenderId(0), fColorAttachment(0), fDepthAttachment(0)
{
    Resize(width, height, format);
}

GLFrameBuffer::~GLFrameBuffer() 
{
    GLint currentFbo;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &currentFbo);

    if (currentFbo == fRenderId)
    {
    }
    glCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    glCall(glDeleteFramebuffers(1, &fRenderId));
    glCall(glDeleteTextures(1, &fColorAttachment));
    glCall(glDeleteTextures(1, &fDepthAttachment));
}

void GLFrameBuffer::Resize(unsigned int width, unsigned int height, Graphics::GFrameBufferFormat format) 
{
    if (width == fWidth && height == fHeight) return;
    if (width == 0 || height == 0) return;

	fWidth = width;
	fHeight = height;
    fFormat = format;

    if (fRenderId)
    {
        glCall(glDeleteFramebuffers(1, &fRenderId));
    }
    
    if (fDepthAttachment)
    {
        glCall(glDeleteTextures(1, &fDepthAttachment));
    }
    
    if (fColorAttachment) 
    {
        glCall(glDeleteTextures(1, &fColorAttachment));
    }


    glCall(glGenFramebuffers(1, &fRenderId));
    glCall(glBindFramebuffer(GL_FRAMEBUFFER, fRenderId));

    

    glCall(glGenTextures(1, &fColorAttachment));
    glCall(glBindTexture(GL_TEXTURE_2D, fColorAttachment));

    if (fFormat == Graphics::GFrameBufferFormat::RGBA16F)
    {
        glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, fWidth, fHeight, 0, GL_RGBA, GL_FLOAT, nullptr));
    }
    else if (fFormat == Graphics::GFrameBufferFormat::RGBA8)
    {
        glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fWidth, fHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
    }

    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    glCall(glBindTexture(GL_TEXTURE_2D, 0));
    
    
    glCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fColorAttachment, 0));

    glCall(glGenTextures(1, &fDepthAttachment));
    glCall(glBindTexture(GL_TEXTURE_2D, fDepthAttachment));
    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, fWidth, fHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL));

    glCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, fDepthAttachment, 0));

    GLenum frameBufferResult = GL_FRAMEBUFFER_COMPLETE;
    if ((frameBufferResult = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("Depth FrameBuffer is incomplete! %d\n", frameBufferResult);
    }
        

    glCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

unsigned int GLFrameBuffer::GetWidth() const
{
    return fWidth;
}

unsigned int GLFrameBuffer::GetHeight() const
{
    return fHeight;
}

void GLFrameBuffer::Bind() const
{
    glCall(glBindFramebuffer(GL_FRAMEBUFFER, fRenderId));
    glCall(glViewport(0, 0, fWidth, fHeight));
}

void GLFrameBuffer::Unbind() const
{
    glCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

unsigned int GLFrameBuffer::GetColorAttachment() const
{
    return fColorAttachment;
}

unsigned int GLFrameBuffer::GetDepthAttachment() const
{
    return fDepthAttachment;
}