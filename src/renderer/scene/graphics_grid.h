#pragma once

namespace Renderer {

    class RGrid : public RObject
    {
    private:
        unsigned int fColumnCount;
        unsigned int fRowCount;

        float fWidth;
        float fHeight;

        Graphics::GVertexArray*     fVertexArray;

    public:
        RGrid(unsigned int columnCount, unsigned int rowCount, float width = 100.0f, float height = 100.0f);
        virtual ~RGrid();

        virtual void OnRender(Graphics::GContext* context) override;

    private:
        void UpdateBuffers();
        std::vector<RMesh::Vertex> GenerateVertices();
    };

}