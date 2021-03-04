#pragma once

#ifdef TI_PLATFORM_WINDOWS

extern TinyEngine::Application* TinyEngine::CreateApplication();
int main(int argc, char** argv)
{
	auto app = TinyEngine::CreateApplication();
	app->Run();
	delete app;
}
#endif // TI_PLATFORM_WINDOWS

