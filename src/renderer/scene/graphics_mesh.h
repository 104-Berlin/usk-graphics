#pragma once

namespace Renderer {

    class RMesh : public RObject
    {
    public:
        struct Vertex
        {
            glm::vec3 Position;
            glm::vec3 Normal;

            Vertex(const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& normal = glm::vec3(0.0f, 0.0f, 1.0f))
                : Position(position), Normal(normal)
            {

            }
        };

        struct Data
        {
            std::vector<Vertex>         Vertices;
            std::vector<unsigned int>   Indices;
        };

    protected:
        Data                        fMeshData;

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