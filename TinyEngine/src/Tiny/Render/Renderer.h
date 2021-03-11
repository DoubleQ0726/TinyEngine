#pragma once
#include "RendererAPI.h"
#include "Tiny/Render/Shader.h"
#include "Tiny/Render/OrthographicCamera.h"
namespace TinyEngine
{
	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, 
			const Ref<VertexArray>& vertexArray, 
			const glm::mat4& transform = glm::mat4(1.0));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:

		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* s_SceneData;
	};
}