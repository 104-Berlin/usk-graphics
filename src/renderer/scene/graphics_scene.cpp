#include "graphics_renderer.h"

using namespace Graphics;

GScene::GScene() 
{

}

void GScene::Add(GObject* object) 
{
    fChildren.push_back(object);
}