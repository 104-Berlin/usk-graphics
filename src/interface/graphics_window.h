#pragma once

namespace Graphics {

    class GWindow
    {
        virtual void Create(const char* title, int width, int height) = 0;
        virtual void Destroy() = 0;
        virtual void SwapBuffer() = 0;
        virtual void PollEvents() = 0;
        virtual bool IsOpen() = 0;

        virtual void MakeContextCurrent() = 0; // This is currently just for opengl. See for other rendering backends
    };
    
}