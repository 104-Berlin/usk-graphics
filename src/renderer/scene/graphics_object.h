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

        void Clear();
        size_t GetChildCount() const;
        RObject* GetChildAt(size_t index) const;
        const std::vector<RObject*>& GetChildren() const;

        RObject* GetParent() const;

        void Render(Graphics::GContext* context);
        virtual void OnRender(Graphics::GContext* context) {};

        template <typename T>
        T* FindTypeOf(bool includeSelf = false)
        {
            T* result = dynamic_cast<T*>(this);
            if (result)
            {
                return result;
            }
            size_t i = 0;
            for (RObject* child : fChildren)
            {
                result = dynamic_cast<T*>(child);
                if (result)
                {
                    return result;
                }
            }
            for (RObject* child : fChildren)
            {
                result = child->FindTypeOf<T>(includeSelf);
                if (result)
                {
                    return result;
                }
            }
            return nullptr;
        }

        /**
         * @brief Set the Parent object

         * @param object 
         * @param addAsChild - If false : You have to handle the livetime of the object yourself if you dont add it to a children array. (AddChild will automatically handle the livetime)
         */
        void SetParent(RObject* object, bool addAsChild = true);
    private:
        void RemoveChild(RObject* object);
    };

}