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
    G_RENDERCMD1(sharedBuffer, {
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
        int bufferIndex = fVertexBufferIndex;
		G_RENDERCMD3(element, stride, bufferIndex, {
			glCall(glEnableVertexAttribArray(bufferIndex));
			glCall(glVertexAttribPointer(bufferIndex,
						element.GetComponentCount(),
						ShaderDataTypeToOpenGLType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						stride, (const void*)element.Offset));
		});
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
    GLuint ID = fRenderId;
    GLuint colorAttach = fColorAttachment;
    GLuint depthAttach = fDepthAttachment;
    G_RENDERCMD3(ID, colorAttach, depthAttach, {
        glCall(glDeleteFramebuffers(1, &ID));
		glCall(glDeleteTextures(1, &colorAttach));
		glCall(glDeleteTextures(1, &depthAttach));
    })
}

void GLFrameBuffer::Resize(unsigned int width, unsigned int height, Graphics::GFrameBufferFormat format) 
{
    if (width == fWidth && height == fHeight) return;
    if (width == 0 || height == 0) return;

	fWidth = width;
	fHeight = height;
    fFormat = format;


	G_RENDERCMD_S({

		if (self->fRenderId)
		{
			glCall(glDeleteFramebuffers(1, &self->fRenderId));
		}
		
		if (self->fDepthAttachment)
		{
			glCall(glDeleteTextures(1, &self->fDepthAttachment));
		}
		
		if (self->fColorAttachment) 
		{
			glCall(glDeleteTextures(1, &self->fColorAttachment));
		}


		glCall(glGenFramebuffers(1, &self->fRenderId));
		glCall(glBindFramebuffer(GL_FRAMEBUFFER, self->fRenderId));

		

		glCall(glGenTextures(1, &self->fColorAttachment));
		glCall(glBindTexture(GL_TEXTURE_2D, self->fColorAttachment));

		if (self->fFormat == Graphics::GFrameBufferFormat::RGBA16F)
		{
			glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, self->fWidth, self->fHeight, 0, GL_RGBA, GL_FLOAT, nullptr));
		}
		else if (self->fFormat == Graphics::GFrameBufferFormat::RGBA8)
		{
			glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, self->fWidth, self->fHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
		}

		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        glCall(glBindTexture(GL_TEXTURE_2D, 0));
        
        
		glCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, self->fColorAttachment, 0));

		glCall(glGenTextures(1, &self->fDepthAttachment));
		glCall(glBindTexture(GL_TEXTURE_2D, self->fDepthAttachment));
		glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, self->fWidth, self->fHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL));

		glCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, self->fDepthAttachment, 0));

        GLenum frameBufferResult = GL_FRAMEBUFFER_COMPLETE;
		if ((frameBufferResult = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
		{
            printf("Depth FrameBuffer is incomplete! %d\n", frameBufferResult);
		}
        else
        {
            printf("Sucesfully created framebuffer\n");
        }
			

		glCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	})
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
    G_RENDERCMD_S({
        glCall(glBindFramebuffer(GL_FRAMEBUFFER, self->fRenderId));
        glCall(glViewport(0, 0, self->fWidth, self->fHeight));
    })
}

void GLFrameBuffer::Unbind() const
{
    G_RENDERCMD({
			glCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	})
}

unsigned int GLFrameBuffer::GetColorAttachment() const
{
    return fColorAttachment;
}

unsigned int GLFrameBuffer::GetDepthAttachment() const
{
    return fDepthAttachment;
}