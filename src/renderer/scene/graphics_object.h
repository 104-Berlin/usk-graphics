#pragma once

namespace Renderer {

    class RObject
    {
        friend class RScene;
    private:
        glm::mat4 fModelMatrix;

        glm::vec3 fPosition;
        glm::vec3 fScale;
        glm::quat fRotation;

        bool      fMatrixAutoUpdate;

        RObject*              fParent;
        std::vector<RObject*> fChildren;
    public:
        RObject();
        virtual ~RObject();

        const glm::vec3& GetPosition() const;
        const glm::vec3& GetScale() const;
        const glm::quat& GetRotation() const;

        void SetPosition(const glm::vec3& value);
        void SetScale(const glm::vec3& value);
        void SetRotation(const glm::quat& value);

        void SetMatrixAutoUpdate(bool value);
        bool GetMatrixAutoUpdate() const;

        glm::mat4 GetModelMatrix();
        void SetModelMatrix(const glm::mat4& modelMatrix);
        void UpdateMatrix();

        void Add(RObject* object);
        void Attach(RObject* object);

        const std::vector<RObject*>& GetChildren() const;

        RObject* GetParent() const;

        void Render(Graphics::GContext* context);
        virtual void OnRender(Graphics::GContext* context) {};

    private:
        void RemoveChild(RObject* object);
    };

}