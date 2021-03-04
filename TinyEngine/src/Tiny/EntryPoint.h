#pragma once

#ifdef TI_PLATFORM_WINDOWS

extern TinyEngine::Application* TinyEngine::CreateApplication();
int main(int argc, char** argv)
{
	TinyEngine::Log::Init();
	TI_CORE_WARN("Initialized Log!");
	int a = 5;
	TI_INFO("Hello Var={0}", a);
	auto app = TinyEngine::CreateApplication();
	app->Run();
	delete app;
}
#endif // TI_PLATFORM_WINDOWS

