#pragma once

namespace Renderer {

    class RGid : public RObject
    {
    private:
        unsigned int fColumnCount;
        unsigned int fRowCount;

        float fWidth;
        float fHeight;

        Graphics::GVertexArray*     fVertexArray;
    public:
        RGid(unsigned int columnCount, unsigned int rowCount, float width = 100.0f, float height = 100.0f);
        virtual ~RGid();

        virtual void OnRender(Graphics::GContext* context) override;

    private:
        void UpdateBuffers();
        std::vector<glm::vec3> GenerateVertices();
    };

}