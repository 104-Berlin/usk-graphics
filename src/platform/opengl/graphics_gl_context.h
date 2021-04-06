#pragma once

namespace GL {

    static GLenum IndexTypeToOpenGLType(Graphics::GIndexType type)
    {
        switch (type)
        {
        case Graphics::GIndexType::UNSIGNED_BYTE:   return GL_UNSIGNED_BYTE;
        case Graphics::GIndexType::UNSIGNED_SHORT:  return GL_UNSIGNED_SHORT;
        case Graphics::GIndexType::UNSIGNED_INT :   return GL_UNSIGNED_INT;
        }
    }

    static GLenum DrawModeToOpenGLMode(Graphics::GDrawMode mode)
    {
        switch (mode)
        {
        case Graphics::GDrawMode::POINTS:          return GL_POINTS;
        case Graphics::GDrawMode::LINE_STRIP:      return GL_LINE_STRIP;
        case Graphics::GDrawMode::LINE_LOOP:       return GL_LINE_LOOP;
        case Graphics::GDrawMode::LINES:           return GL_LINES;
        case Graphics::GDrawMode::TRIANGLE_STRIP:  return GL_TRIANGLE_STRIP;
        case Graphics::GDrawMode::TRIANGLE_FAN:    return GL_TRIANGLE_FAN;
        case Graphics::GDrawMode::TRIANGLES:       return GL_TRIANGLES;
        }
    }

    class GLContext : public Graphics::GContext
    {
    public:
        virtual void Init(void* initData) override;

        virtual void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, unsigned char GCLEAROPTIONS = 0) override;

        virtual void DrawElements(size_t count, Graphics::GIndexType indexType, Graphics::GDrawMode drawMode) override;
        virtual void DrawArrays(size_t start, size_t count, Graphics::GDrawMode drawMode) override;
    };

}