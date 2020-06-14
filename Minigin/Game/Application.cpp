
#pragma warning(push)
#pragma warning( disable : 4201)
#include <vld.h>
#include "Minigin.h"
#include "SceneManager.h"
#define ProjectTest

#ifdef ProjectTest
#include "TestScene.h"
#endif
#pragma warning( pop ) 

int main()
{
	auto engine = new Rius::Minigin();
	engine->Initialize();
	
#ifdef ProjectTest
	auto Scene = new TestScene();
	Rius::SceneManager::GetInstance().AddScene(Scene);
#endif
	
	engine->Run();

	
	delete engine;
} 