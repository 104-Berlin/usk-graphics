#pragma once

namespace GL {

    static GLenum TextureFormatToOpenGLFormat(Graphics::GTextureFormat format)
    {
        switch (format)
        {
            case Graphics::GTextureFormat::RGB8:  return GL_RGB;
            case Graphics::GTextureFormat::RGBA8: return GL_RGBA;
        }
    }

    class GLTexture2D : public Graphics::GTexture2D
    {
    private:
        GLuint fRenderId;
    public:
        GLTexture2D();
        virtual ~GLTexture2D();

        virtual void Bind(unsigned int slot = 0) const override;
        virtual void Unbind() const override;

        virtual unsigned int GetID() const override;

        virtual void SetData(unsigned char* data, size_t width, size_t height) override;
    };

}