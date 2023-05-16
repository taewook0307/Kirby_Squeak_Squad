#pragma once

#include <string>
#include <filesystem>

class GameEnginePath
{
public:
	// constrcuter destructer
	GameEnginePath();
	GameEnginePath(const std::string& _Path);
	~GameEnginePath();

	// delete Function
	/*
	GameEnginePath(const GameEnginePath& _Other) = delete;
	GameEnginePath(GameEnginePath&& _Other) noexcept = delete;
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;
	*/

	std::string GetFileName();

	void GetCurrentPath();

	void MoveParent();

	void MoveParentToExistsChild(const std::string& _ChildPath);

	void MoveChild(const std::string& _ChildPath);

	std::string PlusFliePath(const std::string& _ChildPath);

	std::string GetStringPath()
	{
		return Path.string();
	}

	bool IsDirectory();
protected:

private:
	std::filesystem::path Path;
};