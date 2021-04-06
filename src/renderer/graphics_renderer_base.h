#pragma once

namespace Renderer {

    class RRendererBase
    {
    protected:
        Graphics::GContext* fContext;
    public:
        RRendererBase(Graphics::GContext* context);
        virtual ~RRendererBase() = default;

        virtual void Begin(Graphics::GFrameBuffer* frameBuffer) = 0;
        virtual void End() = 0;
    };

}