#pragma once
#include "glm/glm.hpp"

namespace TinyEngine
{
	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	public:
		Shader(const std::string& filePath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		//Set Uniforms
		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformMat4f(const std::string& name, glm::mat4& matrix);

	private:
		unsigned int GetUniformLocation(const std::string& name);
		ShaderProgramSource ParseShader(const std::string& filePath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	private:
		unsigned int m_RenderID;
		std::string m_FilePath;
		std::unordered_map<std::string, int> m_LocationCache;
	};
}
