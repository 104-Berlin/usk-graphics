#pragma once

namespace Graphics {

    class GShader
    {
    public:
        virtual void Compile(std::string_view vertexSource, std::string_view fragmentSource) = 0;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;


		virtual void SetUniform1i(const char* name, const int& value) = 0;
		virtual void SetUniform1f(const char* name, const float& value) = 0;
		virtual void SetUniform2f(const char* name, const glm::vec2& value) = 0;
		virtual void SetUniform3f(const char* name, const glm::vec3& value) = 0;
		virtual void SetUniform4f(const char* name, const glm::vec4& value) = 0;
		virtual void SetUniformMat4(const char* name, const glm::mat4& value) = 0;
    };

}