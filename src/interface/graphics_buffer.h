#pragma once

namespace Graphics {

    class GBuffer
    {
    public:
        virtual void Bind() const G_EMPTY_IMPL
        virtual void Unbind() const G_EMPTY_IMPL
    };

}