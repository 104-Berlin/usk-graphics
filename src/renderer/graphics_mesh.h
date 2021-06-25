#pragma once

namespace Renderer {

    class RMesh
    {
    public:
        struct Vertex
        {
            glm::vec3 Position;
        };
    protected:
        std::vector<Vertex>         fVertices;
        std::vector<unsigned int>   fIndices;
        size_t                      fIndexCount;

        Graphics::GVertexArray*     fVertexArray;
    public:
        RMesh();
        virtual ~RMesh();

        void SetData(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
        void BindToDraw();
        size_t GetIndexCount() const;

    protected:
        void UpdateBuffers();
    };

    class RLine : public RMesh
    {
    private:
        double fThickness;

        glm::vec3 fStart;
        glm::vec3 fEnd;
    public:
        RLine();

        void SetStart(const glm::vec3& point);
        void SetEnd(const glm::vec3& point);
    };

}