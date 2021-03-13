#pragma once

#ifdef TI_PLATFORM_WINDOWS

extern TinyEngine::Application* TinyEngine::CreateApplication();
int main(int argc, char** argv)
{
	TinyEngine::Log::Init();
	TI_PROFILE_BEGIN_SESSION("Satrtup", "TinyProfile-Satrtup.json");
	auto app = TinyEngine::CreateApplication();
	TI_PROFILE_END_SESSION();

	TI_PROFILE_BEGIN_SESSION("Runtime", "TinyProfile-Runtime.json");
	app->Run();
	TI_PROFILE_END_SESSION();

	TI_PROFILE_BEGIN_SESSION("Shutdown", "TinyProfile-Shdow.json");
	delete app;
	TI_PROFILE_END_SESSION();
}
#endif // TI_PLATFORM_WINDOWS

