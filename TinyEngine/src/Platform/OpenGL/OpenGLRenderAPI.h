#pragma once
#include "Renender/RendererAPI.h"

namespace TinyEngine
{
	class OpenGLRenderAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndex(const std::shared_ptr<VertexArray>& vertexArray) override;

	private:

	};
}