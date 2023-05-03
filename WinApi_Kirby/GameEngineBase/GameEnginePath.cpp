#include "GameEnginePath.h"

GameEnginePath::GameEnginePath()
{
}

GameEnginePath::~GameEnginePath()
{
}

void GameEnginePath::GetCurrentPath()
{
	Path = std::filesystem::current_path();
}