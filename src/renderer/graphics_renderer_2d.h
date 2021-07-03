#pragma once

namespace Renderer {

    class RRenderer2D : public RRendererBase
    {
    private:
        Graphics::GFrameBuffer* fCurrentFrameBuffer;
        Graphics::GShader*      fRenderingShader;
    public:
        RRenderer2D(Graphics::GContext* context = nullptr);
        virtual void Begin(Graphics::GFrameBuffer* frameBuffer, RCamera* camera) override;

        virtual void End() override;
    };

}