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

void Map::Start()
{
	
}

void Map::MapInit(const std::string& _FolderName)
{
	FolderName = _FolderName;

	{
		GameEnginePath FolderPath;

		FolderPath.SetCurrentPath();
		FolderPath.MoveParentToExistsChild("Resources");

		FolderPath.MoveChild("Resources\\Map\\");

		MainTexture = ResourcesManager::GetInst().CreateSpriteFolder(FolderName, FolderPath.PlusFliePath(FolderName));
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Map);

		MainRenderer->CreateAnimation(FolderName + "Idle", FolderName);

		MainRenderer->ChangeAnimation(FolderName + "Idle");
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(5.0f);

		MainRenderer->SetRenderPos((MainTexture->GetSprite(0).BaseTexture->GetScale() *= 5.0f).Half());
	}
}