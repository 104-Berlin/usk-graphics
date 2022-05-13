#pragma once

namespace Renderer {

    class RScene : public RObject
    {
    public:
        using TObjectDeleteFunc = std::function<void(RObject*)>;
    private:
        TObjectDeleteFunc fObjectDeleteFunc;
    public:
        RScene();

        void Traverse(const std::function<void(RObject*)>& fn);

        void DeleteObject(RObject* object);

        void SetObjectDeleteFunction(TObjectDeleteFunc func);
    };

}