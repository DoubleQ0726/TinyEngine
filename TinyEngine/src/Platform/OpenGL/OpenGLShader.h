#pragma once
#include "Tiny/Render/Shader.h"
#include "glm/glm.hpp"

namespace TinyEngine
{
	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filePath);
		virtual ~OpenGLShader();
		
		inline const std::string& GetName() const override { return m_Name; }
		void Bind() const override;
		void Unbind() const override;

		void SetMat4f(const std::string& name, const glm::mat4& matrix) override;
		void Set4f(const std::string& name, float v0, float v1, float v2, float v3) override;
		void Set1i(const std::string& name, int value) override;
		void Set1f(const std::string& name, float value) override;

	private:
		unsigned int GetUniformLocation(const std::string& name);
		ShaderProgramSource ParseShader(const std::string& filePath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

		//Set Uniforms
		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	private:
		unsigned int m_RenderID;
		std::string m_FilePath;
		std::unordered_map<std::string, int> m_LocationCache;
		std::string m_Name;
	};
}
