#include <iostream>
#include <list>
#include <GameEngineCore/GameEngineCore.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineCore::EngineStart("Kirby", hInstance);
	return 0;
}