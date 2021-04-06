#pragma once

namespace Renderer {

    class RRenderer3D : public RRendererBase
    {
    private:
        Graphics::GFrameBuffer* fCurrentFrameBuffer;
    public:
        RRenderer3D(Graphics::GContext* context);

        virtual void Begin(Graphics::GFrameBuffer* frameBuffer);
        void Submit(Graphics::GVertexArray* vertexArray, Graphics::GShader* shader);
        virtual void End();
    };
    

}