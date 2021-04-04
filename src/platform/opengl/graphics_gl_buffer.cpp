#include "graphics_opengl.h"

using namespace GL;

GLVertexBuffer::GLVertexBuffer() 
    : fRenderId(0)
{
    G_RENDERCMD_S({
        glCall(glGenBuffers(1, &self->fRenderId));
    })
}

GLVertexBuffer::~GLVertexBuffer() 
{
    GLuint ID = fRenderId;
    G_RENDERCMD1(ID, {
        glCall(glDeleteBuffers(1, &ID));
    })
}

void GLVertexBuffer::Bind() const
{
    G_RENDERCMD_S({
        glCall(glBindBuffer(GL_ARRAY_BUFFER, self->fRenderId));
    })
}

void GLVertexBuffer::Unbind() const
{
    G_RENDERCMD({
        glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    })
}

void GLVertexBuffer::SetData(unsigned char* data, size_t data_size) 
{
    Bind();

    Graphics::GSharedBuffer sharedBuffer;
    sharedBuffer.InitWith<unsigned char>(data, data_size);
    G_RENDERCMD_S1(sharedBuffer, {
        glCall(glBufferData(GL_ARRAY_BUFFER, sharedBuffer.GetSizeInByte(), sharedBuffer.Data(), GL_STATIC_DRAW));
    })
}

GLIndexBuffer::GLIndexBuffer() 
    : fRenderId(0), fIndexCount(0)
{
    G_RENDERCMD_S({
        glCall(glGenBuffers(1, &self->fRenderId));
    })
}

GLIndexBuffer::~GLIndexBuffer() 
{
    GLuint ID = fRenderId;
    G_RENDERCMD1(ID, {
        glCall(glDeleteBuffers(1, &ID));
    })
}

void GLIndexBuffer::Bind() const 
{
    G_RENDERCMD_S({
        glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->fRenderId));
    })
}

void GLIndexBuffer::Unbind() const 
{
    G_RENDERCMD_S({
        glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    })
}

size_t GLIndexBuffer::GetIndexCount() const 
{
    return fIndexCount;
}

void GLIndexBuffer::SetData(unsigned char* data, size_t size_in_bytes, size_t element_size)
{
    if (size_in_bytes % element_size != 0)
    {
        printf("Cant set Data of IndexBuffer. Size in bytes is not devidable by element size!");
        return;
    }
    Graphics::GSharedBuffer sharedBuffer;
    sharedBuffer.InitWith<unsigned char>(data, size_in_bytes);

    fIndexCount = size_in_bytes / element_size;

    Bind();
    G_RENDERCMD_S1(sharedBuffer, {
        glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sharedBuffer.GetSizeInByte(), sharedBuffer.Data(), GL_STATIC_DRAW));
    })
}

GLVertexArray::GLVertexArray() 
    : fRenderId(0), fIndexBuffer(nullptr), fVertexBufferIndex(0)
{
    G_RENDERCMD_S({
        glCall(glGenVertexArrays(1, &self->fRenderId));
    })
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
    G_RENDERCMD1(ID, {
        glCall(glDeleteVertexArrays(1, &ID));
    })
}

void GLVertexArray::Bind() const 
{
    G_RENDERCMD_S({
        glCall(glBindVertexArray(self->fRenderId));
    })
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
    G_RENDERCMD({
        glCall(glBindVertexArray(0));
    })
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
		G_RENDERCMD_S2(element, stride, {
			glCall(glEnableVertexAttribArray(self->fVertexBufferIndex));
			glCall(glVertexAttribPointer(self->fVertexBufferIndex,
						element.GetComponentCount(),
						ShaderDataTypeToOpenGLType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						stride, (const void*)element.Offset));
			self->fVertexBufferIndex++;
		});
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