#pragma once

namespace GL {

    class GLShader : public Graphics::GShader
    {
    private:
        GLuint fRenderId;
    public:
        GLShader();
        ~GLShader();

        virtual void Compile(std::string_view vertexSource, std::string_view fragmentSource);
        virtual void Bind() const;
        virtual void Unbind() const;


		virtual void SetUniform1i(const char* name, const int& value);
		virtual void SetUniform1f(const char* name, const float& value);
		virtual void SetUniform2f(const char* name, const glm::vec2& value);
		virtual void SetUniform3f(const char* name, const glm::vec3& value);
		virtual void SetUniform4f(const char* name, const glm::vec4& value);
		virtual void SetUniformMat4(const char* name, const glm::mat4& value);
    private:
        int GetUniformLocation(const char* name);
    };

}