#include <iostream>
#include <Minigin.h>
#include "vld.h"
#include "LevelManager.h"

int main(int, char* []) {
	dae::Minigin engine;

	engine.Initialize();
	int gameMode = -1;
	while (gameMode < 0 || gameMode > 2)
	{
		std::cout << "Choose mode:\n";
		std::cout << "0 singlePlayer\n";
		std::cout << "1 co-op\n";
		std::cout << "2 versus\n"; std::cin >> gameMode;
		std::cout << "\n";
	}
	if (gameMode == 0)
	{
		std::cout << "Use A,B,X,Y\n";
	}
	if (gameMode == 1)
	{
		std::cout << "Player 1:\n";
		std::cout << "Use A,B,X,Y\n";
		std::cout << "Player 2:\n";
		std::cout << "Use DPAD\n";
	}
	if (gameMode == 2)
	{
		std::cout << "Qbert:\n";
		std::cout << "Use A,B,X,Y\n";
		std::cout << "Coily:\n";
		std::cout << "Use Keyboard arrows\n";
	}
	std::cout << gameMode;
	
	qbert::LevelManager::GetInstance().LoadLevel(L"../Data/General.json",gameMode);
	engine.Run();
	
	return 0;
}