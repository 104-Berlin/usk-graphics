#pragma once

namespace Renderer {

    class RBezierCurve : public RMesh
    {
    public:
        struct CurveSegment
        {
            glm::vec3 Start;
            glm::vec3 End;
            glm::vec3 Controll1;
            glm::vec3 Controll2;
        };
    private:
        float fThickness;
        float fStepsPerCurve;

        bool fIsDirty;

        std::vector<CurveSegment> fCurveSegments;
    public:
        RBezierCurve();

        void SetSegments(const std::vector<CurveSegment>& segments);

        void SetThickness(float thickness);
        float GetThickness() const;
        void SetSteps(int steps);
        int GetSteps() const;

        void RegenMesh();
    private:

        glm::vec3 GetCurvePoint(const CurveSegment& seg, float t);
        glm::vec3 GetCurveNormal(const CurveSegment& seg, float t);
    };

    class RBezierCurveEdit : public RMesh
    {
    private:
        RObject*  fStartPosition;
        RObject*  fEndPosition;
        RObject*  fControllPoint1;
        RObject*  fControllPoint2;

        float     fThickness;
        int       fSteps;

        bool      fDirty;
    public:
        RBezierCurveEdit();
        virtual ~RBezierCurveEdit();

        void SetStartPos(const glm::vec3& pos);
        const glm::vec3& GetStartPos() const;
        RObject* GetStartPositionObject() const;
        void SetEndPos(const glm::vec3& pos);
        const glm::vec3& GetEndPos() const;
        RObject* GetEndPositionObject() const;
        void SetControll1(const glm::vec3& pos);
        const glm::vec3& GetControll2() const;
        RObject* GetControllPoint1Object() const;
        void SetControll2(const glm::vec3& pos);
        const glm::vec3& GetControll1() const;
        RObject* GetControllPoint2Object() const;
        
        void SetThickness(float thickness);
        float GetThickness() const;
        void SetSteps(int steps);
        int GetSteps() const;

        void RegenMesh();
    private:

        glm::vec3 GetCurvePoint(float t);
        glm::vec3 GetCurveNormal(float t);
    };

}