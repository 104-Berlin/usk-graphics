#pragma once

namespace Graphics {

    class GMesh : public GObject
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
        GMesh();
        virtual ~GMesh();

        void SetData(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
        void BindToDraw();
        size_t GetIndexCount() const;

        virtual void OnRender(GContext* context) override;
    protected:
        void UpdateBuffers();
    };

    class GLine : public GMesh
    {
    private:
        double fThickness;

        glm::vec3 fStart;
        glm::vec3 fEnd;
    public:
        GLine();

        void SetStart(const glm::vec3& point);
        void SetEnd(const glm::vec3& point);
    };

}