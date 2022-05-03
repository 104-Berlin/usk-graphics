#pragma once

namespace Renderer {

    class RMesh : public RObject
    {
    public:
        struct Vertex
        {
            glm::vec3 Position;
            glm::vec3 Normal;
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

        virtual void OnRender(Graphics::GContext* context) override;
    protected:
        void UpdateBuffers();
    };

    class RTestMesh : public RObject
    {
    public:
        struct Vertex
        {
            glm::vec3 Position;
            glm::vec3 Normal;
        };
    private:
        std::vector<Vertex>         fVertices;

        Graphics::GVertexArray*     fVertexArray;
    public:
        RTestMesh();
        virtual ~RTestMesh();

        void SetData(const std::vector<Vertex>& vertices);

        virtual void OnRender(Graphics::GContext* context) override;
    private:

        void UpdateBuffers();
        Graphics::GVertexArray* GetSingleBuffer(const std::vector<Vertex>& vertices);
    };

}