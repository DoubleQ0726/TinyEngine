#include "TinyPch.h"
#include "OpenGLShader.h"
#include "Tiny/Core/Log.h"
#include <glad/glad.h>

namespace TinyEngine
{
	OpenGLShader::OpenGLShader(const std::string& filePath)
		: m_FilePath(filePath), m_RenderID(0)
	{
		ShaderProgramSource source = ParseShader(filePath);
		m_RenderID = CreateShader(source.VertexSource, source.FragmentSource);

		//Extract name from filePath
		// assets/shaders/Texture.glsl
		auto lastSlash = filePath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filePath.rfind(".");
		auto count = lastDot == std::string::npos ? (filePath.size() - lastSlash) : (lastDot - lastSlash);
		m_Name = filePath.substr(lastSlash, count);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RenderID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RenderID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetMat4f(const std::string& name, const glm::mat4& matrix)
	{
		SetUniformMat4f(name, matrix);
	}

	void OpenGLShader::Set4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		SetUniform4f(name, v0, v1, v2, v3);
	}

	void OpenGLShader::Set1i(const std::string& name, int value)
	{
		SetUniform1i(name, value);
	}

	void OpenGLShader::SetUniform1i(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}


	void OpenGLShader::SetUniform1f(const std::string& name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void OpenGLShader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}

	unsigned int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		if (m_LocationCache.find(name) != m_LocationCache.end())
			return m_LocationCache[name];

		int location = glGetUniformLocation(m_RenderID, name.c_str());
		if (location == -1)
			std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
		m_LocationCache[name] = location;
		return location;
	}


	ShaderProgramSource OpenGLShader::ParseShader(const std::string& filePath)
	{
		std::ifstream stream(filePath);
		if (!stream)
			TI_CORE_ERROR("Could not open file '{0}'", filePath);
		enum class ShaderType
		{
			None = -1, VERTEX = 0, FRAGMENT = 1
		};
		std::stringstream ss[2];
		ShaderType type = ShaderType::None;
		std::string line;
		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else
			{
				if (type == ShaderType::None)
					return {};
				ss[(type == ShaderType::VERTEX ? 0 : 1)] << line << "\n";
			}
		}

		return { ss[0].str(), ss[1].str() };
	}

	unsigned int OpenGLShader::CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)_malloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << "Failed to Compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "Shader\n";
			std::cout << message << std::endl;
			glDeleteShader(id);
			return 0;
		}
		//std::cout << "ID: " << id << std::endl;
		return id;
	}

	unsigned int OpenGLShader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);
		//std::cout << "Program: " << program << std::endl;
		return program;
	}
}