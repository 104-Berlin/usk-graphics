#pragma once

namespace GL {

    static GLenum ShaderDataTypeToOpenGLType(Graphics::GShaderDataType type)
	{
		switch (type)
		{
		case Graphics::GShaderDataType::Float:			
		case Graphics::GShaderDataType::Float2:			
		case Graphics::GShaderDataType::Float3:			
		case Graphics::GShaderDataType::Float4:			
		case Graphics::GShaderDataType::Matrix3:			
		case Graphics::GShaderDataType::Matrix4:			return GL_FLOAT;
		case Graphics::GShaderDataType::Int:				
		case Graphics::GShaderDataType::Texture2D:		
		case Graphics::GShaderDataType::TextureCube:		
		case Graphics::GShaderDataType::Int2:				
		case Graphics::GShaderDataType::Int3:				
		case Graphics::GShaderDataType::Int4:				return GL_INT;
		case Graphics::GShaderDataType::UInt:				return GL_UNSIGNED_INT;
		case Graphics::GShaderDataType::Byte4:			    return GL_UNSIGNED_BYTE;
		case Graphics::GShaderDataType::Bool:				return GL_BOOL;
		case Graphics::GShaderDataType::None:				break;
		}
		return 0;
	}

    class GLVertexBuffer : public Graphics::GVertexBuffer
    {
    private:
        GLuint fRenderId;
    public:
        GLVertexBuffer();
        ~GLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetData(unsigned char* data, size_t data_size) override;
    };

    class GLIndexBuffer : public Graphics::GIndexBuffer
    {
    private:
        GLuint fRenderId;
        size_t fIndexCount;
    public:
        GLIndexBuffer();
        ~GLIndexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual size_t GetIndexCount() const override;

        virtual void SetData(unsigned char* data, size_t size_in_bytes, size_t element_size) override;
    };

    class GLVertexArray : public Graphics::GVertexArray
    {
    private:
        GLuint                                   fRenderId;
        int                                      fVertexBufferIndex;
        std::vector<Graphics::GVertexBuffer*>    fVertexBuffers;
        Graphics::GIndexBuffer*                  fIndexBuffer;
    public:
        GLVertexArray();
        ~GLVertexArray();

        virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual void AddVertexBuffer(Graphics::GVertexBuffer* vertexBuffer) override;
		virtual Graphics::GIndexBuffer* GetIndexBuffer() const override;
		virtual void SetIndexBuffer(Graphics::GIndexBuffer* indexBuffer) override;
    };

}