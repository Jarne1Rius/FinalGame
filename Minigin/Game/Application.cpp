
#include "Minigin.h"
#include "SceneManager.h"
#include <fstream>
#define ProjectTest

#ifdef ProjectTest
#include "TestScene.h"
#endif

int main()
{
	auto engine = new Rius::Minigin();
	engine->Initialize();
#ifdef ProjectTest
	auto Scene = new TestScene();
	Rius::SceneManager::GetInstance().AddScene(Scene);
#endif
	engine->Run();
	delete Scene;
	delete engine;
} 