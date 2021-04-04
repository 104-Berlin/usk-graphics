#pragma once

namespace GL {

    class GLContext : public Graphics::GContext
    {
    public:
        virtual void Init(void* initData) override;

        virtual void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, unsigned char GCLEAROPTIONS = 0) override;
    };

}