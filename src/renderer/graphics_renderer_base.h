#pragma once

namespace Renderer {

    /**
     * All renderers have a current context pointer which will not be managed by the renderer.
     * All renderers are copiable and just store pointers to graphics elements which should not get destroyed as long as the renderer is used
     */
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