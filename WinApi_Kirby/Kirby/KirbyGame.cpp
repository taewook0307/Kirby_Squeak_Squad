#include <iostream>
#include <list>
#include <GameEngineCore/GameEngineCore.h>
#include <KirbyContents/TitleLevel.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::EngineStart("Kirby", hInstance);
	return 0;
}