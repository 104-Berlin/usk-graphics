#pragma once

namespace Renderer {

    class RBezierCurve : public RMesh
    {
    private:
        glm::vec3 fStartPos;
        glm::vec3 fEndPos;
        glm::vec3 fControll1;
        glm::vec3 fControll2;
        float     fThickness;
    public:
        RBezierCurve();

        void SetStartPos(const glm::vec3& pos);
        const glm::vec3& GetStartPos() const;
        void SetEndPos(const glm::vec3& pos);
        const glm::vec3& GetEndPos() const;
        void SetControll1(const glm::vec3& pos);
        const glm::vec3& GetControll2() const;
        void SetControll2(const glm::vec3& pos);
        const glm::vec3& GetControll1() const;
        void SetThickness(float thickness);
        float GetThickness() const;
    private:
        void RegenMesh();

        glm::vec3 GetCurvePoint(float t);
        glm::vec3 GetCurveNormal(float t);
    };

}