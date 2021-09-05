#pragma once

namespace Graphics {

    enum class GTextureFormat
    {
        RGB8,
        RGBA8
    };

    class GTexture2D 
    {
    protected:
        GTextureFormat fFormat;
    public:
        GTexture2D(GTextureFormat format = GTextureFormat::RGB8) : fFormat(format) {}
        virtual ~GTexture2D() = default;

        virtual void Bind(unsigned int slot = 0) const = 0;
        virtual void Unbind() const = 0;

        virtual unsigned int GetID() const = 0;

        virtual void SetData(unsigned char* data, size_t width, size_t height) = 0;
        

        void SetTextureFormat(GTextureFormat format) { fFormat = format; }
    };

}