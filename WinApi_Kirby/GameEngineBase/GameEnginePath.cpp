#include "GameEnginePath.h"
#include "GameEngineDebug.h"

GameEnginePath::GameEnginePath()
{
}

GameEnginePath::GameEnginePath(const std::string& _Path)
	: Path(_Path)
{
}

GameEnginePath::~GameEnginePath()
{
}

std::string GameEnginePath::GetFileName()
{
	return Path.filename().string();
}

void GameEnginePath::GetCurrentPath()
{
	Path = std::filesystem::current_path();
}

void GameEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

void GameEnginePath::MoveParentToExistsChild(const std::string& _ChildPath)
{
	while (true)
	{
		std::filesystem::path CheckPath = Path;

		CheckPath.append(_ChildPath);

		if (false == std::filesystem::exists(CheckPath))
		{
			MoveParent();
		}
		else
		{
			break;
		}

		if (Path == Path.root_path())
		{
			MsgBoxAssert(_ChildPath + "경로를 가지는 파일이나 폴더가 존재하지 않습니다.");
		}
	}
}

void GameEnginePath::MoveChild(const std::string& _ChildPath)
{
	std::filesystem::path CheckPath = Path;

	CheckPath.append(_ChildPath);

	if (false == std::filesystem::exists(CheckPath))
	{
		MsgBoxAssert("존재하지 않는 경로입니다" + CheckPath.string());
	}
	Path = CheckPath;
}

std::string GameEnginePath::PlusFliePath(const std::string& _ChildPath)
{
	std::filesystem::path CheckPath = Path;

	CheckPath.append(_ChildPath);

	if (false == std::filesystem::exists(CheckPath))
	{
		MsgBoxAssert("존재하지 않는 경로로 이동하려고 했습니다" + CheckPath.string());
	}

	return CheckPath.string();
}

bool GameEnginePath::IsDirectory()
{
	return std::filesystem::is_directory(Path);
}