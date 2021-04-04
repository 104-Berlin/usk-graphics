#pragma once

namespace Graphics {

    static constexpr unsigned char GCLEAROPTION_COLOR_BUFFER      = 1 << 0;
    static constexpr unsigned char GCLEAROPTION_DEPTH_BUFFER      = 1 << 1;
    static constexpr unsigned char GCLEAROPTION_STENCIL_BUFFER    = 1 << 2;
    static constexpr unsigned char GCLEAROPTION_ACCUM_BUFFER      = 1 << 3;

    class GContext 
    {
    public:
        virtual void Init(void* initData) = 0;

        virtual void Clear(float r, float g, float b, unsigned char GCLEAROPTION) = 0;
    };

}