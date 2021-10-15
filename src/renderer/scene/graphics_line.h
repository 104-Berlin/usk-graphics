#pragma once

namespace Renderer {

    class RLine : public RMesh
    {
    private:
        double fThickness;

        glm::vec3 fStart;
        glm::vec3 fEnd;
    public:
        RLine();

        void SetThickness(float thickness);
        float GetThickness() const;

        void SetStart(const glm::vec3& point);
        const glm::vec3& GetStart() const;
        void SetEnd(const glm::vec3& point);
        const glm::vec3& GetEnd() const;
    private:
        void RegenVertices();
    };

}