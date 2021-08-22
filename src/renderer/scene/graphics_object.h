#pragma once

namespace Graphics {

    class GObject
    {
    private:
        glm::mat4 fModelMatrix;

        glm::vec3 fPosition;
        glm::vec3 fScale;
        glm::quat fRotation;

        bool      fMatrixAutoUpdate;

        GObject*              fParent;
        std::vector<GObject*> fChildren;
    public:
        GObject();
        virtual ~GObject();

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

        void Add(GObject* object);
        void Attach(GObject* object);

        const std::vector<GObject*>& GetChildren() const;


        void Render(GContext* context);
        virtual void OnRender(GContext* context) {};
    };

}