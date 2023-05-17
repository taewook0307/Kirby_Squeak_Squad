#include "Map.h"
#include "KirbyGameEnum.h"

#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

Map::Map()
{
}

Map::~Map()
{
}

void Map::MapAnimation(const std::string& _PathName)
{
	PathName = _PathName;

	{
		GameEnginePath FolderPath;

		FolderPath.SetCurrentPath();
		FolderPath.MoveParentToExistsChild("Resources");

		FolderPath.MoveChild("Resources\\Map\\");

		MainSprite = ResourcesManager::GetInst().CreateSpriteFolder(PathName, FolderPath.PlusFliePath(PathName));
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Map);

		MainRenderer->CreateAnimation(PathName + "Idle", PathName);

		MainRenderer->ChangeAnimation(PathName + "Idle");
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(5.0f);

		MainRenderer->SetRenderPos((MainSprite->GetSprite(0).BaseTexture->GetScale() *= 5.0f).Half());
	}
}