#pragma once

#include <string>
#include <filesystem>

class GameEnginePath
{
public:
	// constrcuter destructer
	GameEnginePath();
	~GameEnginePath();

	// delete Function
	GameEnginePath(const GameEnginePath& _Other) = delete;
	GameEnginePath(GameEnginePath&& _Other) noexcept = delete;
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;

	void GetCurrentPath();

	void MoveParent();

protected:

private:
	std::filesystem::path Path;
};