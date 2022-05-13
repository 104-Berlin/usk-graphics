#include "graphics_renderer.h"

using namespace Renderer;

RScene::RScene() 
{

}

void RScene::Traverse(const std::function<void(RObject*)>& fn) 
{
    std::function<void(RObject*, std::function<void(RObject*)>)> traverse_fn;
    traverse_fn = [&traverse_fn](RObject* object, std::function<void(RObject*)> callback){
        if (!object) { return; }

        for (RObject* child : object->GetChildren())
        {
            callback(child);
            traverse_fn(child, callback);
        }
    };

    for (RObject* child : fChildren)
    {
        fn(child);
        traverse_fn(child, fn);
    }
}

void RScene::DeleteObject(RObject* object) 
{
    if (!object) { printf("WARN: Could not delete object. It was allready destroyed!"); return; }
    object->GetParent()->RemoveChild(object);
    if (fObjectDeleteFunc)
    {
        fObjectDeleteFunc(object);
    }
    delete object;
}


void RScene::SetObjectDeleteFunction(TObjectDeleteFunc func)
{
    fObjectDeleteFunc = func;
}