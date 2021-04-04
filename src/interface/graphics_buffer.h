#pragma once

namespace Graphics {

    class GBuffer
    {
    public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    };

}