#pragma once

namespace Renderer {

    class RMesh
    {
    public:
        struct Vertex
        {
            glm::vec3 Position;
        };
    private:
        std::vector<Vertex>         fVertices;
        std::vector<unsigned int>   fIndices;
        size_t                      fIndexCount;

        Graphics::GVertexArray*     fVertexArray;
    public:
        RMesh();
        ~RMesh();

        void SetData(const std::vector<Vertex>& vertices, const std::vector<unsigned int> indices);
        void BindToDraw();
        size_t GetIndexCount() const;
    };

}