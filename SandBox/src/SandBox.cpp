#include <Tiny.h>

class SandBox : public TinyEngine::Application
{
public:
	SandBox()
	{

	}

	~SandBox()
	{

	}
};

TinyEngine::Application* TinyEngine::CreateApplication()
{
	return new SandBox();
}