#include "graphics_opengl.h"

using namespace GL;


GLShader::GLShader() 
    : fRenderId(0)
{
    
}

GLShader::~GLShader() 
{
    if (fRenderId)
    {
		glCall(glDeleteProgram(fRenderId));
    }
}

void GLShader::Compile(std::string_view vertexSource, std::string_view fragmentSource) 
{
	const GLchar * source = (const GLchar*)vertexSource.data();
	GLuint vertexShader = glCall(glCreateShader(GL_VERTEX_SHADER));

	glCall(glShaderSource(vertexShader, 1, &source, 0));

	// Compile the vertex shader
	glCall(glCompileShader(vertexShader));

	GLint isCompiled = 0;
	glCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled));
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glCall(glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength));

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glCall(glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]));

		// We don't need the shader anymore.
		glCall(glDeleteShader(vertexShader));

		// Use the infoLog as you see fit.
		printf("%s\n", infoLog.data());

		// In this simple fRendererID, we'll just leave
		return;
	}

	// Create an empty fragment shader handle
	GLuint fragmentShader = glCall(glCreateShader(GL_FRAGMENT_SHADER));

	// Send the fragment shader source code to GL
	// Note that std::EString's .c_str is NULL character terminated.
	source = (const GLchar *)fragmentSource.data();
	glCall(glShaderSource(fragmentShader, 1, &source, 0));

	// Compile the fragment shader
	glCall(glCompileShader(fragmentShader));

	glCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled));
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glCall(glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength));

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glCall(glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]));

		// We don't need the shader anymore.
		glCall(glDeleteShader(fragmentShader));
		// Either of them. Don't leak shaders.
		glCall(glDeleteShader(vertexShader));

		// Use the infoLog as you see fit.
		printf("%s\n", infoLog.data());

		// In this simple fRendererID, we'll just leave
		return;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a fRendererID.
	// Get a fRendererID object.
	fRenderId = glCall(glCreateProgram());

	// Attach our shaders to our fRendererID
	glCall(glAttachShader(fRenderId, vertexShader));
	glCall(glAttachShader(fRenderId, fragmentShader));

	// Link our fRendererID
	glCall(glLinkProgram(fRenderId));

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glCall(glGetProgramiv(fRenderId, GL_LINK_STATUS, (int *)&isLinked));
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glCall(glGetProgramiv(fRenderId, GL_INFO_LOG_LENGTH, &maxLength));

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glCall(glGetProgramInfoLog(fRenderId, maxLength, &maxLength, &infoLog[0]));

		// We don't need the fRendererID anymore.
		glCall(glDeleteProgram(fRenderId));
		// Don't leak shaders either.
		glCall(glDeleteShader(vertexShader));
		glCall(glDeleteShader(fragmentShader));

		// Use the infoLog as you see fit.
		printf("%s\n", infoLog.data());

		// In this simple fRendererID, we'll just leave
		return;
	}

	// Always detach shaders after a successful link.
	glCall(glDetachShader(fRenderId, vertexShader));
	glCall(glDetachShader(fRenderId, fragmentShader));
}

void GLShader::Bind() const
{
	glCall(glUseProgram(fRenderId));
}

void GLShader::Unbind() const
{
	glCall(glUseProgram(0));
}

void GLShader::SetUniform1i(const char* name, const int& value)
{
	glCall(glUniform1i(GetUniformLocation(name), value));
}

void GLShader::SetUniform1f(const char* name, const float& value)
{
	glCall(glUniform1f(GetUniformLocation(name), value));
}

void GLShader::SetUniform2f(const char* name, const glm::vec2& value)
{
	glCall(glUniform2f(GetUniformLocation(name), value.x, value.y));
}

void GLShader::SetUniform3f(const char* name, const glm::vec3& value)
{
	glCall(glUniform3f(GetUniformLocation(name), value.x, value.y, value.z));
}

void GLShader::SetUniform4f(const char* name, const glm::vec4& value)
{
	glCall(glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w));
}

void GLShader::SetUniformMat4(const char* name, const glm::mat4& value)
{
	glCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]));
}

int GLShader::GetUniformLocation(const char* name)
{   
    int result = glGetUniformLocation(fRenderId, name);
    if (result == -1)
	{
        printf("Could not find Uniform %s\n", name);
		exit(1);
	}
    return result;
}