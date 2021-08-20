#pragma once

namespace Graphics {

    class GScene
    {
    private:
        std::vector<GObject*> fChildren;
    public:
        GScene();

        void Add(GObject* object);
    };

}