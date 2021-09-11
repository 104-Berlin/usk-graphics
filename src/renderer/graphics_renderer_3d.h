#pragma once

namespace Renderer {

    class RRenderer3D : public RRendererBase
    {
    private:
        Graphics::GShader*          fDefaultShader;
        Graphics::GFrameBuffer*     fFrameBuffer;
        glm::mat4                   fViewProjectionMatrix;
    public:
        RRenderer3D(Graphics::GContext* context, Graphics::GFrameBuffer* frameBuffer);
        virtual ~RRenderer3D();

        virtual void Render(RScene* scene, RCamera* camera);
    };
    

}