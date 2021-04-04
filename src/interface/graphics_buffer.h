#pragma once

namespace Graphics {


	enum class GShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Matrix3, Matrix4, Int, Int2, Int3, Int4, UInt, Byte4, Bool, Texture2D, TextureCube
	};

	static int ShaderDataTypeSize(GShaderDataType type)
	{
		switch (type)
		{
		case GShaderDataType::Float:			return 4;
		case GShaderDataType::Float2:			return 4 * 2;
		case GShaderDataType::Float3:			return 4 * 3;
		case GShaderDataType::Float4:			return 4 * 4;
		case GShaderDataType::Matrix3:			return 4 * 3 * 3;
		case GShaderDataType::Matrix4:			return 4 * 4 * 4;
		case GShaderDataType::Int:				return 4;
		case GShaderDataType::Texture2D:		return 4;
		case GShaderDataType::TextureCube:		return 4;
		case GShaderDataType::Int2:				return 4 * 2;
		case GShaderDataType::Int3:				return 4 * 3;
		case GShaderDataType::Int4:				return 4 * 4;
		case GShaderDataType::UInt:				return 4;
		case GShaderDataType::Byte4:			return 4;
		case GShaderDataType::Bool:				return 1;
		case GShaderDataType::None:				break;
		}
        printf("Unknown GShaderDataType\n");
		return 0;
	}

	static GShaderDataType ShaderDataTypeFromString(const std::string& typeString)
	{
		if (typeString == "float") return GShaderDataType::Float;
		else if (typeString == "vec2") return GShaderDataType::Float2;
		else if (typeString == "vec3") return GShaderDataType::Float3;
		else if (typeString == "vec4") return GShaderDataType::Float4;
		else if (typeString == "bool") return GShaderDataType::Bool;
		else if (typeString == "dont know") return GShaderDataType::Byte4;
		else if (typeString == "int") return GShaderDataType::Int;
		else if (typeString == "ivec2") return GShaderDataType::Int2;
		else if (typeString == "ivec3") return GShaderDataType::Int3;
		else if (typeString == "ivec4") return GShaderDataType::Int4;
		else if (typeString == "mat3") return GShaderDataType::Matrix3;
		else if (typeString == "mat4") return GShaderDataType::Matrix4;
		else if (typeString == "sampler2D") return GShaderDataType::Texture2D;
		else if (typeString == "samplerCube") return GShaderDataType::TextureCube;

		return GShaderDataType::None;
	}

	struct GBufferElement
	{
		GShaderDataType Type;
		std::string Name;
		size_t Size;
		size_t Offset;
		bool Normalized;

		GBufferElement() {}

		GBufferElement(GShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Normalized(normalized), Size(ShaderDataTypeSize(type)), Offset(0)
		{}

		int GetComponentCount() const
		{
			switch (Type)
			{
			case GShaderDataType::Float:		return 1;
			case GShaderDataType::Float2:		return 2;
			case GShaderDataType::Float3:		return 3;
			case GShaderDataType::Float4:		return 4;
			case GShaderDataType::Matrix3:		return 3 * 3;
			case GShaderDataType::Matrix4:		return 4 * 4;
			case GShaderDataType::Int:			return 1;
			case GShaderDataType::Int2:			return 2;
			case GShaderDataType::Int3:			return 3;
			case GShaderDataType::Int4:			return 4;
			case GShaderDataType::UInt:			return 1;
			case GShaderDataType::Byte4:		return 4;
			case GShaderDataType::Bool:			return 1;
			case GShaderDataType::Texture2D: 	return 1;
			case GShaderDataType::TextureCube:	return 1;
			case GShaderDataType::None:			break;
			}

			//TODO: Add ASSERT
			//IN_CORE_ASSERT(false, "Unknown Shader Type");
			return 0;
		}
	};

	class GBufferLayout
	{
	public:
		GBufferLayout() {}

		GBufferLayout(const std::initializer_list<GBufferElement>& elements)
			: fElements(elements)
		{
			CalculateOffsetAndStride();
		}

		inline int GetStride() const { return fStride; }
		inline const std::vector<GBufferElement>& GetElements() const { return fElements; }

		std::vector<GBufferElement>::iterator begin() { return fElements.begin(); }
		std::vector<GBufferElement>::iterator end() { return fElements.end(); }
		std::vector<GBufferElement>::const_iterator begin() const { return fElements.begin(); }
		std::vector<GBufferElement>::const_iterator end() const { return fElements.end(); }
	private:
		void CalculateOffsetAndStride()
		{
			int offset = 0;
			fStride = 0;
			for (auto& element : fElements)
			{
				element.Offset = offset;
				offset += element.Size;
				fStride += element.Size;
			}
		}
	private:
		std::vector<GBufferElement> fElements;
		int fStride = 0;
	};

	enum class EBufferUsage
	{
		STREAM_DRAW, 
		STREAM_READ, 
		STREAM_COPY, 
		STATIC_DRAW, 
		STATIC_READ, 
		STATIC_COPY, 
		DYNAMIC_DRAW, 
		DYNAMIC_READ, 
		DYNAMIC_COPY
	};

    class GVertexBuffer
    {
    private:
        GBufferLayout fBufferLayout;
    public:
        virtual ~GVertexBuffer() = default;

		const GBufferLayout& GetLayout() const { return fBufferLayout; }
		void SetLayout(const GBufferLayout& layout) { fBufferLayout = layout; }

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetData(unsigned char* data, size_t data_size) = 0;
    };

    class GIndexBuffer
    {
    public:
        virtual ~GIndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual size_t GetIndexCount() const = 0;

        virtual void SetData(unsigned char* data, size_t size_in_bytes, size_t element_size) = 0;
    };

    class GVertexArray
    {
    public:
        virtual ~GVertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		virtual void AddVertexBuffer(GVertexBuffer* vertexBuffer) = 0;
		virtual GIndexBuffer* GetIndexBuffer() const = 0;
		virtual void SetIndexBuffer(GIndexBuffer* indexBuffer) = 0;
    };

	enum class GFramebufferFormat
	{
		None = 0,
		RGBA8 = 1,
		RGBA16F = 2
	};

	class GFrameBuffer
	{
	public:
		virtual ~GFrameBuffer() = default;

		virtual void Resize(unsigned int width, unsigned int height, Graphics::GFramebufferFormat format) = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual unsigned int GetColorAttachment() const = 0;
		virtual unsigned int GetDepthAttachment() const = 0;
	};

}