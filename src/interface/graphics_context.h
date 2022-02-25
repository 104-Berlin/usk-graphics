#pragma once

namespace Graphics {

    #define GCLEAROPTION_COLOR_BUFFER      ((unsigned char)(1 << 0))
    #define GCLEAROPTION_DEPTH_BUFFER      ((unsigned char)(1 << 1))
    #define GCLEAROPTION_STENCIL_BUFFER    ((unsigned char)(1 << 2))
    #define GCLEAROPTION_ACCUM_BUFFER      ((unsigned char)(1 << 3))


    enum class GDrawMode
    {
        POINTS, 
        LINE_STRIP, 
        LINE_LOOP, 
        LINES, 
        TRIANGLE_STRIP, 
        TRIANGLE_FAN, 
        TRIANGLES,
    };

    enum class GCullMode
    {
        NONE,
        FRONT,
        BACK
    };

    class GContext 
    {
    public:
        virtual ~GContext() = default;
        virtual void Init(void* initData) = 0;

        virtual void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, unsigned char GCLEAROPTION = GCLEAROPTION_COLOR_BUFFER | GCLEAROPTION_DEPTH_BUFFER) = 0;

        virtual void DrawElements(size_t count, GIndexType indexType, GDrawMode drawMode) = 0;
        virtual void DrawArrays(size_t start, size_t count, Graphics::GDrawMode drawMode) = 0;

        virtual void EnableDepthTest(bool enable) = 0;
        virtual void SetFaceCullingMode(GCullMode mode) = 0;


        static GContext* Get();
        static void Init(GContext* context, void* initData);
        static void CleanUp();
    private:
        static GContext* sMainContext;
    };

}