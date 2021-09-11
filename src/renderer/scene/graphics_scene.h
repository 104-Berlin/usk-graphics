#pragma once

namespace Renderer {

    class RScene : public RObject
    {
    public:
        RScene();

        void Traverse(const std::function<void(RObject*)>& fn);

        void DeleteObject(RObject* object);
    };

}