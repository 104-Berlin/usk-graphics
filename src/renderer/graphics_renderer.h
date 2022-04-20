#pragma once

#include <queue>
#include <vector>



#ifdef R_PI
#undef R_PI
#endif

#define R_PI 3.14159f

#include "graphics_interface.h"
#include "graphics_render_command.h"
#include "graphics_wrapper.h"



#include "scene/graphics_object.h"
#include "scene/graphics_scene.h"
#include "scene/graphics_mesh.h"
#include "scene/graphics_texture_object.h"
#include "scene/graphics_curve.h"
#include "scene/graphics_line.h"
#include "scene/graphics_grid.h"

#include "graphics_camera.h"

#include "graphics_renderer_base.h"
#include "graphics_renderer_3d.h"
#include "graphics_renderer_imgui.h"

