#pragma once

namespace Graphics {

    static constexpr unsigned char GCLEAROPTION_COLOR_BUFFER      = 1 << 0;
    static constexpr unsigned char GCLEAROPTION_DEPTH_BUFFER      = 1 << 1;
    static constexpr unsigned char GCLEAROPTION_STENCIL_BUFFER    = 1 << 2;
    static constexpr unsigned char GCLEAROPTION_ACCUM_BUFFER      = 1 << 3;


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

    class GContext 
    {
    public:
        virtual ~GContext() = default;
        virtual void Init(void* initData) = 0;

        virtual void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, unsigned char GCLEAROPTION = 0) = 0;

        virtual void DrawElements(size_t count, GIndexType indexType, GDrawMode drawMode) = 0;
        virtual void DrawArrays(size_t start, size_t count, Graphics::GDrawMode drawMode) = 0;


        static GContext* Get();
        static void Init(GContext* context, void* initData);
        static void CleanUp();
    private:
        static GContext* sMainContext;
    };

}