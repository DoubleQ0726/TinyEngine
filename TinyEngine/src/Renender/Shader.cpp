#include "TinyPch.h"
#include "Shader.h"
#include <glad/glad.h>

namespace TinyEngine
{

	Shader::Shader(const std::string& filePath)
		: m_FilePath(filePath), m_RenderID(0)
	{
		ShaderProgramSource source = ParseShader(filePath);
		m_RenderID = CreateShader(source.VertexSource, source.FragmentSource);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RenderID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RenderID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::SetUniform1i(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}


	void Shader::SetUniform1f(const std::string& name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void Shader::SetUniformMat4f(const std::string& name, glm::mat4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}

	unsigned int Shader::GetUniformLocation(const std::string& name)
	{
		if (m_LocationCache.find(name) != m_LocationCache.end())
			return m_LocationCache[name];

		int location = glGetUniformLocation(m_RenderID, name.c_str());
		if (location == -1)
			std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
		m_LocationCache[name] = location;
		return location;
	}


	ShaderProgramSource Shader::ParseShader(const std::string& filePath)
	{
		std::ifstream stream(filePath);
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

	unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
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

	unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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