#include "graphics_renderer.h"

using namespace Graphics;

GScene::GScene() 
{

}

void GScene::Add(GObject* object) 
{
    fChildren.push_back(object);
}

void GScene::Traverse(const std::function<void(GObject*)>& fn) 
{
    std::function<void(GObject*, std::function<void(GObject*)>)> traverse_fn;
    traverse_fn = [&traverse_fn](GObject* object, std::function<void(GObject*)> callback){
        if (!object) { return; }

        for (GObject* child : object->GetChildren())
        {
            callback(child);
            traverse_fn(child, callback);
        }
    };

    for (GObject* child : fChildren)
    {
        fn(child);
        traverse_fn(child, fn);
    }
}