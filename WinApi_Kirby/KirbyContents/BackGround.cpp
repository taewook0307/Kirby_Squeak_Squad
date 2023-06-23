#include "BackGround.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

#pragma comment(lib, "msimg32.lib")

BackGround* BackGround::MainBackGround;

BackGround::BackGround()
{
	MainBackGround = this;
}

BackGround::~BackGround()
{
}

void BackGround::Start()
{
	if (nullptr == ResourcesManager::GetInst().FindTexture("MainBackGround.Bmp"))
	{
		GameEnginePath BackGroundPath;
		BackGroundPath.SetCurrentPath();
		BackGroundPath.MoveParentToExistsChild("Resources");
		BackGroundPath.MoveChild("Resources\\BackGround\\");

		MainTexture = ResourcesManager::GetInst().TextureLoad(BackGroundPath.PlusFilePath("MainBackGround.Bmp"));
	}

	float4 Scale = MainTexture->GetScale();

	MainRenderer = CreateRenderer("MainBackGround.Bmp", RenderOrder::BackGround);
	MainRenderer->SetRenderPos(Scale.Half());
	MainRenderer->SetRenderScale(Scale);
}

void BackGround::Update(float _Delta)
{
	SetPos(MainBackGround->GetPos());
}