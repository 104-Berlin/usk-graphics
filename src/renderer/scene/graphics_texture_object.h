#pragma once

namespace Renderer {

    class RTextureObject : public RObject
    {
    private:
        Graphics::GTexture2D* fTexture2D;
    public:
        RTextureObject();
        ~RTextureObject();
    };

}