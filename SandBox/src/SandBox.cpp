#include <Tiny.h>

class ExampleLayer : public TinyEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		TI_INFO("Exampler::Update");
	}

	void OnEvent(TinyEngine::Event& e) override
	{
		TI_TRACE(e);
	}
};

class SandBox : public TinyEngine::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
	}

	~SandBox()
	{

	}
};

TinyEngine::Application* TinyEngine::CreateApplication()
{
	return new SandBox();
}