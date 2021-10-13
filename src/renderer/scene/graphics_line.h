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
        void SetEnd(const glm::vec3& point);
    private:
        void RegenVertices();
    };

}