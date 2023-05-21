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

void Map::MapInit(const std::string& _PathName, const std::string& _BitMapFIleName)
{
	PathName = _PathName;
	DebugBitMapName = _BitMapFIleName;

	{
		GameEnginePath FolderPath;

		FolderPath.SetCurrentPath();
		FolderPath.MoveParentToExistsChild("Resources");

		FolderPath.MoveChild("Resources\\Map\\");

		MainSprite = ResourcesManager::GetInst().CreateSpriteFolder(PathName, FolderPath.PlusFilePath(PathName));
	}

	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Map\\" + _BitMapFIleName);

		DebugTexture = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Map);

		MainRenderer->CreateAnimation(PathName + "Idle", PathName);

		MainRenderer->ChangeAnimation(PathName + "Idle");
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(5.0f);

		MainRenderer->SetRenderPos((MainSprite->GetSprite(0).BaseTexture->GetScale() *= 5.0f).Half());
	}

	{
		DebugRenderer = CreateRenderer(_BitMapFIleName, RenderOrder::Map);
		DebugRenderer->SetRenderPos(DebugTexture->GetScale().Half());
	}

	MainRenderer->On();
	DebugRenderer->Off();
}

void Map::SwitchRender()
{
	SwitchRenderValue = !SwitchRenderValue;

	if (true == SwitchRenderValue)
	{
		MainRenderer->On();
		DebugRenderer->Off();
	}
	else
	{
		MainRenderer->Off();
		DebugRenderer->On();
	}
}