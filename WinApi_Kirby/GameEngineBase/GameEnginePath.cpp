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

void GameEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

void GameEnginePath::MoveChild()
{

}