#include <Minigin.h>
#include "vld.h"
#include "LevelManager.h"

int main(int, char* []) {
	dae::Minigin engine;

	engine.Initialize();
	qbert::LevelManager::GetInstance().LoadLevel();
	engine.Run();
	
	return 0;
}