#pragma once

namespace GL {

    class GLBuffer : public Graphics::GBuffer
    {
    public:
        virtual void Bind() const override;
        virtual void Unbind() const override;
    };

}