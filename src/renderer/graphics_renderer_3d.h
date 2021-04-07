#pragma once

namespace Renderer {

    class RRenderer3D : public RRendererBase
    {
    private:
        Graphics::GShader*      fDefaultShader;
        Graphics::GFrameBuffer* fCurrentFrameBuffer;
    public:
        RRenderer3D(Graphics::GContext* context = nullptr, Graphics::GShader* default_shader = nullptr);

        virtual void Begin(Graphics::GFrameBuffer* frameBuffer);
        void Submit(Graphics::GVertexArray* vertexArray, Graphics::GShader* shader = nullptr);
        virtual void End();
    };
    

}