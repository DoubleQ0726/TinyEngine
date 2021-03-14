#pragma once
#include "glm/glm.hpp"
#include "Tiny/Core/Core.h"

namespace TinyEngine
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual const std::string& GetName() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetMat4f(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void Set4f(const std::string& name, float v0, float v1, float v2, float v3) = 0;
		virtual void Set1i(const std::string& name, int value) = 0;
		virtual void Set1f(const std::string& name, float value) = 0;

		static Ref<Shader> Create(const std::string& filePath);
	};

	class ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filePath);
		Ref<Shader> Load(const std::string& name, const std::string& filePath);

		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}
